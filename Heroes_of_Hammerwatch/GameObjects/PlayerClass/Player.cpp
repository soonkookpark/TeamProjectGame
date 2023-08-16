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
#include "MeleeAttack.h"

void Player::Init()
{
	//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?
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
	tileIntSize = tilemap->TileIntSize();
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleF.csv"));

	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(1);
		
	sortLayer = SortLayer::PLAYER;
	

}

void Player::SetData(const std::string& name)
{
	pTable = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::PlayerClass)->Get(name).PI;	
	creatureInfo = DATATABLE_MGR.Get<PlayerTable>(DataTable::Ids::PlayerClass)->Get(name).CI;	



	skills.insert({ "atk", new MeleeAttack("test") });
	skills["atk"]->SetOwner(this);
}

void Player::Reset()
{
	animation.Play("IdleD");
	SetOrigin(origin);
	//SetPosition({ 0, 0 });
	SetFlipX(false);
	box.setSize({16,16});
	box.setOrigin(box.getSize() * 0.5f);
	SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrScene());

	//currentClipInfo = clipInfos[6];*/
}

void Player::Update(float dt)
{
	
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
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
	
	if (direction == sf::Vector2f{0, 0}&& !attackNow)
	{
		IdleAnimationPrint(lookat);
	}
	else if((((INPUT_MGR.GetKey(sf::Keyboard::S))
		||(INPUT_MGR.GetKey(sf::Keyboard::W)) 
		||(INPUT_MGR.GetKey(sf::Keyboard::D)) 
		||(INPUT_MGR.GetKey(sf::Keyboard::A)))&& !attackNow)
		)
	{
		MoveAnimationPrint(lookat); //ï¿½ï¿½ï¿½ì½ºï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Å°ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ì´ï¿½ ï¿½Ö´Ï¸ï¿½ï¿½Ì¼ï¿½.
		//isAnimationPlay = true;
	}
	if (INPUT_MGR.GetMouseButton(sf::Mouse::Left) && !attackNow)
	{
		attackNow = true;
		AttackAnimationPrint(lookat);
	}
	
	if(attackNow && animation.GetCurrFrame() == 3)
	{
		attackNow = false;
	}

	playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Tilde))
	{
		//ï¿½ï¿½ï¿½ï¿½ ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ï¿½ï¿½ ï¿½ï¿½Ä¡
		std::cout << playerTileIndex.x << ", " << playerTileIndex.y << std::endl;
		//Å¸ï¿½ï¿½ ï¿½ï¿½Ã¼ Å©ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
		std::cout << tileIntSize.x<< ", " << tileIntSize.y << std::endl;
		//ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ï¿½ï¿½ ï¿½ï¿½Ä¡
		std::cout << GetPosition().x << ", " << GetPosition().y << std::endl;
		

	}
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		std::cout << mousePos.x << "," << mousePos.y << std::endl;
		//animation1.Play("MonsterBallEffect");
		if (direction.x == 0 && direction.y == 0)
		{
			//(CheckTileInfo(sf::Vector2f{static_cast<float>(playerTileIndex.x + 1), static_cast<float>(playerTileIndex.y)}));
		}
	}
	
	//direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
	//direction.y = INPUT_MGR.GetAxis(Axis::Vertical);
	//sprite.g

	//std::cout << playerTileIndex.x << ", " << playerTileIndex.y << std::endl;

	PlayerMove();
	
	//std::cout << GetPosition().x << std::endl;
	
	position += direction * creatureInfo.speed * dt;
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
	//ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ï¿½ï¿½ Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ý¾ï¿½
	//FindTileInfo();
	//BoxMaker();
	
	box.setPosition(sprite.getPosition());
	Creature::Update(dt);

	if (InputMgr::Instance().GetMouseButtonDown(sf::Mouse::Left))
	{
		skills["atk"]->Active();
	}
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
		if ((CheckTileInfoRight(sf::Vector2f{static_cast<float>(playerTileIndex.x + 1), static_cast<float>(playerTileIndex.y)})))
		{
			//std::cout<<playerTileIndex.x << std::endl;
			direction.x = +1;
		}
		
		
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::A))
	{
		if ((CheckTileInfoLeft(sf::Vector2f{static_cast<float>(playerTileIndex.x - 1), static_cast<float>(playerTileIndex.y)})))
		{
			direction.x = -1;
		}
		
		//direction.x = -1;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::W))
	{
		if ((CheckTileInfoUp(sf::Vector2f{static_cast<float>(playerTileIndex.x), static_cast<float>(playerTileIndex.y-1)})))
		{
			direction.y= -1;
		}
		//direction.y = -1;
	}
	if (INPUT_MGR.GetKey(sf::Keyboard::S))
	{
		if ((CheckTileInfoDown(sf::Vector2f{static_cast<float>(playerTileIndex.x), static_cast<float>(playerTileIndex.y+1)})))
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
			if (texIndex != 1)//ï¿½Ìµï¿½ï¿½Ò°ï¿½Å¸ï¿½ï¿½
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

bool Player::CheckTileInfoLeft(sf::Vector2f info)
{
	int tileSize = tilemap->tiles.size();
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == info.x && tilemap->tiles[i].y == info.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != 1)// if(¿òÁ÷ÀÏ ¼ö ¾ø´Ù)
			{
				if ((info.x * tilePixelSize + (tilePixelSize / 2) > box.getPosition().x - box.getSize().x))
					return 0;
			}
			return 1;
		}
	}
}

