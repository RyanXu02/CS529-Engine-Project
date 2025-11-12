//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.cpp
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

#include "SandboxScene.h"
#include "Scene.h"
#include "SceneSystem.h"

#include "LoggingSystem.h"

#include "Stream.h"
#include "Vector2D.h"

#include "DemoScene.h"
#include "level1Scene.h"
#include "level2Scene.h"

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

	SandboxScene::SandboxScene()
		: Scene("SandboxScene")
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

	void SandboxScene::Load()
	{
	}

	bool SandboxScene::Initialize()
	{
		return true;
	}

	void SandboxScene::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		UNREFERENCED_PARAMETER(dt);

			// NOTE: This call causes the engine to exit immediately.
			//   Make sure to remove it when you are ready to test out a new scene.
			//SceneSystem::EndScene();
	
	}

	void SandboxScene::Render() const
	{
	}

	void SandboxScene::Shutdown()
	{
	}

	void SandboxScene::Unload()
	{
	}

#pragma endregion Private Functions

}	// namespace