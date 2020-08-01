#pragma once

#include <stdexcept>

namespace Entorpy
{
	template<class T, size_t S>
	class array
	{
	private:
		T data[S];

	public:
		inline constexpr size_t size() const;

		inline T& operator[](size_t index);
		inline constexpr T& operator[](size_t index) const;
	};

	template<class T, size_t S>
	inline constexpr size_t array<T, S>::size() const
	{
		return S;
	}

	template<class T, size_t S>
	inline T& array<T, S>::operator[](size_t index)
	{
		if (index > size())
			throw std::range_error("Index out of range.");
		return data[index];
	}

	template<class T, size_t S>
	inline constexpr T& array<T, S>::operator[](size_t index) const
	{
		if (index > size())
			throw std::range_error("Index out of range.");
		return data[index];
	}
}