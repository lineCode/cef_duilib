#pragma once
#define VC_EXTRALEAN // Exclude rarely-used stuff from Windows headers #include <afxwin.h> // MFC core and standard components #include <afxext.h> // MFC extensions 
#include <afxdisp.h> // MFC Automation classes 
#include <afxdtctl.h> // MFC support for Internet Explorer 4 Common Controls #ifndef _AFX_NO_AFXCMN_SUPPORT 
#include <afxcmn.h> // MFC support for Windows Common Controls #endif // _AFX_NO_AFXCMN_SUPPORT 

#include "simple_handler.h"  
#include "common.h" 


class CDuiFrameWnd : public WindowImplBase
{
public:
	CDuiFrameWnd() ;
	~CDuiFrameWnd() {};
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);
	virtual void Notify(TNotifyUI& msg);

protected:  
	virtual CDuiString GetSkinFolder() { return L".\\skin\\"; }
	virtual CDuiString GetSkinFile() { return L"TestDuiLib.xml"; }
	virtual LPCTSTR GetWindowClassName() const { return _T("UIMainFrame"); };
	virtual UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	virtual UILIB_RESOURCETYPE GetResourceType() const { return UILIB_FILE; }
	virtual CDuiString GetZIPFileName() const { return L""; }
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	void CallJsFunc(LPCWSTR strJSFuncName);
	void CallJsCBFunc(LPCWSTR str);
 
private:
	CButtonUI* m_pBtnClose;
	CEditUI* m_pURL;
	CButtonUI* m_pBtnGo;
	CButtonUI* m_pBtnBack; 
	CefRefPtr<SimpleHandler> m_handler;
};