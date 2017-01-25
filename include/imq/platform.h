#pragma once

#include <string>
#include <cstring>

#define IMQ_VERSION_STR ("0.4.0")

namespace imq
{
	typedef std::string String;
	typedef char* CString;

	inline size_t getStringSize(const String& str)
	{
		return str.length() * sizeof(char);
	}

	inline size_t getCStringSize(const CString str)
	{
		return (strlen(str) + 1) * sizeof(char);
	}

	CString getIMQVersion();
}