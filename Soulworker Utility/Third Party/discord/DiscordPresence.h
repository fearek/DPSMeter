#pragma once
#define DISCORD DiscordCustomPresence::getInstance()

class DiscordCustomPresence: public Singleton<DiscordCustomPresence> {
private:
public:
	discord::Core* core{};
	DWORD Init();
	VOID RunCallbacks();
	VOID UpdatePresence(std::string nick,UINT32 maze, UINT8 playerclass);
	VOID ClearPresence();
	bool shouldLoad = true;
	bool shouldUpdate = true;
	bool isInitialized = false;
};