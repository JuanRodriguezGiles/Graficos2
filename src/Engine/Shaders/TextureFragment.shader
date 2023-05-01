#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform float a = 1.0f;
uniform sampler2D ourTexture;
uniform bool affectedByLight = true;
uniform bool usesTex = false;
uniform float ambientStrength = 0.1;
uniform vec3 lightPos;

void main()
{
    vec4 texColor = texture(ourTexture, TexCoord);
    if (texColor.a < 0.1f)
    {
        discard;
    }

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
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;

        vec3 ambient = ambientStrength * lightColor;
        resultColor *= vec4(ambient + diffuse, a);
    }

    FragColor = resultColor;

}