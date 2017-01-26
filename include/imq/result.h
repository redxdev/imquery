#pragma once

namespace imq
{
	class IMQ_API Result
	{
	public:
		Result()
		{
			this->ok = true;
		}

		Result(bool ok, const String& err)
		{
			this->ok = ok;
			this->err = err;
		}

		Result(bool ok)
		{
			this->ok = ok;
		}

		bool isOk() const
		{
			return ok;
		}

		const String& getErr()
		{
			return err;
		}

		operator bool() const
		{
			return ok;
		}

	private:
		String err;
		bool ok;
	};
}