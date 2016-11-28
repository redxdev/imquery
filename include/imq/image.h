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
}