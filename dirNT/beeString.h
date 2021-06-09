#pragma once

#include "nt.h"

namespace bee
{
	template<class T>
	class basic_string
	{
	public:

		basic_string()
			: _buf(nullptr), _len(0), _capacity(0)
		{
		}
		basic_string(const size_t capacity)
		{
			_buf = nullptr;
			_capacity = 0;
			_len = 0;
			ensureCapacity(capacity);
		}

		basic_string& push_back(const T& _Val)
		{
			ensureCapacity(_len + 1);
			_buf[_len] = _Val;
			_len += 1;
			return *this;
		}
		basic_string& append(const T* ptr, const size_t len)
		{
			ensureCapacity(this->length() + len);

			nt::RtlMoveMemory(&_buf[_len], ptr, len * sizeof(T));
			_len += len;

			return *this;
		}
		basic_string& append(const basic_string& str)
		{
			return append(str.data(), str.length());
		}
		basic_string& assign(const T* other, const size_t len)
		{
			resize(0);
			ensureCapacity(len);
			return append(other, len);
		}
		basic_string& assign(const basic_string& other)
		{
			return assign(other.data(), other.length());
		}
		basic_string& resize(size_t newSize)
		{
			if (newSize > _len)
			{
				ensureCapacity(newSize);
				nt::RtlFillMemory(&_buf[_len], sizeof(T) * (newSize - _len), 0);
			}

			_len = newSize;
			return *this;
		}
		basic_string& reserve(size_t newCapacity)
		{
			ensureCapacity(newCapacity);
			return *this;
		}
		T* data() const
		{
			return _buf;
		}
		T& operator[](size_t idx) const
		{
			return _buf[idx];
		}
		size_t length() const
		{
			return _len;
		}
		const T* c_str()
		{
			const size_t len = length();

			ensureCapacity(len + 1);

			if (L'\0' != (*this)[len])
			{
				(*this)[len] = L'\0';
			}

			return _buf;
		}
		bool ends_with(const T c) const
		{
			if (length() == 0)
			{
				return false;
			}

			T& charAtTheEnd = (*this)[length() - 1];
			return charAtTheEnd == c;
		}

	protected:

		size_t align_to_64(size_t length)
		{
			const size_t c = 64 - 1;
			return (length + c) & ~c;
		}
		void ensureCapacity(const size_t wantCapacity)
		{
			if (_capacity < wantCapacity)
			{
				const size_t newCapacity = align_to_64(wantCapacity);

				if (_buf == __nullptr)
				{
					_buf = (T*)HeapAlloc(GetProcessHeap(), 0, sizeof(T) * newCapacity);
				}
				else
				{
					_buf = (T*)HeapReAlloc(GetProcessHeap(), 0, _buf, sizeof(T) * newCapacity);
				}

				if (_buf == nullptr)
				{
					ExitProcess(ERROR_NOT_ENOUGH_MEMORY);
				}

				_capacity = newCapacity;
			}
		}

		size_t	_capacity;
		size_t	_len;
		T*		_buf;

	};
}