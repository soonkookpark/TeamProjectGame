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
    if(dir == sf::Vector2f(999.f, 999.f))
        dir = Utils::Normalize(owner->GetPosition() - InputMgr::Instance().GetMousePos());   
    SetData(key);
	SetForwardAt();
}

void Arrow::Update(float dt)
{
    SetPosition(position + (dir * speed * dt));
    Projectile::Update(dt);

    if (penetrateNum <= EffectedCreature.size())
        End();

    if (CollidedWithWall())
        End();
}

void Arrow::SetData(const std::string& key)
{
	sprite.setTexture(*ResourceMgr::Instance().GetTexture("graphics/Test/testProjectile.png"));
	tileMap = owner->GetTileMap();
	radius = 3.f;
	speed = 1.f;
	
}

bool Arrow::CheckIsCollided(Creature* target)
{	
	return Utils::CircleToRect(hitPos, radius, target->sprite.getGlobalBounds());
}

void Arrow::End()
{
    //사라지는 애니메이션
}

bool Arrow::CollidedWithWall()
{
	return (tileMap->FindTileInfo(position) == 0);
}

void Arrow::SetForwardAt()
{
	sf::Vector2f size = { sprite.getGlobalBounds().width,sprite.getGlobalBounds().height };
	sf::Vector2f pos = { sprite.getGlobalBounds().top,sprite.getGlobalBounds().left };
	float angle = Utils::Angle(dir);
	if (angle < 0)
		angle += 360;
	if (angle > 22.5 && angle <= 67.5)
	{
		forwardAt = DR;
		hitPos = size + pos;
	}
	else if (angle > 67.5 && angle <= 112.5)
	{
		forwardAt = D;
		hitPos = { size.x / 2 + pos.x, size.y + pos.y };
	}
	else if (angle > 112.5 && angle <= 157.5)
	{
		forwardAt = DL;
		hitPos = { pos.x, size.y + pos.y };
	}
	else if (angle > 157.5 && angle <= 202.5)
	{
		forwardAt = L;
		hitPos = { pos.x, size.y / 2 + pos.y };
	}
	else if (angle > 202.5 && angle <= 247.5)
	{
		forwardAt = UL;
		hitPos = pos;
	}
	else if (angle > 247.5 && angle <= 292.5)
	{
		forwardAt = U;
		hitPos = { size.x / 2 + pos.x, pos.y };
	}
	else if (angle > 292.5 && angle <= 337.5)
	{
		forwardAt = UR;
		hitPos = { size.x + pos.x, pos.y };
	}
	else
	{
		forwardAt = R;
		hitPos = { size.x + pos.x, size.y / 2 + pos.y };
	}
}
