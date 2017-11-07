#version 450   

uniform sampler2D texSampler;                                                                     
                    
in vec2 uvCoords;                     
out vec4 FragColor;   

struct Colors
{
	vec4 colorA;
	vec4 colorB;
	vec4 colorC;
};

uniform colorsUniform
{
	Colors colors;
} ;
                                                                                           
void main()                                                                                 
{                              
	FragColor = texture(texSampler, uvCoords) * ((colors.colorA + colors.colorB + colors.colorC) / 3);                                                                                 
    //FragColor = vec4(0.5,0.0,0.5,1.0);                                                  
}
