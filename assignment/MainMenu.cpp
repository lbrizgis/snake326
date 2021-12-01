#include "MainMenu.h"
#include "GamePlay.h"

MainMenu::MainMenu(std::shared_ptr<Context>& context) : m_context(context), m_isPlayButtonSelected(true), m_isPlayButtonPressed(false), m_isExitButtonSelected(false), m_isExitButtonPressed(false){
	
	
}

MainMenu::~MainMenu() {

}

void MainMenu::Init() {

	m_context->m_assets->addFont(MAIN_FONT, "emulogic.ttf");


	//Music
	m_mainMenuMusic.openFromFile("titlesong.wav");
	m_mainMenuMusic.play();
	m_mainMenuMusic.setVolume(5);

	//Sound Effects
	m_selectBuffer.loadFromFile("select.wav");
	m_select.setBuffer(m_selectBuffer);
	m_select.setVolume(5);

	//Background + Game Title
	m_texture.loadFromFile("titlescreen.png");
	sf::Vector2u size = m_texture.getSize();
	m_background.setTexture(m_texture);
	m_background.setOrigin(size.x / 2, size.y / 2);
	m_background.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);


	//Play Button
	m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_playButton.setOutlineThickness(2);
	m_playButton.setString("Play");
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 135.f);

	//Exit Button
	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setOutlineThickness(2);
	m_exitButton.setString("Quit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 200.f);

}

void MainMenu::ProcessInput() {

	sf::Event event;
	while (m_context->m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			m_context->m_window->close();
		}

		//Key inputs
		else if (event.type == sf::Event::KeyPressed) {

			switch (event.key.code)
			{
			case sf::Keyboard::Up: {
				
				m_select.play();
				if (!m_isPlayButtonSelected) {
					m_isPlayButtonSelected = true;
					m_isExitButtonSelected = false;			
						
				}
				break;
			}
			case sf::Keyboard::Down: {
				
				m_select.play();
				if (!m_isExitButtonSelected) {
					m_isPlayButtonSelected = false;
					m_isExitButtonSelected = true;
					
				}		
				break;
			}
			case sf::Keyboard::Return: {

				m_isPlayButtonPressed = false;
				m_isExitButtonPressed = false;

				if (m_isPlayButtonSelected) {

					m_isPlayButtonPressed = true;
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

void MainMenu::Update(sf::Time deltaTime) {

	if (m_isPlayButtonSelected) {

		m_playButton.setFillColor(sf::Color::Red); //Changing color of selected button
		m_exitButton.setFillColor(sf::Color::White);
	}
	else {

		m_playButton.setFillColor(sf::Color::White); //Changing color of selected button
		m_exitButton.setFillColor(sf::Color::Red);
	}

	if (m_isPlayButtonPressed) {

		m_context->m_states->add(std::make_unique<GamePlay>(m_context), true); //Starting game

	}
	else if (m_isExitButtonPressed) {
		
		m_context->m_window->close(); //Exiting game
	}

}

void MainMenu::Draw() {
	
	m_context->m_window->clear();
	m_context->m_window->draw(m_background);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();
}