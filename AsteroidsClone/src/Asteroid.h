#pragma once
#include "Object.h"

class Asteroid : public Object
{
public:
    Asteroid();
    ~Asteroid() override;
    void Tick(float DeltaTime) override;
    void OnCollisionDetected(Object* Obj) override;
    unsigned int GetMass() const {return Mass;}
    Vector2D GetVelocity() const {return Velocity;}
    void SetVelocity(const Vector2D& _Velocity)  {Velocity = _Velocity; }\
    bool IsCollisionProcessed() const {return bIsCollisionProcessed;}
protected:
    Vector2D Velocity;
    unsigned int Mass;
    bool bIsCollisionProcessed = false;
    float AbilityDropRate = 0;
    float ShieldRate = 1;
};
