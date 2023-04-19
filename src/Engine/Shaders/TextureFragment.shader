#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
uniform float a = 1.0f;
uniform sampler2D ourTexture;
uniform bool affectedByLight = true;
uniform bool usesTex = false;

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
        resultColor *= vec4(lightColor, a);
    }

    FragColor = resultColor;

}