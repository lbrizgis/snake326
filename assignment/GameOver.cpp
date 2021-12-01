#include "GameOver.h"
#include "GamePlay.h"

GameOver::GameOver(std::shared_ptr<Context>& context) : m_context(context), m_isRetryButtonSelected(true), m_isRetryButtonPressed(false), m_isExitButtonSelected(false), m_isExitButtonPressed(false) {

}

GameOver::~GameOver() {

}

void GameOver::Init() {

	//Music
	m_gameOverMusic.openFromFile("gameover.wav");
	m_gameOverMusic.play();
	m_gameOverMusic.setVolume(5);

	//Sound Effects
	m_selectBuffer.loadFromFile("select.wav");
	m_select.setBuffer(m_selectBuffer);
	m_select.setVolume(5);

	//Background
	m_texture.loadFromFile("gameover.png");
	sf::Vector2u size = m_texture.getSize();
	m_gameOverBackground.setTexture(m_texture);
	
	m_gameOverBackground.setOrigin(size.x / 2, size.y / 2);
	m_gameOverBackground.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);


	//Game Over Title
	m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameOverTitle.setString("You lost!");
	m_gameOverTitle.setFillColor(sf::Color::Black);
	m_gameOverTitle.setOutlineColor(sf::Color::White);
	m_gameOverTitle.setOutlineThickness(2);
	m_gameOverTitle.setCharacterSize(50);
	m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
	m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 150.f);


	//Play Button
	m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_retryButton.setOutlineThickness(2);
	m_retryButton.setString("Retry?");
	m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2);
	m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f);

	//Exit Button
	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setOutlineThickness(2);
	m_exitButton.setString("Quit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f);

}

void GameOver::ProcessInput() {

	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}

		//Key Inputs
		else if (event.type == sf::Event::KeyPressed) {

			switch (event.key.code)
			{
			case sf::Keyboard::Up: {

				m_select.play();
				if (!m_isRetryButtonSelected) {
					m_isRetryButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down: {

				m_select.play();
				if (!m_isExitButtonSelected) {
					m_isRetryButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Return: {

				m_isRetryButtonPressed = false;
				m_isExitButtonPressed = false;

				if (m_isRetryButtonSelected) {

					m_isRetryButtonPressed = true;
				}
				else {

					m_isExitButtonPressed = true;
				}
				break;
			}
			default:
				break;
			}
		}
	}

}

void GameOver::Update(sf::Time deltaTime) {

	//Button Selection
	if (m_isRetryButtonSelected) {

		m_retryButton.setFillColor(sf::Color::Red); //Changing color of selected button
		m_exitButton.setFillColor(sf::Color::White);
	}
	else {

		m_retryButton.setFillColor(sf::Color::White); //Changing color of selected button
		m_exitButton.setFillColor(sf::Color::Red);
	}

	if (m_isRetryButtonPressed) {

		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true);

	}
	else if (m_isExitButtonPressed) {

		m_context->m_window->close();
	}
}

void GameOver::Draw() {

	m_context->m_window->clear();
	m_context->m_window->draw(m_gameOverBackground);
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_retryButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();
}