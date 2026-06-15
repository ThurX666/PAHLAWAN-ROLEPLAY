const fs = require('fs');
const path = require('path');

const GIVEAWAY_FILE = path.join(__dirname, '../data/giveaways.json');

// Inisialisasi file
if (!fs.existsSync(GIVEAWAY_FILE)) {
    fs.writeFileSync(GIVEAWAY_FILE, '[]');
}

// ========== CORE FUNCTIONS ==========

function getAllGiveaways() {
    try {
        const data = fs.readFileSync(GIVEAWAY_FILE, 'utf8');
        return JSON.parse(data);
    } catch (error) {
        console.error('Error reading giveaways:', error);
        return [];
    }
}

function saveAllGiveaways(giveaways) {
    try {
        fs.writeFileSync(GIVEAWAY_FILE, JSON.stringify(giveaways, null, 2));
        return true;
    } catch (error) {
        console.error('Error saving giveaways:', error);
        return false;
    }
}

// ========== PUBLIC API ==========

const giveawayStore = {
    // Helper functions
    parseDuration: function(durationStr) {
        console.log(`[parseDuration] Parsing: "${durationStr}"`);
        
        if (!durationStr || typeof durationStr !== 'string') {
            throw new Error('Duration string is required');
        }
        
        const parts = durationStr.trim().split(/\s+/);
        if (parts.length < 2) {
            throw new Error('Invalid duration format. Use: "angka satuan" (contoh: "30 menit")');
        }
        
        const number = parseInt(parts[0]);
        if (isNaN(number) || number <= 0) {
            throw new Error('Duration number must be a positive integer');
        }
        
        const unit = parts[1].toLowerCase();
        let multiplier = 60000; // menit default
        
        if (unit.includes('jam')) {
            multiplier = 3600000; // jam ke ms
        } else if (unit.includes('hari')) {
            multiplier = 86400000; // hari ke ms
        } else if (unit.includes('detik')) {
            multiplier = 1000; // detik ke ms
        } else if (!unit.includes('menit')) {
            throw new Error('Invalid time unit. Use: menit, jam, hari, detik');
        }
        
        const result = number * multiplier;
        console.log(`[parseDuration] Result: ${number} ${unit} = ${result}ms`);
        return result;
    },
    
    formatTime: function(ms) {
        const days = Math.floor(ms / (1000 * 60 * 60 * 24));
        const hours = Math.floor((ms % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
        const minutes = Math.floor((ms % (1000 * 60 * 60)) / (1000 * 60));
        
        if (days > 0) return `${days} hari ${hours} jam`;
        if (hours > 0) return `${hours} jam ${minutes} menit`;
        return `${minutes} menit`;
    },
    
    // CRUD operations
    createGiveaway: function(giveawayData) {
        const giveaways = getAllGiveaways();
        const newGiveaway = {
            id: Date.now().toString() + '_' + Math.random().toString(36).substr(2, 9),
            ...giveawayData,
            participants: [],
            winners: [],
            status: 'active',
            created_at: new Date().toISOString()
        };
        
        giveaways.push(newGiveaway);
        saveAllGiveaways(giveaways);
        console.log(`[createGiveaway] Created: ${newGiveaway.id}`);
        return newGiveaway;
    },
    
    getGiveaway: function(id) {
        const giveaways = getAllGiveaways();
        return giveaways.find(g => g.id === id);
    },
    
    getGiveawayByMessage: function(messageId) {
        const giveaways = getAllGiveaways();
        const found = giveaways.find(g => g.message_id === messageId);
        console.log(`[getGiveawayByMessage] ${messageId} -> ${found ? found.id : 'NOT FOUND'}`);
        return found;
    },
    
    getAllActiveGiveaways: function() {
        const giveaways = getAllGiveaways();
        return giveaways.filter(g => g.status === 'active');
    },
    
    updateGiveaway: function(id, updateData) {
        const giveaways = getAllGiveaways();
        const index = giveaways.findIndex(g => g.id === id);
        
        if (index === -1) return false;
        
        giveaways[index] = { ...giveaways[index], ...updateData };
        return saveAllGiveaways(giveaways);
    },
    
    addParticipant: function(giveawayId, userId) {
        const giveaway = this.getGiveaway(giveawayId);
        if (!giveaway) return false;
        
        if (!giveaway.participants.includes(userId)) {
            giveaway.participants.push(userId);
            const success = this.updateGiveaway(giveawayId, { 
                participants: giveaway.participants 
            });
            console.log(`[addParticipant] ${userId} -> ${giveawayId}: ${success}`);
            return success;
        }
        return false;
    },
    
    removeParticipant: function(giveawayId, userId) {
        const giveaway = this.getGiveaway(giveawayId);
        if (!giveaway) return false;
        
        const index = giveaway.participants.indexOf(userId);
        if (index !== -1) {
            giveaway.participants.splice(index, 1);
            return this.updateGiveaway(giveawayId, { 
                participants: giveaway.participants 
            });
        }
        return false;
    },
    
    setWinners: function(giveawayId, winners) {
        return this.updateGiveaway(giveawayId, { 
            winners, 
            status: 'ended',
            ended_at: new Date().toISOString()
        });
    },
    
    cancelGiveaway: function(giveawayId) {
        return this.updateGiveaway(giveawayId, { 
            status: 'cancelled',
            ended_at: new Date().toISOString()
        });
    },
    
    deleteGiveaway: function(id) {
        const giveaways = getAllGiveaways();
        const filtered = giveaways.filter(g => g.id !== id);
        return saveAllGiveaways(filtered);
    },
    
    pickRandomWinners: function(participants, count) {
        if (!participants || participants.length === 0) return [];
        
        const shuffled = [...participants].sort(() => 0.5 - Math.random());
        return shuffled.slice(0, Math.min(count, participants.length));
    }
};

module.exports = giveawayStore;