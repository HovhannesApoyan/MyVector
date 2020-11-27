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
	capacity_(size_),
	ptr_(new T[capacity_])
{
	for (int i = 0; i < size_; ++i) {
		ptr_[i] = T();
	}
}
template<class T>
inline MyVector<T>::MyVector(const int& count, const T& value)
	:size_(count),
	capacity_(size_),
	ptr_(new T[capacity_])
{
	for (int i = 0; i < size_; ++i) {
		ptr_[i] = value;
	}
}
template<class T>
inline MyVector<T>::MyVector(const std::initializer_list<T>& elements)
	:size_(elements.size()),
	capacity_(size_),
	ptr_(new T[capacity_])
{
	int i = 0;
	for (auto itm : elements) {
		ptr_[i] = itm;
		i++;
	}
}
template<class T>
inline MyVector<T>::MyVector(const T* p1, const T* p2)
	:size_(p2 - p1),
	capacity_(size_),
	ptr_(new T[capacity_])
{
	for (int i = 0; i < size_; ++i) {
		ptr_[i] = p1[i];
	}
}
template<class T>
inline MyVector<T>::MyVector(const MyVector& v)
	:size_(v.size_),
	capacity_(v.capacity_),
	ptr_(new T[capacity_])
{
	int i = 0;
	for (const T* it = v.begin(); it != v.end(); ++it) {
		ptr_[i] = *it;
		i++;
	}
}
template<class T>
inline MyVector<T>& MyVector<T>::operator=(const MyVector<T>& v)
{
	delete[] ptr_;
	this->size_ = v.size_;
	this->capacity_ = v.capacity_;
	ptr_ = new T[capacity_];
	int i = 0;
	for (const T* it = v.begin(); it != v.end(); ++it) {
		ptr_[i] = *it;
		i++;
	}
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
	}
	else {
		if (capacity_ == 0)
			capacity_ = 2;
		else
			capacity_ = size_ * coef_;
		T* p = new T[capacity_];
		int i = 0;
		for (; i < size_; ++i) {
			p[i] = ptr_[i];
		}
		p[i] = value;
		delete[] ptr_;
		ptr_ = p;
		++size_;
	}
}
template<class T>
inline void MyVector<T>::pop_back()
{
	--size_;
}
template<class T>
inline void MyVector<T>::erase(const T* p_other)
{
	T* p_new = new T[size_ - 1];
	int i = 0;
	const T* p = this->ptr_;
	for (; i < size_; ++p, ++i) {
		if (p != p_other)
			p_new[i] = ptr_[i];
		else
			break;
	}
	for (; i < size_ - 1; ++p, ++i) {
		p_new[i] = ptr_[i + 1];
	}
	size_ -= 1;
	capacity_ -= 1;
	delete[]ptr_;
	ptr_ = p_new;
}
template<class T>
inline void MyVector<T>::erase(const T* first, const T* last)
{
	int interval = last - first;
	T* p_new = new T[size_ - interval];
	int i = 0;
	const T* p = this->ptr_;
	int m = 0;
	for (; i < size_; ++p, ++i) {
		if (p != first)
			p_new[i] = ptr_[i];
		else {
			while (true) {
				++p;
				++m;
				if (p == last)
					break;
			}
			break;
		}
	}
	for (; i < size_ - m; ++p, ++i) {
		p_new[i] = ptr_[i + m];
	}
	size_ -= interval;
	capacity_ -= interval;
	delete[]ptr_;
	ptr_ = p_new;
}
template<class T>
inline void MyVector<T>::insert(const T* first, const T& value)
{
	++size_;
	++capacity_;
	T* p_new = new T[capacity_];
	int i = 0;
	const T* p = this->ptr_;
	for (; i < size_; ++p, ++i) {
		if (p != first)
			p_new[i] = ptr_[i];
		else {
			p_new[i] = value;
			++i;
			break;
		}
	}
	for (; i < size_; ++p, ++i) {
		p_new[i] = ptr_[i - 1];
	}
	delete[]ptr_;
	ptr_ = p_new;
}
template<class T>
template<class U>
inline void MyVector<T>::insert(const T* first, const T& size_v, const U& value)
{
	size_ += size_v;
	capacity_ += size_v;
	T* p_new = new T[capacity_];
	int i = 0;
	const T* p = this->ptr_;
	for (; i < size_; ++p, ++i) {
		if (p != first)
			p_new[i] = ptr_[i];
		else {
			int m = size_v;
			while (m) {
				p_new[i] = value;
				++i;
				--m;
			}
			break;
		}
	}
	for (; i < size_; ++p, ++i) {
		p_new[i] = ptr_[i - size_v];
	}
	delete[]ptr_;
	ptr_ = p_new;
}
template<class T>
inline void MyVector<T>::insert(const T* pos, const T* first, const T* last)
{
	size_ += last - first;
	capacity_ = size_;
	T* p_new = new T[capacity_];
	int i = 0;
	const T* p = this->ptr_;
	for (; i < size_; ++p, ++i) {
		if (p != pos)
			p_new[i] = ptr_[i];
		else {
			int m = last - first;
			const T* f = first;
			while (m) {
				p_new[i] = *f;
				f++;
				++i;
				--m;
			}
			break;
		}
	}
	int m = last - first;
	for (; i < size_; ++p, ++i) {
		p_new[i] = ptr_[i - m];
	}
	delete[]ptr_;
	ptr_ = p_new;
}
template<class T>
inline void MyVector<T>::resize(const int& n, const T& value)
{
	if (n > size_ || n < size_) {
		capacity_ = n;
		T* p_new = new T[capacity_];
		int i = 0;
		if (n < size_)
			size_ = n;
		for (; i < size_; ++i) {
			p_new[i] = this->ptr_[i];
		}
		size_ = n;
		for (; i < size_; ++i) {
			p_new[i] = value;
		}
		delete[]ptr_;
		ptr_ = p_new;
	}
}
template<class T>
inline void MyVector<T>::reserve(const int& n)
{
	if (n > size_) {
		capacity_ = n;
		T* p_new = new T[capacity_];
		for (int i = 0; i < size_; ++i) {
			p_new[i] = this->ptr_[i];
		}
		delete[]ptr_;
		ptr_ = p_new;
	}
}
template<class T>
inline void MyVector<T>::swap(MyVector& v)
{
	if (this->size_ == v.size_) {
		T* p = v.ptr_;
		v.ptr_ = this->ptr_;
		this->ptr_ = p;
	}
}
template<class T>
inline T* MyVector<T>::begin()
{
	return ptr_;
}
template<class T>
inline const T* MyVector<T>::begin() const
{
	return ptr_;
}
template<class T>
inline const T* MyVector<T>::cbegin() const
{
	return ptr_;
}
template<class T>
inline T* MyVector<T>::end()
{
	return ptr_ + size_;
}
template<class T>
inline const T* MyVector<T>::end() const
{
	return ptr_ + size_;
}
template<class T>
inline const T* MyVector<T>::cend() const
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
inline T& MyVector<T>::operator[](const int& index) const
{
	try {
		if (index >= 0 && index < size_)
			return *(ptr_ + index);
		throw;
	}
	catch (std::exception const& x) {
		std::cout << x.what() << '\n';
	}
}
template<class T>
bool operator==(const MyVector<T>& v1, const MyVector<T>& v2)
{
	int size_v1 = v1.size();
	int size_v2 = v2.size();
	int size;
	if (size_v1 < size_v2)
		size = size_v1;
	else
		size = size_v2;
	int i = 0;
	for (const T* p = v1.begin(), *p2 = v2.begin(); i < size; ++p, ++p2, ++i) {
		if (*p != *p2)
			return false;
	}
	if (size_v1 != size_v2)
		return false;
	return true;
}
template<class T>
bool operator!=(const MyVector<T>& v1, const MyVector<T>& v2) {
	if (v1 == v2)
		return false;
	return true;
}
template<class T>
bool operator<(const MyVector<T>& v1, const MyVector<T>& v2) {
	int size_v1 = v1.size();
	int size_v2 = v2.size();
	int size;
	if (size_v1 < size_v2)
		size = size_v1;
	else
		size = size_v2;
	int i = 0;
	for (const T* p = v1.begin(), *p2 = v2.begin(); i < size; ++p, ++p2, ++i) {
		if (*p < *p2) {
			return true;
		}
		else if (*p == *p2) {
			continue;
		}
		else
			return false;
	}
	if (size_v1 < size_v2)
		return true;
	return false;
}
template<class T>
bool operator<=(const MyVector<T>& v1, const MyVector<T>& v2) {
	if (v1 < v2 || v1 == v2)
		return true;
	return false;
}
template<class T>
bool operator>(const MyVector<T>& v1, const MyVector<T>& v2) {
	if (v1 <= v2)
		return false;
	return true;
}
template<class T>
bool operator>=(const MyVector<T>& v1, const MyVector<T>& v2) {
	if (v1 < v2)
		return false;
	return true;
}
template<class T>
std::ostream& operator <<(std::ostream& out, const MyVector<T>& p) {
	for (const T* p1 = p.begin(); p1 != p.end(); ++p1) {
		out << *p1 << " ";
	}
	return out;
}