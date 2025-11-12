//------------------------------------------------------------------------------
//
// File Name:	Sprite.cpp
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
#include "Sprite.h"

#include "Transform.h"
#include "Entity.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "Stream.h"

#include "MeshLibrary.h"
#include "SpriteSourceLibrary.h"
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

	Sprite::Sprite(void)
	{
	}

	Sprite::Sprite(const Sprite * other)
	{
		frameIndex = other->frameIndex;
		alpha = other->alpha;
		tintColor = other->tintColor;
		mesh = other->mesh;
		spriteSource = other->spriteSource;
		text = other->text;
	}
	//--------------------------------------------------------------------------

	//Sprite::~Sprite(void)
	//{
	//}

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
	void Sprite::Render() const {
		Transform* transform = Parent()->Get<Transform>();
		if (!transform || !mesh) {
			return;
		}

		if (spriteSource) {
			// Set the DGL shader mode to 'TEXTURE'.
			DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
			// Bind the sprite source's texture using UseTexture.
			spriteSource->UseTexture();
			// Set the sprite source's texture offset.
			spriteSource->SetTextureOffset(frameIndex);
		}
		else {
			// Set the DGL shader mode to 'COLOR'.
			DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
		}

		// Pass the alpha value to the DGL.
		DGL_Graphics_SetCB_Alpha(alpha);
		// Pass the tint color to the DGL.
		DGL_Graphics_SetCB_TintColor(&tintColor);

		if (text == "") {
			DGL_Graphics_SetCB_TransformMatrix(&transform->GetMatrix());
			mesh->Render();
		}
		else {
			Matrix2D transformMatrixCopy = transform->GetMatrix();
			Matrix2D offset;
			offset.Translate(transform->Scale().x, 0.0f);
			for (char c : text) {
				unsigned index = c-' ';
				if (spriteSource) {
					spriteSource->SetTextureOffset(index);
				}
				DGL_Graphics_SetCB_TransformMatrix(&transformMatrixCopy);
				mesh->Render();
				transformMatrixCopy = offset * transformMatrixCopy;
			}

		}

	}

	void Sprite::Read(Stream& stream) {
		// Check for valid stream (optional).
		DRAGON_ASSERT(stream.Contains("Sprite"), "Sprite::Read: Failed to find required key: Sprite");
		// Traverse down the tree to the "Sprite" object (PushNode).
		stream.PushNode("Sprite");
		// Read the alpha value from the stream.
		stream.Read("Alpha", alpha);
		// Read the frameIndex value from the stream.
		stream.Read("FrameIndex", frameIndex);

		std::string meshName;
		stream.Read("Mesh", meshName);
		if (meshName != "") {
			mesh = MeshLibrary::Build(meshName);
		}

		std::string spriteSourceName;
		stream.Read("SpriteSource", spriteSourceName);
		if (spriteSourceName != "") {
			spriteSource = SpriteSourceLibrary::Build(spriteSourceName);
		}
		// Return to the original location in the tree (PopObject).
		stream.PopNode();

	}

	void Sprite::SetFrame(unsigned frame) {
		LoggingSystem::Verbose("Sprite::SetFrame: frame index = {}", frame);
		if (spriteSource) {
			unsigned frameCount = spriteSource->GetFrameCount();
			if (frame < frameCount) {
				frameIndex = frame;
			}
		}
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace