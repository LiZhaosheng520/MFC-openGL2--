
// openGLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "openGL.h"
#include "openGLDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <gl/glut.h>

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CopenGLDlg �Ի���



CopenGLDlg::CopenGLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OPENGL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CopenGLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CopenGLDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CopenGLDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CopenGLDlg ��Ϣ�������

BOOL CopenGLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CopenGLDlg::InitializeOpenGL();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CopenGLDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CopenGLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CopenGLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//OpenGL�ĳ�ʼ��
bool CopenGLDlg::InitializeOpenGL()
{
	m_pDC = new CClientDC(GetDlgItem(IDC_IMAGE_DRAW));
	//��ȡ�豸DC����DCΪPictureControl���豸
	if (m_pDC == NULL)
	{//�������DCΪ�գ��򴴽�DCʧ��
		return FALSE;
	}
	if (!SetupPixelFormat())
	{//���ظ�ʽ���������򵥵�˵����ָ����ͼҪ�õ����ظ�ʽ�������ʽ�������������ظ�ʽ���ĺ����塣
		return FALSE;
	}
	//������ͼ������
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());

	if (m_hRC == 0)
	{//	����ʧ��		
		return FALSE;
	}
	// ʹ��ͼ������Ϊ��ǰ�����̵ֳĵ�ǰ��ͼ������
	if (wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		return FALSE;
	}
	//�������ɫ
	GetSize();
	glClearColor(1.0f, 1.0f,1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	return TRUE;
}

//���ظ�ʽ��������
bool CopenGLDlg::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |            // support OpenGL
		PFD_DOUBLEBUFFER,                // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		16,                             // 16-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int m_nPixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	if (m_nPixelFormat == 0)
	{
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

//��ȡ��ͼ��λ��
void CopenGLDlg::GetSize()
{
	int cx;
	int cy;
	CRect rect;
	GetDlgItem(IDC_IMAGE_DRAW)->GetClientRect(rect);
	//ȡ���ؼ��ľ��ο顣
	cx = rect.Width();
	cy = rect.Height();
	GLdouble aspect_ratio; // width/height ratio
	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	// select the full client area
	glViewport(0, 0, cx, cy);
	//ָ����ͼ�������Ϊ00������Ϊcx,cy
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//�˷�����Ϊ���ء�ʹ��������Ч
	gluPerspective(60.0f, aspect_ratio, .05f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void CopenGLDlg::OnBnClickedButton1()
{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������

	GetSize();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	//gluLookAt(-1, -1, 1, 1, 1, -1.88675, 0, 0, 1);
	
	//glLoadIdentity();
	glTranslatef(-1.50, -1.5f, -4.0f);						// Move Left 1.5 Units And Into The Screen 6.0	
	//glRotatef(10,0.0f,1.0f,0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);						// Rotate The Triangle On The Y axis ( NEW )
	glLineWidth(3);

	//X
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(1.0f, 0.0f, -0.04f);
	glVertex3f(1.0f, 0.0f, 0.04f);
	glVertex3f(1.1f, 0.0f, 0.0f);
	glEnd();
	glRasterPos3f(1.0f,0.0f,-0.2f);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'X');
	//Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.06f, 1.0f, 0.0f);
	glVertex3f(0.06f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.2f, 0.0f);
	glEnd();
	glRasterPos3f(-0.2f, 1.0f, 0.0f);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
	//Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(-0.04f, 0.0f, 1.0f);
	glVertex3f(0.04f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.1f);
	glEnd();
	glRasterPos3f(-0.18f, 0.0f, 1.0f);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Z');

	glFinish();
	// Now Swap the buffers
	SwapBuffers(m_pDC->GetSafeHdc());


}
