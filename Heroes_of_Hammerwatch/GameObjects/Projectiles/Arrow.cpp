#include "stdafx.h"
#include "Arrow.h"
#include "TileMap.h"
#include "Creature.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"

Arrow::Arrow(const std::string& key, Creature* owner, std::list<Creature*> targets, sf::Vector2f pos, sf::Vector2f dir)
    :Projectile(key, owner, targets, pos),dir(dir)
{
    SetData(key);
	SetForwardAt();
}

void Arrow::Update(float dt)
{
    Projectile::Update(dt);
	animation.Update(dt);
	dir = Utils::Normalize(dir);
	sf::Vector2f move = dir * speed * dt;
	movedDistance = Utils::Distance(move);

    SetPosition(position + move);	
	hitPos += move;

    if (penetrateNum <= EffectedCreature.size() || CollidedWithWall() || attackRange < movedDistance)
        End();

}

void Arrow::SetData(const std::string& key)
{
	sprite.setTexture(*ResourceMgr::Instance().GetTexture("graphics/Test/testProjectile.png"));
	tileMap = owner->GetTileMap();
	if (key == "Maggot") 
	{				
		
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/MaggotEffect/EffectDR.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/MaggotEffect/EffectDL.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/MaggotEffect/EffectR.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/MaggotEffect/EffectL.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/MaggotEffect/EffectUR.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/MaggotEffect/EffectUL.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/MaggotEffect/EffectU.csv"));
		animation.SetTarget(&sprite);
		physicalDamage = 12.f;
		magicalDamage = 0.f;
		speed = 75.f;
		radius = 3.f;
		attackRange = 700.f;		
	}
	if (key == "player") 
	{	
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/PaladinEffect/EffectDR.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/PaladinEffect/EffectDL.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/PaladinEffect/EffectR.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/PaladinEffect/EffectL.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/PaladinEffect/EffectUR.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/PaladinEffect/EffectUL.csv"));
		animation.AddClip(*ResourceMgr::Instance().GetAnimationClip("animations/PaladinEffect/EffectU.csv"));
		animation.SetTarget(&sprite);
		physicalDamage = 15.f;
		magicalDamage = 0.f;
		speed = 75.f;
		radius = 5.f;
		attackRange = 700.f;		
	}
}

bool Arrow::CheckIsCollided(Creature* target)
{	
	/*
	std::cout << "hitpos : \t" << hitPos.x << " , " << hitPos.y << std::endl;
	std::cout << "radius : \t" << radius << std::endl;
	std::cout << "playerPos : \t" << target->GetPosition().x << " , " << target->GetPosition().y << std::endl;
	*/
	return Utils::CircleToRect(hitPos, radius, target->sprite.getGlobalBounds());
}

void Arrow::End()
{
    //사라지는 애니메이션
	SceneMgr::Instance().GetCurrScene()->RemoveGo(this);
	//delete(this);
}

bool Arrow::CollidedWithWall()
{
	return (tileMap->GetTileArray()[static_cast<int>(position.y / 16)][static_cast<int>(position.x / 16)] == 0);
}

void Arrow::SetForwardAt()
{
	sf::Vector2f size = { sprite.getGlobalBounds().width,sprite.getGlobalBounds().height };
	sf::Vector2f pos = { sprite.getGlobalBounds().left,sprite.getGlobalBounds().top };
	float angle = Utils::Angle(dir);
	if (angle < 0)
		angle += 360;
	if (angle > 22.5 && angle <= 67.5)
	{
		forwardAt = DR;
		hitPos = size + pos;
		animation.Play("EffectDR");
	}
	else if (angle > 67.5 && angle <= 112.5)
	{
		forwardAt = D;
		hitPos = { size.x / 2 + pos.x, size.y + pos.y };
		animation.Play("EffectD");
	}
	else if (angle > 112.5 && angle <= 157.5)
	{
		forwardAt = DL;
		hitPos = { pos.x, size.y + pos.y };
		animation.Play("EffectDL");
	}
	else if (angle > 157.5 && angle <= 202.5)
	{
		forwardAt = L;
		hitPos = { pos.x, size.y / 2 + pos.y };
		animation.Play("EffectL");
	}
	else if (angle > 202.5 && angle <= 247.5)
	{
		forwardAt = UL;
		hitPos = pos;
		animation.Play("EffectUL");
	}
	else if (angle > 247.5 && angle <= 292.5)
	{
		forwardAt = U;
		hitPos = { size.x / 2 + pos.x, pos.y };
		animation.Play("EffectU");
	}
	else if (angle > 292.5 && angle <= 337.5)
	{
		forwardAt = UR;
		hitPos = { size.x + pos.x, pos.y };
		animation.Play("EffectUR");
	}
	else
	{
		forwardAt = R;
		hitPos = { size.x + pos.x, size.y / 2 + pos.y };
		animation.Play("EffectR");
	}
}
