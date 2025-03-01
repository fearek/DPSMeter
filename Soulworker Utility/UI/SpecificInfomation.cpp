﻿#include "pch.h"
#include ".\UI\SpecificInfomation.h"
#include ".\UI\Option.h"
#include ".\Damage Meter\Damage Meter.h"
#include ".\Buff Meter\Buff Meter.h"
#include ".\UI\UiWindow.h"
#include ".\Damage Meter\MySQLite.h"


SpecificInformation::SpecificInformation(uint32_t playerID) : _playerID(playerID), _monsterID_SKILL(0), _globalFontScale(0), _columnFontScale(0), _tableFontScale(0), _tableTime(0), _accumulatedTime(0) {

}

SpecificInformation::~SpecificInformation() {
	Clear();
}

void SpecificInformation::Clear() {

}

void SpecificInformation::SetupFontScale() {
	ImFont* font = ImGui::GetFont();

	_globalFontScale = font->Scale;
	_columnFontScale = _globalFontScale * UIOPTION.GetColumnFontScale();
	_tableFontScale = _globalFontScale * UIOPTION.GetTableFontScale();
}

void SpecificInformation::Update(bool* open, int64_t index) {

	SetupFontScale();

	_accumulatedTime += UIWINDOW.GetDeltaTime();

	if (_accumulatedTime > UIOPTION.GetRefreshTime()) {
		_tableTime = static_cast<float>((double)DAMAGEMETER.GetTime() / 1000);
		_accumulatedTime = 0;
	}

	char title[128] = { 0 };

	sprintf_s(title, 128, "%s %s ###SpecificInformation%lld", DAMAGEMETER.GetPlayerName(_playerID), LANGMANAGER.GetText("STR_SPECIFICINFO_DETAIL").data(), index);
	ImGui::Begin(title, (bool*)open, ImGuiWindowFlags_None);
	{
		sprintf_s(title, 128, "##tab");

		if(ImGui::BeginTabBar(title))
		{
			UpdateSkillInfo();
			UpdateSkillTotalInfo();
			UpdateBuffMeter();

			ImGui::EndTabBar();
		}
	}
	ImGui::End();
}

void SpecificInformation::UpdateSkillInfo() {
	
	char label[128] = { 0 };
	sprintf_s(label, "%s###DetailSkill", LANGMANAGER.GetText("STR_SPECIFICINFO_SKILL").data());

	if(ImGui::BeginTabItem(label))
	{
		UpdateMonsterCombo();
		
		ImGui::OutlineText::PushOutlineText(ImGui::IMGUIOUTLINETEXT(UIOPTION.GetOutlineColor(), 1));
		ImGui::TextAlignCenter::SetTextAlignCenter();
		{
			UpdateSkillTable();
		}
		ImGui::TextAlignCenter::UnSetTextAlignCenter();
		ImGui::OutlineText::PopOutlineText();

		ImGui::EndTabItem();
	}
}

void SpecificInformation::UpdateSkillTotalInfo() {

	char label[128] = { 0 };
	sprintf_s(label, "%s###SpecificinfoTotal", LANGMANAGER.GetText("STR_SPECIFICINFO_TOTAL").data());
	if (ImGui::BeginTabItem(label))
	{
		ImGui::OutlineText::PushOutlineText(ImGui::IMGUIOUTLINETEXT(UIOPTION.GetOutlineColor(), 1));
		ImGui::TextAlignCenter::SetTextAlignCenter();
		{
			UpdateSkillTotalTable();
		}
		ImGui::TextAlignCenter::UnSetTextAlignCenter();
		ImGui::OutlineText::PopOutlineText();

		ImGui::EndTabItem();
	}
}

