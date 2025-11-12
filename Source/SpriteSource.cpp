//------------------------------------------------------------------------------
//
// File Name:	SpriteSource.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template for a new .cpp file.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "SpriteSource.h"

#include "Vector2D.h"

#include "Stream.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	//--------------------------------------------------------------------------
	// Public Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Public Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	SpriteSource::SpriteSource(void)
	{
	}

	//--------------------------------------------------------------------------

	SpriteSource::~SpriteSource(void)
	{
		if (textureResource) {
			DGL_Graphics_FreeTexture(const_cast<DGL_Texture**>(&textureResource));
		}
	}

#pragma endregion Constructors

	//--------------------------------------------------------------------------
	// Public Static Functions:
	//--------------------------------------------------------------------------

#pragma region Public Static Functions

#pragma endregion Public Static Functions

	//--------------------------------------------------------------------------
	// Public Functions:
	//--------------------------------------------------------------------------

#pragma region Public Functions

	void SpriteSource::LoadTexture(unsigned numCols, unsigned numRows, std::string_view textureName) {
		this->numCols = numCols;
		this->numRows = numRows;
		// std::string_view is not null-terminated, so we make a temp std::string copy of it to feed into the function, man....
		this->textureResource = DGL_Graphics_LoadTexture(std::string(textureName).c_str());
	}

	unsigned SpriteSource::GetFrameCount() const {
		return numCols * numRows;
	}

	void SpriteSource::UseTexture() const {
		DGL_Graphics_SetTexture(textureResource);
	}

	void SpriteSource::CalculateTextureOffset(unsigned frameIndex, Vector2D& uv) const {
		// Don't divide by zero please
		if (numCols == 0 || numRows == 0) {
			uv.x = 0, uv.y = 0;
			return;
		}

		float uSize = 1.0f / numCols;
		float vSize = 1.0f / numRows;

		uv.x = uSize * (frameIndex % numCols);
		uv.y = vSize * (frameIndex / numCols);
	}

	void SpriteSource::SetTextureOffset(unsigned frameIndex) const {
		Vector2D uv;
		CalculateTextureOffset(frameIndex, uv);
		DGL_Graphics_SetCB_TextureOffset(&uv);
	}

	void SpriteSource::Read(Stream& stream) {
		if (!stream.IsValid()) return;
		stream.PushNode("SpriteSource");
		stream.Read("NumCols", numCols);
		stream.Read("NumRows", numRows);
		std::string textureName;
		if (stream.Contains("Texture")) {
			stream.Read("Texture", textureName);
			if (textureName != "") {
				LoadTexture(numCols, numRows, "./Assets/" + textureName);
			}
		}
		stream.PopNode();
	}


#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace