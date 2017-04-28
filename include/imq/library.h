#pragma once

#include "platform.h"
#include "vm.h"
#include "value.h"
#include "result.h"

#define IMQ_LIB(loadName) imq::Result loadName(imq::VMachine* vm)
#define IMQ_LIB_STD(loadName) IMQ_API imq::Result loadName(imq::VMachine* vm)
#define IMQ_LIB_FUNC(name, func) \
	{ \
		Result res = vm->getRootContext()->setValue(name, QValue::Function(vm, func)); \
		if (!res) return res; \
	}
#define IMQ_LIB_VAL(name, val) \
	{ \
		Result res = vm->getRootContext()->setValue(name, val); \
		if (!res) return res; \
	}
#define IMQ_LIB_SUB(name) \
	{ \
		Result res = name(vm); \
		if (!res) return res; \
	}

namespace imq
{
	IMQ_LIB_STD(register_stdlib);
	IMQ_LIB_STD(register_system);
	IMQ_LIB_STD(register_gc);
	IMQ_LIB_STD(register_conversion);
	IMQ_LIB_STD(register_io);
	IMQ_LIB_STD(register_string);
	IMQ_LIB_STD(register_math);
	IMQ_LIB_STD(register_image);
}