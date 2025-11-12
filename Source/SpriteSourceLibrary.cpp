//------------------------------------------------------------------------------
//
// File Name:	SpriteSourceLibrary.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "SpriteSourceLibrary.h"

#include "Stream.h"
#include "SpriteSource.h"
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
	std::unordered_map<std::string, const SpriteSource*> SpriteSourceLibrary::spriteSources{};
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	SpriteSourceLibrary::SpriteSourceLibrary(void)
	{
	}

	//--------------------------------------------------------------------------

	SpriteSourceLibrary::~SpriteSourceLibrary(void)
	{
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
	const SpriteSource* SpriteSourceLibrary::Build(const std::string& spriteSourceName)
	{
		if (!Find(spriteSourceName)) {
			std::string filePath = std::string("./Data/SpriteSources/") + std::string(spriteSourceName) + std::string(".json");
			Stream stream(filePath);
			if (stream.IsValid() && stream.Contains("SpriteSource")) {
				SpriteSource* spriteSource = new SpriteSource();
				spriteSource->Read(stream);
				spriteSources[spriteSourceName] = spriteSource;
				return spriteSource;
			}
			else {
				return nullptr;
			}
		}
		return Find(spriteSourceName);
	}

	const SpriteSource* SpriteSourceLibrary::Find(const std::string spriteSourceName)
	{
		std::unordered_map<std::string, const SpriteSource*>::const_iterator got = spriteSources.find(spriteSourceName);
		if (got == spriteSources.end())
			return nullptr;
		else
			return got->second;
	}

	void SpriteSourceLibrary::DeleteAll()
	{
		for (auto& pair : spriteSources) {
			delete pair.second;
		}
		spriteSources.clear();
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace