#pragma once


class Vector3D
{
public:
	Vector3D() :m_x(0), m_y(0), m_z(0)
	{
	}
	Vector3D(float x, float y, float z) :m_x(x), m_y(y), m_z(z)
	{
	}
	Vector3D(const Vector3D& vector) :m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z)
	{
	}

	~Vector3D()
	{
	}

	static Vector3D Lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.m_x = start.m_x * (1.0f - delta) + end.m_x * (delta);
		v.m_y = start.m_y * (1.0f - delta) + end.m_y * (delta);
		v.m_z = start.m_z * (1.0f - delta) + end.m_z * (delta);
		return v;
	}


	float m_x;
	float m_y; 
	float m_z;
};