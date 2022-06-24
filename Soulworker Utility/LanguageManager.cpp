#include "pch.h"
#include "LanguageManager.h"
#include <unordered_map>
#include <initializer_list>
#include <string>
#include <iostream>

DICTIONARY_t Language =
{
    {STR_WORLD_NO_INFORMATION, {{KOREAN, u8"상세정보"}, {ENGLISH, u8"No Info"}, {CHINESE, u8"未知地區"}, {JAPANESE, u8"情報なし"}}},
    {PLAYER_NAME_CANT_FIND, {{KOREAN, u8"너 누구야?"}, {ENGLISH, u8"Unknown?"}, {CHINESE, u8"未知玩家?"}, {JAPANESE, u8"不明"}}},

    {STR_MENU_RESUME, {{KOREAN, u8"시작/정지"}, {ENGLISH, u8"Start/Pause"}, {CHINESE, u8"開始/暫停"}, {JAPANESE, u8"開始/一時停止"}}},
    {STR_MENU_RESET, {{KOREAN, u8"초기화"}, {ENGLISH, u8"Reset"}, {CHINESE, u8"清除"}, {JAPANESE, u8"リセット"}}},
    {STR_MENU_TOPMOST, {{KOREAN, u8"항상 위에 두기"}, {ENGLISH, u8"Always On Top"}, {CHINESE, u8"顯示在最上層"}, {JAPANESE, u8"最前面で固定"}}},
    {STR_MENU_HISTORY, {{KOREAN, u8"전투내역"}, {ENGLISH, u8"History"}, {CHINESE,  u8"舊記錄"}, {JAPANESE, u8"記録"}}},
    {STR_MENU_OPTIONS, {{KOREAN, u8"옵션"}, {ENGLISH, u8"Option"}, {CHINESE, u8"設定"}, {JAPANESE, u8"環境設定"}}},
    {STR_MENU_EXIT, {{KOREAN, u8"종료"}, {ENGLISH, u8"Exit"}, {CHINESE, u8"離開"}, {JAPANESE, u8"終了"}}},

    {STR_MENU_FIT_COLUMN, {{KOREAN, u8"칸을 크기에 맞추기"}, {ENGLISH, u8"Size column to fit"}, {CHINESE, u8"調整欄位至最適大小"}, {JAPANESE, u8"Size column to fit"}}},
    {STR_MENU_FIT_ALL_COLUMN, {{KOREAN, u8"모든칸을 크기에 맞추기###SizeAll"}, {ENGLISH, u8"Size all columns to fit###SizeAll"}, {CHINESE, u8"調整所有欄位至最適大小"}, {JAPANESE, u8"Size all columns to fit###SizeAll"}}},
    {STR_MENU_RESET_ORDER, {{KOREAN, u8"순서 초기화"}, {ENGLISH, u8"Reset order"}, {CHINESE, u8"重設排序"}, {JAPANESE, u8"Reset order"}}},

    {STR_TABLE_NAME, {{KOREAN, u8"NAME"}, {ENGLISH, u8"NAME"}, {CHINESE, u8"NAME"}, {JAPANESE, u8"NAME"}}},
    {STR_TABLE_DPS, {{KOREAN, u8"DPS"}, {ENGLISH, u8"DPS"}, {CHINESE, u8"DPS"}, {JAPANESE, u8"DPS"}}},
    {STR_TABLE_DAMAGE_PERCENT, {{KOREAN, u8"D%"}, {ENGLISH, u8"D%"}, {CHINESE, u8"D%"}, {JAPANESE, u8"D%"}}},
    {STR_TABLE_TOTAL_DAMAGE, {{KOREAN, u8"DAMAGE"}, {ENGLISH, u8"DAMAGE"}, {CHINESE, u8"DAMAGE"}, {JAPANESE, u8"DAMAGE"}}},
    {STR_TABLE_TOTAL_HIT, {{KOREAN, u8"HIT"}, {ENGLISH, u8"HIT"}, {CHINESE, u8"HIT"}, {JAPANESE, u8"HIT"}}},
    {STR_TABLE_CRIT_RATE, {{KOREAN, u8"CRIT%"}, {ENGLISH, u8"CRIT%"}, {CHINESE, u8"CRIT%"}, {JAPANESE, u8"CRIT%"}}},
    {STR_TABLE_HIT_PER_SECOND, {{KOREAN, u8"HIT/s"}, {ENGLISH, u8"HIT/s"}, {CHINESE, u8"HIT/s"}, {JAPANESE, u8"HIT/s"}}},
    {STR_TABLE_CRIT_HIT_PER_SECOND, {{KOREAN, u8"C.HIT/s"}, {ENGLISH, u8"C.HIT/s"}, {CHINESE, u8"C.HIT/s"}, {JAPANESE, u8"C.HIT/s"}}},
    {STR_TABLE_SKILL_PER_SECOND, {{KOREAN, u8"Skill/s"}, {ENGLISH, u8"Skill/s"}, {CHINESE, u8"Skill/s"}, {JAPANESE, u8"Skill/s"}}},
    {STR_TABLE_MAX_COMBO, {{KOREAN, u8"MAXC"}, {ENGLISH, u8"MAXC"}, {CHINESE, u8"MAXC"}, {JAPANESE, u8"MAXC"}}},
    {STR_TABLE_ATTACK_CDMG_SUM, {{KOREAN, u8"공치합"}, {ENGLISH, u8"ATK+CDMG"}, {CHINESE, u8"攻爆和"}, {JAPANESE, u8"ATK+CDMG"}}},
    {STR_TABLE_SOUL_GAUGE, {{KOREAN, u8"SG"}, {ENGLISH, u8"SG"}, {CHINESE, u8"SG"}, {JAPANESE, u8"SG"}}},
    {STR_TABLE_ATTACK_SPEED, {{KOREAN, u8"공속"}, {ENGLISH, u8"AS"}, {CHINESE,  u8"攻速"}, {JAPANESE, u8"攻撃速度"}}},
    {STR_TABLE_ARMOR_BREAK, {{KOREAN, u8"방관"}, {ENGLISH, u8"AB"}, {CHINESE, u8"貫穿"}, {JAPANESE, u8"貫通"}}},
    {STR_TABLE_STAMINA, {{KOREAN, u8"스태"}, {ENGLISH, u8"Stam"}, {CHINESE, u8"耐力"}, {JAPANESE, u8"スタミナ"}}},
    {STR_TABLE_SOUL_VAPOR, {{KOREAN, u8"SV"}, {ENGLISH, u8"SV"}, {CHINESE, u8"SV"}, {JAPANESE, u8"SV"}}},
    {STR_TABLE_SOULSTONE_PERCENT, {{KOREAN, u8"돌전체비중%"}, {ENGLISH, u8"Stone DMG Rate"}, {CHINESE, u8"靈魂石機率"}, {JAPANESE, u8"Stone Proc"}}},
    {STR_TABLE_SOULSTONE_PROC, {{KOREAN, u8"돌확률%"}, {ENGLISH, u8"Stone Proc"}, {CHINESE, u8"重設排序"}, {JAPANESE, u8"Reset order"}}},
    {STR_TABLE_SOULSTONE_DAMAGE, {{KOREAN, u8"돌데미지%"}, {ENGLISH, u8"Stone DMG"}, {CHINESE,u8"靈魂石傷(%)"}, {JAPANESE, u8"Stone DMG"}}},
    {STR_TABLE_AVERAGE_AB, {{KOREAN, u8"평균방관"}, {ENGLISH, u8"Avg.AB"}, {CHINESE, u8"均貫"}, {JAPANESE, u8"平均貫通"}}},
    {STR_TABLE_AVERAGE_BD, {{KOREAN, u8"평균 BD"}, {ENGLISH, u8"Avg.BD"}, {CHINESE, u8"Avg.BD"}, {JAPANESE, u8"Avg.BD"}}},
    {STR_TABLE_MiSS, {{KOREAN, u8"Miss"}, {ENGLISH, u8"Miss"}, {CHINESE, u8"Miss"}, {JAPANESE, u8"Miss"}}},
    {STR_TABLE_MISS_RATE, {{KOREAN, u8"Miss%"}, {ENGLISH, u8"Miss%"}, {CHINESE, u8"Miss%"}, {JAPANESE, u8"Miss%"}}},
    {STR_TABLE_PARTIAL, {{KOREAN, u8"Partial"}, {ENGLISH, u8"Partial"}, {CHINESE, u8"失敗傷"}, {JAPANESE, u8"Miss時ダメージ%"}}},
    {STR_TABLE_GET_HIT_INCLUDEZERO, {{KOREAN, u8"피격(0뎀포함)"}, {ENGLISH, u8"Get Hit(+0 DMG)"}, {CHINESE, u8"受擊數(含0傷)"}, {JAPANESE, u8"被撃(+0 DMG)"}}},
    {STR_TABLE_GET_HIT, {{KOREAN, u8"피격"}, {ENGLISH, u8"Get Hit"}, {CHINESE, u8"受擊數"}, {JAPANESE, u8"被撃"}}},
    {STR_TABLE_GET_HIT_BS, {{KOREAN, u8"피격(브세)"}, {ENGLISH, u8"Get Hit(BS)"}, {CHINESE, u8"受擊數(BS)"}, {JAPANESE, u8"被撃(BS)"}}},
    {STR_TABLE_ACC1_BS, {{KOREAN, u8"악세1"}, {ENGLISH, u8"ACC1(BS)"}, {CHINESE, u8"76飾1型"}, {JAPANESE, u8"アクセ1(BS)"}}},
    {STR_TABLE_ACC2_BS, {{KOREAN, u8"악세2"}, {ENGLISH, u8"ACC2(BS)"}, {CHINESE, u8"76飾2型"}, {JAPANESE, u8"アクセ2(BS)"}}},
    {STR_TABLE_ACC3_BS, {{KOREAN, u8"악세3"}, {ENGLISH, u8"ACC3(BS)"}, {CHINESE, u8"76飾3型"}, {JAPANESE, u8"アクセ3(BS)"}}},

    {STR_TABLE_EVADE_RATE_A, {{KOREAN, u8"회피율A"}, {ENGLISH, u8"Evade Rate A"}, {CHINESE, u8"迴避率 A"}, {JAPANESE, u8"回避発動率 A"}}},
    {STR_TABLE_EVADE_RATE_B, {{KOREAN, u8"회피율B"}, {ENGLISH, u8"Evade Rate B"}, {CHINESE, u8"迴避率 B"}, {JAPANESE, u8"回避発動率 B"}}},
    {STR_TABLE_GIGA_ENLIGHTEN, {{KOREAN, u8"기가인라"}, {ENGLISH, u8"Giga.Enli"}, {CHINESE, u8"Giga啟蒙"}, {JAPANESE, u8"ギガ.エンラ"}}},
    {STR_TABLE_TERA_ENLIGHTEN, {{KOREAN, u8"테라인라"}, {ENGLISH, u8"Tera.Enli"}, {CHINESE, u8"Tera啟蒙"}, {JAPANESE, u8"テラ.エンラ"}}},
    {STR_TABLE_LOSED_HP, {{KOREAN, u8"잃은HP"}, {ENGLISH, u8"Losed HP"}, {CHINESE, u8"損失HP"}, {JAPANESE, u8"失ったHP"}}},
    {STR_TABLE_DODGE_COUNT, {{KOREAN, u8"회피기"}, {ENGLISH, u8"Dodge"}, {CHINESE, u8"Dodge"}, {JAPANESE, u8"回避使用"}}},

    {STR_TABLE_DURATION, {{KOREAN,u8"지속시간"}, {ENGLISH, u8"DURATION"}, {CHINESE, u8"持續時間"}, {JAPANESE, u8"持続時間"}}},

    {STR_OPTION_WINDOWS_NAME, {{KOREAN,u8"설정"}, {ENGLISH, u8"Option"}, {CHINESE, u8"設定"}, {JAPANESE, u8"環境設定"}}},

    {STR_OPTION_FONTSCALE, {{KOREAN, u8"폰트 크기"}, {ENGLISH, u8"Font Scale"}, {CHINESE, u8"文字放大倍率"}, {JAPANESE, u8"フォントスケール"}}},
    {STR_OPTION_FONTSCALE_DESC, {{KOREAN, u8"폰트 크기를 조정하여 테이블 크기를 조정 할 수 있습니다."}, {ENGLISH, u8"You can scale Table Size by adjusting Font Scale."}, {CHINESE, u8"可根據視窗大小調整文字放大倍率"}, {JAPANESE, u8"You can scale 表 Size by adjusting フォントスケール."}}},
    {STR_OPTION_UNIT_1K, {{KOREAN, u8"단위 설정(1K)"}, {ENGLISH, u8"Unit - 1K"}, {CHINESE, u8"以千單位顯示(K)"}, {JAPANESE, u8"單位 - 1K"}}},
    {STR_OPTION_UNIT_1M, {{KOREAN, u8"단위 설정(1M)"}, {ENGLISH, u8"Unit - 1M"}, {CHINESE, u8"以百萬單位顯示(M)"}, {JAPANESE, u8"單位 - 1M"}}},
    {STR_OPTION_SOLO_MODE, {{KOREAN, u8"1인 모드"}, {ENGLISH, u8"Solo Mode"}, {CHINESE, u8"單人模式 (只顯示自己的數據)"}, {JAPANESE, u8"ソロモード"}}},
    {STR_OPTION_HIDE_NAME, {{KOREAN, u8"이름 숨기기"}, {ENGLISH, u8"Hide Name"}, {CHINESE, u8"隱藏名稱"}, {JAPANESE, u8"名前未表示"}}},

    {STR_OPTION_WINDOW_BORDER_SIZE, {{KOREAN, u8"창 외곽선"}, {ENGLISH, u8"WindowBorderSize"}, {CHINESE, u8"視窗邊框大小"}, {JAPANESE,  u8"WindowBorderSize"}}},
    {STR_OPTION_CELL_PADDING, {{KOREAN, u8"셀 패딩"}, {ENGLISH, u8"CellPadding"}, {CHINESE, u8"表格間距"}, {JAPANESE, u8"CellPadding"}}},
    {STR_OPTION_COLUMN_FONT_SCALE, {{KOREAN, u8"열 폰트 스케일"}, {ENGLISH, u8"Column Font Scale"}, {CHINESE, u8"表格欄位文字放大倍率"}, {JAPANESE, u8"Column Font Scale"}}},
    {STR_OPTION_TABLE_FONT_SCALE, {{KOREAN, u8"테이블 폰트 스케일"}, {ENGLISH, u8"Table Font Scale"}, {CHINESE, u8"表格內容文字放大倍率"}, {JAPANESE, u8"Table Font Scale"}}},
    {STR_OPTION_TABLE_REFRESH_TIME, {{KOREAN, u8"테이블 갱신시간"}, {ENGLISH, u8"Table RefreshTime"}, {CHINESE, u8"表格內容刷新時間(ms)"}, {JAPANESE, u8"Table RefreshTime"}}},
    {STR_OPTION_TEXT_OUTLINE_COLOR, {{KOREAN, u8"글자 외곽선 색상"}, {ENGLISH, u8"Text Outline Color"}, {CHINESE, u8"文字輪廓顏色"}, {JAPANESE, u8"Text Outline Color"}}},
    {STR_OPTION_ACTIVE_COLOR, {{KOREAN, u8"활성화 색상"}, {ENGLISH, u8"Active Color"}, {CHINESE, u8"運作時的標題欄顏色"}, {JAPANESE, u8"Active Color"}}},
    {STR_OPTION_INACTIVE_COLOR, {{KOREAN, u8"비활성화 색상"}, {ENGLISH, u8"InActive Color"}, {CHINESE, u8"停止時的標題欄顏色"}, {JAPANESE, u8"InActive Color"}}},

    {STR_CHAR_UNKNOWN, {{KOREAN, u8"Unknown"}, {ENGLISH, u8"Unknown"}, {CHINESE, u8"未知玩家"}, {JAPANESE, u8"不明"}}},
    {STR_CHAR_HARU, {{KOREAN, u8"하루"}, {ENGLISH, u8"Haru"}, {CHINESE, u8"哈露"}, {JAPANESE, u8"ハル"}}},
    {STR_CHAR_ERWIN, {{KOREAN, u8"어윈"}, {ENGLISH, u8"Erwin"}, {CHINESE, u8"歐文"}, {JAPANESE, u8"アーウィン"}}},
    {STR_CHAR_LILY, {{KOREAN, u8"릴리"}, {ENGLISH, u8"Lily"}, {CHINESE, u8"莉莉"}, {JAPANESE, u8"リリー"}}},
    {STR_CHAR_JIN, {{KOREAN, u8"진"}, {ENGLISH, u8"Jin"}, {CHINESE, u8"金"}, {JAPANESE, u8"ジン"}}},
    {STR_CHAR_STELLA, {{KOREAN, u8"스텔라"}, {ENGLISH, u8"Stella"}, {CHINESE, u8"史黛菈"}, {JAPANESE, u8"ステラ"}}},
    {STR_CHAR_IRIS, {{KOREAN, u8"이리스"}, {ENGLISH, u8"Iris"}, {CHINESE, u8"伊莉絲"}, {JAPANESE, u8"イリス"}}},
    {STR_CHAR_CHII, {{KOREAN, u8"치이"}, {ENGLISH, u8"Chii"}, {CHINESE, u8"琪"}, {JAPANESE, u8"チイ"}}},
    {STR_CHAR_Ephnel, {{KOREAN, u8"에프넬"}, {ENGLISH, u8"Ephnel"}, {CHINESE, u8"艾芙妮爾"}, {JAPANESE, u8"エフネル"}}},
    {STR_CHAR_NABI, {{KOREAN, u8"이나비"}, {ENGLISH, u8"Nabi"}, {CHINESE, u8"李娜飛"}, {JAPANESE, u8"ナビ"}}},

    {STR_OPTION_RESTORE_DEFAULT_COLOR, {{KOREAN, u8"기본 색상으로 바꾸기"}, {ENGLISH, u8"Restore Default Color"}, {CHINESE, u8"恢復預設顏色"}, {JAPANESE, u8"Restore Default Color"}}},

    {STR_OPTION_HOTKEY_DESC_1, {{KOREAN, u8"기본 일시정지/재개 키는 CTRL + END 키입니다.\n"}, {ENGLISH, u8"Pause/Resume : Ctrl + End\n"}, {CHINESE, u8"開始/暫停 : Ctrl + End\n"}, {JAPANESE, u8"Pause/Resume : Ctrl + End\n"}}},
    {STR_OPTION_HOTKEY_DESC_2, {{KOREAN, u8"기본 초기화 키는 CTRL + DEL 키입니다.\n"}, {ENGLISH, u8"Reset : CTRL + DEL\n\n"}, {CHINESE, u8"清除 : CTRL + DEL\n\n"}, {JAPANESE, u8"Reset : CTRL + DEL\n\n"}}},
    {STR_OPTION_HOTKEY_DESC_3, {{KOREAN, u8"현재는 option.XML에서 직접 수정해야 합니다.\n"}, {ENGLISH,u8"You can edit hotkey by editing option.XML\n"}, {CHINESE, u8"您可以通過編輯 option.XML 來編輯熱鍵\n"}, {JAPANESE, u8"You can edit hotkey by editing option.XML\n"}}},
    {STR_OPTION_HOTKEY_DESC_4, {{KOREAN, u8"각 키의 값은 DirectInput Code Table이 기준입니다.\n"}, {ENGLISH, u8"Value of key is from DirectInput Code Table\n"}, {CHINESE, u8"key 對應的值來自 DirectInput Code Table\n"}, {JAPANESE, u8"Value of key is from DirectInput Code Table\n"}}},
    {STR_OPTION_HOTKEY_DESC_5, {{KOREAN, u8"각 키는 key1부터 순서대로 넣되, 할당하지 않을 키는 -1로 넣어야 합니다.\n"}, {ENGLISH, u8"All hotkeys start from key1 (then key2...)\nIf you don't assign any key, then you need to assign -1"}, {CHINESE, u8"熱鍵的設定從 key1 開始 (接著 key2...)\n如不需要使用 key2/key3 請設定成 -1"}, {JAPANESE, u8"All hotkeys start from key1 (then key2...)\nIf you don't assign any key, then you need to assign -1"}}},

    {STR_OPTION_TEST_VALUE_PLAYER, {{KOREAN, u8"플레이어"}, {ENGLISH, u8"Player"}, {CHINESE, u8"玩家"}, {JAPANESE, u8"Player"}}},
    {STR_OPTION_ADD_TEST_VALUE, {{KOREAN, u8"더미 데미지 추가"}, {ENGLISH, u8"Add Test Value"}, {CHINESE, u8"加入測試資料"}, {JAPANESE, u8"テスト用値追加"}}},
    {STR_OPTION_SAVE_AND_EXIT, {{KOREAN, u8"저장하고 종료하기"}, {ENGLISH, u8"Save and close"}, {CHINESE, u8"保存並退出設定"}, {JAPANESE, u8"保存と終了"}}},

    {STR_OPTION_TAB_TABLE_SETTING, {{KOREAN, u8"Table 설정"}, {ENGLISH, u8"Table"}, {CHINESE, u8"表單"}, {JAPANESE, u8"表"}}},
    {STR_OPTION_TAB_HOTKEY_SETTING, {{KOREAN, u8"Hotkey 설정"}, {ENGLISH, u8"Hotkey"}, {CHINESE, u8"熱鍵"}, {JAPANESE, u8"ショートカット"}}},

    {STR_DETAIL_DETAIL, {{KOREAN, u8"상세정보"}, {ENGLISH, u8"Details"}, {CHINESE, u8"詳細資料"}, {JAPANESE, u8"詳細情報"}}},
    {STR_DETAIL_SKILL, {{KOREAN, u8"스킬"}, {ENGLISH, u8"Skill"}, {CHINESE, u8"技能"}, {JAPANESE, u8"スキル"}}},
    {STR_DETAIL_MONSTER, {{KOREAN, u8"몬스터"}, {ENGLISH, u8"Monster"}, {CHINESE, u8"怪物"}, {JAPANESE, u8"敵"}}},
    {STR_DETAIL_BUFF_AND_DEBUFF, {{KOREAN, u8"버프/디버프 (미완성)1"}, {ENGLISH, u8"Buff/Debuff (incomplete)"}, {CHINESE, u8"增益/減益狀態（不完整）"}, {JAPANESE, u8"バフ·デバフ(未完成)"}}},

    {STR_UTILWINDOW_MEOW, {{KOREAN, u8"애옹한접시"}, {ENGLISH, u8"Meow"}, {CHINESE, u8"Meow"}, {JAPANESE, u8"にゃん"}}},

    {STR_UTILWINDOW_DPSGRAPH, {{KOREAN, u8"DPS 그래프"}, {ENGLISH, u8"DPS Graph"}, {CHINESE, u8"DPS變化圖"}, {JAPANESE, u8"DPS グラフ"}}},
    {STR_UTILWINDOW_DPSGRAPH_TIME_SEC, {{KOREAN, u8"시간(초)"}, {ENGLISH, u8"Time(sec)"}, {CHINESE, u8"Time(sec)"}, {JAPANESE, u8"時間(秒)"}}},
    {STR_UTILWINDOW_ABGRAPH, {{KOREAN, u8"방관 그래프"}, {ENGLISH, u8"AB Graph"}, {CHINESE, u8"貫穿變化圖"}, {JAPANESE, u8"貫通 グラフ"}}},
    {STR_UTILWINDOW_ABGRAPH_TIME_SEC, {{KOREAN, u8"시간(초)"}, {ENGLISH, u8"Time(sec)"}, {CHINESE, u8"Time(sec)"}, {JAPANESE, u8"時間(秒)"}}},
    {STR_UTILWINDOW_JQGRAPH, {{KOREAN, u8"정퀸 스택 그래프"}, {ENGLISH, u8"JQ Stack Graph"}, {CHINESE, u8"女王層數變化圖"}, {JAPANESE, u8"クイーン スタック グラフ"}}},
    {STR_UTILWINDOW_JQGRAOH_TIME_SEC, {{KOREAN, u8"시간(초)"}, {ENGLISH, u8"Time(sec)"}, {CHINESE,u8"Time(sec)"}, {JAPANESE, u8"時間(秒)"}}},

    {STR_UTILWINDOW_COMBATLOG, {{KOREAN, u8"전투 로그"}, {ENGLISH, u8"Combat Log"}, {CHINESE,u8"戰鬥紀錄"}, {JAPANESE, u8"戦闘ログ"}}},
};


