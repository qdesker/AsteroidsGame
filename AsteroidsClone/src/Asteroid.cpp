#include "Asteroid.h"
#include <cmath>

#include "Booster.h"
#include "Bullet.h"
#include "Constants.h"
#include "Game.h"
#include "HomingMissile.h"
#include "Player.h"

Asteroid::Asteroid() : Object()
{
    AbilityDropRate = ABILITY_PROBABILITY;
}

Asteroid::~Asteroid()
{
    float Probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    if (Probability <= AbilityDropRate)
    {
        BoosterType _BoosterType = static_cast<BoosterType>(rand() % 3);
        Game::SpawnObject(new Booster(_BoosterType, _Geometry.GetWorldLocation()));
    }
}

void Asteroid::Tick(float DeltaTime)
{
    bIsCollisionProcessed = false;
    _Geometry.GetWorldLocation() += Velocity * DeltaTime * ShieldRate;
    ShieldRate = 1;
}

void Asteroid::OnCollisionDetected(Object* Obj)
{
    if(PendingKill)
    {
        return;
    }
    Asteroid* _Asteroid = dynamic_cast<Asteroid*>(Obj);
    if (_Asteroid && !_Asteroid->IsCollisionProcessed())
    {
        float Mass1 = Mass;
        float Mass2 = _Asteroid->GetMass();
        float MassSum = Mass1 + Mass2;
        Vector2D Location1 = _Geometry.GetWorldLocation();
        Vector2D Location2 = _Asteroid->GetGeometry().GetWorldLocation();
        float NewDirection = pow((Location1 - Location2).Length(), 2);
        Vector2D Velocity1 = Velocity;
        Vector2D Velocity2 = _Asteroid->GetVelocity();
        Vector2D NewVelocity1 = Velocity1 - 2 * Mass2 / MassSum * (Velocity1 - Velocity2).Dot(Location1 - Location2) / NewDirection * (Location1 - Location2);
        Vector2D NewVelocity2 = Velocity2 - 2 * Mass1 / MassSum * (Velocity2 - Velocity1).Dot(Location2 - Location1) / NewDirection * (Location2 - Location1);
        Velocity = NewVelocity1;
        _Asteroid->SetVelocity(NewVelocity2);
        bIsCollisionProcessed = true;
        return;
    }
    Player* _Player = dynamic_cast<Player*>(Obj);
    if (_Player)
    {
        PendingKill = true;
        return;
    }

    Bullet* _Bullet = dynamic_cast<Bullet*>(Obj);
    if(_Bullet)
    {
        PendingKill = true;
        return;
    }
    Booster* _Booster = dynamic_cast<Booster*>(Obj);
    if(_Booster && _Booster->IsActivated() && _Booster->GetBoosterType() == BoosterType::Shield)
    {
        ShieldRate = 0;
    }
    HomingMissile* Missile = dynamic_cast<HomingMissile*>(Obj);
    if(Missile)
    {
        PendingKill = true;
        Missile->SetPendingKill();
    }
}
