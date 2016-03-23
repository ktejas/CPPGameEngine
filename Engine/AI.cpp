#include "AI.h"

namespace Engine
{
	namespace AI
	{
		std::list<AIController*> g_AIControllers = std::list<AIController*>();

		void Init()
		{

		}

		void Update(const float i_dt)
		{
			for (std::list<AIController*>::iterator it = g_AIControllers.begin(); it != g_AIControllers.end(); it++)
			{
				(*it)->Update(i_dt);
			}
		}

		void RegisterAIController(AIController * i_pController)
		{
			g_AIControllers.push_back(i_pController);
		}

		void Shutdown()
		{
			g_AIControllers.clear();
		}

	} // namespace AI
}// namespace Engine