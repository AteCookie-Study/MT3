#pragma once
#include <cmath>

// --- 定数 ---
static const int kWindowWidth = 1280;
static const int kWindowHeight = 720;

// --- 型定義 ---
struct Vector3 {
    float x, y, z;
};

struct Matrix4x4 {
    float m[4][4];
};

// --- 関数宣言 ---
Vector3 Add(const Vector3& a, const Vector3& b);
Vector3 Subtract(const Vector3& a, const Vector3& b);
Vector3 Multiply(const Vector3& a, float scalar);
Vector3 Multiply(float scalar, const Vector3& a);

Matrix4x4 Multiply(const Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 Inverse(const Matrix4x4& a);
Matrix4x4 MakeIdentity4x4();

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);

Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRaito, float nearClip, float farClip);
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

// --- 演算子オーバーロード ---
Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v, float s);
Vector3 operator*(float s, const Vector3& v);

// --- 演算子オーバーロード ---
// 既存のVector3用演算子に加えて、Matrix4x4用の乗算演算子を追加
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);