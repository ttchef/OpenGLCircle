
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
	
	mef::setVsync(mef::SYNC::UNLIMITED);

	mef::mef_rect rect;
	rect.createRect(0.5f, 0.5f);


	while (window.stayOpen())
	{
		mef::clearColorBuffer();
		mef::clearDepthBuffer();


		rect.draw();

		window.swapBuffers();
		window.handleEvents();
	}

}

