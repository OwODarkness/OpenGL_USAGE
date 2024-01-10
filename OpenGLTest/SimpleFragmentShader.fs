#version 330 core
out vec4 FragColor;
in vec3 outColor;
in vec2 outTexCor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alpha;
void main()
{
  FragColor = mix(texture(texture1, outTexCor), texture(texture2, vec2(-outTexCor.x, outTexCor.y)), alpha);
}