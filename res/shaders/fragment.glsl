#version 460 core 

out vec4 FragColor;

in vec2 TexCoord;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2( 1.0 - TexCoord.x, TexCoord.y)), 0.2);
    FragColor = vec4(lightColor * objectColor, 1.0f);
}