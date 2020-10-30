#version 440 core
out vec4 vertColour;	//output colour of vertex
in vec2 textureCoordinate; //tex coords from vertex shader
in vec3 normals;
in vec3 fragmentPosition;
in vec3 lightColour;
in vec3 lightPosition;
in float time;

uniform sampler2D aTex;		//uniform holding texture info from main programme



void main()
{
	//ambient component
	//********************************
	//set the ambient coeff from material
	float lightAmbientStrength = 0.3f;
	vec3 objectAmbientReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
	vec3 ambient = (lightAmbientStrength * objectAmbientReflectionCoeff) * lightColour;
	
	//diffuse component
	//********************************
	//normalise normal vectors (reset them as unit vectors)
	vec3 nNormal = normalize(normals);
	//calculate the light direction from the light position and the fragment position
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
	
	//determine the dot product of normal direction and light direction
	float diffuseStrength = max(dot(nNormal, lightDirection), 0.0f);
	
	//combine this with the light colour
	//set the diffuse coeff from material
	vec3 objectDiffuseReflectionCoeff = vec3(1.0f, 1.0f, 1.0f);
    vec3 diffuse = (diffuseStrength * objectDiffuseReflectionCoeff) * lightColour;

	
	//vec2 point = textureCoordinate.xy;
	//point.x += cos(textureCoordinate.y)*(1.0 - abs(cos(time/1000.0)));
	//point.y += cos(textureCoordinate.x)*(1.0 - abs(cos(time/1000.0)));
	
	vec4 textureColour = texture(aTex, textureCoordinate);
	//vec4 textureColour = texture(aTex, point);
	
	//apply no lighting, ambient and diffuse components with colour contributed by texture
	gl_FragColor = (textureColour);
	//gl_FragColor = (vec4((lightColour), 1.0) * textureColour);
	//gl_FragColor = (vec4((ambient),1.0) * textureColour);
	//gl_FragColor = (vec4((ambient+diffuse),1.0) * textureColour);
	
	
}