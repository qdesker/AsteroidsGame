#include "Player.h"

#include "Booster.h"
#include "Bullet.h"
#include "Constants.h"
#include "HomingMissile.h"
#include "SmallAsteroid.h"

Player::Player(const Vector2D& Location) : Object()
{

    _Sprite = createSprite("data\\spaceship.png");

    if (!_Sprite)
    {
        return;
    }

    int SpriteSizeWidht = 0;
    int SpriteSizeHeight = 0;
    getSpriteSize(_Sprite,SpriteSizeWidht, SpriteSizeHeight);
    _Geometry = Geometry(Vector2D(SpriteSizeWidht, SpriteSizeHeight), Location);

    drawSprite(_Sprite, _Geometry.GetWorldLocation().X, _Geometry.GetWorldLocation().Y);
    Speed = PLAYER_SPEED;
    FrictionForce = FRICTION_FORCE;
    NoSpawnZoneRadius = NO_SPAWN_ZONE_RADIUS;
    ShootCooldown = SHOOT_COOLDOWN;
}

void Player::Tick(float DeltaTime)
{
    TimeToShoot -= DeltaTime;
    if(TimeToShoot <= 0)
    {
        TimeToShoot = 0;
    }
    if(AxisMovement == Vector2D(0, 0))
    {
        ApplyFriction(FrictionForce * DeltaTime);
    }
    else
    {
        Motion = Speed * AxisMovement * DeltaTime;
    }
    _Geometry.GetWorldLocation() += Motion;
    if (ShieldDuration > 0 && CurrentBooster)
    {
        CurrentBooster->SetWorldLocation(_Geometry.GetWorldLocation());
        ShieldDuration -= DeltaTime;
    }
    else if (AutoShootDuration > 0 && CurrentBooster)
    {
        CurrentBooster->SetWorldLocation(_Geometry.GetWorldLocation());
        AutoShootDuration -= DeltaTime;
    }
    else if(IsHomingMissileEquiped && CurrentBooster)
    {
        CurrentBooster->SetWorldLocation(_Geometry.GetWorldLocation());
    }
    else if (CurrentBooster)
    {
        CurrentBooster->SetPendingKill();
        CurrentBooster = nullptr;
    }
}

void Player::ApplyFriction(float Limit)
{
    if(Motion.Length() > Limit)
    {
        Motion -= Motion * Limit;
    }
    else
    {
        Motion = Vector2D(0, 0);
    }
}

void Player::OnCollisionDetected(Object* Obj)
{
    Asteroid* _Asteroid = dynamic_cast<Asteroid*>(Obj);
    if (!_Asteroid)
    {
        return;
    }
    PendingKill = true;
}

Bullet* Player::Shoot(const Vector2D& CrossHairLocation)
{
    if(TimeToShoot > 0)
    {
        return nullptr;
    }
    TimeToShoot = ShootCooldown;
    Vector2D PlayerLocation = _Geometry.GetWorldLocation();
    Vector2D _BulletDirection = Vector2D(CrossHairLocation.X - PlayerLocation.X, CrossHairLocation.Y - PlayerLocation.Y).Norm();
    return new Bullet(_BulletDirection, PlayerLocation);
}

void Player::ActivateBooster(Booster* _Booster)
{
    BoosterType _BoosterType = _Booster->GetBoosterType();
    switch (_BoosterType)
    {
    case BoosterType::Shield:
        AutoShootDuration = 0;
        ShieldDuration = SHIELD_DURATION;
        break;
    case BoosterType::AutoShooting:
        ShieldDuration = 0;
        AutoShootDuration = SHIELD_DURATION;
        break;
    case BoosterType::HomingMissile:
        IsHomingMissileEquiped = true;
        break;
        default:
            break;
    }
    if (CurrentBooster)
    {
        CurrentBooster->SetPendingKill();
    }
    CurrentBooster = _Booster;
}

HomingMissile* Player::ShootHomingMissile(Asteroid* _Asteroid)
{
    IsHomingMissileEquiped = false;
    if(CurrentBooster)
    {
        CurrentBooster->SetPendingKill();
        CurrentBooster = nullptr;
    }
    return new HomingMissile(_Geometry.GetWorldLocation(), _Asteroid);
}

void Player::ApplyMovement(const Vector2D& InputAxis)
{
    AxisMovement = InputAxis;
}

void Player::Draw(const Vector2D& CameraLocation)
{
    Object::Draw(CameraLocation);
}
