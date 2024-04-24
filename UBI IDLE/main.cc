#include <Windows.h>
#include <map>
#include <string>


static HINSTANCE MainHInstance;

const size_t MAX_LOADSTRING { 100 };

const WCHAR MAINWINDOWTITLE[MAX_LOADSTRING] { L"UBI IDLE" };
const WCHAR MAINWINDOWCLASSNAME[MAX_LOADSTRING] { L"MAIN_FRAME" };


std::map<std::string, HWND> ButtonList;



LRESULT CALLBACK MainWindowProcess( HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam )
{
    switch (Message) 
    {
    case WM_CREATE:

        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, Message, wparam, lparam);
    }

    return NULL;
}



ATOM RegistationMainWindow( HINSTANCE hInstance )
{

    WNDCLASS StructRegister 
    {
        .style = CS_VREDRAW | CS_HREDRAW, 
        .lpfnWndProc = MainWindowProcess,
        .hInstance = hInstance,
        .hbrBackground = (HBRUSH)(WHITE_BRUSH),
        .lpszClassName = MAINWINDOWCLASSNAME
    };


    return RegisterClass(&StructRegister);
}

BOOL CreateMainWindow( HINSTANCE hInstance, int nCmdShow )
{
    MainHInstance = hInstance;

    HWND Window = CreateWindowW(MAINWINDOWCLASSNAME, MAINWINDOWTITLE, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!Window)
        return FALSE;   

    ShowWindow(Window, nCmdShow);
    UpdateWindow(Window);
}



BOOL InitButton( std::string id, HWND button )
{
    ButtonList.emplace(id, button);
    return !button;
}



int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
    
    RegistationMainWindow(hInstance);
    CreateMainWindow(hInstance, nCmdShow);


    MSG Message; 


    while (GetMessageW( &Message, NULL, NULL, NULL ))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }


	return static_cast<int>(Message.wParam);
}