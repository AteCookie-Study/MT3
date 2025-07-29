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

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};
	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	uint32_t color[3]{};
	color[0] = RED;
	color[1] = GREEN;
	color[2] = BLUE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		// Imgui
			ImGui::Begin("Window");
		ImGui::DragFloat3("cameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.01f);

		ImGui::DragFloat3("Scale0", &scales[0].x, 0.01f);
		ImGui::DragFloat3("Rotate0", &rotates[0].x, 0.01f);
		ImGui::DragFloat3("Translate0", &translates[0].x, 0.01f);

		ImGui::DragFloat3("Scale1", &scales[1].x, 0.01f);
		ImGui::DragFloat3("Rotate1", &rotates[1].x, 0.01f);
		ImGui::DragFloat3("Translate1", &translates[1].x, 0.01f);

		ImGui::DragFloat3("Scale2", &scales[2].x, 0.01f);
		ImGui::DragFloat3("Rotate2", &rotates[2].x, 0.01f);
		ImGui::DragFloat3("Translate2", &translates[2].x, 0.01f);


		ImGui::End();

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);

		Matrix4x4 worldMatrix[3]{};
		Matrix4x4 localMatrix[3]{};
		for (uint32_t i = 0; i < 3; i++)
		{
			localMatrix[i] = MakeAffineMatrix(scales[i], rotates[i], translates[i]);
		}
		worldMatrix[0] = localMatrix[0];
		worldMatrix[1] = Multiply(MakeAffineMatrix(scales[1], rotates[1], translates[1]), localMatrix[0]);
		worldMatrix[2] = Multiply(Multiply(MakeAffineMatrix(scales[2], rotates[2], translates[2]), localMatrix[1]), localMatrix[0]);


		/// ↑更新処理ここまで
		///

		//-------------------------------------//

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		// 各球体をつなぐ線を引くための点を求める処理
		Vector3 screenPos[3]{};
		for (uint32_t i = 0; i < 3; i++)
		{
			Matrix4x4 wvpMatix = Multiply(worldMatrix[i], viewProjectionMatrix);
			Vector3	ndc = Transform(Vector3(0, 0, 0), wvpMatix);
			screenPos[i] = Transform(ndc, viewportMatrix);
		}

		Novice::DrawLine(int(screenPos[0].x), int(screenPos[0].y), int(screenPos[1].x), int(screenPos[1].y), WHITE);
		Novice::DrawLine(int(screenPos[1].x), int(screenPos[1].y), int(screenPos[2].x), int(screenPos[2].y), WHITE);

		for (uint32_t i = 0; i < 3; ++i)
		{
			DrawSphereWorldMatrix(worldMatrix[i], viewProjectionMatrix, viewportMatrix, color[i]);
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