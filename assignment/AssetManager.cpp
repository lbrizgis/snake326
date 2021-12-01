#include "AssetManager.h"

sn::AssetManager::AssetManager() {

}

sn::AssetManager::~AssetManager() {

}

void sn::AssetManager::addTexture(int id, const std::string& filePath, bool isRepeated) {

	auto texture = std::make_unique<sf::Texture>();

	if (texture->loadFromFile(filePath)) {

		texture->setRepeated(isRepeated);
		m_textures[id] = std::move(texture);

	}
}

void sn::AssetManager::addFont(int id, const std::string& filePath) {

	auto font = std::make_unique<sf::Font>();

	if (font->loadFromFile(filePath)) {

		m_fonts[id] = std::move(font);
	}


}

const sf::Texture& sn::AssetManager::GetTexture(int id) const {

	return *(m_textures.at(id).get());
	
}

const sf::Font& sn::AssetManager::GetFont(int id) const {

	return *(m_fonts.at(id).get());
}



