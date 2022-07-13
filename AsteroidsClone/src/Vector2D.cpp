#include "Vector2D.h"
#include <cmath>

Vector2D::Vector2D(float _X, float _Y) : X(_X), Y(_Y)
{

}

Vector2D::Vector2D(const Vector2D& V) : X(V.X), Y(V.Y)
{

}

Vector2D Vector2D::Norm() const
{
	float InvLength = 1.f / this->Length();
	return Vector2D(X * InvLength, Y * InvLength);
}

Vector2D Vector2D::Pow(int Exp) const
{
	return Vector2D(pow(X, Exp), pow(Y, Exp));
}

float Vector2D::Dot(const Vector2D& V) const
{
	return X * V.X + Y * V.Y;
}

float Vector2D::Length() const
{
	return std::hypot(X, Y);
}

Vector2D Vector2D::operator+(const Vector2D& V) const
{
	return Vector2D(X + V.X, Y + V.Y);
}

Vector2D Vector2D::operator-(const Vector2D& V) const
{
	return Vector2D(X - V.X, Y - V.Y);
}

Vector2D Vector2D::operator*(const Vector2D& V) const
{
	return Vector2D(X * V.X, Y * V.Y);
}

Vector2D Vector2D::operator/(const Vector2D& V) const
{
	return Vector2D(X / V.X, Y / V.Y);
}

Vector2D Vector2D::operator+=(const Vector2D& V)
{
	X += V.X; Y += V.Y;
	return *this;
}

Vector2D Vector2D::operator-=(const Vector2D& V)
{
	X -= V.X; Y -= V.Y;
	return *this;
}

Vector2D Vector2D::operator=(const Vector2D& V)
{
	X = V.X; Y = V.Y;
	return *this;
}

Vector2D Vector2D::operator+(float A) const
{
	return Vector2D(X + A, Y + A);
}

Vector2D Vector2D::operator-(float A) const
{
	return Vector2D(X - A, Y - A);
}

Vector2D Vector2D::operator-=(float A)
{
	X -= A; Y -= A;
	return *this;
}

Vector2D Vector2D::operator+=(float A)
{
	X += A; Y += A;
	return *this;
}

Vector2D Vector2D::operator*(float Scale) const
{
	return Vector2D(X * Scale, Y * Scale);
}

Vector2D Vector2D::operator/(float Scale) const
{
	const float RScale = 1.f / Scale;
	return Vector2D(X * RScale, Y * RScale);
}

bool Vector2D::operator==(const Vector2D& V) const
{
	return X == V.X && Y == V.Y;
}

bool Vector2D::operator!=(const Vector2D& V) const
{
	return X != V.X || Y != V.Y;
}

Vector2D operator/(float Scale, const Vector2D& V)
{
	return Vector2D(Scale / V.X, Scale / V.Y);
}

Vector2D operator*(float Scale, const Vector2D& V)
{
	return Vector2D(Scale * V.X, Scale * V.Y);
}
