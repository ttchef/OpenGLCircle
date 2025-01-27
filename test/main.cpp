
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
	mef::setOpenGLViewport(1920, 1080);
	
	mef::setVsync(mef::SYNC::UNLIMITED);
	mef::enableBlend(true);

	mef::mef_circle circle;
	circle.createCircle(0.5f, glm::vec2(0.0f, 0.0f));


	while (window.stayOpen())
	{
		mef::clearColorBuffer();
		mef::clearDepthBuffer();

		window.update();

		circle.draw(window);

		window.swapBuffers();
		window.handleEvents();
	}

}

