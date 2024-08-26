// tesseract_testapp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "baseapi.h" 
#include "allheaders.h"
#include <iostream>

int main()
{
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // 初始化，加载语言包
    if (api->Init("tessdata", "eng")) {
        std::cout << "Could not initialize tesseract" << std::endl;
        return -1;
    }

    // 因为我们编译的leptonica库支持的格式有限，此处用原生支持的BMP来测试
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