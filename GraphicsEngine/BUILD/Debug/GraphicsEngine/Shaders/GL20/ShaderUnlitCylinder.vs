#version 110

// Vertex structure
// Set order of vertex structure (position, color)
// Search in C++ code funciton GL20Mesh::Render()
// glVertexAttribPointer(0, ...) // this is "position"
// glVertexAttribPointer(1, ...) // this is "color"
attribute vec3 position;
attribute vec4 color;

// Shader parameters
// Search in C++ code functions like "glUniform4"
// i.e. functions: glUniform4fv(), glUniformMatrix4fv().
// These functions pass to shader parameters listed below
uniform vec4 constColor;				//
uniform mat4 matrixWorldViewProjT;		//появились из materials.cpp
uniform vec4 time;						//
uniform mat4 matrixWorldViewProjTopMatrix;
uniform mat4 matrixWorldViewProjBottomMatrix;

void main()
{
	vec3 pos = position;
	float h = (pos.y + 1.) / 2.;
	//mat4 rotationMatrix = matrixWorldViewProjBottomMatrix * (1. - h) + matrixWorldViewProjTopMatrix * h;//+ matrixWorldViewProjT;// + matrixWorldViewProjBottomMatrix * h;// * (1. - h);
	mat4 rotMatrix = matrixWorldViewProjTopMatrix * h +  matrixWorldViewProjBottomMatrix * (1. - h);


	gl_Position = vec4(pos, 1.)  * rotMatrix;
	gl_FrontColor = color* constColor; //vec4(vec3(0., pos.y, 0.), 0.);//, 0.);// 
}