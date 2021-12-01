#include "Game.h"
#include "MainMenu.h"
#include <SFML/Graphics.hpp>

Game::Game() : m_context(std::make_shared<Context>()) {

	m_context->m_window->create(sf::VideoMode(1200, 810), "Snake", sf::Style::Close);
	m_context->m_states->add(std::make_unique<MainMenu>(m_context));
}

Game::~Game() {

}

void Game::Run() {

	sf::Clock clock;
	sf::Time timeSinceLastFrame = sf::Time::Zero;

	while (m_context->m_window->isOpen()) {

		timeSinceLastFrame += clock.restart();

		while (timeSinceLastFrame > TIME_PER_FRAME) {
			
			timeSinceLastFrame -= TIME_PER_FRAME;

			m_context->m_states->ProcessStateChange();
			m_context->m_states->GetCurrent()->ProcessInput();
			m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
			m_context->m_states->GetCurrent()->Draw();
			
		}

	}
		
}