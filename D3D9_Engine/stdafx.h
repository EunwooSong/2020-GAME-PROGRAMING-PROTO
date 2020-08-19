#pragma once

//DirectX Header
#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>

//Program Setting
#define CONSOLE_ON false
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BG_COLOR D3DCOLOR_ARGB(255,255,255,255)
#define PROGRAM_NAME TEXT("D3D9_Engine")
#define CONSOLE_NAME TEXT("D3D9_Console")

//Include Windows Header
#include <Windows.h>
#include <XAudio2.h>

//Include Debug
#include <iostream>

//Include GameManager
#include "TextureManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9d.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
//Input State
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define kEY_ON 3

//Define Dispose Macro
#define SAFE_RELEASE(p) {if(p) {p->Release(); (p) = NULL;}}
#define SAFE_DELETE(p) {if(p){delete(p); (p) = nullptr;}}
#define SAFE_DELETE(p) {if(p){delete []p; (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete []p; (p) = nullptr;}}

//Globle Variable
extern LPDIRECT3D9 pd3d;
extern D3DPRESENT_PARAMETERS d3dpp;
extern LPDIRECT3DDEVICE9 pd3dDevice;
extern LPD3DXSPRITE pd3dSprite;
extern LPD3DXEFFECT pd3dEffect;
extern HWND hWnd;

extern SceneManager* sceneManager;
extern TextureManager* textureManager;
extern InputManager* inputManager;
extern ShaderManager* shaderManager;
extern SoundManager* soundManager;