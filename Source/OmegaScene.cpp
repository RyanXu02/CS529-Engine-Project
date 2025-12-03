//------------------------------------------------------------------------------
//
// File Name:	OmegaScene.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 6
// Purpose:		Omega Scene.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include <Windows.h>

#include "OmegaScene.h"
#include "Scene.h"
#include "SceneSystem.h"

#include "EntityFactory.h"
#include "MeshLibrary.h"

#include "ScoreSystem.h"

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

	OmegaScene::OmegaScene()
		: Scene("OmegaScene"), asteroidSpawnCount(0)
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

	void OmegaScene::Load()
	{
		ScoreSystem::Instance().NewGame();
	}

	bool OmegaScene::Initialize()
	{
		Entity* entityArena = EntityFactory::Build("Arena");
		if (entityArena) {
			this->AddEntity(entityArena);
		}

		Entity* SpaceshipOmega = EntityFactory::Build("SpaceshipOmega");
		if (SpaceshipOmega) {
			this->AddEntity(SpaceshipOmega);
		}

		Entity* OmegaScore = EntityFactory::Build("OmegaScore");
		if (OmegaScore) {
			this->AddEntity(OmegaScore);
		}

		Entity* OmegaHighScore = EntityFactory::Build("OmegaHighScore");
		if (OmegaHighScore) {
			this->AddEntity(OmegaHighScore);
		}

		Entity* OmegaWaveCount = EntityFactory::Build("OmegaWaveCount");
		if (OmegaWaveCount) {
			this->AddEntity(OmegaWaveCount);
		}

		DGL_Color black{ 0.0, 0.0, 0.0, 1.0 };
		DGL_Graphics_SetBackgroundColor(&black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		asteroidSpawnCount = asteroidSpawnInitial;

		ScoreSystem::Instance().Reset();
		return true;
	}

	void OmegaScene::Update(float dt)
	{
		// Tell the compiler that the 'dt' variable is unused.
		//UNREFERENCED_PARAMETER(dt);
		if (!FindEntity("Asteroid")) SpawnWave();
		UpdateEntities(dt);
		CheckCollisions();
		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
		// SceneSystem::EndScene();
	}

	void OmegaScene::Render() const
	{
		RenderEntities();
	}

	void OmegaScene::Shutdown()
	{
		DeleteEntities();
		EntityFactory::DeleteAll();
	}

	void OmegaScene::Unload()
	{
		MeshLibrary::DeleteAll();
		SpriteSourceLibrary::DeleteAll();
	}

	void OmegaScene::SpawnAsteroid()
	{
		Entity* entityAsteroid = EntityFactory::Build("Asteroid");
		if (entityAsteroid) {
			this->AddEntity(entityAsteroid);
		}
	}

	void OmegaScene::SpawnWave() {
		ScoreSystem::Instance().IncreaseWave();
		for (unsigned int i = 0; i < asteroidSpawnCount; ++i) {
			SpawnAsteroid();
		}
		// increment spawn count after every wave
		if (asteroidSpawnCount < asteroidSpawnMaximum) asteroidSpawnCount++;
	}

#pragma endregion Private Functions

}	// namespace