#include "DxLib.h"

typedef enum {
    eScene_Title,   //�^�C�g�����
    eScene_Menu,    //���j���[���
    eScene_Game,    //�Q�[�����
    eScene_Config,  //�ݒ���
} eScene;

static int Scene = eScene_Menu;    //���݂̉��(�V�[��)

//�V�[�����X�V����
void UpdateScene() {
    DrawString(0, 20, "A�L�[�Ń^�C�g����ʁAG�L�[�ŃQ�[����ʁAC�L�[�Őݒ�AM�L�[�Ń��j���[��ʂɂȂ�܂��B", GetColor(255, 255, 255));
    if (CheckHitKey(KEY_INPUT_A) != 0) {
        Scene = eScene_Title;
    }
    if (CheckHitKey(KEY_INPUT_G) != 0) {
        Scene = eScene_Game;
    }
    if (CheckHitKey(KEY_INPUT_C) != 0) {
        Scene = eScene_Config;
    }
    if (CheckHitKey(KEY_INPUT_M) != 0) {
        Scene = eScene_Menu;
    }
}

//�^�C�g�����
void Title() {
    DrawString(0, 0, "�^�C�g����ʂł��B", GetColor(255, 255, 255));
}

//���j���[���
void Menu() {
    DrawString(0, 0, "���j���[��ʂł��B", GetColor(255, 255, 255));
}

//�Q�[�����
void Game() {
    DrawString(0, 0, "�Q�[����ʂł��B", GetColor(255, 255, 255));
}

//�ݒ���
void Config() {
    DrawString(0, 0, "�ݒ��ʂł��B", GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        switch (Scene) {//���݂̃V�[���ɂ���������������

        case eScene_Title://���݂̃V�[�����^�C�g���Ȃ�
            Title();//�^�C�g�����
            break;
        case eScene_Menu://���݂̃V�[�������j���[�Ȃ�
            Menu();//���j���[���
            break;
        case eScene_Game://���݂̃V�[�����Q�[���Ȃ�
            Game();//�Q�[�����
            break;
        case eScene_Config://���݂̃V�[�����ݒ�Ȃ�
            Config();//�ݒ���
            break;
        }

        UpdateScene();//�V�[�����X�V����

    }

    DxLib_End(); // DX���C�u�����I������
    return 0;
}

//void fps() {
//    int i;
//    static int t = 0, ave = 0, f[60];
//
//    f[count % 60] = GetNowCount() - t;
//    t = GetNowCount();
//    if (count % 60 == 59) {
//        ave = 0;
//        for (i = 0; i < 60; i++)
//            ave += f[i];
//        ave /= 60;
//    }
//    if (ave != 0) {
//        DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1fFPS", 1000.0 / (double)ave);
//        DrawFormatString(0, 20, GetColor(255, 255, 255), "%dms", ave);
//    }
//    return;
//}