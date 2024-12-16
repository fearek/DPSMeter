#pragma once
#include ".\UI\SpecificInfomation.h"

typedef struct _SELECTED_PLAYER {
	
	uint32_t _playerID;
	bool _isSelected;
	SpecificInformation* _specificInfo;

	_SELECTED_PLAYER(uint32_t playerID, bool isSelected, SpecificInformation* specificInfo) : _playerID(playerID), _isSelected(isSelected), _specificInfo(specificInfo) { }
}SELECTED_PLAYER;

#define PLAYERTABLE PlayerTable::getInstance()

class PlayerTable : public Singleton<PlayerTable> {
private:
	std::vector<SELECTED_PLAYER*> _selectInfo;

	bool ToggleSelectInfo(uint32_t id);
	void ShowSelectedTable();
	void BeginPopupMenu();

	void SetWindowSize();
	void SetMainWindowSize();
	void StoreWindowWidth();
	void SetupFontScale();

	void DrawBar(float window_Width, float percent, ImU32 color);
	void SetupTable();
	void UpdateTable(float windowWidth);

	float _globalFontScale;
	float _columnFontScale;
	float _tableFontScale;

	float _curWindowSize;

	bool _tableResize;

	float _tableTime;
	float _accumulatedTime;

public:
	PlayerTable();
	~PlayerTable();

	void Update();
	void ClearTable();
	void ResizeTalbe();

	LONG64 _lastSendTimestamp = 0;
	LONG64 _ping = 0;
	uint32_t _tick = 0;
	bool _isNewestVersion = TRUE;

	float GetTableTime()
	{
		return _tableTime;
	}

};