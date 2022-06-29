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
#include "VertexBuffer.h"

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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

class CubeApp : public App {
public:
	CubeApp(std::string title, uint32_t width, uint32_t height)
		: App(title, width, height) {
        Shader m_vertexShader = Shader::CreateShader(SHADER_TYPE::VERTEX);
        Shader m_fragShader = Shader::CreateShader(SHADER_TYPE::FRAGMENT);
		m_vertexShader.load(R"(
            #version 430 core
            layout (location = 0) in vec3 aPos;

            void main()
            {
	            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
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

		m_vBuffer.load(vertices, sizeof(vertices));
		m_vBuffer.use();
	}
	float rotate = 0.f;
	ShaderProgram m_program;
	VertexBuffer m_vBuffer;
protected:
	virtual void render() override {
        // draw our first triangle
        //glUseProgram(shaderProgram);
        m_program.use();
		m_vBuffer.draw();
        return;

        //static float vertices[] =
        //{
        //  1.f,  1.f,  1.f, -1.f,  1.f,  1.f, -1.f, -1.f,  1.f,  1.f, -1.f,  1.f,
        //  1.f,  1.f,  1.f,  1.f, -1.f,  1.f,  1.f, -1.f, -1.f,  1.f,  1.f, -1.f,
        //  1.f,  1.f,  1.f,  1.f,  1.f, -1.f, -1.f,  1.f, -1.f, -1.f,  1.f,  1.f,
        // -1.f, -1.f, -1.f, -1.f,  1.f, -1.f,  1.f,  1.f, -1.f,  1.f, -1.f, -1.f,
        // -1.f, -1.f, -1.f, -1.f, -1.f,  1.f, -1.f,  1.f,  1.f, -1.f,  1.f, -1.f,
        // -1.f, -1.f, -1.f,  1.f, -1.f, -1.f,  1.f, -1.f,  1.f, -1.f, -1.f,  1.f
        //};

        //static float colors[] =
        //{
        //  1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f,
        //  1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f,
        //  0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f,
        //  0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f,
        //  0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
        //  1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f,
        //};


        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glLoadIdentity();
        //glRotatef(rotate, 1.f, 1.f, 0.f);

        //glVertexPointer(3, GL_FLOAT, 0, vertices);
        //glColorPointer(3, GL_FLOAT, 0, colors);

        //glEnableClientState(GL_VERTEX_ARRAY);
        //glEnableClientState(GL_COLOR_ARRAY);

        //glDrawArrays(GL_QUADS, 0, sizeof(vertices) / (sizeof(float) * 3));
        //rotate += 1;
	}
};

int main(void)
{
    CubeApp app("OpenGL Sample App", SCR_WIDTH, SCR_HEIGHT);
	app.Run();

	return 0;
}
