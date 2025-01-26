#pragma once

#include "mefUtils.h"

namespace mef
{

	class mef_rect
	{
	private:
		float width;
		float height;
		
		mef_vao vao;
		mef_vbo vbo;
		mef_ebo ebo;
		mef_shader shader;
	public:
		

		float getWidth() { return width; }
		float getHeight() { return height; }
	};
}
