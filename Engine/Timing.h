#pragma once

#ifndef __Engine__Timing__H__
#define __Engine__Timing__H__

#include <Windows.h>

#define DESIRED_FPS				60.0f
#define DESIRED_FRAMETIME_MS	(1000.0f / DESIRED_FPS)
#define MAX_FRAMETIME_MS		(2 * DESIRED_FRAMETIME_MS)

#define CLAMP_FRAMETIME

namespace Engine
{
	namespace Timing
	{
		extern float		  g_LastFrameTime_ms;
		extern LARGE_INTEGER  g_LastFrameStartTick;
		extern LARGE_INTEGER  g_Frequency;

		void  Init();
		float TimeSinceLastFrame();
		void  CalculateLastFrameTime();

		inline LARGE_INTEGER GetCounter();
		inline LARGE_INTEGER GetFrequency();

	} // namespace Timing
} // namespace Engine

#include "Timing-inl.h"

#endif /*(__Engine__Timing__H__)*/