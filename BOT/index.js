const { execSync } = require('child_process');

// ======================
// AUTO INSTALL PACKAGES
// ======================
const REQUIRED_PACKAGES = [
  'discord.js',
  'groq-sdk',
  'mysql2',
  'openai',
];

function autoInstallPackages() {
  console.log('📦 Checking required packages...\n');
  
  let installed = false;
  
  for (const pkg of REQUIRED_PACKAGES) {
    try {
      require.resolve(pkg, { paths: [__dirname] });
      console.log(`  ✅ ${pkg}`);
    } catch (e) {
      console.log(`  ⬇️  Installing ${pkg}...`);
      try {
        execSync(`npm install ${pkg}`, { stdio: 'inherit', cwd: __dirname });
        console.log(`  ✅ ${pkg} installed!`);
        installed = true;
      } catch (err) {
        console.error(`  ❌ Failed to install ${pkg}: ${err.message}`);
      }
    }
  }
  
  if (installed) {
    console.log('\n📦 All packages installed successfully!\n');
  } else {
    console.log('\n📦 All packages already installed.\n');
  }
}

// Run auto-install before anything else
autoInstallPackages();

const { Client, GatewayIntentBits, Collection, REST, Routes, EmbedBuilder } = require('discord.js');
const fs = require('fs');
const path = require('path');
const config = require('./config.json');

const GREEN = '\x1b[32m';
const RED = '\x1b[31m';
const RESET = '\x1b[0m';

const client = new Client({
  intents: [
    GatewayIntentBits.Guilds,
    GatewayIntentBits.GuildMessages,
    GatewayIntentBits.MessageContent,
    GatewayIntentBits.GuildMembers
  ]
});

// Collections
client.commands = new Collection();
client.cooldowns = new Collection();

// ======================
// FUNGSI REKURSIF UNTUK MEMBACA FOLDER
// ======================
function readCommandsRecursively(dir, commandsArray = []) {
  const files = fs.readdirSync(dir);
  
  for (const file of files) {
    const filePath = path.join(dir, file);
    const stat = fs.statSync(filePath);
    
    if (stat.isDirectory()) {
      readCommandsRecursively(filePath, commandsArray);
    } else if (file.endsWith('.js')) {
      commandsArray.push(filePath);
    }
  }
  
  return commandsArray;
}

// ======================
// AUTO LOAD COMMANDS (REKURSIF)
// ======================
function loadCommands() {
  console.log('📂 Loading commands...');
  
  const commandsPath = path.join(__dirname, 'commands');
  
  if (!fs.existsSync(commandsPath)) {
    console.log('📁 No commands folder found, creating...');
    fs.mkdirSync(commandsPath, { recursive: true });
    console.log(`📊 Total commands: 0`);
    return;
  }
  
  const commandFiles = readCommandsRecursively(commandsPath);
  let loadedCount = 0;
  
  commandFiles.forEach(filePath => {
    try {
      const command = require(filePath);
      
      if ('data' in command && 'execute' in command) {
        client.commands.set(command.data.name, command);
        console.log(`${GREEN}BERHASIL${RESET}: Loaded ${command.data.name} (${path.relative(__dirname, filePath)})`);
        loadedCount++;
      } else {
        console.log(`${RED}GAGAL${RESET}: ${filePath} missing "data" or "execute"`);
      }
    } catch (error) {
      console.error(`${RED}GAGAL${RESET}: Failed to load ${filePath}:`, error.message);
    }
  });
  
  console.log(`📊 Total commands loaded: ${loadedCount}`);
}

// ======================
// staff logs
// ======================
client.on('interactionCreate', async (interaction) => {
    try {
        if (interaction.isChatInputCommand()) {
            // command handler
        }

        if (interaction.isButton()) {
            require('./events/handler/staffAttendance')
                .execute(interaction);
        }

    } catch (err) {
        console.error(err);
    }
});


// ======================
// DEPLOY COMMANDS
// ======================
async function deployCommands() {
  try {
    const commands = [];
    
    for (const [name, command] of client.commands) {
      commands.push(command.data.toJSON());
    }
    
    const rest = new REST({ version: '10' }).setToken(config.token);
    
    console.log(`🔄 Deploying ${commands.length} commands...`);
    
    await rest.put(
      Routes.applicationGuildCommands(config.clientId, config.guildId),
      { body: commands }
    );
    
    console.log(`${GREEN}BERHASIL${RESET}: Commands deployed to guild!`);
    
  } catch (error) {
    console.error(`${RED}GAGAL${RESET}: Error deploying commands:`, error);
  }
}

// ======================
// LOAD EVENTS
// ======================
function loadEvents() {
  console.log('📂 Loading events...');
  
  const eventsPath = path.join(__dirname, 'events');
  
  if (!fs.existsSync(eventsPath)) {
    console.log('📁 No events folder found, creating...');
    fs.mkdirSync(eventsPath, { recursive: true });
    console.log('📁 Events folder created');
    return;
  }
  const eventFiles = readCommandsRecursively(eventsPath);
  
  eventFiles.forEach(filePath => {
    try {
      const event = require(filePath);
      
      if (!event.name) {
        console.log(`${RED}GAGAL${RESET}: ${filePath} missing "name" property`);
        return;
      }
      
      if (event.once) {
        client.once(event.name, (...args) => event.execute(...args, client));
      } else {
        client.on(event.name, (...args) => event.execute(...args, client));
      }
      
      console.log(`${GREEN}BERHASIL${RESET}: Event ${event.name} (${path.relative(__dirname, filePath)})`);
    } catch (error) {
      console.error(`${RED}GAGAL${RESET}: Failed to load event ${filePath}:`, error.message);
    }
  });
}

// ======================
// BOT READY
// ======================
client.once('ready', () => {
  console.log(`\n=====================================`);
  console.log(`${GREEN}BERHASIL${RESET}: ${client.user.tag} is ready!`);
  console.log(` Guilds: ${client.guilds.cache.size}`);
  console.log(`📝 Commands: ${client.commands.size}`);
  console.log(`=====================================\n`);
});

// ======================
// ERROR HANDLING
// ======================
process.on('unhandledRejection', error => {
  console.error(`${RED}GAGAL${RESET}: Unhandled Promise Rejection:`, error);
});

process.on('uncaughtException', error => {
  console.error(`${RED}GAGAL${RESET}: Uncaught Exception:`, error);
});

// ======================
// START BOT
// ======================
async function startBot() {
  try {
    console.log('\n🚀 Starting bot...\n');
    
    // === CEK KONEKSI DATABASE ===
    try {
      const dbStatus = require('./PHRP-AI/utils/dbStatus');
      await dbStatus.checkDatabaseConnection();
    } catch (e) {
      console.log('   ⚠️  Database check module tidak ditemukan, skip.');
    }
    
    loadEvents();
    loadCommands();
    await client.login(config.token);
    setTimeout(deployCommands, 3000);
    
  } catch (error) {
    console.error(`${RED}GAGAL${RESET}: Failed to start bot:`, error);
    process.exit(1);
  }
}

startBot();

module.exports = { client };