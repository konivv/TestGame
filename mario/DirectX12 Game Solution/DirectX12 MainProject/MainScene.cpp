//
// MainScene.cpp
//

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "SceneFactory.h"
#include "DontDestroyOnLoad.h"


// Initialize member variables.
MainScene::MainScene()
{

}

// Initialize a variable and audio resources.
void MainScene::Initialize()
{
    //制御フラグ
    controlFlag = 0;

    //背景
    bgX = 0;
    bgFlag = 0;

    sab_bgZ = 10;

    //プレイヤーX.Y　ジャンプ
    jumpFlag = 0;
    jumpFlag2 = 0;
    jumpPower = 0;

    //プレイヤー余動
    XFlag  = 0.0f;
    XFlag2 = 0.0f;

    XFtime  = 0.0f;
    XFtime2 = 0.0;
    XPower = 0.0f;
    Xspeed = 0.0f;
    PX = 0;


    playerX = 100;
    playerY = 597;
    playerZ = -5;
    playerZ2 = 5;
    playerZ3 = 5;
    playerZ4 = 5;
    playerZ5 = 5;
    playerZ6 = 5;
    /*playerZ7 = 5;
    playerZ8 = 5;*/

    Flag = 0;

    kuriboX = 1280;
    kuriboY = 565;
    kuriboSSR = 0;

    //スコア
    DontDestroy->score = 0;
       

}

// Allocate all memory the Direct3D and Direct2D resources.
void MainScene::LoadAssets()
{
    descriptorHeap = DX12::CreateDescriptorHeap(DXTK->Device, 1);

    ResourceUploadBatch resourceUploadBatch(DXTK->Device);
    resourceUploadBatch.Begin();

    RenderTargetState rtState(DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_FORMAT_D32_FLOAT);
    SpriteBatchPipelineStateDescription pd(rtState, &CommonStates::NonPremultiplied);
    D3D12_VIEWPORT viewport = {
        0.0f, 0.0f, 1280.0f, 720.0f,
        D3D12_MIN_DEPTH, D3D12_MAX_DEPTH
    };

    spriteBatch = DX12::CreateSpriteBatch(DXTK->Device, resourceUploadBatch, pd, &viewport);

    dx9GpuDescriptor = DXTK->Direct3D9->CreateShaderResourceView(descriptorHeap.get(), 0);

    auto uploadResourcesFinished = resourceUploadBatch.End(DXTK->CommandQueue);
    uploadResourcesFinished.wait();

    //背景
    mainbg      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"11.jpg");
    sab_bg      = DX9::Sprite::CreateFromFile(DXTK->Device9, L"炎.png");

    //マリオ画像
    chibimario  = DX9::Sprite::CreateFromFile(DXTK->Device9, L"chibi.png");
    
    bigmario    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"big.png");
    bigmario2    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"big2.png");
    bigmario3    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"big3.png");
    bigmario4    = DX9::Sprite::CreateFromFile(DXTK->Device9, L"big4.png");
    
    firemario   = DX9::Sprite::CreateFromFile(DXTK->Device9, L"fire.png");


    //クリボー読み込み
    kuribo = DX9::Sprite::CreateFromFile(DXTK->Device9, L"kuri1.png");
    

    // グラフィックリソースの初期化処理
}

// Releasing resources required for termination.
void MainScene::Terminate()
{
    DXTK->ResetAudioEngine();
    DXTK->WaitForGpu();

    // TODO: Add your Termination logic here.

}


// Direct3D resource cleanup.
void MainScene::OnDeviceLost()
{

}

// Restart any looped sounds here
void MainScene::OnRestartSound()
{

}

