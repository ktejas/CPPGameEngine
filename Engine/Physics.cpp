#include "Physics.h"

namespace Engine
{
	namespace Physics
	{
		std::list<PhysicsInfo*> g_PhysicsBodies = std::list<PhysicsInfo*>();

		void Init()
		{

		}

		void Update(const float i_dt)
		{
			for (std::list<PhysicsInfo*>::iterator it = g_PhysicsBodies.begin(); it != g_PhysicsBodies.end(); it++)
			{
				(*it)->Update(i_dt);
			}
		}

		void RegisterPhysicsInfo(PhysicsInfo * i_pInfo)
		{
			g_PhysicsBodies.push_back(i_pInfo);
		}

		void Shutdown()
		{
			g_PhysicsBodies.clear();
		}
	} // namespace Physics
}// namespace Engine