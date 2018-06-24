#pragma once
#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>

template <typename T>
class StringItt :public std::iterator<std::forward_iterator_tag, T>
{
public:
	class iterator
	{
		T* ptr;
	public:
		bool invariant()
		{
			return true;
		}

		iterator():ptr(nullptr);
		iterator(T* p)
		{
			ptr = p;
		}
		iterator(iterator & rhs)
		{
			ptr = rhs.ptr;
		}

		bool operator==(const iterator& rhs)
		{
			return ptr == rhs.ptr;
		}
		bool operator!=(const iterator& rhs)
		{
			return ptr != rhs.ptr;
		}
		bool operator<(const iterator& rhs)
		{
			return ptr < rhs.ptr;
		}
		
		T& operator*()
		{
			return *ptr;
		}
		T& operator[](int i)
		{
			return *(ptr + i);
		}


		iterator& operator=(const iterator& rhs)
		{
			ptr = rhs.ptr;

			return *this;
		}
		iterator& operator-(const iterator& rhs)
		{
			ptr -= rhs.ptr;

			return *this;
		}
		iterator operator+(const int i)
		{
			assert(invariant());
			T* temp = ptr;

			return iterator(temp += i);
		}
		iterator operator++()
		{
			assert(invariant());
			++ptr;
			return iterator(ptr);
		}
		iterator operator++(int)
		{
			assert(invariant());
			T* temp = ptr;
			++ptr;
			return iterator(temp);
		}
		iterator operator--(int)
		{
			assert(invariant());
			T* temp = ptr;
			--ptr;
			return iterator(temp);
		}
	};

	class reverse_iterator
	{
		T* ptr;
	public:
		bool invariant() 
		{ 
			return ptr != nullptr; 
		}

		reverse_iterator() = default;
		reverse_iterator(T* p)
		{
			ptr = p;
		}
		reverse_iterator(reverse_iterator & rhs) 
		{
			ptr = rhs.ptr;
		}
		
		bool operator==(const reverse_iterator& rhs) 
		{ 
			return ptr == rhs.ptr; 
		}
		bool operator!=(const reverse_iterator& rhs) 
		{ 
			return ptr != rhs.ptr; 
		}
		bool operator<(const reverse_iterator& rhs)
		{
			return ptr < rhs.ptr;
		}
		
		T& operator*()
		{
			return *ptr;
		}
		T&  operator[](int i) 
		{ 
			return *(ptr - i); 
		}
		
		reverse_iterator& operator=(const reverse_iterator& rhs)
		{
			assert(invariant());
			ptr = rhs.ptr;
			return *this;
		}
		reverse_iterator& operator-(const iterator& rhs)
		{
			ptr += rhs.ptr;
			
			return *this;
		}
		reverse_iterator operator+(const int i)
		{
			assert(invariant());
			T* temp = ptr;
			return reverse_iterator(temp -= i);
		}
		reverse_iterator operator++()
		{
			assert(invariant());
			--ptr;
			return reverse_iterator(ptr);
		}
		reverse_iterator operator++(int)
		{
			assert(invariant());
			T* temp = ptr;
			--ptr;
			return reverse_iterator(temp);
		}
		reverse_iterator operator--(int)
		{
			assert(invariant());
			T* temp = ptr;
			++ptr;
			return reverse_iterator(temp);
		}
	};
};