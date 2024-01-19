//=========================================================================================
//
//�����_���[ [renderer.cpp]
//Author:�����V����
//
//=========================================================================================

//*****************************************************************************************
//�C���N���[�h
//*****************************************************************************************
#include "renderer.h"
#include "object.h"
#include "main.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "game.h"

//=========================================================================================
//�����_���[�̃R���X�g���N�^
//=========================================================================================
CRenderer::CRenderer()
{
	//�f�o�C�X�֌W������
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}

//=========================================================================================
//�����_���[�̃f�X�g���N�^
//=========================================================================================
CRenderer::~CRenderer()
{

}

//=========================================================================================
//�����_���[�̏���������
//=========================================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	//����������
	D3DDISPLAYMODE d3ddm;				//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;		//�v���[���e�[�V�����p�����[�^

	//DirectX 3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���s�̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;								//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;											//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;								//�f�v�X�o�b�t�@�ƃX�e���c���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							//�f�v�X�o�b�t�@�Ƃ���16bit�g��
	d3dpp.Windowed = bWindow;											//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//�C���^�[�o��

	//DirectX 3D�f�o�C�X�̐���
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pD3DDevice)))
		{
			return E_FAIL;
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	return S_OK;
}

//=========================================================================================
//�����_���[�̏I������
//=========================================================================================
void CRenderer::Uninit(void)
{
	//Direct 3D�f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=========================================================================================
//�����_���[�̍X�V����
//=========================================================================================
void CRenderer::Update(void)
{
	//�X�V����
	CObject::UpdateAll();
}

//=========================================================================================
//�����_���[�̕`�揈��
//=========================================================================================
void CRenderer::Draw(void)
{
	//��ʃN���A
	m_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

	//	D3DVIEWPORT9 viewportDef;

		//���݂̃����[�|�[�g���擾
	//	m_pD3DDevice->GetViewport(&viewportDef);

		{
			//�V�[���̕`��
			//CScene::Draw();

			//�`�揈��
			CObject::DrawAll();
		}

		//��ʃN���A
		m_pD3DDevice->Clear(0, NULL,D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		{
			if (CManager::GetManager()->GetMode() == CScene::MODE_GAME)
			{
				//�J�������擾
				CCamera *pCamera = CGame::GetCamera();

				//�J�����̕`��
				pCamera->SetCamera();

			}
		}

		{
			//�f�o�b�O���擾
			CDebugProc *pDebug = CManager::GetManager()->GetDebugProc();

			if (pDebug != NULL)
			{//�g�p����Ă�����

				//�`�揈��
				pDebug->Draw();
			}
		}

		//�����[�|�[�g�����ɖ߂�
		//	m_pD3DDevice->SetViewport(&viewportDef);

		//�`��I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�A�b�v�ƃt�����g�o�b�t�@�̐؂�ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=========================================================================================
//�����_���[�f�o�C�X�̎擾
//=========================================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
