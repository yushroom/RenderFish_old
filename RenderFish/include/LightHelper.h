//***************************************************************************************
// LightHelper.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Helper classes for lighting.
//***************************************************************************************

#ifndef LIGHTHELPER_H
#define LIGHTHELPER_H

#include <Windows.h>
#include <xnamath.h>

#include "Vector.h"


namespace RenderFish
{


	// Note: Make sure structure alignment agrees with HLSL structure padding rules. 
	//   Elements are packed into 4D vectors with the restriction that an element
	//   cannot straddle a 4D vector boundary.

	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		Vector4 Ambient;
		Vector4 Diffuse;
		Vector4 Specular;
		Vector3 Direction;
		float Pad; // Pad the last float so we can set an array of lights if we wanted.
	};

	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(this)); }

		Vector4 Ambient;
		Vector4 Diffuse;
		Vector4 Specular;

		// Packed into 4D vector: (Position, Range)
		Vector3 Position;
		float Range;

		// Packed into 4D vector: (A0, A1, A2, Pad)
		Vector3 Att;
		float Pad; // Pad the last float so we can set an array of lights if we wanted.
	};

	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(this)); }

		Vector4 Ambient;
		Vector4 Diffuse;
		Vector4 Specular;

		// Packed into 4D vector: (Position, Range)
		Vector3 Position;
		float Range;

		// Packed into 4D vector: (Direction, Spot)
		Vector3 Direction;
		float Spot;

		// Packed into 4D vector: (Att, Pad)
		Vector3 Att;
		float Pad; // Pad the last float so we can set an array of lights if we wanted.
	};

	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		Vector4 Ambient;
		Vector4 Diffuse;
		Vector4 Specular; // w = SpecPower
		Vector4 Reflect;
	};

}

#endif // LIGHTHELPER_H