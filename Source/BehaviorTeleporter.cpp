//------------------------------------------------------------------------------
//
// File Name:	BehaviorTeleporter.cpp
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
#include "BehaviorTeleporter.h"
#include "Stream.h"

#include "Transform.h"
#include "Vector2D.h"

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

	BehaviorTeleporter::BehaviorTeleporter(void)
		: Behavior()
	{
		stateCurr = cIdle;
		stateNext = cIdle;
	}

	BehaviorTeleporter::BehaviorTeleporter(const BehaviorTeleporter* other)
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

	void BehaviorTeleporter::Read(Stream& stream)
	{
		stream.PushNode("BehaviorTeleporter");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		Behavior::Read(stream);

		// Read the derived class Behavior variables, if any.

		stream.PopNode();
	}

	void BehaviorTeleporter::onInit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

	void BehaviorTeleporter::onUpdate(float dt)
	{
		switch (stateCurr)
		{
		case cIdle:
			Transform* transform = Parent() ? Parent()->Get<Transform>() : nullptr;
			if (!transform) break;

			const Vector2D winSize = DGL_Window_GetSize();
			Vector2D screenMin{ 0.0f, 0.0f };
			Vector2D screenMax{ winSize.x, winSize.y };

			const Vector2D worldA = DGL_Camera_ScreenCoordToWorld(&screenMin);
			const Vector2D worldB = DGL_Camera_ScreenCoordToWorld(&screenMax);

			const float left = std::min(worldA.x, worldB.x);
			const float right = std::max(worldA.x, worldB.x);
			const float bottom = std::min(worldA.y, worldB.y);
			const float top = std::max(worldA.y, worldB.y);

			Vector2D pos = transform->Translation();
			bool changed = false;

			if (pos.x < left) { pos.x = right;  changed = true; }
			else if (pos.x > right) { pos.x = left;   changed = true; }

			if (pos.y < bottom) { pos.y = top;    changed = true; }
			else if (pos.y > top) { pos.y = bottom; changed = true; }

			if (changed) {
				transform->Translation(pos);
			}
			
			break;
		}
	}

	void BehaviorTeleporter::onExit()
	{
		switch (stateCurr)
		{
		case cIdle:
			break;

		default:
			break;
		}
	}

#pragma endregion Private Functions

}	// namespace