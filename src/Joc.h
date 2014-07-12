/***********************Joc.h****************************/
#ifndef JOC
#define JOC

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "PilaEstats.h"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Joc {

	public:
		Joc();

		int play();

	private:
		
		void processEvents();
        void update(sf::Time dt);
        void render();

		void readNextState(int& skipLines);
		
        void updateStatistics(sf::Time dt);
        void registerStates();

        static const sf::Time TimePerFrame;

        sf::RenderWindow mWindow;
        sf::Vector2u mWindowSize;
        sf::RenderTexture mRenderTexture;
        TextureHolder mTextures;
        FontHolder mFonts;

        PilaEstats mPilaEstats;

        sf::Text mStatisticsText;
        sf::Time mStatisticsUpdateTime;
        std::size_t mStatisticsNumFrames;
};


#endif
