#include "ping.h"

void handle_ping(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    int ping = event.from->websocket_ping * 1000;
    std::string s = std::format("Bot latency is: {}ms", ping);
    dpp::message msg;
    msg.set_content(s);
    event.reply(msg);
}