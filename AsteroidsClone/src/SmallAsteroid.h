#pragma once

#include "Asteroid.h"
#include "Object.h"

class SmallAsteroid : public Asteroid
{
public:
	SmallAsteroid(const Vector2D& Location, const Vector2D& _Direction);
	~SmallAsteroid() override;
};
