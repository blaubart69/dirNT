#pragma once

#include "beewstring.h"

namespace bee
{
	class LastError
	{
	private:

		DWORD   _rc = 0;
		LPCSTR  _func = nullptr;
		wstring _param;

	public:

		LastError() : _rc(0), _func(nullptr) {}
		LastError(LPCSTR errFunc)
		{
			this->set(errFunc);
		}

		bool failed() const { return _rc != 0; }

		LastError* set(LPCSTR errFunc)
		{
			_rc = ::GetLastError();
			_func = errFunc;
			return this;
		}
		LastError* set(LPCSTR errFunc, DWORD lastError)
		{
			_rc = lastError;
			_func = errFunc;
			return this;
		}
		LastError* set(LPCSTR errFunc, const bee::wstring& funcParam)
		{
			this->set(errFunc);
			this->_param.assign(funcParam);
			return this;
		}

		DWORD code(void) { return _rc; }
		void print(void);
	};
}