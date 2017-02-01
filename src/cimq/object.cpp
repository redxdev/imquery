#include "object.h"

#include <imq/image.h>
#include <imq/cast.h>

using namespace imq;

imqValue* imqLoadImageFromFile(imqVMachine* vm, const imqString path)
{
	QImage* image = nullptr;
	Result res = QImage::loadFromFile(reinterpret_cast<VMachine*>(vm), path, &image);
	if (!res)
		return nullptr;

	return reinterpret_cast<imqValue*>(new QValue(QValue::Object(image)));
}

bool imqSaveImageToFile(imqValue* value, const imqString path)
{
	QObject* obj = nullptr;
	QValue val(*reinterpret_cast<QValue*>(value));

	if (!val.getObject(&obj))
	{
		return false;
	}

	QImage* img = objectCast<QImage>(obj);
	if (img == nullptr)
	{
		return false;
	}

	Result res = img->saveToFile(path);
	return res.isOk();
}
