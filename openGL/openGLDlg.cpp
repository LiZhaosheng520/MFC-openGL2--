
// openGLDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "openGL.h"
#include "openGLDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <gl/glut.h>

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CopenGLDlg 对话框



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


// CopenGLDlg 消息处理程序

BOOL CopenGLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CopenGLDlg::InitializeOpenGL();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CopenGLDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CopenGLDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//OpenGL的初始化
bool CopenGLDlg::InitializeOpenGL()
{
	m_pDC = new CClientDC(GetDlgItem(IDC_IMAGE_DRAW));
	//获取设备DC，该DC为PictureControl的设备
	if (m_pDC == NULL)
	{//如果返回DC为空，则创建DC失败
		return FALSE;
	}
	if (!SetupPixelFormat())
	{//像素格式化函数，简单的说就是指定绘图要用的像素格式，必须格式化，下面有像素格式化的函数体。
		return FALSE;
	}
	//创建绘图描述表
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());

	if (m_hRC == 0)
	{//	创建失败		
		return FALSE;
	}
	// 使绘图描述表为当前调用现程的当前绘图描述表
	if (wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		return FALSE;
	}
	//设置清除色
	GetSize();
	glClearColor(1.0f, 1.0f,1.0f, 0.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	return TRUE;
}

//像素格式化函数体
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

//获取画图的位置
void CopenGLDlg::GetSize()
{
	int cx;
	int cy;
	CRect rect;
	GetDlgItem(IDC_IMAGE_DRAW)->GetClientRect(rect);
	//取到控件的矩形块。
	cx = rect.Width();
	cy = rect.Height();
	GLdouble aspect_ratio; // width/height ratio
	if (0 >= cx || 0 >= cy)
	{
		return;
	}
	// select the full client area
	glViewport(0, 0, cx, cy);
	//指定绘图区域，起点为00，右下为cx,cy
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//此方法视为加载。使。。。生效
	gluPerspective(60.0f, aspect_ratio, .05f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void CopenGLDlg::OnBnClickedButton1()
{
//	// TODO: 在此添加控件通知处理程序代码

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
