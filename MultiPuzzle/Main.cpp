#include "Application.h"
#include <windows.h>
#include <tchar.h>

Application g_appi;

int _tmain(int argc, _TCHAR* argv[])
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);

	g_appi.Run();

	return 0;
}