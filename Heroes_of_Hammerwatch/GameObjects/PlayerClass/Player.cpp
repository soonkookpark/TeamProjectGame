#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "TileMap.h"
#include "RectangleGo.h"
#include "SceneMgr.h"
#include "SceneGame.h"
#include "PlayerTable.h"
#include "DataTableMgr.h"
void Player::Init()
{
	//파일 입출력
	/*animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveUR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveUL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveDL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/MoveDR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleUR.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleU.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleUL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleDL.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleD.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/IdleDR.csv"));*/
	//animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	sprite.setScale(1.0, 1.0);
	tileSize = tilemap->tiles.size();
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleF.csv"));

	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(1);


	
	sortLayer = SortLayer::PLAYER;

}

void Player::SetDatas(const std::string& name)
{
	pTable = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::PlayerClass)->Get(name);
	
}

void Player::Reset()
{
	animation.Play("IdleD");
	SetOrigin(origin);
	//SetPosition({ 0, 0 });
	SetFlipX(false);
	box.setSize({8,16});
	box.setOrigin(box.getSize() * 0.5f);
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene());

	//currentClipInfo = clipInfos[6];*/
}

void Player::Update(float dt)
{

	animation.Update(dt);
	look = Utils::Normalize(INPUT_MGR.GetMousePos() - SCENE_MGR.GetCurrScene()->WorldPosToScreen(position));
	angle = Utils::Angle(look);
	if (angle < 0)
	{
		angle += 360;
	}
	CharacterSight(angle);
	if (direction != sf::Vector2f{0, 0}&&lookat != pastAngle)
	{
		pastAngle = lookat;
	}
	//std::cout << lookat << std::endl;
	
	if (direction == sf::Vector2f{0, 0})
	{
		IdleAnimationPrint(lookat);
	}
	else if(((INPUT_MGR.GetKey(sf::Keyboard::S))
		||(INPUT_MGR.GetKey(sf::Keyboard::W)) 
		||(INPUT_MGR.GetKey(sf::Keyboard::D)) 
		||(INPUT_MGR.GetKey(sf::Keyboard::A)))
		)
	{
		MoveAnimationPrint(lookat); //마우스가 가리키는 방향으로 움직이는 애니메이션.
		//isAnimationPlay = true;
	}
	/*else if(pastAngle!= lookat)
	{
		isAnimationPlay = false;
		std::cout << "요기 난 지날게" << std::endl;
	}*/
	

	//look = Utils::Normalize(INPUT_MGR.GetMousePos() - SCENE_MGR.GetCurrScene()->WorldPosToScreen(position));
	//angle = Utils::Angle(look);
	//if (angle < 0)
	//{
	//	angle += 360;
	//}
	//CharacterSight(angle);

	//// 이전에 재생 중인 애니메이션 종료 처리
	//if (lookat != CharacterSight(angle))
	//{
	//	isAnimationPlay = false;
	//}

	//// 움직임 및 애니메이션 처리
	//if (direction == sf::Vector2f{0, 0})
	//{
	//	if (isAnimationPlay)
	//	{
	//		// 재생 중인 애니메이션 업데이트
	//		IdleAnimationUpdate();
	//	}
	//	else
	//	{
	//		// 애니메이션 재생 및 재생 상태 설정
	//		IdleAnimationPrint(lookat);
	//		isAnimationPlay = true;
	//	}
	//}
	//else if (INPUT_MGR.GetKeyDown(sf::Keyboard::S) || INPUT_MGR.GetKey(sf::Keyboard::W) || INPUT_MGR.GetKey(sf::Keyboard::D) || INPUT_MGR.GetKey(sf::Keyboard::A))
	//{
	//	if (isAnimationPlay)
	//	{
	//		// 재생 중인 애니메이션 업데이트
	//		MoveAnimationUpdate();
	//	}
	//	else
	//	{
	//		// 애니메이션 재생 및 재생 상태 설정
	//		MoveAnimationPrint(lookat);
	//		isAnimationPlay = true;
	//	}
	//}
	//else
	//{
	//	// 움직임이 없을 경우 애니메이션 정지 상태 설정
	//	isAnimationPlay = false;
	//}
	//{
	//	//moveanimation 출력!!!!!!!!!!!!!
	//}
	//else if () 
	//{
	//
	//}

	//}
	//std::cout << animation.GetCurrentClipId() << std::endl;// != "MoveD";
	//{
	//	if(animation.GetCurrentClipId()!="MoveD")
	//	{
	/*if (INPUT_MGR.GetKey(sf::Keyboard::S)&&!isAnimationPlay)
	{
		animation.Play("MoveD");
		isAnimationPlay = true;
	}
	if (animation.GetCurrentClipId() != "MoveD")
	{
		isAnimationPlay = false;
	}*/
	
	//	}
	//}
	
	/*static float time = 0.f;
	time += dt;*/
	//이동
	//if (direction.x != 0||direction.y!=0)
	
	playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	
	//direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
	//direction.y = INPUT_MGR.GetAxis(Axis::Vertical);


	//std::cout << playerTileIndex.x << ", " << playerTileIndex.y << std::endl;

	PlayerMove();
	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;

	}
	

	
	/*std::string clipId = magnitude == 0.f ? currentClipInfo.idle : currentClipInfo.move;
	if (animation.GetCurrentClipId() != clipId)

	{
		animation.Play(clipId);
	}*/


	FindTileInfo();
	if (CheckTileInfo(static_cast<sf::Vector2f>(playerTileIndex)))
	{

	}	
	position += direction * pTable.creatureInfo.speed * dt;
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

	
	//CheckTileInfo();

	BoxMaker();
	
	box.setPosition(sprite.getPosition());
}

