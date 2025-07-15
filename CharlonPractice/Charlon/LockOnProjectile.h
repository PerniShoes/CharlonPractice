#pragma once
#include"Projectile.h"

class LockOnProjectile : public Projectile
{

// NON STATICS
public:
	LockOnProjectile(const Point2f& startingPos, Unit* target, float damage = 10.f, float speed = 300.f);
	LockOnProjectile(const LockOnProjectile& proj) = delete;
	LockOnProjectile& operator=(const LockOnProjectile& proj) = delete;
	LockOnProjectile(LockOnProjectile&& proj) = delete;
	LockOnProjectile& operator=(LockOnProjectile&& proj) = delete;
	virtual ~LockOnProjectile();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	virtual bool ReadyToDelete() const override;
	virtual bool HasHit() const;

protected:

	Unit* m_pTarget;
	bool m_HasHit;
};

