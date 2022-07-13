#include "SmallAsteroid.h"
#include <cstdlib>
#include "Constants.h"
#include "Framework.h"
#include "Game.h"

SmallAsteroid::SmallAsteroid(const Vector2D& Location, const Vector2D& _Direction) : Asteroid()
{
	_Sprite = createSprite("data\\small_asteroid.png");

	if (!_Sprite)
	{
		return;
	}

	int SpriteSizeWidht = 0;
	int SpriteSizeHeight = 0;
	Mass = SMALL_ASTEROID_MASS;

	getSpriteSize(_Sprite,SpriteSizeWidht, SpriteSizeHeight);
	_Geometry = Geometry(Vector2D(SpriteSizeWidht, SpriteSizeHeight), Location);
	Speed = ASTEROIDS_DOWN_LIMIT_SPEED + rand() % static_cast<int>(ASTEROIDS_UPPER_LIMIT_SPEED);
	Velocity = Speed * _Direction;
}

SmallAsteroid::~SmallAsteroid()
{
	_Sprite = nullptr;
	Game::AddAsteroidsNum();
}
