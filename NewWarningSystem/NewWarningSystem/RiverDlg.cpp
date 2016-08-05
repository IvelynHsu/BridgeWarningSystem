// RiverDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NewWarningSystem.h"
#include "RiverDlg.h"
#include "afxdialogex.h"

#include "NewWarningSystemDlg.h"
#include "RiverDlg.h"
#include "CheckDlg.h"
#include "VideoPlayer.h"
#include "WarningNoverlDlg.h"
#include "RiverDlg.h"
#include "SettingDlg.h"

// RiverDlg �Ի���

IMPLEMENT_DYNAMIC(RiverDlg, CDialogEx)

RiverDlg::RiverDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RiverDlg::IDD, pParent)
{

}


RiverDlg::~RiverDlg()
{

}

void RiverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RiverDlg, CDialogEx)
	ON_COMMAND(ID_MenuV, &RiverDlg::OnMenuv)
	ON_COMMAND(ID_MenuR, &RiverDlg::OnMenur)
	ON_COMMAND(ID_MenuW, &RiverDlg::OnMenuw)
	ON_COMMAND(ID_MenuC, &RiverDlg::OnMenuc)
	ON_COMMAND(ID_MenuA, &RiverDlg::OnMenua)
	ON_BN_CLICKED(IDOK4, &RiverDlg::OnBnClickedOk4)
	ON_COMMAND(ID_MenuP, &RiverDlg::OnMenup)
	ON_BN_CLICKED(IDOK2, &RiverDlg::OnBnClickedWarning)
	ON_BN_CLICKED(IDOK3, &RiverDlg::OnBnClickedWarningCancelR)
END_MESSAGE_MAP()


// RiverDlg ��Ϣ�������


BOOL RiverDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();


	return TRUE;
}







/**********************************************************/
/*************************����Ŀ¼����********************/
/*********************************************************/
void RiverDlg::OnMenuv()
{
	// TODO: �ڴ���������������

	CNewWarningSystemDlg * pDlg;
	pDlg = new CNewWarningSystemDlg();
	pDlg->Create(IDD_Main);
	pDlg->ShowWindow(SW_SHOW);


	//��������������Ѵ��� ���԰ѹ��ͻ��
}

void RiverDlg::OnMenur()
{
	// TODO: �ڴ���������������
}

void RiverDlg::OnMenuw()
{
	// TODO: �ڴ���������������
	WarningNoverlDlg * pDlg;
	pDlg = new WarningNoverlDlg();
	pDlg->Create(IDD_Warning);
	pDlg->ShowWindow(SW_SHOW);
}

void RiverDlg::OnMenuc()
{
	// TODO: �ڴ���������������
	CheckDlg * pDlg;
	pDlg = new CheckDlg();
	pDlg->Create(IDD_Check);
	pDlg->ShowWindow(SW_SHOW);
}

void RiverDlg::OnMenua()
{
	// TODO: �ڴ���������������
	CDialogEx * pDlg;
	pDlg = new CDialogEx();
	pDlg->Create(IDD_ABOUTBOX);
	pDlg->ShowWindow(SW_SHOW);
}

void RiverDlg::OnMenup()
{
	// TODO: �ڴ���������������
	VideoPlayer * pDlg;
	pDlg = new VideoPlayer();
	pDlg->Create(IDD_VideoPlayer);
	pDlg->ShowWindow(SW_SHOW);
}




















void RiverDlg::OnBnClickedOk4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	CDC *pDC = GetDlgItem(IDC_River)->GetDC();//����ID��ô���ָ���ٻ�ȡ��ô��ڹ�����������ָ��
	HDC hdc= pDC->GetSafeHdc(); // ��ȡ�豸�����ľ��
	CRect rect;// ������
	
	GetDlgItem(IDC_River)->GetClientRect(&rect); //��ȡbox1�ͻ���
	CvvImage cimg;
	IplImage *src; // ����IplImageָ�����src     
    src = cvLoadImage("D:\\WorkSpace\\WorkSpaceVS\\NewWarningSystem\\NewWarningSystem\\res\\River.png",1); // ��srcָ��ǰ�����ļ�Ŀ¼�µ�ͼ��
	cimg.CopyOf(src,src->nChannels);
	cimg.DrawToHDC(hdc,&rect);//���ͼ��
	ReleaseDC(pDC);
	cimg.Destroy();//����

	CDialogEx * pDlg;
	pDlg = new CDialogEx();
	pDlg->Create(IDD_Setting);
	pDlg->ShowWindow(SW_SHOW);
}





























/**********************************************************/
/***********************  �����澯����  ******************/
/*********************************************************/


void RiverDlg::OnBnClickedWarning()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		INT_PTR nRes;   
  
    // ��ʾ��Ϣ�Ի���   
    nRes = MessageBox(_T("��ȷ��Ҫ�ֶ��澯ô��"), _T("�ֶ��澯"), MB_OKCANCEL | MB_ICONQUESTION);   
    // �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��   
    if (IDCANCEL == nRes)   
        return;   
  
    // �����ؼ��е����ݱ��浽��Ӧ�ı���   
    UpdateData(TRUE);   
  
  
    // ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
    UpdateData(FALSE);   
    // �������ԶԻ���Ϊ�򵼶Ի���   
    //sheet.SetWizardMode(); 
}




void RiverDlg::OnBnClickedWarningCancelR()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	INT_PTR nRes;   
  
    // ��ʾ��Ϣ�Ի���   
    nRes = MessageBox(_T("��ȷ��Ҫ����澯ô��"), _T("����澯"), MB_OKCANCEL | MB_ICONQUESTION);   
    // �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��   
    if (IDCANCEL == nRes)   
        return;   
  
    // �����ؼ��е����ݱ��浽��Ӧ�ı���   
    UpdateData(TRUE);   
  
  
    // ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
    UpdateData(FALSE);   
    // �������ԶԻ���Ϊ�򵼶Ի���   
    //sheet.SetWizardMode(); 
}
