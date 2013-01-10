#pragma once
#include <memory>
class Resources
{
public:
	static Resources* Instance();
	const sf::Font& FontBank(sf::String name);
	const sf::Texture& TextureBank(sf::String name);
	const sf::SoundBuffer& SoundBank(const std::string name);
	protected:
	Resources();

private:
	static Resources* instance_;

	//default returns if bad index
	sf::Texture defTex;
	sf::Font defFont;
	sf::SoundBuffer defSnd;

	//banks of resources
	std::map<std::string, sf::Font> fontBank;
	std::map<std::string, sf::Texture> textureBank;
	std::map<std::string, sf::SoundBuffer> sbBank;
};

