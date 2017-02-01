#include "vm.h"

#include <imq/vm.h>
#include <imq/value.h>
#include <imq/parser.h>
#include <imq/library.h>

#include <cstring>

#include <iostream>

using namespace imq;

imqVMachine* imqNewVMachine()
{
	return reinterpret_cast<imqVMachine*>(new VMachine());
}

void imqDestroyVMachine(imqVMachine* vm)
{
	delete reinterpret_cast<VMachine*>(vm);
}

bool imqSetWorkingDirectory(imqVMachine* vm, const imqString dir)
{
	return reinterpret_cast<VMachine*>(vm)->setWorkingDirectory(dir);
}

void imqGCSetDebugMode(imqVMachine* vm, bool mode)
{
	reinterpret_cast<VMachine*>(vm)->getGC()->setDebugMode(mode);
}

imqGCCollectionMode imqGCGetCollectionMode(imqVMachine* vm)
{
	return (imqGCCollectionMode)reinterpret_cast<VMachine*>(vm)->getGC()->getCollectionMode();
}

void imqGCSetCollectionMode(imqVMachine* vm, imqGCCollectionMode mode)
{
	reinterpret_cast<VMachine*>(vm)->getGC()->setCollectionMode((GCCollectionMode)mode);
}

unsigned int imqGCGetManagedCount(imqVMachine* vm)
{
	return (unsigned int)reinterpret_cast<VMachine*>(vm)->getGC()->getManagedCount();
}

unsigned int imqGCGetTrackedMemory(imqVMachine* vm)
{
	return (unsigned int)reinterpret_cast<VMachine*>(vm)->getGC()->getTrackedMemory();
}

unsigned int imqGCGetCollectionBarrier(imqVMachine* vm)
{
	return (unsigned int)reinterpret_cast<VMachine*>(vm)->getGC()->getCollectionBarrier();
}

bool imqGCCollect(imqVMachine* vm, bool force)
{
	return reinterpret_cast<VMachine*>(vm)->getGC()->collect(force);
}

bool imqExecuteString(imqVMachine* vm, const imqString data, imqValue** result)
{
	VMachine* vmachine = reinterpret_cast<VMachine*>(vm);
	QueryParser parser;
	QValue lastResult;
	VBlock* block = nullptr;
	Result res = parser.parseString(data, &block);
	if (!res)
	{
		*result = reinterpret_cast<imqValue*>(new QValue(QValue::String(res.getErr())));
		return false;
	}

	if (!block)
	{
		*result = reinterpret_cast<imqValue*>(new QValue(QValue::Nil()));
		return true;
	}

	block->setEmitLastResult(&lastResult);

	res = vmachine->execute(block);
	if (!res)
	{
		delete block;
		*result = reinterpret_cast<imqValue*>(new QValue(QValue::String(res.getErr())));
		return false;
	}

	delete block;

	*result = reinterpret_cast<imqValue*>(new QValue(lastResult));
	return true;
}

bool imqRegisterStandardLibrary(imqVMachine* vm, imqValue** result)
{
	Result res = register_stdlib(reinterpret_cast<VMachine*>(vm));
	if (res)
	{
		*result = reinterpret_cast<imqValue*>(new QValue(QValue::Nil()));
		return true;
	}
	else
	{
		*result = reinterpret_cast<imqValue*>(new QValue(QValue::String(res.getErr())));
		return false;
	}
}

void imqSetInput(imqVMachine* vm, const imqString key, imqValue* value)
{
	reinterpret_cast<VMachine*>(vm)->getRootContext()->setInput(key, QValue(*reinterpret_cast<QValue*>(value)));
}

imqValue* imqGetInput(imqVMachine* vm, const imqString key)
{
	auto inputs = reinterpret_cast<VMachine*>(vm)->getRootContext()->getInputs();
	auto found = inputs.find(key);
	if (found == inputs.end())
		return nullptr;

	return reinterpret_cast<imqValue*>(new QValue(found->second));
}

imqValue* imqGetOutput(imqVMachine* vm, const imqString key)
{
	auto outputs = reinterpret_cast<VMachine*>(vm)->getRootContext()->getOutputs();
	auto found = outputs.find(key);
	if (found == outputs.end())
		return nullptr;

	return reinterpret_cast<imqValue*>(new QValue(found->second));
}