// Updates the scene.
NextScene MainScene::Update(const float deltaTime)
{
    // If you use 'deltaTime', remove it.
    UNREFERENCED_PARAMETER(deltaTime);

    // TODO: Add your game logic here.
                                                    //背景
    //横スクロール

    if (bgFlag == 1) 
        bgX += 4;
    

    if (playerX == 580 && DXTK->KeyState->D) {
        bgFlag = 0;
        bgX += 8;
    }

        if (bgX >= 9606)
            bgX = 9606;
    
                                               //プレイヤー移動
    if (controlFlag == 0) {
        //右移動

        if (DXTK->KeyState->D)
        {
            playerX += 8;
            bgFlag = 1;
            
            
        }
        
        if (!DXTK->KeyState->D)
            bgFlag = 0;

        //左移動
        if (DXTK->KeyState->A)
        {

            playerX -= 8;    
            bgFlag = 0;
        }

        

        //移動制限
        if (playerX >= 580)
            playerX = 580;

        if (playerX <= -20)
            playerX = -20;



        //余動
        /*if (DXTK->KeyEvent->released.D) {
            XFtime = 1;
            Xspeed = 1;
            jumpPower = -20;

        }*/

        /*if (XFtime == 1) {

            XFlag += 1.0f;
            playerX = playerX + 5;

        }

        if (XFlag >= 24.0f) {

            XFlag = 0;
            XFtime = 0;

        }*/

        /*if (Xspeed >= 1) {

            playerX += XPower;
            XPower += 0.5f;


            if (playerX > PX) {
                playerX = PX;
                XPower = 0;
                Xspeed = 0;
            }

        }*/





        //プレイヤージャンプ


//ジャンプ
        if (DXTK->KeyState->Space && jumpFlag == 0) {
            jumpFlag = 1;
            jumpPower = -23;
            /*jump->Play();*/

        }
        if (jumpFlag >= 1) {

            playerY += jumpPower;
            jumpPower += 0.6;


            if (playerY < 130) {
                playerY = 130;
                jumpPower = 0;
            }


            if (DXTK->KeyEvent->released.Space && playerY >= 400) {


                jumpPower += 12;

                if (playerY <= 370) {
                    playerY = 370;
                    jumpPower = 0;
                }

            }
        }

        if (playerY >= 597 && jumpFlag == 1) {

            playerY = 597;
            jumpFlag2 = 0;
            jumpFlag = 0;

        }

        /*if (playerY >= 536 && jumpFlag == 2) {

            playerY = 535;
            jumpFlag2 = 0;
            jumpFlag = 0;

        }*/

                                        //見た目変化
//状態変化

        if (DXTK->KeyEvent->pressed.F) {

            Flag = 1;
            playerZ = 5;

            if (Flag == 1) {



                if (playerZ == 5) {
                    playerZ6 = -5;
                    playerZ = 6;
                }

                if (playerZ6 == -5) {
                        playerZ5 = -5;
                        playerZ6 = 5;
                }

                    if (playerZ5 == -5) {
                        playerZ4 = -5;
                        playerZ5 = 5;
                    }

                    if (playerZ4 == -5) {
                        playerZ2 = -5;
                        playerZ4 = 5;
                        Flag = 0;
                    }

                }
            }
        }

        //クリボープログラム

//クリボー移動
        /*if (kuriboSSR == 0) {

            kuriboX += -4000.0f * deltaTime;
            if (kuriboX <= 30)
                kuriboSSR = 1;
        }

        if (kuriboSSR == 1) {

            kuriboY += -4000.0f * deltaTime;
            if (kuriboY <= 30)
                kuriboSSR = 2;
        }

        if (kuriboSSR == 2) {

            kuriboX += +4000.0f * deltaTime;
            if (kuriboX >= 1200)
                kuriboSSR = 3;
        }

        if (kuriboSSR == 3) {

            kuriboY += +4000.0f * deltaTime;
            if (kuriboY >= 565)
                kuriboSSR = 0;
        }*/

        if (kuriboX <= -64.0f)
            kuriboX += 1280.0f;








            //if (DXTK->KeyEvent->released.Space && jumpFlag == 0) {
            //    jumpFlag = 2;
            //    jumpPower = -30;
            //    /*jump->Play();*/

            //}
            //if (jumpFlag == 2) {

            //    playerY += jumpPower;
            //    jumpPower += 1.5;
            //    if (playerY < 280) {
            //        playerY = 280;
            //        jumpPower = 0;
            //    }
            //}

            //if (playerY >= 535 && jumpFlag == 2) {
            //    playerY = 535,
            //        jumpFlag = 0;
            //}
    
                                              
                                                 //ゴールプログラム

    if (playerX >= 580 && bgX == 9606) {

        controlFlag = 1;
        if (controlFlag == 1 && playerY <= 585)
            playerY += 5;

        if (playerY >= 583)
            controlFlag = 2;

    }

    if (controlFlag == 2)
        playerX += 4;

    if (playerX >= 890) {
        playerZ += 20;
        goalFlag += deltaTime;
    }

    if (playerX >= 1250) 
        return NextScene::gameover;

                                    //スコアプログラム
    
    DontDestroy->score += 20 * deltaTime;



	return NextScene::Continue;
}

