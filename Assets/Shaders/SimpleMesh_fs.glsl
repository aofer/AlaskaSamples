#version 450   

uniform sampler2D texSampler;                                                                     
                    
in vec2 uvCoords;                     
out vec4 FragColor;                                                                                              
void main()                                                                                 
{                              
	FragColor = texture(texSampler, uvCoords);                                                                                 
    //FragColor = vec4(0.5,0.0,0.5,1.0);                                                  
}
