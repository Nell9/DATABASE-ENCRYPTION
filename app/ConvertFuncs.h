#pragma once
#include <iostream>
#include "string"

using namespace System;
using namespace std;
ref class ConvertFuncs
{

public:
    void ConvertSdtStringToUint8(const std::string& input_text, uint8_t* input_data) {
        for (size_t i = 0; i < input_text.size(); ++i) {
            input_data[i] = static_cast<uint8_t>(input_text[i]);
        }
    }
    void ConvertUint8ToStdString(const uint8_t* input_data, size_t size, std::string& output_text) {
        output_text.clear();

        std::string rez(input_data, input_data + size);
        output_text = rez;
    }
    void ConvertStdStringToSystemString(string input_text, String^ &text) {
        text = gcnew String(input_text.c_str());
    }

    void ConvertSystemStringToStdString(String^ s, string& os) {
        using namespace Runtime::InteropServices;
        const char* chars =
            (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
        os = chars;
        Marshal::FreeHGlobal(IntPtr((void*)chars));
    }

    void ConvertSystemStringToUint8(String^ input_text, uint8_t* out_data) {
        string new_string;
        ConvertSystemStringToStdString(input_text, new_string);
        ConvertSdtStringToUint8(new_string, out_data);
    }

    void ConvertUint8ToSystemString(uint8_t input_data[], size_t size, String^& out_text) {
        string new_string;
        ConvertUint8ToStdString(input_data, size, new_string);
        ConvertStdStringToSystemString(new_string, out_text);
    }
};

