#include "pch.h"
#include ".\UI\PlayerTable.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Damage Meter\History.h"
#include ".\Damage Meter\MySQLite.h"
#include ".\UI\Option.h"
#include ".\UI\UiWindow.h"
#include ".\UI\UtillWindow.h"
#include ".\UI\PlotWindow.h"
#include ".\UI\DX11.h"
#include ".\Soulworker Packet\PacketInfo.h"
#include ".\Soulworker Packet\SWPacketMaker.h"
#include "SWConfig.h"


PlayerTable::PlayerTable() : _tableResize(0), _globalFontScale(0), _columnFontScale(0), _tableFontScale(0), _curWindowSize(0), _tableTime(0), _accumulatedTime(0)
{

}

PlayerTable::~PlayerTable() {
	ClearTable();
}

void PlayerTable::ClearTable() {

	for (auto itr = _selectInfo.begin(); itr != _selectInfo.end(); itr++) {
		delete (*itr)->_specificInfo;
	}

	for (auto itr = _selectInfo.begin(); itr != _selectInfo.end(); itr++) {
		delete (*itr);
	}

	_selectInfo.clear();
	_curWindowSize = 0;
}

void PlayerTable::SetupFontScale() {

	ImFont* font = ImGui::GetFont();

	_globalFontScale = font->Scale;
	_columnFontScale = _globalFontScale * UIOPTION.GetColumnFontScale();
	_tableFontScale = _globalFontScale * UIOPTION.GetTableFontScale();
}

void PlayerTable::ResizeTable() {
	_tableResize = true;
}

void PlayerTable::Update() {

	DAMAGEMETER.GetLock();
	{
		ImGuiStyle& style = ImGui::GetStyle();

		ImVec2 prevWindowPadding = style.WindowPadding;

		style.WindowPadding.x = 0;
		style.WindowPadding.y = 0;

		ImVec4 prevInActiveColor = style.Colors[10];
		ImVec4 prevActiveColor = style.Colors[11];

		if (DAMAGEMETER.isRun()) {
			style.Colors[10] = UIOPTION.GetActiveColor();
			style.Colors[11] = UIOPTION.GetActiveColor();
		}
		else {
			style.Colors[10] = UIOPTION.GetInActiveColor();
			style.Colors[11] = UIOPTION.GetInActiveColor();
		}

		_accumulatedTime += UIWINDOW.GetDeltaTime();

		if (_accumulatedTime > UIOPTION.GetRefreshTime()) {
			_tableTime = static_cast<float>(((double)DAMAGEMETER.GetTime()) / 1000);
			_accumulatedTime = 0;
		}

		SetupFontScale();

		ImGuiWindowFlags windowFlag = ImGuiWindowFlags_None;
		windowFlag |= (ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

		if (!UIOPTION.isOption())
			windowFlag = windowFlag | ImGuiWindowFlags_NoResize;
		

		char title[1024] = { 0 };
		unsigned int miliseconds = ((unsigned int)DAMAGEMETER.GetTime() % 1000);
		if (DAMAGEMETER.mswideness == 1)
		{
			miliseconds = miliseconds / 100;
		}
		else if (DAMAGEMETER.mswideness == 2)
		{
			miliseconds = miliseconds / 10;
		}
		//and if 3 then do nothing basically so we display all to 999
		std::string milisecondsstring = std::to_string(miliseconds);
		//turning it into a string before so we dont display leading 0's so timer is more readable
		sprintf_s(title, 1024, "%s - %02d:%02d.%s [v%s_@FeAr&ga] %s: %ums discord.com/invite/H7jZpcVJhq ###DamageMeter",
			DAMAGEMETER.GetWorldName(),
			(unsigned int)DAMAGEMETER.GetTime() / (60 * 1000), (unsigned int)(DAMAGEMETER.GetTime() / 1000) % 60, milisecondsstring.c_str(),
			APP_VERSION,
			LANGMANAGER.GetText("STR_MENU_PING").c_str(),
			DAMAGEMETER.GetPing()
		);

		ImGui::Begin(title, 0, windowFlag);
		{
			if (!UIOPTION.isOption() || _tableResize)
				SetWindowSize();

			if (UIOPTION.isOption())
				StoreWindowWidth();

			SetMainWindowSize();

			BeginPopupMenu();

			ImGui::OutlineText::PushOutlineText(ImGui::IMGUIOUTLINETEXT(UIOPTION.GetOutlineColor(), 1));
			ImGui::TextAlignCenter::SetTextAlignCenter();
			{
				SetupTable();
			}
			ImGui::TextAlignCenter::UnSetTextAlignCenter();
			ImGui::OutlineText::PopOutlineText();
		}
		ImGui::End();

		ShowSelectedTable();

		style.WindowPadding.x = prevWindowPadding.x;
		style.WindowPadding.y = prevWindowPadding.y;

		style.Colors[10] = prevInActiveColor;
		style.Colors[11] = prevActiveColor;
	}
	DAMAGEMETER.FreeLock();
}

void PlayerTable::SetWindowSize() {

	_tableResize = false;

	ImGuiStyle& style = ImGui::GetStyle();

	if (ImGui::GetScrollMaxY() > 0)
		_curWindowSize += ImGui::GetScrollMaxY();

	ImGui::SetWindowSize(ImVec2(UIOPTION.GetWindowWidth(), FLOOR(_curWindowSize)));
}

void PlayerTable::SetMainWindowSize() {

	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();


	if (UIOPTION.isTopMost()) {
		SetWindowPos(UIWINDOW.GetHWND(), HWND_TOPMOST, static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x + 1), static_cast<int>(size.y + 1), SWP_NOACTIVATE | SWP_SHOWWINDOW);
	}
	else {
		SetWindowPos(UIWINDOW.GetHWND(), HWND_NOTOPMOST, static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x + 1), static_cast<int>(size.y + 1), SWP_NOACTIVATE | SWP_SHOWWINDOW);
	}

	//SetWindowPos(UIWINDOW.GetHWND(), HWND_NOTOPMOST, pos.x, pos.y, size.x + 1, size.y + 1, SWP_NOACTIVATE);
	
}

