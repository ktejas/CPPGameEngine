#include "Timing.h"
#include "EConsolePrint.h"

#include <Windows.h>

namespace Engine
{
	namespace Timing
	{
		float		   g_LastFrameTime_ms = 0.0f;
		LARGE_INTEGER  g_LastFrameStartTick;
		LARGE_INTEGER  g_Frequency;

		void Init()
		{
			g_Frequency = GetFrequency();
			g_LastFrameStartTick = GetCounter();
		}
		
		float TimeSinceLastFrame()
		{
			CalculateLastFrameTime();
#if defined (CONSTANT_FRAMETIME)
			return DESIRED_FRAMETIME_MS;
#elif defined (CLAMP_FRAMETIME)
			if (g_LastFrameTime_ms > MAX_FRAMETIME_MS)
				return MAX_FRAMETIME_MS;
			else
				return g_LastFrameTime_ms;
#else
			return g_lastFrameTime_ms;
#endif
		}

		void CalculateLastFrameTime()
		{
			LARGE_INTEGER currentTick = GetCounter();
			LARGE_INTEGER elapsedTicks;
			elapsedTicks.QuadPart = (currentTick.QuadPart - g_LastFrameStartTick.QuadPart);

			elapsedTicks.QuadPart *= 1000;
			g_LastFrameTime_ms = elapsedTicks.QuadPart * (1.0f / g_Frequency.QuadPart);

			//g_LastFrameTime_ms = static_cast<float>(elapsedTicks.QuadPart);

			g_LastFrameStartTick = currentTick;

		}
	}
}