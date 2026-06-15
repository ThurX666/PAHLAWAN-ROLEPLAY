
export interface Player {
  id: number;
  name: string;
  score: number;
  ping: number;
  faction: string;
  status: 'Online' | 'AFK' | 'Offline' | 'Banned';
  money?: number;
}

export interface ServerStats {
  hostname: string;
  players: number;
  maxPlayers: number;
  mode: string;
  map: string;
  weather: string;
  status: 'Online' | 'Maintenance' | 'Offline';
  ip_address?: string;
  ping?: string | number;
}

export interface CharacterLog {
  id: number;
  timestamp: string;
  action: string;
  details: string;
}

export interface Character {
  id: number;
  name: string;
  level: number;
  money: number;
  bank: number;
  faction: string;
  lastLogin: string;
  status: 'Active' | 'Banned' | 'Pending' | 'Online' | 'Offline' | 'Jailed';
  skinId: number;
  phoneNumber?: string;
  playingHours?: number;
  warns?: number;
  jobName?: string;
  needsHunger?: number;
  needsThirsty?: number;
  needsMood?: number;
  licenseDriveExp?: string;
  licenseFlyExp?: string;
  licenseBoatExp?: string;
  licenseGunExp?: string;
  storyStatus: 'None' | 'Pending' | 'Active' | 'Revision';
  photoUrl?: string;
  logs: CharacterLog[];
}

export interface FactionApp {
  characterName: string;
  realAge: string;
  factionType: 'PD' | 'Medic' | 'Gang' | 'Gov';
  story: string;
  aiFeedback?: string;
  aiScore?: number;
  status: 'Pending' | 'Approved' | 'Rejected';
}

export interface NewsItem {
  id: number;
  title: string;
  content: string;
  date: string;
  author: string;
  tags: string[];
}

export interface UserProfile {
  oocName: string;
  address: string;
  phoneNumber: string;
  discordId?: string;
  birthDate?: string; // Changed from oocAge to birthDate
  gender?: string;
  isLocked?: boolean; 
}

export interface CharacterStory {
    id: number;
    characterId: number;
    characterName: string;
    photoUrl?: string;
    skinId?: number;
    content: string;
    status: 'Pending' | 'Active' | 'Revision' | 'Rejected';
    adminFeedback?: string;
    reviewedBy?: string;
    reviewedAt?: string;
    plagiarismScore?: number; // 0-100 (Simulated AI Check)
    plagiarismDetails?: { source: string; similarity: number }[];
    lastUpdated: string;
}

export interface PromoItem {
  id: string;
  name: string;
  type: 'Vehicle' | 'Property' | 'Item';
  priceGold: number;
  originalPriceGold?: number; // For strikethrough
  image: string;
  description: string;
  stats: { label: string; value: string }[];
  isLimited: boolean;
  isActive: boolean;
}

export interface InboxMessage {
  id: string;
  title: string;
  message?: string;
  type: 'System' | 'Admin' | 'Voucher' | 'Alert';
  code?: string; // For Voucher Code
  itemName?: string;
  itemPrice?: number;
  itemDescription?: string;
  date: string;
  read: boolean;
  template?: string;
  metadata?: any;
}

// --- NEW ASSET TYPES ---

export interface House {
  id: number;
  location: string;
  owner: string;
  price: number;
  locked: boolean;
  storage: { item: string; qty: number }[];
}

export interface Business {
  id: number;
  name: string;
  type: string;
  owner: string;
  location: string;
  revenueHistory: { day: string; amount: number }[];
  balance: number;
}

export interface JobStats {
  id: number;
  name: string;
  type: 'Job' | 'Sidejob';
  location: string;
  avgWorkers: number;
  avgCirculation: number;
  avgHours: number;
}

export interface FactionMember {
  name: string;
  rank: string;
  dutyHours: number;
  lastLogin: string;
}

export interface FactionData {
  id: number;
  name: string;
  leader: string;
  bank: number;
  members: FactionMember[];
  type: string;
}

export interface FamilyData {
  id: number;
  name: string;
  leader: string;
  level: number;
  bank: number;
  members: FactionMember[]; // Reusing FactionMember for simplicity
}