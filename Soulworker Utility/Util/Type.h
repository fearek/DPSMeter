#pragma once
#include <iostream>
#include <codecvt>
#include <locale>
#include <string>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

typedef std::chrono::system_clock::time_point timePoint;

#define FLOOR(x) (float)((int)x)

inline bool UTF16toUTF8(_In_ wchar_t* src, _Out_ char* dest, _In_ SIZE_T destLen) {

	if (src == nullptr || dest == nullptr)
		return false;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> wchar_t_to_utf8;
	std::wstring wstr(src);
	std::string utf8str = wchar_t_to_utf8.to_bytes(wstr);

	if (destLen < utf8str.size())
		return false;

	strcpy_s(dest, destLen, utf8str.c_str());

	return true;
}

inline bool ANSItoUTF8(_In_ char* src, _Out_ char* dest, _In_ int32_t destLen) {

	if (src == nullptr || dest == nullptr)
		return false;

	BSTR bstr;
	int len = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, NULL);
	bstr = SysAllocStringLen(NULL, len);

	MultiByteToWideChar(CP_UTF8, 0, src, -1, bstr, len);

	len = WideCharToMultiByte(CP_ACP, 0, bstr, -1, NULL, 0, NULL, NULL);

	if (len < 1)
		return false;

	if (len < destLen) {
		WideCharToMultiByte(CP_ACP, 0, bstr, -1, dest, destLen, NULL, NULL);
	}
	else {
		SysFreeString(bstr);
		return false;
	}

	return true;
}

inline bool TextCommma(_In_ char* src, _Out_ char* dest) {

	if (src == nullptr || dest == nullptr) {
		return false;
	}

	size_t len = strlen(src);

	while (*src) {
		*dest++ = *src++;

		if (--len && (len % 3) == 0)
			*dest++ = ',';
	}
	*dest++ = 0;

	return true;
}

inline bool TextCommmaIncludeDecimal(_In_ double src, _In_ size_t destLen, _Out_ char* dest) 
{
	if (dest == nullptr) {
		return false;
	}

	char tmp[128] = { 0 };
	char comma[128] = { 0 };
	double whole = floor(src);
	double decimal = (src - whole) * 10;

	sprintf_s(tmp, "%.0f", whole);
	TextCommma(tmp, comma);
	sprintf_s(dest, destLen, "%s.%.0f", comma, decimal);

	return true;
}

inline uint64_t GetCurrentTimeStamp() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

static bool file_contents(const std::filesystem::path& path, std::string* str)
{
	if (!std::filesystem::is_regular_file(path))
		return false;

	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file.is_open())
		return false;

	std::string content{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

	file.close();

	*str = content;

	return true;
}

#define MAX_BUFFER_LENGTH 1024