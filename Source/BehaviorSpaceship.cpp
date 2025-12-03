//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.cpp
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
#include "BehaviorSpaceship.h"
#include "Stream.h"
#include <numbers>

#include "Physics.h"
#include "Transform.h"
#include "Sprite.h"

#include "EntityFactory.h"
#include "SceneSystem.h"

#include "ColliderCircle.h"

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
	static const float spaceshipAcceleration = 150.0f;
	static const float spaceshipSpeedMax = 500.0f;
	static const float spaceshipTurnRateMax = (float)std::numbers::pi / 1.5f;
	static const float spaceshipWeaponCooldownTime = 0.25f;
	static const float spaceshipWeaponBulletSpeed = 750.0f;
	static const float spaceshipDeathDuration = 3.0f;

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

	BehaviorSpaceship::BehaviorSpaceship(void)
		: Behavior()
	{
		stateCurr = cSpaceshipIdle;
		stateNext = cSpaceshipIdle;
	}

	BehaviorSpaceship::BehaviorSpaceship(const BehaviorSpaceship* other)
		: Behavior(other)
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

	void BehaviorSpaceship::Read(Stream& stream)
	{
		stream.PushNode("BehaviorSpaceship");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		Behavior::Read(stream);

		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorSpaceship::onInit()
	{
		if (stateCurr == cSpaceshipIdle) {
			Collider* collider = Parent()->Get<ColliderCircle>();
			if (!collider) return;
			collider->RegisterHandler(CollisionHandler);

			Physics* physics = Parent()->Get<Physics>();
			physics->Drag(0.99f);
		}
		else if (stateCurr == cSpaceshipDead) {
			timer = spaceshipDeathDuration;
		}
	}

	void BehaviorSpaceship::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cSpaceshipIdle:
			UpdateRotation();
			UpdateWeapon(dt);
			if (DGL_Input_KeyDown(VK_UP)) {
				stateNext = cSpaceshipThrust;
			}
			else if (DGL_Input_KeyDown(VK_DOWN)) {
				stateNext = cSpaceshipReverse;
			}
			break;
		case cSpaceshipThrust:
			UpdateRotation();
			UpdateVelocity(dt);
			UpdateWeapon(dt);
			if (!DGL_Input_KeyDown(VK_UP)) stateNext = cSpaceshipIdle;
			if (DGL_Input_KeyDown(VK_DOWN)) stateNext = cSpaceshipReverse;
			break;
		case cSpaceshipReverse:
			UpdateRotation();
			UpdateVelocityReverse(dt);
			UpdateWeapon(dt);
			if (!DGL_Input_KeyDown(VK_DOWN)) stateNext = cSpaceshipIdle;
			if (DGL_Input_KeyDown(VK_UP)) stateNext = cSpaceshipThrust;
			break;
		case cSpaceshipDead:
			timer -= dt;
			if (timer > 0.0f) {
				Physics* physics = Parent()->Get<Physics>();
				if (physics) {
					physics->Velocity(Vector2D{ 0.0f, 0.0f });
					physics->RotationalVelocity(10.0f);
				}
				// flash alpha
				Sprite* sprite = Parent()->Get<Sprite>();
				if (sprite) {
					if (static_cast<int>(timer * 10.0f) % 2 == 0) sprite->Alpha(1.0);		
					else sprite->Alpha(0.0);
				}
			}
			else {
				SceneSystem::Restart();
			}
			break;
		default:
			break;
		}
	}

	void BehaviorSpaceship::onExit()
	{

	}

	void BehaviorSpaceship::UpdateRotation() const
	{
		Physics* physics = Parent()->Get<Physics>();
		if (!physics) return;

		if (DGL_Input_KeyDown(VK_LEFT))
		{
			physics->RotationalVelocity(spaceshipTurnRateMax);
		}
		else if (DGL_Input_KeyDown(VK_RIGHT))
		{
			physics->RotationalVelocity(-spaceshipTurnRateMax);
		}
		else
		{
			physics->RotationalVelocity(0.0f);
		}
	}

	void BehaviorSpaceship::UpdateVelocity(float dt) const
	{
		Physics* physics = Parent()->Get<Physics>();
		Transform* transform = Parent()->Get<Transform>();
		if(!physics || !transform) return;

		float rotation = transform->Rotation();
		Vector2D uRotDir;
		uRotDir.FromAngleRad(rotation);

		Vector2D velocity = physics->Velocity();
		velocity.ScaleAdd(spaceshipAcceleration * dt, uRotDir);

		float speed = velocity.Length();
		if (speed > spaceshipSpeedMax) {
			velocity.Scale(spaceshipSpeedMax/speed);
		}
		physics->Velocity(velocity);
	}

	void BehaviorSpaceship::UpdateVelocityReverse(float dt) const
	{
		Physics* physics = Parent()->Get<Physics>();
		Transform* transform = Parent()->Get<Transform>();
		if (!physics || !transform) return;
		physics->Drag(0.99f);

		float rotation = transform->Rotation();
		Vector2D uRotDir;
		uRotDir.FromAngleRad(rotation);

		Vector2D velocity = physics->Velocity();
		velocity.ScaleAdd(-spaceshipAcceleration * dt, uRotDir);

		float speed = velocity.Length();
		if (speed > spaceshipSpeedMax) {
			velocity.Scale(spaceshipSpeedMax / speed);
		}

		physics->Velocity(velocity);
	}

	void BehaviorSpaceship::UpdateWeapon(float dt)
	{
		if (timer > 0.0) {
			timer -= dt;
			if (timer < 0.0) timer = 0.0f;
		}
		if (timer <= 0.0) {
			if (DGL_Input_KeyDown(VK_SPACE)) {
				SpawnBullet();
				timer = spaceshipWeaponCooldownTime;
			}
		}
	}

	void BehaviorSpaceship::SpawnBullet() const
	{
		Entity* bullet = EntityFactory::Build("Bullet");
		if (bullet) {
			Transform* shipTransform = Parent()->Get<Transform>();
			bullet->Get<Transform>()->Translation(shipTransform->Translation());
			bullet->Get<Transform>()->Rotation(shipTransform->Rotation());

			Vector2D bulletVelocity;
			bulletVelocity.FromAngleRad(shipTransform->Rotation());
			bulletVelocity.Scale(spaceshipWeaponBulletSpeed);
			bullet->Get<Physics>()->Velocity(bulletVelocity);

			SceneSystem::AddEntity(bullet);
		}
	}

	void BehaviorSpaceship::CollisionHandler(Entity*e , const Entity* other) {
		if (!e || !other) return;
		if (other->IsNamed("Asteroid")) {
			BehaviorSpaceship* behavior = e->Get<BehaviorSpaceship>();
			if (behavior) {
				behavior->stateNext = cSpaceshipDead;
			}
		}
	}
#pragma endregion Private Functions

}	// namespace