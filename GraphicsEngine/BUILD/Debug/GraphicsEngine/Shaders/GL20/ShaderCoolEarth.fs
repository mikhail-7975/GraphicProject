#version 110

struct Light
{
	vec4	type;		// тип источника
	vec4	position;	// позиция источника (есть у Point и Spot)
	vec4	direction;	// направление света
	vec4	color;		// (цвет.r, цвет.g, цвет.b, интенсивность)
};

uniform sampler2D texture;
uniform sampler2D textureNormal;
varying vec2 uv1;
varying vec2 uv2;

float epsilon = 0.001;

// Shader parameters
uniform vec4 camPosition; // передаём позицию камеры
uniform mat4 matWorldNormal;
uniform mat4 matWorldT;
uniform vec4 materialColor;
uniform vec4 lightsCount;
uniform Light lights[3];

varying vec3 localPosition;
varying vec3 localNormal;

//dot возвращает косинус угла между векторами
//clamp - нормировка clamp(что нормаровать, от чего, до чего)

float _cosBetweenVecrors(vec3 a, vec3 b) {
	return (dot(a, b) / (length(a) * length(b)) );
}

vec3 calcDiffuse(vec4 lightCol, vec3 lightPosAndDir, vec3 vertexNormal)
{
	float diffuse = clamp( dot(-lightPosAndDir, vertexNormal), 0.0, 1.0 );

	// Цвет = diffuse * (цвет источника) * (интенсивность источника)
	vec3 color = diffuse * lightCol.rgb * lightCol.a;

	return color;
}

float calcIntensiveFromAngle(vec3 LightDir, vec3 vertPos) {
	float I;
	float cos_a = _cosBetweenVecrors(vertPos, LightDir);
	float cos_phi_2 = 0.8;
	float cos_theta_2 = 0.99;
	I = pow( (cos_a - cos_phi_2)/(cos_theta_2 - cos_phi_2) , 0.5);
	return I;
}

//.xyz vec4 -> vec3
 float calcSpecular(vec3 LightDir, vec3 vertPos, vec3 vertNormal) {
 	 vec3 H = normalize(normalize(camPosition.xyz - vertPos) - LightDir);
	 float reflectCoef = 20.0;
	 float specLight = pow(clamp( dot(H, vertNormal), 0.0, 1.0), reflectCoef);
	 return specLight;
 }

float calcAttenuation(vec3 position, float lightType) {
	if (abs(lightType - 1.0) < epsilon)
		return 1.;
	float att0 = 1.0;
	float att1 = 0.0; //какие коэффициенты взять?
	float att2 = 0.05;
	float d = length(position);
	return 1. / (att0 + att1 * d + att2 * d * d);
}

vec3 calculateGlobalNormal(vec3 color, vec3 normalFromVertex) {
	vec3 nLoc = color * 2. - vec3(1., 1., 1.);
	vec3 t = normalize(cross(normalFromVertex, vec3(1., 1., 1.)));//касательная
	vec3 b = normalize(cross(normalFromVertex, t));
	vec3 nGlob = normalize(nLoc.x * t + nLoc.y * b + nLoc.z * normalFromVertex);
	return nGlob;	
}

void main()
{
	vec2 scale = vec2(1., 1);
	vec3 color_forTexture = texture2D( texture, uv1.xy * scale).rgb;
	vec3 color_forNormalTexture = texture2D( textureNormal, uv2.xy * scale).rgb;
	vec3 col = vec3(0,0,0);

	// Переводим нормаль из локальной в глобальную систему координат
	vec3 vertexNormal = (vec4(localNormal, 0.0) * matWorldNormal).xyz;
	vertexNormal = normalize(vertexNormal);
	vertexNormal = calculateGlobalNormal(color_forNormalTexture, vertexNormal);

	// Переводим позицию из локальной в глобальную систему координат
	vec3 vertexPos = (vec4(localPosition, 1.0) * matWorldT).xyz;
	
	for (int i = 0; i < 1; ++i)
	{
		// Выходим, как только закончились источники освещения
        if (float(i) >= lightsCount.x) break;
		
		float type = lights[i].type.x;
		
		
		vec4 lightCol = lights[i].color;
		vec3 lightPosAndDir = vec3(0,0,0);
	
		// Directional light
        if (abs(type - 1.0) < epsilon)
		{
			lightPosAndDir = normalize(lights[i].direction.xyz).xyz;
		}
		// Point light
		else if (abs(type - 2.0) < epsilon)
		{
			lightPosAndDir = vertexPos - lights[i].position.xyz;
		}
		//Spot light 
		else if (abs(type - 3.0) < epsilon)
		{	
			float I;
			float cos_a = _cosBetweenVecrors(lights[i].direction.xyz, normalize(-lights[i].position.xyz + vertexPos).xyz);
			float cos_phi_2 = 0.1;
			float cos_theta_2 = 0.2;
			I = pow( clamp((cos_a -  cos_phi_2)/(cos_theta_2 - cos_phi_2), 0., 1.) , 20.0);
			lightPosAndDir = vertexPos - lights[i].position.xyz * I;
//			float I = calcIntensiveFromAngle(lightPosAndDir, vertexPos);
	//		lightPosAndDir *= I;
		}
		//calcSpecular(vec3 LightDir, vec3 vertPos, vec3 vertNormal)
		//col += materialColor.rgb * calcDiffuse(lightCol, lightPosAndDir, vertexNormal) * calcAttenuation(lightPosAndDir, type) * calcSpecular(lightPosAndDir, vertexPos, vertexNormal);//
		//vec3 kostyl = materialColor.rgb * calcDiffuse(lightCol, lightPosAndDir, vertexNormal) * calcAttenuation(lightPosAndDir, type); ///* */
		vec3 diffuse = calcDiffuse(lightCol, lightPosAndDir, vertexNormal);
		vec3 col_ = materialColor.rgb;
		float specular = calcSpecular(lightPosAndDir, vertexPos, vertexNormal);
		col += (diffuse + specular) * col_ * calcAttenuation(lightPosAndDir, type);
	}
	
	gl_FragColor = vec4(col * color_forTexture, 1.0);
     //   gl_FragColor.a = 1.0;
}
   