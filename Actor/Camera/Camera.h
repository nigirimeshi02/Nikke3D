#include"../../common.h"

class GameMainScene;

#define CAMERA_LOOK_AT_HEIGHT 30.0f	// カメラの注視点の高さ

class Camera
{
private:
	VECTOR location;				//カメラの位置
	VECTOR position1;				//垂直角度算出用
	VECTOR position2;				//水平角度算出用
	VECTOR lookAtPosition;			//カメラの注視点

	float lookAtDistance;			//カメラと注視点の距離

	float vAngle;					//垂直角度
	float hAngle;					//水平角度

	float sinPara;					//sinの値
	float cosPara;					//cosの値

public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//更新
	void Update(GameMainScene* object);

	//描画
	void Draw()const;

	//水平角度を取得する
	float GetHAngle() { return hAngle; }
};