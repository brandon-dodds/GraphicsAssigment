#version 440 core
out vec4 vertColour;	//output colour of vertex
in vec2 textureCoordinate; //tex coords from vertex shader
in vec3 normals;
in vec3 fragmentPosition;
in vec3 lightColour;
in vec3 lightPosition;
in vec3 viewPosition;
in float time;
in vec3 position;

uniform sampler2D aTex;		//uniform holding texture info from main programme


void main()
{	//LIGHTING
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
	
	//specular component
	//**********************************
	float specularStrength = 0.4f;
	vec3 viewDirection = normalize(viewPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nNormal); 
	float sp = pow(max(dot(viewDirection, reflectDirection), 0.0), 8);
    vec3 specular = specularStrength * sp * lightColour; 
	//**************************************
	//
	

	vec4 textureColour = texture(aTex, textureCoordinate);
	vec3 pos = vec3(0.0);
	pos = position;
	
	//Tint texture colours related to height?

	//Output the fragment colours
	vertColour = vec4((ambient+diffuse+specular),1.0) * textureColour ;	
	
	
}