#include <math.h>
#include "snake.h"

Screen scr(SIZEX,SIZEY);
Snake sn(15,10);
Apple app;
int rungame = 1;
using namespace std;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, /* hInstance �������� ������������ ���������� ���� */
                   HINSTANCE hPrevInst, /* hInstance �������� ������������ ���������� ���� */
                   LPSTR lpCmdLine, /* hInstance �������� ������������ ���������� ���� */
                   int nCmdShow) /* ���������� ������ ������ ���� ����� ��� showwindow */
{	
	/*struct tagWNDCLASSEX{
      UINT cbSize; //�������� ��������� � ������
      UINT style; // ���� ������ ����
      WNDPROC WndProc; // ��������� �� ��� ���������������� �������
      int cbWndExtra; // ����� ������������� ������
      int cbClsExtra; // �� ��� ��� � ���� �� ��� ���������� ����������
      HICON hIcon; // ���������� ������
      HICON hIconMini; // .... ����
      HCURSOR hCursor; // .... �������
      HBRUSH hbrBack; // .... ���� ����
      HINSTANCE hInst; // .... ���������� ����������
      LPCTSTR lpszClassName; // ��������� �� const-������ � ������ ������
      LPCTSTR lpszMenuName; // ���������� ���� � ������ ������
}WNDCLASSEX;*/
	HWND hMainWnd;  //windowsDescriptor;
	TCHAR szClassName[] = "My Class";
	MSG msg;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW; 
  wc.lpfnWndProc = WndProc; 
  wc.lpszMenuName = NULL; 
  wc.lpszClassName = szClassName; 
  wc.cbWndExtra = 0; 
  wc.cbClsExtra = 0; 
  wc.hIcon  = LoadIcon(NULL, IDI_WINLOGO); 
  wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); 
  wc.hCursor = LoadCursor(NULL, IDC_ARROW); 
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); 
  wc.hInstance = hInst;
  
  if(!RegisterClassEx(&wc)){ //if class is init
  	MessageBox(NULL, "Alarm!", "Error", MB_OK);
  	return 0;
  }
    
	hMainWnd = CreateWindow(
							szClassName, // ��� �����
							"WindowOne", // ��� ����
							WS_OVERLAPPEDWINDOW,// | WS_VSCROLL, //������ ����������� ����
							50, //������� �� ��� CW_USEDEFAULT
							50, // ������� �� �����, ���� ������ ��� �� ����
							716, //  ������ ���� CW_USEDEFAULT
 							739, // ������. ���� ���� �������
							(HWND)NULL, // ���������� ������������� ����
						 	NULL, // ���������� ����
 							HINSTANCE(hInst), // � ���������� ����������
						 	NULL); // ������ �� �������� �� WndProc
						 	
	if(!hMainWnd) {
		MessageBox(NULL, "Can't create window", "Error", MB_OK);
		return 0;
  }
  
  srand(time(NULL));
  
	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);

  while(GetMessage(&msg, NULL, 0, 0)){
   TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
	return msg.wParam; 
}

LRESULT CALLBACK WndProc(HWND hMainWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

    HDC hDC,hDC1; // ���������� ���������� ������
    PAINTSTRUCT ps; //��������� ���������� �������(������,���..)
    RECT rect; // ������ ���������� �������   
        //GetClientRect(hWnd, &rect); // ������� ���������
    switch(uMsg){
    case WM_KEYDOWN:{
  	  unsigned int key = wParam;
  	switch(key) {
  		case 37:{  	
			sn.setVector(3);		
			}
				break;
			
  		case 38:{  		
			sn.setVector(0);
			};
				break;
			
  		case 39:{  		
			sn.setVector(1);	
			};
				break;
			
  		case 40:{	
			sn.setVector(2);
			};
				break;
		}
	  };
	break;

    case WM_PAINT: {// ���� ��������
        hDC = BeginPaint(hMainWnd, &ps);//�������� ���������� 
        GetClientRect(hMainWnd, &rect); // ������� ���������
				HPEN hPen;	
				scr.draw(hDC);
				sn.draw(hDC);
				app.draw(hDC);
				sn.move();
				//printf("%d = %d | %d = %d\n",sn.getHeadx() , app.getx(), sn.getHeady(), app.gety() );
				if(sn.getHeadx() == app.getx() && sn.getHeady() == app.gety()){
					sn.eat(&app);
				}
				Sleep(150);
        EndPaint(hMainWnd, &ps); //����������� ��������
        if (rungame) {
        InvalidateRect(hMainWnd,NULL,TRUE); // ������� �� ����������� ����
		}
        else{
        PostQuitMessage(0); 
		}
				};
        break;
    case WM_DESTROY: //���� ��������� ���� - ���������� ����
        PostQuitMessage(0); 
       // KillTimer(hMainWnd, 1);
        break;
        
case WM_LBUTTONDOWN:
        PostQuitMessage(0); 
       // KillTimer(hMainWnd, 1);
break;
    default:
        return DefWindowProc(hMainWnd, uMsg, wParam, lParam); //���� ������� ����
    }
    return 0; 
}
