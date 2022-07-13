#pragma once
#include "Asteroid.h"
#include "Object.h"
#include "Vector2D.h"

class HomingMissile : public Object
{
public:
    HomingMissile(const Vector2D& Location, Asteroid* InAsteroid);
    void Tick(float DeltaTime) override;
    void OnCollisionDetected(Object* Obj) override;
private:
    Asteroid* _Asteroid;
};
