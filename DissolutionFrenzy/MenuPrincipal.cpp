#include "MenuPrincipal.h"

using namespace System;
using namespace Windows::Forms;

int main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Application::Run(gcnew DissolutionFrenzy::MenuPrincipal);
}