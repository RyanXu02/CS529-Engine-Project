//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.cpp
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

#include "Level1Scene.h"
#include "Scene.h"
#include "SceneSystem.h"

#include "Stream.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "DemoScene.h"

#include "Mesh.h"
#include "SpriteSource.h"
#include "EntityFactory.h"

#include "Sprite.h"
#include "Transform.h"
#include "Physics.h"
#include "Animation.h"

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
	static const float groundHeight = -150.0f;
	static const float moveVelocity = 500.0f;
	static const float jumpVelocity = 1000.0f;
	static const Vector2D gravityNormal = { 0.0f, -1500.0f };
	static const Vector2D gravityNone = { 0.0f, 0.0f };

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

	Level1Scene::Level1Scene()
		: Scene("Level1Scene")
		, entityMonkey(nullptr)
		, entityLives(nullptr)
		, mesh3x3(nullptr)
		, mesh16x8(nullptr)
		, spriteSourceMonkeyIdle(nullptr)
		, spriteSourceMonkeyJump(nullptr)
		, spriteSourceMonkeyWalk(nullptr)
		, spriteSourceFontSheet(nullptr)
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

	void Level1Scene::Load()
	{
		Stream* stream = new Stream("Data/Level1.json");
		if (stream->IsValid()) 
		{
			stream->Read<int>("NumLives", numLives);
			LoggingSystem::Verbose("{}: Lives: {}", Name(), numLives);

			mesh1x1 = new Mesh();
			mesh1x1->BuildQuad(1.0f, 1.0f, "Mesh1x1");

			spriteSourcePlanet = new SpriteSource();
			spriteSourcePlanet->LoadTexture(1, 1, "Assets/PlanetTexture.png");

			mesh3x3 = new Mesh();
			mesh3x3->BuildQuad(1.0f / 3, 1.0f / 3, "Mesh3x3");

			mesh16x8 = new Mesh();
			mesh16x8->BuildQuad(1.0f / 16, 1.0f / 8, "Mesh16x8");

			spriteSourceMonkeyIdle = new SpriteSource();
			spriteSourceMonkeyIdle->LoadTexture(1, 1, "Assets/MonkeyIdle.png");

			spriteSourceMonkeyJump = new SpriteSource();
			spriteSourceMonkeyJump->LoadTexture(1, 1, "Assets/MonkeyJump.png");

			spriteSourceMonkeyWalk = new SpriteSource();
			spriteSourceMonkeyWalk ->LoadTexture(3, 3, "Assets/MonkeyWalk.png");

			spriteSourceFontSheet = new SpriteSource();
			spriteSourceFontSheet->LoadTexture(16, 8, "Assets/Roboto_Mono_black.png");
		}
	}

	bool Level1Scene::Initialize()
	{
		bool success = true;
		try {
			entityPlanet = EntityFactory::Build("PlanetBounce");
			if (entityPlanet) {
				Sprite* sprite = entityPlanet->Get<Sprite>();
				if (sprite) {
					sprite->SetMesh(mesh1x1);
					sprite->SetSpriteSource(spriteSourcePlanet);
				}
			}

			entityMonkey = EntityFactory::Build("Monkey");
			if (entityMonkey) {
				monkeyState = Invalid;
				SetMonkeyState(entityMonkey, Idle);
			}


			entityLives = EntityFactory::Build("MonkeyLivesText");
			if (entityLives) {
				Sprite* sprite = entityLives->Get<Sprite>();
				sprite->SetSpriteSource(spriteSourceFontSheet);
				sprite->SetMesh(mesh16x8);
				sprite->SetText(std::format("Lives: {}", numLives));
			}

			DGL_Color white{ 1.0, 1.0, 1.0, 1.0 };
			DGL_Graphics_SetBackgroundColor(&white);
			DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
		}
		catch (...) {
			success = false;
		}
		return success;
	}

	void Level1Scene::Update(float dt)
	{
		if (entityPlanet) {
			MovementController(entityMonkey);
			BounceController(entityPlanet);
			entityMonkey->Update(dt);
			entityPlanet->Update(dt);
			entityLives->Update(dt);
		}
		if (IsColliding(entityMonkey, entityPlanet)) {
			Sprite* sprite = entityLives->Get<Sprite>();
			sprite->SetText(std::format("Lives: {}", numLives));
			numLives--;
			if (numLives <= 0) SceneSystem::SetPendingScene<Level2Scene>();
			else SceneSystem::SetPendingScene<Level1Scene>();
		}

		// NOTE: This call causes the engine to exit immediately.
		//   Make sure to remove it when you are ready to test out a new scene.
		//SceneSystem::EndScene();

	}

	void Level1Scene::Render() const
	{
		if (entityPlanet) {
			entityPlanet->Render();
		}
		if (entityMonkey) {
			entityMonkey->Render();
		}
		if (entityLives) {
			entityLives->Render();
		}
	}

	void Level1Scene::Shutdown()
	{
		// ~Entity() deletes all attached components, thanks past self
		delete entityPlanet;
		delete entityMonkey;
		delete entityLives;
	}

	void Level1Scene::Unload()
	{
		delete mesh1x1;
		delete mesh3x3;
		delete mesh16x8;
		delete spriteSourceFontSheet;
		delete spriteSourceMonkeyIdle;
		delete spriteSourceMonkeyJump;
		delete spriteSourceMonkeyWalk;
		delete spriteSourcePlanet;
	}

	void Level1Scene::MovementController(Entity* entity) {
		Physics* physics = entity->Get<Physics>();
		Transform* transform = entity->Get<Transform>();

		if (physics && transform) {
			Vector2D velocity = entity->Get<Physics>()->Velocity();

			if (DGL_Input_KeyDown(VK_LEFT)) {
				velocity.x = -moveVelocity;
				if (monkeyState != Jump) SetMonkeyState(entity, Walk);
			}
			else if (DGL_Input_KeyDown(VK_RIGHT)) {
				velocity.x = moveVelocity;
				if (monkeyState != Jump) SetMonkeyState(entity, Walk);
			}
			else {
				velocity.x = 0.0f;
				if (monkeyState != Jump) SetMonkeyState(entity, Idle);
			}
			
			if (DGL_Input_KeyTriggered(VK_UP)) {
				velocity.y = jumpVelocity;
				entity->Get<Physics>()->Acceleration(gravityNormal);
				SetMonkeyState(entity, Jump);
			}
			// gravity and landing
			Vector2D currentTranslation = transform->Translation();
			if (currentTranslation.y < groundHeight) {
				currentTranslation.y = groundHeight;
				transform->Translation(currentTranslation);
				velocity.y = 0.0f;
				entity->Get<Physics>()->Acceleration(gravityNone);
				SetMonkeyState(entity, Idle);
			}

			physics->Velocity(velocity);
		}
	}

	void Level1Scene::BounceController(Entity* entity) const {
		Physics* physics = entity->Get<Physics>();
		Transform* transform = entity->Get<Transform>();
		if (!physics || !transform) return;

		if (physics && transform) {
			Vector2D translation = transform->Translation();
			Vector2D velocity = physics->Velocity();
			// do collisions
			if (translation.x < -wallDistance) {
				translation.x = -wallDistance;
				velocity.x = -velocity.x;
			}
			if (translation.x > wallDistance) {
				translation.x = wallDistance;
				velocity.x = -velocity.x;
			}
			if (translation.y <= groundHeight) {
				translation.y = groundHeight + (groundHeight - translation.y);
				velocity.y = -velocity.y;
			}
			// store new translation and velocity
			physics->Velocity(velocity);
			transform->Translation(translation);
		}
	}

	void Level1Scene::SetMonkeyState(Entity* entity, MonkeyStates state) {
		if (monkeyState != state) {
			monkeyState = state;
			Sprite* sprite = entity->Get<Sprite>();
			Animation* animation = entity->Get<Animation>();

			switch (monkeyState) {
			case Idle:
				sprite->SetMesh(mesh1x1);
				sprite->SetSpriteSource(spriteSourceMonkeyIdle);
				animation->Play(1, 0.0, false);
				break;
			case Jump:
				sprite->SetMesh(mesh1x1);
				sprite->SetSpriteSource(spriteSourceMonkeyJump);
				animation->Play(1, 0.0, false);
				break;
			case Walk:
				sprite->SetMesh(mesh3x3);
				sprite->SetSpriteSource(spriteSourceMonkeyWalk);
				animation->Play(8, 0.05f, true);
				break;
			}
		}
	}

	bool Level1Scene::IsColliding(const Entity* entityA, const Entity* entityB) const {
		Transform transformA = *entityA->Get<Transform>();
		Transform transformB = *entityB->Get<Transform>();
		Vector2D translationA = transformA.Translation();
		Vector2D translationB = transformB.Translation();
		const float distance_squared = translationA.SquareDistance(translationB);
		if (distance_squared <= CheckSquareDistance) return true;
		else return false;
	}

#pragma endregion Private Functions

}	// namespace