void Player::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(box);
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
	direction.x = 0.f;
	direction.y = 0.f;
	if (INPUT_MGR.GetKey(sf::Keyboard::D))
	{
		if ((CheckTileInfo(sf::Vector2f{static_cast<float>(playerTileIndex.x + 1), static_cast<float>(playerTileIndex.y)})))
		{
			direction.x = +1;
		}
		
		
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::A))
	{
		if ((CheckTileInfo(sf::Vector2f{static_cast<float>(playerTileIndex.x - 1), static_cast<float>(playerTileIndex.y)})))
		{
			direction.x = -1;
		}
		
		//direction.x = -1;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::W))
	{
		if ((CheckTileInfo(sf::Vector2f{static_cast<float>(playerTileIndex.x), static_cast<float>(playerTileIndex.y-1)})))
		{
			direction.y= -1;
		}
		//direction.y = -1;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::S))
	{
		if ((CheckTileInfo(sf::Vector2f{static_cast<float>(playerTileIndex.x), static_cast<float>(playerTileIndex.y+1)})))
		{
		direction.y = +1;
		}
		//direction.y = 1;
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::W)
		|| INPUT_MGR.GetKeyUp(sf::Keyboard::S))
	{
		direction.y= 0;
	}
	if (INPUT_MGR.GetKeyUp(sf::Keyboard::A)
		|| INPUT_MGR.GetKeyUp(sf::Keyboard::D))
	{
		direction.x = 0;
	}
	//direction.x = INPUT_MGR.GetAxisRaw(Axis::Horizontal);
	//direction.y = INPUT_MGR.GetAxisRaw(Axis::Vertical);
}

void Player::FindTileInfo()
{
	//if (tilemap != nullptr)
	
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == playerTileIndex.x && tilemap->tiles[i].y == playerTileIndex.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);

			if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
			{
				std::cout << texIndex << /*", " << tilemap->TileSize().y<<*/ std::endl;

			}
			if (texIndex != 1)//이동불가타운
			{
				/*if (direction.x < 0)
				{
					position.x = (playerTileIndex.x * 16 +16);
					SetPosition(position);
				}
				else if (direction.x > 0)
				{
					position.x = (playerTileIndex.x * 16-16);
					SetPosition(position);
				}*/
				if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
				{
					std::cout << texIndex << /*", " << tilemap->TileSize().y<<*/ std::endl;

				}

				
			}
		}
	}
}

