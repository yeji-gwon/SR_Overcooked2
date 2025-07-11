#include "pch.h"
#include "CPasta.h"
#include "CProtoMgr.h"
#include "CRenderer.h"
#include "IState.h"
#include "CFontMgr.h"
#include "CInteractMgr.h"

CPasta::CPasta(LPDIRECT3DDEVICE9 pGraphicDev)
	: CIngredient(pGraphicDev)
{
}

CPasta::CPasta(const CGameObject& rhs)
	: CIngredient(rhs)
{
}

CPasta::~CPasta()
{
}

HRESULT CPasta::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;

	m_eType = RICE;
	m_eCookState = RAW;
	m_pCurrentState = new IRawState();
	m_pTransformCom->Set_Pos(5.f, m_pTransformCom->Get_Scale().y, 2.f);

	CInteractMgr::GetInstance()->Add_List(CInteractMgr::CARRY, this);

	return S_OK;
}

_int CPasta::Update_GameObject(const _float& fTimeDelta)
{
	int iExit = Engine::CGameObject::Update_GameObject(fTimeDelta);

	CRenderer::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

	if (m_pCurrentState)
		m_pCurrentState->Update_State(this, fTimeDelta);

	if (COOKED == m_eCookState || DONE == m_eCookState)
		Add_Progress(fTimeDelta);

	//// FMS ����� �ӽ�
	//if (RAW == m_eCookState && GetAsyncKeyState('B'))
	//	Set_Progress(1.f);	// Add_Progress(fTimeDelta, 0.5f);
	//swprintf_s(m_szProgress, L"�� : %d, %f", m_eCookState, m_fProgress);
	////

	return iExit;
}

void CPasta::LateUpdate_GameObject(const _float& fTimeDelta)
{
	Engine::CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CPasta::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	//m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	int iIndex = 0;
	if (COOKED == m_eCookState)
		iIndex = 1;
	else if (DONE == m_eCookState)
		iIndex = 2;
	if (BURNT == m_eCookState)
		iIndex = 3;
	m_pTextureCom->Set_Texture(iIndex);

	m_pBufferCom->Render_Buffer();

	//// FMS ����� �ӽ�
	//_vec2   vPos{ 100.f, 150.f };
	//CFontMgr::GetInstance()->Render_Font(L"Font_Default", m_szProgress, &vPos, D3DXCOLOR(0.f, 0.f, 0.f, 1.f));
	////

	//m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

HRESULT CPasta::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<Engine::CRcTex*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_RcTex"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<Engine::CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<Engine::CTexture*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_IngredientTexture_Pasta"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CPasta* CPasta::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPasta* pPasta = new CPasta(pGraphicDev);

	if (FAILED(pPasta->Ready_GameObject()))
	{
		Safe_Release(pPasta);
		MSG_BOX("Pasta Create Failed");
		return nullptr;
	}

	return pPasta;
}

void CPasta::Free()
{
	CInteractMgr::GetInstance()->Add_List(CInteractMgr::CARRY, this);
	CIngredient::Free();
}