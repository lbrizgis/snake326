#include "GamePlay.h"
#include "GameOver.h"
#include "PauseGame.h"
#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Context>& context) : m_context(context), m_snDirection({ 30, 30 }), m_elapsedTime(sf::Time::Zero), m_score(0), m_isPaused(false), m_stageSelector(0) {

	srand(time(nullptr));
	
}

GamePlay::~GamePlay() {

}

void GamePlay::Init() {

	//Stage Randomizer
	m_stageSelector = rand() % 3 + 1;

	//Music
	m_gamePlayMusic.openFromFile("mainsong.wav");
	m_gamePlayMusic.play();
	m_gamePlayMusic.setVolume(5);

	//Sound Effects
	m_eatFoodBuffer.loadFromFile("food eat.wav");
	m_eatFood.setBuffer(m_eatFoodBuffer);
	m_eatFood.setVolume(5);


	//Textures
	m_context->m_assets->addTexture(GRASS, "grass2.png", true);
	m_context->m_assets->addTexture(DESERT, "desert.png", true);
	m_context->m_assets->addTexture(WOODFLOOR, "woodfloor.png", true);
	m_context->m_assets->addTexture(WALLS, "wall2.png", true);
	m_context->m_assets->addTexture(FOOD, "food2.png");
	m_context->m_assets->addTexture(SNAKE, "body.png");



	//Setting up walls
	for (auto& wall : m_walls) {

		wall.setTexture(m_context->m_assets->GetTexture(WALLS));
	}
	m_walls[0].setTextureRect({ 0, 0, (int)m_context->m_window->getSize().x, 30 });
	m_walls[1].setTextureRect({ 0, 0, (int)m_context->m_window->getSize().x, 30 });
	m_walls[1].setPosition(0, m_context->m_window->getSize().y - 30);

	m_walls[2].setTextureRect({ 0, 0, 30, (int)m_context->m_window->getSize().y });
	m_walls[3].setTextureRect({ 0, 0, 30, (int)m_context->m_window->getSize().y });
	m_walls[3].setPosition(m_context->m_window->getSize().x - 30, 0);
	

	//Placing Food
	m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
	m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

	//Snake Texture
	m_snake.Init(m_context->m_assets->GetTexture(SNAKE));


	//Score
	m_scoretxt.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_scoretxt.setString("SCORE: " + std::to_string(m_score));
	m_scoretxt.setCharacterSize(20);
	m_scoretxt.setPosition(m_context->m_window->getSize().x - 210.f , 5.f);
	

}

void  GamePlay::ProcessInput() {

	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}

		//Key inputs
		else if (event.type == sf::Event::KeyPressed) {
			

			sf::Vector2f newDir = m_snDirection;
			switch (event.key.code)
			{
			case sf::Keyboard::Up:

				newDir = { 0.f, -30.f };
				break;
			case sf::Keyboard::Down:

				newDir = { 0.f, 30.f };
				break;
			case sf::Keyboard::Left:

				newDir = { -30.f, 0.f };
				break;
			case sf::Keyboard::Right:

				newDir = { 30.f, 0.f };
				break;
			case sf::Keyboard::Escape :

				m_context->m_states->add(std::make_unique<PauseGame>(m_context));
				break;

			default:
				break;
			}

			if (std::abs(m_snDirection.x) != std::abs(newDir.x) || std::abs(m_snDirection.y) != std::abs(newDir.y))  {

				m_snDirection = newDir;
			}
		}
	}
}

void  GamePlay::Update(sf::Time deltaTime) {


	if (!m_isPaused) {

		m_elapsedTime += deltaTime;

		if (m_elapsedTime.asSeconds() > 0.1) {

			bool isOnWall = false;
			bool isOnSelf = false;
		

			for (auto& wall : m_walls) {
				if (m_snake.IsOn(wall)) {

					m_context->m_states->add(std::make_unique<GameOver>(m_context), true);
					break;
				}
			}


			//Randomizing food placements
			if (m_snake.IsOn(m_food)) {

				m_snake.Grow(m_snDirection); //Snake growth

				int x = 0, y = 0;

				x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 30, m_context->m_window->getSize().x - 2 * 30);
				y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 30, m_context->m_window->getSize().y - 2 * 30);

				m_food.setPosition(x, y);
				m_score += 10;
				m_scoretxt.setString("SCORE: " + std::to_string(m_score)); //Adding points when food is eaten

				m_eatFood.play();
			}
			else {

				m_snake.Move(m_snDirection);
			}

			//Checking if snake is colliding with itself
			if (m_snake.IsOnSelf()) {

				m_context->m_states->add(std::make_unique<GameOver>(m_context), true);

			}

			m_elapsedTime = sf::Time::Zero;

		}
	}
}

void  GamePlay::Draw() {

	m_context->m_window->clear();

	//Stage selection
	if (m_stageSelector == 1) {

		m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
		m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
		m_context->m_window->draw(m_grass);
	}
	else if (m_stageSelector == 2) {

		m_desert.setTexture(m_context->m_assets->GetTexture(DESERT));
		m_desert.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
		m_context->m_window->draw(m_desert);
	}
	else {

		m_woodFloor.setTexture(m_context->m_assets->GetTexture(WOODFLOOR));
		m_woodFloor.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
		m_context->m_window->draw(m_woodFloor);
	}
	
	for (auto& wall : m_walls) {

		m_context->m_window->draw(wall);
	}

	m_context->m_window->draw(m_food);
	m_context->m_window->draw(m_snake);
	m_context->m_window->draw(m_scoretxt);

	m_context->m_window->display();
}

void  GamePlay::Pause() {

	m_isPaused = true; //Optimising game by not running unneccessary code
}

void  GamePlay::Start() {

	m_isPaused = false; //Optimising game by not running unneccessary code
}