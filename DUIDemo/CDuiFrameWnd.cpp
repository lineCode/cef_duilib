#include "CDuiFrameWnd.h"

#include "simple_app.h"
#include "include/cef_client.h"   

#include "include/cef_sandbox_win.h"
#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h" 

 

CDuiFrameWnd::CDuiFrameWnd():m_handler(new SimpleHandler)
{
	 
} 
//const TCHAR* const kCloseButtonControlName = _T("closebtn");
void CDuiFrameWnd::InitWindow()
{   
	m_pBtnClose = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_close"));
	m_pURL = static_cast<CEditUI*>(m_PaintManager.FindControl(L"edit_url"));
	m_pBtnGo = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_go"));
	m_pBtnBack = static_cast<CButtonUI*>(m_PaintManager.FindControl(L"btn_back"));

	RECT rt;
	::GetClientRect(m_hWnd, &rt);
	rt.top += 100;
	rt.bottom -= 3;
	rt.left += 3;
	rt.right -= 3;

	CefWindowInfo info;
	info.SetAsChild(m_hWnd, rt);

	CefBrowserSettings settings;
	CefBrowserHost::CreateBrowser(info, m_handler.get(), L"http://huachenzs.cn/js.html", settings, NULL);
}

void CDuiFrameWnd::OnFinalMessage(HWND hWnd)
{
	::PostQuitMessage(0);
}

void CDuiFrameWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (msg.pSender == m_pBtnClose)
		{
			Close();
		}
		else if (msg.pSender == m_pBtnGo)
		{
			std::wstring strUrl = m_pURL->GetText(); 
			if (strUrl.compare(L"") == 0)
			{
				m_handler->GetBrowser()->GetMainFrame()->ExecuteJavaScript("testfunc()", m_handler->GetBrowser()->GetMainFrame()->GetURL(), 0);
				return;
			}
			m_handler->GetBrowser()->GetMainFrame()->LoadURL(strUrl);
			
		}
		else if (msg.pSender == m_pBtnBack)
		{ 
			//m_handler->GetBrowser()->GoBack();
			CallJsFunc(L"GoBack()");
		}
	}
}
  
LRESULT CDuiFrameWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_SIZE)
	{
		HWND hwnd = ::FindWindowEx(m_hWnd, NULL, L"DUIDemo", NULL);
		::MoveWindow(hwnd, 3, 100, LOWORD(lParam) - 6, HIWORD(lParam) - 103, TRUE);
	}
	else if (uMsg == WM_DROPFILES)
	{
		WCHAR wcFile[MAX_PATH] = { 0 };
		UINT count = DragQueryFile((HDROP)wParam, 0xFFFFFFFF, NULL, 0);
		if (count)
		{
			DragQueryFile((HDROP)wParam, 0, wcFile, MAX_PATH);
			wstring str = wcFile;
			m_handler->GetBrowser()->GetMainFrame()->LoadURL(str);
			m_pURL->SetText(wcFile);
		}
	}
	else if (uMsg == WM_COPYDATA)
	{
		COPYDATASTRUCT* pData = (COPYDATASTRUCT*)lParam;
		::MessageBox(NULL, (LPCWSTR)pData->lpData, L"js func", MB_OK);
	}
	return 0;
}

void CDuiFrameWnd::CallJsFunc(LPCWSTR strJSFuncName)
{
	if (strJSFuncName[0] == L'\0' || strJSFuncName == NULL)
		return; 
	m_handler->GetBrowser()->GetMainFrame()->ExecuteJavaScript(strJSFuncName, m_handler->GetBrowser()->GetMainFrame()->GetURL(), 0);
}

void CDuiFrameWnd::CallJsCBFunc(LPCWSTR str)
{

}