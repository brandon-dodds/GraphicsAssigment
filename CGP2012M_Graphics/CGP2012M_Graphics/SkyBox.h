#pragma once
#include <GL/glew.h>
#include "SDL.h"
#include "SDL_image.h"
#include "TextureClass.h"
#include <iostream>

class SkyBox {

public:
	Texture sbTextures[6];
	//vertex array object and vertex buffer object
	GLuint sbVAO;
	GLuint sbVBO;
	//shader for the skybox
	Shader sbvSh, sbfSh;
	GLuint sbShaderProgram;
	int sbLocation;

	GLfloat SkyBoxVertices[120]{
		//vertices					//texture coords
		//front
		50.0f, 50.0f, 50.0f,		0.0f, 1.0f,
		50.0f, -50.0f, 50.0f,		0.0f, 0.0f,
		-50.0f, 50.0f, 50.0f,		1.0f, 1.0f,
		-50.0f, -50.0f, 50.0f,		1.0f, 0.0f,
		//back
		-50.0f, 50.0f, -50.0f,		0.0f, 1.0f,
		-50.0f, -50.0f, -50.0f,		0.0f, 0.0f,
		50.0f, 50.0f, -50.0f,		1.0f, 1.0f,
		50.0f, -50.0f, -50.0f,		1.0f, 0.0f,
		//left
		-50.0f, 50.0f, 50.0f,		0.0f, 1.0f,
		-50.0f, -50.0f, 50.0f,		0.0f, 0.0f,
		-50.0f, 50.0f, -50.0f,		1.0f, 1.0f,
		-50.0f, -50.0f, -50.0f,		1.0f, 0.0f,
		//right
		50.0f, 50.0f, -50.0f,		0.0f, 1.0f,
		50.0f, -50.0f, -50.0f,		0.0f, 0.0f,
		50.0f, 50.0f, 50.0f,		1.0f, 1.0f,
		50.0f, -50.0f, 50.0f,		1.0f, 0.0f,
		//top
		-50.0f, 50.0f, -50.0f,		0.0f, 1.0f,
		50.0f, 50.0f, -50.0f,		0.0f, 0.0f,
		-50.0f, 50.0f, 50.0f,		1.0f, 1.0f,
		50.0f, 50.0f, 50.0f,		1.0f, 0.0f,
		//bottom
		50.0f, -50.0f, -50.0f,		0.0f, 1.0f,
		-50.0f, -50.0f, -50.0f,		0.0f, 0.0f,
		50.0f, -50.0f, 50.0f,		1.0f, 1.0f,
		-50.0f, -50.0f, 50.0f,		1.0f, 0.0f
	};

	//constructor
	SkyBox()
	{
		sbvSh.shaderFileName("..//..//Assets//Shaders//shader_Projection_skyBox.vert");
		sbfSh.shaderFileName("..//..//Assets//Shaders//shader_Projection_skyBox.frag");

		sbvSh.getShader(1);
		sbfSh.getShader(2);

		sbShaderProgram = glCreateProgram();
		glAttachShader(sbShaderProgram, sbvSh.shaderID);
		glAttachShader(sbShaderProgram, sbfSh.shaderID);
		glLinkProgram(sbShaderProgram);

		glDeleteShader(sbvSh.shaderID);
		glDeleteShader(sbfSh.shaderID);
	};

	void loadSkyBox()
	{
		sbTextures[0].load("..//..//Assets//Textures//SkyBox//front.jpg");
		sbTextures[1].load("..//..//Assets//Textures//SkyBox//back.jpg");
		sbTextures[2].load("..//..//Assets//Textures//SkyBox//left.jpg");
		sbTextures[3].load("..//..//Assets//Textures//SkyBox//right.jpg");
		sbTextures[4].load("..//..//Assets//Textures//SkyBox//top.jpg");
		sbTextures[5].load("..//..//Assets//Textures//SkyBox//bottom.jpg");

		for (int x = 0; x < 6; x++)
		{
			sbTextures[x].setBuffers();
		}
		
	}

	void setBuffers()
	{
		//set up 1 for the triangle
		glGenBuffers(1, &sbVBO);
		// Initialization code using Vertex Array Object (VAO) (done once (unless the object frequently changes))
		glGenVertexArrays(1, &sbVAO);
		// Bind Vertex Array Object
		glBindVertexArray(sbVAO);
		// Copy our vertices array in a buffer for OpenGL to use
		glBindBuffer(GL_ARRAY_BUFFER, sbVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(SkyBoxVertices), SkyBoxVertices, GL_STATIC_DRAW);

		// Then set our vertex attributes pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//set the texture coordinates attribute pointer
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//Unbind the VAO
		glBindVertexArray(0);
	}

	void renderSkyBox()
	{
		glDepthMask(0);
		glBindVertexArray(sbVAO);

		sbLocation = glGetUniformLocation(sbShaderProgram, "aTex3");
		glUniform1i(sbLocation, 3);
		for(int x = 0; x < 6; x++)
		{
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, sbTextures[x].texture);
			glDrawArrays(GL_TRIANGLE_STRIP, x * 4, 4);
		}
		glDepthMask(1);
	}



};