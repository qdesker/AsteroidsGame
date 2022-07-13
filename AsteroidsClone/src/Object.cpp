#include "Object.h"
#include "Framework.h"
#include <cmath>
#include "Constants.h"

bool Object::IsIntersected(const Object* Obj)
{
    Vector2D Temp = _Geometry.GetWorldLocation() - Obj->GetGeometry().GetWorldLocation();
    return std::hypot(Temp.X, Temp.Y) < _Geometry.GetOverlapRadius() + Obj->GetGeometry().GetOverlapRadius();
}

void Object::Draw(const Vector2D& CameraLocation)
{
    Vector2D LocalLocation = _Geometry.GetLocalLocation(CameraLocation);
    drawSprite(_Sprite, LocalLocation.X, LocalLocation.Y);
}

bool Object::IsVisible(const Vector2D& CameraPosition)
{
    Vector2D TopLeft = CameraPosition;
    Vector2D BottomRight = Vector2D(CameraPosition.X + WINDOW_WIDTH, CameraPosition.Y + WINDOW_HEIGHT);
    return TopLeft.X <= _Geometry.GetWorldLocation().X && _Geometry.GetWorldLocation().X <= BottomRight.X &&
        TopLeft.Y <= _Geometry.GetWorldLocation().Y && _Geometry.GetWorldLocation().Y <= BottomRight.Y;
}
