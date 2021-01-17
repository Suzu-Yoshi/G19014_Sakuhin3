/*--+----1----+----2----+----3----+----4----+----5-----+----6----+----7----+----8----+----9----+---*/
//音楽の再生
//プロジェクト直下にMUSICフォルダを作成
//再生したい音楽ファイルを、MUSICフォルダに入れる

//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "resource.h"

//########## マクロ定義 ##########
#define GAME_WIDTH			800	//画面の横の大きさ
#define GAME_HEIGHT			600	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"比べ"	//ウィンドウのタイトル

#define GAME_FPS			60	//FPSの数値	

//マウスのボタン
#define MOUSE_BUTTON_CODE	129		//0x0000〜0x0080まで

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで

//フォント
#define FONT_TANU_PATH			TEXT(".\\FONT\\azukiP.ttf")	//フォントの場所
#define FONT_TANU_NAME			TEXT("あずきフォントP")			//フォントの名前


//エラーメッセージ
#define FONT_INSTALL_ERR_TITLE	TEXT("フォントインストールエラー")
#define FONT_CREATE_ERR_TITLE	TEXT("フォント作成エラー")

//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//画像のパス================================================================================
#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\play.png")	       //プレイ背景の画像
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\player\\player1.png")	   //プレイヤー1の画像(カーソル）
#define IMAGE_PLAYER2_PATH      TEXT(".\\IMAGE\\player\\player2.png")      //プレイヤー２の画像（キャラクタ）
//#define IMAGE_PLAYER2_PATH      TEXT(".\\IMAGE\\play")
#define IMAGE_TITLE_PATH        TEXT(".\\IMAGE\\title.png")        //タイトルの背景
#define IMAGE_CHOICE_PATH       TEXT(".\\IMAGE\\choice.png")       //選択画面の背景
//#define IMAGE_PLAY_PATH         TEXT(".\\IMAGE\\play.png")         //プレイの背景
#define IMAGE_RUSULT_PATH       TEXT(".\\IMAGE\\rusult.png")       //リザルト背景
#define IMAGE_END_PATH          TEXT(".\\IMAGE\\end.png")          //エンド背景

//エラーメッセージ
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

//音楽のパス================================================================================
#define MUSIC_BGM_PATH			     TEXT(".\\MUSIC\\play.mp3")                 	//プレイBGM
#define MUSIC_PLAYER_SHOT_PATH	     TEXT(".\\MUSIC\\ショット音.mp3")				//ショット音
#define MUSIC_RUEULT_BGM_PATH        TEXT(".\\MUSIC\\rusult.mp3")               //リザルト画面のBGM
#define MUSIC_TITLE_BGM_PATH         TEXT(".\\MUSIC\\title.mp3")                    //タイトルBGM
#define MUSIC_CHOICE_BGM_PATH        TEXT(".\\MUSIC\\choice.mp3")                   //選択BGM
#define MUSIC_END_BGM_PATH           TEXT(".\\MUSIC\\end.mp3")                      //エンドBGM

//===========================================================================================

//マップ=====================================================================================
#define GAME_MAP_TATE_MAX	10	//マップの縦の数
#define GAME_MAP_YOKO_MAX	13	//マップの横の数
#define GAME_MAP_KIND_MAX	2	//マップの種類の数

#define GAME_MAP_PATH			TEXT(".\\IMAGE\\MAP\\map1.png")		//マップの画像

#define MAP_DIV_WIDTH		64	//画像を分割する幅サイズ
#define MAP_DIV_HEIGHT		64	//画像を分割する高さサイズ
#define MAP_DIV_TATE		10	//画像を縦に分割する数
#define MAP_DIV_YOKO		4	//画像を横に分割する数
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//画像を分割する総数

//弾の設定----------------------------------------------------△
#define TAMA_CHANGE_MAX      5  //5フレーム目で弾の画像を変える
#define TAMA_MAX            16  //最大16発まで

#define TAMA_RED_PATH       TEXT(".\\IMAGE\\TAMA\\red.png")  //赤弾の画像

#define TAMA_DIV_WIDTH      16  //画像を分割する幅サイズ
#define TAMA_DIV_HEIGHT     16  //画像を分割する高さサイズ

#define TAMA_DIV_TATE        3  //画像を縦に分割する数
#define TAMA_DIV_YOKO        1  //画像を横に分割する数

