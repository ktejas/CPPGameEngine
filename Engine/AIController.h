#pragma once

#ifndef __Engine__AIController__H__
#define __Engine__AIController__H__

#include "GameObject.h"

namespace Engine
{
	namespace AI
	{
		class AIController
		{
		public:
			AIController(GameObject * i_GameObject);
			virtual void Update(const float i_dt);
			virtual ~AIController() {};

		protected:
			GameObject * m_pGameObject;
		};
	}
}

#endif /* (__Engine__AIController__H__) */