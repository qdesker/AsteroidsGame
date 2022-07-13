#include "Game.h"
#include "Constants.h"
#include "SmallAsteroid.h"
#include "BigAsteroid.h"
#include "Bullet.h"
#include "Player.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "HomingMissile.h"

std::vector<Object*> Game::GameObjects = std::vector<Object*>();
std::vector<Object*> Game::ObjectsToSpawn = std::vector<Object*>();
int Game::NumAsteroids = 0;

Cursor::Cursor()
{
	_Sprite = createSprite("data\\reticle.png");

	if (!_Sprite)
	{
		delete this;
		return;
	}
	int SpriteSizeWidht = 0;
	int SpriteSizeHeight = 0;
	getSpriteSize(_Sprite,SpriteSizeWidht, SpriteSizeHeight);
	CursorOverlapRadius = std::max(SpriteSizeHeight, SpriteSizeWidht);
}

void Cursor::Draw(const Vector2D& CursorLocalLocation) const
{
	drawSprite(_Sprite, CursorLocalLocation.X, CursorLocalLocation.Y);
}

void Game::PreInit(int& width, int& height, bool& fullscreen)
{
	width =	WINDOW_WIDTH;
	height = WINDOW_HEIGHT;
	fullscreen = FULLSCREEN;
	srand(42);
}

bool Game::Init()
{
	NumAsteroids = NUM_ASTEROIDS;
	showCursor(false);
	_Cursor = new Cursor();
	if (!_Cursor)
	{
		Close();
	}
	CursorOverlapRadius = _Cursor->GetCursorOverlapRadius();
	_Cursor->Draw(CursorLocalLocation);
	Player* P = new Player(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	_Player = P;
	GameObjects.push_back(P);
	return true;
}

void Game::Close()
{
}

bool Game::Tick()
{
	float DeltaTime = (getTickCount() - PreviousTickTimeEnd) / 1000.f;
	CameraLocation = Vector2D(_Player->GetGeometry().GetWorldLocation().X - WINDOW_WIDTH/ 2,
		_Player->GetGeometry().GetWorldLocation().Y - WINDOW_HEIGHT / 2);
	//Game loo
	for(Object* Obj : ObjectsToSpawn)
	{
		GameObjects.push_back(Obj);
	}
	ObjectsToSpawn.clear();

	if (TimeToAsteroidSpawn <= 0)
	{
		SpawnAsteroid();
		TimeToAsteroidSpawn = AsteroidSpawnInterval;
	}
	else
	{
		TimeToAsteroidSpawn -= DeltaTime;
	}

	std::vector<Object*> ToDelete;
	auto It = GameObjects.begin();
	while (It != GameObjects.end())
	{
		if ((*It)->IsPendingKill())
		{
			Object* Obj = *It;
			ToDelete.push_back(Obj);
			It = GameObjects.erase(It);
		}
		else
		{
			(*It)->Tick(DeltaTime);
			++It;
		}
	}

	for (Object* Obj : ToDelete)
	{
		delete Obj;
		Obj = nullptr;
	}

	for (Object* Obj1 : GameObjects)
	{
		for (Object* Obj2 : GameObjects)
		{
			if(Obj1 && Obj2 && Obj1 != Obj2 && Obj1->IsIntersected(Obj2))
			{
				Obj1->OnCollisionDetected(Obj2);
			}
		}
	}

	for (Object* Obj : GameObjects)
	{
		if (Obj->IsVisible(CameraLocation))
		{
			Obj->Draw(CameraLocation);
		}
	}
	PreviousTickTimeEnd = getTickCount();
	_Cursor->Draw(CursorLocalLocation);
	return false;
}

void Game::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	CursorLocalLocation = Vector2D(x, y);
}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	switch (button)
	{
	case FRMouseButton::LEFT:
		if (!isReleased)
		{
			Vector2D CursorWorldLocation = Vector2D(CursorLocalLocation.X + CameraLocation.X, CursorLocalLocation.Y + CameraLocation.Y);
			if (ActiveBullets.size() >= NUM_AMMO)
			{
				Bullet* _Bullet = ActiveBullets.front();
				ActiveBullets.pop();
				_Bullet->SetPendingKill();
			}
			Bullet* _Bullet = _Player->Shoot(CursorWorldLocation);
			if(!_Bullet)
			{
				return;
			}
			GameObjects.push_back(_Bullet);
			ActiveBullets.push(_Bullet);
		}
		break;

	case FRMouseButton::RIGHT:
		if (isReleased)
		{
			return;
		}
		for (Object* Obj : GameObjects)
		{
			if(IsCursorIntersectedWithObject(Obj))
			{
				Asteroid* _Asteroid = dynamic_cast<Asteroid*>(Obj);
				if (_Asteroid)
				{
					HomingMissile* Missile = _Player->ShootHomingMissile(_Asteroid);
					ObjectsToSpawn.push_back(Missile);
					return;
				}
			}
		}
		break;

	default:
		break;
	}
}

