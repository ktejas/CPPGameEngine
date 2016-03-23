#pragma once

#ifndef __Engine__Timing__inl__H__
#define __Engine__Timing__inl__H__

#include <Windows.h>

namespace Engine
{
	namespace Timing
	{
		inline LARGE_INTEGER GetFrequency()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			return frequency;
		}

		inline LARGE_INTEGER GetCounter()
		{
			LARGE_INTEGER ticks;
			QueryPerformanceCounter(&ticks);
			return ticks;
		}
	} // namespace Timing
}// namespace Engine

#endif /* (__Engine__Timing__inl__H__) */