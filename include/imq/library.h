#pragma once

#include "platform.h"
#include "vm.h"
#include "value.h"
#include "result.h"

#define IMQ_LIB(loadName) imq::Result loadName(imq::VMachine* vm)
#define IMQ_LIB_FUNC(name, func) \
	{ \
		Result res = vm->getRootContext()->setValue(name, QValue::Function(func)); \
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
	IMQ_LIB(register_stdlib);
	IMQ_LIB(register_image);
	IMQ_LIB(register_io);
	IMQ_LIB(register_math);
	IMQ_LIB(register_conversion);
}