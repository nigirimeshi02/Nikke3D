#include"../../common.h"
#include "Enemy.h"
#include "../../calculation/calculation.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include"../../ResourceManager/Model/ModelManager.h"


Enemy::Enemy()
{
	angle = 0.f;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;

	location = VGet(0.0f, 0.0f, 50.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);
	directionVec = VGet(0.0f, 0.0f, 0.0f);

	speed = 0.5;

	//３Ｄモデルのスケールを2.5倍にする
	MV1SetScale(ModelManager::GetModelHandle(Anis), VGet(3.0f, 3.0f, 3.0f));

	//武器
	weaponAttachFrameNum = MV1SearchFrame(ModelManager::GetModelHandle(Anis), "右人指１");
	matrix = MV1GetFrameLocalWorldMatrix(ModelManager::GetModelHandle(Anis), weaponAttachFrameNum);
	MV1SetScale(ModelManager::GetModelHandle(Sword), VGet(0.05f, 0.05f, 0.05f));
}

Enemy::~Enemy()
{

}

void Enemy::Update(GameMainScene* gm)
{
	//ベクトルの設定
	SetVector(gm->GetPlayer());

	//角度を設定
	SetRotation(gm->GetPlayer());



	//座標をセットする
	MV1SetPosition(ModelManager::GetModelHandle(Anis), location);

	//回転値をセットする
	MV1SetRotationXYZ(ModelManager::GetModelHandle(Anis), rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(Anis), animIndex, animPlayTime);

	Movement();


	weaponLocation = MV1GetFramePosition(ModelManager::GetModelHandle(Anis), weaponAttachFrameNum);
	MV1SetPosition(ModelManager::GetModelHandle(Sword), weaponLocation);
}

void Enemy::Draw() const
{
	MV1DrawModel(ModelManager::GetModelHandle(Anis));
	MV1DrawModel(ModelManager::GetModelHandle(Sword));

	DrawFormatString(0, 0 + 48, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 16 + 48, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 32 + 48, 0xffffff, "z:%f", location.z);

	DrawFormatString(200, 0 + 48, 0xffffff, "x:%f", vec.x);
	DrawFormatString(200, 16 + 48, 0xffffff, "y:%f", vec.y);
	DrawFormatString(200, 32 + 48, 0xffffff, "z:%f", vec.z);
	DrawFormatString(200, 48 + 48, 0xffffff, "angle:%f", angle);
	DrawFormatString(200, 64 + 48, 0xffffff, "rot.y:%f", rotation.y);
}

void Enemy::Movement()
{
	location.x += vec.x;
	//location.y += vec.y;
	location.z += vec.z;
}

void Enemy::Animation()
{
	//待機
	if (Get3DVectorLength(vec) == 0) {
		isIdle = true;
		isWalk = false;
		isDash = false;
	}
	//歩く
	else if (Get3DVectorLength(vec) > 0) {
		isIdle = false;
		isWalk = true;
		isDash = false;
	}

	animPlayTime += .5f;

	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = MOVE_SPEED;
	}

	//待機アニメーションの読み込み
	if (isIdle && animState != playerAnim::Idle)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(Anis), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(Anis), playerAnim::Idle, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(Anis), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//歩くアニメーションの読み込み
	if (isWalk && animState != playerAnim::Walk)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(Anis), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(Anis), playerAnim::Walk, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(Anis), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//走るアニメーションの読み込み
	if (isDash && animState != playerAnim::Dash)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(Anis), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(Anis), playerAnim::Dash, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(Anis), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Dash;
	}
}

void Enemy::SetRotation(Player* p)
{
	//基準ベクトルの設定
	VECTOR baseVec;
	baseVec = { 0,0,-10 };

	//ベクトルの長さ
	float dis;
	dis = Get3DVectorLength(directionVec);

	//角度の取得
	angle = GetAngle2Vector(directionVec, baseVec);

	//cosでは0~180までしか取れないので180~359までの正規化
	if (directionVec.x > 0) {
		float tmp = 180 + (180 - angle);
		rotation.y = d_r(tmp);
	}
	else {
		rotation.y = d_r(angle);
	}
}

void Enemy::SetVector(Player* p)
{
	//プレイヤーの位置とエネミーの位置からベクトルを出す
	VECTOR tmp;
	tmp = { p->GetLocation().x - location.x, p->GetLocation().y - location.y, p->GetLocation().z - location.z };

	//プレイヤーとエネミーの距離
	float dis;
	dis = sqrtf(pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2));

	//単位ベクトル
	VECTOR tmp1;
	//距離が0だった場合単位ベクトルをすべて0にする
	if (dis != 0) {
		tmp1 = { tmp.x / dis,tmp.y / dis, tmp.z / dis };
	}
	else {
		tmp1 = { 0,0,0 };
	}

	//プレイヤーと距離が近づいたらストップ
	if (dis < 30.) {
		vec = { 0,0,0 };
	}
	//プレイヤーと距離が遠かったらベクトルを代入
	else{
		//ベクトルに代入
		vec = { tmp1.x * speed,tmp1.y * speed ,tmp1.z * speed };
	}
	
	//キャラクターの方向保持
	directionVec = { tmp1.x * speed,tmp1.y * speed ,tmp1.z * speed };
}

