#ifndef PILAESTATS_HPP
#define PILAESTATS_HPP

#include "Estat.h"
#include "IdentificadorsEstat.h"
#include "ResourceIdentifiers.h"
#include "Utils.h"

class PilaEstats : private sf::NonCopyable {
	public:
        enum Action {
			Push,
			Pop,
			Clear,
		};

        typedef std::pair<Estats::ID, std::string> InfoEstat;

        explicit PilaEstats(Estat::Context context);

        template <typename T>
        void registerState(Estats::ID IDestat);

        bool isEmpty() const;

		void draw();
        void update(sf::Time dt);
        void handleEvent(const sf::Event& event);

        void popState();
        void nextState();
        void clearStates();
        void pushState(Estats::ID IDestat, std::string file);

	private:
        InfoEstat readNextState();

        Estat::Ptr createState(Estats::ID IDestat, std::string file);
        void applyPendingChanges();

        struct PendingChange {
            explicit PendingChange(Action action, Estats::ID stateID = Estats::None, std::string file = std::string());

            Action action;
            Estats::ID stateID;
            std::string file;
		};

        std::vector<Estat::Ptr>	mStack;
        std::vector<PendingChange> mPendingList;

        int skipLines; // Lector estats

        Estat::Context mContext;
        std::map<Estats::ID, std::function<Estat::Ptr(std::string&)>> mFactories;
};


template <typename T>
void PilaEstats::registerState(Estats::ID IDestat) {
    mFactories[IDestat] = [this] (std::string& file) {
        if (file != "")
            return Estat::Ptr(new T(*this, mContext, file));
        else
            return Estat::Ptr(new T(*this, mContext));
	};
}

#endif //PILAESTATS_HPP
