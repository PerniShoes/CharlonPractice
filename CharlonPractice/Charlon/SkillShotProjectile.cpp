#include "pch.h"
#include "SkillShotProjectile.h"

#include "utils.h"

#include "Unit.h"

#include <iostream>
#include <algorithm>

// STATICS
std::vector<Unit*>* SkillShotProjectile::c_UnitVector{ nullptr };
void SkillShotProjectile::InitUnitVector(std::vector<Unit*>* unitVector)
{
	c_UnitVector = unitVector;
}

// NON STATICS
SkillShotProjectile::SkillShotProjectile(const Point2f& startingPos, const Point2f& destination)
    :Projectile{Type::SkillShot, startingPos, 30.0f, 300.0f,Rectf{0,0,8,8}}
	,m_Destination{destination}
    ,m_ReadyToDelete{false}
{

	if (c_UnitVector == nullptr)
	{
		throw "Uninitialised static member variable.";
	}
}

SkillShotProjectile::~SkillShotProjectile()
{
}

void SkillShotProjectile::Draw() const
{
	if (this == nullptr || m_ReadyToDelete)
	{
		return;
	}

	using namespace utils;

	m_Transform.Push();
	{
		m_Transform.Apply();
		SetColor(Color4f{ 1,0,0,0.8f });
		FillEllipse(Point2f{0,0}, m_Hitbox.width / 2, m_Hitbox.height / 2);
		if (c_IsDrawingHitboxes)
		{
			SetColor(Color4f{ 1,1,0,1 });
			DrawRect(m_Hitbox, 2);
		}
	}
	m_Transform.Pop();
}

void SkillShotProjectile::Update(float elapsedSec)
{
	if (this == nullptr || m_ReadyToDelete)
	{
		return;
	}
	Vector2f directionVector{m_Destination - m_Transform.location};
	Vector2f direction = directionVector.Normalized();
	m_Transform.location += direction * m_Speed * elapsedSec;
	for (size_t i{ 0 }; i < c_UnitVector->size(); ++i)
	{
		if (c_UnitVector->at(i)->IsOverlapping(Rectf{m_Transform.location.x,m_Transform.location.y,m_Hitbox.width,m_Hitbox.height}))
		{
			c_UnitVector->at(i)->TakeDamage(m_Damage);
			m_ReadyToDelete = true;
		}
	}
	if (directionVector.Length() < m_Speed * elapsedSec)
	{
		m_ReadyToDelete = true;
	}
}

bool SkillShotProjectile::ReadyToDelete() const
{
    return m_ReadyToDelete;
}