#define TAMA_DIV_NUM     TAMA_DIV_TATE*TAMA_DIV_YOKO  //画像を分割する総数
//----------------------------------------------------------△

//エラーメッセージ
#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

//終了ダイアログ用---------------------------------------

#define MOUSE_ERR_CLICK_TITLE     TEXT("スタート位置エラー")
#define MOUSE_ERR_CLICK_CAPTION   TEXT("スタート位置が決まっていません")


//終了ダイアログ用----------△
#define MOUSE_R_CLICK_TITLE       TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION     TEXT("ゲームを中断し、タイトル画面に戻りますか？")
//-------------------------------------------------------△

enum GAME_MAP_KIND
{
	n = -1,
	k = 0,//ブロック
	y = 1,//床
	t = 9,//空白
	s = 5,//スタート
	g = 9,//ゴール

};//マップの種類
//===========================================================================================

enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_CHOICE,
	GAME_SCENE_PLAY,
	GAME_SCENE_RUSULT,
	GAME_SCENE_END,
};	//ゲームのシーン

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//キャラクターのスピード


enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//キャラクターのリロード


//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;	//座標を初期化
	int y = -1;	//座標を初期化
}iPOINT;

//マウス構造体
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInputの値を入れる
	int WheelValue = 0;	//マウスホイールの回転量(奥はプラス値 / 手前はマイナス値)
	iPOINT Point;		//マウスの座標が入る
	iPOINT OldPoint;	//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力が入る
}MOUSE;

//フォント構造体
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ
	//※タイプは、https://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N10　を参照

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}IMAGE;	//画像構造体


typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
}MUSIC;	//音楽構造体

//弾--------------△
typedef struct STRUCT_TAMA
{
	char path[PATH_MAX];
	int handle[TAMA_DIV_NUM];
	int x;
	int y;
	int width;
	int height;
	BOOL IsDraw;
	int nowImageKind;
	int changeImageCnt;
	int changeImageCntMAX;
	int speed;
}TAMA;//弾の構造体
//-----------------△

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;				//中心X
	int CenterY;				//中心Y


	MUSIC musicShot;			//プレイヤーの発射音

	BOOL CanShot;				//ショットできるか
	int ShotReLoadCnt;			//ショットリロード時間
	int ShotReLoadCntMAX;		//ショットリロード時間(MAX)

	TAMA tama[TAMA_MAX];         //ショットする弾
	//追加------------------------------------△
	RECT coll;                   //当たり判定
	iPOINT collBeforePt;         //当たる前の座標
	//-----------------------------------------△
	//
}CHARA;	//キャラクター構造体

//マップパス
typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];				//パス
	int handle[MAP_DIV_NUM];			//分割したの弾の画像ハンドルを取得
	int kind[MAP_DIV_NUM];				//マップの種類
	int width;							//幅
	int height;							//高さ
}MAPCHIP;	//MAP_IMAGE構造体

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//マップの種類
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}MAP;	//MAP構造体
//=============================================================================

//########## グローバル変数 ##########
//FPS関連
int StartTimeFps;				//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均を取るサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { '\0' };			//すべてのキーの状態が入る
char OldAllKeyState[256] = { '\0' };	//すべてのキーの状態(直前)が入る

//マウスの座標を取得
MOUSE mouse;

FONT FontTanu32;	//たぬき油性マジック：大きさ32　のフォント構造体

int GameScene;		//ゲームシーンを管理

//画像関連===================================================================
IMAGE ImageBack;	//ゲームの背景
IMAGE ImageTitle;   //タイトル背景
IMAGE ImageChoice;  //選択画面の背景

IMAGE ImagePlay;    //プレイ画面の背景
IMAGE ImageRusult;  //リザルト背景
IMAGE ImageEnd;     //エンド背景
CHARA player2;      //キャラの画像
CHARA player;		//カーソルの画像

//=============================================================================



//音楽関連 パス用=================================
MUSIC BGM;			//ゲームのBGM

MUSIC BGM_TITLE;    //タイトルのBGM
MUSIC BGM_CHOICE;   //選択画面のBGM
MUSIC BGM_PLAY;     //プレイ画面のBGM
MUSIC BGM_RUSULT;   //リザルト画面のBGM
MUSIC BGM_END;      //エンド画面のBGM

//================================================

