#include <iostream>
#include "CaptureWindow.h"


//chrome not working because idk, mb it is broken, mb need to set tittle or class like window chrome, not like title browser
// Paint - MSPaintApp 
// cuphead - UnityWndClass
int main() {
    CaptureWindow cw("Notepad");
    cw.openCaptureWindow();
    return 0;
}