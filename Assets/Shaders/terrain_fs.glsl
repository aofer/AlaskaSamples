#version 450 core

out vec4 FragColor;

in TEShaderOut {
	vec2 texCoord;
	vec2 texCoord2;
} fs_in;
    

uniform sampler2D colorTexture;

void main()
{
	//FragColor = vec4(0.2,1.0,0.5,1.0);
	FragColor = texture(colorTexture,fs_in.texCoord2);

}