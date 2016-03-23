#pragma once

#ifndef __Engine__Waitable__Object__H__
#define __Engine__Waitable__Object__H__

#include <Windows.h>

namespace Engine
{

	class WaitableObject
	{
	public:
		WaitableObject() :
			m_Handle(INVALID_HANDLE_VALUE)
		{

		}

		HANDLE GetHandle(void) { return m_Handle; }

	protected:
		HANDLE					m_Handle;

	};

} // namespace Engine

#endif /* (__Engine__Waitable__Object__H__) */
