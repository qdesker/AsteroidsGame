#pragma once
#include "Framework.h"
#include "Vector2D.h"
#include <vector>
#include <queue>

#include "Geometry.h"

class Object;
class Player;
class Bullet;

struct Cursor
{
	Cursor();
	void Draw(const Vector2D& CursorLocation) const;
	float GetCursorOverlapRadius() const {return CursorOverlapRadius;}
private:
	Sprite* _Sprite;
	float CursorOverlapRadius = 0;
};

class Game : public Framework
{
public:
	void PreInit(int& width, int& height, bool& fullscreen) override;

	// return : true - ok, false - failed, application will exit
	bool Init() override;

	void Close() override;

	// return value: if true will exit the application
	bool Tick() override;

	// param: xrel, yrel: The relative motion in the X/Y direction
	// param: x, y : coordinate, relative to window
	void onMouseMove(int x, int y, int xrelative, int yrelative) override;

	void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	void onKeyPressed(FRKey k) override;

	void onKeyReleased(FRKey k) override;

	const char* GetTitle() override;

	void SpawnAsteroid();

	bool IsCursorIntersectedWithObject(Object* Obj) const;

	// hack
	static void SpawnObject(Object* Obj);
	static void AddAsteroidsNum();

	 ~Game();
private:
	Player* _Player = nullptr;
	static std::vector<Object*> GameObjects;
	static std::vector<Object*> ObjectsToSpawn;
	unsigned int PreviousTickTimeEnd = 0;
	float AsteroidSpawnInterval = 0.5;
	float TimeToAsteroidSpawn = 0;
	Vector2D InputAxis;
	Vector2D CameraLocation;
	Vector2D CursorLocalLocation;
	Cursor* _Cursor = nullptr;
	static int NumAsteroids;
	std::queue<Bullet*> ActiveBullets;
	float CursorOverlapRadius = 0;
};