void Game::onKeyPressed(FRKey k)
{
	switch (k)
	{
	case FRKey::UP:
		InputAxis.Y -= 1;
		break;
	case FRKey::DOWN:
		InputAxis.Y += 1;
		break;
	case FRKey::LEFT:
		InputAxis.X -= 1;
		break;
	case FRKey::RIGHT:
		InputAxis.X += 1;
		break;
	default:
		InputAxis = Vector2D(0, 0);
		break;
	}
	_Player->ApplyMovement(InputAxis);
}

void Game::onKeyReleased(FRKey k)
{
	switch (k)
	{
	case FRKey::UP:
		InputAxis.Y += 1;
		break;
	case FRKey::DOWN:
		InputAxis.Y -= 1;
		break;
	case FRKey::LEFT:
		InputAxis.X += 1;
		break;
	case FRKey::RIGHT:
		InputAxis.X -= 1;
		break;
	default:
		InputAxis = Vector2D(0, 0);
		break;
	}
	_Player->ApplyMovement(InputAxis);
}

const char* Game::GetTitle()
{
	return "asteroids";
}

void Game::SpawnAsteroid()
{
	if (NumAsteroids <= 0)
	{
		return;
	}
	if (NumAsteroids > NUM_ASTEROIDS)
	{
		NumAsteroids = NUM_ASTEROIDS;
	}
	int AsteroidType = rand() % 2;
	Vector2D SpawnLocation = Vector2D(CameraLocation.X + rand() % static_cast<int>(CameraLocation.X + WINDOW_WIDTH),CameraLocation.Y + rand() % (static_cast<int>(CameraLocation.Y + WINDOW_HEIGHT)));
	Vector2D PlayerLocation = _Player->GetGeometry().GetWorldLocation();
	unsigned int NoSpawnZoneRadius = _Player->GetNoSpawnZoneRadius();
	while(pow(NoSpawnZoneRadius, 2) >
		pow(SpawnLocation.X - PlayerLocation.X,2) + pow(SpawnLocation.Y - PlayerLocation.Y,2))
	{
		SpawnLocation = Vector2D(rand() % static_cast<int>(CameraLocation.X + WINDOW_WIDTH),rand() % static_cast<int>(CameraLocation.Y + WINDOW_HEIGHT));
	}
	Vector2D Direction = Vector2D(-1.f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2), -1.f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2));
	if(AsteroidType == 0)
	{
		GameObjects.push_back(new SmallAsteroid(SpawnLocation, Direction));
	}
	else
	{
		GameObjects.push_back(new BigAsteroid(SpawnLocation, Direction));
	}
	NumAsteroids--;
}

bool Game::IsCursorIntersectedWithObject(Object* Obj) const
{
	Vector2D Temp = CursorLocalLocation - Obj->GetGeometry().GetLocalLocation(CameraLocation);
	return std::hypot(Temp.X, Temp.Y) < CursorOverlapRadius + Obj->GetGeometry().GetOverlapRadius();
}

void Game::SpawnObject(Object* Obj)
{
	ObjectsToSpawn.push_back(Obj);
}

void Game::AddAsteroidsNum()
{
	NumAsteroids++;
}

Game::~Game()
{
}
