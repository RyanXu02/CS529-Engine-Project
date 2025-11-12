//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 1
// Purpose:		Template for a new .cpp file.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "ColliderCircle.h"

#include "Transform.h"
#include "Entity.h"

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

	ColliderCircle::ColliderCircle(void)
	{
	}

	ColliderCircle::ColliderCircle(const ColliderCircle* other)
	{
		this->radius = other->radius;
	}


	//--------------------------------------------------------------------------

	//ColliderCircle::~ColliderCircle(void)
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

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions
	void ColliderCircle::Read(Stream& stream) {
		if (!stream.IsValid()) return;
		stream.PushNode("ColliderCircle");
		if (stream.Contains("Radius")) {
			stream.Read("Radius", radius);
		}
		stream.PopNode();
	}
	bool ColliderCircle::IsColliding(const Collider* other) const
	{
		const ColliderCircle* otherCircle = dynamic_cast<const ColliderCircle*>(other);
		if (!otherCircle) return false;


		Transform* transformThis = Parent()->Get<Transform>();
		Transform* transformOther = other->Parent()->Get<Transform>();
		if (!transformThis || !transformOther) return false;

		const Vector2D& posA = transformThis->Translation();
		const Vector2D& posB = transformOther->Translation();

		const float distanceSquared = posA.SquareDistance(posB);
		const float radiusSum = this->Radius() + otherCircle->Radius();
		if (distanceSquared <= (radiusSum * radiusSum)) {
			return true;
		}

		return false;
	}
#pragma endregion Private Functions

}	// namespace