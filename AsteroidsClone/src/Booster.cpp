#include "Booster.h"

#include <xlocinfo.h>

#include "Asteroid.h"
#include "Bullet.h"
#include "Constants.h"
#include "Game.h"
#include "Player.h"

Booster::Booster(BoosterType InBoosterType, const Vector2D& Location)
{
    _BoosterType = InBoosterType;
    switch (_BoosterType)
    {
    case BoosterType::Shield:
        _Sprite = createSprite("data\\shield.png");
        break;
    case BoosterType::HomingMissile:
        _Sprite = createSprite("data\\missile.png");
        break;
    case BoosterType::AutoShooting:
        _Sprite = createSprite("data\\autoshoot.png");
        break;
    default:
        delete this;
        break;
    }
    int SpriteSizeWidht = 0;
    int SpriteSizeHeight = 0;
    getSpriteSize(_Sprite,SpriteSizeWidht, SpriteSizeHeight);
    _Geometry = Geometry(Vector2D(SpriteSizeWidht, SpriteSizeHeight), Location);
}

Booster::~Booster()
{
}

void Booster::Tick(float DeltaTime)
{
    if(bIsActivated)
    {
        AutoShootTimeOut -= DeltaTime;
    }
}

void Booster::OnCollisionDetected(Object* Obj)
{
    if(PendingKill)
    {
        return;
    }
    Player* _Player = dynamic_cast<Player*>(Obj);
    if (_Player && !bIsActivated)
    {
        switch (_BoosterType)
        {
        case BoosterType::Shield:
            _Sprite = createSprite("data\\circle.png");
            // Hardcoded hack
            _Geometry = Geometry(Vector2D(150, 150), _Geometry.GetWorldLocation());
            break;
        case BoosterType::AutoShooting:
            _Sprite = createSprite("data\\dot.png");
            _Geometry = Geometry(Vector2D(400, 400), _Geometry.GetWorldLocation());
            break;
        case BoosterType::HomingMissile:
            _Geometry = Geometry(Vector2D(1, 1), _Geometry.GetWorldLocation());
            break;
        default:
            return;
        }
        bIsActivated = true;
        _Player->ActivateBooster(this);
        return;
    }
    Asteroid* _Asteroid = dynamic_cast<Asteroid*>(Obj);
    if (_Asteroid && bIsActivated && _BoosterType == BoosterType::AutoShooting)
    {
        if (AutoShootTimeOut <= 0)
        {
            Vector2D AsteroidLocation = _Asteroid->GetGeometry().GetWorldLocation();
            Vector2D BoosterLocation = _Geometry.GetWorldLocation();
            Vector2D _BulletDirection = Vector2D(AsteroidLocation.X - BoosterLocation.X, AsteroidLocation.Y - BoosterLocation.Y).Norm();
            Game::SpawnObject(new Bullet(_BulletDirection, BoosterLocation));
            AutoShootTimeOut = 0.4;
        }
    }
}

void Booster::Draw(const Vector2D& CameraLocation)
{
    Object::Draw(CameraLocation);
}
