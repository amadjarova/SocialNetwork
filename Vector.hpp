#pragma once
#include <iostream>
const unsigned RESIZE_COEF = 2;
template<typename T>
class Vector
{
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 4;

	void resize(size_t newCapacity);
	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
public:
	Vector();
	Vector(size_t _capacity);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);

	size_t getSize() const;
	size_t getCapacity() const;

	void push_back(const T& obj);
	void push_back(T&& obj);
	void pop_back();
	void insert(const T& obj, unsigned index);
	void erase(unsigned index);
	void clear();
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	~Vector();
	bool contains(const T& el) const;

};

template<typename T>
Vector<T>::Vector() :Vector(4)
{
}

template<typename T>
Vector<T>::Vector(size_t _capacity):capacity(_capacity)
{
	data = new T[_capacity];
}

template<typename T>
size_t Vector<T>::getSize() const
{
	return size;
}

template<typename T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
T& Vector<T>::operator[](size_t index)
{
	return data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const
{
	return data[index];
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
void Vector<T>::free()
{
	delete[] data;
	capacity = 4;
	size = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	size = other.size;
	data = new T[other.capacity];
	capacity = other.capacity;
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}

}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

template<typename T>
void Vector<T>::resize(size_t newCapacity)
{
	T* temp = new T[newCapacity];
	if (size > newCapacity)
		size = newCapacity;
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = std::move(data[i]);
	}
	delete[] data;
	data = temp;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
void Vector<T>::push_back(const T& obj)
{

	if (size == capacity)
	{
		resize(capacity * RESIZE_COEF);
	}

	data[size++] = obj;
}

template<typename T>
void Vector<T>::pop_back()
{
	if (size == 0)
	{
		throw "Vector is empty";
	}
	size--;
}

template<typename T>
void Vector<T>::insert(const T& obj, unsigned index)
{
	if (index >= size)
	{
		throw "Invalid index.";
	}
	data[index] = obj;
}

template<typename T>
void Vector<T>::push_back(T&& obj)
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEF);
	}
	data[size++] = std::move(obj);
}

template<typename T>
void Vector<T>::erase(unsigned index)
{
	if (index >= size)
	{
		throw "Invalid index.";
	}
	for (size_t i = index; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
	size--;
}

template<typename T>
void Vector<T>::clear()
{
	free();
}

template<typename T>
bool Vector<T>::contains(const T& el) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == el)
		{
			return true;
		}
	}
	return false;
}