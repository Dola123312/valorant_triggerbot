#pragma once

#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>

using namespace std;

int snapValue;

int ojasnfouasnuo(void) {
    return GetSystemMetrics(SM_CXSCREEN);
}

int jksanfiabiy(void) {
    return GetSystemMetrics(SM_CYSCREEN);
}

struct point {
    double x;
    double y;
    point(double x, double y) : x(x), y(y) {}
};

//original color purple (not set to default)
inline bool oajsnfijansyib(int red, int green, int blue) {
    if (green >= 190) {
        return false;
    }

    if (green >= 140) {
        return abs(red - blue) <= 8 &&
            red - green >= 50 &&
            blue - green >= 50 &&
            red >= 105 &&
            blue >= 105;
    }

    return abs(red - blue) <= 13 &&
        red - green >= 60 &&
        blue - green >= 60 &&
        red >= 110 &&
        blue >= 100;
}


BYTE* screenData = 0;
bool run_threads = true;

const int screen_width = ojasnfouasnuo(), screen_height = jksanfiabiy();

void ksnfojasnji()
{
    INPUT    Input = { 0 };
    // left down 
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    ::SendInput(1, &Input, sizeof(INPUT));

    // left up
    ::ZeroMemory(&Input, sizeof(INPUT));
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    ::SendInput(1, &Input, sizeof(INPUT));
}

void prints() {
    Sleep(700);
    cout << "C*eat started " << endl;
    Sleep(700);
    cout << "T*igger*ot working now!" << endl; cout << endl;

    Sleep(100);cout << "-->  Shot delay : None" << endl;
    Sleep(100);cout << "-->  Search Fov : 10" << endl;
    Sleep(100);cout << "-->  Color : Purple" << endl;
    Sleep(100);cout << "-->  Fire Button State : Left Click" << endl;
    Sleep(100);cout << "-->  Fire Type : Full Speed" << endl;

}
int fov = 10;
void ijsanfiuasni() {
    int w = fov, h = fov;
    

    HDC hScreen = GetDC(NULL);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
    screenData = (BYTE*)malloc(5 * screen_width * screen_height);
    HDC hDC = CreateCompatibleDC(hScreen);

    point middle_screen(screen_width / 2, screen_height / 2);

    BITMAPINFOHEADER bmi = { 0 };
    bmi.biSize = sizeof(BITMAPINFOHEADER);
    bmi.biPlanes = 1;
    bmi.biBitCount = 32;
    bmi.biWidth = w;
    bmi.biHeight = -h;
    bmi.biCompression = BI_RGB;
    bmi.biSizeImage = 0;

    while (run_threads) {
        HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
        BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, middle_screen.x - (w / 2), middle_screen.y - (h / 2), SRCCOPY);
        SelectObject(hDC, old_obj);
        GetDIBits(hDC, hBitmap, 0, h, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
        bool stop_loop = false;
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < w * 4; i += 4) {
#define red screenData[i + (j*w*4) + 2]
#define green screenData[i + (j*w*4) + 1]
#define blue screenData[i + (j*w*4) + 0]

                if (oajsnfijansyib(red, green, blue)) {
                    ksnfojasnji();
                    stop_loop = true;
                    break;
                }
            }
            if (stop_loop) {
                break;
            }
        }
    }
}


int main()
{
    prints();
    ijsanfiuasni();
}