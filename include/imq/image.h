#pragma once

#include "platform.h"
#include "value.h"
#include "object.h"
#include "gc.h"

namespace imq
{
	class VMachine;

	class QColor : public QObject
	{
		IMQ_DECLARE_TYPE(QColor);

	public:
		QColor(VMachine* vm);
		QColor(VMachine* vm, float r, float g, float b, float a = 1.f);
		QColor(const QColor& other);

		QColor& operator=(const QColor& other);

		virtual ~QColor();

		void initializeObject();

		virtual String toString() const override;
		
		virtual bool equals(const QObject* other) const override;

		virtual std::size_t getHash() const override;

		virtual Result copyObject(QValue* result) const override;

		bool operator==(const QColor& other) const;
		bool operator!=(const QColor& other) const;

		float getRed() const;
		float getGreen() const;
		float getBlue() const;
		float getAlpha() const;

		void setRed(float val);
		void setGreen(float val);
		void setBlue(float val);
		void setAlpha(float val);

		QColor clamp() const;

		virtual Result getField(const String& name, QValue* result) override;
		virtual Result setField(const String& name, const QValue& value) override;

		virtual Result getIndex(const QValue& index, QValue* result) override;
		virtual Result setIndex(const QValue& index, const QValue& value) override;

		virtual Result opAdd(OperationOrder order, const QValue& other, QValue* result) const override;
		virtual Result opSub(OperationOrder order, const QValue& other, QValue* result) const override;
		virtual Result opMul(OperationOrder order, const QValue& other, QValue* result) const override;
		virtual Result opDiv(OperationOrder order, const QValue& other, QValue* result) const override;
		virtual Result opMod(OperationOrder order, const QValue& other, QValue* result) const override;
		virtual Result opNegate(QValue* result) const override;

	private:
		ObjectFieldHelper fields;

		float red;
		float green;
		float blue;
		float alpha;
	};

	class QImage : public QObject
	{
		IMQ_DECLARE_TYPE(QImage);

	public:
		friend class QImageSelection;

		static Result loadFromFile(VMachine* vm, const char* filename, QImage** result);

		QImage(VMachine* vm);
		QImage(VMachine* vm, int32_t width, int32_t height);
		QImage(VMachine* vm, int32_t width, int32_t height, const QColor& color);
		QImage(const QImage& other);
		virtual ~QImage();

		void initializeObject();

		QImage& operator=(const QImage& other);

		virtual String toString() const override;

		// warning - slow operation. This is a pixel-by-pixel equivalence check.
		virtual bool equals(const QObject* other) const override;

		virtual Result copyObject(QValue* result) const override;

		int32_t getWidth() const;
		int32_t getHeight() const;

		float* getData() const;

		bool getPixel(int32_t x, int32_t y, QColor* result) const;
		bool setPixel(int32_t x, int32_t y, const QColor& color);

		void clear(const QColor& color);

		void clamp();

		Result saveToFile(const char* filename);

		virtual Result getField(const String& name, QValue* result) override;

		virtual Result selection(ContextPtr context, const QValue& value, QSelection** result) override;

	private:
		ObjectFieldHelper fields;

		int32_t width;
		int32_t height;
		float* data = nullptr;
	};

	class QImageSelection : public QSelection
	{
	public:
		QImageSelection(ContextPtr parent, QImage* source, QImage* dest);
		virtual ~QImageSelection();

		virtual ContextPtr getContext() const override;
		virtual bool isValid() const override;
		virtual void next() override;
		virtual Result apply(const QValue& value, int32_t coordCount, QValue* coords) override;

	private:
		void updateContext();

		QImage* source;
		QImage* dest;
		QColor* color;
		int32_t index;
		RestrictedSubContext* context;
	};
}