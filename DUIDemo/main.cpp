#include "CDuiFrameWnd.h"
#include "simple_app.h"



int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	void* sandbox_info = NULL;
	CefMainArgs main_args(hInstance);
	CefRefPtr<SimpleApp> app(new SimpleApp);
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	CefInitialize(main_args, settings, app.get(), sandbox_info);

	CPaintManagerUI::SetInstance(hInstance);
	CDuiFrameWnd wnd;
	wnd.Create(NULL, L"", UI_WNDSTYLE_FRAME | WS_THICKFRAME, WS_EX_ACCEPTFILES);
	wnd.ShowWindow();
	wnd.CenterWindow();
	CPaintManagerUI::MessageLoop();
	CefShutdown();
	return 0; 
}


