#pragma once
#include "Object.h"

enum class BoosterType
{
    Shield = 0,
    AutoShooting = 1,
    HomingMissile = 2,
    None
};

class Booster : public Object
{
public:
    Booster(BoosterType _BosterType, const Vector2D& Location);
    ~Booster();
    void Tick(float DeltaTime) override;
    void OnCollisionDetected(Object* Obj) override;
    BoosterType GetBoosterType() const {return _BoosterType;}
    bool IsActivated() const {return bIsActivated;}
    void Draw(const Vector2D& CameraLocation) override;
private:
    BoosterType _BoosterType = BoosterType::None;
    bool bIsActivated = false;
    float AutoShootTimeOut = 0.05;
};