bool Player::CheckTileInfoRight(sf::Vector2f info)
{
	int tileSize = tilemap->tiles.size();
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == info.x && tilemap->tiles[i].y == info.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != 1)// if(¿òÁ÷ÀÏ ¼ö ¾ø´Ù)
			{
				if ((info.x * tilePixelSize + (tilePixelSize / 2)) < box.getPosition().x + box.getSize().x)
					return 0;
			}
			return 1;
		}
	}
}

bool Player::CheckTileInfoUp(sf::Vector2f info)
{
	int tileSize = tilemap->tiles.size();
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == info.x && tilemap->tiles[i].y == info.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != 1)// if(¿òÁ÷ÀÏ ¼ö ¾ø´Ù)
			{
				if ((info.y * tilePixelSize + (tilePixelSize / 2) > box.getPosition().y - box.getSize().y))
					return 0;
			}
			return 1;
		}
	}
}

bool Player::CheckTileInfoDown(sf::Vector2f info)
{
	int tileSize = tilemap->tiles.size();
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == info.x && tilemap->tiles[i].y == info.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != 1)// if(¿òÁ÷ÀÏ ¼ö ¾ø´Ù)
			{
				if ((info.y * tilePixelSize + (tilePixelSize / 2) < box.getPosition().y + box.getSize().y))
					return 0;
			}
			return 1;
		}
	}
}

