#include "pch.h"
#include "ProjectileManager.h"

#include "AutoAttack.h"
#include "SkillShotProjectile.h"

#include "Projectile.h"

#include "Champion.h"

#include "OrientationManager.h"

// STATICS

std::vector<Unit*>* ProjectileManager::c_Units{nullptr};

std::vector<Unit*>* ProjectileManager::GetUnits()
{
    return c_Units;
}

void ProjectileManager::ChangeUnits(std::vector<Unit*>* units)
{
    c_Units = units;
    SkillShotProjectile::InitUnitVector(units);
}

// NON STATICS

ProjectileManager::ProjectileManager(int reserveLockOn, int reserveSkillShot)
    :m_LastMousePos{0,0}
    ,m_LastShooter{ nullptr }
    ,m_pAutoAttackDefault{new AutoAttack(Point2f{0,0},nullptr)}
    ,m_LastAutoAttackUsed{nullptr}
    ,m_IsShiftHeld{false}
{
    m_LastAutoAttackUsed = m_pAutoAttackDefault;
}

ProjectileManager::~ProjectileManager()
{

    for (int i{ 0 }; i < m_Projectiles.size(); i++)
    {
        m_Projectiles.pop_back();
    }
    delete m_pAutoAttackDefault;

}

void ProjectileManager::PushBackLockOn(const Point2f& startingPos, Unit* target, float damage, float speed)
{
    
}

void ProjectileManager::PushBackAutoAttack(const Point2f& startingPos, Unit* target, float damage, float speed)
{
    
}

void ProjectileManager::PushBackAutoAttack(AutoAttack* autoAttack)
{
    m_Projectiles.push_back(autoAttack);
}

void ProjectileManager::PushBackSkillShot(const Point2f& startingPos, const Point2f& destination, float damage, float speed)
{
    PushBack(new SkillShotProjectile{ startingPos, destination});
    //std::cout << "PUSHBACK BOO234M\n";
}

void ProjectileManager::PushBack(LockOnProjectile* proj)
{
   
    delete proj;
}

void ProjectileManager::PushBack(SkillShotProjectile* proj)
{
      m_Projectiles.push_back(proj);
}

void ProjectileManager::DrawAll() const
{
    // Draw projectiles
    for (int i{ 0 }; i < m_Projectiles.size(); i++)
    {
        if (m_Projectiles[i] == nullptr) continue;
        m_Projectiles[i]->Draw();
    }

}

void ProjectileManager::UpdateAll(float elapsedSec)
{
    // Update projectiles
    for (int i{ 0 }; i < m_Projectiles.size(); i++)
    {
        if (m_Projectiles[i] == nullptr) continue;
            m_Projectiles[i]->Update(elapsedSec);
            if (m_Projectiles[i]->ReadyToDelete())
            {
                delete m_Projectiles[i];
                m_Projectiles[i] = nullptr;
            }
    }

    m_Projectiles.erase(std::remove(m_Projectiles.begin(), m_Projectiles.end(), nullptr), 
        m_Projectiles.end());


    // Keep this line
    TryAutoAttack(m_LastMousePos, m_LastShooter, false);
}

bool ProjectileManager::TryAutoAttack(const Point2f& mousePos, Champion* shooter, bool isNewInput)
{
    if (shooter == nullptr)
    {
        return false;
    }

    const Uint8* pStates = SDL_GetKeyboardState(nullptr);
    if (isNewInput)
    {
        m_IsShiftHeld = pStates[SDL_SCANCODE_LSHIFT];
    }

    for (size_t i{ 0 }; i < c_Units->size(); ++i)
    {
        if (m_IsShiftHeld)
        {
            Unit* closestUnit{ shooter->GetClosestUnit(c_Units) };
            if (closestUnit == nullptr) return false;
            ShooterLogic(shooter, closestUnit,m_LastAutoAttackUsed);
            break;
        }
        else if (c_Units->at(i)->IsOverlapping(mousePos))
        {
            ShooterLogic(shooter, c_Units->at(i),m_LastAutoAttackUsed);
            break;
        }
    }
    if (&mousePos != &m_LastMousePos)
    {
        m_LastMousePos = mousePos;
    }
    if (shooter != m_LastShooter)
    {
        m_LastShooter = shooter;
    }
    return true;
}

bool ProjectileManager::TryAutoAttack(const Point2f& mousePos, Champion* shooter, AutoAttack* autoAttack, bool isNewInput)
{
    if (shooter == nullptr)
    {
        return false;
    }

    const Uint8* pStates = SDL_GetKeyboardState(nullptr);
    if (isNewInput)
    {
        m_IsShiftHeld = pStates[SDL_SCANCODE_LSHIFT];
    }

    for (size_t i{ 0 }; i < c_Units->size(); ++i)
    {
        if (m_IsShiftHeld)
        {
            Unit* closestUnit{ shooter->GetClosestUnit(c_Units) };
            if (closestUnit == nullptr) return false;
            ShooterLogic(shooter, closestUnit,autoAttack);
            m_LastAutoAttackUsed = autoAttack;
            break;
        }
        else if (c_Units->at(i)->IsOverlapping(OrientationManager::GetWorldLocation(mousePos)))
        {
            ShooterLogic(shooter, c_Units->at(i),autoAttack);
            m_LastAutoAttackUsed = autoAttack;
            break;
        }
    }
    if ((mousePos.x != m_LastMousePos.x) || (mousePos.y != m_LastMousePos.y))
    {
        m_LastMousePos = OrientationManager::GetWorldLocation(mousePos);
    }
    if (shooter != m_LastShooter)
    {
        m_LastShooter = shooter;
    }
    return true;
}

void ProjectileManager::ShooterLogic(Champion* shooter, Unit* unit)
{
    ShooterLogic(shooter, unit, m_pAutoAttackDefault);
}

void ProjectileManager::ShooterLogic(Champion* shooter, Unit* unit, AutoAttack* autoAttack)
{
    float distance{ Vector2f{shooter->GetTransform().location - unit->GetTransform().location}.Length() };
    if (shooter->GetAutoAttackRangeRadius() < distance)
    {
        return;
    }
    if (shooter->IsAAReadyAndReset())
    {
        PushBackAutoAttack(autoAttack->Clone(shooter->GetTransform().location, unit));
    }
    shooter->StopMovement();
    shooter->RotateTowards(unit->GetTransform().location);
}
