#include "image.h"

#include <string>

#include "thirdparty/stb_image.h"
#include "thirdparty/stb_image_write.h"
#include "cast.h"
#include "utility.h"
#include "errors.h"

namespace imq
{
	// QColor

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

	bool QColor::operator==(const QColor& other) const
	{
		return red == other.red && green == other.green && blue == other.blue && alpha == other.alpha;
	}

	bool QColor::operator!=(const QColor& other) const
	{
		return !(*this == other);
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

	// QImage

	IMQ_DEFINE_TYPE(QImage);

	Result QImage::loadFromFile(const char* filename, QImage** result)
	{
		int width;
		int height;
		int comp;
		unsigned char* data = stbi_load(filename, &width, &height, &comp, 4);
		if (data == nullptr)
		{
			return errors::image_load_error(stbi_failure_reason());
		}

		*result = new QImage(width, height);
		for (size_t idx = 0; idx < (size_t)(4 * width * height); ++idx)
		{
			(*result)->data[idx] = (float)(data[idx] / 255.f);
		}

		stbi_image_free(data);

		return true;
	}

	QImage::QImage()
		: QObject()
	{
		width = 0;
		height = 0;
		data = nullptr;
	}

	QImage::QImage(int32_t width, int32_t height)
		: QImage(width, height, QColor(0.f, 0.f, 0.f))
	{
	}

	QImage::QImage(int32_t width, int32_t height, const QColor& color)
		: QObject()
	{
		this->width = width;
		this->height = height;
		data = new float[4 * width * height];
		clear(color);
	}

	QImage::QImage(const QImage& other)
	{
		this->width = other.width;
		this->height = other.height;
		data = new float[4 * width * height];
		memcpy(data, other.data, sizeof(float) * 4 * width * height);
	}

	QImage& QImage::operator=(const QImage& other)
	{
		if (data != nullptr)
			delete[] data;

		this->width = other.width;
		this->height = other.height;
		data = new float[4 * width * height];
		memcpy(data, other.data, sizeof(float) * 4 * width * height);
		return *this;
	}

	QImage::~QImage()
	{
		delete[] data;
		data = nullptr;
	}

	imq::String QImage::toString() const
	{
		std::stringstream ss;
		ss << "QImage[" << width << "," << height << "]";
		return ss.str();
	}

	bool QImage::equals(const QObject* other) const
	{
		const QImage* image = objectCast<QImage>(other);
		if (image != nullptr)
		{
			if (width != image->width || height != image->height)
				return false;

			if (data == image->data)
				return true;

			QColor colorA;
			QColor colorB;
			for (int32_t y = 0; y < height; ++y)
			{
				for (int32_t x = 0; x < width; ++x)
				{
					if (!getPixel(x, y, &colorA) || !image->getPixel(x, y, &colorB))
						return false;

					if (colorA != colorB)
						return false;
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	int32_t QImage::getWidth() const
	{
		return width;
	}

	int32_t QImage::getHeight() const
	{
		return height;
	}

	float* QImage::getData() const
	{
		return data;
	}

	bool QImage::setPixel(int32_t x, int32_t y, const QColor& color)
	{
		if (x < 0 || y < 0 || x > width || y > height)
		{
			return false;
		}

		size_t idx = (size_t)(y * width + x) * 4;
		data[idx] = color.getRed();
		data[idx + 1] = color.getGreen();
		data[idx + 2] = color.getBlue();
		data[idx + 3] = color.getAlpha();
		return true;
	}

	bool QImage::getPixel(int32_t x, int32_t y, QColor* result) const
	{
		if (x < 0 || y < 0 || x > width || y > height)
		{
			return false;
		}

		size_t idx = (size_t)(y * width + x) * 4;
		result->setRed(data[idx]);
		result->setGreen(data[idx + 1]);
		result->setBlue(data[idx + 2]);
		result->setAlpha(data[idx + 3]);

		return true;
	}

	void QImage::clear(const QColor& color)
	{
		for (int32_t y = 0; y < height; ++y)
		{
			for (int32_t x = 0; x < width; ++x)
			{
				size_t idx = (size_t)(y * width + x) * 4;
				data[idx] = color.getRed();
				data[idx + 1] = color.getGreen();
				data[idx + 2] = color.getBlue();
				data[idx + 3] = color.getAlpha();
			}
		}
	}

	void QImage::clamp()
	{
		for (size_t idx = 0; idx < (size_t)(4 * width * height); ++idx)
		{
			data[idx] = utility::clamp(data[idx], 0.f, 1.f);
		}
	}

	imq::Result QImage::saveToFile(const char* filename)
	{
		// TODO: support for formats other than png
		unsigned char* out = new unsigned char[4 * width * height];
		for (size_t idx = 0; idx < (size_t)(4 * width * height); ++idx)
		{
			out[idx] = (unsigned char)(data[idx] * 255);
		}

		int res = stbi_write_png(filename, width, height, 4, out, 4 * width * sizeof(unsigned char));
		delete[] out;

		if (res == 0)
		{
			return errors::image_save_error(filename);
		}

		return true;
	}

	imq::Result QImage::getField(const String& name, QValue* result) const
	{
		if (name == "width" || name == "w")
		{
			*result = QValue::Integer(width);
			return true;
		}
		else if (name == "height" || name == "h")
		{
			*result = QValue::Integer(height);
			return true;
		}

		return errors::undefined_field(getTypeString(), name);
	}

	Result QImage::selection(ContextPtr context, const QValue& value, QSelection** result)
	{
		QObjectPtr obj;
		if (!value.getObject(&obj))
		{
			return errors::selection_create_error("expected QObject destination");
		}

		QImage* dest = objectCast<QImage>(obj.get());
		if (!dest)
		{
			return errors::selection_create_error("expected QImage destination");
		}

		if (width != dest->width || height != dest->height)
		{
			return errors::selection_create_error("destination dimensions do not match source dimensions");
		}

		*result = new QImageSelection(context, this, dest);
		return true;
	}

	QImageSelection::QImageSelection(ContextPtr parent, QImage* source, QImage* dest)
		: source(source), dest(dest), index(0)
	{
		context = std::shared_ptr<RestrictedSubContext>(new RestrictedSubContext(parent));
		color = std::shared_ptr<QColor>(new QColor());
		context->setRawValue("color", QValue::Object(color));
		updateContext();
	}

	QImageSelection::~QImageSelection()
	{
	}

	ContextPtr QImageSelection::getContext() const
	{
		return context;
	}

	bool QImageSelection::isValid() const
	{
		return index < source->width * source->height;
	}

	void QImageSelection::next()
	{
		++index;
		updateContext();
	}

	Result QImageSelection::apply(const QValue& value)
	{
		QObjectPtr obj;
		if (!value.getObject(&obj))
		{
			return errors::selection_apply_error("expected a QObject");
		}

		QColor* color = objectCast<QColor>(obj.get());
		if (!color)
		{
			return errors::selection_apply_error("expected a QColor");
		}

		size_t idx = index * 4;
		dest->data[idx] = color->getRed();
		dest->data[idx + 1] = color->getGreen();
		dest->data[idx + 2] = color->getBlue();
		dest->data[idx + 3] = color->getAlpha();

		return true;
	}

	void QImageSelection::updateContext()
	{
		if (index < source->width * source->height)
		{
			size_t idx = index * 4;
			color->setRed(source->data[idx]);
			color->setGreen(source->data[idx + 1]);
			color->setBlue(source->data[idx + 2]);
			color->setAlpha(source->data[idx + 3]);

			context->setRawValue("x", QValue::Integer(index % source->width));
			context->setRawValue("y", QValue::Integer(index / source->width));
		}
	}

}