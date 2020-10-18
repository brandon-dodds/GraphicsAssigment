#version 440 core
in vec3 Colour;			//input the Colour values from Vertex shader
in vec2 textureCoordinate; //tex coords from vertex shader

uniform sampler2D aTex;		//uniform holding texture info from main programme


void main()
{
	vec4 tex = texture2D(aTex, textureCoordinate);
	gl_FragColor = tex;
	
}