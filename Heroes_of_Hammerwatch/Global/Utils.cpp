#include "stdafx.h"
#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen(Utils::rd());

int Utils::RandomRange(int min, int maxExclude)
{
	std::uniform_int_distribution<> dist(min, maxExclude - 1);
	return dist(gen);
}

float Utils::RandomRange(float min, float max)
{
	std::uniform_real_distribution<> dist(min, max);
	return (float)dist(gen);
}

sf::Vector2f Utils::RandomOnCircle(float radius)
{
	sf::Vector2f result(RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f));
	result = Normalize(result) * radius;
	return result;
}

sf::Vector2f Utils::RandomInCircle(float radius)
{
	return RandomOnCircle(radius) * RandomValue();
}

float Utils::RandomValue()
{
	return RandomRange(0.0f, 1.0f);
}

void Utils::SetOrigin(sf::Sprite& sprite, Origins origin)
{
	SetOrigin(sprite, origin, sprite.getLocalBounds());
}

void Utils::SetOrigin(sf::Text& text, Origins origin)
{
	SetOrigin(text, origin, text.getLocalBounds());
}

void Utils::SetOrigin(sf::Shape& shape, Origins origin)
{
	SetOrigin(shape, origin, shape.getLocalBounds());
}

void Utils::SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect)
{
	sf::Vector2f originalPos(rect.width, rect.height);
	originalPos.x *= ((int)origin % 3) * 0.5f;
	originalPos.y *= ((int)origin / 3) * 0.5f;
	obj.setOrigin(originalPos);
}

float Utils::Clamp(float v, float min, float max)
{
	return std::max(min, std::min(max, v));
}

sf::Vector2f Utils::Clamp(const sf::Vector2f& v, const sf::Vector2f& min, const sf::Vector2f& max)
{
	sf::Vector2f result;
	result.x = Clamp(v.x, min.x, max.x);
	result.y = Clamp(v.y, min.y, max.y);
	return result;
}

float Utils::Lerp(float a, float b, float t, bool clamping)
{
	float v = a + (b - a) * t;
	if (clamping)
	{
		v = Utils::Clamp(v, std::min(a, b), std::max(a, b));
	}
	return v;
}

sf::Vector2f Utils::Lerp(const sf::Vector2f& a, const sf::Vector2f& b, float t, bool clamping)
{
	if (clamping)
	{
		t = Utils::Clamp(t, 0.f , 1.f);
	}
	return  a + Utils::Normalize(b - a) * (Utils::Distance(a, b) * t);;
}

sf::Color Utils::Lerp(const sf::Color& a, const sf::Color& b, float t, bool clamping)
{
	sf::Color v;
	v.r = (UINT8)Lerp(a.r, b.r, t, clamping);
	v.g = (UINT8)Lerp(a.g, b.g, t, clamping);
	v.b = (UINT8)Lerp(a.b, b.b, t, clamping);
	v.a = (UINT8)Lerp(a.a, b.a, t, clamping);
	return v;
}

const sf::Vector2f Utils::Normalize(const sf::Vector2f& vector)
{
	float mag = Magnitude(vector);
	if (mag == 0.f)
	{
		return vector;
	}
	return vector / mag;
}

float Utils::Magnitude(const sf::Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float Utils::Magnitude(const sf::Vector2i& vector)
{
	return sqrt((float)vector.x * (float)vector.x + (float)vector.y * (float)vector.y);
}

float Utils::SqrMagnitude(const sf::Vector2f& vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float Utils::Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	return Magnitude(p2 - p1);
}

float Utils::Distance(const sf::Vector2i& p1, const sf::Vector2i& p2)
{
	return Magnitude(p2 - p1);
}

float Utils::Angle(const sf::Vector2f& start, const sf::Vector2f& end)
{
	return Angle(Normalize(end - start));
}

float Utils::Angle(const sf::Vector2f& dir)
{
	return (float)(atan2(dir.y, dir.x) * (180.f / M_PI));
}

bool Utils::CircleToRect(const sf::Vector2f& circlePos, const float& radius, const sf::FloatRect& rect, const sf::Vector2f& dir, float angle)
{
	// temporary variables to set edges for testing
	sf::Vector2f test = circlePos;

	// which edge is closest?
	if (circlePos.x < rect.left)         
		test.x = rect.left;      // test left edge
	else if (circlePos.x > rect.left + rect.width)
		test.x = rect.left + rect.width;   // right edge

	if (circlePos.y < rect.top)
		test.y = rect.top;      // top edge
	else if (circlePos.y > rect.top + rect.height)
		test.y = rect.top + rect.height;   // bottom edge
	
	if (angle != 360)
	{
		angle /= 2;
		float testAngle = Angle(dir - circlePos) - Angle(dir - circlePos);
		if (-angle > testAngle || angle < testAngle)
			return false;
	}
	// if the distance is less than the radius, collision!
	if (Distance(circlePos, test) <= radius) {
		
		return true;
	}
	return false;
}

bool Utils::SpriteToSprite(const sf::Sprite& checker, const sf::Sprite& target)
{
	return checker.getGlobalBounds().intersects(target.getGlobalBounds());
}

bool Utils::Contains(const std::wstring& str, const char& c)
{
	std::size_t found = str.find(c);
	return found != std::wstring::npos;
}

std::string Utils::WstringToString(const std::wstring& value)
{
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	return std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(value);
}

std::vector<std::string> Utils::LoadAnimationString(const std::string name)
{
	std::vector<std::string> stringArr;
	for (int i = 0; i < 24; ++i) {
		std::string animationPath = "animations/" + name;

		if (i < 8) {  // Move animations
			animationPath += "/Move";
		}
		else if (i < 16) {  // Attack animations
			animationPath += "/Attack";
		}
		else {  // Idle animations
			animationPath += "/Idle";
		}

		if (i % 8 == 0) {
			animationPath += "DL.csv";
		}
		else if (i % 8 == 1) {
			animationPath += "D.csv";
		}
		else if (i % 8 == 2) {
			animationPath += "DR.csv";
		}
		else if (i % 8 == 3) {
			animationPath += "L.csv";
		}
		else if (i % 8 == 4) {
			animationPath += "R.csv";
		}
		else if (i % 8 == 5) {
			animationPath += "UL.csv";
		}
		else if (i % 8 == 6) {
			animationPath += "U.csv";
		}
		else if (i % 8 == 7) {
			animationPath += "UR.csv";
		}
		stringArr.push_back(animationPath);
	}
	
	return stringArr;
}

