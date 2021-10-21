#include <iostream>
#include "CaptureWindow.h"
#include <wingdi.h>

//chrome not working because idk, mb it is broken, mb need to set tittle or class like window chrome, not like title browser
// Paint - MSPaintApp 
// cuphead - UnityWndClass
int main() {
    try {
        CaptureWindow cw("Notepad");
       // cw.startCaptureWindow4Handler();
        cw.startCaptureWindow4Screenshot("test",'c',1, 0, 0, 900, 1000);
    }
    catch (std::exception ex) {
        std::cout << ex.what() << std::endl;
    }
    return 0;
}