#pragma once

#include "mefUtils.h"
#include <vector>

namespace mef
{

	class mef_circle
	{
	private:
		float width;
		float height;
		float radius;
		glm::vec2 pos; // middle of rect

		mef_vao vao;
		mef_vbo vbo;
		mef_ebo ebo;
		mef_shader shader;

		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		void createRectR()
		{
			vertices = {
				pos.x - width / 2, pos.y - height / 2, 0.0f,
				pos.x - width / 2, pos.y + height / 2, 0.0f,
				pos.x + width / 2, pos.y - height / 2, 0.0f,
				pos.x + width / 2, pos.y + height / 2, 0.0f
			};

			indices = {
				0, 1, 2,
				1, 2, 3
			};

			vao.createVao();
			vbo.createVBO<float>(vertices.data(), vertices.size(), DRAW_MODE::STATIC);
			ebo.createEBO<unsigned int>(indices.data(), indices.size(), DRAW_MODE::STATIC);

			vao.attribPointer(0, 3, MEF_ENUM::MEF_FLOAT, MEF_ENUM::MEF_FALSE, 3 * sizeof(float), (void*)0);

			vao.unbind();
			vbo.unbind();
			ebo.unbind();

			shader.createShader("../mefGL/src/CircleShader.vert", "../mefGL/src/CircleShader.frag");
		}

	public:
		mef_circle() : radius(1.0f), width(2.0f), height(2.0f), pos(glm::vec2(0.0f,0.0f)) { }
		mef_circle(float r, glm::vec2 position) : radius(r), width(r*2), height(r*2), pos(position) { }

		void createCircle(float Nradius, glm::vec2 Npos)
		{
			width = Nradius * 2;
			height = Nradius * 2;
			radius = Nradius;
			pos = Npos;
			createRectR();
		}

		void draw(mef_win& window)
		{
			shader.bind();

			shader.setFloat("radius", radius);
			shader.setVec2f("xPos", "yPos", pos);
			shader.setVec2f("WinWidth", "WinHeight", glm::vec2(window.getWidth(), window.getHeight()));

			vao.bind();

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

			shader.unbind();
			vao.unbind();
		}

		void changeVertices(float w, float h, glm::vec2 Npos)
		{
			width = w;
			height = h;
			pos = Npos;

			vertices = {
				pos.x - width / 2, pos.y - height / 2, 0.0f,
				pos.x - width / 2, pos.y + height / 2, 0.0f,
				pos.x + width / 2, pos.y - height / 2, 0.0f,
				pos.x + width / 2, pos.y + height / 2, 0.0f
			};

			vao.bind();
			vbo.bind();

			vbo.bufferData(vertices.data(), vertices.size(), DRAW_MODE::STATIC);
			vbo.unbind();
			vao.unbind();
		}

		void setPos(glm::vec2 newPos)
		{
			pos = newPos;
			changeVertices(width, height, pos);
		}

		float getWidth() { return width; }
		float getHeight() { return height; }
	};
}


