#pragma once

struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	float x;
	float y;

	Vector2() :
		x(0.0f)
		, y(0.0f)
	{

	}
	Vector2(int _x, int _y)
		:x(_x)
		, y(_y)
	{

	}
	Vector2(float _x, float _y)
		:x(_x)
		, y(_y)
	{

	}
	Vector2(long _x, long _y)
		:x(_x)
		,y(_y)
	{

	}
	/*Vector2(Vector2& _other)
	{
		x = _other.x;
		y = _other.y;
	}*/
	Vector2& operator/(float _value)
	{
		x /= _value;
		y /= _value;
		return *this;
	}
	Vector2& operator+=(const Vector2& _value)
	{
		x += _value.x;
		y += _value.y;
		return *this;
	}
	Vector2& operator-(const Vector2& _value)
	{
		x -= _value.x;
		y -= _value.y;
		return *this;
	}
	Vector2(const Vector2&) = default;
	Vector2(Vector2&&) = default;
	Vector2& operator=(const Vector2&) = default;
	Vector2& operator=(Vector2&&) = default;
	
};
