/*
  MIT License

  Copyright (c) 2021 rbellek

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "App.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <string>

unsigned int shaderProgram;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class CubeApp : public App {
public:
	CubeApp(std::string title, uint32_t width, uint32_t height)
		: App(title, width, height), m_cam(SCR_WIDTH, SCR_HEIGHT), m_program("light")//, m_texture("CarvedTable_Albedo.tga")
	{
		m.importFrom("assets/models/box.obj");
		glm::vec3 pos(0.0f, 3.0f, -3.f);
		glm::vec3 dir = glm::normalize(m.rightTop - pos);
		m_cam.lookAt(pos, dir);

		//glm::vec3 dir = m.leftBottom - m.rightTop;
		//m_cam.lookAt(m.leftBottom + dir * 3.f, m.leftBottom - dir * 3.f);
		//light.importFrom("assets/models/box.obj");
	}
	float rotate = 0.f;
	ShaderProgram m_program;
	Camera m_cam;
	Mesh m, light;
	//Texture m_texture;

protected:
	virtual void render() override {
		m_cam.processInputs(getWindow());
        m_program.use();
		m_program.setVec3("lightPos", glm::vec3(3, 1, -3));
		m_program.setVec3("lightColor", glm::vec3(0.7, 0.1, .3));
		m_program.setMat4("viewProjection", m_cam.getViewProjectionMatrix());
		m_program.setVec3("cameraPos", m_cam.getPosition());
		static float x = 0.0f;
		static float t = 0.1f;
		static float r = 0.0f;
		
		m.translate({ x, 0.f, 0.f });
		m.rotate({ 1.f, 1.0f, 0.f }, r);
		x += t;
		r += t * 20;
		if (x > 5.0f || x < -5.0f) {
			t = -t;
		}

		m.reset();
		m_program.setMat4("model", m.getModel());
		m.reset();
		
		//m_program.setInteger("sampler", 0);
		//m_texture.bind();
		m.render();
		//light.render();
	}
};

int main(void)
{
    CubeApp app("OpenGL Sample App", SCR_WIDTH, SCR_HEIGHT);
	app.Run();

	return 0;
}
