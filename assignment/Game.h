#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "AssetManager.h"
#include "stateManager.h"

enum AssetID {

	MAIN_FONT = 0,
	GRASS,
	DESERT,
	WOODFLOOR,
	WALLS,
	WALL,
	FOOD,
	SNAKE,

	
};

struct Context {

	std::unique_ptr<sn::AssetManager> m_assets;
	std::unique_ptr<sn::stateManager> m_states;
	std::unique_ptr<sf::RenderWindow> m_window;

	Context() {
		
		m_assets = std::make_unique<sn::AssetManager>();
		m_states = std::make_unique<sn::stateManager>();
		m_window = std::make_unique<sf::RenderWindow>();

	}
};

class Game {

private:

	std::shared_ptr<Context> m_context;
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);


public:
	Game();
	~Game();

	void Run();
};