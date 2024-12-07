#include "engine.h"
/*
		tahmlib
		A C++ library for Game Development

		Author: Tamta Asatiani
		tamta@geolab.edu.ge

		-- Game Loop --

		Sets up the game loop and creates conditions
		for breaking out of it, if specific requirements are met,
		and cleans up references when the application is closed.
*/

// event handling
Tahm& tahm = Tahm::getInstance();

// game loop
int main()
{
	if (!tahm.loadPlugin("./libmain.so"))
	{
		std::cerr << "tahm cannot find the game code\n";
		return 0;
	}

	tahm.run();
	return 0;
}