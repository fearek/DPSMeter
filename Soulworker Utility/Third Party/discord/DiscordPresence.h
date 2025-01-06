#pragma once
#define DISCORD DiscordCustomPresence::getInstance()

class DiscordCustomPresence: public Singleton<DiscordCustomPresence> {
private:
public:
	DWORD Init();
	void RunCallbacks();
	void UpdatePresence(std::string nick,uint32_t maze, uint8_t playerclass);
	void ClearPresence();
	bool shouldLoad = true;
	bool shouldUpdate = true;
	bool isInitialized = false;
	bool hideName = false;
	bool hideClass = false;
};