#pragma once

#include "platform.h"
#include "value.h"

namespace imq
{
	class QColor : public QObject
	{
		IMQ_DECLARE_TYPE(QColor);

	public:
		QColor();
		QColor(float r, float g, float b, float a = 1.f);
		QColor(const QColor& other);

		QColor& operator=(const QColor& other);

		virtual ~QColor();

		virtual String toString() const override;
		
		virtual bool equals(const QObject* other) const override;

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

		virtual Result getField(const String& name, QValue* result) const override;
		virtual Result setField(const String& name, const QValue& value) override;

		virtual Result getIndex(const QValue& index, QValue* result) const override;
		virtual Result setIndex(const QValue& index, const QValue& value) override;

	private:
		float red;
		float green;
		float blue;
		float alpha;
	};

	class QImage : public QObject
	{
		IMQ_DECLARE_TYPE(QImage);

	public:
		static Result loadFromFile(const char* filename, QImage* result);

		QImage();
		QImage(int32_t width, int32_t height);
		QImage(int32_t width, int32_t height, const QColor& color);
		QImage(const QImage& other);

		QImage& operator=(const QImage& other);

		virtual ~QImage();

		virtual String toString() const override;

		// warning - slow operation. This is a pixel-by-pixel equivalence check.
		virtual bool equals(const QObject* other) const override;

		int32_t getWidth() const;
		int32_t getHeight() const;

		float* getData() const;

		bool getPixel(int32_t x, int32_t y, QColor* result) const;
		bool setPixel(int32_t x, int32_t y, const QColor& color);

		void clear(const QColor& color);

		Result saveToFile(const char* filename);

		virtual Result getField(const String& name, QValue* result) const override;

	private:
		int32_t width;
		int32_t height;
		float* data = nullptr;
	};
}