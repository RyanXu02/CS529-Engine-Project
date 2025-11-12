//------------------------------------------------------------------------------
//
// File Name:	Mesh.cpp
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
#include "Mesh.h"

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

	Mesh::Mesh(void)
	{
	}

	//--------------------------------------------------------------------------

	Mesh::~Mesh(void)
	{
		if (meshResource) {
			DGL_Graphics_FreeMesh(const_cast<DGL_Mesh**>(&meshResource));
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

	// Create a "unit"-sized quad (rectangular) mesh.
	// [NOTE: A unit-sized mesh extends from (-0.5,-0.5) to (0.5,0.5).]
	// [HINT: Refer to the "simple, textured mesh" in DemoScene for specific information.]
	void Mesh::BuildQuad(float uSize, float vSize, std::string_view name) {
		this->name = std::string(name);

		DGL_Graphics_StartMesh();
		
		static const DGL_Vec2 Vertex_Pos_Tlc = { -0.5f, 0.5f };
		static const DGL_Vec2 Vertex_Pos_Trc = { 0.5f, 0.5f };
		static const DGL_Vec2 Vertex_Pos_Blc = { -0.5f, -0.5f };
		static const DGL_Vec2 Vertex_Pos_Brc = { 0.5f, -0.5f };

		static const DGL_Color DGL_Color_Black = { 0.0f, 0.0f, 0.0f, 1.0f };
		
		const DGL_Vec2 Vertex_UV_Tlc = { 0.0f, 0.0f };
		const DGL_Vec2 Vertex_UV_Trc = { uSize, 0.0f };
		const DGL_Vec2 Vertex_UV_Blc = { 0.0f, vSize };
		const DGL_Vec2 Vertex_UV_Brc = { uSize, vSize };


		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &Vertex_UV_Blc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &Vertex_UV_Trc,
			&Vertex_Pos_Brc, &DGL_Color_Black, &Vertex_UV_Brc);
		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Blc, &DGL_Color_Black, &Vertex_UV_Blc,
			&Vertex_Pos_Tlc, &DGL_Color_Black, &Vertex_UV_Tlc,
			&Vertex_Pos_Trc, &DGL_Color_Black, &Vertex_UV_Trc);
		meshResource = DGL_Graphics_EndMesh();
	}

	// @brief Create a "unit"-sized triangular "Spaceship" mesh.
	// @brief [NOTE: A unit-sized mesh extends from (-0.5,-0.5) to (0.5,0.5).]
	// @brief [HINT: Refer to the "Spaceship" mesh in DemoScene for specific information.]
	void Mesh::BuildSpaceship() {
		DGL_Graphics_StartMesh();

		static const DGL_Vec2 Vertex_Pos_Tlc = { -0.5f, 0.5f };
		static const DGL_Vec2 Vertex_Pos_Blc = { -0.5f, -0.5f };

		static const DGL_Vec2 Vertex_Pos_Right = { 0.5f, 0.0f };
		static const DGL_Vec2 Vertex_UV_Zero = { 0.0f, 0.0f };

		static const DGL_Color DGL_Color_Red = { 1.0f, 0.0f, 0.0f, 1.0f };
		static const DGL_Color DGL_Color_Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };

		DGL_Graphics_AddTriangle(
			&Vertex_Pos_Right, &DGL_Color_Yellow, &Vertex_UV_Zero,
			&Vertex_Pos_Blc, &DGL_Color_Red, &Vertex_UV_Zero,
			&Vertex_Pos_Tlc, &DGL_Color_Red, &Vertex_UV_Zero);
		meshResource = DGL_Graphics_EndMesh();
	}

	void Mesh::Render() const {
		if (meshResource) DGL_Graphics_DrawMesh(meshResource, drawMode);
	}

	void Mesh::Read(Stream& stream)
	{
		if (!stream.IsValid()) return;
		stream.PushNode("Mesh");
		stream.Read("Name", name);
		if (name == "MeshSpaceship") {
			BuildSpaceship();
		}
		else if (stream.Contains("Vertices")) {
			auto readVertex = [&stream]() {
				// vertex pos
				Vector2D vertexPosition;
				stream.ReadVector2D("Position", vertexPosition);
				// vertex colro
				std::vector<float> vertexColors;
				stream.Read<std::vector<float>>("Color", vertexColors);
				float a = 1.0f; float r = 1.0f; float g = 1.0f; float b = 1.0f;
				if (vertexColors.size() == 4) {
					r = vertexColors[0];
					g = vertexColors[1];
					b = vertexColors[2];
					a = vertexColors[3];
				}
				else LoggingSystem::Warning("Mesh: Vertex colors does not have 4 components.");
				const DGL_Color vertexColors_DGL = { r, g, b, a };
				// UV
				Vector2D vertexUV;
				stream.ReadVector2D("UV", vertexUV);

				DGL_Graphics_AddVertex(&vertexPosition, &vertexColors_DGL, &vertexUV);
			};
			DGL_Graphics_StartMesh();
			stream.ReadArray("Vertices", readVertex);
			meshResource = DGL_Graphics_EndMesh();
		}
		else if (stream.Contains("Quad")) {
			unsigned int numRows = 1;
			unsigned int numCols = 1;
			stream.Read("NumCols", numCols);
			stream.Read("NumRows", numRows);
			float uSize = 1.0f / static_cast<float>(numCols);
			float vSize = 1.0f / static_cast<float>(numRows);
			BuildQuad(uSize, vSize, name);
		}
		else {
			LoggingSystem::Warning("Mesh: Unrecognized mesh name '{}'", name);
		}
		stream.PopNode();
	}

#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace