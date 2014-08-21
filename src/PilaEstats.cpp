#include "PilaEstats.h"

PilaEstats::PilaEstats(Estat::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
, skipLines(0) {
}

void PilaEstats::update(sf::Time dt) {
	// Iterate from top to bottom, stop as soon as update() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->update(dt))
			break;
	}

	applyPendingChanges();
}

void PilaEstats::draw() {
	// Draw all active states from bottom to top
    for(Estat::Ptr& estat : mStack) {
        estat->draw();
    }
}

void PilaEstats::handleEvent(const sf::Event& event) {
	// Iterate from top to bottom, stop as soon as handleEvent() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) {
		if (!(*itr)->handleEvent(event))
			break;
	}

	applyPendingChanges();
}

void PilaEstats::nextState() {
    InfoEstat next = readNextState();
    if (next.first != Estats::None)
        mPendingList.push_back(PendingChange(Push, next.first, next.second));
    else
        mPendingList.push_back(PendingChange(Clear));
}

void PilaEstats::pushState(Estats::ID IDestat, std::string file="") {
    mPendingList.push_back(PendingChange(Push, IDestat, file));
}

void PilaEstats::popState() {
	mPendingList.push_back(PendingChange(Pop));
}

void PilaEstats::clearStates() {
	mPendingList.push_back(PendingChange(Clear));
}

bool PilaEstats::isEmpty() const {
	return mStack.empty();
}

Estat::Ptr PilaEstats::createState(Estats::ID IDestat, std::string file="") {
    auto found = mFactories.find(IDestat);
	assert(found != mFactories.end());

    return found->second(file);
}

void PilaEstats::applyPendingChanges() {
    for (PendingChange change : mPendingList) {
        switch (change.action) {
            case Push:
                mStack.push_back(createState(change.stateID, change.file));
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;
        }
    }

	mPendingList.clear();
}

PilaEstats::PendingChange::PendingChange(Action action, Estats::ID IDestat, std::string file)
: action(action)
, stateID(IDestat)
, file(file) {
}


PilaEstats::InfoEstat PilaEstats::readNextState() {
    std::string doc;
    std::ifstream infile;
    infile.open("res/documents/Joc.txt");
    if(!infile.is_open()) std::cerr << "res/document/Joc.txt" << " no obert " << std::endl;

    for(int i = 0; i < skipLines; ++i) std::getline(infile,doc); // Saves the line in STRING.
    std::getline(infile,doc);
    //% means this line is a comment
    while(doc[0] == '%') {
        std::getline(infile,doc);
        ++skipLines;
    }

    switch(doc[0]){
        case 'S': {
            ++skipLines;
            return InfoEstat(Estats::SplashScreen, doc);
        }
        case 'M': {
            std::cerr << "minigameFitIt actiu" << std::endl;
            ++skipLines;
            return InfoEstat(Estats::MinigaemFitIt, doc);
        }
        case 'N': {
            std::cerr << "minigame1 actiu bitches" << std::endl;
            ++skipLines;
            return InfoEstat(Estats::Minigaem1, doc);
        }
        case 'F': {
            std::cerr << "penguins FIGHT" << std::endl;
            ++skipLines;
            return InfoEstat(Estats::Fight, doc);
        }
        case 'W':
            /*
            //buidar drawableObjects;

            drawableObjects.push_back();
            */
            break;
        default:
            return InfoEstat(Estats::None,"");
            break;
    }
    infile.close();
}

void PilaEstats::setContext(Estat::Context c) {
    mContext = c;
}
