//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.h
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 4
// Purpose:		This derived class is responsible for the behavior associated
//   with a "template" entity.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Behavior.h"

//------------------------------------------------------------------------------
// External Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Namespace Declarations:
//------------------------------------------------------------------------------

namespace CS529
{
	// Forward Declarations:
	class Stream;

	// Typedefs:

	// Class Definition:
	class BehaviorHudText : public Behavior
	{
		// Public Constants and Enums:
	public:

		// Constructors/Destructors:
	public:
		BehaviorHudText(void);

		// @brief This copy-constructor should perform a shallow copy of the data.
		BehaviorHudText(const BehaviorHudText* other);

		// Public Static Functions:
	public:

		// Public Functions:
	public:
		// @brief Read the properties of a BehaviorHudText component from a stream.
		// @brief [NOTE: The base Behavior variables must be read using Behavior::Read().]
		//
		// @param stream = The data stream used for reading.
		void Read(Stream& stream);

		// Public Event Handlers
	public:

		// Private Functions:
	private:
		// @brief This function is required to invoke the copy-constructor in derived classes.
		BehaviorHudText* Clone() const override { return new BehaviorHudText(this); }

		// Behavior Finite-State Machine (FSM) functions.
		void onInit() override;
		void onUpdate(float dt) override;
		void onExit() override;

		void UpdateText();

		// Private Constants:
	private:
		typedef enum
		{
			cInvalid = -1,	// Default state for the behavior FSM.
			cIdle,			// Starting state for the behavior FSM.

		} States;

		// Private Static Variables:
	private:

		// Private Variables:
	private:
		// Identifies which score system value is associated with this HUD text.
		unsigned scoreSystemId;
		// The score system value currently being displayed.
		// [NOTE: This is a variation on lazy initialization, in that the displayString
		// will only be reformatted when this display value changes.]
		unsigned displayValue;
		// Contains the formatting string necessary to generate the display string.
		std::string labelString;
		// Contains the final, formatted text to be displayed on screen.
		std::string displayString;

	};

}	// namespace