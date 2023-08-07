#include "stdafx.h"
#include "AnimationController.h"
#include "ResourceMgr.h"

void AnimationController::AddClip(const AnimationClip& newClip)
{
	if (clips.find(newClip.id) == clips.end()) //맵에선 검사이렇게 함.
	{
		clips.insert({ newClip.id,newClip });
	}
}

void AnimationController::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime +=dt * speed;
	if (accumTime < clipDuration)
		return;

	accumTime = 0.f;
	++currentFrame;//프레임이 변경되는 순간임.
	
	if (currentFrame == totalFrame)
	{
		if (!queue.empty()) //큐가 안비어있으면
		{
			std::string id = queue.front(); //queue에 담긴 애들중 1번을 가져온다,
			queue.pop();
			Play(id, false);
			return;
		}
		else
		{
			switch (currentClip->loopType)
			{
			case AnimationLoopTypes::Single:
				currentFrame = totalFrame - 1;
				return;
			case AnimationLoopTypes::Loop:
				currentFrame = 0;
				break;
			}
		}
	}

	



	if ((currentClip->frames[currentFrame]).action != nullptr)
	{
		currentClip->frames[currentFrame].action();
	}


	if (target != nullptr)
	{
		SetFrame(currentClip->frames[currentFrame]);
	}

}

void AnimationController::Play(const std::string& clipId, bool ClearQueue) //여기서 하는건 헤더에있느 값들을 갱신한다. 재생할 애니메이션의 정보에 맞춰서. 그렇게 리셋을 해주고 프레임을 변경해주고 셋팅하고있는정보가 현재 프레임이 몇이냐 
{
	if (ClearQueue)
	{
		while(!queue.empty())//queue를 빼고싶으면 비어있을때까지 pop 을 시킴
			queue.pop();//들어가있는 queue를 뺌.
	}
	auto find = clips.find(clipId);// 없는경우
	if (find == clips.end())	// 없는경우
	{
		Stop();
		std::cout << "ERR: NotExist Clip" << std::endl;
		return;
	}

	isPlaying = true;
	currentClip = &find->second;
	currentFrame = 0;
	totalFrame = (int)currentClip->frames.size();
	clipDuration = 1.f / currentClip->fps;
	accumTime = 0.f;


	SetFrame(currentClip->frames[currentFrame]);
}

void AnimationController::PlayQueue(const std::string& clipId)
{
	queue.push(clipId);
}

void AnimationController::Stop()
{
	isPlaying = false;
}

void AnimationController::SetFrame(const AnimationFrame& frame)
{
	sf::Texture* tex = RESOURCE_MGR.GetTexture(frame.textureId);

	target->setTexture(*tex);
	target->setTextureRect(frame.texCoord);
}

std::string AnimationController::GetCurrentClipId()
{
	return currentClip->id;
}
