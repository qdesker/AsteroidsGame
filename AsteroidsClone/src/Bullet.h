#pragma once
#include "Object.h"

class Bullet : public Object
{
public:
    Bullet(const Vector2D& _Direction, const Vector2D& _Location);
    ~Bullet() override;
    void Tick(float DeltaTime) override;
    void OnCollisionDetected(Object* Obj) override;
    void Draw(const Vector2D& CameraLocation) override;

private:
    Vector2D Direction;
};
