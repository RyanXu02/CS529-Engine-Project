//------------------------------------------------------------------------------
//
// File Name:	Stream.cpp
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

	Stream::Stream(std::string_view filePath)
	{
		Open(filePath);
	}

	//--------------------------------------------------------------------------

	Stream::~Stream(void)
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

	bool Stream::Contains(std::string_view key) {
		// make sure we have valid node ptr
		if (dataNode == nullptr){
			return false;
		}

		return dataNode->contains(key);
	}

	void Stream::ReadArray(std::string_view key, std::function<void()> lambda) {
		if (Contains(key)) {
			PushNode(key);
			for (auto& it : dataNode->items()) {
				dataStack.push_back(dataNode);
				dataNode = &(it.value());
				lambda();
				PopNode();
			}
			PopNode();
		}
	}

	void Stream::ReadObject(std::string_view key, std::function<void(const std::string& key)> lambda)
	{
		if (Contains(key)) {
			PushNode(key);
			for (auto& it : dataNode->items()) {
				lambda(it.key());
			}
			PopNode();
		}
	}

	void Stream::PushNode(std::string_view key) {
		if (Contains(key)) {
			dataStack.push_back(dataNode);
			dataNode = &dataNode->at(key);
		}
		else {
			return;
		}

	}

	void Stream::PopNode() {
		if (!dataStack.empty()) {
			dataNode = dataStack.back();
			dataStack.pop_back();
		}
		else {
			return;
		}

	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions
	bool Stream::Open(std::string_view filePath)
	{
		isValid = false;

		// Open the JSON file.
		std::ifstream file(filePath.data());
		if (!file.is_open())
		{
			LoggingSystem::Error("Stream: Failed to open file {}", filePath);
			return isValid;
		}

		// Parse the JSON file into a json object.
		try
		{
			file >> jsonData;
			// init dataNode to point at root of jsonData
			dataNode = &jsonData;
		}
		catch (const json::parse_error& exception)
		{
			LoggingSystem::Error("Stream: JSON parsing error reading {}: ", filePath, exception.what());
			return isValid;
		}

		// The JSON file has been read and parsed successfully.
		isValid = true;
		return isValid;

	}
#pragma endregion Private Functions

}	// namespace