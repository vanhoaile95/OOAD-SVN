#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <map>

enum MTexture
{
	UI_TEXTURE,
	TEXTURE_ATLAS_1,
};


class TextureManager
{

private:
	LPDIRECT3DDEVICE9 *_d3ddv;
	LPD3DXSPRITE* _SpriteHandler;
	std::map<MTexture, LPDIRECT3DTEXTURE9 *> _ListTexture;
	static TextureManager* _instance;
	TextureManager(){};
	~TextureManager(){};

public:
	static TextureManager* GetInstance();
	void GetSpriteHandler(LPD3DXSPRITE* SpriteHandler);
	void GetD3DDevice(LPDIRECT3DDEVICE9 *d3ddv);
	LPDIRECT3DTEXTURE9 CreateTexture(char* FilePath);
	LPDIRECT3DTEXTURE9 CreateTexture(char * FilePath, int Scale);
	LPDIRECT3DSURFACE9 CreateSurfaceFromFile(char * FilePath);
	bool Add(MTexture type,char* path);
	void InitTexture();
	void InitLoading();
	LPDIRECT3DTEXTURE9* Get(MTexture name);

};

#endif