//------------------------------------------------------------------------------
//
// File Name:	Vector2D.cpp
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
#include "Vector2D.h"

#include "DGL.h"
#include <numbers>

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

	Vector2D::Vector2D(void)
	{
	}

	Vector2D::Vector2D(float x, float y)
	{
		Set(x, y);
	}

	Vector2D::Vector2D(const Vector2D& other)
	{
		x = other.x;
		y = other.y;
	}

	void Vector2D::Zero()
	{
		Vector2D::Set(0.0f, 0.0f);
	}

	void Vector2D::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Vector2D::Negate()
	{
		Set(-this->x, -this->y);
	}

	void Vector2D::Add(const Vector2D& offset)
	{
		x += offset.x;
		y += offset.y;
	}

	void Vector2D::Sub(const Vector2D& offset)
	{
		x -= offset.x;
		y -= offset.y;
	}

	void Vector2D::Normalize()
	{
		float length = Length();
		if (length != 0.0f)
		{
			x /= length;
			y /= length;
		}
		else
		{
			Zero();
		}
	}

	void Vector2D::Scale(float scale)
	{
		x *= scale;
		y *= scale;
	}

	void Vector2D::ScaleAdd(float scale, const Vector2D& offset)
	{
		Vector2D temp(offset);
		temp.Scale(scale);
		this->Add(temp);
	}

	void Vector2D::ScaleSub(float scale, const Vector2D& offset)
	{
		Vector2D temp(offset);
		temp.Scale(scale);
		this->Sub(temp);
	}

	float Vector2D::Length() const
	{
		float lengthSquared = this->SquareLength();
		if (lengthSquared > 0.0f)
		{
			return sqrtf(lengthSquared);
		}
		return 0.0f;
	}

	float Vector2D::SquareLength() const
	{
		return (x*x) + (y*y);
	}

	float Vector2D::Distance(const Vector2D& point2) const
	{
		float distanceSquared = this->SquareDistance(point2);
		if (distanceSquared > 0.0f)
		{
			return sqrtf(distanceSquared);
		}
		return 0.0f;
	}

	float Vector2D::SquareDistance(const Vector2D& point2) const
	{
		float dx = point2.x - x;
		float dy = point2.y - y;
		Vector2D diff(dx, dy);

		return diff.SquareLength();
	}

	float Vector2D::DotProduct(const Vector2D& vector2) const
	{
		return (x * vector2.x) + (y * vector2.y);
	}

	void Vector2D::FromAngleDeg(float angle)
	{
		this->FromAngleRad((angle * static_cast<float>(std::numbers::pi)) / 180.0f);
	}

	void Vector2D::FromAngleRad(float angle)
	{
		this->Set(std::cosf(angle), std::sinf(angle));
	}

	float Vector2D::ToAngleRad() const
	{
		return std::atan2f(y, x);
	}

	//--------------------------------------------------------------------------

	//Vector2D::~Vector2D(void)
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

#pragma endregion Private Functions

}	// namespace