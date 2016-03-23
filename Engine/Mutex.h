#pragma once

#ifndef __Engine__Mutex__H__
#define __Engine__Mutex__H__

#include "WaitableObject.h"

namespace Engine {
	class Mutex : public WaitableObject
	{
	public:
		Mutex(const char * i_pName);
		~Mutex();

		bool TryLock(void);
		void Lock(void);
		void Release(void);

	};
} // namespace Engine


#endif /* (__Engine__Mutex__H__) */