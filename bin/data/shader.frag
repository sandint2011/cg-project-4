#version 410

in vec3 fragNormal;

out vec4 outColor;

uniform vec3 meshColor;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 ambientColor;

void main()
{
	// Color based on normals.
	
	// Lighting.
	vec3 normal = normalize(fragNormal);
	float nDotL = max(0, dot(normal, lightDirection));
	// Surface lighting.
	vec3 irradiance = ambientColor + lightColor * nDotL;
	// Surface reflection.
	vec3 linearColor = meshColor * irradiance;

	// Color based on normals, lighting.
	outColor = vec4(pow(linearColor, vec3(1.0 / 2.2)), 1.0);
}