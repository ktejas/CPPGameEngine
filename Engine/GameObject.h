#pragma once

#ifndef __Engine__GameObject__H__
#define __Engine__GameObject__H__

#include "Vector3.h"

namespace Engine
{

	class GameObject
	{
	public:
		GameObject();
		GameObject(Vector3 i_Position);
		GameObject(Vector3 i_Position, Vector3 i_Velocity);
		Vector3 getPosition();
		void setPosition(const Vector3& i_Position);
		Vector3 getVelocity();
		void setVelocity(const Vector3& i_Velocity);
		
	private:
		Vector3 m_Position;
		Vector3 m_Velocity;
	};

} // namespace Engine

#endif /* defined(__Engine__GameObject__H__) */