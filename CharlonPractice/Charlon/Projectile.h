#pragma once

#include "Transform.h"
class Unit;

class Projectile
{
	// STATICS
public:
	static void SetDrawingHitboxes(bool state);
	static void SwitchDrawingHitboxes();
	static bool IsDrawingHitboxes();
protected:
	static bool c_IsDrawingHitboxes;

	// NON-STATICS
public:
	enum class Type
	{
		LockOn, SkillShot
	};
	Projectile(Type type, const Point2f& startingPos, float damage = 10.f, float speed = 300.f, Rectf hitbox = Rectf{ 0,0,15,8 });
	Projectile(const Projectile& Projectile) = delete;
	Projectile& operator=(const Projectile& Projectile) = delete;
	Projectile(Projectile&& Projectile) = delete;
	Projectile& operator=(Projectile&& Projectile) = delete;
	virtual ~Projectile();

	virtual void Draw() const = 0;
	virtual void Update(float elapsedSec) = 0;
	virtual bool ReadyToDelete() const = 0;

protected:
	Type m_Type;
	Transform m_Transform;
	float m_Speed;
	float m_Damage;
	Rectf m_Hitbox;

};
