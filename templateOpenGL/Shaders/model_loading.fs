#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;
uniform vec3 viewPos;

struct Material
{
    float ambient;
    float diffuse;
    float specular;
    float shininess;
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

uniform bool lightOn;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    
    vec3 lightDir = normalize(-light.direction);
    // 漫反射着色
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    // 镜面光着色
    
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 合并结果
    vec3 ambient  = light.ambient  * texture(texture_diffuse1, TexCoords).rgb;
    vec3 diffuse  = light.diffuse  * diff * texture(texture_diffuse1, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(texture_diffuse1, TexCoords).rgb;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(Light light, vec3 Normal, vec3 viewDir, bool lightOn)
{
    if (!lightOn)
    {
        vec3 ambient = texture(texture_diffuse1, TexCoords).rgb * light.ambient;
        return ambient;
    }
    else
    {
    //环境光
     vec3 ambient = texture(texture_diffuse1, TexCoords).rgb * light.ambient;

     
    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse * texture(texture_diffuse1, TexCoords).rgb;
    //vec3 diffuse = diff * light.diffuse * material.diffuse;
    //vec3 diffuse = light.diffuse * texture(texture_normal1, TexCoords).rgb;


    // 镜面反射
    // float specularStrength = 0.5;
    
    //vec3 reflectDir = reflect(-lightDir, norm);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = texture(texture_diffuse1, TexCoords).rgb * light.specular * spec;
    //vec3 specular = material.specular * light.specular * spec;

    return (ambient + diffuse + specular);
    }
}

void main()
{    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcPointLight(light, Normal, viewDir, lightOn);
    //vec3 result = CalcDirLight(dirLight, Normal, viewDir);
    //result += CalcDirLight(dirLight, Normal, viewDir);
    FragColor = vec4(result, 1.0f);    
    //vec3 result = (specular + ambient + diffuse) * 
    //FragColor = vec4(result, 1.0);
    //vec4 result = vec4(ambient, 1.0);
    //FragColor = vec4(ambient + diffuse + specular, 1.0);
    //FragColor = vec4((ambient + diffuse + specular) * objectColor, 1.0);

}