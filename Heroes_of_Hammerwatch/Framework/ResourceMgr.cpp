#include "stdafx.h"
#include "ResourceMgr.h"
#include "rapidcsv.h"
ResourceMgr::~ResourceMgr()
{
	for (auto pair : mapTexture)
	{
		delete std::get<0>(pair.second);
	}
	mapTexture.clear();
	for (auto pair : mapFont)
	{
		delete std::get<0>(pair.second);
	}
	mapFont.clear();
	for (auto pair : mapSoundBuffer)
	{
		delete std::get<0>(pair.second);
	}
	mapSoundBuffer.clear();
	for (auto pair : mapAnimationClip)
	{
		delete std::get<0>(pair.second);
	}
	mapAnimationClip.clear();
}

void ResourceMgr::Init()
{
	LoadFromCsv("scripts/DefaultResourceList.csv", true);
}

void ResourceMgr::UnLoadAll()
{
	{
		auto it = mapTexture.begin();
		while (it != mapTexture.end())// 이터레이터 while문 초기화
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				it = mapTexture.erase(it);
			}
			else 
			{
				++it;
			}
		}
	}
	{
		auto it = mapFont.begin();
		while (it != mapFont.end())// 이터레이터 while문 초기화
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				it = mapFont.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	{
		auto it = mapSoundBuffer.begin();
		while (it != mapSoundBuffer.end())// 이터레이터 while문 초기화
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				it = mapSoundBuffer.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	{
		auto it = mapAnimationClip.begin();
		while (it != mapAnimationClip.end())// 이터레이터 while문 초기화
		{
			if (!std::get<1>(it->second))
			{
				delete std::get<0>(it->second);
				it = mapAnimationClip.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
	
}

void ResourceMgr::LoadFromCsv(const std::string path, bool isDefault)
{
	rapidcsv::Document doc(path);
	std::vector<int> types = doc.GetColumn<int>(0);
	std::vector<std::string> paths = doc.GetColumn<std::string>(1);
	for (int i = 0; i < types.size(); ++i)
	{
		Load((ResourceTypes)types[i], paths[i], isDefault);
	}
}

void ResourceMgr::Load(ResourceTypes t, const std::string path, bool isDefault)
{
	switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(path);
		if (mapTexture.end() == it)
		{
			auto texture = new sf::Texture();
			texture->loadFromFile(path);
			mapTexture.insert({ path, { texture, isDefault} });
		}
	}
	break;
	case ResourceTypes::Font:
	{
		auto it = mapFont.find(path);
		if (mapFont.end() == it)
		{
			auto font = new sf::Font();
			font->loadFromFile(path);
			mapFont.insert({ path, { font, isDefault } });
		}
	}
	break;
	case ResourceTypes::SoundBuffer:
	{
		auto it = mapSoundBuffer.find(path);
		if (mapSoundBuffer.end() == it)
		{
			auto sb = new sf::SoundBuffer();
			sb->loadFromFile(path);
			mapSoundBuffer.insert({ path, { sb, isDefault } });
		}
	}
	break;
	case ResourceTypes::AnimationClip:
	{
		auto it = mapAnimationClip.find(path);
		if (mapAnimationClip.end() == it)
		{
			auto clip = new AnimationClip();
			clip->LoadFromFile(path);
			mapAnimationClip.insert({ path, { clip, isDefault } });
		}
	}
	break;
	}
}

void ResourceMgr::LoadTextureRect(const std::string name, const std::string path, int left, int top, int width, int height, bool isDefault)
{
	auto texture = new sf::Texture();
	texture->loadFromFile(name, {left, top, width, height});
	mapTexture.insert({ name, { texture, isDefault} });
}

//void ResourceMgr::Load(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
//{
//	for (const auto& tuple : array)
//	{
//		Load(std::get<0>(tuple), std::get<1>(tuple));
//	}
//}

void ResourceMgr::Unload(ResourceTypes t, const std::string id)
{
	switch (t)
	{
	case ResourceTypes::Texture:
	{
		auto it = mapTexture.find(id);
		if (it != mapTexture.end())
		{
			if (!std::get<0>(it->second))
			{
				delete std::get<0>(it->second);
				mapTexture.erase(it);
			}
			else
			{
				std::cout << "ERR: Default Resource (Texture,Unload)" << std::endl;
			}
		}
	}
	break;
	case ResourceTypes::Font:
	{
		auto it = mapFont.find(id);
		if (it != mapFont.end())
		{
			if (!std::get<0>(it->second))
			{
				delete std::get<0>(it->second);
				mapFont.erase(it);
			}
			else
			{
				std::cout << "ERR: Default Resource (Font, Unload)" << std::endl;
			}
		}
	}
	break;
	case ResourceTypes::SoundBuffer:
	{
		auto it = mapSoundBuffer.find(id);
		if (it != mapSoundBuffer.end())
		{
			if (!std::get<0>(it->second))
			{
				delete std::get<0>(it->second);
					mapSoundBuffer.erase(it);
			}
			else
			{
				std::cout << "ERR: Default Resource (SoundBuffer, Unload)" << std::endl;
			}
		}
	}
	break;
	case ResourceTypes::AnimationClip:
	{
		auto it = mapAnimationClip.find(id);
		if (mapAnimationClip.end()==it)
		{
			delete std::get<0>(it->second);
			mapAnimationClip.erase(it);
		}
	}
	break;
	}
}

//void ResourceMgr::Unload(const std::vector<std::tuple<ResourceTypes, std::string>>& array)
//{
//	for (const auto& tuple : array)
//	{
//		Unload(std::get<0>(tuple), std::get<1>(tuple));
//	}
//}

sf::Texture* ResourceMgr::GetTexture(const std::string& id)
{
	auto it = mapTexture.find(id);
	if (it != mapTexture.end())
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}

sf::Font* ResourceMgr::GetFont(const std::string& id)
{
	auto it = mapFont.find(id);
	if (it != mapFont.end())
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}

sf::SoundBuffer* ResourceMgr::GetSoundBuffer(const std::string& id)
{
	auto it = mapSoundBuffer.find(id);
	if (it != mapSoundBuffer.end())
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}

AnimationClip* ResourceMgr::GetAnimationClip(const std::string& id)
{
	auto it = mapAnimationClip.find(id);
	if(it != mapAnimationClip.end())
	{
		return std::get<0>(it->second);
	}
	return nullptr;
}
