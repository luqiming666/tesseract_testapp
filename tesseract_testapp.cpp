// tesseract_testapp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "baseapi.h" 
#include "allheaders.h"
#include <iostream>
#include <string>
#include <windows.h>

//#define _TEST_CHINESE_

#ifdef _TEST_CHINESE_
const char szLang[] = "chi_sim";
const char szSourceFile[] = "chinese.bmp";
#else
const char szLang[] = "eng";
const char szSourceFile[] = "numbers.bmp";
#endif

int main()
{  
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    // 初始化，加载语言包
    if (api->Init("tessdata", szLang)) {
        std::cout << "Could not initialize tesseract" << std::endl;
        return -1;
    }

    // 因为我们编译的leptonica库支持的格式有限，此处用原生支持的BMP来测试
    Pix* image = pixRead(szSourceFile);
    if (image) {
        api->SetImage(image);
        char* outText = api->GetUTF8Text();

#ifdef _TEST_CHINESE_
        std::locale currentLocale = std::locale::global(std::locale(""));
        std::wcout.imbue(std::locale());

        int size = ::MultiByteToWideChar(CP_UTF8, 0, outText, -1, NULL, 0);
        wchar_t* wcStr = new wchar_t[size];
        MultiByteToWideChar(CP_UTF8, 0, outText, -1, wcStr, size);
        std::wcout << L"OCR Result: " << wcStr << std::endl;
        delete[] wcStr;
#else
        std::cout << "OCR Result: " << outText << std::endl;
#endif // _TEST_CHINESE_
        
        delete[] outText;
        pixDestroy(&image);
    }
    
    api->End();
    delete api;
    return 0;
}