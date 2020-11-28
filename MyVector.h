#pragma once
#include <iostream>
#include <initializer_list>

template<class T>
class MyVector {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
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

	void erase(const_iterator p);
	void erase(const_iterator first, const_iterator last);

	void insert(const_iterator position, const T& val);
	void insert(const_iterator position, const T& size_v, const T& value);
	void insert(const_iterator position, const_iterator first, const_iterator last);

	void resize(const int& n, const T& value = T());
	void reserve(const int& n);
	void swap(MyVector& v);
	bool empty()const;

	const T& front()const;
	const T& back()const;

	int operator*()const;
	T& operator[](const int& index);
	const T& operator[](const int& index)const;
	iterator begin();
	const_iterator begin()const;
	const_iterator cbegin()const;
	iterator end();
	const_iterator end()const;
	const_iterator cend()const;

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