#include "Bullet.h"

#include <xlocale>

#include "Asteroid.h"
#include "Constants.h"
#include "Player.h"

Bullet::Bullet(const Vector2D& _Direction, const Vector2D& _Location) : Object()
{
    _Sprite = createSprite("data\\bullet.png");

    if (!_Sprite)
    {
        return;
    }

    int SpriteSizeWidht = 0;
    int SpriteSizeHeight = 0;
    getSpriteSize(_Sprite,SpriteSizeWidht, SpriteSizeHeight);
    _Geometry = Geometry(Vector2D(SpriteSizeWidht, SpriteSizeHeight), _Location);
    Direction = _Direction;
    Speed = BULLET_SPEED;
}

Bullet::~Bullet()
{
}

void Bullet::Tick(float DeltaTime)
{
    _Geometry.GetWorldLocation() += Speed * Direction * DeltaTime;
}

void Bullet::OnCollisionDetected(Object* Obj)
{
    Asteroid* _Asteroid = dynamic_cast<Asteroid*>(Obj);

    if (_Asteroid)
    {
        PendingKill = true;
    }
}

void Bullet::Draw(const Vector2D& CameraLocation)
{
    Object::Draw(CameraLocation);
}


