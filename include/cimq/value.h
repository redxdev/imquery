#pragma once

#include "platform.h"

#ifdef __cplusplus
extern "C"
{
#endif

	struct imqValue;
	struct imqFunction;
	struct imqObject;

	enum imqType
	{
		IMQ_NIL = 0,
		IMQ_BOOL = 1,
		IMQ_INTEGER = 2,
		IMQ_FLOAT = 3,
		IMQ_STRING = 4,
		IMQ_FUNCTION = 5,
		IMQ_OBJECT = 6
	};

	CIMQ_API void imqDestroyValue(imqValue* value);

	CIMQ_API imqValue* imqNilValue();
	CIMQ_API imqValue* imqBoolValue(bool val);
	CIMQ_API imqValue* imqIntegerValue(int val);
	CIMQ_API imqValue* imqFloatValue(float val);
	CIMQ_API imqValue* imqStringValue(const imqString val);
	CIMQ_API imqValue* imqFunctionValue(imqFunction* val);
	CIMQ_API imqValue* imqObjectValue(imqObject* val);

	CIMQ_API imqType imqGetValueType(imqValue* value);
	CIMQ_API imqValue* imqGetValueTypeString(imqType typeId);

	CIMQ_API imqValue* imqValueAsString(imqValue* value);

	CIMQ_API imqValue* imqCopyValue(imqValue* value);

	CIMQ_API bool imqGetBool(imqValue* value, bool* result);
	CIMQ_API bool imqGetInteger(imqValue* value, int* result);
	CIMQ_API bool imqGetFloat(imqValue* value, float* result);
	CIMQ_API bool imqGetNumberAsInteger(imqValue* value, int* result);
	CIMQ_API bool imqGetNumberAsFloat(imqValue* value, float* result);
	CIMQ_API bool imqGetString(imqValue* value, imqString* result);
	CIMQ_API bool imqGetFunction(imqValue* value, imqFunction** result);
	CIMQ_API bool imqGetObject(imqValue* value, imqObject** result);

	CIMQ_API imqValue* imqToBool(imqValue* value);
	CIMQ_API imqValue* imqToInteger(imqValue* value);
	CIMQ_API imqValue* imqToFloat(imqValue* value);
	CIMQ_API imqValue* imqToString(imqValue* value);

	CIMQ_API bool imqValueEquals(imqValue* a, imqValue* b);

#ifdef __cplusplus
}
#endif