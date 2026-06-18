
import React from 'react';
import { PageHeader } from '../ui/PageHeader';
import { Settings } from 'lucide-react';
import { UCP_VERSION } from '../../version';

export const SettingsHeader: React.FC = () => {
  return (
    <PageHeader 
      title="PENGATURAN" 
      description={`Kelola profil OOC dan keamanan. UCP ${UCP_VERSION}`}
      icon={Settings} 
    />
  );
};
