/******************************WalkMap.h**********************************/
#ifndef WM
#define WM

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

class WalkMap: public Estat {

    public:
        //Constructor
        WalkMap(PilaEstats& stack, Context context);
        WalkMap(PilaEstats& stack, Context context, std::string document);

        void draw();
        bool update(sf::Time dt);
        bool handleEvent(const sf::Event& event);

    private:
        enum Layer {
            Background,
            Pnjs,
            Items,
            Boxes,
            Text,
            LayerCount
        };

        TextureHolder mOwnTextures;
        ResourceHolder<sf::Texture, int> mItemTextures;
        ResourceHolder<sf::Texture, int> mPnjTextures;

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;

        sf::View view;
        Player* mPlayer;
        TextNode* mText;
        const int movVel = 300;
        std::vector<Box*> mPnjs;
        std::vector<Box*> mItems;

        void handleRealtimeInput();

};

    //heredats de Estat
        /*
        directions dir;
        mouseButtons mouseBut;
        sf::Vector2f mouseClick;
        */

#endif
