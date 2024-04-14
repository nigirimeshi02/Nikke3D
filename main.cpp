#include"SceneManager/SceneManager.h"
#include"Scene/Load/LoadScene.h"
#include"common.h"
#include"InputControl/Key/KeyInput.h"
#include"InputControl/Pad/PadInput.h"
#include"ResourceManager/Model/ModelManager.h"

/************************************************
* プログラムの開始
*************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	double nextTime = GetNowCount();	//システム時間の取得

	//タイトル
	SetMainWindowText("3D");

	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);	

	//常にアクティブ状態にする
	//SetAlwaysRunFlag(TRUE);	

	//画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	

	//DXライブラリの初期化処理
	if (DxLib_Init() == -1)return -1;	

	//描画先を裏にする
	SetDrawScreen(DX_SCREEN_BACK);		

	// Zバッファを有効にする。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	SetWriteZBuffer3D(TRUE);

	//背景の色を灰色にする
	SetBackgroundColor(128, 128, 128);

	//マウスカーソルを画面中央に設定
	SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//マウスカーソルを表示しない
	SetMouseDispFlag(FALSE);

	try
	{
		ModelManager::CreateModelManager();

		SceenManager* sceenManager = new SceenManager(dynamic_cast<SceneBase*>(new LoadScene()));

		//ゲームループ
		while ((ProcessMessage() == 0) &&
			sceenManager->Update() != nullptr &&
			!(CheckHitKey(KEY_INPUT_ESCAPE)))

		{	//画面の初期化
			ClearDrawScreen();

			KeyInput::Update();

			PadInput::Update();

			sceenManager->Draw();


			nextTime += 1.0 / 60.0 * 1000.0;		//フレームレートの設定＋ミリ単位に合わせる

			//現在の時間が現在のシステム時間をこえたら
			//現在の時間を現在のシステム時間を引いた分だけ待たせる
			if (nextTime > GetNowCount())
			{
				WaitTimer((int)nextTime - GetNowCount());
			}
			//現在のシステム時間を取得
			else
			{
				nextTime = GetNowCount();
			}

			//裏画面の内容を表画面に反映
			ScreenFlip();

		}
	}
	catch (const char* errorLog)
	{
		OutputDebugString(_T(errorLog));

		return -1;
	}

	ModelManager::DeleteModleManager();

	//DXライブラリ使用の終了処理
	DxLib_End();		

	return 0;

}