#pragma once
class MyAlgorithms
{
public:
	template<typename SFMLOBJ>
	static bool IsWithin(const sf::Vector2i& pos, const SFMLOBJ& bounds)
	{
		if (pos.x > bounds.getGlobalBounds().left && pos.x < bounds.getGlobalBounds().left + bounds.getGlobalBounds().width
			&& pos.y > bounds.getGlobalBounds().top && pos.y < bounds.getGlobalBounds().top + bounds.getGlobalBounds().height)
			return true;
		return false;
	}

	template<typename SFMLOBJ>
	static void CenterOrigin(SFMLOBJ& obj)
	{
		obj.setOrigin(obj.getGlobalBounds().left+obj.getGlobalBounds().width/2, obj.getGlobalBounds().top+obj.getGlobalBounds().height/2);
	}
};

