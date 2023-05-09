#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform float a = 1.0f;
uniform sampler2D ourTexture;
uniform bool affectedByLight = true;
uniform bool usesTex = false;
uniform float ambientStrength = 0.1;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    float specularStrength = 0.5;

    vec4 texColor = texture(ourTexture, TexCoord);
    //if(texColor.a < 0.1f)
    //{
    //    discard;
    //}

    vec4 resultColor = vec4(1.0);

    if (usesTex)
    {
        resultColor = texColor * vec4(ourColor.x * color.x, ourColor.y * color.y, ourColor.z * color.z, a);
    }
    else
    {
        resultColor = vec4(ourColor.x * color.x, ourColor.y * color.y, ourColor.z * color.z, a);
    }

    if (affectedByLight)
    {
        // ambient
        vec3 ambient = lightColor * material.ambient;

        // diffuse 
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = lightColor * (diff * material.diffuse);

        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = lightColor * (spec * material.specular);

        //ambient *= light.ambient;
        //diffuse *= light.diffuse;
        //specular *= light.specular;


        //vec3 ambient = light.ambient * material.ambient;
        //vec3 diffuse = light.diffuse * (diff * material.diffuse);
        //vec3 specular = light.specular * (spec * material.specular);

        resultColor *= vec4(ambient + diffuse + specular, a);
    }

    FragColor = resultColor;

}