#pragma once
#include "Asteroid.h"
#include "Booster.h"
#include "Object.h"

class HomingMissile;
class Bullet;

class Player : public Object
{
public:
    Player(const Vector2D& Location);
    ~Player() = default;
    void Tick(float DeltaTime) override;
    unsigned int GetNoSpawnZoneRadius() const {return NoSpawnZoneRadius;}
    void ApplyMovement(const Vector2D& InputAxis);
    void Draw(const Vector2D& CameraLocation) override;
    void ApplyFriction(float Limit);
    void OnCollisionDetected(Object* Obj) override;
    Bullet* Shoot(const Vector2D& CrossHairLocation);
    void ActivateBooster(Booster* _Booster);
    HomingMissile* ShootHomingMissile(Asteroid* _Asteroid);
private:

    Vector2D CurrentSpeed;
    Vector2D AccumulatedSpeed;
    Vector2D AxisMovement;
    Vector2D Motion;
    float FrictionForce = 0;

    bool bIsMoving = false;
    unsigned int NoSpawnZoneRadius = 0;
    float ShootCooldown = 0;
    float TimeToShoot = 0;
    float ShieldDuration;
    float AutoShootDuration;
    bool IsHomingMissileEquiped = false;
    Booster* CurrentBooster;
};
