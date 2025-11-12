//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.cpp
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
#include "Matrix2D.h"

#include "Vector2D.h"
#include "LoggingSystem.h"

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
	const Matrix2D Matrix2D::identity = [] {
		Matrix2D mat;
		mat.m[0][0] = 1.0f; mat.m[0][1] = 0.0f; mat.m[0][2] = 0.0f; mat.m[0][3] = 0.0f;
		mat.m[1][0] = 0.0f; mat.m[1][1] = 1.0f; mat.m[1][2] = 0.0f; mat.m[1][3] = 0.0f;
		mat.m[2][0] = 0.0f; mat.m[2][1] = 0.0f; mat.m[2][2] = 1.0f; mat.m[2][3] = 0.0f;
		mat.m[3][0] = 0.0f; mat.m[3][1] = 0.0f; mat.m[3][2] = 0.0f; mat.m[3][3] = 1.0f;
		return mat;
	}();
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

	Matrix2D::Matrix2D(void) : DGL_Mat4{ identity }
	{
	}

	//--------------------------------------------------------------------------



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

	void Matrix2D::Identity() {
		*this = identity;
	}

	void Matrix2D::Translate(const Vector2D& v) {
		Identity();
		m[0][3] = v.x;
		m[1][3] = v.y;
	}
	void Matrix2D::Translate(float x, float y) {
		Identity();
		m[0][3] = x;
		m[1][3] = y;
	}

	void Matrix2D::Scale(const Vector2D& v) {
		Identity();
		m[0][0] = v.x;
		m[1][1] = v.y;
	}
	void Matrix2D::Scale(float x, float y) {
		Identity();
		m[0][0] = x;
		m[1][1] = y;
	}

	void Matrix2D::RotationDeg(float angle) {
		Identity();
		float radians = angle * (static_cast<float>(std::numbers::pi) / 180.0f); // pretty sure this was never implmented as a standalone method in Vector2D.cpp/h
		m[0][0] = cosf(radians);
		m[1][0] = sinf(radians);
		m[0][1] = -sinf(radians);
		m[1][1] = cosf(radians);
	}
	void Matrix2D::RotationRad(float angle) {
		Identity();
		m[0][0] = cosf(angle);
		m[1][0] = sinf(angle);
		m[0][1] = -sinf(angle);
		m[1][1] = cosf(angle);
	}

	Matrix2D Matrix2D::operator*(const Matrix2D& other) const {
		Matrix2D result;
		for (int row = 0; row < 4; ++row) {
			for (int col = 0; col < 4; ++col) {
				result.m[row][col] = m[row][0] * other.m[0][col] +
									 m[row][1] * other.m[1][col] +
									 m[row][2] * other.m[2][col] +
									 m[row][3] * other.m[3][col];
			}
		}
		return result;
	}
	Vector2D Matrix2D::operator*(const Vector2D& v) const {
		Vector2D result;
		// skip z and w since theyre always 0 and 1
		result.x = v.x * m[0][0] + v.y * m[0][1] + m[0][3];
		result.y = v.x * m[1][0] + v.y * m[1][1] + m[1][3];
		return result;
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace