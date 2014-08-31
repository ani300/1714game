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
            Boxes,
            Text,
            LayerCount
        };

        TextureHolder mOwnTextures;

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;

        Player* mPlayer;
        TextNode* mText;
        const int movVel = 300;

        void handleRealtimeInput();

};

    //heredats de Estat
        /*
        directions dir;
        mouseButtons mouseBut;
        sf::Vector2f mouseClick;
        */
/*};*/

#endif
