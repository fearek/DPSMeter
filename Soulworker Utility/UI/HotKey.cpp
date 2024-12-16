#include "pch.h"
#include "HotKey.h"
#include ".\UI\DX Input.h"
#include ".\UI\PlayerTable.h"
#include ".\Damage Meter\Damage Meter.h"

AutoHotKey::~AutoHotKey() {
	_callbacks.clear();
}

AutoHotKey::AutoHotKey(const int key1, int key2, int key3, const char* name, int callback_num, HOTKEYCALLBACK* callback, ...) {
	_key[0] = key1; _key[1] = key2; _key[2] = key3;
	_isActive = FALSE;

	if (key3 == -1 && key2 == -1)
		_hotkeyCount = 1;
	else if (key3 == -1 && key2 != -1)
		_hotkeyCount = 2;
	else if (key3 != -1 && key2 != -1)
		_hotkeyCount = 3;

	if (name != nullptr)
		strcpy_s(_name, name);

	va_list va;
	va_start(va, callback);

	for (int i = 0; i < callback_num; i++) {
		_callbacks.push_back(move(*callback));
		callback = va_arg(va, HOTKEYCALLBACK*);
	}

	va_end(va);
}

AutoHotKey::AutoHotKey(const int key1, int key2, const char* name, int callback_num, HOTKEYCALLBACK* callback, ...) {
	_key[0] = key1; _key[1] = key2; _key[2] = -1;
	_isActive = FALSE;

	if (key2 == -1)
		_hotkeyCount = 1;
	else if (key2 != -1)
		_hotkeyCount = 2;

	if (name != nullptr)
		strcpy_s(_name, name);

	va_list va;
	va_start(va, callback);

	for (int i = 0; i < callback_num; i++) {
		_callbacks.push_back(move(*callback));
		callback = va_arg(va, HOTKEYCALLBACK*);
	}

	va_end(va);
}

AutoHotKey::AutoHotKey(const int key1, const char* name, int callback_num, HOTKEYCALLBACK* callback, ...) : _hotkeyCount(1) {
	_key[0] = key1; _key[1] = -1, _key[2] = -1;
	_isActive = FALSE;

	if (name != nullptr)
		strcpy_s(_name, name);

	va_list va;
	va_start(va, callback);

	for (int i = 0; i < callback_num; i++) {
		_callbacks.push_back(move(*callback));
		callback = va_arg(va, HOTKEYCALLBACK*);
	}

	va_end(va);
}

void AutoHotKey::CheckKey() {

	if (_hotkeyCount > HOTKEY._pressedKey.size()) {
		_isActive = FALSE;
		return;
	}

	if (_isActive) {
		if (DXINPUT.isKeyIdle(_key[0]) || DXINPUT.isKeyIdle(_key[1]) || DXINPUT.isKeyIdle(_key[2])) {
			_isActive = FALSE;
		}
		else {
			return;
		}
	}

	for (auto itr = HOTKEY._pressedKey.begin(); itr != HOTKEY._pressedKey.end(); itr++) {

		bool find = FALSE;

		for (int i = 0; i < _hotkeyCount; i++) {
			if (_key[i] == *itr) {
				find = TRUE;
				break;
			}
		}

		if (!find) {
			_isActive = FALSE;
			return;
		}
	}

#if DEBUG_HOTKEY == 1
	LogInstance.WriteLog("[DEBUG] [HOTKEY] [KEY1 = %d] [KEY2 = %d] [KEY3 = %d] [%s]", _key[0], _key[1], _key[2], _name);
#endif

	_isActive = TRUE;

	for (auto itr = _callbacks.begin(); itr != _callbacks.end(); itr++) {
		if ((*itr) != nullptr) {
			DAMAGEMETER.GetLock();
			{
				(*itr)();
			}
			DAMAGEMETER.FreeLock();
		}
	}
}

HotKey::~HotKey() {
	for (auto itr = _hotkeys.begin(); itr != _hotkeys.end(); itr++) {
		delete* itr;
	}
}

void HotKey::CheckKey() {

	for (unsigned int i = 0; i < DXINPUT.GetStateSize(); i++) {
		if (DXINPUT.isKeyRelease(i)) {
			for (auto itr = _pressedKey.begin(); itr != _pressedKey.end(); itr++) {
				if (*itr == i) {

#if DEBUG_HOTKEY == 1
					LogInstance.WriteLog(const_cast<char*>("Release Key - %d"), i);
#endif
					_pressedKey.erase(itr);
					break;
				}
			}
		}
	}

	for (unsigned int i = 0; i < DXINPUT.GetStateSize(); i++) {
		if (DXINPUT.isKeyDown(i)) {
#if DEBUG_HOTKEY == 1
			LogInstance.WriteLog(const_cast<char*>("Down Key - %d"), i);
#endif
			_pressedKey.push_back(i);
		}
	}
}

void HotKey::CheckHotKey() {
	
	for (auto itr = _hotkeys.begin(); itr != _hotkeys.end(); itr++) {
		(*itr)->CheckKey();
	}
}

void HotKey::Update() {

	CheckKey();
	CheckHotKey();

}

void HotKey::InsertHotkeyToogle(int key1, int key2, int key3) {
	
//	HOTKEYCALLBACK callback = bind(&SWDamageMeter::Toggle, &DAMAGEMETER);

//	_hotkeys.push_back(new AutoHotKey(key1, key2, key3, "Toogle", 1, &callback));

}

void HotKey::InsertHotkeyStop(int key1, int key2, int key3) {

	HOTKEYCALLBACK callback1 = std::bind(&SWDamageMeter::Clear, &DAMAGEMETER);
	HOTKEYCALLBACK callback2 = std::bind(&PlayerTable::ClearTable, &PLAYERTABLE);

	_hotkeys.push_back(new AutoHotKey(key1, key2, key3, "Clear", 2, &callback1, &callback2));
}

std::vector<AutoHotKey*>::const_iterator HotKey::begin() { 
	return _hotkeys.begin(); 
}

std::vector<AutoHotKey*>::const_iterator HotKey::end() { 
	return _hotkeys.end(); 
}