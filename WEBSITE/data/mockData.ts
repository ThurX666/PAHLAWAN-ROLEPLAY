
import { House, Business, JobStats, FactionData, FamilyData, Player } from '../types';

export const MOCK_HOUSES: House[] = [
    { id: 101, location: "Mulholland", owner: "Big_Smoke", price: 500000, locked: true, storage: [{item: "Desert Eagle", qty: 2}, {item: "Crack", qty: 50}] },
    { id: 102, location: "Ganton", owner: "Ryder_Wilson", price: 25000, locked: false, storage: [{item: "Bat", qty: 1}, {item: "Pot", qty: 10}] },
    { id: 103, location: "Vinewood", owner: "None", price: 1200000, locked: true, storage: [] },
    { id: 104, location: "Palomino", owner: "Ucok_Slepbeuw", price: 150000, locked: true, storage: [{item: "AK-47", qty: 5}] },
];

export const ADMIN_RANKS: Record<number, string> = {
  1: "Volunteer",
  2: "Junior Helper",
  3: "Senior Helper",
  4: "Head Helper",
  5: "Admin Level 1",
  6: "Admin Level 2",
  7: "Admin Level 3",
  8: "Head Admin",
  9: "Management",
  10: "Executive"
};

export const MOCK_BUSINESSES: Business[] = [
    { 
        id: 1, name: "Pizza Stack", type: "F&B", owner: "Mike_Toreno", location: "Idlewood", balance: 5000000,
        revenueHistory: [
            { day: 'Sen', amount: 150000 }, { day: 'Sel', amount: 120000 }, { day: 'Rab', amount: 180000 }, 
            { day: 'Kam', amount: 160000 }, { day: 'Jum', amount: 250000 }, { day: 'Sab', amount: 300000 }, { day: 'Min', amount: 280000 }
        ]
    },
    { 
        id: 2, name: "Ammunation", type: "Weapon", owner: "Officer_Tenpenny", location: "Market", balance: 12000000,
        revenueHistory: [
            { day: 'Sen', amount: 500000 }, { day: 'Sel', amount: 450000 }, { day: 'Rab', amount: 600000 }, 
            { day: 'Kam', amount: 550000 }, { day: 'Jum', amount: 800000 }, { day: 'Sab', amount: 950000 }, { day: 'Min', amount: 900000 }
        ]
    }
];

export const MOCK_JOBS: JobStats[] = [
    { id: 1, name: "Trucker", type: "Job", location: "Flint County", avgWorkers: 45, avgCirculation: 2500000, avgHours: 4.5 },
    { id: 2, name: "Mechanic", type: "Job", location: "Ocean Docks", avgWorkers: 20, avgCirculation: 1200000, avgHours: 3.2 },
    { id: 3, name: "Sweeper", type: "Sidejob", location: "Los Santos", avgWorkers: 85, avgCirculation: 500000, avgHours: 1.5 },
    { id: 4, name: "Fisherman", type: "Sidejob", location: "Santa Maria", avgWorkers: 30, avgCirculation: 800000, avgHours: 2.0 },
];

export const MOCK_FACTIONS: FactionData[] = [
    { 
        id: 1, name: "Los Santos Police Dept", leader: "Frank_Tenpenny", bank: 55000000, type: "Legal",
        members: [
            { name: "Officer_Tenpenny", rank: "Chief", dutyHours: 45, lastLogin: "Today" },
            { name: "Officer_Pulaski", rank: "Sergeant", dutyHours: 32, lastLogin: "Yesterday" },
            { name: "Officer_Hernandez", rank: "Cadet", dutyHours: 12, lastLogin: "2 days ago" },
        ]
    },
    { 
        id: 2, name: "Los Santos Medical", leader: "Doctor_Strange", bank: 25000000, type: "Legal",
        members: [
            { name: "Nurse_Joy", rank: "Director", dutyHours: 25, lastLogin: "Today" },
            { name: "Dr_House", rank: "Specialist", dutyHours: 40, lastLogin: "Today" },
        ]
    }
];

