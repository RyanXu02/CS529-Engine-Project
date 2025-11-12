//------------------------------------------------------------------------------
//
// File Name:	Animation.cpp
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
#include "Animation.h"

#include "Stream.h"
#include "Sprite.h"
#include "Entity.h"

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

	Animation::Animation(void)
	{
	}

	Animation::Animation(const Animation * other) 
	{
		frameIndex = other->frameIndex;
		frameCount = other->frameCount;
		frameDelay = other->frameDelay;
		frameDuration = other->frameDuration;	
		isRunning = other->isRunning;
		isLooping = other->isLooping;
		isDone = other->isDone;
	}

	//--------------------------------------------------------------------------

	//Animation::~Animation(void)
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
	void Animation::Play(unsigned frameCount, float frameDuration, bool isLooping) {
		// check for valid pointers
		Entity* entity = Parent();
		if (!entity)
			return;
		Sprite* sprite = entity->Get<Sprite>();
		if (!sprite)
			return;

		this->frameCount = frameCount;
		this->frameDuration = frameDuration;
		this->isLooping = isLooping;

		this->isRunning = true;
		this->isDone = false;
		this->frameIndex = 0;
		this->frameDelay = frameDuration;

	
		sprite->SetFrame(frameIndex);
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------
#pragma region Private Functions
	void Animation::Read(Stream& stream) {
		// Check for valid stream (optional).
		DRAGON_ASSERT(stream.Contains("Animation"), "Animation::Read: Failed to find required key: Animation");
		// Traverse down the tree to the "Animation" object (PushNode).
		stream.PushNode("Animation");
		// read all
		stream.Read("FrameIndex", frameIndex);
		stream.Read("FrameCount", frameCount);
		stream.Read("FrameDelay", frameDelay);
		stream.Read("FrameDuration", frameDuration);
		stream.Read("IsRunning", isRunning);
		stream.Read("IsLooping", isLooping);
		stream.Read("IsDone", isDone);
		// Return to the original location in the tree (PopObject).
		stream.PopNode();
	}

	void Animation::Update(float dt) {
		// check for valid pointers
		Entity* entity = Parent();
		if (!entity)
			return;
		Sprite* sprite = entity->Get<Sprite>();
		if (!sprite)
			return;

		isDone = false;
		if (!isRunning) {
			return;
		}
		frameDelay -= dt;
		if (frameDelay <= 0) {
			AdvanceFrame();
		}
		return;
	}

	void Animation::AdvanceFrame() {
		// check for valid pointers
		Entity* entity = Parent();
		if (!entity)
			return;
		Sprite* sprite = entity->Get<Sprite>();
		if (!sprite)
			return;

		++frameIndex;
		if (frameIndex >= frameCount) {
			if (isLooping) {
				frameIndex = 0;
			}
			else {
				frameIndex = frameCount - 1;
				isRunning = false;
			}
			isDone = true;
		}
		if (isRunning) {
			sprite->SetFrame(frameIndex);
			frameDelay += frameDuration;
		}
		else {
			frameDelay = 0;
		}
		return;
	}

#pragma endregion Private Functions

}	// namespace