void PlayerTable::StoreWindowWidth() {
	UIOPTION.SetWindowWidth(ImGui::GetWindowSize().x);
}

void PlayerTable::BeginPopupMenu() {

	if (ImGui::BeginPopupContextItem()) {
		//if (ImGui::MenuItem(STR_MENU_RESUME)) {
		//	//
		//	//DAMAGEMETER.Toggle();
		//}

		if (ImGui::MenuItem(LANGMANAGER.GetText("STR_MENU_RESET").c_str())) {
			DAMAGEMETER.Clear();
			PLAYERTABLE.ClearTable();
		}

		if (ImGui::MenuItem(LANGMANAGER.GetText("STR_MENU_TOPMOST").c_str(), nullptr, UIOPTION.isTopMost())) {
			UIOPTION.ToggleTopMost();
		}

		if (ImGui::MenuItem(LANGMANAGER.GetText("STR_MENU_UTILL").c_str())) {
			UTILLWINDOW.OpenWindow();
		}

		bool history_open = false;
		if (HISTORY.size() > 0)
			history_open = true;

		if (ImGui::BeginMenu(LANGMANAGER.GetText("STR_MENU_HISTORY").c_str(), history_open)) {
			HISTORY.GetLock();
			{
				int32_t i = static_cast<int32_t>(HISTORY.size()), iSelectedID = 0;
				bool bChangeHistory = false;
				HISTORY_INFO* pSelectedHI = nullptr;
				for (auto itr = HISTORY.rbegin(); itr != HISTORY.rend(); itr++)
				{
					HISTORY_INFO* pHI = (HISTORY_INFO*)*itr;

					char label[512] = { 0 };
					char mapName[MAX_MAP_LEN] = { 0 };
					SWDB.GetMapName(pHI->_worldID, mapName, MAX_MAP_LEN);

					sprintf_s(label, "%d.[%02d:%02d:%02d] %s - %02d:%02d.%01d###history%d",
						i,
						pHI->_saveTime->wHour, pHI->_saveTime->wMinute, pHI->_saveTime->wSecond,
						mapName,
						(unsigned int)pHI->_time / (60 * 1000), (unsigned int)(pHI->_time / 1000) % 60, (unsigned int)pHI->_time % 1000 / 100,
						i
					);

					i--;

					if (ImGui::Selectable(label, DAMAGEMETER.GetCurrentHistoryId() == i) && !DAMAGEMETER.isRun()) 
					{
						if (!DAMAGEMETER.isRun()) {
							bChangeHistory = true;
							iSelectedID = i;
							pSelectedHI = pHI;
						}
					}
				}

				if (bChangeHistory)
				{
					DAMAGEMETER.SetCurrentHistoryId(iSelectedID);
					DAMAGEMETER.SetHistory((void*)pSelectedHI);
					bChangeHistory = false;
				}
				HISTORY.FreeLock();
			}
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem(LANGMANAGER.GetText("STR_MENU_MEOW").c_str())) {
			PLOTWINDOW.OpenWindow();
		}

		if (ImGui::MenuItem(LANGMANAGER.GetText("STR_MENU_OPTIONS").c_str())) {
			UIOPTION.UpdateFontList();
			UIOPTION.OpenOption();
		}

		if (ImGui::MenuItem(LANGMANAGER.GetText("STR_MENU_EXIT").c_str())) {
			PostMessage(UIWINDOW.GetHWND(), WM_CLOSE, 0, 0);
		}

		ImGui::EndPopup();
	}
}

