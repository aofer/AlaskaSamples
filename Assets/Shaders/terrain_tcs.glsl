#version 450 core

//how many times this shader will run per patch (nº of out control points)
layout (vertices = 4) out;

uniform vec3 cameraPosition;

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

void main()
{

	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;
	vec4 p3 = gl_in[3].gl_Position;
    // Calculate the distance from the camera to the three control points
	vec4 camPos = vec4(cameraPosition,1.0);
    float EyeToVertexDistance0 = distance(camPos, p0);
    float EyeToVertexDistance1 = distance(camPos, p1);
    float EyeToVertexDistance2 = distance(camPos, p2);
	float EyeToVertexDistance3 = distance(camPos, p3);

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance3, EyeToVertexDistance0);
    gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
    gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
	gl_TessLevelOuter[3] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance3);
	gl_TessLevelInner[0] = (gl_TessLevelOuter[1] + gl_TessLevelOuter[3]) * 0.5;
	gl_TessLevelInner[1] = (gl_TessLevelOuter[0], gl_TessLevelOuter[2]) * 0.5;

	tcs_out[gl_InvocationID].texCoord = tcs_in[gl_InvocationID].texCoord;
	tcs_out[gl_InvocationID].texCoord2 = tcs_in[gl_InvocationID].texCoord2;
	
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}

