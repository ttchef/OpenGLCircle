
#include "mefGL.h"


int main()
{
	if (!mef::initMef())
	{
		return -1;
	}

	mef::setOpenGLProfile(3, 3, mef::Profile::Core);

	mef::mef_win window;
	window.createWindow("Mef Test");

	if (!mef::initOpenGL(window.getWin()))
	{
		return -1;
	}

	window.setSize(1920, 1080);

	mef::mef_rect rect;

	while (window.stayOpen())
	{
		


		window.swapBuffers();
		window.handleEvents();
	}

}

