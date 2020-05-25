#version 110

attribute vec3 position;
attribute vec4 color;
attribute vec3 texcoord0;

uniform vec4 constColor;
uniform mat4 matrixWorldViewProjT;

varying vec2 uv1;
varying vec2 uv2;//добавили ещё 2 текстуры
varying vec2 uv3;


void main()
{
	gl_Position		= vec4(position, 1.0) * matrixWorldViewProjT;
	gl_FrontColor	= color * constColor;
	uv1				= texcoord0.xy;
	uv2				= texcoord0.xy;
	uv3				= texcoord0.xy;
}