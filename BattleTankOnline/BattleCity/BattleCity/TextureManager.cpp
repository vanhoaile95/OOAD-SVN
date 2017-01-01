#include "TextureManager.h"

TextureManager* TextureManager::_instance = NULL;

TextureManager* TextureManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new TextureManager();
	}
	return _instance;
}

void TextureManager::GetD3DDevice(LPDIRECT3DDEVICE9 *d3ddv)
{
	this->_d3ddv = d3ddv;
}
void TextureManager::GetSpriteHandler(LPD3DXSPRITE* SpriteHandler)
{
	_SpriteHandler=SpriteHandler;
}
bool TextureManager::Add(MTexture type,char* path)
{
	if (_ListTexture.find(type) != _ListTexture.end()) 
		return false;
	
	LPDIRECT3DTEXTURE9* Image = new LPDIRECT3DTEXTURE9();
	*Image = CreateTexture(path);
	_ListTexture[type] = Image;

	return true;
}
LPDIRECT3DTEXTURE9* TextureManager::Get(MTexture name)
{
	std::map<MTexture, LPDIRECT3DTEXTURE9 *>::iterator i;

	i = _ListTexture.find(name);
	if (i == _ListTexture.end())
	{
		return NULL;
	}
	return i->second;
}
void TextureManager::InitLoading()
{
	if (_d3ddv != NULL)
	{
		Add(UI_TEXTURE, "Asset/UI.png");
	}
}
void TextureManager::InitTexture()
{
	if (_d3ddv != NULL)
	{
		Add(TEXTURE_ATLAS_1, "Asset/atlas_1.png");
	}
}
LPDIRECT3DTEXTURE9 TextureManager::CreateTexture(char* FilePath)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DTEXTURE9 Image = NULL;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		return Image;
	}
	/*LPD3DXSPRITE a = *_SpriteHandler;
	a->GetDevice(_d3ddv);*/

	result = D3DXCreateTextureFromFileEx(
		*_d3ddv,
		FilePath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 63, 63),
		&info,
		NULL,
		&Image);

	if (result != D3D_OK)
	{
		return NULL;
	}
	return Image;
}
LPDIRECT3DTEXTURE9 TextureManager::CreateTexture(char* FilePath,int Scale)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	LPDIRECT3DTEXTURE9 Image = NULL;

	result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		return Image;
	}
	/*LPD3DXSPRITE a = *_SpriteHandler;
	a->GetDevice(_d3ddv);*/

	result = D3DXCreateTextureFromFileEx(
		*_d3ddv,
		FilePath,
		info.Width * Scale,
		info.Height * Scale,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(0, 63, 63),
		&info,
		NULL,
		&Image);

	if (result != D3D_OK)
	{
		return NULL;
	}
	return Image;
}
LPDIRECT3DSURFACE9 TextureManager::CreateSurfaceFromFile(char* FilePath)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK)
	{
		return NULL;
	}

	LPDIRECT3DSURFACE9 surface;
	LPDIRECT3DDEVICE9 d3ddv = *_d3ddv;
	d3ddv->CreateOffscreenPlainSurface(
		info.Width,				// width
		info.Height,			// height
		D3DFMT_X8R8G8B8,		// format
		D3DPOOL_DEFAULT,
		&surface,
		NULL);

	result = D3DXLoadSurfaceFromFile(
		surface, 		// surface
		NULL,			// destination palette	
		NULL,			// destination rectangle 
		FilePath,
		NULL,			// source rectangle
		D3DX_DEFAULT, 	// filter image
		D3DCOLOR_XRGB(0, 0, 0),				// transparency (0 = none)
		NULL);			// reserved

	if (result != D3D_OK)
	{
		return NULL;
	}

	return surface;
}