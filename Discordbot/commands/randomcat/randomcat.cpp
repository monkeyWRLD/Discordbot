#include "randomcat.h"


void handle_randomcat(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    bot.request("https://api.thecatapi.com/v1/images/search", dpp::m_get, [event](const dpp::http_request_completion_t& cc) {
        json response = json::parse(cc.body);
        std::string caturl = response.at(0)["url"].get<std::string>();
        dpp::embed embed = dpp::embed().
            set_color(dpp::colors::raspberry).
            set_image(caturl).
            set_footer(dpp::embed_footer().set_text("made by Monkey"));

        dpp::message msg(event.command.channel_id, embed);
        event.reply(msg);
        });
}