//マップの配置--------------------------------------
GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,
		t,t,t,t,t,t,t,t,t,t,t,t,t,	// 0
		t,t,t,t,t,t,t,t,t,t,t,t,t,	// 1
		t,t,t,t,t,t,t,t,t,t,t,t,t,	// 2
		t,t,t,t,t,t,t,t,t,t,t,t,t,	// 3
		t,t,t,t,t,t,t,t,t,t,t,t,t,	// 4
		t,t,t,t,t,t,t,t,t,t,t,t,t,	// 5
		t,t,s,t,t,t,t,t,t,t,t,t,t,	// 6
		y,y,y,y,y,y,y,y,y,y,y,y,y,	// 7
		k,k,k,k,k,k,k,k,k,k,k,k,k,	// 8
		k,k,k,k,k,k,k,k,k,k,k,k,k,  // 9
};	//ゲームのマップ

//ゲームマップの初期化
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//マップチップの画像を管理
MAPCHIP mapChip;

//マップの場所を管理
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//スタートの位置
iPOINT startPt{ -1,-1 };

//マップの当たり判定--------------△
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];
//----------------------------------△
//=======================================================================

//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

VOID MY_MOUSE_UPDATE(VOID);			//マウスの入力情報を更新する
BOOL MY_MOUSE_DOWN(int);			//ボタンを押しているか、マウスコードで判断する
BOOL MY_MOUSE_UP(int);				//ボタンを押し上げたか、マウスコードで判断する
BOOL MY_MOUSEDOWN_KEEP(int, int);	//ボタンを押し続けているか、マウスコードで判断する

BOOL MY_FONT_INSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);			//フォントを作成する
VOID MY_FONT_DELETE(VOID);			//フォントを削除する

VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_CHOICE(VOID);       //選択画面
VOID MY_CHOICE_PROC(VOID);  //選択画面の処理
VOID MY_CHOICE_DRAW(VOID);  //選択画面の描画

VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_RUSULT(VOID);       //リザルト画面
VOID MY_RUSULT_PROC(VOID);  //リザルト画面の処理
VOID MY_RUSULT_DRAW(VOID);  //リザルト画面の描画

VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);		//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);		//画像をまとめて削除する関数


BOOL MY_LOAD_MUSIC(VOID);		//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);		//音楽をまとめて削除する関数

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT); //マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT, RECT);  //領域の当たり判定をする関数

//キャラクター座標------------------------------------------
int kx = 200, ky = 240;
//グラフィックハンドル格納用配列


//---------------------------------------------------
//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
	SetWindowIconID(IDI_ICON1);							//アイコンファイルを読込

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }


	//音楽を読み込む
	if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//プレイヤーの設定
	player.CanShot = TRUE;
	player.ShotReLoadCnt = 0;
	player.ShotReLoadCntMAX = CHARA_RELOAD_LOW;


	//フォントを一時的にインストール
	if (MY_FONT_INSTALL_ONCE() == FALSE) { return -1; }
	//フォントハンドルを作成
	if (MY_FONT_CREATE() == FALSE) { return -1; }

	SetMouseDispFlag(TRUE);			//マウスカーソルを表示


	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画

	//プレイヤーの最初の位置を、スタート位置にする=================
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//スタート位置を探す
			if (mapData[tate][yoko] == s)
			{
				//スタート位置を計算
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//中心X座標を取得
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//中心Y座標を取得
				break;
			}
		}
		//スタートが決まっていれば、ループ終了
		if (startPt.x != -1 && startPt.y != -1) { break; }
	}

	//スタートが決まっていなければ
	if (startPt.x == -1 && startPt.y == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}
	//========================================================================

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_MOUSE_UPDATE();						//マウスの状態を取得

		MY_FPS_UPDATE();	//FPSの処理[更新]

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_CHOICE:
			MY_CHOICE();//選択画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_RUSULT:
			MY_RUSULT();//リザルト画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	//フォントハンドルを破棄
	MY_FONT_DELETE();

	//一時的にインストールしたフォントをアンインストール
	MY_FONT_UNINSTALL_ONCE();

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();


	//音楽ハンドルを破棄
	MY_DELETE_MUSIC();


	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{

	char TempKey[256];	//一時的に、現在のキーの入力状態を格納する

	//直前のキー入力をとっておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
//引　数：int：キーを押し続ける時間
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//マウスの入力情報を更新する
VOID MY_MOUSE_UPDATE(VOID)
{
	//マウスの以前の座標を取得
	mouse.OldPoint = mouse.Point;

	//マウスの以前のボタン入力を取得
	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	//マウスの座標を取得
	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	//マウスの押しているボタンを取得
	mouse.InputValue = GetMouseInput();

	//左ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }		//押していない

	//中ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }	//押している
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }	//押していない

	//右ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }	//押していない

	//ホイールの回転量を取得
	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

//ボタンを押しているか、マウスーコードで判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	//マウスコードのボタンを押している時
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;	//ボタンを押している
	}
	else
	{
		return FALSE;	//ボタンを押していない
	}
}

