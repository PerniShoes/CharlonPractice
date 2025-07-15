#include "pch.h"
#include "Volley.h"
#include <cmath>

#include <iostream>
#include "utils.h"

#include "Timer.h"

#include "ProjectileManager.h"

Volley::Volley(const std::string& key,const Point2f& championLocationRef)
    :Ability(Type::skillshot,key, "Volley", 1, 3)
    ,m_ChampionLocationRef{championLocationRef}
    ,m_LastMousePos{}
    ,m_IsHoldingDown{false}
    ,m_Range{300}
    ,m_ProjAmount{4}
    ,m_AngleBetweenProj{5}
    ,m_Projectiles{}
    
{


};

Volley::~Volley()
{
    for (int i{0}; i < m_ProjAmount; i++)
    {
        if (m_Projectiles.size() == 0) break;
        delete m_Projectiles.back();
        m_Projectiles.pop_back();
    }
};

void Volley::Draw() const
{
    if (m_IsHoldingDown)
    {
        
        utils::SetColor(Color4f{0,1,1,1});
        for (int i{0}; i < m_ProjAmount; i++)
        {
            if (m_Projectiles.size() == 0)break;
            utils::DrawLine(m_ChampionLocationRef,*m_Projectiles[i]);
        }
    }
};

bool Volley::OnPress(const Point2f& mousePos)
{
    if (m_IsHoldingDown)
    {

    }
    else
    {
        m_IsHoldingDown = true;
    }
    return false;

};

bool Volley::OnHolding(float elapsedSec, const Point2f& mousePos)
{
    m_LastMousePos = mousePos;
    return false;

};

bool Volley::OnRelease(const Point2f& mousePos)
{
    m_IsHoldingDown = false;
    if (m_Cooldown->IsDone())
    {
        for (int i{0}; i < m_ProjAmount; i++)
        {
            if (m_Projectiles.size() == 0)break;
            c_ProjectileManagerRef->PushBackSkillShot(m_ChampionLocationRef,*m_Projectiles[i],20,100);
        }
        m_Cooldown->ResetTimer();
        return true;
    }
    return false;

};

void Volley::Update(float elapsedSec)
{
    SetupProjectiles();
    m_Cooldown->Update(elapsedSec);

};

void Volley::DrawIcon()const
{


};

void Volley::SetupProjectiles()
{

    for (int i{0}; i < m_ProjAmount; i++)
    {
        if (m_Projectiles.size() == 0) break;
        delete m_Projectiles.back();
        m_Projectiles.pop_back();
    }


    int halfProjAmount{m_ProjAmount / 2};
    float radians{m_AngleBetweenProj * float(M_PI / 180)};

    Vector2f direction{m_LastMousePos - m_ChampionLocationRef};
    float originalAngle{atan2(direction.y , direction.x)};
    direction = direction.Normalized();

    int tempIndx{};
    if (m_ProjAmount % 2 == 0)
    {
        originalAngle -= radians/2.0f;
    }
    for (int i{0}; i < m_ProjAmount; i++)
    {
        tempIndx = i;
        if (i > halfProjAmount)
        {
            if (radians > 0) { radians *= -1; }
            tempIndx -= halfProjAmount;
        }

        Vector2f tempDirection{
         direction.Length() * cos(originalAngle + radians * tempIndx)
        ,direction.Length() * sin(originalAngle + radians * tempIndx)};
        m_Projectiles.push_back(new Point2f{m_ChampionLocationRef + tempDirection * m_Range});
    }

}