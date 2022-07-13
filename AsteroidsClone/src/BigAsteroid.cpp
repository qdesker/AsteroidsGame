#include "BigAsteroid.h"

#include "Constants.h"
#include "Game.h"
#include "SmallAsteroid.h"

BigAsteroid::BigAsteroid(const Vector2D& Location, const Vector2D& _Direction)
    : Asteroid()
{
    _Sprite = createSprite("data\\big_asteroid.png");

    if (!_Sprite)
    {
        return;
    }

    int SpriteSizeWidht = 0;
    int SpriteSizeHeight = 0;
    Mass = BIG_ASTEROID_MASS;

    getSpriteSize(_Sprite,SpriteSizeWidht, SpriteSizeHeight);
    _Geometry = Geometry(Vector2D(SpriteSizeWidht, SpriteSizeHeight), Location);
    Speed = ASTEROIDS_DOWN_LIMIT_SPEED + rand() % static_cast<int>(ASTEROIDS_UPPER_LIMIT_SPEED);
    Velocity = Speed * _Direction;
    PartitionTimes = BIG_ASTEROID_PARTITION_TIME;
}

BigAsteroid::~BigAsteroid()
{
    _Sprite = nullptr;

    for (unsigned int i = 0; i < PartitionTimes; ++i)
    {
        Vector2D Direction = Vector2D(-1.f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2), -1.f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2));
        Game::SpawnObject(new SmallAsteroid(_Geometry.GetWorldLocation() + i * 100, Direction));
    }
    Game::AddAsteroidsNum();
}
