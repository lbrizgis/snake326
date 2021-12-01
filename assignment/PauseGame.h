#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "state.h"
#include "Game.h"

class PauseGame : public sn::state {

private:

	std::shared_ptr<Context> m_context;
	sf::Texture m_texture;
	sf::Sprite m_background;
	sf::Text m_pauseTitle;
	
public:

	PauseGame(std::shared_ptr<Context>& context);
	~PauseGame();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};