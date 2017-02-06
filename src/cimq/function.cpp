#include "function.h"

#include <imq/value.h>
#include <imq/vm.h>

using namespace imq;

class QCVMFunction : public QFunction
{
public:
	QCVMFunction(VMachine* vm, QCFunction f)
		: QFunction(vm)
	{
		func = f;
	}

	virtual ~QCVMFunction()
	{
	}

	virtual Result execute(VMachine* vm, int32_t argCount, QValue* args, QValue* result) override
	{
		imqValue** argsArr = nullptr;
		if (argCount > 0)
			argsArr = new imqValue*[argCount];

		for (int32_t i = 0; i < argCount; ++i)
		{
			argsArr[i] = reinterpret_cast<imqValue*>(new QValue(args[i]));
		}

		FunctionReturn r = func(reinterpret_cast<imqVMachine*>(vm), argCount, argsArr);
		delete[] argsArr;
		if (!r.bError)
		{
			if (r.result != nullptr)
				*result = QValue(*reinterpret_cast<QValue*>(r.result));
			return true;
		}
		else
		{
			if (r.result != nullptr)
			{
				String str;
				QValue val;
				reinterpret_cast<QValue*>(r.result)->toString(&val);
				val.getString(&str);
				return Result(false, str);
			}
			else
			{
				return false;
			}
		}
	}

	virtual size_t GC_getSize() const override
	{
		return sizeof(QCVMFunction);
	}

	virtual bool GC_isDynamic() const override
	{
		return false;
	}

private:
	QCFunction func;
};

imqValue* imqCreateFunction(imqVMachine* vm, QCFunction func)
{
	return reinterpret_cast<imqValue*>(new QValue(QValue::Function(new QCVMFunction(reinterpret_cast<VMachine*>(vm), func))));
}