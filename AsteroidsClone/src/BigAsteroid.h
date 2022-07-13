#pragma once
#include "Object.h"
#include "Asteroid.h"

class BigAsteroid : public Asteroid
{
public:
    BigAsteroid(const Vector2D& Location, const Vector2D& _Direction);
    ~BigAsteroid() override;
private:
    unsigned int PartitionTimes = 0;
};