/*bool Player::CheckTileInfo(sf::Vector2f info)
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Num1))
	{
		
		
		std::cout << "Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½: ";
		std::cout << info.x * tilePixelSize + (tilePixelSize / 2) << std::endl;
		std::cout << "ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½: ";
		std::cout << box.getPosition().x - box.getSize().x << std::endl;
		

		std::cout << "Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½: ";
		std::cout << (info.x * tilePixelSize + (tilePixelSize / 2)) << std::endl;
		std::cout << "ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½: ";
		std::cout << box.getPosition().x + box.getSize().x << std::endl;
	}
	int tileSize = tilemap->tiles.size();
	//playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	for (int i = 0; i < tileSize; i++)
	{

		if (tilemap->tiles[i].x == info.x && tilemap->tiles[i].y == info.y)
		{
			int texIndex = static_cast<int>(tilemap->tiles[i].texIndex);
			if (texIndex != 1)// if(¿òÁ÷ÀÏ ¼ö ¾ø´Ù)
			{
				if((info.x*tilePixelSize+(tilePixelSize/2)> box.getPosition().x - box.getSize().x)
					|| ((info.x * tilePixelSize + (tilePixelSize / 2)) < box.getPosition().x + box.getSize().x))
					return 0;
				
				
				Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : 8
				ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : 15.9863
				Å¸ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : 8
				ï¿½Ã·ï¿½ï¿½Ì¾ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ : 47.9863
				

				//	ÇÃ·¹ÀÌ¾îÀÇ À§Ä¡
				//	ÇÃ·¹ÀÌ¾î°¡ Å°¸¦ ´­·¶À»¶§ÀÇ Å¸ÀÏÀÇ À§Ä¡
				//	ÇÃ·¹ÀÌ¾îÀÇ À§Ä¡
				//	Å¸ÀÏ ÇÑÄ­ ÇÑÄ­ÀÇ »çÀÌÁî
				//	Å¸ÀÏ ÇÑÄ­ ÇÑÄ­ÀÇ »çÀÌÁî
				//	ÀÎµ¦½º°¡ ¾Æ´Ï¶ó
				//	±× Å¸ÀÏÀÇ ÁÂÇ¥¿Í
				//	ÇÃ·¹ÀÌ¾îÀÇ ÁÂÇ¥¸¦ ºñ±³ÇØ¼­ ±× µÑÀÇ Àý¹Ý »çÀÌÁî¸¸Å­ ºÙÀ» ¼ö ÀÖ°Ô ÇÏÀÚ

				//	°¡µµµÇ³Ä°¡
				//	±× Å¸ÀÏÀÇ ÁßÁ¡±îÁö ÀÌµ¿ÇÏ°Ô ÇØÁà¾ßÇØ.
				//	³»°¡ ¾Ë¾Æ¾ßÇÒ°Í



				//	ÇÃ·¹ÀÌ¾îÀÇ À§Ä¡ getposition
				//	ÇÃ·¹ÀÌ¾îÀÇ x»çÀÌÁî getposition
				//	// ÇÃ·¹ÀÌ¾î Å¸ÀÏÀÇ Á¤º¸ FindTileInfo

				//	Å¸ÀÏÀÇ ÁÂÇ¥
				//	Å¸ÀÏÀÇ Á¤º¸ CheckTileInfo //°¥ ¼ö ÀÖ³Ä ÆÇ´Ü
				//	Å¸ÀÏÀÇ »çÀÌÁî

				//	x·Î °¥¶§ È®ÀÎy·Î °¥¶§ È®ÀÎ

				//	//¾Ë°í½ÍÀº ÁÂÃø Å¸ÀÏÀÇ x ÁÂÇ¥
				//	(info.x * tilePixelSize + (tilePixelSize / 2))




			}
			return 1;
		}
	}
}*/

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

void Player::AttackAnimationPrint(SightDegree lookat)
{

	switch (lookat)
	{
	case 0:
		if (animation.GetCurrentClipId() == "AttackR")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackR");
		break;
	case 1:
		if (animation.GetCurrentClipId() == "AttackDR")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackDR");
		break;
	case 2:
		if (animation.GetCurrentClipId() == "AttackD")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackD");
		break;
	case 3:
		if (animation.GetCurrentClipId() == "AttackDL")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackDL");
		break;
	case 4:
		if (animation.GetCurrentClipId() == "AttackL")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackL");
		break;
	case 5:
		if (animation.GetCurrentClipId() == "AttackUL")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackUL");
		break;
	case 6:
		if (animation.GetCurrentClipId() == "AttackU")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackU");
		break;
	case 7:
		if (animation.GetCurrentClipId() == "AttackUR")
			if (animation.GetCurrFrame() <= 1) break;
		animation.Play("AttackUR");
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
	if (curHealth > creatureInfo.maxHealth)
		curHealth = creatureInfo.maxHealth;
}

void Player::HealMP(int value)
{
	curMana += value;
	if (curMana > pTable.manaPoint)
		curMana = pTable.manaPoint;
}

void Player::Damaged(float physicalDmg, float magicalDmg)
{
	std::cout << "ï¿½Ç°Ýµï¿½" << std::endl;
	physicalDmg = 1 / (1 + creatureInfo.armor / 50) * physicalDmg;
	magicalDmg = 1 / (1 + creatureInfo.resistance / 50) * magicalDmg;

	//ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ù´ï¿?ï¿½ï¿½ ï¿½ï¿½Æ¿ï¿½ï¿½ ï¿½Ö¾ï¿½ï¿?ï¿½Òµï¿½

	curHealth -= physicalDmg + magicalDmg;
	if (curHealth < 0)
	{
		//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ô¼ï¿½
	}
}
