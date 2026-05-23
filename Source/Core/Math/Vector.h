#pragma once

#include "string" // Printing
#include <cmath>

// Naming defs to stop clashing with RayLib's Math header!
#define Vec2 INTRNL_Vector2<float>
#define Vec2i INTRNL_Vector2<int32_t>
#define Vec3 INTRNL_Vector3<float>
#define Vec3i INTRNL_Vector3<int32_t>
#define Vec4 INTRNL_Vector4<float>
#define Vec4i INTRNL_Vector4<int32_t>
#define Quat INTRNL_Vector4<float>
#define Transform INTRNL_Transform<float, float, float>

#define VECTOR2_TO_RAYLIB(Vector) Vector2(Vector.X, Vector.Y);
#define VECTOR3_TO_RAYLIB(Vector) Vector3(Vector.X, Vector.Y, Vector.Z);
#define VECTOR4_TO_RAYLIB(Vector) Vector4(Vector.X, Vector.Y, Vector.Z, Vector.W);

#define DEGREE2RAD (3.141592f / 180.0f)
#define RAD2DEGREE (180.0f / 3.141592f)

template <typename T>
class INTRNL_Vector2
{
public:
	T X, Y;

	INTRNL_Vector2() : X(0), Y(0) {};
	INTRNL_Vector2(T In) : X(In), Y(In) {};
	INTRNL_Vector2(T InX, T InY) : X(InX), Y(InY) {};

	static INTRNL_Vector2 Up() { return INTRNL_Vector2<T>(0,1); }
	static INTRNL_Vector2 Right() { return INTRNL_Vector2<T>(1,0); }
	static INTRNL_Vector2 Down() { return INTRNL_Vector2<T>(0,-1); }
	static INTRNL_Vector2 Left() { return INTRNL_Vector2<T>(-1,0); }
};

template <typename T>
class INTRNL_Vector3
{
public:
	T X,Y,Z;

	INTRNL_Vector3() : X(0), Y(0), Z(0) {};
	INTRNL_Vector3(T In) : X(In), Y(In), Z(In) {};
	INTRNL_Vector3(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ) {};

	static INTRNL_Vector3<T> Right() {return INTRNL_Vector3<T>(1,0,0);}
	static INTRNL_Vector3<T> Up(){ return INTRNL_Vector3<T>(0,1,0);}
	static INTRNL_Vector3<T> Forward() {return INTRNL_Vector3<T>(0,0,1);}

	INTRNL_Vector3<T> operator+(const INTRNL_Vector3<T>& Rhs) const { return INTRNL_Vector3<T>(X + Rhs.X, Y + Rhs.Y, Z + Rhs.Z); }
	INTRNL_Vector3<T> operator-(const INTRNL_Vector3<T>& Rhs) const { return INTRNL_Vector3<T>(X - Rhs.X, Y - Rhs.Y, Z - Rhs.Z); }
	INTRNL_Vector3<T> operator*(const INTRNL_Vector3<T>& Rhs) const { return INTRNL_Vector3<T>(X * Rhs.X, Y * Rhs.Y, Z * Rhs.Z); }
	INTRNL_Vector3<T> operator/(const INTRNL_Vector3<T>& Rhs) const { return INTRNL_Vector3<T>(X / Rhs.X, Y / Rhs.Y, Z / Rhs.Z); }

	INTRNL_Vector3<T>& operator+=(const INTRNL_Vector3<T>& Rhs) { X += Rhs.X; Y += Rhs.Y; Z += Rhs.Z; return *this; }
	INTRNL_Vector3<T>& operator-=(const INTRNL_Vector3<T>& Rhs) { X -= Rhs.X; Y -= Rhs.Y; Z -= Rhs.Z; return *this; }
	INTRNL_Vector3<T>& operator*=(const INTRNL_Vector3<T>& Rhs) { X *= Rhs.X; Y *= Rhs.Y; Z *= Rhs.Z; return *this; }
	INTRNL_Vector3<T>& operator/=(const INTRNL_Vector3<T>& Rhs) { X /= Rhs.X; Y /= Rhs.Y; Z /= Rhs.Z; return *this; }

	// Scalar
	INTRNL_Vector3<T> operator/(const float Scalar) const { return INTRNL_Vector3<T>(X / Scalar, Y / Scalar, Z / Scalar); }
	INTRNL_Vector3<T> operator*(const float Scalar) const { return INTRNL_Vector3<T>(X * Scalar, Y * Scalar, Z * Scalar); }

