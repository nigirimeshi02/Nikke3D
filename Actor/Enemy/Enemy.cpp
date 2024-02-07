#include"../../common.h"
#include "Enemy.h"
#include "../../calculation/calculation.h"
#include "../../Scene/GameMain/GameMainScene.h"


Enemy::Enemy()
{
	//３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("Anis.fbm/Anis-Apose.pmx");

	angle = 0.f;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;

	location = VGet(0.0f, 0.0f, 50.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);
	directionVec = VGet(0.0f, 0.0f, 0.0f);

	speed = 0.25;

	//３Ｄモデルのスケールを2.5倍にする
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));

	//武器
	weaponModelHandle = MV1LoadModel("Anis.fbm/Sword.mv1");
	weaponAttachFrameNum = MV1SearchFrame(modelHandle, "右人指１");
	MV1SetScale(weaponModelHandle, VGet(0.05f, 0.05f, 0.05f));
	num = MV1GetFrameNum(weaponModelHandle);
	weaponRotation = VGet(0.0f, 0.0f, 0.0f);
}

Enemy::~Enemy()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Update(GameMainScene* gm)
{
	//ベクトルの設定
	SetVector(gm->GetPlayer());

	//角度を設定
	SetRotation(gm->GetPlayer());



	//座標をセットする
	MV1SetPosition(modelHandle, location);

	//回転値をセットする
	MV1SetRotationXYZ(modelHandle, rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(modelHandle, animIndex, animPlayTime);

	Movement();


	
	//weaponLocation = { weaponLocation.x,weaponLocation.y,weaponLocation.z };
	
	/*for (int i = 0; i < 500; i++)
	{
		MV1SetFrameVisible(modelHandle, i, TRUE);
	}*/
	//weaponRotation.x++;
	SetWeaponLocation();
	MV1SetPosition(weaponModelHandle, weaponLocation[1]);
	SetWeaponRotation();
	//MV1SetRotationXYZ(weaponModelHandle, weaponRotation);
}

void Enemy::Draw() const
{
	MV1DrawModel(modelHandle);
	MV1DrawModel(weaponModelHandle);
	/*for (int i = 0; i < 1; i++)
	{
		MV1DrawFrame(modelHandle, i);
	}*/
	//MV1DrawFrame(modelHandle, 1);

	DrawSphere3D(weaponLocation[0], 2, 5, 0xff0000, 0xff0000, TRUE);
	DrawSphere3D(weaponLocation[1], 2, 5, 0xff0000, 0xff0000, TRUE);
	DrawSphere3D(weaponLocationTmp, 2, 5, 0x00ff00, 0xff0000, TRUE);

	DrawFormatString(0, 0 + 48, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 16 + 48, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 32 + 48, 0xffffff, "z:%f", location.z);

	DrawFormatString(200, 0 + 48, 0xffffff, "x:%f", weaponVector.x);
	DrawFormatString(200, 16 + 48, 0xffffff, "y:%f", weaponVector.y);
	DrawFormatString(200, 32 + 48, 0xffffff, "z:%f", weaponVector.z);
	DrawFormatString(200, 48 + 48, 0xffffff, "angle:%f", angle);
	DrawFormatString(200, 64 + 48, 0xffffff, "rot.y:%f", rotation.y);

	DrawFormatString(400, 0 + 48, 0xffffff, "wrx:%f", weaponRotation.x);
	DrawFormatString(400, 16 + 48, 0xffffff, "wry:%f", weaponRotation.y);
	DrawFormatString(400, 32 + 48, 0xffffff, "wrz:%f", weaponRotation.z);

	DrawFormatString(600, 0 + 48, 0xffffff, "x:%f", weaponLocation[1].x);
	DrawFormatString(600, 16 + 48, 0xffffff, "y:%f", weaponLocation[1].y);
	DrawFormatString(600, 32 + 48, 0xffffff, "z:%f", weaponLocation[1].z);
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
		MV1DetachAnim(modelHandle, animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Idle, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//歩くアニメーションの読み込み
	if (isWalk && animState != playerAnim::Walk)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(modelHandle, animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Walk, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//走るアニメーションの読み込み
	if (isDash && animState != playerAnim::Dash)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(modelHandle, animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Dash, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

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

	//角度の取得
	angle = Get3DAngle2Vector(directionVec, baseVec);

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

void Enemy::SetWeaponRotation()
{
	//weaponAttachFrameNum = MV1SearchFrame(modelHandle, "右人指１");
	int frameNum = MV1SearchFrame(modelHandle, "右人指１");
	int frameNum1 = MV1SearchFrame(modelHandle, "右小指１");

	VECTOR loc = MV1GetFramePosition(modelHandle, frameNum);		//人指
	VECTOR loc1 = MV1GetFramePosition(modelHandle, frameNum1);		//小指

	VECTOR v;
	v = { loc.x - loc1.x,loc.y - loc1.y ,loc.z - loc1.z };


	VECTOR tmpv;	
	VECTOR tmp2dBase;	//2d(xとyを使う)

	//x軸の角度
	float tmp;
	//tmp2d = { loc.z - loc1.z, loc.y - loc1.y };
	//tmp2d = { weaponVector.z - loc.z, weaponVector.y - loc.y };
	tmp2dBase = { 0, 50, 0 };
	tmp = Get2DAngle2Vector(weaponVector.z, weaponVector.y, tmp2dBase.z, tmp2dBase.y);
	//tmp = Get3DAngle2Vector(weaponVector, tmp2dBase);
	
	if (weaponVector.z > 0) {
		float d = 180 + (180 - tmp);
		weaponRotation.x = d_r(d);
	}
	else {
		weaponRotation.x = d_r(tmp);
	}

	//weaponRotation.x = d_r(tmp);

	//tmpv = {weaponRotation.x,}

	//MV1SetRotationXYZ(weaponModelHandle, weaponRotation);

	/*tmp2dBase = { tmp2dBase.x,
		Get2DRotation(tmp2dBase.y,tmp2dBase.z,weaponRotation.x).x,
		Get2DRotation(tmp2dBase.y,tmp2dBase.z,weaponRotation.x).y };*/

	tmp2dBase = { tmp2dBase.x,
		Get2DRotation(tmp2dBase.z,tmp2dBase.y,weaponRotation.x).x,
		Get2DRotation(tmp2dBase.z,tmp2dBase.y,weaponRotation.x).y };

	weaponLocationTmp.x = tmp2dBase.x + weaponLocation[0].x;
	weaponLocationTmp.y = tmp2dBase.y + weaponLocation[0].y;
	weaponLocationTmp.z = tmp2dBase.z + weaponLocation[0].z;

	tmp = Get2DAngle2Vector(weaponVector.x, weaponVector.z, tmp2dBase.x, tmp2dBase.z);

	/*if (weaponVector.x > 0) {
		float d = 180 + (180 - tmp);
		weaponRotation.y = d_r(d);
	}else{
		weaponRotation.y = d_r(tmp);
	}*/

	//weaponRotation.y = d_r(tmp);

	/*tmp2dBase = { Get2DRotation(tmp2dBase.x,tmp2dBase.z,-weaponRotation.y).x,
		tmp2dBase.y,
		Get2DRotation(tmp2dBase.x,tmp2dBase.z,weaponRotation.y).y };

	weaponLocationTmp.x = tmp2dBase.x + weaponLocation[0].x;
	weaponLocationTmp.y = tmp2dBase.y + weaponLocation[0].y;
	weaponLocationTmp.z = tmp2dBase.z + weaponLocation[0].z;*/

	tmp = Get2DAngle2Vector(weaponVector.x, weaponVector.y, tmp2dBase.x, tmp2dBase.y);
	//tmp = Get3DAngle2Vector(weaponVector, tmp2dBase);
	/*if (weaponVector.y > 0) {
		float d = 180 + (180 - tmp);
		weaponRotation.z = d_r(d);
	}
	else {
		weaponRotation.z = d_r(tmp);
	}*/
	//weaponRotation.z = d_r(tmp);

	/*tmp2dBase = { Get2DRotation(tmp2dBase.x,tmp2dBase.y,weaponRotation.z).x,
		Get2DRotation(tmp2dBase.x,tmp2dBase.y,weaponRotation.z).y,
		tmp2dBase.z, };

	weaponLocationTmp.x = tmp2dBase.x + weaponLocation[0].x;
	weaponLocationTmp.y = tmp2dBase.y + weaponLocation[0].y;
	weaponLocationTmp.z = tmp2dBase.z + weaponLocation[0].z;*/

	MV1SetRotationXYZ(weaponModelHandle, weaponRotation);
	//MV1SetRotationXYZ(weaponModelHandle, tmp2dBase);

	//weaponRotation.x+= 0.1;
	//weaponRotation.y+= 0.1;
	//weaponRotation.z+= 0.1;
}

void Enemy::SetWeaponLocation()
{
	int frameNum = MV1SearchFrame(modelHandle, "右人指１");
	int frameNum1 = MV1SearchFrame(modelHandle, "右小指１");

	VECTOR loc = MV1GetFramePosition(modelHandle, frameNum);		//人指
	VECTOR loc1 = MV1GetFramePosition(modelHandle, frameNum1);		//小指

	VECTOR v;
	v = { loc.x - loc1.x,loc.y - loc1.y ,loc.z - loc1.z };		//小→人
	//v = { loc1.x - loc.x,loc1.y - loc.y ,loc1.z - loc.z };

	float dis;
	dis = Get3DVectorLength(v);

	//単位ベクトル
	VECTOR tmp;
	//距離が0だった場合単位ベクトルをすべて0にする
	if (dis != 0) {
		tmp = { v.x / dis,v.y / dis, v.z / dis };
	}
	else {
		tmp = { 0,0,0 };
	}

	weaponLocation[0] = MV1GetFramePosition(modelHandle, weaponAttachFrameNum);
	weaponLocation[1] = MV1GetFramePosition(modelHandle, weaponAttachFrameNum);

	weaponLocation[0] = { weaponLocation[0].x,weaponLocation[0].y,weaponLocation[0].z };
	weaponLocation[1] = { weaponLocation[1].x + tmp.x * 50,weaponLocation[1].y + tmp.y * 50,weaponLocation[1].z + tmp.z * 50 };

	//weaponVector = { -1 * (weaponLocation[1].x - weaponLocation[0].x), -1 * (weaponLocation[1].y - weaponLocation[0].y) ,-1 * (weaponLocation[1].z - weaponLocation[0].z) };
	weaponVector = { (weaponLocation[1].x - weaponLocation[0].x), (weaponLocation[1].y - weaponLocation[0].y) ,(weaponLocation[1].z - weaponLocation[0].z) };
	//weaponVector = { (weaponLocation[0].x - weaponLocation[1].x), (weaponLocation[0].y - weaponLocation[1].y) ,(weaponLocation[0].z - weaponLocation[1].z) };


	//weaponLocation[0].x += tmp.x * 50;
	//weaponLocation[0].y += tmp.y * 50;
	//weaponLocation[0].z += tmp.z * 50;


	/*VECTOR base;
	base = { 10,0 };

	tmp = { weaponLocation[0].x - weaponLocation[1].x,weaponLocation[0].y - weaponLocation[1].y,weaponLocation[0].z - weaponLocation[1].z };*/


}

