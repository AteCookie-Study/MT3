#include <Novice.h>
#include <Vector3.h>
#include <math.h>

struct Matrix4x4
{
	float m[4][4];
};

const char kWindowTitle[] = "GC2C_03_キョク_キンウ";
const int kWindowWidth = 1280; // 画面の横幅
const int kWindowHeight = 720; // 画面の縦幅

//Vector3 Add(const Vector3& v1, const Vector3& v2);
//Vector3 Sub(const Vector3& v1, const Vector3& v2);
//Vector3 Mul(float scalar, const Vector3& v);
//float Dot(const Vector3& v1, const Vector3& v2);
//float Length(const Vector3& v);
//Vector3 Normalize(const Vector3& v);

//行列の加法
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
//行列の減法
Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2);
//行列の積
Matrix4x4 Mul(const Matrix4x4& m1, const Matrix4x4& m2);
//逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
//行列の転置
Matrix4x4 Transpose(const Matrix4x4& m);
//单位行列の作成
Matrix4x4 MakeIdentity4x4();

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

//void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
//	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
//	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
//	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
//	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
//}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%6.02f", matrix.m[row][column]);
		}
	}

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	/// 初期処理

	/*Vector3 v1{ 1.0f,3.0f,-5.0f };
	Vector3 v2{ 4.0f,-1.0f,2.0f };*/
	Matrix4x4 m1 = { 3.2f,0.7f,9.6f,4.4f,
	    5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f 
	};
	Matrix4x4 m2 = { 4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};

	/*float k = { 4.0f };*/

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		/*Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSub = Sub(v1, v2);
		Vector3 resultMul = Mul(k, v1);

		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Normalize(v2);*/

		Matrix4x4 resultAdd = Add(m1, m2);
		Matrix4x4 resultMul = Mul(m1, m2);
		Matrix4x4 resultSub = Sub(m1, m2);
		Matrix4x4 inverseM1 = Inverse(m1);
		Matrix4x4 inverseM2 = Inverse(m2);
		Matrix4x4 transposeM1 = Transpose(m1);
		Matrix4x4 transposeM2 = Transpose(m2);
		Matrix4x4 identity = MakeIdentity4x4();


		///
		/// ↑更新処理ここまで
		///

		//-------------------------------------//

		///
		/// ↓描画処理ここから
		///

		/*VectorScreenPrintf(0, 0, resultAdd, "Add");	
		VectorScreenPrintf(0, 20, resultSub, "Sub");
		VectorScreenPrintf(0, 40, resultMul, "Mul");
		Novice::ScreenPrintf(0, 60, "Dot: %.02f", resultDot);
		Novice::ScreenPrintf(0, 80, "Length: %.02f", resultLength);
		VectorScreenPrintf(0, 100, resultNormalize, "Normalize");*/

		Novice::ScreenPrintf(0, 0, "Add");
		MatrixScreenPrintf(0, 20, resultAdd);
		Novice::ScreenPrintf(0, 100, "Sub");
		MatrixScreenPrintf(0, 120, resultSub);
		Novice::ScreenPrintf(0, 200, "Mul");
		MatrixScreenPrintf(0, 220, resultMul);
		Novice::ScreenPrintf(0, 300, "InverseM1");
		MatrixScreenPrintf(0, 320, inverseM1);
		Novice::ScreenPrintf(0, 400, "InverseM2");
		MatrixScreenPrintf(0, 420, inverseM2);

		Novice::ScreenPrintf(500, 00, "TransposeM1");
		MatrixScreenPrintf(500, 20, transposeM1);
		Novice::ScreenPrintf(500, 100, "TransposeM2");
		MatrixScreenPrintf(500, 120, transposeM2);
		Novice::ScreenPrintf(500, 200, "Identity");
		MatrixScreenPrintf(500, 220, identity);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

//Vector3 Add(const Vector3& v1, const Vector3& v2)
//{
//	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
//	
//}
//Vector3 Sub(const Vector3& v1, const Vector3& v2)
//{
//	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
//	
//}
//Vector3 Mul(float scalar, const Vector3& v)
//{
//	return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
//	
//}
//float Dot(const Vector3& v1, const Vector3& v2)
//{
//	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
//}
//float Length(const Vector3& v)
//{
//	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
//}
//Vector3 Normalize(const Vector3& v){
//	Vector3 result;
//	result.x = v.x / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
//	result.y = v.y / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
//	result.z = v.z / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
//	return result;
//}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] = m1.m[row][column] + m2.m[row][column];
		}
	}
	return result;
}
Matrix4x4 Sub(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] = m1.m[row][column] - m2.m[row][column];
		}
	}
	return result;
}
Matrix4x4 Mul(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] = m1.m[row][0] * m2.m[0][column] +
				m1.m[row][1] * m2.m[1][column] +
				m1.m[row][2] * m2.m[2][column] +
				m1.m[row][3] * m2.m[3][column];
		}
	}
	return result;
}
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result{};
	float det = 0.0f;
	for (int i = 0; i < 4; ++i) {
		det += (m.m[0][i] * (m.m[1][(i + 1) % 4] * m.m[2][(i + 2) % 4] * m.m[3][(i + 3) % 4] -
			m.m[1][(i + 2) % 4] * m.m[2][(i + 1) % 4] * m.m[3][(i + 3) % 4]));
	}
	if (det == 0.0f) {
		return result;
	}
	float invDet = 1.0f / det;
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] =
				(m.m[(row + 1) % 4][(column + 1) % 4] * m.m[(row + 2) % 4][(column + 2) % 4] * m.m[(row + 3) % 4][(column + 3) % 4] -
					m.m[(row + 1) % 4][(column + 2) % 4] * m.m[(row + 2) % 4][(column + 1) % 4] * m.m[(row + 3) % 4][(column + 3) % 4]) * invDet;
		}
	}
	return result;
}
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.m[row][column] = m.m[column][row];
		}
	}
	return result;
}
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result{};
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			if (row == column) {
				result.m[row][column] = 1.0f;
			}
			else {
				result.m[row][column] = 0.0f;
			}
		}
	}
	return result;
}
