#pragma once
#include "CUi.h"
#include "CUi_Factory.h"
#include "CGraphicDev.h"

class CUi_Button :   public CUi
{
	/**
	* @file CUi_Button
	* @date 2025.06.29
	* @author 김서영
	* @brief 버튼 정보를 저장하는 클래스
	*/
	
private: 
	LPDIRECT3DTEXTURE9 m_pTexBtn; /// 기본 하늘색 버튼
	LPDIRECT3DTEXTURE9 m_pTexName; //선택지 이름
	LPDIRECT3DTEXTURE9 m_pTexLock;///잠금 된 버튼 (색이 더 찐함)
	LPDIRECT3DTEXTURE9 m_pTexLockImage;///자물쇠 그림
	LPDIRECT3DTEXTURE9 m_pTexMenuHover; /// 주황색 버튼
	LPDIRECT3DTEXTURE9 m_pTexScroll; ///버튼 누르면 나오는 스크롤 
	LPDIRECT3DTEXTURE9 m_pTexScrollStart; // 선택지
	LPDIRECT3DTEXTURE9 m_pTexOkBox; //수락 버튼
	LPDIRECT3DTEXTURE9 m_pTexNoBox;  //거절 버튼
	BUTTON_TYPE m_eType = END_BUTTON;

	D3DXVECTOR3 m_vPos;


	int m_iKeyPress;
	float m_fscaleX;
	float m_fscaleY;
	

public:
	CUi_Button(LPDIRECT3DDEVICE9 pGraphicDev);
	CUi_Button(const CGameObject& rhs);
	~CUi_Button();

public:
	/**
	* @brief BUTTON_TYPE에 따라 이미지 정보를 불러오는 함수로 매개변수로 받은 BUTTON_TYPE을 m_eType에 저장한다.
	*/
	HRESULT Ready_GameObject(LPDIRECT3DDEVICE9 pGraphicDev, BUTTON_TYPE _cValue);
	/**
	* @brief m_etype에 저장된 BUTTON_TYPE에 따라 다른 기능이 동작. (마우스 피킹, 키보드 입력 등)
	*/
	_int Update_GameObject(const _float& fTimeDelta);
	void LateUpdate_GameObject(const _float& fTimeDelta);
	void Render_GameObject();

	/**
	* @brief 키입력 시, 입력값에 따라 이미지 정보나 씬 전환등을 업데이트 한다.
	*/
	void Select_Button(float _fTimeDelta);


private:
	void Free();

};

