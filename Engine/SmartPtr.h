#pragma once

#ifndef __Engine__SmartPtr__
#define __Engine__SmartPtr__

#include <assert.h>
#include "EConsolePrint.h"

namespace Engine
{

	template <class T>
	class SmartPtr
	{
	public:

		SmartPtr(T * i_pGameObject = NULL);
		SmartPtr(const SmartPtr & i_other);
		T * operator->() const;
		T & operator*() const;
		SmartPtr& operator = (const SmartPtr & i_other);
		bool operator == (const SmartPtr & i_other) const;
		bool operator != (const SmartPtr & i_other) const;
		bool operator ! () const;
		~SmartPtr();

	private:
		void ReleaseCurrentReference();
		void AcquireNewReference(const SmartPtr &i_other);

		short *			m_pRefCount;
		T *				m_pGameObject;
	};
}// namespace Engine

namespace Engine
{
	template <class T>
	SmartPtr<T>::SmartPtr(T * i_pGameObject) : m_pGameObject(i_pGameObject), m_pRefCount(new short(1))
	{

	}

	template <class T>
	T * SmartPtr<T>::operator->() const
	{
		assert(m_pGameObject != NULL);
		return m_pGameObject;
	}

	template <class T>
	T & SmartPtr<T>::operator*() const
	{
		assert(m_pGameObject != NULL);
		return *m_pGameObject;
	}

	template <class T>
	SmartPtr<T>::SmartPtr(const SmartPtr<T> & i_other) : m_pGameObject(i_other.m_pGameObject), m_pRefCount(i_other.m_pRefCount)
	{
		(*m_pRefCount)++;
	}

	template <class T>
	void SmartPtr<T>::ReleaseCurrentReference()
	{
		assert(*m_pRefCount != 0);
		if (--(*m_pRefCount) == 0)
		{
			delete m_pGameObject;
			delete m_pRefCount;
		}
	}

	template <class T>
	SmartPtr<T>& SmartPtr<T>::operator = (const SmartPtr<T> & i_other)
	{
		ReleaseCurrentReference();
		AcquireNewReference(i_other);
		return *this;
	}

	template <class T>
	bool SmartPtr<T>::operator == (const SmartPtr<T> & i_other) const
	{
		return m_pGameObject == i_other.m_pGameObject;
	}

	template <class T>
	bool SmartPtr<T>::operator != (const SmartPtr<T> & i_other) const
	{
		return m_pGameObject != i_other.m_pGameObject;
	}

	template <class T>
	bool SmartPtr<T>::operator ! () const
	{
		return !m_pGameObject;
	}

	template <class T>
	SmartPtr<T>::~SmartPtr()
	{
		ReleaseCurrentReference();
	}

	template <class T>
	void SmartPtr<T>::AcquireNewReference(const SmartPtr &i_other)
	{
		m_pRefCount = i_other.m_pRefCount;
		m_pGameObject = i_other.m_pGameObject;
	}
}

#endif /*(__Engine__SmartPtr__)*/