void SpecificInformation::UpdateSkillTotalTable()
{
	auto player = DAMAGEMETER.GetPlayerInfo(_playerID);

	if (player == DAMAGEMETER.end())
		return;

	ImGuiStyle& style = ImGui::GetStyle();

	ImVec2 prevWindowPadding = style.WindowPadding;
	style.WindowPadding.x = 0;
	style.WindowPadding.y = 0;

	char table[128] = { 0 };
	sprintf_s(table, 128, "##skilltotaltable");
	if (ImGui::BeginTable(table, 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Reorderable)) {

		ImGui::SetWindowFontScale(_columnFontScale);

		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_NAME").data(), ImGuiTableColumnFlags_NoReorder | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoClip | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_SPECIFICINFO_USE_SKILL_COUNTS").data(), ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_SPECIFICINFO_USE_SKILL_COUNTS_IN_FULL_AB").data(), ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableHeadersRow();

		char comma[128] = { 0 }; char label[128] = { 0 };
		float windowWidth = ImGui::GetWindowWidth();

		ImGui::SetWindowFontScale(_tableFontScale);
		for (auto itr = (*player)->skillCounts.begin(); itr != (*player)->skillCounts.end(); itr++) {
			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			// NAME
			SWDB.GetSkillName(itr->first, _skillName, SKILL_NAME_LEN);
			ImGui::Text(_skillName);
			ImGui::TableNextColumn();

			// 시전횟수
			sprintf_s(label, 128, "%d", itr->second->_count);
			TextCommma(label, comma);
			ImGui::Text(comma);
			ImGui::TableNextColumn();

			// In Full AB
			if ((*player)->GetID() == DAMAGEMETER.GetMyID(TRUE))
			{
				sprintf_s(label, 128, "%d", itr->second->_in_full_ab_count);
			}
			else {
				sprintf_s(label, 128, "-");
			}
			TextCommma(label, comma);
			ImGui::Text(comma);
		}
		ImGui::EndTable();
	}
	ImGui::SetWindowFontScale(_globalFontScale);

	style.WindowPadding.x = prevWindowPadding.x;
	style.WindowPadding.y = prevWindowPadding.y;
}

void SpecificInformation::UpdateMonsterCombo() {

	auto player = DAMAGEMETER.GetPlayerInfo(_playerID);

	if (player == DAMAGEMETER.end())
		return;

	const char* comboPreview = nullptr;

	auto monster = (*player)->GetMonsterInfo(_monsterID_SKILL);

	if (monster != (*player)->end()) {
		comboPreview = (*monster)->GetName();
	}

	char label[128] = { 0 };
	sprintf_s(label, "%s###DetailMonster", LANGMANAGER.GetText("STR_SPECIFICINFO_MONSTER").data());
	if(ImGui::BeginCombo(label, comboPreview, ImGuiComboFlags_HeightLarge)) {
	
		for (auto itr = (*player)->begin(); itr != (*player)->end(); itr++) 
		{
		
			char ext[MONSTER_NAME_LEN] = { 0 };
#ifdef _DEBUG
			sprintf_s(ext, "(%d)", (*itr)->GetDB2());
#endif

			char label[MONSTER_NAME_LEN + MONSTER_NAME_LEN] = { 0 };
			sprintf_s(label, MONSTER_NAME_LEN + MONSTER_NAME_LEN, "%s%s##%d", (*itr)->GetName(), ext, (*itr)->GetID());

			if (ImGui::Selectable(label, _monsterID_SKILL == (*itr)->GetID())) {
				_monsterID_SKILL = (*itr)->GetID();
			}
		}

		ImGui::EndCombo();
	}
}