//ボタンを押し上げたか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1	//直前は押していて
		&& mouse.Button[MOUSE_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//ボタンを押し上げている
	}
	else
	{
		return FALSE;	//ボタンを押し上げていない
	}
}

//ボタンを押し続けているか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
//引　数：int：ボタンを押し続ける時間
BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//フォントをこのソフト用に、一時的にインストール
BOOL MY_FONT_INSTALL_ONCE(VOID)
{
	//フォントを一時的に読み込み(WinAPI)
	if (AddFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//フォントをこのソフト用に、一時的にアンインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID)
{
	//一時的に読み込んだフォントを削除(WinAPI)
	RemoveFontResourceEx(FONT_TANU_PATH, FR_PRIVATE, NULL);

	return;
}

//フォントを読み込む関数
//引　数：const char *：読み込むフォントの名前
//引　数：int　：フォントの大きさ
//引　数：int　：フォントの太さ
//引　数：int　：フォントのタイプ
//戻り値：なし→変更→戻り値：BOOL：エラー時：FALSE
BOOL MY_FONT_CREATE(VOID)
{
	//↓↓↓たぬき油性マジックのフォントを作成↓↓↓

	//フォントデータを作成
	strcpy_s(FontTanu32.path, sizeof(FontTanu32.path), FONT_TANU_PATH);	//パスをコピー
	strcpy_s(FontTanu32.name, sizeof(FontTanu32.name), FONT_TANU_NAME);	//フォント名をコピー
	FontTanu32.handle = -1;								//ハンドルを初期化
	FontTanu32.size = 32;								//サイズは32
	FontTanu32.bold = 1;								//太さ1
	FontTanu32.type = DX_FONTTYPE_ANTIALIASING_EDGE;	//アンチエイリアシング付きのフォント

	//フォントハンドル作成
	FontTanu32.handle = CreateFontToHandle(FontTanu32.name, FontTanu32.size, FontTanu32.bold, FontTanu32.type);
	//フォントハンドル作成できないとき、エラー
	if (FontTanu32.handle == -1) { MessageBox(GetMainWindowHandle(), FONT_TANU_NAME, FONT_CREATE_ERR_TITLE, MB_OK); return FALSE; }

	//↑↑↑たぬき油性マジックのフォントを作成↑↑↑

	return TRUE;
}

//フォントを削除する関数
VOID MY_FONT_DELETE(VOID)
{
	//フォントデータを削除
	DeleteFontToHandle(FontTanu32.handle);	//フォントのハンドルを削除

	return;
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);		//マウスカーソルを表示


		GameScene = GAME_SCENE_CHOICE;

		return;
	}

	//BGMが流れていないなら
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);	//50%の音量にする

		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	return;
}


//スタート画面の描画
VOID MY_START_DRAW(VOID)
{

	//背景を描画する
	DrawGraph(ImageTitle.x, ImageTitle.y, ImageTitle.handle, TRUE);

	DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//選択画面
VOID MY_CHOICE(VOID)
{
	MY_CHOICE_PROC();
	MY_CHOICE_DRAW();

	return;
}

//選択画面の処理
VOID MY_CHOICE_PROC(VOID)
{

	//Gを押したら、プレイシーンへ移動する
	if (CheckHitKey(KEY_INPUT_G) != 0)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM_CHOICE.handle) != 0)
		{
			StopSoundMem(BGM_CHOICE.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);		//マウスカーソルを表示

		GameScene = GAME_SCENE_PLAY;
		return;
	}

	//BGMが流れていないなら
	if (CheckSoundMem(BGM_CHOICE.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_CHOICE.handle);	//50%の音量にする

		PlaySoundMem(BGM_CHOICE.handle, DX_PLAYTYPE_LOOP);
	}

	//プレイヤーの当たる以前の位置を設定する--△
	player.collBeforePt.x = player.CenterX;
	player.collBeforePt.y = player.CenterY;
	//-----------------------------------------△



	return;
}
//選択画面の描画
VOID MY_CHOICE_DRAW(VOID)
{
	//背景を描画する
	DrawGraph(ImageChoice.x, ImageChoice.y, ImageChoice.handle, TRUE);

	DrawString(0, 0, "選択画面(Gを押して下さい)", GetColor(255, 255, 255));
	return;
	return;
}


