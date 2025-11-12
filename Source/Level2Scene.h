//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.h
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new scene.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Scene.h"

#include "Entity.h"

#include "Mesh.h"
#include "SpriteSource.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:

	// Typedefs:

	// Class Definition:
	class Level2Scene : public Scene
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		Level2Scene(void);

		// All objects need a virtual destructor to have their destructor called 
		~Level2Scene(void) override {};

		// Public Static Functions:
	public:

		// Public Functions:
	public:

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief Load any large assets required by the scene.
		void Load();

		// @brief Initialize the scene, including constructing the entities.
		//
		// @return bool = true if initialization successful, otherwise false.
		bool Initialize() override;

		// @brief Update the scene each frame.
		//
		// @param dt = Delta time (in seconds) of the last frame.
		void Update(float dt) override;

		// @brief Render the scene each frame.
		void Render() const override;

		// @brief Shutdown the scene, destroying any remaining entities.
		void Shutdown() override;

		// @brief Unload any large assets loaded for the scene.
		void Unload() override;

		// @brief movement controller for an entity
		void MovementController(Entity* entity);

		// Private Constants:
	private:
		const float spaceshipSpeed = 500.0f;

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		Entity* entitySpaceship{ nullptr };
		Mesh* meshSpaceship{ nullptr };

	};

}	// namespace