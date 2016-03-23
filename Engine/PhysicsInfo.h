#pragma once

#ifndef __Engine__PhysicsInfo__H__
#define __Engine__PhysicsInfo__H__

#include "GameObject.h"

namespace Engine 
{
	namespace Physics
	{
		class PhysicsInfo
		{
		public:
			PhysicsInfo(GameObject * i_pGameObject);
			virtual void Update(const float i_dt);

		private:
			GameObject * m_pGameObject;
			float		 m_mass;
			float		 m_drag;
		};
	} // namespace Physics
} //namespace Engine

#endif