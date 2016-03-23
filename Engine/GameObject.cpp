#include "GameObject.h"

namespace Engine
{

	GameObject::GameObject() 
	{
		m_Position = Vector3::Zero;
	}

	GameObject::GameObject(Vector3 i_Position) : m_Position(i_Position)
	{
	}

	GameObject::GameObject(Vector3 i_Position, Vector3 i_Velocity) : m_Position(i_Position), m_Velocity(i_Velocity)
	{
	}

	Vector3 GameObject::getPosition()
	{
		return m_Position;
	}

	void GameObject::setPosition(const Vector3& i_Position)
	{
		m_Position = i_Position;
	}


	Vector3 GameObject::getVelocity()
	{
		return m_Velocity;
	}

	void GameObject::setVelocity(const Vector3& i_Velocity)
	{
		m_Velocity = i_Velocity;
	}
} // namespace Engine