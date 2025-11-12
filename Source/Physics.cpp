//------------------------------------------------------------------------------
//
// File Name:	Physics.cpp
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
#include "Physics.h"

#include "Transform.h"
#include "Entity.h"
#include "Vector2D.h"
#include "Stream.h"

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

	Physics::Physics(void)
	{
	}

	Physics::Physics(const Physics* other)
	{
		velocity = other->velocity;
		acceleration = other->acceleration;
		oldTranslation = other->oldTranslation;
		rotationalVelocity = other->rotationalVelocity;
	}

	//--------------------------------------------------------------------------

	//Physics::~Physics(void)
	//{
	//}

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

	bool Physics::Initialize() {
		Transform* transform = Parent()->Get<Transform>();

		if (transform) {
			oldTranslation = transform->Translation();
			return true;
		}
		return false;
	}

	void Physics::Update(float dt) {
		Transform* transform = Parent()->Get<Transform>();

		if (transform) {
			oldTranslation = transform->Translation();

			velocity.ScaleAdd(dt, acceleration);
			velocity.Scale(drag);

			Vector2D newTranslation = transform->Translation();
			newTranslation.ScaleAdd(dt, velocity);

			transform->Translation(newTranslation);

			transform->Rotation(transform->Rotation() + rotationalVelocity * dt);
		}
	}

	void Physics::Read(Stream& stream) {
		// Check for valid stream (optional).
		DRAGON_ASSERT(stream.Contains("Physics"), "Physics::Read: Failed to find required key: Physics");
		// Traverse down the tree to the "Physics" object (PushNode).
		stream.PushNode("Physics");
		// Read the Velocity from the stream.
		stream.ReadVector2D("Velocity", velocity);
		// Read the Acceleration from the stream.
		stream.ReadVector2D("Acceleration", acceleration);
		// this one is even more redundant, I don't think anyone will or should have this as part of an entity's json file
		stream.ReadVector2D("OldTranslation", oldTranslation);
		//    Return to the original location in the tree (PopObject).
		stream.PopNode();

	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace