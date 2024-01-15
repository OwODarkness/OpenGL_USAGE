#version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec2 aTexCor;
out vec2 outTexCor;

uniform mat4 transform;

void main()
{
  gl_Position = transform * vec4(aPos,1.0);
  outTexCor = vec2(aTexCor.x,aTexCor.y);
}