//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}


//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{
	//スペースキーを押したら、エンドシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_SPACE) == TRUE)
	{

		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);		//マウスカーソルを表示


		GameScene = GAME_SCENE_RUSULT;

		return;	//強制的にエンド画面に飛ぶ

	}


	//BGMが流れていないなら
	if (CheckSoundMem(BGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);	//50%の音量にする

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//マウスを右クリックすると、タイトル画面に戻る--△
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//クリックした座標を取得しておく
		iPOINT R_ClickPt = mouse.Point;

		//マウスを表示
		SetMouseDispFlag(TRUE);

		//終了ダイアログを表示
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YESなら、ゲームを中断する
		{
			//強制的にタイトル画面に飛ぶ
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NOなら、ゲームを続行する
		{
			//マウスの位置を、クリックする前に戻す
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//マウスを非表示にする。
			SetMouseDispFlag(FALSE);
		}
	}
	//---------------------------------△

			//マウスの当たる前の位置から、現在位置の差がこの数値以内なら、動ける
	int MoveValue = 100;

	//マウスの移動量が少ないときに、移動させる
	if (abs(player.collBeforePt.x - mouse.Point.x) < MoveValue
		&& abs(player.collBeforePt.y - mouse.Point.y) < MoveValue)
	{
		//プレイヤーの中心位置を設定する
		player.CenterX = mouse.Point.x;
		player.CenterY = mouse.Point.y;
	}
	else
	{
		//プレイヤーの中心位置を設定する
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;

		//マウスの位置を設定する
		SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
	}
	//-----------------------------△



	//当たり判定-----------------------△
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//プレイヤーとマップがあたっていたら
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{

		/*[キー操作ここから]
		player.CenterX = player.collBeforePt.x;
		player.CenterY = player.collBeforePt.y;
		*/

		SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);

		IsMove = FALSE;
	}

	if (IsMove == TRUE)
	{
		//画面内にマウスがいれば
		if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH
			&& mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
		{
			//プレイヤーの位置に置き換える
			player.image.x = player.CenterX - player.image.width / 2;
			player.image.y = player.CenterY - player.image.height / 2;

			//あたっていないときの座標を取得
			player.collBeforePt.x = player.CenterX;
			player.collBeforePt.y = player.CenterY;
		}

	}

	//---------------△△

	//マウスの左ボタンをクリックしたとき
	if (MY_MOUSE_DOWN(MOUSE_INPUT_LEFT) == TRUE)
	{
		//ショットが撃てるとき
		if (player.CanShot == TRUE)
		{
			//ショット発射！！
			PlaySoundMem(player.musicShot.handle, DX_PLAYTYPE_BACK);
			player.CanShot = FALSE;

			//空いているスロットで、弾の描画をする
			for (int cnt = 0; cnt < TAMA_MAX; cnt++)
			{
				if (player.tama[cnt].IsDraw == FALSE)
				{
					//弾のX位置はプレイヤーの中心から発射
					player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

					//弾のY位置はプレイヤーの上部分から発射
					player.tama[cnt].y = player.image.y;

					//弾を描画する
					player.tama[cnt].IsDraw = TRUE;

					break;
				}
			}


		}
	}

	//ショットが撃てないとき
	if (player.CanShot == FALSE)
	{
		//リロード時間が終わったとき
		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;		//再びショットできる
		}

		player.ShotReLoadCnt++;	//リロードする
	}


	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{

		
	//while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(AllKeyState) == 0) {


		//背景を描画する========================================================
		DrawGraph(ImageBack.x, ImageBack.y, ImageBack.handle, TRUE);

		//マップの描画
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//マップを描画
				DrawGraph(
					map[tate][yoko].x,
					map[tate][yoko].y,
					mapChip.handle[map[tate][yoko].kind],
					TRUE);
			}
		}
		//====================================================================

		//キャラクタの描画
		//DrawGraph(x, yy, pp[result], TRUE);
		//--------------------------------
		DrawGraph(kx, ky, player2.image.handle, TRUE);

		//当たり判定の描画（デバッグ用）----------------△
		for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
			{
				//壁ならば
				if (mapData[tate][yoko] == k)
				{
					DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
				}


				//yならば
				if (mapData[tate][yoko] == y)
				{
					DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(0, 0, 255), FALSE);
				}

				//通路ならば
				if (mapData[tate][yoko] == t)
				{
					DrawBox(mapColl[tate][yoko].left, mapColl[tate][yoko].top, mapColl[tate][yoko].right, mapColl[tate][yoko].bottom, GetColor(255, 255, 0), FALSE);
				}
			}
		}
		DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

		//当たり判定描画（デバッグ）----------------△
		DrawBox(player.coll.left, player.coll.top, player.coll.right, player.coll.bottom, GetColor(255, 0, 0), FALSE);

	    //-------------------------------------------------△








		//弾の情報を生成
		for (int cnt = 0; cnt < TAMA_MAX; cnt++)
		{
			//描画できる弾の処理
			if (player.tama[cnt].IsDraw == TRUE)
			{
				//弾を描画する
				DrawGraph(
					player.tama[cnt].x,
					player.tama[cnt].y,
					player.tama[cnt].handle[player.tama[cnt].nowImageKind],	//現在の画像の種類にあったハンドル
					TRUE);

				//弾の表示フレームを増やす
				if (player.tama[cnt].changeImageCnt < player.tama[cnt].changeImageCntMAX)
				{
					player.tama[cnt].changeImageCnt++;
				}
				else
				{
					//現在表示している弾の種類が、まだあるとき
					if (player.tama[cnt].nowImageKind < TAMA_DIV_NUM - 1)	//-1しないと、最後の種類のときに++されてしまう
					{
						player.tama[cnt].nowImageKind++;	//弾を次の種類にする
					}
					else
					{
						player.tama[cnt].nowImageKind = 0;	//弾の種類をリセットする
					}

					player.tama[cnt].changeImageCnt = 0;
				}

				//弾を上に移動させる
				if (player.tama[cnt].y < 0)
				{
					player.tama[cnt].IsDraw = FALSE;	//描画終了
				}
				else
				{
					player.tama[cnt].y -= player.tama[cnt].speed;
				}
			}
		}

		DrawString(0, 0, "プレイ画面(スペースキーを押して下さい)", GetColor(255, 255, 255));

	//}

	//------------------------------------------------

	
	
	return;
}

