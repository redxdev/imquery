#pragma once

#include "platform.h"
#include "value.h"
#include "vm.h"

#ifdef __cplusplus
extern "C"
{
#endif

	CIMQ_API imqValue* imqLoadImageFromFile(imqVMachine* vm, const imqString path);
	CIMQ_API bool imqSaveImageToFile(imqValue* value, const imqString path);

#ifdef __cplusplus
}
#endif