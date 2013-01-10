#include "stdafx.h"
#include "Resources.h"



Resources* Resources::instance_ = 0;

Resources* Resources::Instance()
{
	if(instance_ == 0)
		instance_ = new Resources;

	return instance_;
}

Resources::Resources()
{
	//load fonts
	sf::Font arial;
	arial.loadFromFile("resources/fonts/arial.ttf");
	fontBank.insert(std::pair<std::string, sf::Font>("Arial", arial));

	////load textures
	//sf::Texture scrub1;
	//scrub1.loadFromFile("images/scrub1.png");
	//textureBank.insert(std::pair<std::string, sf::Texture>("Scrub1", scrub1));

	//sf::Texture boss1;
	//boss1.loadFromFile("images/boss1.png");
	//textureBank.insert(std::pair<std::string, sf::Texture>("Boss1", boss1));

	////load sounds
	//sf::SoundBuffer intoScrub;
	//intoScrub.loadFromFile("sounds/sfxr/intobattle.wav");
	//sbBank.insert(std::pair<std::string, sf::SoundBuffer>("IntoScrub", intoScrub));

	//sf::SoundBuffer intoBoss;
	//intoBoss.loadFromFile("sounds/sfxr/intobattle2.wav");
	//sbBank.insert(std::pair<std::string, sf::SoundBuffer>("IntoBoss", intoBoss));

	//insert dummy variables to give default load conditions
	fontBank.insert(std::pair<std::string, sf::Font>("zzzzzzz", sf::Font()));
	textureBank.insert(std::pair<std::string, sf::Texture>("zzzzzz", sf::Texture()));
	sbBank.insert(std::pair<std::string, sf::SoundBuffer>("zzzzzzz", sf::SoundBuffer()));
}

const sf::Font& Resources::FontBank(sf::String name)
{
	if(fontBank.find(name)==fontBank.end())
		return sf::Font();
	return instance_->fontBank.at(name);
}

const sf::Texture& Resources::TextureBank(sf::String name)
{
	if(textureBank.find(name)==textureBank.end())
		return sf::Texture();
	return instance_->textureBank.at(name);
}

const sf::SoundBuffer& Resources::SoundBank(const std::string name)
{
	if(sbBank.find(name)==sbBank.end())
		return sf::SoundBuffer();
	return instance_->sbBank.at(name);
}