void SpecificInformation::UpdateSkillTable() {

	auto player = DAMAGEMETER.GetPlayerInfo(_playerID);

	if (player == DAMAGEMETER.end())
		return;

	auto monster = (*player)->GetMonsterInfo(_monsterID_SKILL);

	if (monster == (*player)->end())
		return;

	ImGuiStyle& style = ImGui::GetStyle();

	ImVec2 prevWindowPadding = style.WindowPadding;
	style.WindowPadding.x = 0;
	style.WindowPadding.y = 0;

	char table[128] = { 0 };
	sprintf_s(table, 128, "##skilltable");
	if(ImGui::BeginTable(table, 7, ImGuiTableFlags_Resizable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Reorderable)) {
	
		ImGui::SetWindowFontScale(_columnFontScale);

		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_NAME").data(), ImGuiTableColumnFlags_NoReorder | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoClip | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_DPS").data(), ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_DAMAGE_PERCENT").data(), ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_TOTAL_DAMAGE").data(), ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultHide, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_TOTAL_HIT").data(), ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultHide, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_CRIT_RATE").data(), ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultHide, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_HIT_PER_SECOND").data(), ImGuiTableColumnFlags_WidthFixed, -1);
	// ImGui::TableSetupColumn(STR_TABLE_SKILL_PER_SECOND, ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableHeadersRow();

		uint64_t max_Damage = 1;
		char comma[128] = { 0 }; char label[128] = { 0 };
		float windowWidth = ImGui::GetWindowWidth();

		ImGui::SetWindowFontScale(_tableFontScale);

		for (auto itr = (*monster)->begin(); itr != (*monster)->end(); itr++) {

			if (itr == (*monster)->begin())
				max_Damage = (*itr)->GetDamage();

			float damage_percent = static_cast<float>((double)(*itr)->GetDamage() / (double)max_Damage);

			if (damage_percent > 1)
				damage_percent = 1;
			else if (damage_percent < 0)
				damage_percent = 0;

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			DrawBar(windowWidth, damage_percent, UIOPTION.GetJobColor(DAMAGEMETER.GetPlayerJob(_playerID)));

			// NAME
			ImGui::Text((*itr)->GetName());

			ImGui::TableNextColumn();

			// DPS
			double dps = ((double)(*itr)->GetDamage()) / _tableTime;
			if (UIOPTION.is1K()) {
				dps /= 1000;
				sprintf_s(label, 128, "%.0lf", dps);
			}
			else if (UIOPTION.is1M()) {
				dps /= 1000000;
				sprintf_s(label, 128, "%.1lf", dps);
			}
			else if (UIOPTION.is10K()) {
				dps /= 10000;
				sprintf_s(label, 128, "%.0lf", dps);
			}
			if (UIOPTION.is1M())
				TextCommmaIncludeDecimal(dps, sizeof(comma), comma);
			else {
				sprintf_s(label, 128, "%.0lf", dps);
				TextCommma(label, comma);
			}
			if (UIOPTION.is1K())
				strcat_s(comma, 128, LANGMANAGER.GetText("STR_DISPLAY_UNIT_1K").data());
			else if (UIOPTION.is1M())
				strcat_s(comma, 128, LANGMANAGER.GetText("STR_DISPLAY_UNIT_1M").data());
			else if (UIOPTION.is10K())
				strcat_s(comma, 128, LANGMANAGER.GetText("STR_DISPLAY_UNIT_10K").data());
			ImGui::Text(comma);

			ImGui::TableNextColumn();

			// D%
			sprintf_s(label, 128, "%.0lf", ((double)(*itr)->GetDamage() / (double)(*monster)->GetSkillTotalDamage() * 100));
			ImGui::Text(label);

			ImGui::TableNextColumn();

			// DAMAGE
			uint64_t damage = (*itr)->GetDamage();
			if (UIOPTION.is1K())
				damage /= 1000;
			else if (UIOPTION.is1M())
				damage /= 1000000;
			else if (UIOPTION.is10K())
				damage /= 10000;
			sprintf_s(label, 128, "%llu", damage);
			TextCommma(label, comma);
			if (UIOPTION.is1K())
				strcat_s(comma, 128, LANGMANAGER.GetText("STR_DISPLAY_UNIT_1K").data());
			else if (UIOPTION.is1M())
				strcat_s(comma, 128, LANGMANAGER.GetText("STR_DISPLAY_UNIT_1M").data());
			else if (UIOPTION.is10K())
				strcat_s(comma, 128, LANGMANAGER.GetText("STR_DISPLAY_UNIT_10K").data());
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
				crit = (float)(*itr)->GetCritHitCount() / (float)(*itr)->GetHitCount() * 100;

			sprintf_s(label, 128, "%.0f", crit);
			ImGui::Text(label);

			ImGui::TableNextColumn();

			// HIT/S
			sprintf_s(label, 128, "%.2lf", (double)(*itr)->GetHitCount() / _tableTime);
			ImGui::Text(label);

			ImGui::TableNextColumn();
		}
		
		ImGui::SetWindowFontScale(_globalFontScale);
		ImGui::EndTable();
	}

	style.WindowPadding.x = prevWindowPadding.x;
	style.WindowPadding.y = prevWindowPadding.y;

}

