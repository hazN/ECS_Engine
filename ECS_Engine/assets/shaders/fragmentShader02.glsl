//#version 420 core
//
//in vec4 fColour;		// colour;			
//in vec4 fNormal;
//in vec4 fVertWorldLocation;	// using only matModel
//in vec4 fUVx2;
//in vec4 fTangent;
//in vec4 fBinormal;
//
//out vec4 pixelOutputColour;
//
//uniform vec4 RGBA_Colour;
//uniform bool bUseRGBA_Colour;
//
//uniform vec4 specularColour;
//
//uniform bool bDoNotLight;
//uniform vec4 eyeLocation;
//
//
//void main()
//{
//    vec3 materialColour = fColour.rgb;
//    vec3 normalValue = fNormal.xyz;
//    
//    float alphaTransparency = RGBA_Colour.w;
//    materialColour = RGBA_Colour.rgb;
//    //pixelOutputColour = vec4(materialColour.rgb, alphaTransparency);
//    pixelOutputColour = fColour;
//}

#version 420 core
layout(location = 0) out vec4 color;
in vec4 v_Position;
in vec4 v_Color;
uniform vec4 RGBA_Colour;
void main()
{
    //color = vec4(0.4, 0.4, 0.7, 1.0);
    color = RGBA_Colour;
}