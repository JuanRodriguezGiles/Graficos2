#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);
uniform bool usesTexture = false;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    ourColor = aColor;
    Normal = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));

    if (usesTexture)
    {
        TexCoord = aTexCoord;
    }
    else
    {
        TexCoord = vec2(0.0f, 0.0f);
    }

}