// Draws the scene.
void MainScene::Render()
{
    DXTK->Direct3D9->Clear(DX9::Colors::RGBA(0, 0, 0, 255));

    DXTK->Direct3D9->BeginScene();
    DX9::SpriteBatch->Begin();

    //背景
    DX9::SpriteBatch->DrawSimple(mainbg.Get(), SimpleMath::Vector3(0, 0, 0), //背景スクロール
    RectWH(bgX, 0, 1280, 720));

    //背景エフェクト
    
    DX9::SpriteBatch->DrawSimple(sab_bg.Get(), SimpleMath::Vector3(0, 0, sab_bgZ)); //炎

    //マリオ
    DX9::SpriteBatch->DrawSimple(chibimario.Get(), SimpleMath::Vector3(playerX, playerY, playerZ));
    DX9::SpriteBatch->DrawSimple(bigmario.Get(), SimpleMath::Vector3(playerX, playerY, playerZ2));
    DX9::SpriteBatch->DrawSimple(firemario.Get(), SimpleMath::Vector3(playerX, playerY, playerZ3));
    DX9::SpriteBatch->DrawSimple(bigmario2.Get(), SimpleMath::Vector3(playerX, playerY, playerZ4));
    DX9::SpriteBatch->DrawSimple(bigmario3.Get(), SimpleMath::Vector3(playerX, playerY, playerZ5));
    DX9::SpriteBatch->DrawSimple(bigmario4.Get(), SimpleMath::Vector3(playerX, playerY, playerZ6));
  /*  DX9::SpriteBatch->DrawSimple(bigmario.Get(), SimpleMath::Vector3(playerX, playerY, playerZ7));*/

                                                                      //1280設定
    DX9::SpriteBatch->DrawSimple(kuribo.Get(), SimpleMath::Vector3(kuriboX, kuriboY, -5));
    if(kuriboX < 0)
        DX9::SpriteBatch->DrawSimple(kuribo.Get(), SimpleMath::Vector3(1280.0f + kuriboX, kuriboY, -5));
    
    
    DX9::SpriteBatch->End();
    DXTK->Direct3D9->EndScene();

    DXTK->Direct3D9->UpdateResource();

	// TODO: Add your rendering code here.
	DXTK->ResetCommand();
	DXTK->ClearRenderTarget(Colors::CornflowerBlue);

    const auto heapes = descriptorHeap->Heap();
    DXTK->CommandList->SetDescriptorHeaps(1, &heapes);

    spriteBatch->Begin(DXTK->CommandList);
    spriteBatch->Draw(
        dx9GpuDescriptor,
        XMUINT2(1280, 720),
        SimpleMath::Vector2(0.0f, 0.0f)
    );
    spriteBatch->End();

    DXTK->Direct3D9->WaitUpdate();

	DXTK->ExecuteCommandList();
}