export const MOCK_FAMILIES: FamilyData[] = [
    { 
        id: 1, name: "Grove Street Families", leader: "Sweet_Johnson", level: 5, bank: 120000,
        members: [
            { name: "Carl_Johnson", rank: "OG", dutyHours: 10, lastLogin: "Today" },
            { name: "Ryder_Wilson", rank: "Member", dutyHours: 5, lastLogin: "Today" },
            { name: "Big_Smoke", rank: "Legend", dutyHours: 0, lastLogin: "Yesterday" },
        ]
    },
    { 
        id: 2, name: "Ballas", leader: "Kane", level: 4, bank: 350000,
        members: [
            { name: "Ballas_Member1", rank: "OG", dutyHours: 8, lastLogin: "Today" }
        ]
    }
];

export const MOCK_ALL_PLAYERS: Player[] = [
  { id: 1, name: "Big_Smoke", score: 4050, ping: 45, faction: "Grove Street", status: 'Online', money: 25000 },
  { id: 2, name: "Officer_Tenpenny", score: 1200, ping: 22, faction: "LSPD", status: 'Online', money: 5000 },
  { id: 3, name: "Ryder_Wilson", score: 850, ping: 56, faction: "Grove Street", status: 'AFK', money: 1200 },
  { id: 4, name: "Cesar_Vialpando", score: 3200, ping: 110, faction: "Varrios Los Aztecas", status: 'Online', money: 15000 },
  { id: 5, name: "Wu_Zi_Mu", score: 5000, ping: 89, faction: "Triads", status: 'Online', money: 500000 },
  { id: 6, name: "Mike_Toreno", score: 9999, ping: 15, faction: "Gov", status: 'Online', money: 1000000 },
  { id: 7, name: "Kendl_Johnson", score: 400, ping: 42, faction: "Warga Sipil", status: 'Offline', money: 800 },
  { id: 8, name: "Frank_Tenpenny", score: 100, ping: 0, faction: "LSPD", status: 'Offline', money: 200 },
];

export const ECONOMY_DATA = [
  { day: 'Sen', circulation: 1500000, assets: 400000 },
  { day: 'Sel', circulation: 1650000, assets: 410000 },
  { day: 'Rab', circulation: 1700000, assets: 420000 },
  { day: 'Kam', circulation: 1850000, assets: 430000 },
  { day: 'Jum', circulation: 2100000, assets: 450000 },
  { day: 'Sab', circulation: 2400000, assets: 470000 },
  { day: 'Min', circulation: 2600000, assets: 480000 },
];

export const MOCK_TICKETS = [
    { 
        id: 1024, 
        subject: "Konfirmasi Donasi Paket Gold", 
        category: "Masalah Donasi", 
        status: "Dijawab", 
        lastUpdate: new Date(Date.now() - 1000 * 60 * 10).toISOString(), // 10 mins ago
        messages: [
            { sender: 'Player', text: "Min, status masih pending.", time: new Date(Date.now() - 1000 * 60 * 15).toISOString() }, // 15 mins ago
            { sender: 'Admin', text: "Mohon lampirkan ulang bukti transfer.", time: new Date(Date.now() - 1000 * 60 * 10).toISOString() } // 10 mins ago
        ]
    }
];

