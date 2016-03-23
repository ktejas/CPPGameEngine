#pragma once

#ifndef __Engine__Event__H__
#define __Engine__Event__H__

#include <windows.h>

#include "WaitableObject.h"

namespace Engine
{

	class ManualResetEvent : public WaitableObject
	{
	public:
		ManualResetEvent(const char * i_pName, bool i_bInitiallySignaled);
		~ManualResetEvent();

		void Reset(void);
		// We should add a wait timeout parameter but I'm in a hurry
		bool WaitFor(void);
		void Signal(void);
	};

	class AutoResetEvent : public WaitableObject
	{
	public:
		AutoResetEvent(const char * i_pName, bool i_bInitiallySignaled);
		~AutoResetEvent();

		// We should add a wait timeout parameter but I'm in a hurry
		bool WaitFor(void);
		void Signal(void);
	};
} // namespace Engine

#endif // /* (__Engine__Event__H__) */


