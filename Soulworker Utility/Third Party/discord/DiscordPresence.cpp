#include "pch.h"
#include "DiscordPresence.h"
#include ".\Damage Meter\MySQLite.h"
#include ".\Damage Meter\Damage Meter.h"
DWORD DiscordCustomPresence::Init()
{
	if (isInitialized || !shouldLoad)
	{
		return TRUE;
	}
	auto result = discord::Core::Create(766705016081612810, DiscordCreateFlags_Default, &core);
	if (result != discord::Result::Ok)
	{
		return FALSE;
	}
	isCoreCreated = true;
	discord::Activity Activity{};
	Activity.SetDetails("Idle");
	Activity.SetState("discord.com/invite/H7jZpcVJhq");
	Activity.SetType(discord::ActivityType::Playing);
	Activity.GetAssets().SetLargeImage("https://cdn.discordapp.com/app-icons/766705016081612810/424794a1896ac89b9fe0d4ffe3619912.png?size=256");
	core->ActivityManager().UpdateActivity(Activity, [](discord::Result callback) {if (callback == discord::Result::Ok) { LogInstance.WriteLog("Discord is initialized"); DISCORD.isInitialized = true; } else { LogInstance.WriteLog("Failed to init discord: %u", callback);}});
	LogInstance.WriteLog("Initialized discord");
	return TRUE;
}
VOID DiscordCustomPresence::RunCallbacks()
{
	core->RunCallbacks();
	return;
}
std::string getCharacterName(int id)
{
	switch (id)
	{
	case 0:
		return "UNKNOWN";
	case 1:
		return "Haru";
	case 2:
		return "Erwin";
	case 3:
		return "Lilly";
	case 4:
		return "Jin";
	case 5:
		return "Stella";
	case 6:
		return "Iris";
	case 7:
		return "Chii";
	case 8:
		return "Ephnel";
	case 9:
		return "Nabi";
	default:
		return "UNKNOWN";
	}
}
VOID DiscordCustomPresence::UpdatePresence(std::string nick, UINT32 maze, UINT8 playerclass)
{
	if (!shouldLoad || !shouldUpdate || !isInitialized)
	{
		return;
	}
	discord::Activity Activity{};
	if (maze != 0) {
		char _mapName[MAX_MAP_LEN];
		SWDB.GetMapNameENG(maze, _mapName, MAX_MAP_LEN);
		std::string detailsString = _mapName;
		detailsString += " | " + nick + " (" + getCharacterName(playerclass) + ")";
		Activity.SetDetails(detailsString.c_str());
		std::string pingString;
		pingString += std::to_string(DAMAGEMETER.GetPing()) + "ms discord.com/invite/H7jZpcVJhq";
		Activity.SetState(pingString.c_str());
	}
	else
	{
		Activity.SetDetails("Character Selection");
		Activity.SetState("discord.com/invite/H7jZpcVJhq");
	}
	if (DAMAGEMETER.isRun()) {
		Activity.GetTimestamps().SetStart(DAMAGEMETER.GetStartTime());
	}
	Activity.SetType(discord::ActivityType::Playing);
	Activity.GetAssets().SetLargeImage("https://cdn.discordapp.com/app-icons/766705016081612810/424794a1896ac89b9fe0d4ffe3619912.png?size=256");
	core->ActivityManager().UpdateActivity(Activity, [](discord::Result callback) {if (callback != discord::Result::Ok) { LogInstance.WriteLog("Failed to update presence: %u", callback); }});

}
VOID DiscordCustomPresence::ClearPresence()
{
	if (isInitialized) {
		core->ActivityManager().ClearActivity([](discord::Result callback) {if (callback != discord::Result::Ok) { LogInstance.WriteLog("Failed to clear presence: %u", callback); }});
	}
}