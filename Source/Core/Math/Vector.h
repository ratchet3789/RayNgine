#pragma once

#include "string" // Printing

// Naming defs to stop clashing with RayLib's Math header!
#define Vec2 INTRNL_Vector2<float>
#define Vec2i INTRNL_Vector2<int32_t>
#define Vec3 INTRNL_Vector3<float>
#define Vec3i INTRNL_Vector3<int32_t>
#define Vec4 INTRNL_Vector4<float>
#define Vec4i INTRNL_Vector4<int32_t>
#define Quat INTRNL_Vector4<float>

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
};

template <typename T>
class INTRNL_Vector3
{
public:
	T X,Y,Z;

	INTRNL_Vector3() : X(0), Y(0), Z(0) {};
	INTRNL_Vector3(T In) : X(In), Y(In), Z(In) {};
	INTRNL_Vector3(T InX, T InY, T InZ) : X(InX), Y(InY), Z(InZ) {};

	static INTRNL_Vector3<T> Up(){ return INTRNL_Vector3<T>(0,1,0);}
	static INTRNL_Vector3<T> Right() {return INTRNL_Vector3<T>(1,0,0);}
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