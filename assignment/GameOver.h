#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "Game.h"

class GameOver : public sn::state {

private:

	std::shared_ptr<Context> m_context;
	sf::Texture m_texture;
	sf::Sprite m_gameOverBackground;
	sf::Text m_gameOverTitle;
	sf::Text m_retryButton;
	sf::Text m_exitButton;

	sf::SoundBuffer m_selectBuffer;
	sf::Sound m_select;
	sf::Music m_gameOverMusic;

	bool m_isRetryButtonSelected;
	bool m_isRetryButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;


public:

	GameOver(std::shared_ptr<Context>& context);
	~GameOver();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};
