
// openGLDlg.h : 头文件
//

#pragma once


// CopenGLDlg 对话框
class CopenGLDlg : public CDialogEx
{
// 构造
public:
	CopenGLDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENGL_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
public:
	CDC *m_pDC; 
	HGLRC m_hRC;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool InitializeOpenGL();                //OpenGL初始化
	bool SetupPixelFormat();                //像素格式化
	void GetSize();                         //获取位置
	afx_msg void OnBnClickedButton1();      //响应函数
};
