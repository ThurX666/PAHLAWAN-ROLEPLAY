import { Crown, Gem, Star, Shield, LucideIcon } from 'lucide-react';

export interface VipStyle {
  icon: LucideIcon;
  colorClass: string;
  bgClass: string;
  borderClass: string;
  gradientClass: string;
  textClass: string;
  buttonClass: string;
}

export const getVipStyle = (tier: string | undefined | null): VipStyle => {
  const normalizedTier = tier?.toLowerCase() || 'none';

  switch (normalizedTier) {
    case 'diamond':
      return {
        icon: Gem,
        colorClass: 'text-cyan-400',
        bgClass: 'bg-cyan-50 dark:bg-cyan-500/10',
        borderClass: 'border-cyan-200 dark:border-cyan-500/20',
        gradientClass: 'from-cyan-400 to-blue-600',
        textClass: 'text-cyan-600 dark:text-cyan-400',
        buttonClass: 'bg-cyan-50 dark:bg-cyan-500/10 text-cyan-600 dark:text-cyan-400 hover:bg-cyan-100 dark:hover:bg-cyan-500/20 border-cyan-200 dark:border-cyan-500/20',
      };
    case 'platinum':
      return {
        icon: Shield,
        colorClass: 'text-purple-500',
        bgClass: 'bg-purple-50 dark:bg-purple-500/10',
        borderClass: 'border-purple-200 dark:border-purple-500/20',
        gradientClass: 'from-purple-400 to-indigo-600',
        textClass: 'text-purple-600 dark:text-purple-400',
        buttonClass: 'bg-purple-50 dark:bg-purple-500/10 text-purple-600 dark:text-purple-400 hover:bg-purple-100 dark:hover:bg-purple-500/20 border-purple-200 dark:border-purple-500/20',
      };
    case 'gold':
      return {
        icon: Crown,
        colorClass: 'text-amber-500',
        bgClass: 'bg-amber-50 dark:bg-amber-500/10',
        borderClass: 'border-amber-200 dark:border-amber-500/20',
        gradientClass: 'from-amber-400 to-orange-600',
        textClass: 'text-amber-600 dark:text-amber-400',
        buttonClass: 'bg-amber-50 dark:bg-amber-500/10 text-amber-600 dark:text-amber-400 hover:bg-amber-100 dark:hover:bg-amber-500/20 border-amber-200 dark:border-amber-500/20',
      };
    case 'silver':
      return {
        icon: Star,
        colorClass: 'text-slate-400',
        bgClass: 'bg-slate-50 dark:bg-slate-500/10',
        borderClass: 'border-slate-200 dark:border-slate-500/20',
        gradientClass: 'from-slate-400 to-gray-600',
        textClass: 'text-slate-600 dark:text-slate-400',
        buttonClass: 'bg-slate-50 dark:bg-slate-500/10 text-slate-600 dark:text-slate-400 hover:bg-slate-100 dark:hover:bg-slate-500/20 border-slate-200 dark:border-slate-500/20',
      };
    case 'bronze':
      return {
        icon: Star,
        colorClass: 'text-orange-500',
        bgClass: 'bg-orange-50 dark:bg-orange-500/10',
        borderClass: 'border-orange-200 dark:border-orange-500/20',
        gradientClass: 'from-orange-400 to-red-600',
        textClass: 'text-orange-600 dark:text-orange-400',
        buttonClass: 'bg-orange-50 dark:bg-orange-500/10 text-orange-600 dark:text-orange-400 hover:bg-orange-100 dark:hover:bg-orange-500/20 border-orange-200 dark:border-orange-500/20',
      };
    default:
      return {
        icon: Crown,
        colorClass: 'text-gray-400',
        bgClass: 'bg-gray-50 dark:bg-gray-500/10',
        borderClass: 'border-gray-200 dark:border-gray-500/20',
        gradientClass: 'from-gray-400 to-gray-600 dark:from-gray-700 dark:to-gray-900',
        textClass: 'text-gray-600 dark:text-gray-400',
        buttonClass: 'bg-gray-50 dark:bg-gray-500/10 text-gray-600 dark:text-gray-400 hover:bg-gray-100 dark:hover:bg-gray-500/20 border-gray-200 dark:border-gray-500/20',
      };
  }
};
