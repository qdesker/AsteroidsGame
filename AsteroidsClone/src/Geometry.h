#pragma once
#include "Vector2D.h"

class Geometry
{
public:
    Geometry() {}
    Geometry(const Vector2D& _SpriteSize, const Vector2D& WorldLocation);

    Vector2D GetSpriteSize() const {return SpriteSize;}

    Vector2D& GetWorldLocation() {return WorldLocation;}

    unsigned GetOverlapRadius() const {return OverlapRadius;}

    Vector2D GetLocalLocation(const Vector2D& CameraLocation) const;

    void SetWorldLocation(const Vector2D& _WorldLocation);

private:
    Vector2D SpriteSize;
    Vector2D WorldLocation;

    unsigned int OverlapRadius = 0;
};
