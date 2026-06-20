param(
    [string]$BaseUrl = "http://127.0.0.1:8000/api",
    [int]$TimeoutSeconds = 20,
    [string]$ResendIdentifier,
    [switch]$ResendOnly,
    [switch]$CreateUnverifiedResendTarget
)

$ErrorActionPreference = "Stop"

function Wait-ApiReady {
    param(
        [string]$Url,
        [int]$TimeoutSeconds
    )

    $deadline = (Get-Date).AddSeconds($TimeoutSeconds)
    while ((Get-Date) -lt $deadline) {
        try {
            Invoke-WebRequest -Method Get -Uri "$Url/test_email.php" -TimeoutSec 3 | Out-Null
            return
        } catch {
            try {
                $response = $_.Exception.Response
                if ($response -and [int]$response.StatusCode -eq 401) {
                    return
                }
            } catch {
            }
        }

        Start-Sleep -Milliseconds 500
    }

    throw "API tidak siap di $Url dalam $TimeoutSeconds detik."
}

function Invoke-FormPost {
    param(
        [string]$Url,
        [hashtable]$Body
    )

    Invoke-RestMethod -Method Post -Uri $Url -Body $Body -ContentType "application/x-www-form-urlencoded"
}

function Register-PreviewAccount {
    param(
        [string]$Url,
        [string]$Username,
        [string]$Email,
        [string]$Password
    )

    $registerResponse = Invoke-FormPost -Url "$Url/register.php" -Body @{
        action   = "register"
        username = $Username
        email    = $Email
        password = $Password
    }

    if (-not $registerResponse.local_preview) {
        throw "Register tidak mengembalikan local_preview. Pastikan APP_ENV=local dan UCP_LOCAL_MAIL_MODE=preview."
    }

    return $registerResponse
}

function Get-SafeMessage {
    param(
        [string]$Message
    )

    if ([string]::IsNullOrWhiteSpace($Message)) {
        return $null
    }

    $normalized = $Message.ToLowerInvariant()

    if ($normalized.Contains("local-only otp preview")) { return "local preview active" }
    if ($normalized.Contains("registrasi sukses")) { return "register OTP issued" }
    if ($normalized.Contains("kode otp untuk reset kata sandi telah dikirim")) { return "forgot OTP issued" }
    if ($normalized.Contains("verifikasi email berhasil")) { return "verify success" }
    if ($normalized.Contains("tunggu 30 menit")) { return "resend blocked by cooldown" }
    if ($normalized.Contains("sudah diverifikasi")) { return "already verified" }
    if ($normalized.Contains("akun tidak ditemukan")) { return "account not found" }
    if ($normalized.Contains("kode otp salah") -or $normalized.Contains("tidak valid")) { return "invalid OTP" }
    if ($normalized.Contains("kedaluwarsa") -or $normalized.Contains("habis masa berlaku")) { return "expired OTP" }
    if ($normalized.Contains("unauthorized")) { return "unauthorized" }
    if ($normalized.Contains("gagal mengirim email otp")) { return "mail delivery failed" }
    if ($normalized.Contains("terjadi kesalahan sistem")) { return "endpoint error" }
    if ($normalized.Contains("invalid action")) { return "invalid action" }

    return "response received"
}

function Get-OutcomeCategory {
    param(
        $Response
    )

    $status = [string]$Response.status
    $safeMessage = Get-SafeMessage -Message ([string]$Response.message)

    if ($status -eq "success" -or $status -eq "success_verify" -or $status -eq "discord_required") {
        return "success"
    }

    if ($safeMessage -eq "resend blocked by cooldown") {
        return "cooldown"
    }

    if ($safeMessage -eq "unauthorized") {
        return "unauthorized"
    }

    if ($safeMessage -eq "invalid OTP" -or $safeMessage -eq "expired OTP") {
        return "invalid_otp"
    }

    return "endpoint_error"
}

