#version 450 core

out vec4 FragColor;

in GShaderOut {
	vec3 positionWorld;
	vec3 positionEye;
	//vec4 positionShadowMap;
	vec2 texCoord;
	vec2 texCoord2;
	noperspective vec3 distToEdges;
} fs_in;

uniform sampler2D colorTexture;
uniform bool enableWireframe;

void main()
{
	//FragColor = vec4(0.2,1.0,0.5,1.0);
	vec4 color = texture(colorTexture,fs_in.texCoord2);

		//WIREFRAME
	if(enableWireframe) {
		const vec4 WIREFRAME_COLOR = vec4(1.0,0.0,0.0,0.0);
		const float WIREFRAME_THICKNESS = 1.0;
		
		float wireframeStrength = 0.0;

		float minDistToEdge = min(fs_in.distToEdges.x, min(fs_in.distToEdges.y, fs_in.distToEdges.z));
		if(minDistToEdge <= WIREFRAME_THICKNESS) {
			wireframeStrength = smoothstep(0.0, 1.0, 1.0 - (minDistToEdge / WIREFRAME_THICKNESS));
		}

		color = WIREFRAME_COLOR * wireframeStrength + (1.0 - wireframeStrength) * color;
	}
	FragColor = color;
	FragColor.a = 1.0;

}