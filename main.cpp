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

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <iostream>

unsigned int shaderProgram;

float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left  
	 0.5f, -0.5f, 0.0f, // right 
	 0.0f,  0.5f, 0.0f  // top   
};


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class CubeApp : public App {
public:
	CubeApp(std::string title, uint32_t width, uint32_t height)
		: App(title, width, height) {
        Shader m_vertexShader = Shader::CreateShader(SHADER_TYPE::VERTEX);
        Shader m_fragShader = Shader::CreateShader(SHADER_TYPE::FRAGMENT);
		m_vertexShader.load(R"(
            #version 430 core
            layout (location = 0) in vec3 aPos;
			uniform mat4 viewProjection;

            void main()
            {
	            gl_Position = viewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
		)");

		m_vertexShader.compile();

		m_fragShader.load(R"(
            #version 430 core
			out vec4 FragColor;

			void main()
			{
				FragColor = vec4(1.0f, 0.0f, 0.2f, 1.0f);
			} 
		)");

		m_fragShader.compile();

		m_program.attachShader(m_vertexShader);
		m_program.attachShader(m_fragShader);
		m_program.link();

	}
	float rotate = 0.f;
	ShaderProgram m_program;
protected:
	virtual void render() override {
		Camera cam(SCR_WIDTH, SCR_HEIGHT);
		cam.lookAt({ 0, 0, -10 }, { 0, 0, 1.f });
        m_program.use();
		m_program.setMat4("viewProjection", cam.getViewProjectionMatrix());
	}
};

int main(void)
{
    CubeApp app("OpenGL Sample App", SCR_WIDTH, SCR_HEIGHT);
	app.Run();

	return 0;
}