bool Player::CheckTileInfo(sf::Vector2f info)
{
	int tileSize = tilemap->tiles.size();
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == info.x && tilemap->tiles[i].y == info.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != 1)//다음 이동할곳이 갈 수 없어
			{
				
				//std::cout << "여긴 바닥이 아니야" << std::endl;
				
				return 0;
			}
			return 1;
		}
	}
}

int Player::CharacterSight(float angle)
{
	if (angle > 22.5 && angle <= 67.5)
	{
		lookat = DR;
	}
	else if (angle > 67.5 && angle <= 112.5)
	{
		lookat = D;
	}
	else if (angle > 112.5 && angle <= 157.5)
	{
		lookat = DL;
	}
	else if (angle > 157.5 && angle <= 202.5)
	{
		lookat = L;
	}
	else if (angle > 202.5 && angle <= 247.5)
	{
		lookat = UL;
	}
	else if (angle > 247.5 && angle <= 292.5)
	{
		lookat = U;
	}
	else if (angle > 292.5 && angle <= 337.5)
	{
		lookat = UR;
	}
	else
	{
		lookat = R;
	}
	return lookat;

}

void Player::IdleAnimationPrint(SightDegree lookat)
{
	switch (lookat)
	{
	case 0 :
		animation.Play("IdleR");
		break;
	case 1:
		animation.Play("IdleDR");
		break;
	case 2:
		animation.Play("IdleD");
		break;
	case 3:
		animation.Play("IdleDL");
		break;
	case 4 :
		animation.Play("IdleL");
		break;
	case 5 :
		animation.Play("IdleUL");
		break;
	case 6 :
		animation.Play("IdleU");
		break;
	case 7:
		animation.Play("IdleUR");
		break;
	}
}

void Player::MoveAnimationPrint(SightDegree lookat)
{
	switch (lookat)
	{
	case 0:
		if (animation.GetCurrentClipId() == "MoveR")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveR");
		break;
	case 1:
		if (animation.GetCurrentClipId() == "MoveDR")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveDR");
		break;
	case 2:
		if (animation.GetCurrentClipId() == "MoveD")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveD");
		break;
	case 3:
		if (animation.GetCurrentClipId() == "MoveDL")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveDL");
		break;
	case 4:
		if (animation.GetCurrentClipId() == "MoveL")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveL");
		break;
	case 5:
		if (animation.GetCurrentClipId() == "MoveUL")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveUL");
		break;
	case 6:
		if (animation.GetCurrentClipId() == "MoveU")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveU");
		break;
	case 7:
		if (animation.GetCurrentClipId() == "MoveUR")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("MoveUR");
		break;
	}
}

void Player::SetTile(TileMap* tile)
{
	this->tilemap = tile;
}

void Player::BoxMaker()
{
	int tileSize = tilemap->tiles.size();
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	for (int i = 0; i < tileSize; i++)
	{
		int textBox = tilemap->tiles[i].texIndex;
		if (textBox == 0)
		{
			
		}
	}
}


void Player::HealHP(int value)
{
	curHealth += value;
	if (curHealth > pTable.creatureInfo.maxHealth)
		curHealth = pTable.creatureInfo.maxHealth;
}

void Player::HealMP(int value)
{
	curMana += value;
	if (curMana > pTable.manaPoint)
		curMana = pTable.manaPoint;
}

void Player::Damaged(float physicalDmg, float magicalDmg)
{
	physicalDmg = (1 - 1 / (1 + pTable.creatureInfo.armor / 50)) * physicalDmg;
	magicalDmg = (1 - 1 / (1 + pTable.creatureInfo.resistance / 50)) * magicalDmg;

	//대충 위에 받은 데미지 숫자 뜬다는 뜻 유틸에 넣어야 할듯

	curHealth -= physicalDmg + magicalDmg;
	if (curHealth < 0)
	{
		//죽을때 함수
	}
}
