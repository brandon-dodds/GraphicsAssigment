#version 440 core
out vec4 vertColour;		
in vec2 textureCoordinate;

uniform sampler2D aTex3;		

void main()
{

	vec4 texColour = texture(aTex3, textureCoordinate);
	
	vertColour = vec4(  texColour.x, 
						texColour.y,      	 		
						texColour.z, 
						texColour.a);
}