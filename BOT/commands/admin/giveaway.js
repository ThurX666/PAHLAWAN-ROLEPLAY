const { SlashCommandBuilder } = require('discord.js');
const config = require('../../config.json');
const giveawayHandler = require('../../events/handler/giveaway');

module.exports = {
    data: new SlashCommandBuilder()
        .setName('giveaway')
        .setDescription('Giveaway commands')
        .setDefaultMemberPermissions('0')
        .addSubcommand(subcommand =>
            subcommand
                .setName('create')
                .setDescription('Buat giveaway baru'))
        .addSubcommand(subcommand =>
            subcommand
                .setName('end')
                .setDescription('Hentikan giveaway')
                .addStringOption(option =>
                    option.setName('id')
                        .setDescription('ID giveaway (lihat di embed giveaway)')
                        .setRequired(true)))
        .addSubcommand(subcommand =>
            subcommand
                .setName('reroll')
                .setDescription('Pilih ulang pemenang')
                .addStringOption(option =>
                    option.setName('id')
                        .setDescription('ID giveaway')
                        .setRequired(true))),
    
    async execute(interaction) {
        if (!interaction.member.roles.cache.has(config.role.admin)) {
            return interaction.reply({ 
                content: '❌ **Hanya admin yang bisa menggunakan command ini!**', 
                ephemeral: true 
            });
        }
        
        const subcommand = interaction.options.getSubcommand();
        
        if (subcommand === 'create') {
            await giveawayHandler.showCreateModal(interaction);
        } else if (subcommand === 'end') {
            await giveawayHandler.handleEndGiveaway(interaction);
        } else if (subcommand === 'reroll') {
            await giveawayHandler.handleRerollGiveaway(interaction);
        }
    }
};