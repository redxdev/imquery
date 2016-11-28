#include "image.h"

#include <string>

#include "utility.h"
#include "errors.h"

namespace imq
{
	IMQ_DEFINE_TYPE(QColor);

	QColor::QColor()
		: QObject(),
		red(0.f), green(0.f), blue(0.f), alpha(1.f)
	{
	}

	QColor::QColor(float r, float g, float b, float a)
		: QObject(),
		red(r), green(g), blue(b), alpha(a)
	{
	}


	QColor::QColor(const QColor& other)
	{
		this->red = other.red;
		this->green = other.green;
		this->blue = other.blue;
		this->alpha = other.alpha;
	}

	QColor& QColor::operator=(const QColor& other)
	{
		this->red = other.red;
		this->green = other.green;
		this->blue = other.blue;
		this->alpha = other.alpha;
		return *this;
	}

	QColor::~QColor()
	{
	}

	imq::String QColor::toString() const
	{
		std::stringstream ss;
		ss << "{" << red << "," << green << "," << blue << "," << alpha << "}";
		return ss.str();
	}

	bool QColor::equals(const QObject* other) const
	{
		const QColor* color = objectCast<QColor>(other);
		if (color == nullptr)
			return false;

		return red == color->red && green == color->green && blue == color->blue && alpha == color->alpha;
	}

	float QColor::getRed() const
	{
		return red;
	}

	float QColor::getGreen() const
	{
		return green;
	}

	float QColor::getBlue() const
	{
		return blue;
	}

	float QColor::getAlpha() const
	{
		return alpha;
	}

	void QColor::setRed(float val)
	{
		red = val;
	}

	void QColor::setGreen(float val)
	{
		green = val;
	}

	void QColor::setBlue(float val)
	{
		blue = val;
	}

	void QColor::setAlpha(float val)
	{
		alpha = val;
	}

	imq::QColor QColor::clamp() const
	{
		return QColor(
			utility::clamp(red, 0.f, 1.f),
			utility::clamp(green, 0.f, 1.f),
			utility::clamp(blue, 0.f, 1.f),
			utility::clamp(alpha, 0.f, 1.f)
		);
	}

	Result QColor::getField(const String& name, QValue* result) const
	{
		if (name == "red" || name == "r")
		{
			*result = QValue::Float(red);
			return true;
		}
		else if (name == "green" || name == "g")
		{
			*result = QValue::Float(green);
			return true;
		}
		else if (name == "blue" || name == "b")
		{
			*result = QValue::Float(blue);
			return true;
		}
		else if (name == "alpha" || name == "a")
		{
			*result = QValue::Float(alpha);
			return true;
		}

		return errors::undefined_field(getTypeString(), name);
	}

	Result QColor::setField(const String& name, const QValue& value)
	{
		if (name == "red" || name == "r")
		{
			return value.getFloat(&red);
		}
		else if (name == "green" || name == "g")
		{
			return value.getFloat(&green);
		}
		else if (name == "blue" || name == "b")
		{
			return value.getFloat(&blue);
		}
		else if (name == "alpha" || name == "a")
		{
			return value.getFloat(&alpha);
		}

		return errors::undefined_field(getTypeString(), name);
	}

	Result QColor::getIndex(const QValue& index, QValue* result) const
	{
		int32_t idx;
		if (!index.getInteger(&idx))
			return false;

		switch (idx)
		{
		default:
			return errors::undefined_index(getTypeString(), index);

		case 0:
			*result = QValue::Float(red);
			return true;

		case 1:
			*result = QValue::Float(green);
			return true;

		case 2:
			*result = QValue::Float(blue);
			return true;

		case 3:
			*result = QValue::Float(alpha);
			return true;
		}
	}

	Result QColor::setIndex(const QValue& index, const QValue& value)
	{
		int32_t idx;
		if (!index.getInteger(&idx))
			return errors::invalid_index_type(getTypeString(), index);

		switch (idx)
		{
		default:
			return errors::undefined_index(getTypeString(), index);

		case 0:
			return value.getFloat(&red);

		case 1:
			return value.getFloat(&green);

		case 2:
			return value.getFloat(&blue);

		case 3:
			return value.getFloat(&alpha);
		}
	}

}