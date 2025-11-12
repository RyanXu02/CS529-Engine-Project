//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.cpp
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
#include "EntityContainer.h"

#include "Entity.h"
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

	EntityContainer::EntityContainer(void)
	{
		entities.reserve(100);
	}

	//--------------------------------------------------------------------------

	//EntityContainer::~EntityContainer(void)
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

	void EntityContainer::Update(float dt)
	{
		for (int i = 0; i < entities.size(); )
		{
			Entity* e = entities[i];
			if (!e)
			{
				entities.erase(entities.begin() + i);
				continue;
			}

			e->Update(dt);

			if (e->IsDestroyed())
			{
				delete e;
				entities.erase(entities.begin() + i);
			}
			else
			{
				++i; // ERASE INCREMENTS THE ITERATOR SO WE ONLY INCREMENT IF WE DID'T ERASE!!!!!
			}
		}
	}

	void EntityContainer::Render() const
	{
		for (Entity* e : entities) {
			if (!e) continue;
			e->Render();
		}
	}

	Entity* EntityContainer::FindByName(std::string_view findName) const
	{
		for (Entity* e : entities) {
			if (!e) continue;
			if (e->IsNamed(findName)) {
				return e; 
			}
		}
		return nullptr;
	}

	void EntityContainer::CheckCollisions() const {
		for (size_t i=0, n = entities.size(); i<n; ++i) {
			Entity* a = entities[i];
			if (!a) continue;
			ColliderCircle* colliderA = a->Get<ColliderCircle>();
			if (!colliderA) continue;

			for (size_t j=i+1; j<n; ++j) {
				Entity* b = entities[j];
				if (!b) continue;
				ColliderCircle* colliderB = b->Get<ColliderCircle>();
				if (!colliderB) continue;

				colliderA->CheckCollision(colliderB);
			}
		}
	}

	void EntityContainer::DeleteAll()
	{
		for (Entity* e : entities) {
			delete e;
			e = nullptr;
		}
		entities.clear();
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace