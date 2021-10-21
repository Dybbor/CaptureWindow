#pragma once
#include <string>
#include <windows.h>
#include <conio.h>
#include <opencv2/highgui.hpp>

class CaptureWindow
{
private:
    std::string nameclassWindow;
    HWND handlerWindow;
    cv::Mat Bitmap2Mat(HDC& deviceContext, HDC& memoryDeviceContext, int x0, int y0, int x1, int y1);
    void hideConsole();
    void showConsole();
public:
    /**
    @param nameWindow - class window, u can know class window with spy++. Used only in handler capture
    */
    CaptureWindow(std::string _nameWindow="");

    /**
     @param nameWindow - title window
     @param delayWaitkey - delay in cv::waitKey()
     @param x0, y0 - left-top point
     @param stopSymbol - pressed symbol exit program, but some problem with small delay
    */
    void startCaptureWindow4Handler(std::string nameWindow = "Window", int delayWaitKey = 24, char stopSymbol = 'c');

    /**
     @param nameWindow - title window
     @param delayWaitkey - delay in cv::waitKey()
     @param stopSymbol - pressed symbol exit program, but some problem with small delay
     ###### default x, y - screen resolution ######
     @param x0, y0 - left-top point
     @param x1, y1 - right-bottom point
                               
    */
    void startCaptureWindow4Screenshot(std::string nameWindow = "Window", int delayWaitKey = 24,char stopSymbol = 'c', int x0 = -1, int y0 = -1, int x1  = -1, int y1 = -1);
};

