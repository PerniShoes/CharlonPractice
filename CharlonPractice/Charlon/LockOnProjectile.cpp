#include "pch.h"
#include "LockOnProjectile.h"

#include "utils.h"

#include "unit.h"

// NON-STATICS
LockOnProjectile::LockOnProjectile(const Point2f& startingPos,Unit* target, float damage, float speed)
	:Projectile{ Type::LockOn, startingPos, 10.0f, 300.0f,Rectf{0,0,15,8} }
	,m_pTarget{target}
	,m_HasHit{false}
{

}

LockOnProjectile::~LockOnProjectile()
{
}

void LockOnProjectile::Draw() const
{
	if (this == nullptr)
	{
		return;
	}

	using namespace utils;

	m_Transform.Push();
	{
		m_Transform.Apply();
		SetColor(Color4f{ 1,0.75f,0,0.8f });
		FillTriangle(Point2f{ -m_Hitbox.width / 2,m_Hitbox.height / 2 }, Point2f{ m_Hitbox.width / 2,0 }, Point2f{ -m_Hitbox.width / 2,-m_Hitbox.height / 2 });
		if (c_IsDrawingHitboxes)
		{
			SetColor(Color4f{ 1,1,0,1 });
			DrawRect(m_Hitbox, 2);
		}
	}
	m_Transform.Pop();
}

void LockOnProjectile::Update(float elapsedSec)
{
	if (this == nullptr)
	{
		return;
	}

	m_Transform.RotateTowards(m_pTarget->GetTransform().location);
	Vector2f direction{ m_pTarget->GetTransform().location - m_Transform.location };
	direction = direction.Normalized();
	direction *= m_Speed;
	m_Transform.location += direction * elapsedSec;
	
	if (m_pTarget->IsOverlapping(Rectf{ m_Transform.location.x, m_Transform.location.y, m_Hitbox.width,m_Hitbox.height }))
	{
		m_pTarget->TakeDamage(m_Damage);

		m_HasHit = true;
	}
}

bool LockOnProjectile::ReadyToDelete() const
{
	return HasHit();
}
bool LockOnProjectile::HasHit() const
{
	if (this == nullptr)
	{
		return false;
	}
	return m_HasHit;
}
