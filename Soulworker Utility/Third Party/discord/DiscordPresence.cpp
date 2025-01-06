#include "pch.h"
#include ".\DiscordPresence.h"
#include ".\Damage Meter\MySQLite.h"
#include ".\Damage Meter\Damage Meter.h"
#include <atomic>


#ifndef SERVER_KOREA
const char* appId = "1325916409670406325";
const char imageLink[] = "https://cdn.discordapp.com/app-icons/766705016081612810/2e18ca8613674db1caf850a35ca8e9df.png?size=256";
#else
const uint64_t appId = 997228082530353242;
const char imageLink[] = "https://cdn.discordapp.com/app-icons/997228082530353242/daed10ef3cfd4aeef5738e7dbf73d132.png?size=256";
#endif
static bool firstInit = true;
static void handleDiscordError(int errcode, const char* message)
{
	LogInstance.WriteLog("Discord: error (%d: %s)\n", errcode, message);

	DISCORD.isInitialized = false;
	if (!firstInit)
	{
		DISCORD.Init();
	}
}
static void handleDiscordReady(const DiscordUser* connectedUser)
{
	LogInstance.WriteLog("\nDiscord: connected to user %s#%s - %s\n",
		connectedUser->username,
		connectedUser->discriminator,
		connectedUser->userId);

}
DWORD DiscordCustomPresence::Init()
{
	if (isInitialized || !shouldLoad)
	{
		return TRUE;
	}
	firstInit = false;
	DiscordEventHandlers handlers;
	handlers.errored = handleDiscordError;
	handlers.ready = handleDiscordReady;
	memset(&handlers, 0, sizeof(handlers));

	Discord_Initialize(appId, &handlers, 1, NULL);

	LogInstance.WriteLog("Initialized discord");
	isInitialized = true;
	return TRUE;
}
void DiscordCustomPresence::RunCallbacks()
{
	if (!isInitialized)
	{
		Init();
	}
	Discord_RunCallbacks();

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
		return "Lily";
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
	case 10:
		return "Dhana";
	default:
		return "UNKNOWN";
	}
}
void DiscordCustomPresence::UpdatePresence(std::string nick, uint32_t maze, uint8_t playerclass)
{
	if (!shouldLoad || !shouldUpdate || !isInitialized)
	{
		return;
	}
	DiscordRichPresence discordPresence;
	std::string detailsString; //lifetime must be enough so Discord_UpdatePresence can run
	memset(&discordPresence, 0, sizeof(discordPresence));
	if (maze != 0) {
		char _mapName[MAX_MAP_LEN];
		SWDB.GetMapNameENG(maze, _mapName, MAX_MAP_LEN);
		
		if (!hideName)
		{
			detailsString += nick;
		}
		if (!hideClass)
		{
			detailsString += " (" + getCharacterName(playerclass) + ")";
		}
		detailsString += " " + std::to_string(DAMAGEMETER.GetPing()) + "ms";
		discordPresence.details = detailsString.c_str();

		discordPresence.state = _mapName;
	}
	else
	{
		discordPresence.details = "Character Selection";
		discordPresence.state = "discord.com/invite/H7jZpcVJhq";
	}
	if (DAMAGEMETER.isRun()) {
		discordPresence.startTimestamp = DAMAGEMETER.GetStartTime();
	}
	discordPresence.largeImageKey = imageLink;
	discordPresence.button1_label = "Get Meter";
	discordPresence.button1_url = "https://discord.gg/qefpmJXGRu";
	Discord_UpdatePresence(&discordPresence);

}
void DiscordCustomPresence::ClearPresence()
{
	if (isInitialized) {
		Discord_ClearPresence();
	}
}