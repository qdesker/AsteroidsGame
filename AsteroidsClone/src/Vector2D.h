#pragma once

struct Vector2D
{
	float X, Y;
public:
	Vector2D() {};
	Vector2D(float _X, float _Y);
	Vector2D(const Vector2D& V);

	Vector2D Norm() const;
	Vector2D Pow(int Exp) const;
	float Dot(const Vector2D& V) const;

	float Length() const;

	Vector2D operator+(const Vector2D& V) const;
	Vector2D operator-(const Vector2D& V) const;
	Vector2D operator*(const Vector2D& V) const;
	Vector2D operator/(const Vector2D& V) const;
	Vector2D operator+=(const Vector2D& V);
	Vector2D operator-=(const Vector2D& V);
	Vector2D operator=(const Vector2D& V);

	Vector2D operator*(float Scale) const;
	Vector2D operator/(float Scale) const;
	Vector2D operator+(float A) const;
	Vector2D operator-(float A) const;
	Vector2D operator-=(float A);
	Vector2D operator+=(float A);

	bool operator==(const Vector2D& V) const;
	bool operator!=(const Vector2D& V) const;

	friend Vector2D operator/(float Scale, const Vector2D& V);
	friend Vector2D operator*(float Scale, const Vector2D& V);
};

Vector2D operator/(float Scale, const Vector2D& V);
Vector2D operator*(float Scale, const Vector2D& V);

