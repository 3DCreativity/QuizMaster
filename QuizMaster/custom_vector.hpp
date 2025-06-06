#pragma once

#include <stdexcept>

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
	}

	void resize()
	{
		this->capacity_arr *= 2;
		T* new_arr = new T[this->capacity_arr];
		for (size_t i = 0; i < this->size_arr; i++)
		{
			new_arr[i] = this->arr[i];
		}
		this->freeDynamic();
		this->arr = new_arr;
	}
public:
	custom_vector(size_t capacity = 5) :size_arr(0), capacity_arr(capacity) {
		this->arr = new T[capacity];
	}
	custom_vector(const custom_vector& other):size_arr(other.size_arr),capacity_arr(other.capacity_arr) {
		this->arr = new T[other.capacity_arr];
		for (size_t i = 0; i < other.size_arr; i++)
		{
			this->arr[i] = other.arr[i];
		}
	}
	~custom_vector() {
		this->freeDynamic();
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
				this->arr[i] = other.arr[i];
			}
		}

		return *this;
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
	size_t getSize() {
		return this->size_arr;
	}

	void add(const T& value)
	{
		if (this->size_arr >= this->capacity_arr)
		{
			resize();
		}
		this->arr[this->size_arr] = value;
		this->size_arr++;
	}

	void remove(const size_t index)
	{
		if (this->index >= this->size_arr)
		{
			throw std::out_of_range("Index out of bounds");
		}

		for (size_t i = index; i < this->size_arr-1; i++)
		{
			this->arr[i] = this->arr[i + 1];
		}

		this->size_arr--;
	}
};