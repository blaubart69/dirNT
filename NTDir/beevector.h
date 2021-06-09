#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <type_traits>

extern "C"
{
#undef RtlMoveMemory
	__declspec(dllimport) void __stdcall RtlMoveMemory(void* dst, const void* src, size_t len);

#undef RtlFillMemory
	__declspec(dllimport) void __stdcall RtlFillMemory(void* Destination, size_t Length, int Fill);
}

namespace bee
{
	template< typename T, typename = typename std::enable_if<std::is_trivially_copyable<T>::value>::type >
	class vector
	{
	public:
		vector& push_back(const T& _Val) 
		{
			ensureCapacity(_len + 1);
			_codepageConvertBuffer[_len] = _Val;
			_len += 1;
			return *this;
		}
		vector& append(const T* ptr, const size_t len)
		{
			ensureCapacity(this->size() + len);
			
			RtlMoveMemory(&_codepageConvertBuffer[_len], ptr, len * sizeof(T));
			_len += len;

			return *this;
		}
		vector& append(const vector& vec)
		{
			return append(vec.data(), vec.size());
		}
		void assign(const T* other, const size_t len)
		{
			resize(0);
			ensureCapacity(len);
			append(other, len);
		}
		void assign(const vector& other)
		{
			assign(other.data(), other.size());
		}
		size_t size() const
		{
			return _len;
		}
		void resize(size_t newSize)
		{
			if (newSize > _len)
			{
				ensureCapacity(newSize);
				RtlFillMemory(&_codepageConvertBuffer[_len],  sizeof(T) * (newSize - _len), 0);
			}

			_len = newSize;
		}
		void reserve(size_t newCapacity)
		{
			ensureCapacity(newCapacity);
		}
		T* data() const
		{
			return _codepageConvertBuffer;
		}
		T& operator[](size_t idx) const
		{
			return _codepageConvertBuffer[idx];
		}
		~vector()
		{
			if (_codepageConvertBuffer != nullptr)
			{
				HeapFree(GetProcessHeap(), 0, _codepageConvertBuffer);
			}
		}
		vector() 
			: _codepageConvertBuffer(nullptr), _len(0), _capacity(0) 
		{
		}
		vector(const size_t capacity) 
		{
			_codepageConvertBuffer = nullptr;
			_capacity = 0;
			_len = 0;
			ensureCapacity(capacity);
		}

	protected:

		T*     _codepageConvertBuffer;
		size_t _capacity;
		size_t _len;

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

				if (_codepageConvertBuffer == __nullptr) 
				{ 
					_codepageConvertBuffer = (T*)HeapAlloc  (GetProcessHeap(), 0,       sizeof(T) * newCapacity); 
				}
				else				   
				{ 
					_codepageConvertBuffer = (T*)HeapReAlloc(GetProcessHeap(), 0, _codepageConvertBuffer, sizeof(T) * newCapacity); 
				}

				if (_codepageConvertBuffer == nullptr)
				{
					ExitProcess(ERROR_NOT_ENOUGH_MEMORY);
				}

				_capacity = newCapacity;
			}
		}
	};
}