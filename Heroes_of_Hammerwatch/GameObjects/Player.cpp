#include "stdafx.h"
#include "Player.h"
#include "InputMgr.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "TileMap.h"
#include "RectangleGo.h"
void Player::Init()
{
	//애니메이션 csv 

	RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleB.csv");
	//캐릭ㅇ터 애니메이션 그리고 나오게 함.
	
	//RESOURCE_MGR.Load(ResourceTypes::AnimationClip, "animations/idleF.csv");
	
	//파일 입출력
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleB.csv"));
	animation.SetTarget(&sprite);
	SetOrigin(Origins::MC);
	sprite.setScale(1.0, 1.0);
	tileSize = tilemap->tiles.size();
	//animation.AddClip(*RESOURCE_MGR.GetAnimationClip("animations/idleF.csv"));

	box.setFillColor(sf::Color::Transparent);
	box.setOutlineColor(sf::Color::Red);
	box.setOutlineThickness(1);

	//clipInfos.push_back({ "IdleS", "MoveS", false, Utils::Normalize({ -1.f, -1.f }) });
	//clipInfos.push_back({ "IdleB", "MoveB", true, {0.f, -1.f} });
	//clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, -1.f }) });

	//clipInfos.push_back({ "IdleS", "MoveS", false, {-1.f, 0.f} });
	//clipInfos.push_back({ "IdleS", "MoveS", true, {1.f, 0.f} });

	//clipInfos.push_back({ "IdleS", "MoveS", false, Utils::Normalize({ -1.f, 1.f }) });
	//clipInfos.push_back({ "IdleF", "MoveF", true,{0.f, 1.f} });
	//clipInfos.push_back({ "IdleS", "MoveS", true, Utils::Normalize({ 1.f, 1.f }) });
	
	sortLayer = SortLayer::PLAYER;
}

void Player::Reset()
{
	animation.Play("IdleB");
	SetOrigin(origin);
	//SetPosition({ 0, 0 });
	SetFlipX(false);
	box.setSize({ sprite.getGlobalBounds().width,sprite.getGlobalBounds().height });

	//currentClipInfo = clipInfos[6];*/
}

void Player::Update(float dt)
{
	static float time = 0.f;
	time += dt;
	//이동
	//if (direction.x != 0||direction.y!=0)
	
	playerTileIndex = { static_cast<int>(position.x / tilemap->TileSize().x), static_cast<int>(position.y / tilemap->TileSize().y) };
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Tab))
	{
	}
	
	//direction.x = INPUT_MGR.GetAxis(Axis::Horizontal);
	//direction.y = INPUT_MGR.GetAxis(Axis::Vertical);


	//std::cout << playerTileIndex.x << ", " << playerTileIndex.y << std::endl;

	PlayerMove();
	float magnitude = Utils::Magnitude(direction);
	if (magnitude > 1.f)
	{
		direction /= magnitude;

	}
	if (direction.x == 0.f)
		std::cout << time << std::endl;

	FindTileInfo();
	if (CheckTileInfo(static_cast<sf::Vector2f>(playerTileIndex)))
	{

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

	
	//CheckTileInfo();

	BoxMaker();
	animation.Update(dt);
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
