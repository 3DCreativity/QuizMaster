#pragma once
#include <stdexcept>

template<typename K,typename V>
class custom_hashmap {
private:
	K* keys;
	V* values;
	size_t size_map;
	size_t capacity_map;

	void freeDynamic()
	{
		delete[] keys;
		delete[] values;
	}

	void resize()
	{
		this->capacity_map *= 2;
		K* new_keys = new K[this->capacity_map];
		V* new_values = new V[this->capacity_map];
		for (size_t i = 0; i < this->size_map; i++)
		{
			new_keys[i] = this->keys[i];
			new_values[i] = this->values[i];
		}
		this->freeDynamic();
		this->keys = new_keys;
		this->values = new_values;
	}

public:

	custom_hashmap(size_t capacity = 5) : size_map(0), capacity_map(capacity) {
		this->keys = new K[capacity];
		this->values = new V[capacity];
	}

	custom_hashmap(const custom_hashmap& other) : size_map(other.size_map), capacity_map(other.capacity_map) {
		this->keys = new K[capacity_map];
		this->values = new V[capacity_map];
	}

	~custom_hashmap() {
		this->freeDynamic();
	}

	custom_hashmap& operator=(const custom_hashmap& other)
	{
		if (this != &other)
		{
			this->freeDynamic();

			this->size_map = other.size_map;
			this->capacity_map = other.capacity_map;
			this->keys = new K[this->capacity_map];
			this->values = new V[this->capacity_map];

			for (size_t i = 0; i < this->size_map; i++)
			{
				this->keys[i] = other.keys[i];
				this->values[i] = other.values[i];
			}
		}

		return *this;
	}

	const K* getKeys() const {
		return this->keys;
	}

	V& getValue(const K& key)
	{
		size_t index = 0;
		while (this->keys[index] != key && index < this->size_map)
		{
			index++;
		}
		if (index >= this->size_map)
		{
			throw std::invalid_argument("Key not found");
		}

		return this->values[index];
	}

	size_t getSize()
	{
		return this->size_map;
	}
	
	void add(const K& key, const V& value)
	{
		if (this->size_map >= this->capacity_map)
		{
			resize();
		}
		this->keys[this->size_map] = key;
		this->values[this->size_map] = value;
		this->size_map++;
	}
	
	void remove(const K& key)
	{
		size_t index = 0;
		while (this->keys[index] != key && index < this->size_map)
		{
			index++;
		}
		if (index >= this->size_map)
		{
			throw std::invalid_argument("Key not found");
		}
		
		for (size_t i = index; i < this->size_map - 1; i++)
		{
			this->keys[i] = this->keys[i + 1];
			this->values[i] = this->values[i + 1];
		}

		this->size_map--;
	}
};