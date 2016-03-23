#include "PhysicsInfo.h"

namespace Engine
{
	namespace Physics
	{
		PhysicsInfo::PhysicsInfo(GameObject * i_pGameObject) : m_pGameObject(i_pGameObject)
		{

		}

		void PhysicsInfo::Update(const float i_dt)
		{
			Vector3 v_t = m_pGameObject->getVelocity();
			Vector3 position = m_pGameObject->getPosition();

			position += v_t * i_dt * 100;

			m_pGameObject->setPosition(position);

		} // namespace Physics
	} // namespace Engine
}