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

void main()
{
	vec3 p = position;
	vec3 p_normed = normalize(p);

	float _time = time.x; // время, ограниченное нулём и 1

	vec3 realPos = p * (1.0 - _time) + p_normed * _time; 

	gl_Position = vec4(realPos, 1.0) * matrixWorldViewProjT;	// DirectX

	//gl_Position = matrixWorldViewProjT * vec4(position, 1.0);	// OpenGL
	//gl_Position = vec4(position, 1.0) * matrixWorldViewProjT;	// DirectX //закомменчено
	gl_FrontColor = color * constColor;
}