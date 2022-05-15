#pragma once

#include <unordered_map>
#include <initializer_list>
#include <string>
#include <iostream>

enum STRINGS
{
    //https://i.imgur.com/dT4XLuh.png
    STR_WORLD_NO_INFORMATION,
    PLAYER_NAME_CANT_FIND,

    //https://i.imgur.com/phiBmly.png
    STR_MENU_RESUME,
    STR_MENU_RESET,
    STR_MENU_TOPMOST,
    STR_MENU_HISTORY,
    STR_MENU_OPTIONS,
    STR_MENU_EXIT,

    // https://i.imgur.com/e0KEFOM.png
    STR_MENU_FIT_COLUMN,
    STR_MENU_FIT_ALL_COLUMN,
    STR_MENU_RESET_ORDER,

    // https://i.imgur.com/0UqwGlV.png
    STR_TABLE_NAME,
    STR_TABLE_DPS,
    STR_TABLE_DAMAGE_PERCENT,
    STR_TABLE_TOTAL_DAMAGE,
    STR_TABLE_TOTAL_HIT,
    STR_TABLE_CRIT_RATE,
    STR_TABLE_HIT_PER_SECOND,
    STR_TABLE_CRIT_HIT_PER_SECOND,
    STR_TABLE_SKILL_PER_SECOND,
    STR_TABLE_MAX_COMBO,
    STR_TABLE_ATTACK_CDMG_SUM,
    STR_TABLE_SOUL_GAUGE,
    STR_TABLE_ATTACK_SPEED,
    STR_TABLE_ARMOR_BREAK,
    STR_TABLE_STAMINA,
    STR_TABLE_SOUL_VAPOR,
    STR_TABLE_SOULSTONE_PERCENT,
    STR_TABLE_SOULSTONE_PROC,
    STR_TABLE_SOULSTONE_DAMAGE,
    STR_TABLE_AVERAGE_AB,
    STR_TABLE_MiSS,
    STR_TABLE_MISS_RATE,
    STR_TABLE_PARTIAL,
    STR_TABLE_GET_HIT_INCLUDEZERO,
    STR_TABLE_GET_HIT,
    STR_TABLE_GET_HIT_BS,
    STR_TABLE_ACC1_BS,
    STR_TABLE_ACC2_BS,
    STR_TABLE_ACC3_BS,

    STR_TABLE_EVADE_RATE_A,
    STR_TABLE_EVADE_RATE_B,
    STR_TABLE_GIGA_ENLIGHTEN,
    STR_TABLE_TERA_ENLIGHTEN,
    STR_TABLE_LOSED_HP,
    STR_TABLE_DODGE_COUNT,

    STR_TABLE_DURATION, // buff,debuff

    // https://i.imgur.com/YG64tR1.png
    STR_OPTION_WINDOWS_NAME,

    STR_OPTION_FONTSCALE,
    STR_OPTION_FONTSCALE_DESC,
    STR_OPTION_UNIT_1K,
    STR_OPTION_UNIT_1M,
    STR_OPTION_SOLO_MODE,
    STR_OPTION_HIDE_NAME,

    STR_OPTION_WINDOW_BORDER_SIZE,
    STR_OPTION_CELL_PADDING,
    STR_OPTION_COLUMN_FONT_SCALE,
    STR_OPTION_TABLE_FONT_SCALE,
    STR_OPTION_TABLE_REFRESH_TIME,
    STR_OPTION_TEXT_OUTLINE_COLOR,
    STR_OPTION_ACTIVE_COLOR,
    STR_OPTION_INACTIVE_COLOR,

    STR_CHAR_UNKNOWN,
    STR_CHAR_HARU,
    STR_CHAR_ERWIN,
    STR_CHAR_LILY,
    STR_CHAR_JIN,
    STR_CHAR_STELLA,
    STR_CHAR_IRIS,
    STR_CHAR_CHII,
    STR_CHAR_Ephnel,
    STR_CHAR_NABI,

    STR_OPTION_RESTORE_DEFAULT_COLOR,

    STR_OPTION_HOTKEY_DESC_1,
    STR_OPTION_HOTKEY_DESC_2,
    STR_OPTION_HOTKEY_DESC_3,
    STR_OPTION_HOTKEY_DESC_4,
    STR_OPTION_HOTKEY_DESC_5,

    STR_OPTION_TEST_VALUE_PLAYER,
    STR_OPTION_ADD_TEST_VALUE,
    STR_OPTION_SAVE_AND_EXIT,

    STR_OPTION_TAB_TABLE_SETTING,
    STR_OPTION_TAB_HOTKEY_SETTING,

    // https://i.imgur.com/OBnBsek.png
    STR_DETAIL_DETAIL,
    STR_DETAIL_SKILL,
    STR_DETAIL_MONSTER,
    STR_DETAIL_BUFF_AND_DEBUFF,

    STR_UTILWINDOW_MEOW,

    STR_UTILWINDOW_DPSGRAPH,
    STR_UTILWINDOW_DPSGRAPH_TIME_SEC,
    STR_UTILWINDOW_ABGRAPH,
    STR_UTILWINDOW_ABGRAPH_TIME_SEC,
    STR_UTILWINDOW_JQGRAPH,
    STR_UTILWINDOW_JQGRAOH_TIME_SEC,

    STR_UTILWINDOW_COMBATLOG
};

enum LANGUAGE
{
    ENGLISH,
    KOREAN,
    CHINESE,
    JAPANESE
};

struct DICTIONARY_VAL
{
    LANGUAGE lang;
    std::string text;
};

struct DICTIONARY_BLOCK_t {
    STRINGS key;
    std::vector<DICTIONARY_VAL> values;
};

class DICTIONARY_t
{
private:
    std::unordered_map<STRINGS, std::vector<DICTIONARY_VAL>> _data;
    LANGUAGE _lang;
public:
    DICTIONARY_t(std::initializer_list<DICTIONARY_BLOCK_t> var);

    /// <summary>
    /// Set the Language to used.
    /// </summary>
    /// <param name="lang"></param>
    void SetLanguage(LANGUAGE lang);

    /// <summary>
    /// Get the short language name used by SQLite
    /// </summary>
    /// <returns>The short language name used by SQLite</returns>
    std::string GetLanguageNameUsedForSQLite();

    /// <summary>
    /// Get the text by key for corresponding Language.
    /// </summary>
    /// <param name="key">key</param>
    /// <returns>text</returns>
    std::string GetText(STRINGS key);
};

extern DICTIONARY_t Language;