#include "MyForm.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(cli::array<System::String^>^ args) {
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    app::MyForm form;
    Application::Run(% form);
}
