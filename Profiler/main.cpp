#include <stdio.h>
#include <strsafe.h>

#include "Profiler.h"
#include <process.h>

using namespace std;
Profiler g_Profiler;


void TestFunc1()
{
	Sleep(1);
}

void TestFunc2()
{
	Sleep(2);
}
void TestFunc3()
{
	Sleep(3);
}
void TestFunc4()
{
	for (int i = 0; i < 100; ++i)
	{

	}
}

HANDLE g_Thread[5];

unsigned int __stdcall ThreadTest(LPVOID param)
{
	WCHAR buf1[100];
	WCHAR buf2[100];

	for (int i = 0; i < 10000000; ++i)
	{
		g_Profiler.ProfileBegin(L"strcpy");
		wcscpy_s(buf1, 8, L"ABCD");
		g_Profiler.ProfileEnd(L"strcpy");
	}
	for (int i = 0; i < 10000000; ++i)
	{
		g_Profiler.ProfileBegin(L"stringcchcopyw");
		StringCchCopyW(buf2, 100, L"ABCD");
		g_Profiler.ProfileEnd(L"stringcchcopyw");
	}

	return 0;
	
}
int main()
{
	
	for (int i = 0; i < 5; ++i)
	{
		g_Thread[i] = (HANDLE)_beginthreadex(NULL, 0, ThreadTest, NULL, 0, NULL);
	}




	WaitForMultipleObjects(5, g_Thread, TRUE, INFINITE);

	g_Profiler.ProfileDataOutText(L"ProfileReport.txt");

}