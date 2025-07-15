#include "pch.h"
#include "Projectile.h"

#include "utils.h"
#include "Unit.h"


// STATICS
bool Projectile::c_IsDrawingHitboxes{ false };
void Projectile::SetDrawingHitboxes(bool state)
{
	c_IsDrawingHitboxes = state;
}
void Projectile::SwitchDrawingHitboxes()
{
	c_IsDrawingHitboxes = !c_IsDrawingHitboxes;
}
bool Projectile::IsDrawingHitboxes()
{
	return c_IsDrawingHitboxes;
}


// NON STATICS
Projectile::Projectile(Type type, const Point2f& startingPos, float damage, float speed, Rectf hitbox)
	:m_Type{ type }
	,m_Transform{ startingPos }
	,m_Speed{ speed }
	,m_Damage{ damage }
	,m_Hitbox{ hitbox }
{
	m_Hitbox.left = -m_Hitbox.width / 2;
	m_Hitbox.bottom = -m_Hitbox.height / 2;

}

Projectile::~Projectile()
{
}

