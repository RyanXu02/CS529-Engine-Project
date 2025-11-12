//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template class for a new scene.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <Windows.h>

#include "Level2Scene.h"
#include "Scene.h"
#include "SceneSystem.h"

#include "Stream.h"

#include "SandboxScene.h"
#include "DemoScene.h"
#include "Level1Scene.h"

#include "Mesh.h"
#include "EntityFactory.h"

#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"

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

	Level2Scene::Level2Scene()
		: Scene("Level2Scene")
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

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

	void Level2Scene::Load()
	{
		meshSpaceship = new Mesh();
		meshSpaceship->BuildSpaceship();
	}

	bool Level2Scene::Initialize()
	{
		bool success = false;
		entitySpaceship = EntityFactory::Build("SpaceshipHoming");
		if (entitySpaceship) {
			Sprite* sprite = entitySpaceship->Get<Sprite>();
			if (sprite) {
				sprite->SetMesh(meshSpaceship);
				success = true;
			}
		}
		DGL_Color black{ 0.0, 0.0, 0.0, 1.0 };
		DGL_Graphics_SetBackgroundColor(&black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
		return success;
	}

	void Level2Scene::Update(float dt)
	{
		if (entitySpaceship) {
			MovementController(entitySpaceship);
			entitySpaceship->Update(dt);
		}

		if (DGL_Input_KeyTriggered('Z')) entitySpaceship->Get<Sprite>()->Alpha(0.5f);
		if (DGL_Input_KeyTriggered('X')) entitySpaceship->Get<Sprite>()->Alpha(1.0f);
	}



	void Level2Scene::Render() const
	{
		if (entitySpaceship) {
			entitySpaceship->Render();
		}
	}

	void Level2Scene::Shutdown()
	{
		delete entitySpaceship;
	}

	void Level2Scene::Unload()
	{
		delete meshSpaceship;
	}

	void Level2Scene::MovementController(Entity* entity)
	{
		Physics* physics = entity->Get<Physics>();
		Transform* transform = entity->Get<Transform>();

		if (physics && transform) {

			DGL_Vec2 mousePos = DGL_Input_GetMousePosition();
			DGL_Vec2 mousePosSS = DGL_Camera_ScreenCoordToWorld(&mousePos);
			Vector2D mouseposSS_V2D(mousePosSS.x, mousePosSS.y); // Convert to Vector2D

			Vector2D translation = transform->Translation();
			translation.Sub(mouseposSS_V2D);
			translation.Negate(); // wrong direction
			translation.Normalize();
			float heading = translation.ToAngleRad();
			entity->Get<Transform>()->Rotation(heading);
			translation.Scale(spaceshipSpeed);
			entity->Get<Physics>()->Velocity(translation);
		}
	}

#pragma endregion Private Functions

}	// namespace