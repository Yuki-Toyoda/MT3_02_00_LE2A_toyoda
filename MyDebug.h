#pragma once
#include <Novice.h>
#include "MyMath.h"
#include "MyConst.h"

/// <summary>
/// デバック系関数のクラス
/// </summary>
class MyDebug
{

public:

	/// <summary>
	/// ベクトルの情報を書き出す関数
	/// </summary>
	/// <param name="x">描画開始地点のx座標</param>
	/// <param name="y">描画開始地点のy座標</param>
	/// <param name="vector">描画するベクトル</param>
	/// <param name="label">名前</param>
	static void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	/// <summary>
	/// グリッドを描画する関数
	/// </summary>
	/// <param name="viewProjectionMatrix">射影行列</param>
	/// <param name="viewportMatrix">ビューポート行列</param>
	static void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

	/// <summary>
	/// 球を描画する関数
	/// </summary>
	/// <param name="sphere">球構造体</param>
	/// <param name="viewProjectionMatrix">射影行列</param>
	/// <param name="viewPortMatrix">ビューポート行列</param>
	/// <param name="color">球の色</param>
	static void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color);

};

