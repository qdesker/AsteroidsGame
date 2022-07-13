#include "Geometry.h"

#include <algorithm>

#include "Constants.h"

Geometry::Geometry(const Vector2D& _SpriteSize, const Vector2D& _WorldLocation)
{
    SpriteSize = _SpriteSize;
    OverlapRadius = std::max(SpriteSize.X, SpriteSize.Y ) / 2;
    WorldLocation = _WorldLocation;
}

Vector2D Geometry::GetLocalLocation(const Vector2D& CameraLocation) const
{
    return Vector2D(WorldLocation.X - CameraLocation.X, WorldLocation.Y - CameraLocation.Y);
}

void Geometry::SetWorldLocation(const Vector2D& _WorldLocation)
{
    WorldLocation.X = _WorldLocation.X;
    WorldLocation.Y = _WorldLocation.Y;
}
