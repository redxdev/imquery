#include <imq/value.h>
#include <imq/object.h>
#include <imq/cast.h>
#include <imq/vm.h>
#include <gtest/gtest.h>

using namespace imq;

class ATestObject : public QObject
{
	IMQ_DECLARE_TYPE(ATestObject);

public:
	ATestObject(VMachine* vm)
		: QObject(vm)
	{

	}

	virtual ~ATestObject()
	{

	}

	virtual bool equals(const QObject* other) const override
	{
		return other == this;
	}
};

IMQ_DEFINE_TYPE(ATestObject);

class BTestObject : public QObject
{
	IMQ_DECLARE_TYPE(BTestObject);

public:
	BTestObject(VMachine* vm)
		: QObject(vm)
	{

	}

	virtual ~BTestObject()
	{

	}

	virtual bool equals(const QObject* other) const override
	{
		return other == this;
	}
};

IMQ_DEFINE_TYPE(BTestObject);

TEST(QObject, Cast)
{
	QObject* obj = new ATestObject(nullptr);
	ATestObject* testA = objectCast<ATestObject>(obj);

	ASSERT_NE(testA, nullptr);

	delete obj;

	obj = new BTestObject(nullptr);
	testA = objectCast<ATestObject>(obj);

	ASSERT_EQ(testA, nullptr);

	delete obj;
}