#pragma once

#define HOTKEY HotKey::getInstance()
typedef std::function<void(void)> HOTKEYCALLBACK;

#ifdef _DEBUG
#define DEBUG_HOTKEY 0
#endif
#define AUTO_HOTKEY_NAME_LEN 32

struct AutoHotKey {
private:
	int _key[3];
	std::vector<HOTKEYCALLBACK> _callbacks;
	bool _isActive;
	int _hotkeyCount;
	char _name[AUTO_HOTKEY_NAME_LEN];

	AutoHotKey() {}
	AutoHotKey(const AutoHotKey& other) {}

public:
	~AutoHotKey();
	AutoHotKey(const int key1, int key2, int key3, const char* name, int callback_num = 0, HOTKEYCALLBACK* callback = nullptr, ...);
	AutoHotKey(const int key1, int key2, const char* name, int callback_num = 0, HOTKEYCALLBACK* callback = nullptr, ...);
	AutoHotKey(const int key1, const char* name, int callback_num = 0, HOTKEYCALLBACK* callback = nullptr, ...);

	const char* GetName() { return _name; }
	const int& GetKeyCount() { return _hotkeyCount; }
	const int* GetKey() { return _key; }

	void CheckKey();
};

class HotKey : public Singleton<HotKey> {
	friend AutoHotKey;
private:
	std::vector<AutoHotKey*> _hotkeys;

	void CheckKey();
	void CheckHotKey();
	
protected:
	std::vector<int> _pressedKey;

public:
	HotKey(){}
	~HotKey();

	void Update();

	void InsertHotkeyToogle(int key1, int key2, int key3);
	void InsertHotkeyStop(int key1, int key2, int key3);

	std::vector<AutoHotKey*>::const_iterator begin();
	std::vector<AutoHotKey*>::const_iterator end();
};