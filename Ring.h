#pragma once

#include "stdafx.h"
#include <iostream>
#include <exception>
#include <string>

// limits for tests, lecture is 8.44
#define L_844_MAX_CAPACITY		  50
#define L_844_MAX_DATA_POINTS   8000

using namespace std;

template <typename T>
class Ring
{
	// 8.42 Nested template classes
	// 8.43 Ring buffer class
	// 8.44 making classes iterable
private:
	int		m_pos;
	int		m_size;
	bool	m_isFull;
	T 		*m_values;
public:
	class iterator;
public:
	Ring(int size) :
		m_pos(0),
		m_size(size),
		m_isFull(false),
		m_values(NULL)
	{
		m_values = new T[size];
	}

	Ring(const Ring &copy) :
		m_pos(copy.m_pos),
		m_size(copy.m_size),
		m_isFull(copy.m_isFull),
		m_values(NULL)
	{
		m_values = new T[m_size];
	}

	~Ring()
	{
		delete[] m_values;
	}

	void add(T value)
	{
		m_values[m_pos] = value;
		m_pos += 1;
		if (m_pos == m_size)
		{
			m_pos = 0;
			m_isFull = true;
		}
		return;
	}

	int capacity() const
	{
		return m_size;
	}

	T & get(int pos) 
	{
		return m_values[pos];
	}

	int getPos() const
	{
		return m_pos;
	}


	bool empty() const
	{
		return ((!m_isFull) && (m_pos == 0));
	}

	int size() const
	{
		if (m_isFull)return m_size;
		return m_pos;
	}

	// iterator methods

	iterator begin() 
	{
		if (!m_isFull)return iterator(0, *this);
		return iterator(m_pos, *this);
	}

	iterator end()
	{
		if (!m_isFull)return iterator(m_pos, *this);
		return iterator((-1), *this);
	}
};





template <typename T>
class Ring<T>::iterator
{
private:
	int m_pos;
	Ring & m_ring;

public:
	iterator(
		int pos, 
		Ring & ring):	m_pos(pos), 
						m_ring(ring){}

	// overloaded prefix ++
	iterator & operator ++ ()
	{
		if (m_pos < 0)
		{
			return *this;
		}
		m_pos++;
		m_pos %= m_ring.m_size;	// wrap aroud
		if (m_pos == m_ring.m_pos)
		{
			if (m_ring.m_isFull)m_pos = -1;
			return *this;
		}
		return *this;
	}

	//// overloaded postfix ++
	iterator operator ++ (int)
	{
		iterator old = *this;
		++(*this);
		return old;
	}

	// overloaded * dereference
	T &operator*()
	{
		return m_ring.get(m_pos);
	}

	// overloaded != 
	bool operator != (const iterator & other) const
	{
		return (m_pos != other.m_pos);
	}

	// overloaded = 
	iterator & operator = (const iterator & other) 
	{
		if (this == &other) return *this;
		this->m_pos = other.m_pos;
		this->m_ring = other.m_ring;
		return *this;
	}

};

