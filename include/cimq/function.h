#pragma once

#include "platform.h"
#include "value.h"
#include "vm.h"

#ifdef __cplusplus
extern "C"
{
#endif

	struct FunctionReturn
	{
		bool bError;
		imqValue* result;
	};

	typedef FunctionReturn (*QCFunction)(imqVMachine*, int, imqValue**);

	CIMQ_API imqValue* imqCreateFunction(imqVMachine* vm, QCFunction func);

#ifdef __cplusplus
}
#endif