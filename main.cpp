#include <Novice.h>
#include"Cal.h"
#include"Draw.h"
#include <imgui.h>

const char kWindowTitle[] = "GC2C_03_キョク_キンウ";
const int kWindowWidth = 1280; // 画面の横幅
const int kWindowHeight = 720; // 画面の縦幅


static const int kRowHeight = 20;
static const int kColumnWidth = 60;



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	/// 初期処理
	Vector3 rotate = {};
	Vector3 translate = {};
	Vector3 cameraTranslate = { 0.0f,1.9f,-6.49f };
	Vector3 cameraRotate = { 0.26f,0.0f,0.0f };

	AABB aabb1{
		{-0.5f,-0.5f,-0.5f},
		{0.0f, 0.0f, 0.0f},
	};
	AABB aabb2{
		{0.2f, 0.2f, 0.2f},
		{1.0f, 1.0f, 1.0f},
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
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldMViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewPortMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);


		/// ↑更新処理ここまで
		///

		//-------------------------------------//

		///
		/// ↓描画処理ここから
		///
		DrawGrid(worldMViewProjectionMatrix, viewportMatrix);

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("AABB1", &aabb1.max.x, 0.01f);
		ImGui::DragFloat3("AABB1", &aabb1.min.x, 0.01f);
		ImGui::DragFloat3("AABB2", &aabb2.max.x, 0.01f);
		ImGui::DragFloat3("AABB2", &aabb2.min.x, 0.01f);
		ImGui::End();

		if (IsCollision(aabb1, aabb2)) {
			DrawAABB(aabb1, worldMViewProjectionMatrix, viewportMatrix, RED);
		}
		else
		{
			DrawAABB(aabb1, worldMViewProjectionMatrix, viewportMatrix, WHITE);
		}
		DrawAABB(aabb2, worldMViewProjectionMatrix, viewportMatrix, WHITE);

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