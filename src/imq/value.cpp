#include "value.h"

#include <sstream>
#include <limits>
#include <cmath>

#include "object.h"
#include "errors.h"
#include "vm.h"

namespace imq
{

	QFunction::QFunction(VMachine* vm)
		: vm(vm)
	{
		if (vm != nullptr)
		{
			vm->getGC()->manage(this);
		}
	}

	QFunction::~QFunction()
	{
		if (vm != nullptr)
		{
			vm->getGC()->unmanage(this);
		}
	}

	QSimpleFunction::QSimpleFunction(VMachine* vm, QFunctionPtr func)
		: QFunction(vm), func(func)
	{
	}

	QSimpleFunction::~QSimpleFunction()
	{
	}

	Result QSimpleFunction::execute(VMachine* vm, int32_t argCount, QValue* args, QValue* result)
	{
		return func(vm, argCount, args, result);
	}

	QBoundFunction::QBoundFunction(VMachine* vm, QObject* obj, QFunctionPtr func)
		: QSimpleFunction(vm, func), obj(obj)
	{
	}

	QBoundFunction::~QBoundFunction()
	{
	}

	void QBoundFunction::GC_markChildren()
	{
		obj->GC_mark();
	}

	QValue QValue::Nil()
	{
		return QValue();
	}

	QValue QValue::Bool(bool val)
	{
		QValue result;
		result.valueType = Type::Bool;
		result.b = val;
		return result;
	}

	imq::QValue QValue::Integer(int32_t val)
	{
		QValue result;
		result.valueType = Type::Integer;
		result.i = val;
		return result;
	}

	QValue QValue::Float(float val)
	{
		QValue result;
		result.valueType = Type::Float;
		result.f = val;
		return result;
	}

	QValue QValue::Function(QFunction* val)
	{
		QValue result;
		result.valueType = Type::Function;
		result.func = val;
		return result;
	}

	QValue QValue::Function(VMachine* vm, QFunctionPtr val)
	{
		return QValue::Function(new QSimpleFunction(vm, val));
	}

	QValue QValue::Function(VMachine* vm, QObject* obj, QFunctionPtr val)
	{
		return QValue::Function(new QBoundFunction(vm, obj, val));
	}

	imq::QValue QValue::Object(QObject* val)
	{
		QValue result;
		result.valueType = Type::Object;
		result.obj = val;
		return result;
	}

	imq::String QValue::getTypeString(Type t)
	{
		switch (t)
		{
		default:
			return "<???>";

		case Type::Nil:
			return "Nil";

		case Type::Bool:
			return "Bool";

		case Type::Integer:
			return "Integer";

		case Type::Float:
			return "Float";

		case Type::Function:
			return "Function";

		case Type::Object:
			return "Object";
		}
	}

	QValue::QValue()
	{
		valueType = Type::Nil;
	}

	QValue::QValue(const QValue& other)
	{
		valueType = other.valueType;
		switch (valueType)
		{
		default:
			break;

		case Type::Bool:
			b = other.b;
			break;

		case Type::Integer:
			i = other.i;
			break;

		case Type::Float:
			f = other.f;
			break;

		case Type::Object:
			obj = other.obj;
			break;

		case Type::Function:
			func = other.func;
			break;
		}
	}

	QValue::~QValue()
	{
	}

	QValue::Type QValue::getType() const
	{
		return valueType;
	}

	imq::String QValue::toString() const
	{
		switch (valueType)
		{
		default:
			return "<?>";

		case Type::Nil:
			return "";
			
		case Type::Bool:
			return b ? "true" : "false";

		case Type::Integer:
		{
			std::stringstream ss;
			ss << i;
			return ss.str();
		}

		case Type::Float:
		{
			std::stringstream ss;
			ss << f;
			return ss.str();
		}

		case Type::Function:
			return "<QFunction>";

		case Type::Object:
			return obj->toString();
		}
	}

	bool QValue::isNil() const
	{
		return valueType == Type::Nil;
	}

	bool QValue::isBool() const
	{
		return valueType == Type::Bool;
	}

	bool QValue::isInteger() const
	{
		return valueType == Type::Integer;
	}

	bool QValue::isFloat() const
	{
		return valueType == Type::Float;
	}

	bool QValue::isFunction() const
	{
		return valueType == Type::Function;
	}

