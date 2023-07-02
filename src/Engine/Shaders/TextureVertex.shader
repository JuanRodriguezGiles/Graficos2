#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{
    mat4 mvp = projection * view * model;

    mat4 normalMatrix = mat4(mvp);

    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));

    TexCoord = aTexCoord;

    gl_Position = projection * view * vec4(FragPos, 1.0f);
}