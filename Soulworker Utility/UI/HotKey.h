#pragma once


#define HOTKEY HotKey::getInstance()
typedef std::function<VOID(VOID)> HOTKEYCALLBACK;

#define DEBUG_HOTKEY 0
#define AUTO_HOTKEY_NAME_LEN 32

struct AutoHotKey {
private:
	INT _key[3];
	std::vector<HOTKEYCALLBACK> _callbacks;
	BOOL _isActive;
	INT _hotkeyCount;
	CHAR _name[AUTO_HOTKEY_NAME_LEN];

	AutoHotKey() {}
	AutoHotKey(const AutoHotKey& other) {}

public:
	~AutoHotKey();
	AutoHotKey(const INT key1, INT key2, INT key3, const CHAR* name, INT callback_num = 0, HOTKEYCALLBACK* callback = nullptr, ...);
	AutoHotKey(const INT key1, INT key2, const CHAR* name, INT callback_num = 0, HOTKEYCALLBACK* callback = nullptr, ...);
	AutoHotKey(const INT key1, const CHAR* name, INT callback_num = 0, HOTKEYCALLBACK* callback = nullptr, ...);

	const CHAR* GetName() { return _name; }
	const INT& GetKeyCount() { return _hotkeyCount; }
	const INT* GetKey() { return _key; }

	VOID CheckKey();
};

class HotKey : public Singleton<HotKey> {
	friend AutoHotKey;
private:
	std::vector<AutoHotKey*> _hotkeys;

	VOID CheckKey();
	VOID CheckHotKey();
	
protected:
	std::vector<INT> _pressedKey;

public:
	HotKey(){}
	~HotKey();

	VOID Update();

	VOID InsertHotkeyToogle(INT key1, INT key2, INT key3);
	VOID InsertHotkeyStop(INT key1, INT key2, INT key3);

	std::vector<AutoHotKey*>::const_iterator begin();
	std::vector<AutoHotKey*>::const_iterator end();
};