void SpecificInformation::UpdateBuffMeter() {

	BUFFMETER.GetLock();
	{
		char label[128] = { 0 };
		sprintf_s(label, "%s###DetailBuffDeBuff", LANGMANAGER.GetText("STR_SPECIFICINFO_BUFF_AND_DEBUFF").data());
		if (ImGui::BeginTabItem(label))
		{
			ImGui::OutlineText::PushOutlineText(ImGui::IMGUIOUTLINETEXT(UIOPTION.GetOutlineColor(), 1));
			ImGui::TextAlignCenter::SetTextAlignCenter();
			{
				UpdateBuffTable();
			}
			ImGui::TextAlignCenter::UnSetTextAlignCenter();
			ImGui::OutlineText::PopOutlineText();

			ImGui::EndTabItem();
		}
	}
	BUFFMETER.FreeLock();
}

void SpecificInformation::UpdateBuffTable() {

	auto buff = BUFFMETER.find(_playerID);

	if (buff == BUFFMETER.end())
		return;

	ImGuiStyle& style = ImGui::GetStyle();

	ImVec2 prevWindowPadding = style.WindowPadding;
	style.WindowPadding.x = 0;
	style.WindowPadding.y = 0;

	char table[128] = { 0 };
	sprintf_s(table, 128, "##bufftable");
	if (ImGui::BeginTable(table, 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Reorderable)) {

		ImGui::SetWindowFontScale(_columnFontScale);

		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_SPECIFICINFO_BUFF_NAME").data(), ImGuiTableColumnFlags_NoReorder | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoClip | ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableSetupColumn(LANGMANAGER.GetText("STR_TABLE_DURATION").data(), ImGuiTableColumnFlags_WidthFixed, -1);
		ImGui::TableHeadersRow();

		ImGui::SetWindowFontScale(_tableFontScale);

		float windowWidth = ImGui::GetWindowWidth();
		for (auto itr = (*buff)->begin(); itr != (*buff)->end(); itr++) {

			char label[128] = { 0 };
			float duration_percent = (*itr)->GetTime() / (DAMAGEMETER.GetTime() / 1000);

			if (duration_percent > 1)
				duration_percent = 1;
			else if (duration_percent < 0)
				duration_percent = 0;

			ImGui::TableNextRow();
			ImGui::TableNextColumn();

			DrawBar(windowWidth, duration_percent, UIOPTION.GetJobColor(DAMAGEMETER.GetPlayerJob(_playerID)));

			// NAME & DESC
			ImGui::TextAlignCenter::UnSetTextAlignCenter();
			{
				// Custom text align bug BRUH
				ImGui::SetCursorPosX((ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize((*itr)->GetName()).x - ImGui::GetScrollX()) * 0.5f);
				ImGui::Text((*itr)->GetName());
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip((*itr)->GetDesc());
			}
			ImGui::TextAlignCenter::SetTextAlignCenter();
			ImGui::TableNextColumn();

			// DURATION
			sprintf_s(label, 128, "%.0f", duration_percent * 100);
			ImGui::Text(label);
		}

		ImGui::SetWindowFontScale(_globalFontScale);
		ImGui::EndTable();
	}

	style.WindowPadding.x = prevWindowPadding.x;
	style.WindowPadding.y = prevWindowPadding.y;
}

void SpecificInformation::DrawBar(float window_Width, float percent, ImU32 color) {

	auto draw_list = ImGui::GetWindowDrawList();

	float result_width = window_Width * percent;
	float height = ImGui::GetFontSize();
	ImVec2 line = ImGui::GetCursorScreenPos();

	line.x = FLOOR(line.x);	line.y = line.y;
	height = height;

	draw_list->AddRectFilled(ImVec2(line.x, line.y), ImVec2(line.x + result_width, line.y + height), color, 0, 0);
}