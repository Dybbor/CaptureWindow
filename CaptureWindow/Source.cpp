#include <iostream>
#include <windows.h>
#include <conio.h>
#include <opencv2/highgui.hpp>

cv::Mat getMat(HWND handlerWindow) {
    HDC deviceContext = GetDC(handlerWindow);
    HDC memoryDeviceContext = CreateCompatibleDC(deviceContext);

    RECT windowRect;
    GetClientRect(handlerWindow, &windowRect);

    int height = windowRect.bottom;
    int width = windowRect.right;

    HBITMAP bitmap = CreateCompatibleBitmap(deviceContext, width, height);

    SelectObject(memoryDeviceContext, bitmap);

    BitBlt(memoryDeviceContext, 0, 0, width, height, deviceContext, 0, 0, SRCCOPY);


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
    DeleteDC(memoryDeviceContext); 
    ReleaseDC(handlerWindow, deviceContext);

    return mat;
 }

//chrome not working because idk, mb it is broken, mb need to set tittle or class like window chrome, not like title browser
// Paint - MSPaintApp 
// cuphead - UnityWndClass
int main() {
    HWND handlerChrome = FindWindowEx(NULL, NULL, "UnityWndClass", NULL);
    std::cout << handlerChrome << std::endl;
    cv::namedWindow("image", cv::WINDOW_NORMAL);
  
    while (1) {
        cv::Mat image = getMat(handlerChrome);
        cv::imshow("image", image);
        cv::waitKey(24);
    
    }
   //cv::Mat image = getMat(handlerChrome);//= cv::Mat::zeros(cv::Size(500, 500), CV_8UC1);
   // cv::imshow("image", image);
   // cv::waitKey();
    return 0;
}