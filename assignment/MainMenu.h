#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "Game.h"

class MainMenu : public sn::state {

private:

	std::shared_ptr<Context> m_context;
	sf::Texture m_texture;
	sf::Sprite m_background;
	sf::Text m_playButton;
	sf::Text m_exitButton;
	
	sf::SoundBuffer m_selectBuffer;
	sf::Sound m_select;
	sf::Music m_mainMenuMusic;

	bool m_isPlayButtonSelected;
	bool m_isPlayButtonPressed;
	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;



public:

	MainMenu(std::shared_ptr<Context>& context);
	~MainMenu();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};
