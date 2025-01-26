
#include "mefGL.h"


int main()
{
	if (!mef::initMef())
	{
		return -1;
	}

	mef::setOpenGLProfile(3, 3, mef::Profile::Core);

	mef::mef_win window;
	window.createWindow(800, 600, "Mef Test");

	while (window.stayOpen())
	{
		

		window.swapBuffers();
		window.handleEvents();
	}

}

