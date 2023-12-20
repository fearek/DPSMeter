#pragma once
#include "pch.h"
#include <unordered_map>

#define UIOPTION UiOption::getInstance()

#define OPTION_FILE_NAME "option.xml"
#define NETWORK_NAME_LEN 256

#ifdef _DEBUG
#define DEBUG_READ_XML 0
#define DEBUG_COLUMN_WIDTH 0
#endif

class UiOption : public Singleton<UiOption> {
private:
	ImVec4 _jobColor[11];
	ImVec4 _jobBasicColor[11];
	ImVec4 _activeColor[2];
	ImVec4 _outlineColor;
	ImVec4 _textColor;
	ImVec4 _windowBg;

	float _fontScale;
	bool ShowFontSelector();
	void ShowFeatures();

	float _columnFontScale;
	float _tableFontScale;
	bool _is1K;
	bool _is1M;
	bool _isSoloMode;
	bool _hideName;
	ImVec2 _cellPadding;
	float _framerate;
	float _windowBorderSize;
	float _windowWidth;
	float _refreshTime;
	bool _isTopMost;
	bool _teamTA_LF;
	int32_t _teamTA_LF_Mode = 1;
	char _selectedLang[128] = { 0 };
	bool _isSoloRankMode;
	bool _isUseSaveData;
	bool _isUseImage;
	bool _oriIsUseSaveData;
	char _selectedInterface[MAX_PATH] = { 0 };
	bool _isDontSaveUnfinishedMaze;

	bool ShowTableOption();
	bool ShowHotkeySetting();
	void ShowLangSelector();
	void ChangeLang();

	void ShowTeamTALFSelector();

	void Helper();

	bool GetOption();
	bool SetBasicOption();

	bool _open;

	bool _inited = false;

	std::unordered_map<std::string, std::string> _allLangList = LANGMANAGER.GetAllLangFile();

	std::map<std::string, std::string> _interfaceList;

public:
	UiOption();
	~UiOption();

	const bool& isOption();
	void OpenOption();
	void Update();
	void Init();

	const ImU32 GetJobColor(unsigned int index);
	const ImU32 GetOutlineColor();
	const float& GetFontScale();
	const float& GetColumnFontScale();
	const float& GetTableFontScale();
	const ImVec4& GetActiveColor();
	const ImVec4& GetInActiveColor();
	const ImVec4& GetWindowBGColor();
	const bool& is1K();
	const bool& is1M();
	const bool& isSoloMode();
	const bool& doHideName();
	const bool& isTopMost();
	const bool& isTeamTALF();
	const int32_t& TeamTALFMode();
	const bool& isSoloRankMode();
	const int32_t& GetCaptureMode();
	const bool& isUseSaveData();
	const char* GetUseInterface();
	const bool& isDontSaveUnfinishedMaze();
	const bool& isUseImage();
	bool ToggleTopMost();

	const float& GetFramerate();
	void SetFramerate(float i);

	const float& GetWindowWidth();
	void SetWindowWidth(const float& width);

	const float& GetRefreshTime();

	bool SaveOption(bool skipWarning = false);
};