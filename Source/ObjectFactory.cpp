//------------------------------------------------------------------------------
//
// File Name:	ObjectFactory.cpp
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
#include "ObjectFactory.h"

#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"
#include "Animation.h"
#include "BehaviorSpaceship.h"
#include "BehaviorBullet.h"
#include "BehaviorAsteroid.h"
#include "BehaviorHudText.h"
#include "BehaviorTeleporter.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"

#include "LoggingSystem.h"

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

	ObjectFactory::ObjectFactory(void)
	{
		Register("Transform", []() { return new Transform(); });
		Register("Sprite", []() { return new Sprite(); });
		Register("Physics", []() { return new Physics(); });
		Register("Animation", []() { return new Animation(); });
		Register("BehaviorSpaceship", []() { return new BehaviorSpaceship(); });
		Register("BehaviorBullet", []() { return new BehaviorBullet(); });
		Register("BehaviorAsteroid", []() { return new BehaviorAsteroid(); });
		Register("BehaviorHudText", []() { return new BehaviorHudText(); });
		Register("BehaviorTeleporter", []() { return new BehaviorTeleporter(); });
		Register("ColliderCircle", []() { return new ColliderCircle(); });
		Register("ColliderLine", []() { return new ColliderLine(); });
	}

	//--------------------------------------------------------------------------

	ObjectFactory::~ObjectFactory(void)
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
	bool ObjectFactory::Register(const std::string& objectName, objectConstructor constructor)
	{
		if (IsRegistered(objectName))
		{
			LoggingSystem::Warning("ObjectFactory::Register: Attempted to register duplicate object name: {}", objectName);
			return false;
		}
		registry[objectName] = constructor;
		return true;
	}

	Object* ObjectFactory::Create(const std::string& objectName) const
 	{
		auto it = registry.find(objectName);
		if (it != registry.end())
		{
			return it->second();
		}
		return nullptr;
	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace