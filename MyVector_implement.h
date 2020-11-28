#pragma once
#include "MyVector.h"

template<class T>
inline MyVector<T>::MyVector()
	:size_(0),
	capacity_(size_),
	ptr_(new T[capacity_])
{
}

template<class T>
inline MyVector<T>::MyVector(const int& count)
	:size_(count),
	capacity_(size_)
{
	if (size_ < 0)
		throw std::length_error("vector too long");

	ptr_ = new T[capacity_];
	std::fill(begin(), end(), T());
}

template<class T>
inline MyVector<T>::MyVector(const int& count, const T& value)
	:size_(count),
	capacity_(size_),
	ptr_(new T[capacity_])
{
	if (size_ < 0)
		throw std::length_error("vector too long");

	ptr_ = new T[capacity_];
	std::fill(begin(), end(), value);
}

template<class T>
inline MyVector<T>::MyVector(const std::initializer_list<T>& elements)
	:size_(elements.size()),
	capacity_(size_),
	ptr_(new T[capacity_])
{
	std::copy(elements.begin(), elements.end(), begin());
}

template<class T>
inline MyVector<T>::MyVector(const_iterator p1, const_iterator p2)
	:size_(p2 - p1),
	capacity_(size_),
	ptr_(new T[capacity_])
{
	for (int i = 0; i < size_; ++i) {
		ptr_[i] = p1[i];
	}
}

template<class T>
inline MyVector<T>::MyVector(const MyVector& v)//
	:size_(v.size_),
	capacity_(v.size_),
	ptr_(new T[size_])
{
	std::copy(v.cbegin(), v.cend(), begin());
}

template<class T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& v)
{
	MyVector(v).swap(*this);
	return *this;
}

template<class T>
inline int MyVector<T>::size() const
{
	return size_;
}

template<class T>
inline int MyVector<T>::capacity() const
{
	return capacity_;
}

template<class T>
inline void MyVector<T>::push_back(const T& value)
{
	if (capacity_ > size_) {
		ptr_[size_] = value;
		++size_;
		return;
	}

	capacity_ += size_ * coef_ + 2;
	T* p = new T[capacity_];
	std::copy(begin(), end(), p);
	p[size_] = value;
	delete[] ptr_;
	ptr_ = p;
	++size_;
}

template<class T>
inline void MyVector<T>::pop_back()
{
	--size_;
}

template<class T>
inline void MyVector<T>::erase(const_iterator p_other)
{
	int index = p_other - begin();
	std::copy(begin() + index + 1, end(), begin() + index);
	resize(size_ - 1);
}

template<class T>
inline void MyVector<T>::erase(const_iterator first, const_iterator last)
{
	int interval = last - first;
	int index = first - begin();
	std::copy(begin() + index + interval, end(), begin() + index);
	resize(size_ - interval);
}

template<class T>
inline void MyVector<T>::insert(const_iterator position, const T& value)
{
	int index = position - begin();
	resize(size_ + 1);

	std::copy_backward(begin() + index, end() - 1, end());
	(*this)[index] = value;
}

template<class T>
inline void MyVector<T>::insert(const_iterator position, const T& size_v, const T& value)
{
	int index = position - begin();
	resize(size_ + size_v);

	std::copy_backward(begin() + index, end() - size_v, end());
	std::fill(begin() + index, begin() + index + size_v, value);
}

template<class T>
inline void MyVector<T>::insert(const_iterator position, const_iterator first, const_iterator last)
{
	int index = position - begin();
	int s = last - first;
	resize(size_ + s);

	std::copy_backward(begin() + index, end() - s, end());
	std::copy(first, last, begin() + index);
}

template<class T>
inline void MyVector<T>::resize(const int& new_size, const T& value)
{
	if (new_size == size_)
		return;
	if (new_size < 0)
		throw std::invalid_argument("size can not be negative");
	if (new_size < size_)
	{
		size_ = new_size;
		return;
	}
	if (new_size > capacity_)
		reserve(new_size);

	std::fill(ptr_ + size_, ptr_ + new_size, value);
	size_ = new_size;
}

template<class T>
inline void MyVector<T>::reserve(const int& new_capacity)
{
	if (new_capacity <= size_)
		return;

	capacity_ = new_capacity;
	T* p_new = new T[capacity_];
	std::copy(begin(), end(), p_new);
	delete[]ptr_;
	ptr_ = p_new;
}

template<class T>
inline void MyVector<T>::swap(MyVector& v)
{
	std::swap(size_, v.size_);
	std::swap(capacity_, v.capacity_);
	std::swap(ptr_, v.ptr_);
}

template<class T>
typename inline MyVector<T>::iterator MyVector<T>::begin()
{
	return ptr_;
}

template<class T>
typename inline MyVector<T>::const_iterator MyVector<T>::begin() const
{
	return ptr_;
}

template<class T>
typename inline MyVector<T>::const_iterator MyVector<T>::cbegin() const
{
	return ptr_;
}

template<class T>
typename inline MyVector<T>::iterator MyVector<T>::end()
{
	return ptr_ + size_;
}

template<class T>
typename inline MyVector<T>::const_iterator MyVector<T>::end() const
{
	return ptr_ + size_;
}

template<class T>
typename inline MyVector<T>::const_iterator MyVector<T>::cend() const
{
	return ptr_ + size_;
}

template<class T>
inline bool MyVector<T>::empty() const
{
	return size_ == 0;
}

template<class T>
inline const T& MyVector<T>::front() const
{
	return *ptr_;
}

template<class T>
inline const T& MyVector<T>::back() const
{
	return *(ptr_ + size_ - 1);
}

template<class T>
inline int MyVector<T>::operator*() const
{
	return *ptr_;
}

template<class T>
inline T& MyVector<T>::operator[](const int& index)
{
	if (index < 0 || index >= size())
		throw std::out_of_range("index out of range");
	return ptr_[index];//*(ptr_ + index)
}

template<class T>
inline const T& MyVector<T>::operator[](const int& index) const
{
	if (index < 0 || index >= size())
		throw std::out_of_range("index out of range");
	return ptr_[index];
}

template<class T>
bool operator==(const MyVector<T>& v1, const MyVector<T>& v2)
{
	return std::equal(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
}

template<class T>
bool operator!=(const MyVector<T>& v1, const MyVector<T>& v2) {
	return !(v1 == v2);
}

template<class T>
bool operator<(const MyVector<T>& v1, const MyVector<T>& v2) {
	return std::lexicographical_compare(v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend());
}

template<class T>
bool operator<=(const MyVector<T>& v1, const MyVector<T>& v2) {
	return !(v1 > v2);
}

template<class T>
bool operator>(const MyVector<T>& v1, const MyVector<T>& v2) {
	return v2 < v1;
}

template<class T>
bool operator>=(const MyVector<T>& v1, const MyVector<T>& v2) {
	return !(v1 < v2);
}

template<class T>
std::ostream& operator <<(std::ostream& out, const MyVector<T>& p) {
	for (auto p1 = p.begin(); p1 != p.end(); ++p1) {
		out << *p1 << " ";
	}
	return out;
}