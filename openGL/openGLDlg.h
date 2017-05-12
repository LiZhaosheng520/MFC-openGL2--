
// openGLDlg.h : ͷ�ļ�
//

#pragma once


// CopenGLDlg �Ի���
class CopenGLDlg : public CDialogEx
{
// ����
public:
	CopenGLDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
public:
	CDC *m_pDC; 
	HGLRC m_hRC;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool InitializeOpenGL();                //OpenGL��ʼ��
	bool SetupPixelFormat();                //���ظ�ʽ��
	void GetSize();                         //��ȡλ��
	afx_msg void OnBnClickedButton1();      //��Ӧ����
};