DICTIONARY_t::DICTIONARY_t(std::initializer_list<DICTIONARY_BLOCK_t> var)
{
    _lang = ENGLISH;
    for (DICTIONARY_BLOCK_t val : var)
    {
        _data[val.key] = val.values;
    }
}

/// <summary>
/// Set the Language to used.
/// </summary>
/// <param name="lang"></param>
void DICTIONARY_t::SetLanguage(LANGUAGE lang)
{
    if (lang >= ENGLISH && lang <= JAPANESE)
        _lang = lang;
    else
    {
        _lang = ENGLISH;
        LogInstance.WriteLog("Set a wrong language");
    }

}

/// <summary>
/// Get the short language name used by SQLite
/// </summary>
/// <returns>The short language name used by SQLite</returns>
std::string DICTIONARY_t::GetLanguageNameUsedForSQLite()
{
    if (_lang == KOREAN)
        return u8"KR";
    else if (_lang == ENGLISH)
        return u8"EN";
    else if (_lang == CHINESE)
        return u8"TC";
    else if (_lang == JAPANESE)
        return u8"JP";
    else
        return u8"EN";
}

/// <summary>
/// Get the text by key for corresponding Language.
/// </summary>
/// <param name="key">key</param>
/// <returns>text</returns>
std::string DICTIONARY_t::GetText(STRINGS key)
{
    std::string l_ret = u8"Not Found";
    auto& got = _data.find(key);
    if (got == _data.end())
        return l_ret;

    for (uint32_t j = 0; j < _data[key].size(); j++)
    {
        if (_data[key][j].lang == _lang)
        {
            l_ret = _data[key][j].text;
            break;
        }
    }

    return l_ret;
}