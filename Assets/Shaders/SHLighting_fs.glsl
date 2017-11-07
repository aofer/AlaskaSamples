#version 450 core                                                                 
                                                                                    
                                                   
const float C1 = 0.429043;
const float C2 = 0.511664;
const float C3 = 0.743125;
const float C4 = 0.886227;
const float C5 = 0.247708;     

                                              
in vec2 TexCoord0;                                                                  
in vec3 Normal0;                                                                    
in vec3 WorldPos0;                                                                  
                                                                                    
out vec4 FragColor;                                                             
       
struct SpotLight
{ 
  vec4 Color;
  vec4 Position;
  vec4 Direction;
  float AmbientIntensity;
  float DiffuseIntensity;
  float ConstAtten;
  float LinearAtten;
  float ExpAtten;
  float Cutoff;
};

uniform SceneLight
{
	SpotLight lightData;
} ;
                                                                                    
uniform Material
{
	vec4 diffuseColor;
	vec4 specColor;
	vec4 ambientColor;
	float shininess;
	float specularIntensity;

} mat;                                                                                                                                                                                                                                              
                                                             
uniform vec3 camPosition;                                                                                                             
uniform vec3 gCoef[9];                                                           
                                                                                            
vec4 CalcLightInternal(SpotLight Light, vec3 LightDirection, vec3 Normal)                   
{                                                                                           
    vec4 AmbientColor = Light.Color * Light.AmbientIntensity;
    float DiffuseFactor = dot(Normal, -LightDirection);                                     
                                                                                            
    vec4 DiffuseColor  = vec4(0, 0, 0, 0);                                                  
    vec4 SpecularColor = vec4(0, 0, 0, 0);                                                  
                                                                                            
    if (DiffuseFactor > 0) {                                                                
        DiffuseColor = Light.Color * Light.DiffuseIntensity * DiffuseFactor * mat.diffuseColor;
                                                                                            
        vec3 VertexToEye = normalize(camPosition - WorldPos0);                             
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));                     
        float SpecularFactor = dot(VertexToEye, LightReflect);                                      
        if (SpecularFactor > 0) {                                                           
            SpecularFactor = pow(SpecularFactor, mat.shininess);                               
            SpecularColor = Light.Color * mat.specularIntensity * SpecularFactor * mat.specColor;
        }                                                                                   
    }                                                                                       
    //DiffuseColor = vec4(1.0,0.3,0.3,1.0);                                                                                     
    return (AmbientColor + DiffuseColor + SpecularColor);                                   
}                                                                                           
                                                                                                                                                                                  
vec4 CalcPointLight(SpotLight l, vec3 Normal)                                              
{                                                                                           
    vec3 LightDirection = WorldPos0 - l.Position.xyz;                                           
    float Distance = length(LightDirection);                                                
    LightDirection = normalize(LightDirection);                                             
                                                                                            
    vec4 Color = CalcLightInternal(l, LightDirection, Normal);                         
    float Attenuation =  l.ConstAtten +                                                 
                         l.LinearAtten * Distance +                                        
                         l.ExpAtten * Distance * Distance;                                 
                                                                                     
    return Color / Attenuation;                                                             
}                                                                                           
                                                                                            
vec4 CalcSpotLight(SpotLight l, vec3 Normal)                                                
{                                                                                           
    vec3 LightToPixel = normalize(WorldPos0 - l.Position.xyz);                             
    float SpotFactor = dot(LightToPixel, l.Direction.xyz);                                      
                                                                                            
    if (SpotFactor > l.Cutoff) {                                                            
        vec4 Color = CalcPointLight(l, Normal);                                        
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));                   
	}                                                                                       
    else {                                                                                  
        return vec4(0.0,0,0.0,1.0);                                                               
    }                                                                                       
}      

vec3 calculateAmbientFromSH(vec3 N)
{
	return

      // constant term, lowest frequency //////
      C4 * gCoef[0] +

      // axis aligned terms ///////////////////
      2.0 * C2 * gCoef[1] * N.y + 
      2.0 * C2 * gCoef[2] * N.z +
      2.0 * C2 * gCoef[3] * N.x +

      // band 2 terms /////////////////////////
      2.0 * C1 * gCoef[4] * N.x * N.y +
      2.0 * C1 * gCoef[5] * N.y * N.z +
      C3 * gCoef[6] * N.z * N.z - C5 * gCoef[6] +
      2.0 * C1 * gCoef[7] * N.x * N.z +
      C1 * gCoef[8] * (N.x * N.x - N.y * N.y);
}                                                                                     
                                                                                            
void main()                                                                                 
{                                                                                           
    vec3 Normal = normalize(Normal0);                                                                                                                                           
    vec4 TotalLight = vec4(0.0,0.0,0.0,0.0);                                                                                                             
    TotalLight = CalcSpotLight(lightData, Normal);                                

	vec3 ambient = calculateAmbientFromSH(Normal);
	FragColor.rgb = TotalLight.rgb + ambient * mat.ambientColor.rgb /*+ vec3(0.2,0.01,0.0)*/;     
	FragColor.a = 1.0;                                                                          
   // FragColor = texture2D(gSampler, TexCoord0.xy)* TotalLight;
}