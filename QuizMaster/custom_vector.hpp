#pragma once

#include <stdexcept>
#include <utility>
#include <memory>
#include <type_traits>

template<typename T>
class custom_vector
{
private:
	T* arr;
	size_t size_arr;
	size_t capacity_arr;

	void freeDynamic()
	{
		delete[] this->arr;
		this->arr = nullptr;
	}

	// Trait to detect if T is a std::unique_ptr
	template<typename U>
	struct is_unique_ptr : std::false_type {};

	template<typename U>
	struct is_unique_ptr<std::unique_ptr<U>> : std::true_type {};

	void resize()
	{
		this->capacity_arr *= 2;
		T* new_arr = new T[this->capacity_arr];

		for (size_t i = 0; i < this->size_arr; i++)
		{
			if constexpr (is_unique_ptr<T>::value)
			{
				new_arr[i] = std::move(this->arr[i]);
			}
			else
			{
				new_arr[i] = this->arr[i];
			}
		}

		delete[] this->arr;
		this->arr = new_arr;
	}

public:
	custom_vector(size_t capacity = 5)
		: size_arr(0), capacity_arr(capacity)
	{
		this->arr = new T[capacity];
	}

	custom_vector(const custom_vector& other)
		: size_arr(other.size_arr), capacity_arr(other.capacity_arr)
	{
		this->arr = new T[capacity_arr];
		for (size_t i = 0; i < size_arr; i++)
		{
			if constexpr (is_unique_ptr<T>::value)
			{
				// Cannot copy unique_ptr — throw or assert here if needed
				// static_assert(!is_unique_ptr<T>::value, "Copy constructor not allowed for unique_ptr types");
			}
			else
			{
				this->arr[i] = other.arr[i];
			}
		}
	}

	custom_vector& operator=(const custom_vector& other)
	{
		if (this != &other)
		{
			this->freeDynamic();

			this->size_arr = other.size_arr;
			this->capacity_arr = other.capacity_arr;
			this->arr = new T[this->capacity_arr];

			for (size_t i = 0; i < this->size_arr; i++)
			{
				if constexpr (is_unique_ptr<T>::value)
				{
					static_assert(!is_unique_ptr<T>::value, "Copy assignment not allowed for unique_ptr types");
				}
				else
				{
					this->arr[i] = other.arr[i];
				}
			}
		}
		return *this;
	}

	custom_vector(custom_vector&& other) noexcept
		: arr(other.arr), size_arr(other.size_arr), capacity_arr(other.capacity_arr)
	{
		other.arr = nullptr;
		other.size_arr = 0;
		other.capacity_arr = 0;
	}

	custom_vector& operator=(custom_vector&& other) noexcept
	{
		if (this != &other)
		{
			this->freeDynamic();

			this->arr = other.arr;
			this->size_arr = other.size_arr;
			this->capacity_arr = other.capacity_arr;

			other.arr = nullptr;
			other.size_arr = 0;
			other.capacity_arr = 0;
		}
		return *this;
	}

	~custom_vector()
	{
		this->freeDynamic();
	}

	size_t findFirstMatch(const T& other)
	{
		for (size_t result = 0; result < this->size_arr; result++)
		{
			if (this->arr[result] == other)
			{
				return result;
			}
		}
		return -1;
	}

	T& operator[](size_t index)
	{
		return this->arr[index];
	}

	size_t getSize() const
	{
		return this->size_arr;
	}

	void add(const T& value)
	{
		if constexpr (is_unique_ptr<T>::value)
		{
			static_assert(!is_unique_ptr<T>::value, "Cannot copy unique_ptr — use move");
		}
		else
		{
			if (this->size_arr >= this->capacity_arr)
			{
				resize();
			}
			this->arr[this->size_arr++] = value;
		}
	}

	void add(T&& value)
	{
		if (this->size_arr >= this->capacity_arr)
		{
			resize();
		}
		this->arr[this->size_arr++] = std::move(value);
	}

	void remove(size_t index)
	{
		if (index >= this->size_arr)
		{
			throw std::out_of_range("Index out of bounds");
		}

		for (size_t i = index; i < this->size_arr - 1; i++)
		{
			this->arr[i] = std::move(this->arr[i + 1]);
		}
		this->size_arr--;
	}

	T pop()
	{
		T result = std::move(arr[0]);
		remove(0);
		return result;
	}
};
