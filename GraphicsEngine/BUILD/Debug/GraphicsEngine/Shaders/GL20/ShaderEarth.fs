/*#version 110

varying vec4 texCoords;
uniform sampler2D texture;

varying vec2 uv1;

void main()
{
	vec2 Longitude_Latitude = vec2((atan(texCoords.z, texCoords.x)) * 0.159156 + 0.50001, (-sin(texCoords.y) + 0.49));
	//vec2 Longitude_Latitude = vec2((atan(texCoords.z, texCoords.x)) * 0.14, (-sin(texCoords.y) + 0.49));
	//vec2 scale = vec2(0.5, 0.5);
	//vec3 colori = texture2D(texture, uv1.xy * scale ).rgb;
	//gl_FragColor.rgb = colori / 1.;
    //gl_FragColor.a = 1.0;
	gl_FragColor = texture2D(texture, Longitude_Latitude);
}*/

#version 110

uniform sampler2D texture;

varying vec3 localPosition;
varying vec3 localNormal;
varying vec2 uv1;

void main()
{
	vec2 scale = vec2(1., 1);
	vec3 color_forTexture = texture2D( texture, uv1.xy * scale).rgb;	
	gl_FragColor.rgb =  color;
    gl_FragColor.a = 1.0;
}

