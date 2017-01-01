#include "Camera.h"

Camera* Camera::_instance = NULL;

Camera::Camera()
{
	_SpriteHandler = NULL;
	//ViewPort = new RECT();
	VPX = 0;
    VPY = SCREEN_HEIGHT;
}

Camera::~Camera()
{
	//mario_x = mario_y = NULL;
}

Camera* Camera::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new Camera();
	}
	return _instance;
}
void Camera::BeginDraw()
{
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
}
void Camera::EndDraw()
{
	_SpriteHandler->End();
}
void Camera::Draw(LPDIRECT3DTEXTURE9 Image,RECT srect,P pos)
{
	D3DXVECTOR3 position(pos.X, pos.Y, 0);
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = -1.0f;
	mt._41 = -VPX;
	mt._42 = VPY;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &position, &mt);
	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	D3DXVECTOR3 center(0, (float)(srect.bottom - srect.top), 0);

	_SpriteHandler->Draw(
		Image,
		&srect,
		&center,
		&p,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}
void Camera::FixedDraw(LPDIRECT3DTEXTURE9 Image,RECT srect,P pos)
{
	D3DXVECTOR3 position(pos.X, pos.Y, 0);
	_SpriteHandler->Draw(
		Image,
		&srect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
		);
}
//void Camera::UpdateViewPoint()
//{
//
//	ViewPort->left = (long)VPX;
//	ViewPort->top = (long)VPY;
//	ViewPort->right = ViewPort->left + SCREEN_WIDTH;
//	ViewPort->bottom = (long)VPY - SCREEN_HEIGHT;
//
//	CameraBox[0]->X = (float) ViewPort->left;
//	CameraBox[0]->Y = (float) ViewPort->top;
//	CameraBox[1]->X = (float) ViewPort->left-1;
//	CameraBox[1]->Y = (float) ViewPort->bottom;
//	CameraBox[2]->X = (float) ViewPort->right +1;
//	CameraBox[2]->Y = (float) ViewPort->bottom;
//}
//Box Camera::GetBox()
//{
//	return *CameraBox[0];
//}
//
//RECT Camera::getRect()
//{
//	return *ViewPort;
//}
//void Camera::SetMarioPosition(float *X, float *Y)
//{
//	mario_x = X;
//	mario_y = Y;
//	UpdateViewPoint();
//}