#pragma once
#include "pch.h"
#include <unordered_map>

#define LANGMANAGER Language::getInstance()

class Language : public Singleton<Language>
{

private:
	std::unordered_map<std::string, std::string> _textList;
	CHAR _currentLang[128] = { 0 };
	std::vector<std::string> _notFoundText;

public:
	Language() : _currentLang("zh_tw.json") {}

	const CHAR _langFolder[6] = "Lang/";

	CHAR* GetCurrentLang()
	{
		return _currentLang;
	}
	DWORD SetCurrentLang(CHAR* langFile);
	CHAR* GetText(CHAR* text, std::unordered_map<std::string, std::string>* vector = nullptr);
	std::unordered_map<std::string, std::string> GetAllLangFile();
	auto GetLangFile(CHAR* langFile, BOOL outputERROR = TRUE);
	std::unordered_map<std::string, std::string> MapLangData(CHAR* langFile, BOOL useReplace = TRUE);
};