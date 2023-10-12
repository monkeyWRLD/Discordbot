#include <iostream>
#include <dpp/dpp.h>
#include "commands/command.h"
#include "commands/randomcat/randomcat.h"
#include "commands/ping/ping.h"
#include "commands/ban/ban.h"

const std::string token = "MTE2MTM2NTM0MTY3NTQ1NDQ3NA.GbBZ0J.0M6tB2C7H6qfDNlBFaBK66yHzneQrByQzPz--Y";

std::map<std::string, command_definition> commands = {
    { "ping", { "displays the ping of the bot", handle_ping }},
    { "randomcat", { "Sends a random cat picture", handle_randomcat }},
    { "ban", { "ban a member", handle_ban}}
};

int main()
{
    dpp::cluster bot(token);

    bot.on_log(dpp::utility::cout_logger());

   

    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        dpp::command_interaction cmd_data = event.command.get_command_interaction();
        auto command_iter = commands.find(cmd_data.name);
        if (command_iter != commands.end()) {
            command_iter->second.function(bot, event);
        }
        });

    bot.on_ready([&](const dpp::ready_t& event) {
        if (dpp::run_once<struct bulk_register>()) {
            std::vector<dpp::slashcommand> slash_commands;
            for (auto& def : commands) {
                dpp::slashcommand c;
                c.set_name(def.first).
                    set_description(def.second.description).
                    set_application_id(bot.me.id);
                c.options = def.second.parameters;
                slash_commands.push_back(c);
            }
            bot.global_bulk_command_create(slash_commands);
        }
        bot.set_presence(dpp::presence(dpp::ps_dnd, dpp::at_competing, "deez"));

        });

    bot.start(dpp::st_wait);
    return EXIT_SUCCESS;
}
