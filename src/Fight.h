#ifndef FIGHT_H
#define FIGHT_H

#include "Utils.h"
#include "Estat.h"
#include "FightScreenPlayer.h"
#include "FightScreenEnemy.h"
#include "MovileObject.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "TextNode.hpp"


class Fight : public Estat {
	public:
        //Constructor
        Fight(PilaEstats& stack, Context context);
        Fight(PilaEstats& stack, Context context, std::string document);

        void draw();
        bool update(sf::Time dt);
        bool handleEvent(const sf::Event& event);

        struct Timer {
            sf::Clock temps;
            int pos;
            int ms;
            bool isBig;
        };

        struct Enemy {
            int actualStep;
            sf::Clock temps;
            FightScreenEnemy* object;
        };

    private:
        static constexpr int posicions[5][3][2] = {
            {
                {
                    100,
                    100
                },
                {
                    200,
                    200
                },
                {
                    300,
                    300
                }
            },
            {
                {
                    200,
                    100
                },
                {
                    300,
                    200
                },
                {
                    400,
                    300
                }
            },
            {
                {
                    500,
                    500
                },
                {
                    600,
                    600
                },
                {
                    700,
                    700
                }
            },
            {
                {
                    500,
                    100
                },
                {
                    600,
                    200
                },
                {
                    700,
                    300
                }
            },
            {
                {
                    150,
                    150
                },
                {
                    250,
                    250
                },
                {
                    350,
                    350
                }
            }
        };

        enum Layer {
            Background,
            Objects,
            Text,
            LayerCount
        };

        TextureHolder mOwnTextures;

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount> mSceneLayers;

        FightScreenPlayer* mPlayer;
        TextNode* mText;
        int nEnemies;
        std::vector<Timer> mTimers;
        std::vector<Enemy> mEnemies;
        void handleRealtimeInput();
        void click(mouseButtons mouseButton, sf::Vector2f mouseClick);


};

#endif // FIGHT_H
