#pragma once
#include <iostream>
#include <initializer_list>
template<class T>
class MyVector {
public:
	MyVector();
	MyVector(const int& count);
	MyVector(const int& count, const T& value);
	MyVector(const std::initializer_list<T>& elements);
	MyVector(const T* p1, const T* p2);
	MyVector(const MyVector& v);//copy
	MyVector& operator= (const MyVector& v);

	int size()const;
	int capacity()const;

	void push_back(const T& value);
	void pop_back();

	void erase(const T* p);
	void erase(const T* first, const T* last);

	void insert(const T* first, const T& value);
	template<class U>
	void insert(const T* first, const T& size_v, const U& value);
	void insert(const T* pos, const T* first, const T* last);

	void resize(const int& n, const T& value = T());
	void reserve(const int& n);
	void swap(MyVector& v);
	bool empty()const;

	const T& front()const;
	const T& back()const;

	int operator*()const;
	T& operator[](const int& index)const;
	T* begin();
	const T* begin()const;
	const T* cbegin()const;
	T* end();
	const T* end()const;
	const T* cend()const;

	~MyVector() {
		delete[]ptr_;
		ptr_ = nullptr;
	}
private:
	const int coef_ = 2;
	int size_;
	int capacity_;
	T* ptr_;
};
#include "MyVector_implement.h"