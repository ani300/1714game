/******************************MinigaemFitIt.h**********************************/
#ifndef MFI
#define MFI

#include "Utils.h"
#include "Estat.h"
#include "Player.h"
#include "MovileObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "TextNode.hpp"
#include "Box.h"

class MinigaemFitIt: public Estat {

    public:
        //Constructor
        MinigaemFitIt(PilaEstats& stack, Context context);
        MinigaemFitIt(PilaEstats& stack, Context context, std::string document);

        void draw();
        bool update(sf::Time dt);
        bool handleEvent(const sf::Event& event);

    private:
        enum Layer {
            Background,
            Boxes,
            Text,
            LayerCount
        };

        TextureHolder mOwnTextures;
        ResourceHolder<sf::Texture, int> mBoxTextures;

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;

        Player* mPlayer;
        TextNode* mText;
        sf::Vector2i mGood_bad;
        std::vector<Box*> mBoxes;
        std::vector<int> mGoodBoxes;

        void handleRealtimeInput();
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);

        

};
        
    //heredats de Estat
        /*
        directions dir;
        mouseButtons mouseBut;
        sf::Vector2f mouseClick;
        */
/*};*/

#endif
