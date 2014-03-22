/******************************Logic.h**********************************/
#ifndef LOGIC
#define LOGIC

#include "Graphic.h"

class Logic {

	public:
		//Constructor
		Logic(Graphic &graphicModule);

		//Destructor
		~Logic();

	private:

		Graphic graphic;

};

#endif