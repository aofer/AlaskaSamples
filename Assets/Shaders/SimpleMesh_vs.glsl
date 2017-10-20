#version 450 core                                                                        
                                                                                    
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textcoords;
layout(location = 2) in vec3 in_normal;                                            
                                                                                    
uniform mat4 viewMatrix;                                                                  
uniform mat4 projectionMatrix;                                                             
         
out vec2 uvCoords;                                                   
                                                                                    
                                                               
                                                                                    
void main()                                                                         
{      
	uvCoords = in_textcoords;                                                                             
    gl_Position = projectionMatrix * viewMatrix *  vec4(in_position, 1.0);                                                         
}
