require("dotenv").config();
const {
  Client,
  Collection,
  GatewayIntentBits,
  GuildMember,
} = require("discord.js");
const fs = require("fs");
const { initializeLogger } = require("./functions/tools/logger");

initializeLogger();

// Inisialisasi client Discord beserta intents
const client = new Client({
  intents: [
    GatewayIntentBits.DirectMessages,
    GatewayIntentBits.Guilds,
    GatewayIntentBits.GuildMessages,
    GatewayIntentBits.MessageContent,
    GatewayIntentBits.GuildPresences,
  ],
});

// Inisialisasi koleksi command serta array untuk command
client.commands = new Collection();
client.buttons = new Collection();
client.selectMenus = new Collection();
client.modals = new Collection();
client.commandArray = [];

// Load fungsi-fungsi/event-event dari folder "functions"
const functionFolders = fs.readdirSync(`./src/functions`);

for (const folder of functionFolders) {
  const functionFiles = fs
    .readdirSync(`./src/functions/${folder}`)
    .filter((file) => file.endsWith(".js"));

  // Require setiap fungsi/event yang ada di folder "functions"
  for (const file of functionFiles) {
    const importedModule = require(`./functions/${folder}/${file}`);

    if (typeof importedModule === "function") {
      importedModule(client);
      continue;
    }

    if (
      importedModule &&
      typeof importedModule === "object" &&
      typeof importedModule.default === "function"
    ) {
      importedModule.default(client);
      continue;
    }

    if (
      importedModule &&
      typeof importedModule === "object" &&
      typeof importedModule.setup === "function"
    ) {
      importedModule.setup(client);
      continue;
    }

    console.warn(
      `Module './functions/${folder}/${file}' does not export an executable initializer.`
    );
  }
}

// Handle event, command, dan interaction
client.handleEvents();
client.handleCommands();
client.handleComponents();

// Lakukan login ke bot dengan TOKEN yang sudah diambil
client.login(process.env.TOKEN);
