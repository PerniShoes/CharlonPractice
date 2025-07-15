#pragma once
#include "Projectile.h"
#include <vector>

class SkillShotProjectile final : public Projectile
{
// STATICS
public:
	static void InitUnitVector(std::vector<Unit*>* unitVector);
	static std::vector<Unit*>* c_UnitVector;

// NON-STATICS
public:
	SkillShotProjectile(const Point2f& startingPos, const Point2f& destination);
	SkillShotProjectile(const SkillShotProjectile& skillshotprojectile) = delete;
	SkillShotProjectile& operator=(const SkillShotProjectile& skillshotprojectile) = delete;
	SkillShotProjectile(SkillShotProjectile&& skillshotprojectile) = delete;
	SkillShotProjectile& operator=(SkillShotProjectile&& skillshotprojectile) = delete;
	virtual ~SkillShotProjectile();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	virtual bool ReadyToDelete() const override;

private:

	Point2f m_Destination;
	bool m_ReadyToDelete;
};

