#pragma once
#include <functional>
#include "MyAlgorithms.h"
#include "IVisibleObject.h"
class ClickableText : public IVisibleObject
{
public:
	ClickableText(const std::string& message, std::function<void()> func, int x, int y, const sf::Color& color=sf::Color::Red);
	bool HandleEvents(const sf::Event& someEvent);
	void Update();
	void Draw();

	void MouseOver(bool b);
	void Show(bool b);
	const sf::Text& GetText();
	void SetPosition(float x, float y);
	void Click();

private:
	bool isMousedOver;
	bool isShowing;
	sf::Text text;
	std::function<void()> OnClick;
};