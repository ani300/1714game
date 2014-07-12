#ifndef ESTAT_H
#define ESTAT_H

#include "Utils.h"
#include "DrawableObject.h"
#include "IdentificadorsEstat.h"
#include "ResourceIdentifiers.h"

class PilaEstats;

class Estat {
    public:
        typedef std::unique_ptr<Estat> Ptr;

        struct Context {
            Context(sf::RenderTexture& rTexture, TextureHolder& textures, FontHolder& fonts, sf::Vector2f escala);

            sf::RenderTexture* rTexture;
            TextureHolder* textures;
            FontHolder* fonts;
            sf::Vector2f escala;
        };

        Estat(PilaEstats& pila, Context context);
        virtual ~Estat();

        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event& event) = 0;

    protected:
        void requestNextState();
        void requestStackPush(Estats::ID stateID, std::string file="");
        void requestStackPop();
        void requestStackClear();

        Context	getContext() const;

    private:
        PilaEstats* mPila;
        Context mContext;
};


#endif // ESTAT_H
