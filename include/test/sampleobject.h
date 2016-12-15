#include <imq/value.h>
#include <imq/object.h>
#include <imq/vm.h>

inline imq::Result sampleNativeFunction(imq::VMachine* vm, int32_t argc, imq::QValue* args, imq::QValue* result)
{
	*result = imq::QValue::Nil();
	return true;
}

class SampleObject : public imq::QObject
{
	IMQ_DECLARE_TYPE(SampleObject);

public:
	SampleObject(imq::VMachine* vm)
		: QObject(vm)
	{

	}

	virtual ~SampleObject()
	{

	}

	virtual bool equals(const QObject* other) const override
	{
		return this == other;
	}
};