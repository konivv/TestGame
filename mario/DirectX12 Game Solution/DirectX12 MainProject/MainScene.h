//
// MainScene.h
//

#pragma once

#include "Scene.h"
#include "DontDestroyOnLoad.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class MainScene final : public Scene {
public:
	MainScene();
	virtual ~MainScene() { Terminate(); }

	MainScene(MainScene&&) = default;
	MainScene& operator= (MainScene&&) = default;

	MainScene(MainScene const&) = delete;
	MainScene& operator= (MainScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

    private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;


	
	
	
	//制御フラグ
	int controlFlag;


	//背景　ステージ
	DX9::SPRITE mainbg;
	DX9::SPRITE sab_bg;
	int bgX;
	int bgFlag;

	int sab_bgZ;


	//ジャンプ
	int jumpFlag;
	int jumpFlag2;
	float jumpPower;
	int Flag;

	//マリオ
	DX9::SPRITE chibimario;
	DX9::SPRITE bigmario;
	DX9::SPRITE bigmario2;
	DX9::SPRITE bigmario3;
	DX9::SPRITE bigmario4;
	//移動
	int playerX;
	int playerY;

	float XFlag;
	float XFlag2;
	float XFtime;
	float XFtime2;
	float Xspeed;
	float XPower;
	int PX;

	//マリオアニメーションレトロ
	int playerZ;
	int playerZ2;
	int playerZ3;
	int playerZ4;
	int playerZ5;
	int playerZ6;
	int playerZ7;

	//ファイアーマリオ
	DX9::SPRITE firemario;



	//クリボー
	DX9::SPRITE kuribo;
	//移動
	float kuriboX;
	float kuriboY;
	int kuriboSSR;

	//ゴールフラグ
	int goalFlag;


};