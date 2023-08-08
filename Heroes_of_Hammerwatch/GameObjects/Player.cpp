#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"

void Player::Init()
{
	//애니메이션 csv 

	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleB.csv");
	//캐릭ㅇ터 애니메이션 그리고 나오게 함.

	//파일 입출력
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleB.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	
	sortLayer = SortLayer::PLAYER;
}

void Player::Reset()
{
	animation.Play("IdleB");
	SetOrigin(origin);
	SetPosition({ 0, 0 });
	SetFlipX(false);

	//currentClipInfo = clipInfos[6];*/
}

void Player::Update(float dt)
{
	//이동
	direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxis(Axis::Vertical);
	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;
	}

	position += direction * speed * dt;
	SetPosition(position);

	/*if (direction.x != 0.f || direction.y != 0.f)
	{
		auto min = std::min_element(clipInfos.begin(), clipInfos.end(),
			[this](const ClipInfo& lhs, const ClipInfo& rhs) {
				return Utils::Distance(lhs.point, direction) < Utils::Distance(rhs.point, direction);
			});
		currentClipInfo = *min;
	}

	std::string clipId = magnitude == 0.f ? currentClipInfo.idle : currentClipInfo.move;
	if (GetFlipX() != currentClipInfo.flipX)
	{
		SetFlipX(currentClipInfo.flipX);
	}*/

	/*if (animation.GetCurrentClipId() != clipId)
	{
		animation.Play(clipId);
	}*/

	animation.Update(dt);

}

bool Player::GetFlipX() const
{
	return filpX;
}

void Player::SetFlipX(bool filp)
{
	filpX = filp;

	sf::Vector2f scale = sprite.getScale();
	scale.x = !filpX ? abs(scale.x) : -abs(scale.x);
	sprite.setScale(scale);
}

void Player::PlayerMove()
{
	direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
	direction.y = INPUT_MGR.GetAxis(Axis::Vertical);
}
