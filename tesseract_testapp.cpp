// tesseract_testapp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "baseapi.h" 
#include "allheaders.h"
#include <iostream>

int main()
{
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    if (api->Init("tessdata", "eng")) {
        std::cout << "Could not initialize tesseract" << std::endl;
        return -1;
    }

    Pix* image = pixRead("numbers.bmp");
    if (image) {
        api->SetImage(image);
        char* outText = api->GetUTF8Text();
        std::cout << "OCR result: " << outText << std::endl;
        delete[] outText;
        pixDestroy(&image);
    }
    
    api->End();
    delete api;
    return 0;
}