#include "HomingMissile.h"

#include "Constants.h"

HomingMissile::HomingMissile(const Vector2D& Location, Asteroid* InAsteroid)
{
    _Sprite = createSprite("data\\missile.png");

    if (!_Sprite)
    {
        return;
    }

    int SpriteSizeWidht = 0;
    int SpriteSizeHeight = 0;
    getSpriteSize(_Sprite,SpriteSizeWidht, SpriteSizeHeight);
    _Geometry = Geometry(Vector2D(SpriteSizeWidht, SpriteSizeHeight), Location);

    drawSprite(_Sprite, _Geometry.GetWorldLocation().X, _Geometry.GetWorldLocation().Y);
    Speed = HOMING_MISSILE_SPEED;
    _Asteroid = InAsteroid;
}

void HomingMissile::Tick(float DeltaTime)
{
    if (!_Asteroid)
    {
        PendingKill = true;
    }
    Vector2D AsteroidLocation = _Asteroid->GetGeometry().GetWorldLocation();
    Vector2D MissileLocation = _Geometry.GetWorldLocation();
    Vector2D _MissleDirection = Vector2D(AsteroidLocation.X - MissileLocation.X, AsteroidLocation.Y - MissileLocation.Y).Norm();

    _Geometry.GetWorldLocation() += _MissleDirection * Speed * DeltaTime;
}

void HomingMissile::OnCollisionDetected(Object* Obj)
{

}
