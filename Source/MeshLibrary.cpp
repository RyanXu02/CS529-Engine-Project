//------------------------------------------------------------------------------
//
// File Name:	MeshLibrary.cpp
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
#include "MeshLibrary.h"

#include "Stream.h"
#include "Mesh.h"
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
	std::unordered_map<std::string, const Mesh*> MeshLibrary::meshes{};
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	MeshLibrary::MeshLibrary(void)
	{
	}

	//--------------------------------------------------------------------------

	MeshLibrary::~MeshLibrary(void)
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
	const Mesh* MeshLibrary::Build(const std::string& meshName)
	{
		if (!Find(meshName)) {
			std::string filePath = std::string("./Data/Meshes/") + std::string(meshName) + std::string(".json");
			Stream stream(filePath);
			if (stream.IsValid() && stream.Contains("Mesh")) {
				Mesh* mesh = new Mesh();
				mesh->Read(stream);
				meshes[meshName] = mesh;
				return mesh;
			}
			else {
				return nullptr;
			}
		}
		return Find(meshName);
	}

	const Mesh* MeshLibrary::Find(const std::string meshName)
	{
		std::unordered_map<std::string, const Mesh*>::const_iterator got = meshes.find(meshName);
		if (got == meshes.end())
			return nullptr;
		else
			return got->second;
	}

	void MeshLibrary::DeleteAll()
	{
		for (auto& pair : meshes) {
			delete pair.second;
		}
		meshes.clear();
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace