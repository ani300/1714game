#ifndef CONTROLLER
#define CONTROLLER

#include "Utils.h"
//#include <Book/Command.hpp>

/*

class CommandQueue;

class Controller {
    public:
        enum Action {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            ActionCount
        };

        Controller();

        void handleEvent(const sf::Event& event, CommandQueue& commands);
        void handleRealtimeInput(CommandQueue& commands);

        void assignKey(Action action, sf::Keyboard::Key key);
        sf::Keyboard::Key getAssignedKey(Action action) const;


    private:
        void initializeActions();
        static bool isRealtimeAction(Action action);


    private:
        std::map<sf::Keyboard::Key, Action> mKeyBinding;
        std::map<Action, Command> mActionBinding;
};*/

#endif // CONTROLLER
