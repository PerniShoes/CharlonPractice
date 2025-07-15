#pragma once

#include "Ability.h"
#include <vector>


class Volley final : public Ability
{
public:
    Volley(const std::string& key, const Point2f& championLocationRef);
    Volley(const Volley& volley) = delete;
    Volley& operator = (const Volley& volley) = delete;
    Volley(const Volley&& volley) = delete;
    Volley& operator = (const Volley&& volley) = delete;
    ~Volley();


	void Draw() const override;
	bool OnPress(const Point2f& mousePos) override;
	bool OnHolding(float elapsedSec, const Point2f& mousePos) override;
	bool OnRelease(const Point2f& mousePos) override;
	void Update(float elapsedSec) override;
    
    void SetupProjectiles();

private:
    const Point2f& m_ChampionLocationRef;
    Point2f m_LastMousePos;

    bool m_IsHoldingDown;
    float m_Range;

    int m_ProjAmount;
    float m_AngleBetweenProj;
    std::vector<Point2f*> m_Projectiles;

    void DrawIcon() const override;

};

