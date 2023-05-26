#include "MyDebug.h"

/// <summary>
/// ベクトルの情報を書き出す関数
/// </summary>
/// <param name="x">描画開始地点のx座標</param>
/// <param name="y">描画開始地点のy座標</param>
/// <param name="vector">描画するベクトル</param>
/// <param name="label">名前</param>
void MyDebug::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x); // x
	Novice::ScreenPrintf(x + kColumWidth, y, "%0.2f", vector.y); // y
	Novice::ScreenPrintf(x + kColumWidth * 2, y, "%0.2f", vector.z); // z
	Novice::ScreenPrintf(x + kColumWidth * 3, y, "%s", label);

}

/// <summary>
/// グリッドを描画する関数
/// </summary>
/// <param name="viewProjectionMatrix">射影行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
void MyDebug::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	const float kGridHalfWidth = 2.0f; // グリッドの半分の幅
	const uint32_t kSubdivision = 10; // 分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // 1つ分の長さ

	// <para>返還前のワールド座標<para>
	// 0 ... 始点　1 ... 終点
	Vector3 worldVertex[2];
	// <para>返還後のワールド座標<para>
	// 0 ... 始点　1 ... 終点
	Vector3 screenVertex[2];

	// 奥から手前に線を引いて行く
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {

		// 上記の除法を使ってワールド座標系の始点、終点を求める
		worldVertex[0] = { (float)xIndex * kGridEvery - kGridHalfWidth, 0.0f, -kGridHalfWidth };
		worldVertex[1] = { (float)xIndex * kGridEvery - kGridHalfWidth, 0.0f, kGridHalfWidth };
		// スクリーン座標系に変換
		// 始点
		screenVertex[0] = MyMath::Transform(worldVertex[0], viewProjectionMatrix);
		screenVertex[0] = MyMath::Transform(screenVertex[0], viewportMatrix);
		// 終点
		screenVertex[1] = MyMath::Transform(worldVertex[1], viewProjectionMatrix);
		screenVertex[1] = MyMath::Transform(screenVertex[1], viewportMatrix);

		// 変換した座標を使用して描画する
		Novice::DrawLine((int)screenVertex[0].x, (int)screenVertex[0].y, (int)screenVertex[1].x, (int)screenVertex[1].y, 0xAAAAAAFF);

	}

	// 奥から手前に線を引いて行く
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++) {

		// 上記の除法を使ってワールド座標系の始点、終点を求める
		worldVertex[0] = { -kGridHalfWidth, 0.0f,  (float)zIndex * kGridEvery - kGridHalfWidth };
		worldVertex[1] = { kGridHalfWidth, 0.0f, (float)zIndex * kGridEvery - kGridHalfWidth };
		// スクリーン座標系に変換
		// 始点
		screenVertex[0] = MyMath::Transform(worldVertex[0], viewProjectionMatrix);
		screenVertex[0] = MyMath::Transform(screenVertex[0], viewportMatrix);
		// 終点
		screenVertex[1] = MyMath::Transform(worldVertex[1], viewProjectionMatrix);
		screenVertex[1] = MyMath::Transform(screenVertex[1], viewportMatrix);

		// 変換した座標を使用して描画する
		Novice::DrawLine((int)screenVertex[0].x, (int)screenVertex[0].y, (int)screenVertex[1].x, (int)screenVertex[1].y, 0xAAAAAAFF);

	}

}

/// <summary>
/// 球を描画する関数
/// </summary>
/// <param name="sphere">球構造体</param>
/// <param name="viewProjectionMatrix">射影行列</param>
/// <param name="viewPortMatrix">ビューポート行列</param>
/// <param name="color">球の色</param>
void MyDebug::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {

	const uint32_t kSubdivison = 30;
	const float kLonEvery = 2.0f * float(std::numbers::pi) / float(kSubdivison);
	const float kLatEvery = float(std::numbers::pi) / float(kSubdivison);

	// 緯度の方向に分割
	for (uint32_t latIndex = 0; latIndex < kSubdivison; latIndex++) {
		float lat = float(-std::numbers::pi) / 2.0f + kLatEvery * latIndex;
		// 軽度の方向に分割
		for (uint32_t lonIndex = 0; lonIndex < kSubdivison; lonIndex++) {
			float lon = lonIndex * kLonEvery;

			// ワールド座標系でのa, b, cを求める
			Vector3 a, b, c;
			a = { sphere.radius * std::cosf(lat) * std::cosf(lon),sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon) };
			a = MyMath::Add(a, sphere.center);
			b = { sphere.radius * std::cosf(lat + kLatEvery) * std::cosf(lon), sphere.radius * std::sinf(lat + kLatEvery), sphere.radius * std::cosf(lat + kLatEvery) * std::sinf(lon) };
			b = MyMath::Add(b, sphere.center);
			c = { sphere.radius * std::cosf(lat) * cosf(lon + kLonEvery), sphere.radius * std::sinf(lat), sphere.radius * std::cosf(lat) * std::sinf(lon + kLonEvery) };
			c = MyMath::Add(c, sphere.center);

			// a, b, c をスクリーン座標系に変換
			a = MyMath::Transform(a, viewProjectionMatrix);
			a = MyMath::Transform(a, viewPortMatrix);
			b = MyMath::Transform(b, viewProjectionMatrix);
			b = MyMath::Transform(b, viewPortMatrix);
			c = MyMath::Transform(c, viewProjectionMatrix);
			c = MyMath::Transform(c, viewPortMatrix);

			// 線を引く
			Novice::DrawLine(int(a.x), int(a.y), int(b.x), int(b.y), color);
			Novice::DrawLine(int(a.x), int(a.y), int(c.x), int(c.y), color);

		}
	}

}

