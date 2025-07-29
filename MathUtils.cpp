#define NOMINMAX
#include "MathUtils.h"
#include <Novice.h>
#include <algorithm>
#include <cmath>

// Vector3 加算
Vector3 Add(const Vector3& a, const Vector3& b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

// Vector3 減算
Vector3 Subtract(const Vector3& a, const Vector3& b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

// Vector3 乗算（スカラー）
Vector3 Multiply(const Vector3& a, float scalar) {
    return { a.x * scalar, a.y * scalar, a.z * scalar };
}
Vector3 Multiply(float scalar, const Vector3& a) {
    return { a.x * scalar, a.y * scalar, a.z * scalar };
}

// Matrix4x4 乗算
Matrix4x4 Multiply(const Matrix4x4& a, const Matrix4x4& b) {
    Matrix4x4 result{};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] =
                a.m[row][0] * b.m[0][col] +
                a.m[row][1] * b.m[1][col] +
                a.m[row][2] * b.m[2][col] +
                a.m[row][3] * b.m[3][col];
        }
    }
    return result;
}

// Matrix4x4 逆行列
Matrix4x4 Inverse(const Matrix4x4& a) {
    // 省略: main.cpp 仅用到函数名，具体实现可根据实际需要保留
    Matrix4x4 A = a;
    Matrix4x4 B = MakeIdentity4x4();
    int i, j, k;
    for (i = 0; i < 4; ++i) {
        float scale = 1.0f / A.m[i][i];
        for (j = 0; j < 4; ++j) {
            A.m[i][j] *= scale;
            B.m[i][j] *= scale;
        }
        for (k = 0; k < 4; ++k) {
            if (k != i) {
                float factor = A.m[k][i];
                for (j = 0; j < 4; ++j) {
                    A.m[k][j] -= factor * A.m[i][j];
                    B.m[k][j] -= factor * B.m[i][j];
                }
            }
        }
    }
    return B;
}

// 单位矩阵
Matrix4x4 MakeIdentity4x4() {
    Matrix4x4 identity{};
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            identity.m[i][j] = (i == j) ? 1.0f : 0.0f;
    return identity;
}

// 仿射变换矩阵
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
    Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
    Matrix4x4 rotateMatrix = MakeRotateXYZMatrix(rotate);
    Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
    return Multiply(scaleMatrix, Multiply(rotateMatrix, translateMatrix));
}

// 旋转矩阵
Matrix4x4 MakeRotateXMatrix(float radian) {
    Matrix4x4 rotateX{};
    rotateX.m[0][0] = 1.0f;
    rotateX.m[1][1] = std::cos(radian);
    rotateX.m[1][2] = std::sin(radian);
    rotateX.m[2][1] = -std::sin(radian);
    rotateX.m[2][2] = std::cos(radian);
    rotateX.m[3][3] = 1.0f;
    return rotateX;
}
Matrix4x4 MakeRotateYMatrix(float radian) {
    Matrix4x4 rotateY{};
    rotateY.m[0][0] = std::cos(radian);
    rotateY.m[0][2] = -std::sin(radian);
    rotateY.m[1][1] = 1.0f;
    rotateY.m[2][0] = std::sin(radian);
    rotateY.m[2][2] = std::cos(radian);
    rotateY.m[3][3] = 1.0f;
    return rotateY;
}
Matrix4x4 MakeRotateZMatrix(float radian) {
    Matrix4x4 rotateZ{};
    rotateZ.m[0][0] = std::cos(radian);
    rotateZ.m[0][1] = std::sin(radian);
    rotateZ.m[1][0] = -std::sin(radian);
    rotateZ.m[1][1] = std::cos(radian);
    rotateZ.m[2][2] = 1.0f;
    rotateZ.m[3][3] = 1.0f;
    return rotateZ;
}
Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate) {
    return Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));
}

// 缩放矩阵
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
    Matrix4x4 result{};
    result.m[0][0] = scale.x;
    result.m[1][1] = scale.y;
    result.m[2][2] = scale.z;
    result.m[3][3] = 1.0f;
    return result;
}

// 平移矩阵
Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
    Matrix4x4 result = MakeIdentity4x4();
    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;
    return result;
}

// 透视投影矩阵
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRaito, float nearClip, float farClip) {
    Matrix4x4 result{};
    result.m[0][0] = (1.0f / aspectRaito) * (1.0f / std::tan(fovY / 2.0f));
    result.m[1][1] = 1.0f / std::tan(fovY / 2.0f);
    result.m[2][2] = farClip / (farClip - nearClip);
    result.m[2][3] = 1.0f;
    result.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
    return result;
}

// 视口矩阵
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
    Matrix4x4 result{};
    result.m[0][0] = width / 2.0f;
    result.m[1][1] = -height / 2.0f;
    result.m[2][2] = maxDepth - minDepth;
    result.m[3][0] = left + width / 2.0f;
    result.m[3][1] = top + height / 2.0f;
    result.m[3][2] = minDepth;
    result.m[3][3] = 1.0f;
    return result;
}

// 绘制网格
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
    (void)viewProjectionMatrix;
    (void)viewportMatrix;
}

// 运算符重载
Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(const Vector3& v, float s) { return Multiply(v, s); }
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }

// Matrix4x4同士の乗算演算子オーバーロードの実装
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.m[row][col] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result.m[row][col] += m1.m[row][k] * m2.m[k][col];
            }
        }
    }
    return result;
}