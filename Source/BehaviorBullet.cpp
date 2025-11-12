//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.cpp
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
#include "BehaviorBullet.h"
#include "Stream.h"

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

	BehaviorBullet::BehaviorBullet(void)
		: Behavior()
	{
	}

	BehaviorBullet::BehaviorBullet(const BehaviorBullet* other)
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

	void BehaviorBullet::Read(Stream& stream)
	{
		stream.PushNode("BehaviorBullet");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		Behavior::Read(stream);

		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorBullet::onInit()
	{
		ColliderCircle* collider = Parent()->Get<ColliderCircle>();
		if (!collider) return;

		collider->RegisterHandler(CollisionHandler);
	}

	void BehaviorBullet::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cIdle:
			timer -= dt;
			if (timer <= 0.0) Parent()->Destroy();
			break;

		default:
			break;
		}
	}

	void BehaviorBullet::onExit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorBullet::CollisionHandler(Entity* e, const Entity* other) {
		if (!e || !other) return;
		if (other->IsNamed("Asteroid")) {
			e->Destroy();
		}
	}

#pragma endregion Private Functions

}	// namespace