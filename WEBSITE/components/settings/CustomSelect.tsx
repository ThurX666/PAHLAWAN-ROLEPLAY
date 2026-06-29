import React, { useState, useRef, useEffect } from 'react';
import { createPortal } from 'react-dom';
import { ChevronDown, Search, X, Check } from 'lucide-react';

interface Option {
  value: string;
  label: string;
}

interface CustomSelectProps {
  value: string;
  onChange: (value: string) => void;
  options: Option[];
  placeholder: string;
  icon?: React.ReactNode;
  error?: string;
  disabled?: boolean;
  searchable?: boolean;
}

export const CustomSelect: React.FC<CustomSelectProps> = ({
  value,
  onChange,
  options,
  placeholder,
  icon,
  error,
  disabled = false,
  searchable = false,
}) => {
  const [isOpen, setIsOpen] = useState(false);
  const [searchTerm, setSearchTerm] = useState('');
  const dropdownRef = useRef<HTMLDivElement>(null);
  const [mounted, setMounted] = useState(false);
  const [dropdownPos, setDropdownPos] = useState({ top: 0, left: 0, width: 0 });

  const updatePosition = () => {
    if (dropdownRef.current) {
      const rect = dropdownRef.current.getBoundingClientRect();
      // Check if there's enough space below, otherwise open upwards
      const spaceBelow = window.innerHeight - rect.bottom;
      const dropdownHeight = 320; // max-h-80 is 320px
      
      let top = rect.bottom + 8;
      if (spaceBelow < dropdownHeight && rect.top > dropdownHeight) {
        top = rect.top - dropdownHeight - 8;
      }

      setDropdownPos({
        top,
        left: rect.left,
        width: rect.width
      });
    }
  };

  useEffect(() => {
    setMounted(true);
    const handleClickOutside = (event: MouseEvent) => {
      const target = event.target as HTMLElement;
      if (dropdownRef.current && !dropdownRef.current.contains(target) && !target.closest('.custom-select-portal')) {
        setIsOpen(false);
      }
    };
    
    const handleScroll = (e: Event) => {
      // Don't close if scrolling inside the dropdown itself
      const target = e.target as HTMLElement;
      if (target.closest('.custom-select-portal')) return;
      
      if (isOpen) {
        updatePosition();
      }
    };

    document.addEventListener('mousedown', handleClickOutside);
    window.addEventListener('scroll', handleScroll, true);
    window.addEventListener('resize', updatePosition);
    
    return () => {
      document.removeEventListener('mousedown', handleClickOutside);
      window.removeEventListener('scroll', handleScroll, true);
      window.removeEventListener('resize', updatePosition);
    };
  }, [isOpen]);

  useEffect(() => {
    if (isOpen) {
      updatePosition();
    } else {
      setSearchTerm('');
    }
  }, [isOpen]);

  const selectedOption = options.find(opt => opt.value === value);

  const filteredOptions = options.filter(opt => 
    opt.label.toLowerCase().includes(searchTerm.toLowerCase())
  );

  const mobileBottomSheet = mounted && isOpen ? createPortal(
    <div className="fixed inset-0 z-[9999] md:hidden flex flex-col justify-end custom-select-portal">
      <div className="absolute inset-0 bg-black/60 backdrop-blur-sm animate-in fade-in" onClick={() => setIsOpen(false)} />
      <div className="relative bg-white dark:bg-ph-surface-card w-full rounded-t-3xl max-h-[85vh] flex flex-col animate-in slide-in-from-bottom-full duration-300 shadow-2xl border-t border-gray-200 dark:border-white/10">
        <div className="w-12 h-1.5 bg-gray-300 dark:bg-gray-700 rounded-full mx-auto mt-4 mb-2"></div>
        <div className="px-6 py-4 border-b border-gray-100 dark:border-white/5 flex items-center justify-between shrink-0">
          <span className="font-bold text-gray-900 dark:text-white text-base">{placeholder}</span>
          <button onClick={(e) => { e.stopPropagation(); setIsOpen(false); }} className="p-2 -mr-2 text-gray-500 hover:bg-gray-100 dark:hover:bg-white/10 rounded-full transition-colors">
            <X size={20} />
          </button>
        </div>
        {searchable && (
          <div className="p-4 border-b border-gray-100 dark:border-white/5 relative shrink-0">
            <Search size={18} className="absolute left-8 top-1/2 -translate-y-1/2 text-gray-400" />
            <input 
              type="text"
              className="w-full bg-gray-50 dark:bg-black/20 border border-gray-200 dark:border-white/10 rounded-xl pl-12 pr-4 py-3.5 text-sm text-gray-900 dark:text-white outline-none focus:border-red-500 transition-colors"
              placeholder="Cari..."
              value={searchTerm}
              onChange={(e) => setSearchTerm(e.target.value)}
              onClick={(e) => e.stopPropagation()}
            />
          </div>
        )}
        <div className="overflow-y-auto flex-1 p-4 pb-8 scrollbar-thin scrollbar-thumb-gray-300 dark:scrollbar-thumb-gray-700">
          {filteredOptions.length > 0 ? (
            filteredOptions.map((opt) => (
              <div
                key={opt.value}
                className={`px-4 py-4 text-sm rounded-xl cursor-pointer transition-colors mb-2 flex items-center justify-between ${value === opt.value ? 'bg-red-50 dark:bg-red-500/10 text-red-600 dark:text-red-400 font-bold border border-red-200 dark:border-red-500/20' : 'text-gray-700 dark:text-gray-300 hover:bg-gray-50 dark:hover:bg-white/5 font-medium border border-transparent'}`}
                onClick={(e) => {
                  e.stopPropagation();
                  onChange(opt.value);
                  setIsOpen(false);
                }}
              >
                {opt.label}
                {value === opt.value && <div className="w-2 h-2 rounded-full bg-red-500"></div>}
              </div>
            ))
          ) : (
            <div className="px-4 py-8 text-center text-sm text-gray-500">
              Tidak ditemukan
            </div>
          )}
        </div>
      </div>
    </div>,
    document.body
  ) : null;

  const desktopDropdown = mounted && isOpen ? createPortal(
    <div 
      className="hidden md:flex fixed z-[9999] bg-white dark:bg-ph-surface-panel border border-gray-200 dark:border-white/10 rounded-xl shadow-2xl overflow-hidden flex-col animate-in fade-in zoom-in-95 duration-150 custom-select-portal"
      style={{
        top: `${dropdownPos.top}px`,
        left: `${dropdownPos.left}px`,
        width: `${dropdownPos.width}px`,
        maxHeight: '320px'
      }}
    >
      {searchable && (
        <div className="p-3 border-b border-gray-100 dark:border-white/5 relative shrink-0 bg-gray-50/50 dark:bg-black/20">
          <Search size={16} className="absolute left-6 top-1/2 -translate-y-1/2 text-gray-400" />
          <input 
            type="text"
            className="w-full bg-white dark:bg-ph-surface-card border border-gray-200 dark:border-white/10 rounded-lg pl-10 pr-4 py-2.5 text-sm text-gray-900 dark:text-white outline-none focus:border-red-500 focus:ring-1 focus:ring-red-500 transition-all shadow-sm"
            placeholder="Cari pilihan..."
            value={searchTerm}
            onChange={(e) => setSearchTerm(e.target.value)}
            onClick={(e) => e.stopPropagation()}
            autoFocus
          />
        </div>
      )}
      <div className="overflow-y-auto flex-1 p-2 scrollbar-thin scrollbar-thumb-gray-300 dark:scrollbar-thumb-gray-700">
        {filteredOptions.length > 0 ? (
          filteredOptions.map((opt) => (
            <div
              key={opt.value}
              className={`px-4 py-3 text-sm rounded-lg cursor-pointer transition-all flex items-center justify-between mb-1 last:mb-0 ${value === opt.value ? 'bg-red-50 dark:bg-red-500/10 text-red-600 dark:text-red-400 font-bold' : 'text-gray-700 dark:text-gray-300 hover:bg-gray-100 dark:hover:bg-white/10 font-medium'}`}
              onClick={(e) => {
                e.stopPropagation();
                onChange(opt.value);
                setIsOpen(false);
              }}
            >
              <span className="truncate pr-4">{opt.label}</span>
              {value === opt.value && <Check size={16} className="shrink-0 text-red-500" />}
            </div>
          ))
        ) : (
          <div className="px-4 py-8 text-center text-sm text-gray-500 flex flex-col items-center gap-2">
            <Search size={24} className="text-gray-300 dark:text-gray-600" />
            <span>Pilihan tidak ditemukan</span>
          </div>
        )}
      </div>
    </div>,
    document.body
  ) : null;

  return (
    <div className="relative group" ref={dropdownRef}>
      {icon && (
        <div className="absolute left-4 top-3.5 md:top-4 text-gray-400 dark:text-gray-500 z-10 pointer-events-none">
          {icon}
        </div>
      )}
      <div 
        className={`w-full bg-gray-50 dark:bg-black/20 border ${error ? 'border-red-500' : 'border-gray-200 dark:border-white/10'} rounded-xl ${icon ? 'pl-12' : 'pl-4'} pr-10 py-3 md:py-3.5 text-gray-900 dark:text-white text-xs md:text-sm focus-within:border-red-500 focus-within:bg-white dark:focus-within:bg-black/40 transition-all cursor-pointer flex items-center justify-between ${disabled ? 'opacity-50 cursor-not-allowed' : 'hover:border-gray-300 dark:hover:border-white/20'}`}
        onClick={() => !disabled && setIsOpen(!isOpen)}
      >
        <span className={`truncate ${selectedOption ? 'font-medium' : 'text-gray-500'}`}>
          {selectedOption ? selectedOption.label : placeholder}
        </span>
        <ChevronDown size={16} className={`text-gray-400 shrink-0 transition-transform duration-300 ${isOpen ? 'rotate-180' : ''}`} />
      </div>

      {mobileBottomSheet}
      {desktopDropdown}
    </div>
  );
};
