#include <imq/value.h>

inline bool sampleNativeFunction(int argc, imq::QValue** args, imq::QValue* result)
{
	return false;
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