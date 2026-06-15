
import React, { useRef } from 'react';
import { Bold, Italic, Underline, AlignLeft, AlignCenter, List, Type, CheckCircle2 } from 'lucide-react';

interface RichTextEditorProps {
  content: string;
  setContent: (content: string) => void;
}

export const RichTextEditor: React.FC<RichTextEditorProps> = ({ content, setContent }) => {
  const textareaRef = useRef<HTMLTextAreaElement>(null);

  const insertFormat = (tag: string, endTag?: string) => {
      if (!textareaRef.current) return;
      
      const start = textareaRef.current.selectionStart;
      const end = textareaRef.current.selectionEnd;
      const text = content;
      const before = text.substring(0, start);
      const selection = text.substring(start, end);
      const after = text.substring(end);

      const closeTag = endTag || tag;
      const newText = `${before}<${tag}>${selection}</${closeTag}>${after}`;
      
      setContent(newText);
      
      setTimeout(() => {
          if(textareaRef.current) {
            textareaRef.current.focus();
            textareaRef.current.setSelectionRange(start + tag.length + 2, end + tag.length + 2);
          }
      }, 0);
  };

  return (
    <div className="bg-white dark:bg-[#121212] border border-gray-200 dark:border-white/10 rounded-xl shadow-lg dark:shadow-none overflow-hidden flex flex-col h-[500px] md:h-[600px] lg:h-[75vh] transition-all duration-300">
        {/* Editor Toolbar */}
        <div className="bg-gray-50 dark:bg-[#1a1a1a] border-b border-gray-200 dark:border-white/5 p-2 md:p-3 flex flex-wrap gap-1 md:gap-2 sticky top-0 z-20">
            <EditorBtn icon={Bold} label="Bold" onClick={() => insertFormat('b')} />
            <EditorBtn icon={Italic} label="Italic" onClick={() => insertFormat('i')} />
            <EditorBtn icon={Underline} label="Underline" onClick={() => insertFormat('u')} />
            <div className="w-px h-6 bg-gray-300 dark:bg-white/10 mx-1 md:mx-2"></div>
            <EditorBtn icon={AlignLeft} label="Paragraph" onClick={() => insertFormat('p')} />
            <EditorBtn icon={AlignCenter} label="Center" onClick={() => insertFormat('center')} />
            <EditorBtn icon={List} label="List" onClick={() => insertFormat('li')} />
            <div className="flex-1"></div>
            <span className="text-[10px] font-mono text-gray-400 self-center px-2 hidden md:block">HTML Mode Enabled</span>
        </div>

        {/* Text Area Container */}
        <div className="flex-1 relative bg-gray-100 dark:bg-[#0c0c0c] p-0 md:p-8 overflow-hidden">
            {/* Paper Effect on Desktop */}
            <div className="w-full h-full md:max-w-4xl md:mx-auto bg-white dark:bg-[#121212] md:shadow-sm md:border md:border-gray-200 dark:md:border-white/5 relative flex flex-col">
                <textarea
                    ref={textareaRef}
                    className="flex-1 w-full bg-transparent p-4 md:p-10 text-gray-900 dark:text-gray-200 outline-none resize-none text-sm md:text-base leading-relaxed font-serif custom-scrollbar"
                    placeholder="Mulai menulis cerita karakter Anda di sini..."
                    value={content}
                    onChange={(e) => setContent(e.target.value)}
                    spellCheck={false}
                ></textarea>
                
                {/* Static Info */}
                <div className="absolute bottom-0 left-0 right-0 bg-white/90 dark:bg-[#121212]/90 backdrop-blur-sm border-t border-gray-100 dark:border-white/5 p-3 text-center text-xs font-mono text-gray-500">
                    Syarat pengiriman: Cerita harus memiliki minimal 300 kata dan dibagi menjadi minimal 3 paragraf.
                </div>
            </div>
        </div>
    </div>
  );
};

const EditorBtn = ({ icon: Icon, label, onClick }: { icon: any, label: string, onClick: () => void }) => (
    <button 
        type="button"
        onClick={onClick}
        className="p-1.5 md:p-2 rounded hover:bg-gray-200 dark:hover:bg-white/10 text-gray-600 dark:text-gray-400 transition-colors"
        title={label}
    >
        <Icon size={16} />
    </button>
);

const ValidationBadge = ({ label, current, target, icon: Icon }: any) => {
    const isMet = current >= target;
    return (
        <div className={`px-2 py-1 md:px-3 md:py-1.5 rounded-lg border backdrop-blur-md flex items-center gap-1.5 transition-colors shadow-sm ${
            isMet 
            ? 'bg-green-500/10 border-green-500/30 text-green-600 dark:text-green-400' 
            : 'bg-red-500/10 border-red-500/30 text-red-600 dark:text-red-400'
        }`}>
            {isMet ? <CheckCircle2 size={12}/> : <Icon size={12}/>}
            <span className="text-[10px] font-bold uppercase tabular-nums">
                {current}/{target} {label}
            </span>
        </div>
    );
};
