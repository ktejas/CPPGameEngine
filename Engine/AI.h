#pragma once

#ifndef __Engine__AI__H__
#define __Engine__AI__H__

#include "AIController.h"

#include <list>

namespace Engine
{
	namespace AI
	{
		extern std::list<AIController*> g_AIControllers;

		void Init();
		void Update(const float i_dt);
		void RegisterAIController(AIController * i_pController);
		void Shutdown();

	} //namespace AI
}// namespace Engine


#endif /* (__Engine__AI__H__) */