void PlayerTable::SetupTable() {

	ImGuiTableFlags tableFlags = ImGuiTableFlags_None;
	tableFlags |= (ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Resizable);

	const int columnSize = 46;
	if (ImGui::BeginTable("###Player Table", columnSize, tableFlags)) {

		ImGuiTableColumnFlags columnFlags = ImGuiTableColumnFlags_None;
		columnFlags |= ImGuiTableColumnFlags_NoSort;

		ImGui::SetWindowFontScale(_columnFontScale);

		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_NAME").c_str(), ImGuiTableColumnFlags_NoReorder | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoClip | ImGuiTableColumnFlags_WidthFixed | columnFlags, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_DPS").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_DAMAGE_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_TOTAL_DAMAGE").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_TOTAL_HIT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_CRIT_RATE").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_HIT_PER_SECOND").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_CRIT_HIT_PER_SECOND").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_SKILL_PER_SECOND").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_MAX_COMBO").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_ATTACK_CDMG_SUM").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_SOUL_GAUGE").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_ATTACK_SPEED").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_ARMOR_BREAK").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_BOSS_DAMAGE").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_STAMINA").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_SOUL_VAPOR").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_SOULSTONE_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_SOULSTONE_PROC").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_SOULSTONE_DAMAGE").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_AVERAGE_AB").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_AVERAGE_BD").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_MISS").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_MISS_RATE").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_PARTIAL").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_GET_HIT_INCLUDE_ZERO_DAMAGE").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_GET_HIT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_GET_HIT_BS").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_ACC1_BS").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_ACC2_BS").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_ACC3_BS").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_EVADE_RATE_A").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_EVADE_RATE_B").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_GIGA_ENLIGHTEN").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_TERA_ENLIGHTEN").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_LOSED_HP").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_DODGE_COUNT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_DEATH").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_FULL_AB_TIME").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_FULL_AB_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_GIGA_ENLIGHTEN_SKILL_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_TERA_ENLIGHTEN_SKILL_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_AGGRO_TIME_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_FULL_AS_TIME").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_FULL_AS_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_AVG_AS_PERCENT").c_str(), columnFlags | ImGuiTableColumnFlags_WidthFixed, -1);
		//ImGuiTableColumnFlags_WidthStretch

		ImGui::TableHeadersRow();

		float window_width = ImGui::GetWindowWidth();

		ImGui::SetWindowFontScale(_tableFontScale);

		UpdateTable(window_width);

		ImGui::SetWindowFontScale(_globalFontScale);

		ImGui::EndTable();
	}

}
#define SET_BIT(var,val, bitIndex) var |= (val << bitIndex)
enum PlayerStatuses {
	NONE = 0,
	AGGROED = 1,
	CHILD_AGGROED = 2,
	AGGROED_CHILD_AGGROED = 3,
	AWAKENED = 4,
	AGGROED_AWAKENED = 5,
	CHILD_AGGROED_AWAKENED = 6,
	ALL = 7
};
class PlayerStatus
{
	enum BITS {
		IS_AGGROED,
		IS_CHILD_AGGROED,
		IS_AWAKENED
	};
	unsigned char flags = 0;
public:
	PlayerStatus(bool isAggroed, bool isChildAggroed, bool isAwakened)
	{
		SET_BIT(flags, isAggroed, IS_AGGROED);
		SET_BIT(flags, isChildAggroed, IS_CHILD_AGGROED);
		SET_BIT(flags, isAwakened, IS_AWAKENED);
	}
	operator unsigned char() { return flags; }
	operator int() { return flags; }

};
void PlayerTable::UpdateTable(float windowWidth) {
	uint64_t max_Damage = 1;
	char comma[128] = { 0 }; char label[128] = { 0 };

	for (auto itr = DAMAGEMETER.begin(); itr != DAMAGEMETER.end(); itr++) {

		// 
		if (UIOPTION.isSoloMode() && DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU")) {
			continue;
		}

		// Skip Unknown Player
		if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) == LANGMANAGER.GetText("PLAYER_NAME_CANT_FIND"))
			continue;

		// 
		if (itr == DAMAGEMETER.begin())
			max_Damage = (*itr)->GetDamage();

		float damage_percent = static_cast<float>((double)(*itr)->GetDamage() / (double)max_Damage);

		if (damage_percent > 1)
			damage_percent = 1;
		else if (damage_percent < 0)
			damage_percent = 0;

		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		DrawBar(windowWidth, damage_percent, UIOPTION.GetJobColor(DAMAGEMETER.GetPlayerJob((*itr)->GetID())));
		uint64_t milliTableTime = (uint64_t)((double)_tableTime * 1000);
		// NAME
		const char* playerName = DAMAGEMETER.GetPlayerName((*itr)->GetID());
		if (UIOPTION.doHideName() && playerName != LANGMANAGER.GetText("STR_TABLE_YOU")) {
			playerName = "";
		}

		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4 saved = ImVec4(style.Colors[0].x, style.Colors[0].y, style.Colors[0].z, style.Colors[0].w);

		uint32_t playerId = (*itr)->GetID();
		bool isAggro = (playerId == DAMAGEMETER.GetAggro());
		bool isChildAggro = (playerId == DAMAGEMETER.GetOwnerID(DAMAGEMETER.GetAggro()));
		bool isAwakened = DAMAGEMETER.PlayerInAwakening(playerId);
		unsigned char status = PlayerStatus(isAggro, isChildAggro, isAwakened);
		switch (status)
		{
		case AGGROED:
			style.Colors[0] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); //red
			break;
		case CHILD_AGGROED:
			style.Colors[0] = ImVec4(0.0f, 0.0f, 1.0f, 1.0f); //blue
			break;
		case AGGROED_CHILD_AGGROED:
			style.Colors[0] = ImVec4(1.0f, 0.0f, 1.0f, 1.0f); //purple
			break;
		case AWAKENED:
			style.Colors[0] = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); //yellow
			break;
		case AGGROED_AWAKENED:
			style.Colors[0] = ImVec4(1.0f, 0.5f, 0.0f, 1.0f); //orange
			break;
		case CHILD_AGGROED_AWAKENED:
			style.Colors[0] = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); //green
			break;
		case ALL:
			style.Colors[0] = ImVec4(0.5f, 0.25f, 0.0f, 1.0f); //brown
			break;
		}
			bool useImage = UIOPTION.isUseImage();


			Texture playerTexture = DIRECTX11.getCharacterTexture(DAMAGEMETER.GetPlayerJob((*itr)->GetID()));

			if (useImage && playerTexture.ptr) {
				ImGui::SetCursorPosX((ImGui::GetColumnWidth() * 0.5) - ((ImGui::CalcTextSize(playerName).x + playerTexture.xSize) / 2)); //because font size can change, we need to use texture size to center properly
			}
			else
			{
				ImGui::SetCursorPosX(ImGui::GetColumnWidth() * 0.5 - (ImGui::CalcTextSize(playerName).x / 2)); // we dont use texture here so center text only, have to do it myself because disabled text centering for this part as it was breaking rendering
			}
			if (useImage && playerTexture.ptr) {
				ImGui::Image((void*)playerTexture.ptr, ImVec2(playerTexture.xSize, playerTexture.ySize));
				ImGui::SameLine();
			}
			ImGui::TextAlignCenter::UnSetTextAlignCenter(); //some gay custom function, breaks text align with image
			if (ImGui::Selectable(playerName, false, ImGuiSelectableFlags_SpanAllColumns))
				ToggleSelectInfo((*itr)->GetID());

			ImGui::TextAlignCenter::SetTextAlignCenter();

			ImGui::TableNextColumn();
			style.Colors[0] = saved;


			// DPS
			if (_tableTime < 1) {
				ImGui::Text("-");
			}
			else {
				double dps = ((double)(*itr)->GetDamage()) / _tableTime;
				if (UIOPTION.is1K())
					dps /= 1000;
				else if (UIOPTION.is1M())
					dps /= 1000000;
				sprintf_s(label, 128, "%.0lf", dps);
				TextCommma(label, comma);
				if (UIOPTION.is1K())
					strcat_s(comma, 128, "K");
				else if (UIOPTION.is1M())
					strcat_s(comma, 128, "M");
				ImGui::Text(comma);

				bool isFirstElement = ((itr - DAMAGEMETER.begin()) == 0);
				PLOTWINDOW.AddData((*itr)->GetID(), DAMAGEMETER.GetPlayerName((*itr)->GetID()), dps, _tableTime, isFirstElement);
			}


			ImGui::TableNextColumn();

			// D%
			if (DAMAGEMETER.GetPlayerTotalDamage() == 0) {
				sprintf_s(label, 128, "%.0lf", (float)0);
				ImGui::Text(label);
			}
			else {
				sprintf_s(label, 128, "%.0lf", ((double)(*itr)->GetDamage() / (double)DAMAGEMETER.GetPlayerTotalDamage()) * 100);
				ImGui::Text(label);
			}

			ImGui::TableNextColumn();

			// DAMAGE
			uint64_t damage = (*itr)->GetDamage();
			if (UIOPTION.is1K())
				damage /= 1000;
			else if (UIOPTION.is1M())
				damage /= 1000000;
			sprintf_s(label, 128, "%llu", damage);
			TextCommma(label, comma);
			if (UIOPTION.is1K())
				strcat_s(comma, 128, "K");
			else if (UIOPTION.is1M())
				strcat_s(comma, 128, "M");
			ImGui::Text(comma);

			ImGui::TableNextColumn();

			// HIT
			sprintf_s(label, 128, "%d", (*itr)->GetHitCount());
			TextCommma(label, comma);
			ImGui::Text(comma);

			ImGui::TableNextColumn();

			// CRIT
			float crit = 0;

			if ((*itr)->GetHitCount() != 0)
				crit = (float)(*itr)->GetCritHitCountForCritRate() / (float)(*itr)->GetHitCountForCritRate() * 100;

			sprintf_s(label, 128, "%.1f", crit);
			ImGui::Text(label);

			ImGui::TableNextColumn();

			// HIT/S
			if (_tableTime == (float)0) {
				sprintf_s(label, 128, "%d", 0);
				ImGui::Text(label);
			}
			else {
				sprintf_s(label, 128, "%.2lf", (double)(*itr)->GetHitCount() / _tableTime);
				ImGui::Text(label);

			}
			ImGui::TableNextColumn();

			//CRIT/S
			if (_tableTime == (float)0) {
				sprintf_s(label, 128, "%d", 0);
				ImGui::Text(label);
			}
			else {
				sprintf_s(label, 128, "%.2lf", (double)(*itr)->GetCritHitCount() / _tableTime);
				ImGui::Text(label);
			}

			ImGui::TableNextColumn();

			// Skill/s
			if (_tableTime == 0.0f) {
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
			}
			else {
				sprintf_s(label, 128, "%.2lf", (double)(*itr)->GetSkillUsed() / _tableTime);
				ImGui::Text(label);
			}

			ImGui::TableNextColumn();


			// MAXC
			sprintf_s(label, 128, "%d", (*itr)->GetMaxCombo());
			TextCommma(label, comma);
			ImGui::Text(comma);

			ImGui::TableNextColumn();

			uint32_t playerID = (*itr)->GetID();
			SWDamageMeter::SW_PLAYER_METADATA* playerMetaData = DAMAGEMETER.GetPlayerMetaData(playerID);

			// Not found stat data
			if (playerMetaData == NULL) {
				continue;
			}

			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime < 1) {
				// Attack+Crit SUM
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();

				// SG
				sprintf_s(label, 128, "%.1f", playerMetaData->GetStat(StatType::SG));
				ImGui::Text(label);
				ImGui::TableNextColumn();
				// AttackSpeed
				sprintf_s(label, 128, "%.1f", playerMetaData->GetStat(StatType::AttackSpeed));
				ImGui::Text(label);
				ImGui::TableNextColumn();

				// AB
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();
				// BD
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();
				// STAM
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();
				// SV
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}
			else {
				// Attack+Crit SUM
				double gongchihap = (double)playerMetaData->GetStat(StatType::MaxAttack) + (double)playerMetaData->GetStat(StatType::CritDamage);
				if (UIOPTION.is1K())
					gongchihap /= 1000;
				else if (UIOPTION.is1M())
					gongchihap /= 1000000;
				sprintf_s(label, 128, "%.0f", gongchihap);
				TextCommma(label, comma);
				if (UIOPTION.is1K())
					strcat_s(comma, 128, "K");
				else if (UIOPTION.is1M())
					strcat_s(comma, 128, "M");
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				static float statTmp = 0;

				// SG
				sprintf_s(label, 128, "%.1f", playerMetaData->GetStat(StatType::SG));
				ImGui::Text(label);

				ImGui::TableNextColumn();
				// AttackSpeed
				sprintf_s(label, 128, "%.1f", playerMetaData->GetStat(StatType::AttackSpeed));
				ImGui::Text(label);

				ImGui::TableNextColumn();
				// AB
				statTmp = playerMetaData->GetStat(StatType::ArmorBreak);
				sprintf_s(label, 128, "%.1f", statTmp);
				PLOTWINDOW.AddAbData(statTmp, _tableTime);
				ImGui::Text(label);

				ImGui::TableNextColumn();
				// BD
				statTmp = playerMetaData->GetSpecialStat(SpecialStatType::BossDamageAddRate);
				sprintf_s(label, 128, "%.1f", statTmp);
				PLOTWINDOW.AddBdData(statTmp, _tableTime);
				ImGui::Text(label);

				ImGui::TableNextColumn();
				// stamina
				sprintf_s(label, 128, "%.1f", playerMetaData->GetStat(StatType::Stamina));
				ImGui::Text(label);

				ImGui::TableNextColumn();
				// SV
				sprintf_s(label, 128, "%.1f", playerMetaData->GetStat(StatType::SV));
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}



			// Soulstone all percent
			double soulstoneAllPercent;
			if ((*itr)->GetDamage() == 0) {
				soulstoneAllPercent = 0.0;
			}
			else {
				soulstoneAllPercent = ((double)(*itr)->GetSoulstoneDamage()) / (*itr)->GetDamage() * 100;
			}

			sprintf_s(label, 128, "%.1f", soulstoneAllPercent);
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// Soulstone crit rate
			double soulstoneProcRate;
			if ((*itr)->GetCritHitCountForCritRate() == 0) {
				soulstoneProcRate = 0.0;
			}
			else {
				soulstoneProcRate = ((double)(*itr)->GetSoulstoneCount()) / (*itr)->GetHitCountForCritRate() * 100;
			}

			sprintf_s(label, 128, "%.1f", soulstoneProcRate);
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// Soulstone damage %
			double soulstoneDamage;
			if ((*itr)->GetDamageForSoulstone() == 0) {
				soulstoneDamage = 0.0;
			}
			else {
				soulstoneDamage = ((double)(*itr)->GetSoulStoneDamageForSoulstone()) / (*itr)->GetDamageForSoulstone() * 100;
			}
			sprintf_s(label, 128, "%.1f", soulstoneDamage);
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// history data tmp
			static double savedResultAB = 0;

			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime == 0) {
				sprintf_s(label, 128, "-");
			}
			else if (DAMAGEMETER.isHistoryMode()) {
				savedResultAB = (*itr)->GetHistoryAvgAB();
				sprintf_s(label, 128, "%.1f", savedResultAB);
			}
			else {

				if ((int64_t)(milliTableTime - playerMetaData->_avgABPreviousTime) < 0) {
					sprintf_s(label, 128, "%.1f", savedResultAB);
				}
				else {
					uint64_t timeDifference = (milliTableTime - playerMetaData->_avgABPreviousTime);
					double currentAB = playerMetaData->GetStat(StatType::ArmorBreak);
					currentAB = currentAB > 100.0 ? 100.0 : currentAB;
					uint64_t calculatedAvgAB = static_cast<uint64_t>((playerMetaData->_avgABSum + timeDifference * currentAB));

					savedResultAB = (double)calculatedAvgAB / milliTableTime;
					sprintf_s(label, 128, "%.1f", savedResultAB);
				}
			}

			ImGui::Text(label);
			ImGui::TableNextColumn();

			// BD
			static double savedResultBD = 0;

			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime == 0) {
				sprintf_s(label, 128, "-");
			}
			else if (DAMAGEMETER.isHistoryMode()) {
				savedResultBD = (*itr)->GetHistoryAvgBD();
				sprintf_s(label, 128, "%.1f", savedResultBD);
			}
			else {

				if ((int64_t)(milliTableTime - playerMetaData->_avgBDPreviousTime) < 0) {
					sprintf_s(label, 128, "%.1f", savedResultBD);
				}
				else {
					uint64_t timeDifference = (milliTableTime - playerMetaData->_avgBDPreviousTime);
					double currentBD = playerMetaData->GetSpecialStat(SpecialStatType::BossDamageAddRate);
					uint64_t calculatedAvgBD = static_cast<uint64_t>((playerMetaData->_avgBDSum + timeDifference * currentBD));

					savedResultBD = (double)calculatedAvgBD / milliTableTime;
					sprintf_s(label, 128, "%.1f", savedResultBD);
				}
			}

			ImGui::Text(label);
			ImGui::TableNextColumn();
			// Miss
			sprintf_s(label, 128, "%d", (*itr)->GetMissCount());
			TextCommma(label, comma);
			ImGui::Text(comma);

			ImGui::TableNextColumn();
			// Miss%
			if ((*itr)->GetMissCount() == 0 || (*itr)->GetHitCountForCritRate() == 0) {
				sprintf_s(label, 128, "%.1f", 0.0);
			}
			else {
				sprintf_s(label, 128, "%.1f", (double)(*itr)->GetMissCount() / (*itr)->GetHitCountForCritRate() * 100);
			}

			ImGui::Text(label);
			ImGui::TableNextColumn();

			// MissDamageRate
			sprintf_s(label, 128, "%.1f", playerMetaData->GetStat(StatType::PartialDamage));
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// GetHit(Include Zero Damage)
			sprintf_s(label, 128, "%d", (*itr)->GetGetHitAll());
			TextCommma(label, comma);
			ImGui::Text(comma);

			ImGui::TableNextColumn();

			// GetHit
			sprintf_s(label, 128, "%d", (*itr)->GetGetHit());
			TextCommma(label, comma);
			ImGui::Text(comma);

			ImGui::TableNextColumn();

			// GetHit(BS)
			sprintf_s(label, 128, "%d", (*itr)->GetGetHitBS());
			TextCommma(label, comma);
			ImGui::Text(comma);

			ImGui::TableNextColumn();

			// BS Gear
			static double gear90savedResult = 0.0;
			static double gear50savedResult = 0.0;
			static double acc01savedResult = 0.0;
			static double acc02savedResult = 0.0;

			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime == 0) {
				sprintf_s(label, 128, "-");
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "-");
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "-");
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();
			}

			else if (DAMAGEMETER.isHistoryMode()) {
				double gearSavedResultSum = (*itr)->GetHistoryBS(90) + (*itr)->GetHistoryBS(50);
				acc01savedResult = (*itr)->GetHistoryBS(1);
				acc02savedResult = (*itr)->GetHistoryBS(2);

				sprintf_s(label, 128, "%.0f", gearSavedResultSum + (*itr)->GetHistoryBS(1));
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "%.0f", gearSavedResultSum + (*itr)->GetHistoryBS(2));
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "%.0f", gearSavedResultSum + 650);
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();
			}
			else {

				uint64_t bs3GearOngoing = playerMetaData->CalBsGear3Set(false, milliTableTime);
				if (bs3GearOngoing != 0 && _accumulatedTime == 0) {
					gear90savedResult = (double)(playerMetaData->_gear90Sum + bs3GearOngoing) / milliTableTime;
				}
				if (bs3GearOngoing == 0 && _accumulatedTime == 0) {
					gear90savedResult = (double)playerMetaData->_gear90Sum / milliTableTime;
				}

				uint64_t bs4GearOngoing = playerMetaData->CalBsGear4Set(false, milliTableTime);
				if (bs4GearOngoing != 0 && _accumulatedTime == 0) {
					gear50savedResult = (double)(playerMetaData->_gear50Sum + bs4GearOngoing) / milliTableTime;
				}
				if (bs4GearOngoing == 0 && _accumulatedTime == 0) {
					gear50savedResult = (double)(playerMetaData->_gear50Sum) / milliTableTime;
				}

				uint64_t bsAcc1Ongoing = playerMetaData->CalBsAccSet1(false, milliTableTime);
				if (bsAcc1Ongoing != 0 && _accumulatedTime == 0) {
					acc01savedResult = (double)(playerMetaData->_acc01Sum + bsAcc1Ongoing) / milliTableTime;
				}
				if (bsAcc1Ongoing == 0 && _accumulatedTime == 0) {
					acc01savedResult = (double)(playerMetaData->_acc01Sum) / milliTableTime;
				}

				uint64_t bsAcc2Ongoing = playerMetaData->CalBsAccSet2(false, milliTableTime);
				if (bsAcc2Ongoing != 0 && _accumulatedTime == 0) {
					acc02savedResult = (double)(playerMetaData->_acc02Sum + bsAcc2Ongoing) / milliTableTime;
				}
				if (bsAcc2Ongoing == 0 && _accumulatedTime == 0) {
					acc02savedResult = (double)(playerMetaData->_acc02Sum) / milliTableTime;
				}

				double gearSum = gear50savedResult + gear90savedResult;

				sprintf_s(label, 128, "%.0f", gearSum + acc01savedResult);
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "%.0f", gearSum + acc02savedResult);
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "%.0f", gearSum + 650);
				TextCommma(label, comma);
				ImGui::Text(comma);
				ImGui::TableNextColumn();

				//if ((int64)(milliTableTime - playerMetaData->_gear90PreviousTime) < 0) {
				//	sprintf_s(label, 128, "%.1f", gear90savedResult);
				//}
				//else if (playerMetaData->_gear90Started == false) {
				//	sprintf_s(label, 128, "0.0");
				//}
				//else {
				//	uint64_t timeDifference = (milliTableTime - playerMetaData->_gear90PreviousTime);
				//	timeDifference = (timeDifference >= 5000) ? 5000 : timeDifference;

				//	uint64_t gear90Sum = (playerMetaData->_gear90Sum + timeDifference * 500);

				//	gear90savedResult = (double)gear90Sum / milliTableTime;
				//	sprintf_s(label, 128, "%.1f", gear90savedResult);
				//}


			}

			//

			// Evade A
			if ((*itr)->GetGetHitAll() == 0) {
				sprintf_s(label, 128, "-");
			}
			else {
				sprintf_s(label, 128, "%.1f%%", (double)(*itr)->GetGetHitMissed() / (*itr)->GetGetHitAll() * 100);
			}
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// Evade B
			if ((*itr)->GetGetHit() == 0) {
				sprintf_s(label, 128, "-");
			}
			else {
				sprintf_s(label, 128, "%.1f%%", (double)(*itr)->GetGetHitMissedReal() / (*itr)->GetGetHit() * 100);
			}
			ImGui::Text(label);
			ImGui::TableNextColumn();


			// Enlighten
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime == 0) {
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}
			else {
				sprintf_s(label, 128, "%u", (*itr)->GetGigaEnlighten());
				ImGui::Text(label);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "%u", (*itr)->GetTeraEnlighten());
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}

			// HP
			double losedHP = 0.0;
			if (DAMAGEMETER.isHistoryMode()) {
				losedHP = (*itr)->GetHistoryLosedHP();
			}
			else {
				losedHP = playerMetaData->_losedHp;
			}
			if (UIOPTION.is1K())
				losedHP /= 1000;
			else if (UIOPTION.is1M())
				losedHP /= 1000000;
			sprintf_s(label, 128, "%.0f", losedHP);
			TextCommma(label, comma);

			if (UIOPTION.is1K())
				strcat_s(comma, 128, "K");
			else if (UIOPTION.is1M())
				strcat_s(comma, 128, "M");

			ImGui::Text(comma);
			ImGui::TableNextColumn();

			// Dodge
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime == 0) {
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}
			else {
				sprintf_s(label, 128, "%u", (*itr)->GetDodgeUsed());
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}

			// Death Counter
			sprintf_s(label, 128, "%u", (*itr)->GetDeathCount());
			ImGui::Text(label);
			ImGui::TableNextColumn();

			static double savedResultFullAB = 0;
			// Full AB Time
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) == LANGMANAGER.GetText("STR_TABLE_YOU")) {
				if (DAMAGEMETER.isHistoryMode()) {
					savedResultFullAB = (*itr)->GetHistoryABTime();
				}
				else {
					playerMetaData->CalcFullABTime(DAMAGEMETER.GetTime());
					savedResultFullAB = playerMetaData->_fullABTime;
				}
				sprintf_s(label, 128, "%.1f", savedResultFullAB);
			}
			else {
				sprintf_s(label, 128, "-");
			}
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// Full AB Percent
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) == LANGMANAGER.GetText("STR_TABLE_YOU")) {
				sprintf_s(label, 128, "%.0f", ((double)(savedResultFullAB * 1000) / DAMAGEMETER.GetTime()) * 100);
			}
			else {
				sprintf_s(label, 128, "-");
			}
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// Enli/Skill(%)
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime == 0 || (*itr)->GetSkillUsed() <= 0) {
				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "-");
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}
			else {
				sprintf_s(label, 128, "%.1f", ((double)(*itr)->GetGigaEnlighten() / (*itr)->GetSkillUsed()) * 100);
				ImGui::Text(label);
				ImGui::TableNextColumn();

				sprintf_s(label, 128, "%.1f", ((double)(*itr)->GetTeraEnlighten() / (*itr)->GetSkillUsed()) * 100);
				ImGui::Text(label);
				ImGui::TableNextColumn();
			}

			// Aggro Percent
			static double savedResultAggroTime = 0;
			if (DAMAGEMETER.isHistoryMode()) {
				savedResultAggroTime = (*itr)->GetHistoryAggroTime();
			}
			else {
				playerMetaData->CalcAggroTime(DAMAGEMETER.GetTime());
				savedResultAggroTime = playerMetaData->_AggroTime;
			}
			sprintf_s(label, 128, "%.0f", ((double)(savedResultAggroTime * 1000) / DAMAGEMETER.GetTime()) * 100);
			ImGui::Text(label);
			ImGui::TableNextColumn();

			static double savedResultFullAS = 0;
			// Full AS Time
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) == LANGMANAGER.GetText("STR_TABLE_YOU")) {
				if (DAMAGEMETER.isHistoryMode()) {
					savedResultFullAS = (*itr)->GetHistoryASTime();
				}
				else {
					playerMetaData->CalcFullASTime(DAMAGEMETER.GetTime());
					savedResultFullAS = playerMetaData->_fullASTime;
				}
				sprintf_s(label, 128, "%.1f", savedResultFullAS);
			}
			else {
				sprintf_s(label, 128, "-");
			}
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// Full AS Percent
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) == LANGMANAGER.GetText("STR_TABLE_YOU")) {
				sprintf_s(label, 128, "%.0f", ((double)(savedResultFullAS * 1000) / DAMAGEMETER.GetTime()) * 100);
			}
			else {
				sprintf_s(label, 128, "-");
			}
			ImGui::Text(label);
			ImGui::TableNextColumn();

			// AS
			static double savedResultAS = 0;
			if (DAMAGEMETER.GetPlayerName((*itr)->GetID()) != LANGMANAGER.GetText("STR_TABLE_YOU") || _tableTime == 0) {
				sprintf_s(label, 128, "-");
			}
			else if (DAMAGEMETER.isHistoryMode()) {
				savedResultAS = (*itr)->GetHistoryAvgAS();
				sprintf_s(label, 128, "%.1f", savedResultAS);
			}
			else {

				if ((int64_t)(milliTableTime - playerMetaData->_avgASPreviousTime) < 0) {
					sprintf_s(label, 128, "%.1f", savedResultAS);
				}
				else {
					uint64_t timeDifference = (milliTableTime - playerMetaData->_avgASPreviousTime);
					double currentAS = playerMetaData->GetStat(StatType::AttackSpeed);
					uint64_t calculatedAvgAS = static_cast<uint64_t>((playerMetaData->_avgASSum + timeDifference * currentAS));

					savedResultAS = (double)calculatedAvgAS / milliTableTime;
					sprintf_s(label, 128, "%.1f", savedResultAS);
				}
			}
			ImGui::Text(label);
			ImGui::TableNextColumn();

			//  (etc)
			PLOTWINDOW.AddJqData((*itr)->GetJqStack(), _tableTime);
		}
	}

