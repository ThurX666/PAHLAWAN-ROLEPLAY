
import React, { useState, useEffect } from 'react';
import { UserProfile } from '../types';
import { SettingsHeader } from './settings/SettingsHeader';
import { ProfileForm } from './settings/ProfileForm';
import { DiscordCard } from './settings/DiscordCard';
import { SecurityCard } from './settings/SecurityCard';
import { DataRequestCard } from './settings/DataRequestCard';
import { isPreviewEnv, API_URL, getResolvedApiUrl } from '../config';

interface SettingsProps {
  userName: string;
  initialProfile: UserProfile;
  is2FAEnabled: boolean;
  onDiscordLinked?: (discordUsername: string) => void;
  onPasswordChanged?: (dateString: string) => void;
}

export const Settings: React.FC<SettingsProps> = ({ userName, initialProfile, is2FAEnabled, onDiscordLinked, onPasswordChanged }) => {
  const [loading, setLoading] = useState(false);
  const [profile, setProfile] = useState<UserProfile>(initialProfile);
  const [twoFAStatus, setTwoFAStatus] = useState<boolean>(is2FAEnabled);

  useEffect(() => {
    if (!isPreviewEnv()) {
      const fetchProfile = async () => {
        try {
          const res = await fetch(`${API_URL}/api_profile.php?username=${encodeURIComponent(userName)}&_t=${Date.now()}`);
          const data = await res.json();
          if (data && data.status === 'success') {
             setProfile({
                oocName: data.data.ooc_name || '',
                birthDate: data.data.birth_date || '',
                address: data.data.address || '',
                phoneNumber: data.data.phone_number || '',
                discordId: data.data.discord_id || '',
                gender: data.data.gender || '',
                isLocked: data.data.is_locked === '1' || data.data.is_locked === 1 || data.data.is_locked === true
             });
             setTwoFAStatus(data.data.is_2fa_enabled === '1' || data.data.is_2fa_enabled === 1 || data.data.is_2fa_enabled === true);
          }
        } catch (e) {
          console.error("Error fetching profile:", e);
        }
      };
      fetchProfile();
    } else {
      setProfile(initialProfile);
    }
  }, [userName, initialProfile]);

  const handleSave = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    
    if (!isPreviewEnv()) {
        try {
            const formData = new FormData();
            formData.append('username', userName);
            formData.append('ooc_name', profile.oocName);
            formData.append('birth_date', profile.birthDate);
            formData.append('phone_number', profile.phoneNumber);
            formData.append('address', profile.address);
            formData.append('gender', profile.gender || '');

            const res = await fetch(`${API_URL}/api_profile.php`, {
                method: 'POST',
                body: formData
            });
            const data = await res.json();
            if (data && data.status === 'success') {
                setProfile(prev => ({ ...prev, isLocked: true }));
            } else {
                alert(data?.message || 'Gagal menyimpan profil.');
            }
        } catch (error) {
            console.error('Error saving profile:', error);
        } finally {
            setLoading(false);
        }
    } else {
        setTimeout(() => {
          setLoading(false);
          setProfile(prev => ({ ...prev, isLocked: true }));
        }, 1500);
    }
  };

  const handleDiscordLink = async () => {
    if (!isPreviewEnv()) {
        try {
            const resolvedBase = getResolvedApiUrl();
            const cleanAPIUrl = resolvedBase.endsWith('/') ? resolvedBase.slice(0, -1) : resolvedBase;
            const url = new URL(`${cleanAPIUrl}/discord_link.php`, window.location.href);
            url.searchParams.append('username', userName);
            url.searchParams.append('return_url', window.location.href);
            window.location.href = url.toString();
        } catch (error) {
            console.error(error);
            alert("Kesalahan navigasi OAuth Discord.");
        }
    } else {
        setProfile(prev => ({...prev, discordId: "847382910..."}));
        if (onDiscordLinked) {
            onDiscordLinked("Simulated Preview User");
        }
    }
  };

  const handleToggle2FA = async () => {
    if (!isPreviewEnv()) {
        try {
            const formData = new FormData();
            formData.append('action', 'toggle_2fa');
            formData.append('username', userName);

            const res = await fetch(`${API_URL}/api_profile.php`, {
                method: 'POST',
                body: formData
            });
            const data = await res.json();
            if (data && data.status === 'success') {
                setTwoFAStatus(data.is_2fa_enabled === 1 || data.is_2fa_enabled === true);
                alert('Pengaturan 2FA berhasil diubah.');
            } else {
                alert(data?.message || 'Gagal mengubah 2FA.');
            }
        } catch (error) {
            console.error(error);
        }
    } else {
        setTwoFAStatus(!twoFAStatus);
    }
  };

  const handleChangePassword = async (oldPass: string, newPass: string) => {
    if (!isPreviewEnv()) {
        try {
            const formData = new FormData();
            formData.append('action', 'change_password');
            formData.append('username', userName);
            formData.append('oldPassword', oldPass);
            formData.append('newPassword', newPass);

            const res = await fetch(`${API_URL}/api_profile.php`, {
                method: 'POST',
                body: formData
            });
            const data = await res.json();
            if (data && data.status === 'success') {
                if (onPasswordChanged) {
                    onPasswordChanged(new Date().toLocaleString('id-ID', {day: '2-digit', month: 'short', year: 'numeric', hour: '2-digit', minute: '2-digit'}) + ' WIB');
                }
                return true;
            } else {
                return data?.message || 'Gagal mengubah sandi.';
            }
        } catch (error) {
            console.error(error);
            return 'Terjadi kesalahan sistem.';
        }
    } else {
        if (onPasswordChanged) {
            onPasswordChanged(new Date().toLocaleString('id-ID', {day: '2-digit', month: 'short', year: 'numeric', hour: '2-digit', minute: '2-digit'}) + ' WIB');
        }
        return true;
    }
  };

  return (
    <div className="w-full animate-[fadeIn_0.5s_ease-out]">
      <SettingsHeader />

      <div className="grid grid-cols-1 lg:grid-cols-12 gap-6 items-stretch">
        
        {/* Profile Form (Left Side) - Takes up 8 of 12 columns gracefully */}
        <div className="lg:col-span-8 flex flex-col h-full">
            <ProfileForm 
                profile={profile} 
                setProfile={setProfile} 
                onSave={handleSave} 
                isLoading={loading} 
            />
        </div>

        {/* Sidebar Settings (Right Side) - Takes up 4 columns */}
        <div className="lg:col-span-4 flex flex-col gap-6 h-full">
           <div className="flex-1 flex flex-col">
               <DiscordCard 
                    discordId={profile.discordId} 
                    onLink={handleDiscordLink} 
               />
           </div>
           <div className="flex-[1.5] flex flex-col">
               <SecurityCard 
                    is2FAEnabled={twoFAStatus} 
                    userName={userName}
                    onToggle2FA={handleToggle2FA}
                    onChangePassword={handleChangePassword}
               />
           </div>
        </div>

        {/* Bottom Utility Area (Spans full width to fix empty gaps) */}
        {profile.isLocked && (
            <div className="lg:col-span-12 w-full mt-2">
               <DataRequestCard 
                    userName={userName}
               />
            </div>
        )}

      </div>
    </div>
  );
};