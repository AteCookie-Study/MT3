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
		
		// 行列の加法（m1 と m2 の各要素を加算）
		Matrix4x4 resultAdd = Add(m1, m2);
		// 行列の積（m1 と m2 を掛け算）
		Matrix4x4 resultMul = Mul(m1, m2);
		// 行列の減法（m1 から m2 を減算）
		Matrix4x4 resultSub = Sub(m1, m2);
		// m1 の逆行列を計算
		Matrix4x4 inverseM1 = Inverse(m1);
		// m2 の逆行列を計算
		Matrix4x4 inverseM2 = Inverse(m2);
		// m1 の転置行列を計算
		Matrix4x4 transposeM1 = Transpose(m1);
		// m2 の転置行列を計算
		Matrix4x4 transposeM2 = Transpose(m2);
		// 単位行列を作成
		Matrix4x4 identity = MakeIdentity4x4();


		///
		/// ↑更新処理ここまで
		///

		//-------------------------------------//

		///
		/// ↓描画処理ここから
		///

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
	float inv[16], det;
	float mat[16];

	
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			mat[i * 4 + j] = m.m[i][j];

	inv[0] = mat[5] * mat[10] * mat[15] -
		mat[5] * mat[11] * mat[14] -
		mat[9] * mat[6] * mat[15] +
		mat[9] * mat[7] * mat[14] +
		mat[13] * mat[6] * mat[11] -
		mat[13] * mat[7] * mat[10];

	inv[4] = -mat[4] * mat[10] * mat[15] +
		mat[4] * mat[11] * mat[14] +
		mat[8] * mat[6] * mat[15] -
		mat[8] * mat[7] * mat[14] -
		mat[12] * mat[6] * mat[11] +
		mat[12] * mat[7] * mat[10];

	inv[8] = mat[4] * mat[9] * mat[15] -
		mat[4] * mat[11] * mat[13] -
		mat[8] * mat[5] * mat[15] +
		mat[8] * mat[7] * mat[13] +
		mat[12] * mat[5] * mat[11] -
		mat[12] * mat[7] * mat[9];

	inv[12] = -mat[4] * mat[9] * mat[14] +
		mat[4] * mat[10] * mat[13] +
		mat[8] * mat[5] * mat[14] -
		mat[8] * mat[6] * mat[13] -
		mat[12] * mat[5] * mat[10] +
		mat[12] * mat[6] * mat[9];

	inv[1] = -mat[1] * mat[10] * mat[15] +
		mat[1] * mat[11] * mat[14] +
		mat[9] * mat[2] * mat[15] -
		mat[9] * mat[3] * mat[14] -
		mat[13] * mat[2] * mat[11] +
		mat[13] * mat[3] * mat[10];

	inv[5] = mat[0] * mat[10] * mat[15] -
		mat[0] * mat[11] * mat[14] -
		mat[8] * mat[2] * mat[15] +
		mat[8] * mat[3] * mat[14] +
		mat[12] * mat[2] * mat[11] -
		mat[12] * mat[3] * mat[10];

	inv[9] = -mat[0] * mat[9] * mat[15] +
		mat[0] * mat[11] * mat[13] +
		mat[8] * mat[1] * mat[15] -
		mat[8] * mat[3] * mat[13] -
		mat[12] * mat[1] * mat[11] +
		mat[12] * mat[3] * mat[9];

	inv[13] = mat[0] * mat[9] * mat[14] -
		mat[0] * mat[10] * mat[13] -
		mat[8] * mat[1] * mat[14] +
		mat[8] * mat[2] * mat[13] +
		mat[12] * mat[1] * mat[10] -
		mat[12] * mat[2] * mat[9];

	inv[2] = mat[1] * mat[6] * mat[15] -
		mat[1] * mat[7] * mat[14] -
		mat[5] * mat[2] * mat[15] +
		mat[5] * mat[3] * mat[14] +
		mat[13] * mat[2] * mat[7] -
		mat[13] * mat[3] * mat[6];

	inv[6] = -mat[0] * mat[6] * mat[15] +
		mat[0] * mat[7] * mat[14] +
		mat[4] * mat[2] * mat[15] -
		mat[4] * mat[3] * mat[14] -
		mat[12] * mat[2] * mat[7] +
		mat[12] * mat[3] * mat[6];

	inv[10] = mat[0] * mat[5] * mat[15] -
		mat[0] * mat[7] * mat[13] -
		mat[4] * mat[1] * mat[15] +
		mat[4] * mat[3] * mat[13] +
		mat[12] * mat[1] * mat[7] -
		mat[12] * mat[3] * mat[5];

	inv[14] = -mat[0] * mat[5] * mat[14] +
		mat[0] * mat[6] * mat[13] +
		mat[4] * mat[1] * mat[14] -
		mat[4] * mat[2] * mat[13] -
		mat[12] * mat[1] * mat[6] +
		mat[12] * mat[2] * mat[5];

	inv[3] = -mat[1] * mat[6] * mat[11] +
		mat[1] * mat[7] * mat[10] +
		mat[5] * mat[2] * mat[11] -
		mat[5] * mat[3] * mat[10] -
		mat[9] * mat[2] * mat[7] +
		mat[9] * mat[3] * mat[6];

	inv[7] = mat[0] * mat[6] * mat[11] -
		mat[0] * mat[7] * mat[10] -
		mat[4] * mat[2] * mat[11] +
		mat[4] * mat[3] * mat[10] +
		mat[8] * mat[2] * mat[7] -
		mat[8] * mat[3] * mat[6];

	inv[11] = -mat[0] * mat[5] * mat[11] +
		mat[0] * mat[7] * mat[9] +
		mat[4] * mat[1] * mat[11] -
		mat[4] * mat[3] * mat[9] -
		mat[8] * mat[1] * mat[7] +
		mat[8] * mat[3] * mat[5];

	inv[15] = mat[0] * mat[5] * mat[10] -
		mat[0] * mat[6] * mat[9] -
		mat[4] * mat[1] * mat[10] +
		mat[4] * mat[2] * mat[9] +
		mat[8] * mat[1] * mat[6] -
		mat[8] * mat[2] * mat[5];

	det = mat[0] * inv[0] + mat[1] * inv[4] + mat[2] * inv[8] + mat[3] * inv[12];

	if (det == 0.0f) {
		return result; 
	}

	det = 1.0f / det;

	for (int i = 0; i < 16; ++i) {
		((float*)result.m)[i] = inv[i] * det;
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
