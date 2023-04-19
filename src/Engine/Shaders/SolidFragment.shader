#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform vec3 color = vec3(1.0f, 1.0f, 1.0f);

uniform float a = 1.0f;

vec3 lightColor = vec3(0, 98.0f, 255.0f);

void main()
{
   FragColor = vec4(ourColor.x * color.x, ourColor.y * color.y, ourColor.z * color.z, a);

   float ambientStrength = 0.1;
   vec3 ambient = ambientStrength * lightColor;

   vec3 result = ambient * ourColor;
   FragColor = vec4(result, 1.0);
}