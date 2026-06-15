import React, { ReactNode } from 'react';
import { LucideIcon } from 'lucide-react';

interface PageHeaderProps {
  title: string;
  description: string;
  action?: ReactNode;
  icon?: LucideIcon;
  iconColor?: string;
}

export const PageHeader: React.FC<PageHeaderProps> = ({ title, description, action, icon: Icon, iconColor = 'bg-red-600' }) => {
  return (
    <div className="flex flex-col md:flex-row justify-between items-start md:items-end mb-4 md:mb-6 gap-4 md:gap-6 border-b border-gray-200 dark:border-white/5 pb-4 md:border-none md:pb-0">
      <div className="w-full md:w-auto">
        <div className="flex items-center gap-3 mb-2">
          {Icon && (
            <div className={`p-2 ${iconColor} rounded-lg shadow-lg shadow-red-600/20`}>
              <Icon className="text-white" size={24} />
            </div>
          )}
          <h1 className="text-2xl md:text-4xl font-black text-gray-900 dark:text-white uppercase italic tracking-tighter">
            {title}
          </h1>
        </div>
        <p className="text-xs md:text-sm text-gray-500 dark:text-gray-400 font-medium max-w-lg leading-relaxed">
          {description}
        </p>
      </div>
      {action && (
        <div className="flex items-center gap-3 w-full md:w-auto">
          {action}
        </div>
      )}
    </div>
  );
};
