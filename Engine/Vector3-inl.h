#ifndef __Engine__Vector3__inl__H__
#define __Engine__Vector3__inl__H__

namespace Engine
{

	inline float Vector3::getX() const {
		return m_x;
	}

	inline float Vector3::getY() const {
		return m_y;
	}

	inline float Vector3::getZ() const {
		return m_z;
	}

	inline void Vector3::setX(float i_x) {
		if (!isNaN(i_x)) m_x = i_x;
	}

	inline void Vector3::setY(float i_y) {
		if (!isNaN(i_y)) m_y = i_y;
	}

	inline void Vector3::setZ(float i_z) {
		if (!isNaN(i_z)) m_z = i_z;
	}

	inline bool Vector3::isNaN(const float i_val)
	{
		volatile float v = i_val;
		return v != v;
	}

} /* namespace Engine */

inline Engine::Vector3 operator + (const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs)
{
	return Engine::Vector3(i_lhs.getX() + i_rhs.getX(), i_lhs.getY() + i_rhs.getY(), i_lhs.getZ() + i_rhs.getZ());
}

inline Engine::Vector3 operator - (const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs)
{
	return Engine::Vector3(i_lhs.getX() - i_rhs.getX(), i_lhs.getY() - i_rhs.getY(), i_lhs.getZ() - i_rhs.getZ());
}

inline Engine::Vector3 operator * (const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs)
{
	return Engine::Vector3(i_lhs.getX() * i_rhs.getX(), i_lhs.getY() * i_rhs.getY(), i_lhs.getZ() * i_rhs.getZ());
}

inline Engine::Vector3 operator / (const Engine::Vector3& i_lhs, const Engine::Vector3& i_rhs)
{
	return Engine::Vector3(i_lhs.getX() / i_rhs.getX(), i_lhs.getY() / i_rhs.getY(), i_lhs.getZ() / i_rhs.getZ());
}

inline Engine::Vector3 operator*(const Engine::Vector3& i_lhs, const float i_scalar)
{
	return Engine::Vector3(i_lhs.getX() * i_scalar, i_lhs.getY() * i_scalar, i_lhs.getZ() * i_scalar);
}

inline Engine::Vector3 operator*(const float i_scalar, const Engine::Vector3& i_rhs)
{
	return Engine::Vector3(i_rhs.getX() * i_scalar, i_rhs.getY() * i_scalar, i_rhs.getZ() * i_scalar);
}


#endif /* defined(__Engine__Vector3__inl__H__) */

