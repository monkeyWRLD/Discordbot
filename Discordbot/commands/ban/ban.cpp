#include "ban.h"
void handle_ban(dpp::cluster& bot, const dpp::slashcommand_t& event) {
	dpp::permission perms = event.command.get_resolved_permission(event.command.usr.id);
	dpp::snowflake user_id = std::get<dpp::snowflake>(event.get_parameter("user"));
	dpp::permission userperms = event.command.get_resolved_permission(user_id);

	if (!perms.can(dpp::p_ban_members) && (event.command.usr.id != dpp::snowflake(framework::configfile["creator"]))) {
		
		dpp::embed embed = dpp::embed().
			set_color(dpp::colors::raspberry).
			set_title("ERROR!").
			set_description("No Permissions!").
			set_footer(dpp::embed_footer().set_text("made by Monkey"));

		dpp::message msg(event.command.channel_id, embed);
		event.reply(msg);
		return;
	}
	
	if (userperms.has(dpp::p_administrator)) {
		event.reply("You can't ban Admins!");
		return;
	}

	if (!event.command.app_permissions.can(dpp::p_ban_members)) {
		event.reply("The bot doesn't have the required permission to ban anyone!");
		return;
	}

	event.reply("meow");
}