const fs = require('fs');
const path = require('path');

const TICKETS_FILE = path.join(__dirname, '../data/tickets.json');
const TRANSCRIPTS_DIR = path.join(__dirname, '../data/transcripts');

// ==================== HELPER FUNCTIONS ====================
function initStorage() {
    const dataDir = path.dirname(TICKETS_FILE);
    if (!fs.existsSync(dataDir)) {
        fs.mkdirSync(dataDir, { recursive: true });
    }
    
    if (!fs.existsSync(TRANSCRIPTS_DIR)) {
        fs.mkdirSync(TRANSCRIPTS_DIR, { recursive: true });
    }
    
    if (!fs.existsSync(TICKETS_FILE)) {
        const defaultData = {
            tickets: [],
            last_order_id: 0,
            total_tickets: 0,
            last_updated: null
        };
        fs.writeFileSync(TICKETS_FILE, JSON.stringify(defaultData, null, 2));
    }
}

function readTickets() {
    if (!fs.existsSync(TICKETS_FILE)) {
        initStorage();
    }
    try {
        const data = fs.readFileSync(TICKETS_FILE, 'utf8');
        if (!data || data.trim() === '') {
            return { tickets: [], last_order_id: 0, total_tickets: 0, last_updated: null };
        }
        const parsed = JSON.parse(data);
        // Pastikan struktur data benar
        if (!parsed.tickets || !Array.isArray(parsed.tickets)) {
            return { tickets: [], last_order_id: 0, total_tickets: 0, last_updated: null };
        }
        return parsed;
    } catch (error) {
        console.error('❌ Error reading tickets:', error);
        return { tickets: [], last_order_id: 0, total_tickets: 0, last_updated: null };
    }
}

function writeTickets(data) {
    try {
        if (!data.tickets || !Array.isArray(data.tickets)) {
            data.tickets = [];
        }
        data.last_updated = new Date().toISOString();
        data.total_tickets = data.tickets.length;
        fs.writeFileSync(TICKETS_FILE, JSON.stringify(data, null, 2));
        return true;
    } catch (error) {
        console.error('❌ Error writing tickets:', error);
        return false;
    }
}

// ==================== TICKET FUNCTIONS ====================
function generateOrderId() {
    const data = readTickets();
    const newId = (data.last_order_id || 0) + 1;
    data.last_order_id = newId;
    writeTickets(data);
    return `DON-${newId.toString().padStart(3, '0')}`;
}

function createTicket(ticketData) {
    try {
        const data = readTickets();
        
        if (!data.tickets || !Array.isArray(data.tickets)) {
            console.error('❌ Tickets data is corrupted, reinitializing...');
            data.tickets = [];
        }
        
        const newTicket = {
            id: `TKT_${Date.now()}`,
            order_id: generateOrderId(),
            ...ticketData,
            created_at: new Date().toISOString(),
            status: 'pending',
            messages: []
        };
        
        data.tickets.push(newTicket);
        
        if (writeTickets(data)) {
            console.log(`✅ Ticket created: ${newTicket.order_id}`);
            return newTicket;
        }
        
        return null;
    } catch (error) {
        console.error('❌ Failed to create ticket:', error);
        return null;
    }
}

function getTicketByChannel(channelId) {
    const data = readTickets();
    if (!data.tickets || !Array.isArray(data.tickets)) return null;
    return data.tickets.find(t => t.channel_id === channelId);
}

function getTicketByOrderId(orderId) {
    const data = readTickets();
    if (!data.tickets || !Array.isArray(data.tickets)) return null;
    return data.tickets.find(t => t.order_id === orderId);
}

function updateTicketStatus(channelId, status, price = null) {
    const data = readTickets();
    if (!data.tickets || !Array.isArray(data.tickets)) return false;
    
    const ticketIndex = data.tickets.findIndex(t => t.channel_id === channelId);
    
    if (ticketIndex === -1) {
        console.error(`❌ Ticket not found for channel: ${channelId}`);
        return false;
    }
    
    data.tickets[ticketIndex].status = status;
    data.tickets[ticketIndex].updated_at = new Date().toISOString();
    
    if (price) {
        data.tickets[ticketIndex].final_price = price;
    }
    
    const success = writeTickets(data);
    if (success) {
        console.log(`✅ Ticket status updated: ${channelId} -> ${status}`);
    }
    return success;
}

function deleteTicket(channelId) {
    const data = readTickets();
    if (!data.tickets || !Array.isArray(data.tickets)) return false;
    
    const initialLength = data.tickets.length;
    data.tickets = data.tickets.filter(t => t.channel_id !== channelId);
    
    if (data.tickets.length !== initialLength) {
        const success = writeTickets(data);
        if (success) {
            console.log(`✅ Ticket deleted: ${channelId}`);
        }
        return success;
    }
    
    console.error(`❌ Ticket not found for deletion: ${channelId}`);
    return false;
}

function addMessageToTicket(channelId, messageData) {
    const data = readTickets();
    if (!data.tickets || !Array.isArray(data.tickets)) return false;
    
    const ticketIndex = data.tickets.findIndex(t => t.channel_id === channelId);
    
    if (ticketIndex === -1) {
        console.error(`❌ Ticket not found for message: ${channelId}`);
        return false;
    }
    
    if (!data.tickets[ticketIndex].messages) {
        data.tickets[ticketIndex].messages = [];
    }
    
    data.tickets[ticketIndex].messages.push({
        ...messageData,
        timestamp: new Date().toISOString()
    });
    
    return writeTickets(data);
}

// ==================== TRANSCRIPT FUNCTIONS ====================
function saveTranscript(channelId, transcript) {
    try {
        if (!fs.existsSync(TRANSCRIPTS_DIR)) {
            fs.mkdirSync(TRANSCRIPTS_DIR, { recursive: true });
        }
        
        const fileName = `transcript_${channelId}_${Date.now()}.txt`;
        const filePath = path.join(TRANSCRIPTS_DIR, fileName);
        
        fs.writeFileSync(filePath, transcript, 'utf8');
        console.log(`✅ Transcript saved: ${filePath}`);
        return filePath;
    } catch (error) {
        console.error('❌ Error saving transcript:', error);
        return null;
    }
}

function formatWaktuIndonesia(date) {
    const options = {
        weekday: 'long',
        year: 'numeric',
        month: 'long',
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit',
        timeZone: 'Asia/Jakarta'
    };
    return date.toLocaleDateString('id-ID', options);
}

function formatRupiah(amount) {
    if (!amount || isNaN(amount)) {
        return 'Rp 0';
    }
    return new Intl.NumberFormat('id-ID', {
        style: 'currency',
        currency: 'IDR',
        minimumFractionDigits: 0
    }).format(amount);
}

// Initialize storage on require
initStorage();

module.exports = {
    createTicket,
    getTicketByChannel,
    getTicketByOrderId,
    updateTicketStatus,
    deleteTicket,
    addMessageToTicket,
    saveTranscript,
    formatWaktuIndonesia,
    formatRupiah
};