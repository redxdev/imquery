#pragma once

#if defined(CIMQ_SHARED_LIB) && defined(_MSC_VER)
	#ifdef CIMQ_SHARED_LIB_BUILD
		#define CIMQ_API __declspec(dllexport)
	#else
		#define CIMQ_API __declspec(dllimport)
	#endif
#else
	#define CIMQ_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif

	typedef char* imqString;

	CIMQ_API const imqString imqGetVersion();

#ifdef __cplusplus
}
#endif