//リザルト画面
VOID MY_RUSULT(VOID)
{
	MY_RUSULT_PROC();
	MY_RUSULT_DRAW();

	return;
}

//リザルト画面の処理
VOID MY_RUSULT_PROC(VOID)
{

	//Gを押したら、プレイシーンへ移動する
	if (CheckHitKey(KEY_INPUT_K) != 0)
	{

		//BGMが流れているなら
		if (CheckSoundMem(BGM_RUSULT.handle) != 0)
		{
			StopSoundMem(BGM_RUSULT.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);		//マウスカーソルを表示

		GameScene = GAME_SCENE_END;
		return;
	}

	//BGMが流れていないなら


	if (CheckSoundMem(BGM_RUSULT.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_RUSULT.handle);	//50%の音量にする

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(BGM_RUSULT.handle, DX_PLAYTYPE_LOOP);
	}

	return;
}
//リザルト画面の描画
VOID MY_RUSULT_DRAW(VOID)
{
	//背景を描画する
	DrawGraph(ImageRusult.x, ImageRusult.y, ImageRusult.handle, TRUE);

	DrawString(0, 0, "リザルト画面(Kを押して下さい)", GetColor(255, 255, 255));
	return;
}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{
	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM_END.handle) != 0)
		{
			StopSoundMem(BGM_END.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);		//マウスカーソルを表示

		GameScene = GAME_SCENE_START;
		return;
	}

	//BGMが流れていないなら
	if (CheckSoundMem(BGM_END.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_END.handle);	//50%の音量にする

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(BGM_END.handle, DX_PLAYTYPE_LOOP);
	}


	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//背景を描画する
	DrawGraph(ImageEnd.x, ImageEnd.y, ImageEnd.handle, TRUE);

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}


