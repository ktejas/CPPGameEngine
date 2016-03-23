#pragma once

#ifndef __Engine__Vector3__H__
#define __Engine__Vector3__H__

namespace Engine 
{

	class Vector3 
	{

	public:
		Vector3();
		Vector3(float i_x, float i_y, float i_z);

		inline float getX(void) const;
		inline float getY(void) const;
		inline float getZ(void) const;

		inline void setX(float i_x);
		inline void setY(float i_y);
		inline void setZ(float i_z);

		Vector3& operator += (const Vector3 & i_other);
		Vector3& operator -= (const Vector3 & i_other);
		Vector3& operator *= (const Vector3 & i_other);
		Vector3& operator /= (const Vector3 & i_other);
		bool operator == (const Vector3 & i_other);
		bool operator != (const Vector3 & i_other);

		static const Vector3 Zero;

	private:
		float m_x, m_y, m_z;
		inline bool isNaN(const float i_val);

	};
} /* namespace Engine */

inline Engine::Vector3 operator+(const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs);
inline Engine::Vector3 operator-(const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs);
inline Engine::Vector3 operator*(const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs);
inline Engine::Vector3 operator/(const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs);
inline Engine::Vector3 operator*(const Engine::Vector3& i_lhs, const float i_scalar);
inline Engine::Vector3 operator*(const float i_scalar, const Engine::Vector3& i_lhs);

#include "Vector3-inl.h"

#endif /* defined(__Engine__Vector3__H__) */