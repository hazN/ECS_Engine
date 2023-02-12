// Vertex shader
#version 420

in vec3 vCol;
in vec3 vPos;
in vec3 vNormal;

// Going "out" to the fragment shader
out vec3 colour;			// varying
out vec3 fNormal;
out vec3 fVertWorldLocation;	// 

//uniform mat4 MVP;
uniform mat4 mModel;
uniform mat4 mModelInverseTranspose;		// mModel with Only Rotation;
uniform mat4 mView;
uniform mat4 mProjection;

void main()
{
	vec3 vertPosition = vPos;

	//	vertPosition.xyz *= 0.1f;
	//	vertPosition.x += 10.0f;

		// Output is in screen space 
		// x & y are in (normalized) screen space, z is the depth from the camera
	mat4 mMVP = mProjection * mView * mModel;

	gl_Position = mMVP * vec4(vertPosition, 1.0f);

	// The location of the vertex in WORLD SPACE 
	// for the lighting
	fVertWorldLocation.xyz = (mModel * vec4(vertPosition, 1.0f)).xyz;

	// Send the normals to the fragment shader
	// Rotate the normal if the model is rotated
	fNormal.xyz = (mModelInverseTranspose * vec4(vNormal, 1.0f)).xyz;

	colour = vCol;
}
