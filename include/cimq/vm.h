#pragma once

#include "platform.h"
#include "value.h"

#ifdef __cplusplus
extern "C"
{
#endif

	struct imqVMachine;

	enum imqGCCollectionMode
	{
		COLLECT_NOBARRIERS = 0,
		COLLECT_BARRIERS = 1,
		COLLECT_ALWAYS = 2
	};

	CIMQ_API imqVMachine* imqNewVMachine();
	CIMQ_API void imqDestroyVMachine(imqVMachine* vm);

	CIMQ_API bool imqSetWorkingDirectory(imqVMachine* vm, const imqString dir);

	CIMQ_API void imqGCSetDebugMode(imqVMachine* vm, bool mode);
	CIMQ_API imqGCCollectionMode imqGCGetCollectionMode(imqVMachine* vm);
	CIMQ_API void imqGCSetCollectionMode(imqVMachine* vm, imqGCCollectionMode mode);
	CIMQ_API unsigned int imqGCGetManagedCount(imqVMachine* vm);
	CIMQ_API unsigned int imqGCGetTrackedMemory(imqVMachine* vm);
	CIMQ_API unsigned int imqGCGetCollectionBarrier(imqVMachine* vm);
	CIMQ_API bool imqGCCollect(imqVMachine* vm, bool force);

	CIMQ_API bool imqExecuteString(imqVMachine* vm, const imqString data, imqValue** result);

	CIMQ_API bool imqRegisterStandardLibrary(imqVMachine* vm, imqValue** result);

	CIMQ_API void imqSetInput(imqVMachine* vm, const imqString key, imqValue* value);
	CIMQ_API imqValue* imqGetInput(imqVMachine* vm, const imqString key);

	CIMQ_API imqValue* imqGetOutput(imqVMachine* vm, const imqString key);

#ifdef __cplusplus
}
#endif