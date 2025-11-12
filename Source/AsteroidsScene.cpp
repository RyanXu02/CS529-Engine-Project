//------------------------------------------------------------------------------
//
// File Name:	AsteroidsScene.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 2
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

#include "AsteroidsScene.h"
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

	AsteroidsScene::AsteroidsScene()
		: Scene("AsteroidsScene"), asteroidSpawnCount(0)
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

	void AsteroidsScene::Load()
	{
		ScoreSystem::Instance().NewGame();
	}

	bool AsteroidsScene::Initialize()
	{
		Entity* entitySpaceship = EntityFactory::Build("Spaceship");
		if (entitySpaceship) {
			this->AddEntity(entitySpaceship);
		}

		Entity* AsteroidsScore = EntityFactory::Build("AsteroidsScore");
		if (AsteroidsScore) {
			this->AddEntity(AsteroidsScore);
		}

		Entity* AsteroidsHighScore = EntityFactory::Build("AsteroidsHighScore");
		if (AsteroidsHighScore) {
			this->AddEntity(AsteroidsHighScore);
		}

		Entity* AsteroidsWave = EntityFactory::Build("AsteroidsWaveCount");
		if (AsteroidsWave) {
			this->AddEntity(AsteroidsWave);
		}

		DGL_Color black{ 0.0, 0.0, 0.0, 1.0 };
		DGL_Graphics_SetBackgroundColor(&black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		asteroidSpawnCount = asteroidSpawnInitial;

		ScoreSystem::Instance().Reset();
		return true;
	}

	void AsteroidsScene::Update(float dt)
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

	void AsteroidsScene::Render() const
	{
		RenderEntities();
	}

	void AsteroidsScene::Shutdown()
	{
		DeleteEntities();
		EntityFactory::DeleteAll();
	}

	void AsteroidsScene::Unload()
	{
		MeshLibrary::DeleteAll();
		SpriteSourceLibrary::DeleteAll();
	}

	void AsteroidsScene::SpawnAsteroid()
	{
		Entity* entityAsteroid = EntityFactory::Build("Asteroid");
		if (entityAsteroid) {
			this->AddEntity(entityAsteroid);
		}
	}

	void AsteroidsScene::SpawnWave() {
		ScoreSystem::Instance().IncreaseWave();
		for (unsigned int i = 0; i < asteroidSpawnCount; ++i) {
			SpawnAsteroid();
		}
		// increment spawn count after every wave
		if (asteroidSpawnCount < asteroidSpawnMaximum) asteroidSpawnCount++;
	}

#pragma endregion Private Functions

}	// namespace