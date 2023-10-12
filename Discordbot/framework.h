#pragma once
//C++ Discord Library
#include <dpp/dpp.h>


//Bot Commands
#include "commands/command.h"
#include "commands/randomcat/randomcat.h"
#include "commands/ping/ping.h"
#include "commands/ban/ban.h"




namespace framework{
	std::ifstream stream("C:/Users/monkey/Documents/GitHub/Discordbot/Discordbot/config.json");
	json configfile = json::parse(stream);
}