	bool QValue::isObject() const
	{
		return valueType == Type::Object;
	}

	bool QValue::getBool(bool* result) const
	{
		if (isBool())
		{
			*result = b;
			return true;
		}

		return false;
	}

	bool QValue::getInteger(int32_t* result) const
	{
		if (isInteger())
		{
			*result = i;
			return true;
		}

		return false;
	}

	bool QValue::getFloat(float* result) const
	{
		if (isFloat())
		{
			*result = f;
			return true;
		}

		return false;
	}

	bool QValue::getFunction(QFunction** result) const
	{
		if (isFunction())
		{
			*result = func;
			return true;
		}

		return false;
	}

	bool QValue::getObject(QObject** result) const
	{
		if (isObject())
		{
			*result = obj;
			return true;
		}

		return false;
	}

	bool QValue::toBool(QValue* result) const
	{
		switch (valueType)
		{
		default:
			return false;

		case Type::Bool:
			*result = QValue(*this);
			return true;

		case Type::Integer:
			*result = QValue::Bool(i != 0);
			return true;

		case Type::Float:
			*result = QValue::Bool(std::abs(f) >= std::numeric_limits<float>::epsilon());
			return true;
		}
	}

	bool QValue::toInteger(QValue* result) const
	{
		switch (valueType)
		{
		default:
			return false;

		case Type::Bool:
			*result = QValue::Integer(b ? 1 : 0);
			return true;

		case Type::Integer:
			*result = QValue(*this);
			return true;

		case Type::Float:
			*result = QValue::Integer((int32_t)f);
			return true;
		}
	}

	bool QValue::toFloat(QValue* result) const
	{
		switch (valueType)
		{
		default:
			return false;

		case Type::Bool:
			*result = QValue::Float(b ? 1.f : 0.f);
			return true;

		case Type::Integer:
			*result = QValue::Float((float)i);
			return true;

		case Type::Float:
			*result = QValue(*this);
			return true;
		}
	}

