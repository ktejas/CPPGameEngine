#pragma once

#ifndef __Engine__Physics__H__
#define __Engine__Physics__H__

#include "PhysicsInfo.h"

#include <list>

namespace Engine
{
	namespace Physics
	{
		extern std::list<PhysicsInfo*> g_PhysicsBodies;

		void Init();
		void Update(const float i_dt);
		void RegisterPhysicsInfo(PhysicsInfo * i_pInfo);
		void Shutdown();

	} //namespace Physics
}// namespace Engine

#endif /* (__Engine__Physics__H__) */