#include <Novice.h>
#include"Cal.h"
#include"Draw.h"
#include <imgui.h>


const char kWindowTitle[] = "GC2C_03_キョク_キンウ";
const int kWindowWidth = 1280; // 画面の横幅
const int kWindowHeight = 720; // 画面の縦幅


static const int kRowHeight = 20;
static const int kColumnWidth = 60;

Matrix4x4 MakeViewProjectionMatrix(Vector3 scale, Vector3 rotate, Vector3 translate, Vector3 cameraScale, Vector3 cameraRotate, Vector3 cameraTranslate) {
	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix(cameraScale, cameraRotate, cameraTranslate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	return (Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix)));

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/// 初期処理
	Vector3 cameraTranslate{ 0.00f,1.90f,-5.0f };
	Vector3 cameraRotate{ 0.39f,0.0f,0.0f };

	Vector3 controlPoint[4] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
		{-0.53f,-0.26f,-0.15f},
	};

	Sphere controlSphere[4] = {};

	for (uint32_t i = 0; i < 4; i++) {
		controlSphere[i].center = controlPoint[i];
		
		controlSphere[i].radius = 0.01f;
		controlSphere[i].rotate = { 0.0f,0.0f,0.0f };
	}

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);


		ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("controlPoint0", &controlSphere[0].center.x, 0.01f);
		ImGui::DragFloat3("controlPoint1", &controlSphere[1].center.x, 0.01f);
		ImGui::DragFloat3("controlPoint2", &controlSphere[2].center.x, 0.01f);

		ImGui::End();
		/// ↑更新処理ここまで
		///

		//-------------------------------------//

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawCatmullRom(controlSphere[0].center, controlSphere[1].center, controlSphere[2].center, controlSphere[3].center, viewProjectionMatrix, viewportMatrix, BLACK);
		for (uint32_t i = 0; i < 4; i++) {
			DrawSphere(controlSphere[i], viewProjectionMatrix, viewportMatrix);
		}
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