	imq::Result QValue::opAdd(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "+");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "+");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "+");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "+");

			case Type::Integer:
				*result = QValue::Integer(i + rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Float(i + rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "+");

			case Type::Object:
				return rhs.obj->opAdd(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "+");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "+");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "+");

			case Type::Integer:
				*result = QValue::Float(f + rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Float(f + rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "+");

			case Type::Object:
				return rhs.obj->opAdd(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "+");

		case Type::Function:
			return errors::math_operator_invalid("Function", "+");

		case Type::Object:
			return obj->opAdd(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "+");
	}

	imq::Result QValue::opSub(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "-");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "-");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "-");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "-");

			case Type::Integer:
				*result = QValue::Integer(i - rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Float(i - rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "-");

			case Type::Object:
				return rhs.obj->opSub(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "-");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "-");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "-");

			case Type::Integer:
				*result = QValue::Float(f - rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Float(f - rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "-");

			case Type::Object:
				return rhs.obj->opSub(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "-");

		case Type::Function:
			return errors::math_operator_invalid("Function", "-");

		case Type::Object:
			return obj->opSub(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "-");
	}

	imq::Result QValue::opMul(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "*");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "*");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "*");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "*");

			case Type::Integer:
				*result = QValue::Integer(i * rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Float(i * rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "*");

			case Type::Object:
				return rhs.obj->opMul(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "*");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "*");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "*");

			case Type::Integer:
				*result = QValue::Float(f * rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Float(f * rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "*");

			case Type::Object:
				return rhs.obj->opMul(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "*");

		case Type::Function:
			return errors::math_operator_invalid("Function", "*");

		case Type::Object:
			return obj->opMul(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "*");
	}

	imq::Result QValue::opDiv(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "/");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "/");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "/");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "/");

			case Type::Integer:
				if (rhs.i == 0)
					return errors::math_divide_by_zero();

				*result = QValue::Integer(i / rhs.i);
				return true;

			case Type::Float:
				if (rhs.f == 0.f)
					return errors::math_divide_by_zero();

				*result = QValue::Float(i / rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "/");

			case Type::Object:
				return rhs.obj->opDiv(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "/");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "/");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "/");

			case Type::Integer:
				if (rhs.i == 0)
					return errors::math_divide_by_zero();

				*result = QValue::Float(f / rhs.i);
				return true;

			case Type::Float:
				if (rhs.f == 0.f)
					return errors::math_divide_by_zero();

				*result = QValue::Float(f / rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "/");

			case Type::Object:
				return rhs.obj->opDiv(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "/");

		case Type::Function:
			return errors::math_operator_invalid("Function", "/");

		case Type::Object:
			return obj->opDiv(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "/");
	}

	imq::Result QValue::opMod(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "%");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "%");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "%");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "%");

			case Type::Integer:
				if (rhs.i == 0)
					return errors::math_mod_by_zero();

				*result = QValue::Integer(i % rhs.i);
				return true;

			case Type::Float:
				if (rhs.f == 0.f)
					return errors::math_mod_by_zero();
				*result = QValue::Float(std::fmod((float) i, rhs.f));
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "%");

			case Type::Object:
				return rhs.obj->opMod(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "%");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "%");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "%");

			case Type::Integer:
				if (rhs.i == 0)
					return errors::math_mod_by_zero();

				*result = QValue::Float(std::fmod(f, (float)rhs.i));
				return true;

			case Type::Float:
				if (rhs.f == 0.f)
					return errors::math_mod_by_zero();

				*result = QValue::Float(std::fmod(f, rhs.f));
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "%");

			case Type::Object:
				return rhs.obj->opMod(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "%");

		case Type::Function:
			return errors::math_operator_invalid("Function", "%");

		case Type::Object:
			return obj->opMod(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "%");
	}

	imq::Result QValue::opNegate(QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "-");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "-");

		case Type::Integer:
			*result = QValue::Integer(-i);
			return true;

		case Type::Float:
			*result = QValue::Float(-f);
			return true;

		case Type::Function:
			return errors::math_operator_invalid("Function", "-");

		case Type::Object:
			return obj->opNegate(result);
		}

		return errors::math_operator_invalid("<???>", "-");
	}

	imq::Result QValue::opNot(QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "not");

		case Type::Bool:
			*result = QValue::Bool(!b);
			return true;

		case Type::Integer:
			return errors::math_operator_invalid("Integer", "not");

		case Type::Float:
			return errors::math_operator_invalid("Float", "not");

		case Type::Function:
			return errors::math_operator_invalid("Function", "not");

		case Type::Object:
			return obj->opNot(result);
		}

		return errors::math_operator_invalid("<???>", "!");
	}

	imq::Result QValue::opAnd(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "and");

		case Type::Bool:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "and");

			case Type::Bool:
				*result = QValue::Bool(b && rhs.b);
				return true;

			case Type::Integer:
				return errors::math_operator_invalid("Integer", "and");

			case Type::Float:
				return errors::math_operator_invalid("Float", "and");

			case Type::Function:
				return errors::math_operator_invalid("Function", "and");

			case Type::Object:
				return rhs.obj->opAnd(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "and");

		case Type::Integer:
			return errors::math_operator_invalid("Integer", "and");

		case Type::Float:
			return errors::math_operator_invalid("Float", "and");

		case Type::Function:
			return errors::math_operator_invalid("Function", "and");

		case Type::Object:
			return obj->opAnd(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "and");
	}

	imq::Result QValue::opOr(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "or");

		case Type::Bool:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "or");

			case Type::Bool:
				*result = QValue::Bool(b || rhs.b);
				return true;

			case Type::Integer:
				return errors::math_operator_invalid("Integer", "or");

			case Type::Float:
				return errors::math_operator_invalid("Float", "or");

			case Type::Function:
				return errors::math_operator_invalid("Function", "or");

			case Type::Object:
				return rhs.obj->opOr(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "or");

		case Type::Integer:
			return errors::math_operator_invalid("Integer", "or");

		case Type::Float:
			return errors::math_operator_invalid("Float", "or");

		case Type::Function:
			return errors::math_operator_invalid("Function", "or");

		case Type::Object:
			return obj->opOr(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "or");
	}

	Result QValue::opLess(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "less");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "less");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "less");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "less");

			case Type::Integer:
				*result = QValue::Bool(i < rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(i < rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "less");

			case Type::Object:
				return rhs.obj->opLess(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "less");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "less");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "less");

			case Type::Integer:
				*result = QValue::Bool(f < rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(f < rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "less");

			case Type::Object:
				return rhs.obj->opLess(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "less");

		case Type::Function:
			return errors::math_operator_invalid("Function", "less");

		case Type::Object:
			return obj->opLess(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "less");
	}

	Result QValue::opLessEq(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "lesseq");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "lesseq");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "lesseq");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "lesseq");

			case Type::Integer:
				*result = QValue::Bool(i <= rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(i <= rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "lesseq");

			case Type::Object:
				return rhs.obj->opLessEq(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "lesseq");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "lesseq");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "lesseq");

			case Type::Integer:
				*result = QValue::Bool(f <= rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(f <= rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "lesseq");

			case Type::Object:
				return rhs.obj->opLessEq(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "lesseq");

		case Type::Function:
			return errors::math_operator_invalid("Function", "lesseq");

		case Type::Object:
			return obj->opLessEq(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "lesseq");
	}

	Result QValue::opGreater(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "greater");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "greater");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "greater");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "greater");

			case Type::Integer:
				*result = QValue::Bool(i > rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(i > rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "greater");

			case Type::Object:
				return rhs.obj->opGreater(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "greater");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "greater");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "greater");

			case Type::Integer:
				*result = QValue::Bool(f > rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(f > rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "greater");

			case Type::Object:
				return rhs.obj->opGreater(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "greater");

		case Type::Function:
			return errors::math_operator_invalid("Function", "greater");

		case Type::Object:
			return obj->opGreater(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "greater");
	}

	Result QValue::opGreaterEq(const QValue& rhs, QValue* result) const
	{
		switch (valueType)
		{
		case Type::Nil:
			return errors::math_operator_invalid("Nil", "greatereq");

		case Type::Bool:
			return errors::math_operator_invalid("Bool", "greatereq");

		case Type::Integer:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "greatereq");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "greatereq");

			case Type::Integer:
				*result = QValue::Bool(i >= rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(i >= rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "greatereq");

			case Type::Object:
				return rhs.obj->opGreaterEq(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "greatereq");

		case Type::Float:
			switch (rhs.valueType)
			{
			case Type::Nil:
				return errors::math_operator_invalid("Nil", "greatereq");

			case Type::Bool:
				return errors::math_operator_invalid("Bool", "greatereq");

			case Type::Integer:
				*result = QValue::Bool(f >= rhs.i);
				return true;

			case Type::Float:
				*result = QValue::Bool(f >= rhs.f);
				return true;

			case Type::Function:
				return errors::math_operator_invalid("Function", "greatereq");

			case Type::Object:
				return rhs.obj->opGreaterEq(OperationOrder::RHS, *this, result);
			}
			return errors::math_operator_invalid("<???>", "greatereq");

		case Type::Function:
			return errors::math_operator_invalid("Function", "greatereq");

		case Type::Object:
			return obj->opGreaterEq(OperationOrder::LHS, rhs, result);
		}

		return errors::math_operator_invalid("<???>", "greatereq");
	}

	void QValue::GC_mark()
	{
		switch (valueType)
		{
		case Type::Object:
			obj->GC_mark();
			break;

		case Type::Function:
			func->GC_mark();
			break;
		}
	}

	QValue& QValue::operator=(const QValue& other)
	{
		valueType = other.valueType;
		switch (valueType)
		{
		default:
			break;

		case Type::Bool:
			b = other.b;
			break;

		case Type::Integer:
			i = other.i;
			break;

		case Type::Float:
			f = other.f;
			break;

		case Type::Object:
			obj = other.obj;
			break;

		case Type::Function:
			func = other.func;
			break;
		}

		return *this;
	}

	bool operator==(const QValue& a, const QValue& b)
	{
		if (a.valueType != b.valueType)
			return false;

		switch (a.valueType)
		{
		default:
			return false;

		case QValue::Type::Nil:
			return true;

		case QValue::Type::Bool:
			return a.b == b.b;

		case QValue::Type::Integer:
			return a.i == b.i;

		case QValue::Type::Float:
			return a.f == b.f;

		case QValue::Type::Function:
			return a.func == b.func;

		case QValue::Type::Object:
			return a.obj->equals(b.obj);
		}
	}

	bool operator!=(const QValue& a, const QValue& b)
	{
		return !(a == b);
	}
}