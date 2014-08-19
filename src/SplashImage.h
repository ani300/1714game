/********************************SplashImage.h***************************************/

#ifndef SPLASHIMAGE
#define SPLASHIMAGE

#include "Utils.h"
#include "Estat.h"
#include "SceneNode.hpp"
#include "TextNode.hpp"
#include "SpriteNode.hpp"
#include "DrawableObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class SplashImage: public Estat {

    public:
        //Constructor with name of the image it want's to display
        SplashImage(PilaEstats& stack, Context context);
        SplashImage(PilaEstats& stack, Context context, std::string document);

        void draw();
        bool update(sf::Time dt);
        bool handleEvent(const sf::Event& event);

    private:
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

        enum Layer {
            Background,
            Text,
            LayerCount
        };

        ResourceHolder<sf::Texture, Textures::SplashImage::ID> mOwnTextures;

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;

        std::string str;
};


#endif
