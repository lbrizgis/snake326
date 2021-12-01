#pragma once

#include <list>
#include <SFML/Graphics.hpp>

class Snake : public sf::Drawable{

private:
	std::list<sf::Sprite> m_body;
	std::list<sf::Sprite>::iterator m_head;
	std::list<sf::Sprite>::iterator m_tail;

public:
	Snake();
	~Snake();

	void Init(const sf::Texture& texture);
	void Move(const sf::Vector2f& direction);
	bool IsOn(const sf::Sprite& other) const;
	void Grow(const sf::Vector2f& direction);
	bool IsOnSelf() const;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};
