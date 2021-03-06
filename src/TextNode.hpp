#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP

#include "Utils.h"
#include "SceneNode.hpp"

class TextNode: public SceneNode {
	public:
		explicit TextNode(const sf::Font& font, const std::string& text);
		void setString(const std::string& text);
		void setCharacterSize(unsigned int size);
		void setColor(const sf::Color& color);

	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		sf::Text mText;
};

#endif // TEXTNODE_HPP