//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//背景画像===================================================================================
	strcpy_s(ImageBack.path, IMAGE_BACK_PATH);		//パスの設定
	ImageBack.handle = LoadGraph(ImageBack.path);	//読み込み
	if (ImageBack.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageBack.handle, &ImageBack.width, &ImageBack.height);	//画像の幅と高さを取得
	ImageBack.x = GAME_WIDTH / 2 - ImageBack.width / 2;		//左右中央揃え
	ImageBack.y = GAME_HEIGHT / 2 - ImageBack.height / 2;	//上下中央揃え

	//============================================================================================

	//タイトル背景画像
	strcpy_s(ImageTitle.path, IMAGE_TITLE_PATH);
	ImageTitle.handle = LoadGraph(ImageTitle.path);
	if (ImageTitle.handle == -1)
	{
		//エラーメッセージ
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitle.handle, &ImageTitle.width, &ImageTitle.height);
	ImageTitle.x = GAME_WIDTH / 2 - ImageTitle.width / 2;
	ImageTitle.y = GAME_HEIGHT / 2 - ImageTitle.height / 2;
	//==============================================================================================

	//選択背景画像
	strcpy_s(ImageChoice.path, IMAGE_CHOICE_PATH);
	ImageChoice.handle = LoadGraph(ImageChoice.path);
	if (ImageChoice.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_CHOICE_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageChoice.handle, &ImageChoice.width, &ImageChoice.height);
	ImageChoice.x = GAME_WIDTH / 2 - ImageChoice.width / 2;
	ImageChoice.y = GAME_HEIGHT / 2 - ImageChoice.height / 2;
	//==============================================================================================

	//リザルト背景画像
	strcpy_s(ImageRusult.path, IMAGE_RUSULT_PATH);
	ImageRusult.handle = LoadGraph(ImageRusult.path);
	if (ImageRusult.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_RUSULT_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageRusult.handle, &ImageRusult.width, &ImageRusult.height);
	ImageRusult.x = GAME_WIDTH / 2 - ImageRusult.width / 2;
	ImageRusult.y = GAME_HEIGHT / 2 - ImageRusult.height / 2;
	//==============================================================================================

	//エンド背景画像
	strcpy_s(ImageEnd.path, IMAGE_END_PATH);
	ImageEnd.handle = LoadGraph(ImageEnd.path);
	if (ImageEnd.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_END_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEnd.handle, &ImageEnd.width, &ImageEnd.height);
	ImageEnd.x = GAME_WIDTH / 2 - ImageEnd.width / 2;
	ImageEnd.y = GAME_HEIGHT / 2 - ImageEnd.height / 2;
	//==============================================================================================


	//プレイヤーの画像(カーソル）
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//パスの設定
	player.image.handle = LoadGraph(player.image.path);	//読み込み
	if (player.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_LOW;									//スピードを設定
	//------------------------------------------------------------------
	//---------キャラクタ△
	strcpy_s(player2.image.path, IMAGE_PLAYER2_PATH);//パスの設定
	player2.image.handle = LoadGraph(player2.image.path);//読込
	if (player2.image.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER2_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player2.image.handle, &player.image.width, &player.image.height);
	//キャラクタ-----------------------------△
	//マップの画像を分割する--------------------------------------------------------------
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//赤弾のパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//赤弾を分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割するの幅と高さ
		&mapChip.handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップデータ初期化用に情報をコピー
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//マップの種類をコピー
			map[tate][yoko].kind = mapData[tate][yoko];

			//マップの幅と高さをコピー
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//マップの座標を設定
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	//-----------------------------------------------------------------------------------------------
		//赤弾の画像を分割するーーーーーーーーーー△
	int tamaRedRes = LoadDivGraph(
		TAMA_RED_PATH,										//赤弾のパス
		TAMA_DIV_NUM, TAMA_DIV_TATE, TAMA_DIV_YOKO,			//赤弾を分割する数
		TAMA_DIV_WIDTH, TAMA_DIV_HEIGHT,					//画像を分割するの幅と高さ
		&player.tama[0].handle[0]);							//分割した画像が入るハンドル

	/*なぜか読み込める？？？*/

	if (tamaRedRes == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), TAMA_RED_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//幅と高さを取得
	GetGraphSize(player.tama[0].handle[0], &player.tama[0].width, &player.tama[0].height);

	//弾の情報を生成
	for (int cnt = 0; cnt < TAMA_MAX; cnt++)
	{
		//パスをコピー
		strcpyDx(player.tama[cnt].path, TEXT(TAMA_RED_PATH));

		for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++)
		{
			//ハンドルをコピー
			player.tama[cnt].handle[i_num] = player.tama[0].handle[i_num];
		}

		//幅をコピー
		player.tama[cnt].width = player.tama[0].width;

		//高さをコピー
		player.tama[cnt].height = player.tama[0].height;

		//弾のX位置はプレイヤーの中心から発射
		player.tama[cnt].x = player.CenterX - player.tama[cnt].width / 2;

		//弾のY位置はプレイヤーの上部分から発射
		player.tama[cnt].y = player.image.y;

		//弾は最初は非表示
		player.tama[cnt].IsDraw = FALSE;

		//弾の表示カウントを0にする
		player.tama[cnt].changeImageCnt = 0;

		//弾の表示カウントMAXを設定する
		player.tama[cnt].changeImageCntMAX = TAMA_CHANGE_MAX;

		//現在の画像の種類を初期化する
		player.tama[cnt].nowImageKind = 0;

		//弾のスピードを設定する
		player.tama[cnt].speed = CHARA_SPEED_LOW;
	}

	//------------------------------△


	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップデータ初期化用に情報をコピー
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//マップの種類をコピー
			map[tate][yoko].kind = mapData[tate][yoko];

			//マップの幅と高さをコピー
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//マップの座標を設定
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}


	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	//------------------------------------------△
	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{
	DeleteGraph(ImageBack.handle);
	DeleteGraph(player.image.handle);
	DeleteGraph(ImageTitle.handle);
	DeleteGraph(ImageChoice.handle);
	DeleteGraph(ImageRusult.handle);
	DeleteGraph(ImageEnd.handle);
	//DeleteGraph(player2.handle);

	//マップ削除
	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }
	//-------------------
	for (int i_num = 0; i_num < TAMA_DIV_NUM; i_num++) { DeleteGraph(player.tama[0].handle[i_num]); }

	return;
}


