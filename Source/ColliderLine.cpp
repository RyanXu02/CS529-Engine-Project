//------------------------------------------------------------------------------
//
// File Name:	ColliderLine.cpp
// Author(s):	Ryan
// Course:		CS529F25
// Project:		Project 6
// Purpose:		This component class is responsible for detecting collisions
//   between a circle collider and a line collider.
//
// Copyright © 2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------

#include "Precompiled.h"
#include "ColliderLine.h"

#include "Stream.h"
#include "ColliderCircle.h"
#include "Transform.h"
#include "Entity.h"
#include "Physics.h"

#include "CollisionRecord.h"
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

	ColliderLine::ColliderLine(void)
	{
	}

	ColliderLine::ColliderLine(const ColliderLine* other)
		: Collider(other)
	{
		lineSegments = other->lineSegments;
	}

	//--------------------------------------------------------------------------

	//ColliderLine::~ColliderLine(void)
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
	void ColliderLine::Read(Stream& stream)
	{
		DRAGON_ASSERT(stream.Contains("ColliderLine"), "ColliderLine::Read: Failed to find required key: ColliderLine");
		stream.PushNode("ColliderLine");
		if (stream.Contains("LineSegments"))
		{
			auto readLineSegment = [this, &stream]() {
				LineSegment line;
				stream.ReadVector2D("P0", line.p0);
				stream.ReadVector2D("P1", line.p1);
				AddLineSegment(line);
			};
			stream.ReadArray("LineSegments", readLineSegment);
		}
		stream.PopNode();
	}

	bool ColliderLine::IsColliding(const Collider* other) const
	{
		const ColliderCircle* circleCollider = dynamic_cast<const ColliderCircle*>(other);
		if (!circleCollider) return false;

		Entity* otherEntity = other->Parent();
		if (!otherEntity) return false;
		 
		Transform* transform = otherEntity->Get<Transform>();
		if (!transform) return false;

		const Vector2D& Be = transform->Translation();

		Physics* physics = otherEntity->Get<Physics>();
		if (!physics) return false;

		const Vector2D& Bs = physics->OldTranslation();

		return IntersectAndReflect(circleCollider, Bs, Be);
	}

	void ColliderLine::AddLineSegment(const LineSegment& line) 
	{
		lineSegments.push_back(line);
	}

	bool ColliderLine::IntersectAndReflect(const ColliderCircle* circle, const Vector2D& Bs, const Vector2D& Be) const
	{
		Vector2D v = Be;
		v.Sub(Bs);
		if (v.SquareLength() <= 0.0f) return false; // Stationary

		// Initialize collision record (A = moving object, B = other object so this line entity)
		const Entity* entityA = circle->Parent();
		const Entity* entityB = this->Parent();
		CollisionRecord record(entityA, entityB, Bs, Be);
		record.Reset();

		// Iterate all line segments
		for (const LineSegment& seg : lineSegments)
		{
			const Vector2D& p0 = seg.p0;
			const Vector2D& p1 = seg.p1;

			// Edge vector
			Vector2D e(p1.x - p0.x, p1.y - p0.y);

			// Unit normal (perpendicular to edge)
			Vector2D n(e.y, -e.x);
			n.Normalize();

			float nv = n.DotProduct(v);
			// circle moving parallel to line
			if (nv == 1.0f) continue;

			// inside outside half-plane checks
			float nBs = n.DotProduct(Bs);
			float nBe = n.DotProduct(Be);
			float nP0 = n.DotProduct(p0);

			bool inside = (nBs <= nP0 && nBe < nP0);
			bool outside = (nBs >= nP0 && nBe > nP0);
			if (inside || outside) continue;

		
			float ti = (nP0 - nBs) / nv;
			if (ti < 0.0f || ti > 1.0f) continue;
			// Ignore this potential collision point, as it won't be reached.
			if (ti >= record.ti) continue;

			// Calculate the point of intersection (Bi).
			Vector2D Bi = Bs;
			Bi.ScaleAdd(ti, v);

			if (IsOutsideSegment(Bi, p0, p1)) continue; // behind p0
			if (IsOutsideSegment(Bi, p1, p0)) continue; // behind p1

			record.Update(ti, Bi, n);
		}

		// if collision detected
		if (record.ti != record.NoCollision)
		{
			Reflect(record);
			return true;
		}

		return false;
	}

	bool ColliderLine::IsOutsideSegment(const Vector2D& Bi, const Vector2D& p0, const Vector2D& p1) const
	{
		Vector2D a(Bi.x - p0.x, Bi.y - p0.y);
		Vector2D b(p1.x - p0.x, p1.y - p0.y);
		return a.DotProduct(b) < 0.0f;
	}

	void ColliderLine::Reflect(const CollisionRecord& collision) const
	{
		if (!collision.entityA) return;

		// i = Be - Bi
		Vector2D i = collision.Be;
		i.Sub(collision.Bi);

		// r = i - 2*(i·n)*n
		float iDotN = i.DotProduct(collision.n);
		Vector2D n = collision.n;
		n.Scale(2.0f * iDotN);
		Vector2D r = i;
		r.Sub(n);

		// Entity A
		Transform* tA = collision.entityA->Get<Transform>();
		Physics* pA = collision.entityA->Get<Physics>();
		ColliderCircle* circle = collision.entityA->Get<ColliderCircle>();

		// r = Be' - Bi
		Vector2D newTranslation = collision.Bi;
		newTranslation.Add(r);
		tA->Translation(newTranslation);

		// rotation
		Vector2D dir = r;
		dir.Normalize();
		tA->Rotation(dir.ToAngleRad());

		// velocity
		Vector2D newVelocity = dir;
		newVelocity.Scale(pA->Velocity().Length()); // velocity = v_dir||curr velocity||
		pA->Velocity(newVelocity);

		IntersectAndReflect(circle, collision.Bi, newTranslation);
			

	}
#pragma endregion Public Functions

	//--------------------------------------------------------------------------
	// Private Functions:
	//--------------------------------------------------------------------------

#pragma region Private Functions

#pragma endregion Private Functions

}	// namespace