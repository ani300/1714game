#include "Estat.h"
#include "PilaEstats.h"

Estat::Context::Context(sf::RenderTexture& rTexture, TextureHolder& textures, FontHolder& fonts, sf::Vector2f escala)
: rTexture(&rTexture)
, textures(&textures)
, fonts(&fonts)
, escala(escala) {
}

Estat::Estat(PilaEstats& stack, Context context)
: mPila(&stack)
, mContext(context) {
}

Estat::~Estat() {
}

void Estat::requestNextState() {
    mPila->nextState();
}

void Estat::requestStackPush(Estats::ID IDEstat, std::string file) {
    mPila->pushState(IDEstat, file);
}

void Estat::requestStackPop() {
    mPila->popState();
}

void Estat::requestStackClear() {
    mPila->clearStates();
}

Estat::Context Estat::getContext() const {
    return mContext;
}