function New-FlowResult {
    param(
        [string]$Name,
        $Response,
        [hashtable]$Extra = @{}
    )

    $result = [ordered]@{
        status  = [string]$Response.status
        message = Get-SafeMessage -Message ([string]$Response.message)
        outcome = Get-OutcomeCategory -Response $Response
    }

    foreach ($key in $Extra.Keys) {
        $result[$key] = $Extra[$key]
    }

    return $result
}

Wait-ApiReady -Url $BaseUrl -TimeoutSeconds $TimeoutSeconds

$stamp = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
$username = "cpv_$stamp"
$email = "codex_preview_$stamp@example.com"
$password = "PreviewOnly123!"
$resendProbeUsername = "cpr_$stamp"
$resendProbeEmail = "codex_resend_$stamp@example.com"
$register = $null
$verify = $null
$forgot = $null
$registerProven = $false
$verifyProven = $false
$forgotProven = $false
$flowMode = if ($ResendOnly) { "resend_only" } else { "full_preview" }

if (-not $ResendOnly) {
    $register = Register-PreviewAccount -Url $BaseUrl -Username $username -Email $email -Password $password
    $verifyOtp = $register.local_preview.otp_code

    $verify = Invoke-FormPost -Url "$BaseUrl/verify.php" -Body @{
        action   = "verify_otp"
        username = $username
        otp_code = $verifyOtp
        device   = "PowerShell Preview Smoke"
        ip       = "127.0.0.1"
        location = "Local Preview"
    }

    $forgot = Invoke-FormPost -Url "$BaseUrl/forgot.php" -Body @{
        action = "forgot_password"
        email  = $email
    }

    $registerProven = ($register.status -eq "success_verify" -and $null -ne $register.local_preview)
    $verifyProven = ($verify.status -eq "success" -or $verify.status -eq "discord_required")
    $forgotProven = ($forgot.status -eq "success" -and $null -ne $forgot.local_preview)
}

$shouldCreateResendTarget = $CreateUnverifiedResendTarget -or [string]::IsNullOrWhiteSpace($ResendIdentifier)
$resendScenario = if ($shouldCreateResendTarget) { "fresh_unverified_target" } else { "existing_unverified" }

if ($shouldCreateResendTarget) {
    $resendProbeRegister = Register-PreviewAccount -Url $BaseUrl -Username $resendProbeUsername -Email $resendProbeEmail -Password $password
    $resendTarget = $resendProbeUsername
} else {
    $resendTarget = $ResendIdentifier
}

$resend = Invoke-FormPost -Url "$BaseUrl/resend_otp.php" -Body @{
    action   = "resend_otp"
    username = $resendTarget
}

[bool]$resendProven = ($resend.status -eq "success")
[bool]$resendBlockedByCooldown = ((Get-OutcomeCategory -Response $resend) -eq "cooldown")
[bool]$task54Ready = ($registerProven -and $verifyProven -and $forgotProven -and $resendProven)

[ordered]@{
    base_url       = $BaseUrl
    mode           = $flowMode
    task_5_4_ready = $task54Ready
    register       = if ($register) {
        New-FlowResult -Name "register" -Response $register -Extra @{
            has_local_preview = ($null -ne $register.local_preview)
        }
    } else {
        [ordered]@{ skipped = $true }
    }
    verify         = if ($verify) {
        New-FlowResult -Name "verify" -Response $verify -Extra @{
            completed_verification = $verifyProven
        }
    } else {
        [ordered]@{ skipped = $true }
    }
    forgot         = if ($forgot) {
        New-FlowResult -Name "forgot" -Response $forgot -Extra @{
            has_local_preview = ($null -ne $forgot.local_preview)
        }
    } else {
        [ordered]@{ skipped = $true }
    }
    resend         = New-FlowResult -Name "resend" -Response $resend -Extra @{
        scenario          = $resendScenario
        target_supplied   = (-not [string]::IsNullOrWhiteSpace($ResendIdentifier))
        created_unverified_target = $shouldCreateResendTarget
        resend_target_identifier = $resendTarget
        has_local_preview = ($null -ne $resend.local_preview)
        has_cooldown      = ($null -ne $resend.cooldown)
        blocked_by_cooldown = $resendBlockedByCooldown
    }
} | ConvertTo-Json -Depth 5
