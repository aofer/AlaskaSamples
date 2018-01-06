#version 450 core

//how many times this shader will run per patch (nº of out control points)
layout (vertices = 4) out;

uniform vec3 cameraPosition;
uniform float tessellatedTriWidth;
uniform ivec2 viewportSize;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform float displacementScale;
uniform sampler2D displacementTexture;

in VertexShaderOut {
	vec2 texCoord;
	vec2 texCoord2;
} tcs_in[];

out TCShaderOut {
	vec2 texCoord;
	vec2 texCoord2;
} tcs_out[];


float GetTessLevel(float Distance0, float Distance1)
{
    float AvgDistance = (Distance0 + Distance1) / 2.0;

    if (AvgDistance <= 2.0) {
        return 10.0;
    }
    else if (AvgDistance <= 5.0) {
        return 7.0;
    }
    else {
        return 3.0;
    }
}

// Project a sphere into clip space and return the number of triangles that are required
// to fit across the screenspace diameter.
float sphereToScreenSpaceTessellation(vec3 cp0, vec3 cp1, float diameter) {
	vec3 mid = (cp0 + cp1) * 0.5;
	
	vec4 p0 = viewMatrix * vec4(mid, 1.0);
	vec4 p1 = p0;
	p1.x += diameter;

	vec4 clip0 = projMatrix * p0;
	vec4 clip1 = projMatrix * p1;
	
	clip0 /= clip0.w;
	clip1 /= clip1.w;
	
	clip0.xy = ((clip0.xy * 0.5) + 0.5) * viewportSize;
	clip1.xy = ((clip1.xy * 0.5) + 0.5) * viewportSize;
	
	return distance(clip0, clip1) / tessellatedTriWidth; //spec says it will be clamped by GL
	//return clamp(distance(clip0, clip1) / tessellatedTriWidth, 1.0, 64.0);
}

void main()
{

	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;
	vec4 p3 = gl_in[3].gl_Position;

	//Displace control points on y, to account for height on LOD computations
	p0.y += texture(displacementTexture, tcs_in[0].texCoord).r * displacementScale;
	p1.y += texture(displacementTexture, tcs_in[1].texCoord).r * displacementScale;
	p2.y += texture(displacementTexture, tcs_in[2].texCoord).r * displacementScale;
	p3.y += texture(displacementTexture, tcs_in[3].texCoord).r * displacementScale;

    // Calculate the distance from the camera to the three control points
	//vec4 camPos = vec4(cameraPosition,1.0);
 //   float EyeToVertexDistance0 = distance(camPos, p0);
 //   float EyeToVertexDistance1 = distance(camPos, p1);
 //   float EyeToVertexDistance2 = distance(camPos, p2);
	//float EyeToVertexDistance3 = distance(camPos, p3);

 //   // Calculate the tessellation levels
 //   gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance3, EyeToVertexDistance0);
 //   gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
 //   gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
	//gl_TessLevelOuter[3] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance3);
	float diameter = p1.x - p0.x;
	gl_TessLevelOuter[0] = sphereToScreenSpaceTessellation(p3.xyz, p0.xyz, diameter);
    gl_TessLevelOuter[1] = sphereToScreenSpaceTessellation(p0.xyz, p1.xyz, diameter);
    gl_TessLevelOuter[2] = sphereToScreenSpaceTessellation(p1.xyz, p2.xyz, diameter);
	gl_TessLevelOuter[3] = sphereToScreenSpaceTessellation(p2.xyz, p3.xyz, diameter);
	gl_TessLevelInner[0] = (gl_TessLevelOuter[1] + gl_TessLevelOuter[3]) * 0.5;
	gl_TessLevelInner[1] = (gl_TessLevelOuter[0], gl_TessLevelOuter[2]) * 0.5;

	tcs_out[gl_InvocationID].texCoord = tcs_in[gl_InvocationID].texCoord;
	tcs_out[gl_InvocationID].texCoord2 = tcs_in[gl_InvocationID].texCoord2;
	
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

