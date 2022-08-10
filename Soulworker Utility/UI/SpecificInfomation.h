#pragma once

class SpecificInformation : public MemoryPool<SpecificInformation, 10> {
private:
	FLOAT _globalFontScale;
	FLOAT _columnFontScale;
	FLOAT _tableFontScale;

	UINT32 _playerID;

	FLOAT _tableTime;
	FLOAT _accumulatedTime;

	// 스킬 상세 정보
	UINT32 _monsterID_SKILL;

	CHAR _skillName[64];

	VOID UpdateSkillInfo();
	VOID UpdateSkillTotalInfo();
	VOID UpdateMonsterCombo();
	VOID UpdateSkillTable();
	VOID UpdateSkillTotalTable();

	// 버프 집계 정보
	VOID UpdateBuffMeter();
	VOID UpdateBuffTable();

	VOID DrawBar(FLOAT window_Width, FLOAT percent, ImU32 color);
	VOID SetupFontScale();
	VOID Clear();

	SpecificInformation() : _playerID(0), _monsterID_SKILL(0), _globalFontScale(0), _columnFontScale(0), _tableFontScale(0), _tableTime(0), _accumulatedTime(0) {}
public:
	SpecificInformation(UINT32 playerID);
	~SpecificInformation();

	VOID Update(BOOL* open);
};