void PlayerTable::DrawBar(float window_Width, float percent, ImU32 color) {

	auto draw_list = ImGui::GetWindowDrawList();

	float result_width = window_Width * percent;
	float height = ImGui::GetFontSize();
	ImVec2 line = ImGui::GetCursorScreenPos();

	line.x = FLOOR(line.x);
	ImGui::TablePushBackgroundChannel(); //without this image drawing will break bar
	draw_list->AddRectFilled(ImVec2(line.x, line.y), ImVec2(line.x + result_width, line.y + height), color, 0, 0);
	ImGui::TablePopBackgroundChannel();
}

bool PlayerTable::ToggleSelectInfo(uint32_t id) {

	for (auto itr = _selectInfo.begin(); itr != _selectInfo.end(); itr++) {
		if ((*itr)->_playerID == id) {
			(*itr)->_isSelected = !(*itr)->_isSelected;

			return (*itr)->_isSelected;
		}
	}

	SELECTED_PLAYER* selectinfo = new SELECTED_PLAYER(id, true, new SpecificInformation(id));
	_selectInfo.push_back(selectinfo);

	return selectinfo->_isSelected;
}

void PlayerTable::ShowSelectedTable() {

	for (auto itr = _selectInfo.begin(); itr != _selectInfo.end(); itr++) {
		if ((*itr)->_isSelected == true) {
			(*itr)->_specificInfo->Update(&(*itr)->_isSelected, itr - _selectInfo.begin());
		}
	}
}
