/***********************Joc.h****************************/
#ifndef JOC
#define JOC

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "PilaEstats.h"
#include "IdentificadorsEstat.h"
#include "Controller.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Joc {

    public:
        Joc();

        int play();

    private:
        
        void render();
        void processInput();
        void registerStates();
        void update(sf::Time dt);
        void updateStatistics(sf::Time dt);

        static const sf::Time TimePerFrame;

        sf::Vector2f mEscala;
        sf::Vector2u mWindowSize;
        sf::RenderWindow mWindow;
        sf::Text mStatisticsText;
        sf::Time mStatisticsUpdateTime;
        sf::RenderTexture mRenderTexture;

        FontHolder mFonts;
        PilaEstats mPilaEstats;
        TextureHolder mTextures;
        std::size_t mStatisticsNumFrames;
};


#endif
