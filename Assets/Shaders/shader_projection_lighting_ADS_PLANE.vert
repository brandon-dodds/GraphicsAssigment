#version 440 core
layout (location = 0) in vec3 Position; //vertex positions
layout (location=1) in vec2 texCoord;	//tex coords
layout (location=2) in vec3 normal;	// vertex normals

 						
out vec2 textureCoordinate;
out vec3 normals;
out vec3 fragmentPosition;
out vec3 lightColour;
out vec3 lightPosition;
out vec3 viewPosition;
out float time;
out vec3 position;

uniform mat4 uNormalMatrix;
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec3 uLightColour;
uniform vec3 uAmbientIntensity;
uniform vec3 lightCol;
uniform vec3 uLightPosition;
uniform vec3 uViewPosition;
uniform float uTime; 

// in: vec2 out:random float value
//'fract()' returns only the fractional part of a value.
//Deterministic - not really random
//Introduce time to get progression
float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123  );
}

//Value noise function
//in: vec2 out: float value
float noiseFunction(vec2 st) {
    vec2 d = vec2(0.0, 1.0);
    vec2 b = floor(st);
    vec2 f = smoothstep(vec2(0.0), vec2(1.0), fract(st));
    
return mix(mix(random(b), random(b + d.yx), f.x), mix(random(b + d.xy), random(b + d.yy), f.x), f.y);
}



void main()
{
	vec2 uv = texCoord;
	uv *= 10.0;
	
	vec3 pos = Position;
	
	float ovn = 1.0*(noiseFunction(uv ));
    ovn += 1.0*(noiseFunction(uv   *2.0 )*0.5);
    ovn +=  1.0*(noiseFunction(uv   *4.0 )*0.25);
    ovn +=  1.0*(noiseFunction(uv   *8.0 )*0.125);
	ovn +=  1.0*(noiseFunction(uv   *16.0 )*0.0625);
    ovn +=  1.0*(noiseFunction(uv   *32.0 )*0.03125);
	
	
	//Alter the positions of the y coordinate of the vertices
	//Use the noise function
	pos.y = (pos.y+(ovn/4.0))-(1.0-(sin(ovn))*1.0);
	
	

	gl_Position = uProjection * uView * uModel * vec4(pos.x, pos.y, pos.z, 1.0); 
						
	textureCoordinate = vec2(texCoord.x, 1 - texCoord.y);
	
	//get the fragment position in world coordinates as this is where the lighting will be calculated
	fragmentPosition = vec3(uModel * vec4(Position, 1.0f));
	//fragmentPosition = vec3(uModel * vec4(pos, 1.0f));
	
	
	//pass the normals to the fragment shader unmodified
	//normals = normal;
	
	//pass normals to fragment shader after modifying for scaling
	//calculate a 'normal matrix' and multiply by the unmodified normal
	normals = mat3(uNormalMatrix) * normal;
	
	
	lightColour = uLightColour;
	lightPosition = uLightPosition;
	viewPosition = uViewPosition;
	time = uTime;
	//Send the vertext position data to the fragment shader
	position = pos;

}