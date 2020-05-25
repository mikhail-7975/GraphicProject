#version 110


attribute vec3 position;
//attribute vec4 color;
attribute vec3 normal;
attribute vec3 texcoord0;

uniform vec4 constColor;
uniform mat4 matrixWorldViewProjT;

varying vec3 localPosition;
varying vec3 localNormal;
varying vec2 uv1;
varying vec2 uv2;
varying vec4 texCoords;


void main()
{
	gl_Position		= vec4(position, 1.0) * matrixWorldViewProjT;
	gl_FrontColor	= constColor;
    uv1				= texcoord0.xy;
	uv2				= texcoord0.xy;
	texCoords       =  vec4(position, 1.0);
	localPosition	= position;
	localNormal		= normal;
}


