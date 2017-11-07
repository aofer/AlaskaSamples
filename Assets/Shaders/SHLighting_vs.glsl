#version 450 core                                                                  
                                                                                    
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 in_textcoords;
layout(location = 2) in vec3 in_normal;                                            
                                                                                    
uniform mat4 viewProjMatrix;                                                                  
uniform mat4 worldMatrix;                                                       
out vec2 TexCoord0;                                                                 
out vec3 Normal0;                                                                   
out vec3 WorldPos0;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position =  viewProjMatrix * worldMatrix * vec4(in_position, 1.0 );                    
    TexCoord0   = in_textcoords;                                                         
    Normal0     =  (worldMatrix * vec4(in_normal,0.0)).xyz;                                 
    WorldPos0   = (worldMatrix * vec4(in_position,1.0)).xyz;                                                    
}
