param(
    [string]$BaseUrl = "http://127.0.0.1:8000/api",
    [int]$TimeoutSeconds = 20
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

Wait-ApiReady -Url $BaseUrl -TimeoutSeconds $TimeoutSeconds

$stamp = [DateTimeOffset]::UtcNow.ToUnixTimeSeconds()
$username = "codex_preview_$stamp"
$email = "codex_preview_$stamp@example.com"
$password = "PreviewOnly123!"

$register = Invoke-FormPost -Url "$BaseUrl/register.php" -Body @{
    action   = "register"
    username = $username
    email    = $email
    password = $password
}

if (-not $register.local_preview) {
    throw "Register tidak mengembalikan local_preview. Pastikan APP_ENV=local dan UCP_LOCAL_MAIL_MODE=preview."
}

$verifyOtp = $register.local_preview.otp_code

$resend = Invoke-FormPost -Url "$BaseUrl/resend_otp.php" -Body @{
    action   = "resend_otp"
    username = $username
}

$forgot = Invoke-FormPost -Url "$BaseUrl/forgot.php" -Body @{
    action = "forgot_password"
    email  = $email
}

$verify = Invoke-FormPost -Url "$BaseUrl/verify.php" -Body @{
    action   = "verify_otp"
    username = $username
    otp_code = $verifyOtp
    device   = "PowerShell Preview Smoke"
    ip       = "127.0.0.1"
    location = "Local Preview"
}

[ordered]@{
    base_url = $BaseUrl
    register = [ordered]@{
        status            = $register.status
        has_local_preview = ($null -ne $register.local_preview)
    }
    resend = [ordered]@{
        status            = $resend.status
        has_local_preview = ($null -ne $resend.local_preview)
        has_cooldown      = ($null -ne $resend.cooldown)
    }
    forgot = [ordered]@{
        status            = $forgot.status
        has_local_preview = ($null -ne $forgot.local_preview)
    }
    verify = [ordered]@{
        status   = $verify.status
        username = $verify.username
    }
} | ConvertTo-Json -Depth 5
