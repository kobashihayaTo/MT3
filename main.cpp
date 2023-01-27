#include "DxLib.h"
#include "Vector3.h"
#include <cstring>

// 球(sphere)の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int
	SpcColor, const int FillFlag);

// 線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

// カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition, // カメラの位置
	const Vector3& cameraTarget,   // カメラの注視点
	const Vector3& vameraUp        // カメラの上の向き
);

void DrawAxis3D(const float lengh); // x,y,z 軸の描画

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2C_10_コバシ_ハヤト";
const int WindowWidth = 1600;
const int WindowHeight = 900;
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WindowWidth, WindowHeight, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0, 0, 64);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(TRUE); // Zバッファを有効にする
	SetWriteZBuffer3D(TRUE); // Zバッファへの書き込みを有効にする

	// クリップ面   近　　　遠
	SetCameraNearFar(1.0f, 1000.0f); // カメラの有効範囲の設定
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f); // 画面の中心をカメラの中心に合わせる
	SetCameraPositionAndTargetAndUpVec(
		Vector3(0.0f, 200.0f, 0.0f),
		Vector3(0.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f)
	);

	// 時間計測に必要なデータ
	long long startCount = 0;
	long long nowCount = 0;
	long long elapsedCount = 0;

	// 補間で使うデータ
	// start -> end を 5 [s] で完了させる
	Vector3 p0(-100.0f, 0.0f, 0.0f);  // スタート地点
	Vector3 p1(-0.0f, 0.0f, +100.0f);  // 制御点
	Vector3 p2(+0.0f, 0.0f, -100.0f);  // 制御点
	Vector3 p3(+100.0f, 0.0f, 0.0f);  // エンド地点
	float maxTime = 5.0f; // 全体時間[s]
	float timeRate;       // 何% 時間が進んだか(率)

	// 球の位置
	Vector3 position;

	//プレイヤー
	Vector3 player;
	float X = 0;
	float Y = 0;
	float Z = 0;

	int time = 200;
	int coolTime = 50;
	bool timerFlag = false;

	// 実行前にカウンタ値を取得
	startCount = GetNowHiPerformanceCount(); // long long int型 64bit int 

	// 画像などのリソースデータの変数宣言と読み込み

	// ゲームループで使う変数の宣言

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		// [R]キーで、リスタート
		if (CheckHitKey(KEY_INPUT_R)) {
			startCount = GetNowHiPerformanceCount();
		}

		if (keys[KEY_INPUT_RIGHT]==1&& oldkeys[KEY_INPUT_RIGHT] == 0)
		{
			timerFlag = true;
			Z = 30;
		}

		if (timerFlag == true)
		{
			coolTime--;
		}
		if (coolTime <= 0 && timerFlag == true)
		{
			timerFlag = false;
			coolTime = 50;
			Z = 0;
		}
		// 経過時間(wlapsedTime[s])の計算
		nowCount = GetNowHiPerformanceCount();
		elapsedCount = nowCount - startCount;
		float elapsedTime = static_cast<float> (elapsedCount) / 1'000'000.0f;

		// スタート地点　：　start
		// エンド地点　：　end
		// 経過時間　：　wlapsedTime[s]
		// 移動完了の率(経過時間/全体時間) : timeRate(%)

		timeRate = min(elapsedTime / maxTime, 1.0f);

		// 2次ベジェ曲線の考え方を適用する
		Vector3 a = lerp(p0, p1, timeRate);
		Vector3 b = lerp(p1, p2, timeRate);
		Vector3 c = lerp(p2, p3, timeRate);
		Vector3 d = lerp(a, b, timeRate);
		Vector3 e = lerp(b, c, timeRate);

		position = lerp(d, e, timeRate);

		player = { X,Y,Z };

		// position = easeIn(start, end, timeRate);
		// position = easeOut(start,end,timeRate);
		// position = easeInOut(start,end,timeRate);

		// 描画処理
		ClearDrawScreen(); // 画面を消去
		DrawAxis3D(500.0f); // xyz軸の描画

		// 球の描画
		DrawSphere3D(player, 5.0f, 32, GetColor(0, 0, 0), GetColor(255, 255, 255), TRUE);

		DrawSphere3D(position, 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p0, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p1, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p2, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
		DrawSphere3D(p3, 3.0f, 32, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);

		//
		DrawFormatString(0, 0, GetColor(255, 255, 255), "position(%5.1f,%5.1f,%5.1f)", position.x, position.y, position.z);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%7.3f[s]", elapsedTime);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "[R] : Restart");
		DrawFormatString(0, 60, GetColor(255, 255, 255), "p0 (%6.1f,%6.1f,%6.1f)", p0.x, p0.y, p0.z);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "p1 (%6.1f,%6.1f,%6.1f)", p1.x, p1.y, p1.z);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "p2 (%6.1f,%6.1f,%6.1f)", p2.x, p2.y, p2.z);
		DrawFormatString(0, 120, GetColor(255, 255, 255), "p3 (%6.1f,%6.1f,%6.1f)", p3.x, p3.y, p3.z);

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

// x軸、ｙ軸、ｚ軸の描画
void DrawAxis3D(const float length)
{
	DrawLine3D(Vector3(-length, 0, 0), Vector3(+length, 0, 0), GetColor(255, 0, 0)); // ｘ軸
	DrawLine3D(Vector3(0, -length, 0), Vector3(0, +length, 0), GetColor(0, 255, 0)); // ｙ軸
	DrawLine3D(Vector3(0, 0, -length), Vector3(0, 0, +length), GetColor(0, 0, 255)); // ｚ軸
}

// カメラの位置と姿勢の設定
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,  // カメラの位置
	const Vector3& cameraTarget,    // カメラの注視点
	const Vector3& cameraUp         // カメラの上の向き
)
{
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}

// 球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

// 線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z }; // 構造体　初期化子リスト
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z }; // 構造体　初期化子リスト

	return DrawLine3D(p1, p2, Color);
}