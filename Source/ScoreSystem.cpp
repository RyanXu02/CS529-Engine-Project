//------------------------------------------------------------------------------
//
// File Name:	ScoreSystem.cpp
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

	//--------------------------------------------------------------------------
	// Private Constants:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Private Static Variables:
	//--------------------------------------------------------------------------
	ScoreSystem* ScoreSystem::instance = nullptr;
	//--------------------------------------------------------------------------
	// Private Variables:
	//--------------------------------------------------------------------------

	//--------------------------------------------------------------------------
	// Constructors/Destructors:
	//--------------------------------------------------------------------------

#pragma region Constructors

	ScoreSystem::ScoreSystem(void)
		: System("ScoreSystem") // Call base class constructor with a name
	{
		instance = this;
	}

	//--------------------------------------------------------------------------

	ScoreSystem::~ScoreSystem(void)
	{
		if (instance == this) instance = nullptr;
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
	void ScoreSystem::NewGame() {
		score = 0;
		highScore = 0;
		waveCount = 0;
	}

	void ScoreSystem::Reset() {
		highScore = score > highScore ? score : highScore;
		score = 0;
		waveCount = 0;
	}

	unsigned ScoreSystem::GetValue(ScoreSystemId id) const {
		switch (id) {
		case SsiScore:
			return score;
		case SsiHighScore:
			return highScore;
		case SsiWaveCount:
			return waveCount;
		default:
			return 0;
		}
	}

	void ScoreSystem::IncreaseScore(unsigned amount) {
		score += amount;
	}

	void ScoreSystem::IncreaseWave(void) {
		++waveCount;
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace