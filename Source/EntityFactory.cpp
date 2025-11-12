//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.cpp
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
#include "EntityFactory.h"

#include "Stream.h"
#include "Entity.h"

#include "EntityContainer.h"

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
	EntityContainer EntityFactory::archetypes{};
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	//EntityFactory::EntityFactory(void)
	//{
	//}

	//--------------------------------------------------------------------------

	//EntityFactory::~EntityFactory(void)
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
	Entity* EntityFactory::Build(std::string_view entityName) {
		Entity* archetype = archetypes.FindByName(entityName);
		if (!archetype) {
			std::string filePath = std::string("./Data/Archetypes/") + std::string(entityName) + std::string(".json");
			Stream stream(filePath);
			if (stream.IsValid() && stream.Contains("Entity")) {
				Entity * entity = new Entity();
				entity->Read(stream);
				archetypes.Add(entity);
				return new Entity(entity);
			}
		}
		else {
			return new Entity(archetype);
		}
		return nullptr;
	}

	void EntityFactory::DeleteAll()
	{
		archetypes.DeleteAll();
	}


#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace