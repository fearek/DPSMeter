#pragma once
#include <iostream>
#include <codecvt>
#include <locale>
#include <string>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

typedef std::chrono::system_clock::time_point timePoint;

#define FLOOR(x) (FLOAT)((INT)x)

inline BOOL UTF16toUTF8(_In_ WCHAR* src, _Out_ CHAR* dest, _In_ SIZE_T destLen) {

	if (src == nullptr || dest == nullptr)
		return FALSE;

	std::wstring_convert<std::codecvt_utf8_utf16<WCHAR>> wchar_to_utf8;
	std::wstring wstr(src);
	std::string utf8str = wchar_to_utf8.to_bytes(wstr);

	if (destLen < utf8str.size())
		return FALSE;

	strcpy_s(dest, destLen, utf8str.c_str());

	return TRUE;
}

inline BOOL ANSItoUTF8(_In_ CHAR* src, _Out_ CHAR* dest, _In_ INT32 destLen) {

	if (src == nullptr || dest == nullptr)
		return FALSE;

	BSTR bstr;
	int len = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, NULL);
	bstr = SysAllocStringLen(NULL, len);

	MultiByteToWideChar(CP_UTF8, 0, src, -1, bstr, len);

	len = WideCharToMultiByte(CP_ACP, 0, bstr, -1, NULL, 0, NULL, NULL);

	if (len < 1)
		return FALSE;

	if (len < destLen) {
		WideCharToMultiByte(CP_ACP, 0, bstr, -1, dest, destLen, NULL, NULL);
	}
	else {
		SysFreeString(bstr);
		return FALSE;
	}

	return TRUE;
}

inline BOOL TextCommma(_In_ CHAR* src, _Out_ CHAR* dest) {

	if (src == nullptr || dest == nullptr) {
		return FALSE;
	}

	size_t len = strlen(src);

	while (*src) {
		*dest++ = *src++;

		if (--len && (len % 3) == 0)
			*dest++ = ',';
	}
	*dest++ = 0;

	return TRUE;
}

inline BOOL TextCommmaIncludeDecimal(_In_ DOUBLE src, _In_ size_t destLen, _Out_ CHAR* dest) 
{
	if (dest == nullptr) {
		return FALSE;
	}

	char tmp[128] = { 0 };
	char comma[128] = { 0 };
	DOUBLE whole = floor(src);
	DOUBLE decimal = (src - whole) * 10;

	sprintf_s(tmp, "%.0f", whole);
	TextCommma(tmp, comma);
	sprintf_s(dest, destLen, "%s.%.0f", comma, decimal);

	return TRUE;
}

inline ULONG64 GetCurrentTimeStamp() {
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

static BOOL file_contents(const std::filesystem::path& path, std::string* str)
{
	if (!std::filesystem::is_regular_file(path))
		return FALSE;

	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file.is_open())
		return FALSE;

	std::string content{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };

	file.close();

	*str = content;

	return TRUE;
}

#define MAX_BUFFER_LENGTH 1024