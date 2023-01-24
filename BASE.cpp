#include "DxLib.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <bitset>

using namespace std;

/*
int main() {
    int Han[100] = { 0 };
    for (int i = 0; i <= 25; i++) {
        if (i < 10) {
            cout << "画像/キャラクタ0""<<i<<"".png" << endl;
            //Han[i] = LoadGraph("画像/キャラクタ0""<<i<<"".png");
        }
        else {
            //Han[i] = LoadGraph("画像/キャラクタ""<<i<<"".png");
        }
    }

}
*/
int Key[256]; // キーが押されているフレーム数を格納する

int gpUpdateKey() {
    char tmpKey[256]; // 現在のキーの入力状態を格納する
    GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
            Key[i]++;     // 加算
        }
        else {              // 押されていなければ
            Key[i] = 0;   // 0にする
        }
    }
    return 0;
}
typedef struct MenuElement_t{
    int x, y;       // 座標格納用変数
    char name[128]; // 項目名格納用変数
    int avg[128];
    MenuElement_t* next;
}/*/MenuElement_t*/;
typedef struct Baseball {
    char strike_ball[128];
    char ball[128];
};

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
    ChangeWindowMode(TRUE); // ウィンドウモードに設定
    DxLib_Init();   // DXライブラリ初期化処理
    //LoadGraphScreen(50, 100, "画像/キャラクタ00.png", TRUE);
    MenuElement_t MenuElement[5] = {
                {  80, 100, "近本 5", }, // タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が
                { 100, 150, "糸原 33" ,},
                { 100, 200, "マルテ 31", },
                { 100, 250, "大山 3",},
                { 100, 300, "サンズ 52" },
    };
    int strike, ball, out;
    strike = ball = out = 0;
    int SelectNum = 0;
    Baseball St;
    int score =0 ;
    int N = 0;
    srand((unsigned)time(NULL));
    bitset<8> Hantei("11110000");
    bitset<8> Init("00000001");
    bitset<8> s = 1/*("00000001")*/;
    bitset<8> S = 0;
    int RAN,RAN1;
    RAN = RAN1 = 0;
    int Ining;
    Ining = 1;
    int Handle,kona;
    int Base = 0;
    Handle = 0;
    kona = 0;
    Base  =LoadGraph("画像/RosaRosa.jpg");;
    Handle = LoadSoundMem("サウンド/1up.wav");
    //IN[0] = 0;
    //Baseball ball[3];
    /*
    while(1){
        PlaySoundMem(kona, DX_PLAYTYPE_BACK);*/
        while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && gpUpdateKey() == 0 && Ining < 10) {
            // 計算フェーズ 
            // 
            //if (Key[KEY_INPUT_S] == 1 && strike < 3) {

            if (/*Key[KEY_INPUT_DOWN] == 1 || out == 1*//*strike == 3 &&*/Key[KEY_INPUT_H] == 1) { // 下キーが押された瞬間だけ処理
                RAN = (rand() % 3) * 20;
                RAN1 = (rand() % 3) * 20;
                if (strike < 3) {
                    N = rand() % 6;//空振り ,凡打,一塁打、二塁打、三塁打、本塁打
                    if (N == 0) {
                        //DrawFormatString(250, 200, GetColor(255, 255, 255), "空振り");
                        strike++;
                    }
                    else if (N == 1) {
                        strike = 0;
                        ball = 0;
                        //DrawFormatString(250, 200, GetColor(255, 255, 255), "ボール");
                        out++;
                        PlaySoundMem(Handle, DX_PLAYTYPE_BACK);
                        if (out == 3) {
                            Ining += 1;
                            out = 0;
                        }
                    }
                    else if (N == 2) {
                        strike = 0;
                        ball = 0;
                        //DrawFormatString(250, 200, GetColor(255, 255, 255), "ヒット");
                        S = (s << 1);
                    }
                    else if (N == 3) {
                        strike = 0;
                        ball = 0;
                        //DrawFormatString(250, 200, GetColor(255, 255, 255), "ツーベース");
                        S = (s << 2);
                    }
                    else if (N == 4) {
                        strike = 0;
                        ball = 0;
                        //DrawFormatString(250, 200, GetColor(255, 255, 255), "スリーベース");
                        S = (s << 3);
                    }
                    else {
                        strike = 0;
                        ball = 0;
                        //DrawFormatString(250, 200, GetColor(255, 255, 255), "ホームラン");
                        S = (s << 4);
                    }
                }
                else if (strike == 3) {
                    out++;
                }
                if (Key[KEY_INPUT_B] == 1 && ball < 4) {
                    ball++;
                }
                else if (ball == 4) {
                    out++;
                }

                if (N != 0) {
                    SelectNum = (SelectNum + 1) % 5; // 現在の選択項目を一つ下にずらす(ループする)
                }
                else {
                    //strike = ball = 0;
                }

                for (int i = 0; i < 5; i++) {              // メニュー項目数である5個ループ処理
                    if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
                        MenuElement[i].x = 80; // 座標を80にする
                    }
                    else {                       // 今処理しているのが、選択番号以外なら
                        MenuElement[i].x = 100;// 座標を100にする
                    }
                }
                auto c = Init | S;
                s = c;
                auto P = Hantei & s;
                s.reset(7);
                s.reset(6);
                s.reset(5);
                s.reset(4);
                score += P.count();


                //DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255));
            }

            else if (Key[KEY_INPUT_Q] == 1) {
                break;
            }


            if (strike == 3) {
                //strike = 0;
            }
            else if (ball == 4) {
                //ball = 0;
            }

            // 描画フェーズ

            for (int i = 0; i < 5; i++) { // メニュー項目を描画
                if (strike < 3) {
                    DrawFormatString(MenuElement[SelectNum].x + 100, MenuElement[SelectNum].y, GetColor(255, 255, 255), "strike:%d", strike);
                    DrawFormatString(MenuElement[SelectNum].x + 200, MenuElement[SelectNum].y, GetColor(255, 255, 255), "ball:%d", ball);
                    DrawFormatString(MenuElement[SelectNum].x + 300, MenuElement[SelectNum].y, GetColor(255, 255, 255), "out:%d", out);
                    DrawFormatString(400, 50, GetColor(255, 255, 255), "%d回", Ining);
                }
                DrawGraph(500, 100, Base, TRUE);
                //DrawFormatString(500, 300, GetColor(255, 255, 255), "*");
                if (N == 0 && strike != 0) {
                    DrawFormatString(500 + RAN1, 200 + RAN, GetColor(255, 255, 255), "*");
                    DrawFormatString(250, 10, GetColor(255, 255, 255), "空振り");
                }
                else if (N == 1) {
                    DrawFormatString(250, 10, GetColor(255, 255, 255), "ボール");
                }
                else if (N == 2) {
                    DrawFormatString(250, 10, GetColor(255, 255, 255), "ヒット");
                }
                else if (N == 3) {
                    DrawFormatString(250, 10, GetColor(255, 255, 255), "ツーベース");
                }
                else if (N == 4) {
                    DrawFormatString(250, 10, GetColor(255, 255, 255), "スリーベース");
                }
                else if (N == 5) {
                    DrawFormatString(250, 10, GetColor(255, 255, 255), "ホームラン");
                }
                DrawFormatString(250, 400, GetColor(255, 255, 255), "得点%d", score);
                DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255), MenuElement[i].name);
                if (s.to_ullong() == 1) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "ランナーなし");
                }
                else if (s.to_ullong() == 3) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "1塁");
                }
                else if (s.to_ullong() == 5) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "2塁");
                }
                else if (s.to_ullong() == 7) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "1,2塁");
                }
                else if (s.to_ullong() == 9) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "3塁");
                }
                else if (s.to_ullong() == 11) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "1,3塁");
                }
                else if (s.to_ullong() == 13) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "2,3塁");
                }
                else if (s.to_ullong() == 15) {
                    DrawFormatString(400, 400, GetColor(255, 255, 255), "満塁");
                }
                //DrawFormatString(MenuElement[i].x, MenuElement[i].y, GetColor(255, 255, 255));
            }
        //}
        /*
        auto c = Init | S;
        s = c;
        auto P = Hantei & s;
        s.reset(7);
        s.reset(6);
        s.reset(5);
        s.reset(4);
        */
        

        //cout << "binary" << s << endl;
        //cout << "10進数" << s.to_ullong() << endl;

    }
    int Han[24] = { 0 };
    //LoadDivGraph("画像/Matsui.jpg", 26, 4, 6, 230, 383, Han);//画像を16個に分割してImage配列に保存
    //SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

    for (int i = 0; i <= 25; i++) {
        
    }
    //int Handle, Count = 0;
    //Handle = LoadSoundMem("サウンド/We_Are_The_Champions.mp3"); // サウンド/1up.wavをロードし、識別番号をHandleに格納

    // while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
    /*
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
        
        if (Count % 12000 == 0) { // 2秒に一度
            PlaySoundMem(Handle, DX_PLAYTYPE_BACK); // 効果音を再生する
        }
        else if (Count > 13000) {
            break;
        }
        Count++;

    }*/
    //DrawGraph(50, 100, Han, TRUE);
    int I = 0;
    /*
    while (1) {
        ProcessMessage();
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
            break;
        }
        ClearDrawScreen();
        DrawGraph(50, 100, Han[I], TRUE);
        if (I < 24) {
            I++;
        }
    }*/
    //WaitKey();      // キー入力待ち
    DxLib_End();    // DXライブラリ終了処理
    return 0;

}

/*
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

        int Handle, Count=0;
        Handle = LoadSoundMem("サウンド/1up.wav"); // サウンド/1up.wavをロードし、識別番号をHandleに格納

        // while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

                if( Count % 120 == 0 ){ // 2秒に一度
                        PlaySoundMem( Handle, DX_PLAYTYPE_BACK ); // 効果音を再生する
                }

                Count++;

        }

        DxLib_End(); // DXライブラリ終了処理
        return 0;
} 
 */
 