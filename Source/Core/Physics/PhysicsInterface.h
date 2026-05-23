#pragma once

#include "../Math/Vector.h"

class PhysicsInterface
{
	virtual void Initialize() = 0;
	virtual void Release() = 0;
	virtual void Tick();


	Vec3 Gravity{0,0,-9.81f};
	virtual Vec3 ConvertToEngineSafeVec3() = 0;

	/*
	Notes:
	I'm looking at Unitys Phys API and I see these so I'm going to note them down

	Character Control - Does Bullet have a Character Controller? If not then we should just write our own
	Rigidbody Physics
	Collision
	*/
};

class IPhysicsWorld
{
	virtual ~IPhysicsWorld() = default;

	virtual void StepSimulation(float deltaTime) = 0;
	virtual void SetGravity(const Vec3& gravity) = 0;
	virtual Vec3 GetGravity() const = 0;

	virtual IPhysicsBody* CreateBody(const RigidbodyDesc& desc) = 0;
	virtual IPhysicsCharacter CreateCharacter(const CharacterDesc& desc) = 0;
	virtual IPhysicsJoint CreatePhysicsJoint(const JointDesc& desc) = 0;

	virtual void Raycast(const Ray& ray, RaycastHit& outHit) const = 0;
	virtual void Overlap(const ShapeDesc& shape, const Transform& worldXf, OverlapResults& outResults) const = 0;
	virtual void Sweep(const ShapeDesc& sgape, const Transform& startXf, const Vec3& direction, SweepHit& outHit) const = 0;
	virtual void RemoveBody(IPhysicsBody* body) const = 0;
	virtual void RemoveCharacter(IPhysicsCharacter* character) const = 0;
	virtual void RemovePhysicsJoint(IPhysicsJoint joint) const = 0;
};

class IPhysicsBody
{
	virtual ~IPhysicsBody() = default;

	virtual void SetTransform() = 0;
	virtual Transform GetTransform() const = 0;

	virtual void SetLinearVelocity(const Vec3& v) = 0;
	virtual Vec3 GetLinearVelocity() const = 0;

	virtual void SetAngularVelocity(const Vec3& v) = 0;
	virtual Vec3 GetAngularVelocity() const = 0;

	virtual void ApplyForce(const Vec3& force) = 0;
	virtual void ApplyImpulse(const Vec3& impulse) = 0;
	virtual void ApplyTorque(const Vec3& torque) = 0;

	virtual void SetMass(float mass) = 0;
	virtual float GetMass() const = 0;

	virtual void SetDampening(float linear, float angular) = 0;

	virtual void SetCollisionEnabled(bool enabled) = 0;
	virtual void SetKinematic(bool kinematic) = 0;

	virtual void SetUserData(void* user) = 0;
	virtual void* GetUserData() const = 0;
};

class IPhysicsCharacter
{
	virtual ~IPhysicsCharacter() = default;

	virtual void SetTransfomr(const Transform& xf) = 0;
	virtual Transform GetTransform() const = 0;

	virtual bool Move(const Vec3 displacement, float dt) = 0;

	virtual void SetSlopeLimit(float radians) = 0;
	virtual void SetStepHeight(float height) = 0;
	virtual void SetCapsuleDimensions(float radius, float height) = 0;

	virtual bool IsGrounded() const = 0;

	virtual void SetUserData(void* user) = 0;
	virtual void* GetUserData() const = 0;
};

class IPhysicsJoint
{
	virtual ~IPhysicsJoint() = default;

	virtual void SetBreakForce(float force) = 0;
	virtual void SetBreakTorque(float torque) = 0;

	virtual void EnableCollisionBetweenBodies(bool enable) = 0;

	virtual void SetUserData(void* user) = 0;
	virtual void* GetUserData() const = 0;
};

class IPhysicsDebugDraw
{
	virtual ~IPhysicsDebugDraw() = default;

	virtual void DrawLine(const Vec3& pointA, const Vec3& pointB, const Color& color) = 0;
	virtual void DrawBox(const Transform& xf, const Vec3& halfExtent, const Color& color) = 0;
	virtual void DrawSphere(const Transform& xf, float radius, const Color& color) = 0;
	virtual void DrawCapsule(const Transform& xf, float radius, float height, const Color& color) = 0;
};

class IPhysicsQuery
{
	virtual ~IPhysicsQuery() = default;
};

class IPhysicsEvent
{

};