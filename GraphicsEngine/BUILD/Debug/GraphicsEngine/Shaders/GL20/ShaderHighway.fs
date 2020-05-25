#version 110

varying vec2 uv1;
varying vec2 uv2;//добавили координаты
varying vec2 uv3;

uniform sampler2D texture1;
uniform sampler2D texture2;//добавили текстуры
uniform sampler2D texture3;


void main()
{//386 x 64
	vec2 scale1 = vec2(-1, 0.5);
	vec2 uv1Scale = vec2(1, 2048. / 1024.) * scale1;
	vec3 color1 = texture2D( texture1, uv1.xy * uv1Scale ).rgb;

	vec2 uv2Scale = vec2(1, 1) * 2. * scale1;
	vec3 color2 = texture2D( texture2, uv2.xy * uv2Scale ).rgb;

	vec2 uv3Scale = vec2(1, 1) * 0.02 * scale1;
	vec3 color3 = texture2D( texture3, uv3.xy * uv3Scale ).rgb;
	
	gl_FragColor.rgb = color1;// * color2 * color3 * 2.;
	gl_FragColor.a = 1.0;
}
