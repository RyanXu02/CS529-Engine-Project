//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This derived class is responsible for the behavior associated
//   with a "template" entity.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"

#include "Entity.h"
#include "Behavior.h"
#include "BehaviorAsteroid.h"
#include "Stream.h"

#include "Random.h"
#include "Transform.h"
#include "Physics.h"
#include "ColliderCircle.h"

#include "ScoreSystem.h"

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
	static const unsigned asteroidScore = 20;
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

	BehaviorAsteroid::BehaviorAsteroid(void)
		: Behavior(), origin(static_cast<AsteroidOrigin>(0))
	{
	}

	BehaviorAsteroid::BehaviorAsteroid(const BehaviorAsteroid* other)
		: Behavior(other), origin(other ? other->origin : static_cast<AsteroidOrigin>(0))
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

	void BehaviorAsteroid::Read(Stream& stream)
	{
		stream.PushNode("BehaviorAsteroid");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		Behavior::Read(stream);

		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorAsteroid::onInit()
	{
		origin = static_cast<AsteroidOrigin>(Random::Range(0, 3));
		SetPosition();
		SetVelocity();

		ColliderCircle* collider = Parent()->Get<ColliderCircle>();
		if (!collider) return;
		collider->RegisterHandler(CollisionHandler);
	}

	void BehaviorAsteroid::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorAsteroid::onExit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorAsteroid::SetPosition() {
		Transform* transform = Parent()->Get<Transform>();
		if (!transform) return;

		const Vector2D winSize = DGL_Window_GetSize();
		const Vector2D screenTlc{ 0.0f,       0.0f };
		const Vector2D screenTrc{ winSize.x,  0.0f };
		const Vector2D screenBlc{ 0.0f,       winSize.y };
		const Vector2D screenBrc{ winSize.x,  winSize.y };

		const Vector2D worldTlc = DGL_Camera_ScreenCoordToWorld(&screenTlc);
		const Vector2D worldTrc = DGL_Camera_ScreenCoordToWorld(&screenTrc);
		const Vector2D worldBlc = DGL_Camera_ScreenCoordToWorld(&screenBlc);
		const Vector2D worldBrc = DGL_Camera_ScreenCoordToWorld(&screenBrc);

		switch (origin)
		{
		case cAsteroidOriginTlc:
			transform->Translation(worldTlc);
			break;
		case cAsteroidOriginTrc:
			transform->Translation(worldTrc);
			break;
		case cAsteroidOriginBlc:
			transform->Translation(worldBlc);
			break;
		case cAsteroidOriginBrc:
			transform->Translation(worldBrc);
			break;
		default:
			transform->Translation(worldTlc); // if everything is spawning top-left, come here
			break;
		}
	}
	void BehaviorAsteroid::SetVelocity(){
		Physics* physics = Parent()->Get<Physics>();
		if (!physics) return;

		float angle = 0.0f;
		switch (origin)
		{
		case cAsteroidOriginTlc:
			angle = Random::Range(-80.0f, -10.0f);
			break;
		case cAsteroidOriginTrc:
			angle = Random::Range(-170.0f, -100.0f);
			break;
		case cAsteroidOriginBlc:
			angle = Random::Range(10.0f, 80.0f);
			break;
		case cAsteroidOriginBrc:
			angle = Random::Range(100.0f, 170.0f);
			break;
		default:
			angle = Random::Range(0.0f, 0.0f);
			break;
		}

		const float speed = Random::Range(asteroidSpeedMin, asteroidSpeedMax);
		Vector2D dir; 
		dir.FromAngleDeg(angle); 
		dir.Scale(speed);
		physics->Velocity(dir);
	}

	void BehaviorAsteroid::CollisionHandler(Entity* e, const Entity* other) {
		if (!e || !other) return;

		else if (other->IsNamed("Bullet") || other->IsNamed("Spaceship")) {
  			ScoreSystem::Instance().IncreaseScore(asteroidScore);
			e->Destroy();
		}
		
	}

#pragma endregion Private Functions

}	// namespace