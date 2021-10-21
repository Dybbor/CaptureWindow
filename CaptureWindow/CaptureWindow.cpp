#include "CaptureWindow.h"

CaptureWindow::CaptureWindow(std::string _nameWindow) {
    nameclassWindow = _nameWindow;
}


void CaptureWindow::hideConsole() {
    HWND consoleHandler = GetConsoleWindow();
    ShowWindow(consoleHandler, SW_HIDE);
    Sleep(1000);
}
void CaptureWindow::showConsole() {
    HWND consoleHandler = GetConsoleWindow();
    ShowWindow(consoleHandler, SW_SHOW);
    Sleep(1000);
}

cv::Mat CaptureWindow::Bitmap2Mat(HDC& deviceContext,HDC& memoryDeviceContext,int x, int y, int width, int height) {
   
    HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, width, height);
    SelectObject(memoryDeviceContext, bitmap);
    BitBlt(memoryDeviceContext, 0, 0, width, height, deviceContext, x, y, SRCCOPY);

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 1;
    bi.biYPelsPerMeter = 2;
    bi.biClrUsed = 3;
    bi.biClrImportant = 4;
    cv::Mat mat = cv::Mat(height, width, CV_8UC4);
    GetDIBits(memoryDeviceContext, bitmap, 0, height, mat.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    DeleteObject(bitmap);

    return mat;
}

void CaptureWindow::startCaptureWindow4Handler(std::string nameWindow, int delayWaitKey , char stopSymbol) {
    handlerWindow = FindWindowEx(NULL, NULL, nameclassWindow.c_str(), NULL);
    if (!handlerWindow)
        throw std::invalid_argument("error: invalid nameclass window");
    HDC deviceContext = GetDC(handlerWindow);
    HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);
    RECT windowRect;
    GetClientRect(handlerWindow, &windowRect);
    int height = windowRect.bottom;
    int width = windowRect.right;
    cv::namedWindow(nameWindow, cv::WINDOW_NORMAL);    
    while (true) {
        cv::Mat frame = Bitmap2Mat(deviceContext, memoryDeviceContext, 0,0, width, height);
        cv::namedWindow(nameWindow, cv::WINDOW_NORMAL);
        cv::imshow(nameWindow, frame);
        if (stopSymbol == cv::waitKey(delayWaitKey) ||
            cv::getWindowProperty(nameWindow, cv::WindowPropertyFlags::WND_PROP_VISIBLE) != 1)
            break;
    }
    DeleteDC(memoryDeviceContext);
    ReleaseDC(handlerWindow, deviceContext);
}

void CaptureWindow::startCaptureWindow4Screenshot(std::string nameWindow, int delayWaitKey,char stopSymbol, int x0, int y0, int x1, int y1) {

    if (x0 == -1 || x1 == -1 || y0 == -1 || y1 == -1) {
        x0 = GetSystemMetrics(SM_XVIRTUALSCREEN);
        y0 = GetSystemMetrics(SM_YVIRTUALSCREEN);
        x1 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
        y1 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    }
       
    int width = x1 - x0;
    int height = y1 - y0;
    HDC screenContext = GetDC(NULL);
    HDC memoryDeviceContext = CreateCompatibleDC(screenContext);
    cv::namedWindow(nameWindow, cv::WINDOW_NORMAL);
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        cv::Mat frame = Bitmap2Mat(screenContext, memoryDeviceContext, x0, y0, width, height);
        cv::namedWindow(nameWindow, cv::WINDOW_NORMAL);
        cv::imshow(nameWindow, frame);
        if (stopSymbol == cv::waitKey(delayWaitKey) ||
            cv::getWindowProperty(nameWindow, cv::WindowPropertyFlags::WND_PROP_VISIBLE) != 1)
            break;
    }
    DeleteDC(memoryDeviceContext);
    ReleaseDC(handlerWindow, screenContext);
    
}


