#include"../../common.h"

class Player;

// カメラの注視点の高さ
#define CAMERA_LOOK_AT_HEIGHT 30.0f

class Camera
{
private:
	VECTOR location;				//カメラの位置
	VECTOR position1;				//垂直角度算出用
	VECTOR position2;				//水平角度算出用
	VECTOR lookAtPosition;			//カメラの注視点
	VECTOR dVec;					//方向ベクトル
	VECTOR identity;				//正規化後のベクトル

	float magnitude;				//ベクトルの大きさ

	float lookAtDistance;			//カメラと注視点の距離

	float vAngle;					//垂直角度
	float hAngle;					//水平角度

	float baseLocX;					//画面中央x
	float baseLocY;					//画面中央y

	float sinPara;					//sinの値
	float cosPara;					//cosの値

public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//更新
	void Update(Player* player);

	//描画
	void Draw()const;

	//方向ベクトルを取得する
	VECTOR GetDVec() { return dVec; }

	//正規化後のベクトルを取得する
	VECTOR GetIdentity() { return identity; }

	//水平角度を取得する
	float GetHAngle() { return hAngle; }
};