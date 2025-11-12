//------------------------------------------------------------------------------
//
// File Name:	Entity.cpp
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
#include "Entity.h"

#include "Component.h"
#include "Stream.h"

#include "Transform.h"
#include "Sprite.h"
#include "Physics.h"
#include "Animation.h"

#include "ObjectFactory.h"

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

	Entity::Entity(void)
	{
	}

	Entity::Entity(const Entity* other)
	{
		name = other->name;
		isDestroyed = other->isDestroyed;
		for (Component* component : other->components) {
			this->Add(component->Clone());
		}
	}

	//--------------------------------------------------------------------------

	Entity::~Entity(void)
	{
		for (Component* component : components) {
			delete component;
		}
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
	bool Entity::Initialize() {
		bool success = true;
		for (Component* component : components) {
			if (!component) {
				success = false;
				continue;
			}
			if (!component->Initialize()) {
				success = false;
			}
		}
		return success;
	}

	void Entity::Update(float dt) {
		for (Component* component : components) {
			if (!component) continue;
			component->Update(dt);
		}
	}

	void Entity::Render() const
	{
		for (Component* component : components) {
			if (!component) continue;
			component->Render();
		}
	}

	void Entity::Add(Component* component)
	{
		if (!component) return;
		components.push_back(component);
		component->Parent(this);
	}

	void Entity::Read(Stream& stream) {
		if (!stream.IsValid()) return;

		stream.PushNode("Entity");
		stream.Read("Name", name);

		auto readComponent = [this, &stream](const std::string& key)
			{
				Object* object = ObjectFactory::GetInstance().Create(key);
				if (!object) {
					LoggingSystem::Debug("Entity::Read: Failed to create component: {}", key);
					return;
				}

				Component* component = dynamic_cast<Component*>(object);
				if (component) {
					component->Read(stream);
					this->Add(component);
				}
				else {
					delete object;
				}
			};

		if (stream.Contains("Components")) {
			stream.ReadObject("Components", readComponent);
		}
		stream.PopNode(); // back to root
	}


#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace