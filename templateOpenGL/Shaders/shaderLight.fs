#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    float constant;
    float linear;
    float quadratic;

    //spotlight specs
    float cutoff;
    float outerCutoff;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

vec3 lightDir   = normalize(light.position - FragPos);
vec3 viewDir    = normalize(viewPos - FragPos);

uniform bool isFlashLight;


void main()
{
    vec3 lightDir = normalize(light.position - FragPos);


    //衰减
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    //手电筒判断
    if (isFlashLight)
    {
        float theta = dot(lightDir, normalize(-light.direction));
        float epsilon = light.cutoff - light.outerCutoff;
        float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0); 
       
            //环境光
            //float ambientStrength = 0.1;
            vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambient;

            //漫反射
            vec3 norm = normalize(Normal);
            //vec3 lightDir = normalize(-light.direction);
            
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * light.diffuse * texture(material.diffuse, TexCoords).rgb;

            //镜面反射
            //float specularStrength = 0.5;
            vec3 viewDir = normalize(viewPos - FragPos);
            //vec3 reflectDir = reflect(-lightDir, norm);
            vec3 halfwayDir = normalize(lightDir + viewDir);
            //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//32：shininess
            float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
            vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.specular;
                
            ambient *= attenuation;
            diffuse *= attenuation;
            specular *= attenuation;

            diffuse  *= intensity;
            specular *= intensity;

            vec3 result = (specular + ambient + diffuse);

            float gamma = 2.2;
            //FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
            result = pow(result, vec3(1.0/gamma));

            FragColor = vec4(result, 1.0);
        
    }
    else
    {
    //环境光
    //float ambientStrength = 0.1;
    vec3 ambient = texture(material.diffuse, TexCoords).rgb * light.ambient;

    //漫反射
    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(-light.direction);
    
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * texture(material.diffuse, TexCoords).rgb;

    //镜面反射
    //float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);//32：shininess
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.specular;
        
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = (specular + ambient + diffuse);

    float gamma = 2.2;
    //FragColor.rgb = pow(FragColor.rgb, vec3(1.0/gamma));
    result = pow(result, vec3(1.0/gamma));
 
    FragColor = vec4(result, 1.0);

    
    }
    //FragColor = vec4(0.2f * objectColor, 1.0);
    //FragColor = vec4(objectColor, 1.0);
    //FragColor = vec4(ambient + diffuse, 1.0f);
}