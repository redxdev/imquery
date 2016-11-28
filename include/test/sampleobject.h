#include <imq/value.h>
#include <imq/object.h>

inline imq::Result sampleNativeFunction(int argc, imq::QValue* args, imq::QValue* result)
{
	*result = imq::QValue::Nil();
	return true;
}

class SampleObject : public imq::QObject
{
	IMQ_DECLARE_TYPE(SampleObject);

public:
	SampleObject()
		: QObject()
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