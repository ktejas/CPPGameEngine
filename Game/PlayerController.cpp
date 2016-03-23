#include "PlayerController.h"
#include "GameObject.h"
#include "EInput.h"
#include "EConsolePrint.h"
#include "Vector3.h"

PlayerController::PlayerController(Engine::GameObject * i_GameObject) : Engine::AI::AIController(i_GameObject)
{

}

void PlayerController::Update(const float i_dt)
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

	m_pGameObject->setVelocity(velocity * 0.003f);

}