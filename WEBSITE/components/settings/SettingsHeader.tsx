
import React from 'react';
import { PageHeader } from '../ui/PageHeader';
import { Settings } from 'lucide-react';

export const SettingsHeader: React.FC = () => {
  return (
    <PageHeader 
      title="PENGATURAN" 
      description="Kelola profil OOC dan keamanan." 
      icon={Settings} 
    />
  );
};
