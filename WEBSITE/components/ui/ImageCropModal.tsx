import React, { useCallback, useState } from 'react';
import Cropper from 'react-easy-crop';
import { X, Check } from 'lucide-react';
import getCroppedImg from '../../utils/cropImage';

interface ImageCropModalProps {
  aspect: number;
  imageSrc: string;
  title: string;
  onCancel: () => void;
  onConfirm: (croppedImage: string) => void | Promise<void>;
}

export const ImageCropModal: React.FC<ImageCropModalProps> = ({
  aspect,
  imageSrc,
  title,
  onCancel,
  onConfirm,
}) => {
  const [crop, setCrop] = useState({ x: 0, y: 0 });
  const [zoom, setZoom] = useState(1);
  const [croppedAreaPixels, setCroppedAreaPixels] = useState<any>(null);
  const [isSaving, setIsSaving] = useState(false);

  const onCropComplete = useCallback((_: any, nextCroppedAreaPixels: any) => {
    setCroppedAreaPixels(nextCroppedAreaPixels);
  }, []);

  const handleConfirm = async () => {
    if (!imageSrc || !croppedAreaPixels || isSaving) return;

    try {
      setIsSaving(true);
      const croppedImage = await getCroppedImg(imageSrc, croppedAreaPixels);
      if (croppedImage) {
        await onConfirm(croppedImage);
      }
    } catch (error) {
      console.error(error);
    } finally {
      setIsSaving(false);
    }
  };

  return (
    <div className="fixed inset-0 z-[70] flex items-center justify-center bg-black/80 backdrop-blur-sm p-4">
      <div className="bg-white dark:bg-ph-surface-panel rounded-2xl w-full max-w-md overflow-hidden flex flex-col shadow-2xl border border-gray-200 dark:border-white/10">
        <div className="p-4 border-b border-gray-200 dark:border-white/10 flex justify-between items-center">
          <h3 className="font-black uppercase tracking-wider text-gray-900 dark:text-white">{title}</h3>
          <button onClick={onCancel} className="text-gray-500 hover:text-gray-900 dark:hover:text-white transition-colors">
            <X size={20} />
          </button>
        </div>

        <div className="relative w-full h-80 bg-black">
          <Cropper
            image={imageSrc}
            crop={crop}
            zoom={zoom}
            aspect={aspect}
            cropShape="rect"
            showGrid={true}
            onCropChange={setCrop}
            onCropComplete={onCropComplete}
            onZoomChange={setZoom}
          />
        </div>

        <div className="p-4 flex flex-col gap-4">
          <div className="flex items-center gap-4">
            <span className="text-xs font-bold text-gray-500 uppercase">Zoom</span>
            <input
              type="range"
              value={zoom}
              min={1}
              max={3}
              step={0.1}
              aria-labelledby="Zoom"
              onChange={(event) => setZoom(Number(event.target.value))}
              className="w-full h-2 bg-gray-200 rounded-lg appearance-none cursor-pointer dark:bg-gray-700"
            />
          </div>

          <div className="flex gap-3 mt-2">
            <button
              onClick={onCancel}
              className="flex-1 py-3 px-4 bg-gray-100 hover:bg-gray-200 dark:bg-white/5 dark:hover:bg-white/10 text-gray-900 dark:text-white rounded-xl font-bold uppercase tracking-wider text-sm transition-colors"
            >
              Batal
            </button>
            <button
              onClick={handleConfirm}
              disabled={isSaving}
              className="flex-1 py-3 px-4 bg-red-600 hover:bg-red-700 disabled:opacity-60 text-white rounded-xl font-bold uppercase tracking-wider text-sm transition-colors flex items-center justify-center gap-2 shadow-lg shadow-red-600/20"
            >
              <Check size={18} /> {isSaving ? 'Menyimpan...' : 'Simpan'}
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};
