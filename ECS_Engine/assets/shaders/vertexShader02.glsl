//#version 420 core
//layout(location = 0)in vec4 vColour;			// Was vec3
//layout(location = 1)in vec4 vPosition;			// Was vec3
//layout(location = 2)in vec4 vNormal;			// Vertex normal
//layout(location = 3)in vec4 vUVx2;				// 2 x Texture coords
//layout(location = 4)in vec4 vTangent;			// For bump mapping
//layout(location = 5)in vec4 vBiNormal;			// For bump mapping
//layout(location = 6)in vec4 vBoneID;			// For skinned mesh (FBX)
//layout(location = 7)in vec4 vBoneWeight;		// For skinned mesh (FBX)
//
//// Going "out" to the fragment shader
//out vec4 fColour;		// colour;			
//out vec4 fNormal;
//out vec4 fVertWorldLocation;	// using only matModel
//out vec4 fUVx2;
//out vec4 fTangent;
//out vec4 fBinormal;
//
//uniform mat4 mModel;
//uniform mat4 mModelInverseTranspose;		// mModel with Only Rotation;
//uniform mat4 mView;
//uniform mat4 mProjection;
//
//
//void main()
//{
//	vec3 vertPosition = vPosition.xyz;
//	
//    mat4 mMVP = mProjection * mView * mModel;
//	
//	gl_Position = mMVP * vec4(vertPosition, 1.0f);
//	fVertWorldLocation.xyz = (mModel * vec4(vertPosition, 1.0f)).xyz;
//	fVertWorldLocation.w = 1.0f;
//	fNormal.xyz = normalize(mModelInverseTranspose * vec4(vNormal.xyz, 1.0f)).xyz;
//	fNormal.w = 1.0f;
//	fColour = vColour;
//	fUVx2 = vUVx2;
//	fTangent = vTangent;
//	fBinormal = vBiNormal;
//}

#version 420 core
layout(location = 0)in vec4 vColour;			// Was vec3
layout(location = 1)in vec4 vPosition;			// Was vec3
layout(location = 2)in vec4 vNormal;			// Vertex normal
layout(location = 3)in vec4 vUVx2;				// 2 x Texture coords
layout(location = 4)in vec4 vTangent;			// For bump mapping
layout(location = 5)in vec4 vBiNormal;			// For bump mapping
layout(location = 6)in vec4 vBoneID;			// For skinned mesh (FBX)
layout(location = 7)in vec4 vBoneWeight;		// For skinned mesh (FBX)
out vec4 v_Position;
out vec4 v_Color;
uniform mat4 mView;
uniform mat4 mModel;
uniform mat4 mProjection;

void main()
{
	vec3 vertPosition = vPosition.xyz;
    v_Position = vPosition;
    v_Color = vColour;
    mat4 mMVP = mProjection * mView * mModel;
	gl_Position = vec4(vertPosition, 1.0f);
}
