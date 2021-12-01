#pragma once

#include <memory>
#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "Game.h"
#include "Snake.h"

class GamePlay : public sn::state {

private:
	
	int m_stageSelector;

	std::shared_ptr<Context> m_context;
	sf::Sprite m_grass;
	sf::Sprite m_desert;
	sf::Sprite m_woodFloor;
	sf::Sprite m_food;
	std::array<sf::Sprite, 4> m_walls;
	Snake m_snake;

	sf::Music m_gamePlayMusic;
	sf::SoundBuffer m_eatFoodBuffer;
	sf::Sound m_eatFood;

	sf::Text m_scoretxt;
	int m_score;

	sf::Vector2f m_snDirection;
	sf::Time m_elapsedTime;

	bool m_isPaused;


public:

	GamePlay(std::shared_ptr<Context>& context);
	~GamePlay();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
	void Pause() override;
	void Start() override;

};