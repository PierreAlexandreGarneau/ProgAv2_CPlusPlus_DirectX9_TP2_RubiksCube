// Binaire.cpp : Définit le point d'entrée pour l'application console.
//
#include "stdafx.h"

#include <windows.h>
#include <iostream>

struct VideoOptions_Desc
{
	bool isFullscreen;
	bool isHardwareAccelerated;
	bool isVerticalSync;
	bool isBorderless;
	bool isTransformAndLightingCapable;
	bool isAntialiasing2x;
	bool isAntialiasing4x;
	bool isAntialiasing8x;
	bool isAntialiasing16x;
	//[...]
};

void InitVideo(bool, bool, bool, bool, bool, bool, bool, bool, bool);
void InitVideo(const VideoOptions_Desc& options);
void InitVideo(WORD options);

void AfficherBinaire(WORD bn);

int main()
{
	// Flags
	{ 
		bool isFullscreen = true;
		bool isHardwareAccelerated = true;
		bool isVerticalSync = false;
		bool isBorderless = true;
		bool isTransformAndLightingCapable = false;
		bool isAntialiasing2x = true;
		bool isAntialiasing4x = false;
		bool isAntialiasing8x = false;
		bool isAntialiasing16x = false;
		//[...]

		InitVideo(
			isFullscreen, 
			isHardwareAccelerated, 
			isVerticalSync, 
			isBorderless, 
			isTransformAndLightingCapable, 
			isAntialiasing2x, 
			isAntialiasing4x, 
			isAntialiasing8x, 
			isAntialiasing16x);

	}

	{
		VideoOptions_Desc options;
		options.isFullscreen = true;
		options.isHardwareAccelerated = false;
		options.isVerticalSync = false;
		options.isBorderless = false;
		options.isTransformAndLightingCapable = true;
		options.isAntialiasing2x = false;
		options.isAntialiasing4x = true;
		options.isAntialiasing8x = false;
		options.isAntialiasing16x = false;
			
		InitVideo(options);
	}

	{
		//const WORD DRAPEAU1 = 1;
		//const WORD DRAPEAU2 = 2;
		//const WORD DRAPEAU3 = 4;
		//const WORD DRAPEAU4 = 8;
		//const WORD DRAPEAU5 = 16;
		//const WORD DRAPEAU6 = 32;
		//const WORD DRAPEAU7 = 64;
		//const WORD DRAPEAU8 = 128;
		//const WORD DRAPEAU9 = 256;
		//// [...]
		//const WORD DRAPEAU16 = 65535;

		const WORD DRAPEAU1 = 0x0001;
		const WORD DRAPEAU2 = 0x0002;
		const WORD DRAPEAU3 = 0x0004;
		const WORD DRAPEAU4 = 0x0008;
		const WORD DRAPEAU5 = 0x0010;
		const WORD DRAPEAU6 = 0x0020;
		const WORD DRAPEAU7 = 0x0040;
		const WORD DRAPEAU8 = 0x0080;
		const WORD DRAPEAU9 = 0x0100;
		// [...]
		const WORD DRAPEAU16 = 0xFFFF;

		// 4 octets = 32 bits
		// 00000000 00000000 00000000 00000000
		WORD flags = DRAPEAU1 | DRAPEAU3;

		// Operateur OU Binaire (|)
		//00000000 00000001
		//        |
		//00000000 00000100
		// ---------------
		//00000000 00000101

		// Operateur ET Binaire (&)
		//00000000 00000101
		//        &
        //00000000 00000100 
		//-----------------
		//00000000 00000100

		if ((flags & DRAPEAU3) != 0)
		{
			std::cout << "Drapeau3 est contenu" << std::endl;
		}

		WORD flags2 = 5;
	    // 0000000 00000101

		InitVideo(DRAPEAU1 | DRAPEAU3);

		AfficherBinaire(flags);
	}
    return 0;
}

void InitVideo(
	bool isFullscreen,
	bool isHardwareAccelerated,
	bool isVerticalSync,
	bool isBorderless,
	bool isTransformAndLightingCapable,
	bool isAntialiasing2x,
	bool isAntialiasing4x,
	bool isAntialiasing8x,
	bool isAntialiasing16x)
{

}

void InitVideo(const VideoOptions_Desc& options)
{

}

void InitVideo(WORD options)
{

}

void AfficherBinaire(WORD bn)
{
	std::cout << bn << std::endl;

	WORD mask = 0x8000;

	for (int i = 0; i < sizeof(WORD) * 8; i++)
	{
		std::cout << ((bn & mask) ? 1 : 0);
		bn <<= 1;
	}
	std::cout << std::endl;
}