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
    cv::Mat Bitmap2Mat();
public:
    CaptureWindow(std::string _nameWindow);
    void openCaptureWindow(std::string nameWindow = "Window", int delayWaitKey = 24, char stopSymbol = 'c');
};

