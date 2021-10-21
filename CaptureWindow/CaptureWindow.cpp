#include "CaptureWindow.h"

CaptureWindow::CaptureWindow(std::string _nameWindow) {
    nameclassWindow = _nameWindow;
    handlerWindow = FindWindowEx(NULL, NULL, nameclassWindow.c_str(), NULL);
    if (!handlerWindow)
        throw std::invalid_argument("error: invalid nameclass window");
}

cv::Mat CaptureWindow::Bitmap2Mat() {
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

void CaptureWindow::openCaptureWindow(std::string nameWindow, int delayWaitKey, char stopSymbol) {
    cv::namedWindow(nameWindow, cv::WINDOW_NORMAL);
    while (true) {
        cv::Mat frame = Bitmap2Mat();
        cv::namedWindow(nameWindow, cv::WINDOW_NORMAL);
        cv::imshow(nameWindow, frame);
        if (stopSymbol == cv::waitKey(delayWaitKey) ||
            cv::getWindowProperty(nameWindow, cv::WindowPropertyFlags::WND_PROP_VISIBLE) != 1)
            break;
    }
}

