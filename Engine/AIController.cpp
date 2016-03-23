#include "AIController.h"
#include "EInput.h"

namespace Engine
{
	namespace AI
	{
		AIController::AIController(GameObject * i_pGameObject) : m_pGameObject(i_pGameObject)
		{

		}

		void AIController::Update(const float i_dt)
		{
			Engine::Vector3 velocity = Engine::Vector3::Zero;

			if (Engine::Input::IsKeyDown('W'))
			{
				velocity.setY(1.0f);
			}

			if (Engine::Input::IsKeyDown('S'))
			{
				velocity.setY(-1.0f);
			}

			if (Engine::Input::IsKeyDown('A'))
			{
				velocity.setX(-1.0f);
			}

			if (Engine::Input::IsKeyDown('D'))
			{
				velocity.setX(1.0f);
			}

			m_pGameObject->setVelocity(velocity * 0.001f);
		}
	}
}