export const INITIAL_ADMIN_TRANSACTIONS = [
    { 
        id: "INV-1001", 
        account: "Admin",
        player: "Ryder_Wilson", 
        senderName: "Ryder Wilson", 
        item: "Change Name (Ryder_Wilson)", 
        type: "gold_shop",
        quantity: 1, 
        amount: "500 GC", 
        total_transfer: "500 GC",
        fee_info: "0 GC",
        method: "Gold Coin", 
        status: "Pending", 
        date: "2026-02-23T10:05:00", 
        proofImage: "https://picsum.photos/seed/inv1/400/600" 
    },
    { 
        id: "INV-1002", 
        account: "Admin",
        player: "Big_Smoke", 
        senderName: "Melvin Harris", 
        item: "1000 Gold", 
        type: "donation",
        quantity: 1000, 
        amount: "Rp 150.000", 
        total_transfer: "Rp 157.500",
        fee_info: "Rp 7.500 (Admin Fee 5%)",
        method: "Gopay", 
        status: "Success", 
        date: "2026-02-22T15:30:00", 
        proofImage: "https://picsum.photos/seed/inv2/400/600" 
    },
    { 
        id: "INV-1003", 
        account: "Admin",
        player: "Kendl_Johnson", 
        senderName: "Kendl Johnson", 
        item: "500 Gold", 
        type: "donation",
        quantity: 500, 
        amount: "Rp 75.000", 
        total_transfer: "Rp 88.235",
        fee_info: "0.85 (Rate Convert)",
        method: "Pulsa Telkomsel", 
        status: "Rejected", 
        date: "2026-02-22T09:15:00", 
        proofImage: "https://picsum.photos/seed/inv3/400/600" 
    },
    { 
        id: "INV-1004", 
        account: "Admin",
        player: "Ucok_Slepbeuw", 
        senderName: "Ucok Slepbeuw", 
        item: "Custom Mapping (Ucok_Slepbeuw)", 
        type: "gold_shop",
        quantity: 1, 
        amount: "1000 GC", 
        total_transfer: "1000 GC",
        fee_info: "0 GC",
        method: "Gold Coin", 
        status: "Success", 
        date: "2026-02-20T18:45:00", 
        proofImage: "https://picsum.photos/seed/inv4/400/600" 
    },
    { 
        id: "INV-1005", 
        account: "Admin",
        player: "Carl_Johnson", 
        senderName: "Carl Johnson", 
        item: "2000 Gold", 
        type: "donation",
        quantity: 2000, 
        amount: "Rp 250.000", 
        total_transfer: "Rp 250.000",
        fee_info: "Rp 0 (Admin Fee)",
        method: "BCA", 
        status: "Success", 
        date: "2026-02-19T14:20:00", 
        proofImage: "https://picsum.photos/seed/inv5/400/600" 
    },
    { 
        id: "INV-1006", 
        account: "Admin",
        player: "Sweet_Johnson", 
        senderName: "Sweet Johnson", 
        item: "Change Number (Sweet_Johnson)", 
        type: "gold_shop",
        quantity: 1, 
        amount: "250 GC", 
        total_transfer: "250 GC",
        fee_info: "0 GC",
        method: "Gold Coin", 
        status: "Success", 
        date: "2026-02-18T11:10:00", 
        proofImage: "https://picsum.photos/seed/inv6/400/600" 
    },
    { 
        id: "INV-1007", 
        account: "Admin",
        player: "Cesar_Vialpando", 
        senderName: "Cesar Vialpando", 
        item: "500 Gold", 
        type: "donation",
        quantity: 500, 
        amount: "Rp 75.000", 
        total_transfer: "Rp 75.000",
        fee_info: "Rp 0 (Admin Fee)",
        method: "OVO", 
        status: "Pending", 
        date: "2026-02-17T09:05:00", 
        proofImage: "https://picsum.photos/seed/inv7/400/600" 
    },
    { 
        id: "INV-1008", 
        account: "Admin",
        player: "Wu_Zi_Mu", 
        senderName: "Wu Zi Mu", 
        item: "Custom Gate (Wu_Zi_Mu)", 
        type: "gold_shop",
        quantity: 1, 
        amount: "1500 GC", 
        total_transfer: "1500 GC",
        fee_info: "0 GC",
        method: "Gold Coin", 
        status: "Success", 
        date: "2026-02-16T20:30:00", 
        proofImage: "https://picsum.photos/seed/inv8/400/600" 
    },
];
