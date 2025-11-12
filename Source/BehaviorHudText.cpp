//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.cpp
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
#include "BehaviorHudText.h"
#include "Stream.h"

#include "ScoreSystem.h"

#include "Sprite.h"

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

	BehaviorHudText::BehaviorHudText(void)
		: Behavior(), scoreSystemId(0), displayValue(UINT_MAX), labelString(""), displayString("")
	{
	}

	BehaviorHudText::BehaviorHudText(const BehaviorHudText* other)
		: Behavior(other), 
		scoreSystemId(other->scoreSystemId), 
		displayValue(other->displayValue), 
		labelString(other->labelString), 
		displayString(other->displayString)
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

	void BehaviorHudText::Read(Stream& stream)
	{
		stream.PushNode("BehaviorHudText");

		// Read the base Behavior variables.
		// [HINT: Behavior::Read().]
		Behavior::Read(stream);

		// Read the derived class Behavior variables, if any.
		stream.Read("ScoreSystemId", scoreSystemId);
		stream.Read("LabelString", labelString);
		
		stream.PopNode();
	}

	void BehaviorHudText::onInit()
	{
		UpdateText();
	}

	void BehaviorHudText::onUpdate(float dt)
	{
		if(displayValue != ScoreSystem::Instance().GetValue(static_cast<ScoreSystem::ScoreSystemId>(scoreSystemId)))
		{
			UpdateText();
		}
	}

	void BehaviorHudText::onExit()
	{

	}

	void BehaviorHudText::UpdateText() {
		// validate scoreSystemId
		if (scoreSystemId >= ScoreSystem::SsiMax) return;

		displayValue = ScoreSystem::Instance().GetValue(static_cast<ScoreSystem::ScoreSystemId>(scoreSystemId));
		//displayString = std::format("{} {}", labelString, std::to_string(displayValue));
		displayString = labelString + " " + std::to_string(displayValue);

		Sprite* sprite = Parent()->Get<Sprite>();
		if (sprite) {
			sprite->SetText(displayString);
		}

	}

#pragma endregion Private Functions

}	// namespace