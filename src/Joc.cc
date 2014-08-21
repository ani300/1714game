#include "Joc.h"

#include "Utils.h"
#include "Estat.h"
#include "IdentificadorsEstat.h"
#include "SplashImage.h"
#include "Minigaem1.h"
#include "MinigaemFitIt.h"
//#include "Fight.h"

const sf::Time Joc::TimePerFrame = sf::seconds(1.f/60.f);

//Constructor
Joc::Joc() :
  mWindow(sf::VideoMode(sf::VideoMode::getDesktopMode()), L"1714: La resistència de l'Història"
    , sf::Style::Titlebar | sf::Style::Close)
, mRenderTexture()
, mTextures()
, mFonts()
, mWindowSize(mWindow.getSize().x, mWindow.getSize().y)
, mEscala(float(mWindow.getSize().x)/1920.0, 9.0/16.0*float(mWindow.getSize().x)/1920.0)
, mPilaEstats(Estat::Context(mRenderTexture, mTextures, mFonts, mEscala))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0){
    if (!mRenderTexture.create(1920, 1080)) cout << "OPSHIT: No pot crear la RenderTexture" << endl;
    mRenderTexture.setSmooth(true);

    mWindowSize = mWindow.getSize();
    mEscala = sf::Vector2f(float(mWindow.getSize().x)/1920.0, float(mWindow.getSize().x)/1920.0);
    mPilaEstats.setContext(Estat::Context(mRenderTexture, mTextures, mFonts, mEscala));

    mWindow.setKeyRepeatEnabled(false);

    // Carrega recursos comuns
    mFonts.load(Fonts::AlluraRegular, "res/media/AlluraRegular.otf");
    mFonts.load(Fonts::Sansation, "res/media/Sansation.ttf");
    mTextures.load(Textures::Llibre, "res/pictures/tex1.png");

    mStatisticsText.setFont(mFonts.get(Fonts::Sansation));
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10u);

    mWindow.setVerticalSyncEnabled(true);

    registerStates();

    mPilaEstats.nextState();
}

int Joc::play() {

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
            if (mPilaEstats.isEmpty())
                mWindow.close();
        }

        updateStatistics(dt);
        render();
    }

    return EXIT_SUCCESS;
}

void Joc::processInput() {
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mPilaEstats.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Joc::update(sf::Time dt) {
    mPilaEstats.update(dt);
}

void Joc::render() {
    mRenderTexture.clear();

    mPilaEstats.draw();

    mRenderTexture.display();

    // Now we start rendering to the window, clear it first
    mWindow.clear();
    mWindow.setView(mWindow.getDefaultView());
    // Draw the texture
    sf::Sprite sprite(mRenderTexture.getTexture());
    // Llegeix mida de la finestra (x, y)
    mWindowSize = mWindow.getSize();
    sprite.setScale(1.0, 1.0);
    sprite.setPosition(0.0, 0.0);
    mEscala = sf::Vector2f(float(mWindowSize.x)/float(mRenderTexture.getSize().x), float(mWindowSize.x)/float(mRenderTexture.getSize().x)); // 16:9 aspect
    //std::cout << mEscala.x << " " << mEscala.y << std::endl;
    sprite.setScale(mEscala);
    mWindow.draw(sprite);
    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    // End the current frame and display its contents on screen
    mWindow.display();

}

void Joc::updateStatistics(sf::Time dt) {
    mStatisticsUpdateTime += dt;
    mStatisticsNumFrames += 1;
    if (mStatisticsUpdateTime >= sf::seconds(1.0f))
    {
        mStatisticsText.setString("FPS: " + std::to_string(mStatisticsNumFrames));

        mStatisticsUpdateTime -= sf::seconds(1.0f);
        mStatisticsNumFrames = 0;
    }
}

void Joc::registerStates() {
    mPilaEstats.registerState<SplashImage>(Estats::SplashScreen);
    mPilaEstats.registerState<Minigaem1>(Estats::Minigaem1);
    mPilaEstats.registerState<MinigaemFitIt>(Estats::MinigaemFitIt);
}

