#include "image.h"

#include <string>
#include <cstring>
#include <cmath>

#include "thirdparty/stb_image.h"
#include "thirdparty/stb_image_write.h"
#include "cast.h"
#include "utility.h"
#include "errors.h"
#include "hash.h"
#include "vm.h"

namespace imq
{
	// QColor

	IMQ_DEFINE_TYPE_WITH_SIZE_FIELDS(QColor, fields);

	QColor::QColor(VMachine* vm)
		: QObject(vm),
		red(0.f), green(0.f), blue(0.f), alpha(1.f)
	{
		initializeObject();
	}

	QColor::QColor(VMachine* vm, float r, float g, float b, float a)
		: QObject(vm),
		red(r), green(g), blue(b), alpha(a)
	{
		initializeObject();
	}


	QColor::QColor(const QColor& other)
		: QObject(other.getVM())
	{
		this->red = other.red;
		this->green = other.green;
		this->blue = other.blue;
		this->alpha = other.alpha;

		initializeObject();
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

	void QColor::initializeObject()
	{
		fields.getter("red", [&](QValue* result) { *result = QValue::Float(red); return true; });
		fields.getter("r", [&](QValue* result) { *result = QValue::Float(red); return true; });

		fields.getter("green", [&](QValue* result) { *result = QValue::Float(green); return true; });
		fields.getter("g", [&](QValue* result) { *result = QValue::Float(green); return true; });

		fields.getter("blue", [&](QValue* result) { *result = QValue::Float(blue); return true; });
		fields.getter("b", [&](QValue* result) { *result = QValue::Float(blue); return true; });

		fields.getter("alpha", [&](QValue* result) { *result = QValue::Float(alpha); return true; });
		fields.getter("a", [&](QValue* result) { *result = QValue::Float(alpha); return true; });

		fields.getter("clamp", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
				{
					return errors::args_count("QColor.clamp", 0, argCount);
				}

				*result = QValue::Object(new QColor(this->clamp()));
				return true;
			});
			return true;
		});

		fields.getter("each", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
				{
					return errors::args_count("QColor.each", 1, argCount);
				}

				QFunction* func;
				if (!args[0].getFunction(&func))
				{
					return errors::args_type("QColor.each", 0, "QFunction", args[0]);
				}

				float r;
				float g;
				float b;
				float a;

				QValue* funcArgs = new QValue[1]{ QValue::Float(red) };
				QValue value;

				Result res = func->execute(vm, 1, funcArgs, &value);
				if (!res)
				{
					delete[] funcArgs;
					return res;
				}

				if (!value.getFloat(&r))
				{
					delete[] funcArgs;
					return errors::return_type("Float", value);
				}

				value = QValue::Nil();
				funcArgs[0] = QValue::Float(green);
				res = func->execute(vm, 1, funcArgs, &value);
				if (!res)
				{
					delete[] funcArgs;
					return res;
				}

				if (!value.getFloat(&g))
				{
					delete[] funcArgs;
					return errors::return_type("Float", value);
				}

				value = QValue::Nil();
				funcArgs[0] = QValue::Float(blue);
				res = func->execute(vm, 1, funcArgs, &value);
				if (!res)
				{
					delete[] funcArgs;
					return res;
				}

				if (!value.getFloat(&b))
				{
					delete[] funcArgs;
					return errors::return_type("Float", value);
				}

				value = QValue::Nil();
				funcArgs[0] = QValue::Float(alpha);
				res = func->execute(vm, 1, funcArgs, &value);
				if (!res)
				{
					delete[] funcArgs;
					return res;
				}

				if (!value.getFloat(&a))
				{
					delete[] funcArgs;
					return errors::return_type("Float", value);
				}

				delete[] funcArgs;

				*result = QValue::Object(new QColor(getVM(), r, g, b, a));
				return true;
			});
			return true;
		});
	}

	String QColor::toString() const
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

	std::size_t QColor::getHash() const
	{
		std::size_t seed = 0;
		hash_combine(seed, red);
		hash_combine(seed, green);
		hash_combine(seed, blue);
		hash_combine(seed, alpha);

		return seed;
	}

	Result QColor::copyObject(QValue* result) const
	{
		*result = QValue::Object(new QColor(*this));
		return true;
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

	QColor QColor::clamp() const
	{
		return QColor(
			getVM(),
			utility::clamp(red, 0.f, 1.f),
			utility::clamp(green, 0.f, 1.f),
			utility::clamp(blue, 0.f, 1.f),
			utility::clamp(alpha, 0.f, 1.f)
		);
	}

	Result QColor::getField(const String& name, QValue* result)
	{
		return fields.handleGet(this, name, result);
	}

	Result QColor::setField(const String& name, const QValue& value)
	{
		return errors::immutable_obj(getTypeString());
	}

	Result QColor::getIndex(const QValue& index, QValue* result)
	{
		int32_t idx;
		if (!index.getInteger(&idx))
			return errors::invalid_index_type(getTypeString(), index);

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
		return errors::immutable_obj(getTypeString());
	}

	Result QColor::opAdd(OperationOrder order, const QValue& other, QValue* result) const
	{
		switch (other.getType())
		{
		default:
			return errors::math_operator_obj_invalid("+", getTypeString(), other);

		case QValue::Type::Integer:
		{
			int32_t i;
			other.getInteger(&i);
			*result = QValue::Object(new QColor(getVM(), red + i, green + i, blue + i, alpha + i));
			return true;
		}

		case QValue::Type::Float:
		{
			float f;
			other.getFloat(&f);
			*result = QValue::Object(new QColor(getVM(), red + f, green + f, blue + f, alpha + f));
			return true;
		}

		case QValue::Type::Object:
		{
			QObject* obj;
			other.getObject(&obj);
			QColor* col = objectCast<QColor>(obj);
			if (!col)
				return errors::math_operator_obj_invalid("+", getTypeString(), obj->getTypeString());

			*result = QValue::Object(new QColor(getVM(), red + col->red, green + col->green, blue + col->blue, alpha + col->alpha));
			return true;
		}
		}
	}

	Result QColor::opSub(OperationOrder order, const QValue& other, QValue* result) const
	{
		QColor* res = nullptr;
		switch (other.getType())
		{
		default:
			return errors::math_operator_obj_invalid("-", getTypeString(), other);

		case QValue::Type::Integer:
		{
			int32_t i;
			other.getInteger(&i);
			res = new QColor(getVM(), red - i, green - i, blue - i, alpha - i);
			break;
		}

		case QValue::Type::Float:
		{
			float f;
			other.getFloat(&f);
			res = new QColor(getVM(), red - f, green - f, blue - f, alpha - f);
			break;
		}

		case QValue::Type::Object:
		{
			QObject* obj;
			other.getObject(&obj);
			QColor* col = objectCast<QColor>(obj);
			if (!col)
				return errors::math_operator_obj_invalid("-", getTypeString(), obj->getTypeString());

			res = new QColor(getVM(), red - col->red, green - col->green, blue - col->blue, alpha - col->alpha);
			break;
		}
		}

		if (order == OperationOrder::RHS)
		{
			res->red *= -1;
			res->green *= -1;
			res->blue *= -1;
			res->alpha *= -1;
		}

		*result = QValue::Object(res);
		return true;
	}

	Result QColor::opMul(OperationOrder order, const QValue& other, QValue* result) const
	{
		switch (other.getType())
		{
		default:
			return errors::math_operator_obj_invalid("*", getTypeString(), other);

		case QValue::Type::Integer:
		{
			int32_t i;
			other.getInteger(&i);
			*result = QValue::Object(new QColor(getVM(), red * i, green * i, blue * i, alpha * i));
			return true;
		}

		case QValue::Type::Float:
		{
			float f;
			other.getFloat(&f);
			*result = QValue::Object(new QColor(getVM(), red * f, green * f, blue * f, alpha * f));
			return true;
		}

		case QValue::Type::Object:
		{
			QObject* obj;
			other.getObject(&obj);
			QColor* col = objectCast<QColor>(obj);
			if (!col)
				return errors::math_operator_obj_invalid("/", getTypeString(), obj->getTypeString());

			*result = QValue::Object(new QColor(getVM(), red * col->red, green * col->green, blue * col->blue, alpha * col->alpha));
			return true;
		}
		}
	}

	Result QColor::opDiv(OperationOrder order, const QValue& other, QValue* result) const
	{
		switch (other.getType())
		{
		default:
			return errors::math_operator_obj_invalid("/", getTypeString(), other);

		case QValue::Type::Integer:
		{
			int32_t i;
			other.getInteger(&i);
			if (order == OperationOrder::LHS)
			{
				if (i == 0)
					return errors::math_divide_by_zero();

				*result = QValue::Object(new QColor(getVM(), red / i, green / i, blue / i, alpha / i));
			}
			else
			{
				if (red == 0.f || green == 0.f || blue == 0.f || alpha == 0.f)
					return errors::math_divide_by_zero();

				*result = QValue::Object(new QColor(getVM(), i / red, i / green, i / blue, i / alpha));
			}
			return true;
		}

		case QValue::Type::Float:
		{
			float f;
			other.getFloat(&f);
			if (order == OperationOrder::LHS)
			{
				if (f == 0.f)
					return errors::math_divide_by_zero();

				*result = QValue::Object(new QColor(getVM(), red / f, green / f, blue / f, alpha / f));
			}
			else
			{
				if (red == 0.f || green == 0.f || blue == 0.f || alpha == 0.f)
					return errors::math_divide_by_zero();

				*result = QValue::Object(new QColor(getVM(), f / red, f / green, f / blue, f / alpha));
			}
			return true;
		}

		case QValue::Type::Object:
		{
			QObject* obj;
			other.getObject(&obj);
			QColor* col = objectCast<QColor>(obj);
			if (!col)
				return errors::math_operator_obj_invalid("/", getTypeString(), obj->getTypeString());

			if (order == OperationOrder::LHS)
			{
				if (col->red == 0.f || col->green == 0.f || col->blue == 0.f || col->alpha == 0.f)
					return errors::math_divide_by_zero();

				*result = QValue::Object(new QColor(getVM(), red / col->red, green / col->green, blue / col->blue, alpha / col->alpha));
			}
			else
			{
				if (red == 0.f || green == 0.f || blue == 0.f || alpha == 0.f)
					return errors::math_divide_by_zero();

				*result = QValue::Object(new QColor(getVM(), col->red / red, col->green / green, col->blue / blue, col->alpha / alpha));
			}
			return true;
		}
		}
	}

	Result QColor::opMod(OperationOrder order, const QValue& other, QValue* result) const
	{
		switch (other.getType())
		{
		default:
			return errors::math_operator_obj_invalid("%", getTypeString(), other);

		case QValue::Type::Integer:
		{
			int32_t i;
			other.getInteger(&i);
			if (order == OperationOrder::LHS)
			{
				if (i == 0)
					return errors::math_mod_by_zero();

				*result = QValue::Object(new QColor(getVM(), (float)std::fmod<float>(red, i), (float)std::fmod<float>(green, i), (float)std::fmod<float>(blue, i), (float)std::fmod<float>(alpha, i)));
			}
			else
			{
				if (red == 0.f || green == 0.f || blue == 0.f || alpha == 0.f)
					return errors::math_mod_by_zero();

				*result = QValue::Object(new QColor(getVM(), std::fmod<float>((float)i, red), std::fmod<float>((float)i, green), std::fmod<float>((float)i, blue), std::fmod<float>((float)i, alpha)));
			}
			return true;
		}

		case QValue::Type::Float:
		{
			float f;
			other.getFloat(&f);
			if (order == OperationOrder::LHS)
			{
				if (f == 0.f)
					return errors::math_mod_by_zero();

				*result = QValue::Object(new QColor(getVM(), std::fmod(red, f), std::fmod(green, f), std::fmod(blue, f), std::fmod(alpha, f)));
			}
			else
			{
				if (red == 0.f || green == 0.f || blue == 0.f || alpha == 0.f)
					return errors::math_mod_by_zero();

				*result = QValue::Object(new QColor(getVM(), std::fmod(f, red), std::fmod(f, green), std::fmod(f, blue), std::fmod(f, alpha)));
			}
			return true;
		}

		case QValue::Type::Object:
		{
			QObject* obj;
			other.getObject(&obj);
			QColor* col = objectCast<QColor>(obj);
			if (!col)
				return errors::math_operator_obj_invalid("%", getTypeString(), obj->getTypeString());

			if (order == OperationOrder::LHS)
			{
				if (col->red == 0.f || col->green == 0.f || col->blue == 0.f || col->alpha == 0.f)
					return errors::math_mod_by_zero();

				*result = QValue::Object(new QColor(getVM(), std::fmod(red, col->red), std::fmod(green, col->green), std::fmod(blue, col->blue), std::fmod(alpha, col->alpha)));
			}
			else
			{
				if (red == 0.f || green == 0.f || blue == 0.f || alpha == 0.f)
					return errors::math_mod_by_zero();

				*result = QValue::Object(new QColor(getVM(), std::fmod(col->red, red), std::fmod(col->green, green), std::fmod(col->blue, blue), std::fmod(col->alpha, alpha)));
			}
			return true;
		}
		}
	}

	Result QColor::opNegate(QValue* result) const
	{
		*result = QValue::Object(new QColor(getVM(), -red, -green, -blue, -alpha));
		return true;
	}

	// QImage

	IMQ_DEFINE_TYPE_WITH_SIZE_FIELDS_CUSTOM(QImage, fields, ((size_t) width * height * sizeof(float) * 4));

	Result QImage::loadFromFile(VMachine* vm, const char* filename, QImage** result)
	{
		int width;
		int height;
		int comp;
		String path = vm->buildPath(filename);
		unsigned char* data = stbi_load(path.data(), &width, &height, &comp, 4);
		if (data == nullptr)
		{
			return errors::image_load_error(stbi_failure_reason());
		}

		*result = new QImage(vm, width, height);
		for (size_t idx = 0; idx < (size_t)(4 * width * height); ++idx)
		{
			(*result)->data[idx] = (float)(data[idx] / 255.f);
		}

		stbi_image_free(data);

		return true;
	}

	QImage::QImage(VMachine* vm)
		: QObject(vm)
	{
		width = 0;
		height = 0;
		data = nullptr;

		initializeObject();
	}

	QImage::QImage(VMachine* vm, int32_t width, int32_t height)
		: QImage(vm, width, height, QColor(vm, 0.f, 0.f, 0.f))
	{
	}

	QImage::QImage(VMachine* vm, int32_t width, int32_t height, const QColor& color)
		: QObject(vm)
	{
		this->width = width;
		this->height = height;
		data = new float[4 * width * height];
		clear(color);

		initializeObject();
	}

	QImage::QImage(const QImage& other)
		: QObject(other.getVM())
	{
		this->width = other.width;
		this->height = other.height;
		data = new float[4 * width * height];
		memcpy(data, other.data, sizeof(float) * 4 * width * height);

		initializeObject();
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

	void QImage::initializeObject()
	{
		fields.getter("width", [&](QValue* result) { *result = QValue::Integer(width); return true; });
		fields.getter("w", [&](QValue* result) { *result = QValue::Integer(width); return true; });

		fields.getter("height", [&](QValue* result) { *result = QValue::Integer(height); return true; });
		fields.getter("h", [&](QValue* result) { *result = QValue::Integer(height); return true; });

		fields.getter("pixel", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 2 && argCount != 3)
					return errors::args_count("pixel", 2, 3, argCount);

				int32_t x;
				int32_t y;

				if (!args[0].getInteger(&x))
					return errors::args_type("pixel", 0, "Integer", args[0]);

				if (!args[1].getInteger(&y))
					return errors::args_type("pixel", 1, "Integer", args[1]);

				if (argCount == 2)
				{
					QColor col(getVM());
					bool res = getPixel(x, y, &col);
					if (!res)
						return errors::func_generic_error("Unable to get pixel");

					*result = QValue::Object(new QColor(col));
					return true;
				}
				else
				{
					QObject* obj;
					if (!args[2].getObject(&obj))
						return errors::args_type("pixel", 2, "Object", args[2]);

					QColor* col = objectCast<QColor>(obj);
					if (!col)
						return errors::args_type("pixel", 2, "Color", args[2]);

					bool res = setPixel(x, y, *col);
					if (!res)
						return errors::func_generic_error("Unable to set pixel");

					*result = QValue::Nil();
					return true;
				}
			});
			return true;
		});

		fields.getter("clamp", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 0)
					return errors::args_count("clamp", 0, argCount);

				clamp();

				*result = QValue::Nil();
				return true;
			});
			return true;
		});

		fields.getter("save", [&](QValue* result) {
			*result = QValue::Function(getVM(), this, [&](VMachine* vm, int32_t argCount, QValue* args, QValue* result) -> Result {
				if (argCount != 1)
					return errors::args_count("save", 1, argCount);

				char* path;

				if (!args[0].getString(&path))
				{
					return errors::args_type("save", 0, "String", args[0]);
				}

				Result res = this->saveToFile(path);
				if (!res)
					return res;

				return true;
			});
			return true;
		});
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

			QColor colorA(getVM());
			QColor colorB(getVM());
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

	Result QImage::copyObject(QValue* result) const
	{
		*result = QValue::Object(new QImage(*this));
		return true;
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
		if (x < 0 || y < 0 || x >= width || y >= height)
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
		if (x < 0 || y < 0 || x >= width || y >= height)
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

		String path = getVM()->buildPath(filename);
		int res = stbi_write_png(path.data(), width, height, 4, out, 4 * width * sizeof(unsigned char));
		delete[] out;

		if (res == 0)
		{
			return errors::image_save_error(filename);
		}

		return true;
	}

	imq::Result QImage::getField(const String& name, QValue* result)
	{
		return fields.handleGet(this, name, result);
	}

	Result QImage::selection(Context* context, const QValue& value, QSelection** result)
	{
		QObject* obj;
		if (!value.getObject(&obj))
		{
			return errors::selection_create_error("expected QObject destination");
		}

		QImage* dest = objectCast<QImage>(obj);
		if (!dest)
		{
			return errors::selection_create_error("expected QImage destination");
		}

		*result = new QImageSelection(context, this, dest);
		return true;
	}

	QImageSelection::QImageSelection(Context* parent, QImage* source, QImage* dest)
		: source(source), dest(dest), xCoord(0), yCoord(0)
	{
		context = new RestrictedSubContext(parent->getVM(), parent);
		context->setBreakable(true);
		color = new QColor(parent->getVM());
		context->setRawValue("color", QValue::Object(color));

		auto gc = parent->getVM()->getGC();
		gc->manage(context);
		gc->addRoot(context);

		updateContext();
	}

	QImageSelection::~QImageSelection()
	{
		auto gc = context->getVM()->getGC();
		gc->removeRoot(context);
	}

	Context* QImageSelection::getContext() const
	{
		return context;
	}

	bool QImageSelection::isValid() const
	{
		return xCoord >= 0 && xCoord < source->width && yCoord >= 0 && yCoord < source->height;
	}

	void QImageSelection::next()
	{
		++xCoord;
		if (xCoord == source->width)
		{
			xCoord = 0;
			++yCoord;
		}

		updateContext();
	}

	Result QImageSelection::apply(const QValue& value, int32_t coordCount, QValue* coords)
	{
		QObject* obj;
		if (!value.getObject(&obj))
		{
			return errors::selection_apply_error("expected a QObject");
		}

		QColor* color = objectCast<QColor>(obj);
		if (!color)
		{
			return errors::selection_apply_error("expected a QColor");
		}

		int32_t xOut = xCoord;
		int32_t yOut = yCoord;
		switch (coordCount)
		{
		default:
			return errors::selection_apply_error("expected 0 or 2 coordinate rewrites");

		case 0:
			break;

		case 2:
		{
			if (!coords[0].getInteger(&xOut))
				return errors::selection_apply_error("x coordinate must be an Integer");
			if (!coords[1].getInteger(&yOut))
				return errors::selection_apply_error("y coordinate must be an Integer");
			break;
		}
		}

		if (dest->width == 0 || dest->height == 0)
			return errors::selection_apply_error("width or height of destination image is 0");

		if (xOut < 0 || xOut >= dest->width)
			return errors::selection_apply_error("x coordinate is out of range at " + std::to_string(xOut));
		if (yOut < 0 || yOut >= dest->height)
			return errors::selection_apply_error("y coordinate is out of range at " + std::to_string(yOut));

		size_t idx = (yOut * dest->width + xOut) * 4;
		dest->data[idx] = color->getRed();
		dest->data[idx + 1] = color->getGreen();
		dest->data[idx + 2] = color->getBlue();
		dest->data[idx + 3] = color->getAlpha();

		return true;
	}

	void QImageSelection::updateContext()
	{
		if (isValid())
		{
			size_t idx = (yCoord * source->width + xCoord) * 4;
			color->setRed(source->data[idx]);
			color->setGreen(source->data[idx + 1]);
			color->setBlue(source->data[idx + 2]);
			color->setAlpha(source->data[idx + 3]);

			context->setRawValue("x", QValue::Integer(xCoord));
			context->setRawValue("y", QValue::Integer(yCoord));
		}
	}
}