//音楽をまとめて読み込む関数
BOOL MY_LOAD_MUSIC(VOID)
{
	//背景音楽
	strcpy_s(BGM.path, MUSIC_BGM_PATH);		//パスの設定
	BGM.handle = LoadSoundMem(BGM.path);	//読み込み
	if (BGM.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//リザルトBGM
	strcpy_s(BGM_RUSULT.path, MUSIC_RUEULT_BGM_PATH);         //パスの設定
	BGM_RUSULT.handle = LoadSoundMem(BGM_RUSULT.path);        //読込
	if (BGM_RUSULT.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_RUEULT_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//タイトルBGM
	strcpy_s(BGM_TITLE.path, MUSIC_TITLE_BGM_PATH);      //パスの設定
	BGM_TITLE.handle = LoadSoundMem(BGM_TITLE.path);     //読込
	if (BGM_TITLE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_TITLE_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//選択BGM
	strcpy_s(BGM_CHOICE.path, MUSIC_CHOICE_BGM_PATH);//
	BGM_CHOICE.handle = LoadSoundMem(BGM_CHOICE.path);//
	if (BGM_CHOICE.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_CHOICE_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	//エンドBGM
	strcpy_s(BGM_END.path, MUSIC_END_BGM_PATH);//
	BGM_END.handle = LoadSoundMem(BGM_END.path);//
	if (BGM_END.handle == -1)
	{
		MessageBox(GetMainWindowHandle(), MUSIC_END_BGM_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//プレイヤーのショット音
	strcpy_s(player.musicShot.path, MUSIC_PLAYER_SHOT_PATH);			//パスの設定
	player.musicShot.handle = LoadSoundMem(player.musicShot.path);		//読み込み
	if (player.musicShot.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), MUSIC_PLAYER_SHOT_PATH, MUSIC_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

//音楽をまとめて削除する関数
VOID MY_DELETE_MUSIC(VOID)
{
	DeleteSoundMem(BGM.handle);
	DeleteSoundMem(player.musicShot.handle);
	DeleteSoundMem(BGM_TITLE.handle);
	DeleteSoundMem(BGM_CHOICE.handle);
	DeleteSoundMem(BGM_PLAY.handle);
	DeleteSoundMem(BGM_RUSULT.handle);
	DeleteSoundMem(BGM_END.handle);


	return;
}


//マップとプレイヤーの当たり判定をする関数--△
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//壁のときは、プレイヤーとマップが当たっている
				if (map[tate][yoko].kind == k) { return TRUE; }
				if (map[tate][yoko].kind == y) { return TRUE; }
				{

				}
			}
		}
	}

	return FALSE;
}

//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}
