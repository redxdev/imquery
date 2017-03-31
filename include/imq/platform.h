#pragma once

#include <string>
#include <cstring>

#define IMQ_VERSION_STR ("0.4.2")

#ifdef _MSC_VER
	#pragma warning(disable: 4251)
#endif

#if defined(IMQ_SHARED_LIB) && defined(_MSC_VER)
	#ifdef IMQ_SHARED_LIB_BUILD
		#define IMQ_API __declspec(dllexport)
	#else
		#define IMQ_API __declspec(dllimport)
	#endif
#else
	#define IMQ_API
#endif

namespace imq
{
	typedef std::string String;
	typedef char* CString;

	inline IMQ_API size_t getStringSize(const String& str)
	{
		return str.length() * sizeof(char);
	}

	inline IMQ_API size_t getCStringSize(const CString str)
	{
		return (strlen(str) + 1) * sizeof(char);
	}

	IMQ_API const CString getIMQVersion();
}