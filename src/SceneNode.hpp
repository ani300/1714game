#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include "Utils.h"

class SceneNode: public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
	public:
		typedef std::unique_ptr<SceneNode> Ptr;

		SceneNode();

		void attachChild(Ptr child);
		Ptr	detachChild(const SceneNode& node);
		
		void update(sf::Time dt);

		sf::Vector2f getWorldPosition() const;
		sf::Transform getWorldTransform() const;


	private:
		virtual void updateCurrent(sf::Time dt);
		void updateChildren(sf::Time dt);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

		std::vector<Ptr> mChildren;
		SceneNode* mParent;
};

#endif // SCENENODE_HPP