	INTRNL_Vector3<T> operator/=(const float Scalar) { X /= Scalar; Y /= Scalar; Z /= Scalar; return *this; }
	INTRNL_Vector3<T> operator*=(const float Scalar) { X *= Scalar; Y *= Scalar; Z *= Scalar; return *this; }

	float DotProduct(const INTRNL_Vector3<T>& Rhs) { return X * Rhs.X + Y * Rhs.Y + Z * Rhs.Z;}
	INTRNL_Vector3 CrossProduct(const INTRNL_Vector3<T>& Rhs) { return INTRNL_Vector3<T>(Y * Rhs.Z - Z * Rhs.Y, Z * Rhs.X - X * Rhs.Z, X * Rhs.Y - Y * Rhs.X); }

	static INTRNL_Vector3 CrossProduct(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T>& B) { return INTRNL_Vector3<T>(A.Y * B.Z - A.Z * B.Y, A.Z * B.X - A.X * B.Z, A.X * B.Y - A.Y * B.X); }
	static float Length(const INTRNL_Vector3<T> Rhs) { return std::sqrt(LengthSquared(Rhs)); }
	static float LengthSquared(const INTRNL_Vector3<T> Rhs) { return Rhs.X * Rhs.X + Rhs.Y * Rhs.Y + Rhs.Z * Rhs.Z;}
	static float Distance(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T> B) { return Length(A-B); }
	static float DistanceSquared(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T> B) { return LengthSquared(A-B); }
	INTRNL_Vector3<T> Lerp(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T> B, const float t) { return A + (B-A)*t; }
	// Normalizes A and B
	float NormalizedAngleTo(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T> B) { return std::acos(DotProduct(A, B) / (Length(A) * Length(B))); }
	float AngleTo(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T> B) { return std::acos(DotProduct(A, B)); }
	float SignedAngleTo(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T> B, const INTRNL_Vector3<T> Reference)
	{
		float Angle = AngleTo(A, B);
		INTRNL_Vector3<T> Cross = CrossProduct(A, B);
		if (Reference.DotProduct(Cross) < 0)
			return -Angle;
		return Angle;
	}
	static INTRNL_Vector3<T> ReflectedAngle(const INTRNL_Vector3<T> IncomingAngle, const INTRNL_Vector3<T> Normal) { return IncomingAngle - 2*(IncomingAngle*Normal) * Normal; }
	static INTRNL_Vector3<T> ProjectedAngle(const INTRNL_Vector3<T> A, const INTRNL_Vector3<T> B) { return B * (A.DotProduct(B) / B.LengthSquared()); }

	std::string Print() { return std::to_string(X) + " " + std::to_string(Y) + " " + std::to_string(Z);}
};

template <typename T>
class INTRNL_Vector4
{
public:
	T X,Y,Z,W;

	INTRNL_Vector4() : X(0), Y(0), Z(0), W(0) {};
	INTRNL_Vector4(T In) : X(In), Y(In), Z(In), W(In) {};
	INTRNL_Vector4(T InX, T InY, T InZ, T InW) : X(InX), Y(InY), Z(InZ), W(InW) {};

	static INTRNL_Vector4 Up(){ return INTRNL_Vector3<T>(0,1,0);}
	static INTRNL_Vector4 Right() {return INTRNL_Vector3<T>(1,0,0);}
	static INTRNL_Vector4 Forward() {return INTRNL_Vector3<T>(0,0,1);}
};

template <typename T, typename U, typename V>
struct INTRNL_Transform
{
	INTRNL_Transform() {};
	INTRNL_Transform(const INTRNL_Vector3<T> Loc) : Location(Loc) {};
	INTRNL_Transform(const INTRNL_Vector3<T> Loc, const INTRNL_Vector4<U> Rot) : Location(Loc), Rotation(Rot) {};
	INTRNL_Transform(const INTRNL_Vector3<T> Loc, const INTRNL_Vector4<U> Rot, const INTRNL_Vector3<V> Scl) : Location(Loc), Rotation(Rot), Scale(Scl) {};

	INTRNL_Vector3<T> Location{0};
	INTRNL_Vector4<U> Rotation{0};
	INTRNL_Vector3<V> Scale{0};
};