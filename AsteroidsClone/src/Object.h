#pragma once
#include "Framework.h"
#include "Geometry.h"
struct Vector2D;

class Object
{
public:
	Object() {};
	virtual ~Object() = default;
	virtual void Tick(float DeltaTime) = 0;
	virtual bool IsIntersected(const Object* Obj);
	virtual void Draw(const Vector2D& CameraLocation);
	Geometry GetGeometry() const {return _Geometry;}
	bool IsVisible(const Vector2D& CameraPosition);
	virtual void OnCollisionDetected(Object* Obj) = 0;
	bool IsPendingKill() const { return PendingKill;}
	void SetPendingKill() {PendingKill = true;}
	void SetWorldLocation(const Vector2D& Location) {_Geometry.SetWorldLocation(Location);}
protected:
	bool PendingKill = false;
	bool _IsVisible = false;
	Sprite* _Sprite;
	Geometry _Geometry;
	float Speed;

};
