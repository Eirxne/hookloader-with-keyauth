#include <Windows.h>
#include <iostream>
#include "auth.hpp"
#include "skStr.h"
#include <vector>
#include <fstream>
#include <string>

using namespace std;
using namespace KeyAuth;

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

std::string name = "APP NAME"; 
std::string ownerid = "OWNER ID";
std::string secret = "SECRET KEY"; 
std::string version = "VERSION"; 
std::string url = "https://keyauth.win/api/1.2/"; 

api KeyAuthApp(name, ownerid, secret, version, url);

int INJECT()
{
	std::string url = "YOUR DLL LINK";
	std::string path = "C:\\Windows\\System\\cheetos.dll";
	std::string command = "powershell -Command \"(New-Object System.Net.WebClient).DownloadFile('" + url + "', '" + path + "')\"";
	system(command.c_str());

	const wchar_t* dllName = L"C:\\Windows\\System\\cheetos.dll";
	if (GetFileAttributes(dllName) == INVALID_FILE_ATTRIBUTES) {
		cout << "[ ERROR: 1 ]" << endl;
		system("pause");
		return 1;
	}

	HWND hwnd = FindWindowW(L"UnrealWindow", 0);
	if (hwnd == 0) {
		cout << "[ ERROR: 2 ]" << endl;
		system("pause");
		return 1;
	}

	DWORD pid = 0;
	DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
	if (tid == 0) {
		cout << "[ ERROR: 3 ]" << endl;
		system("pause");
		return 1;
	}

	HMODULE dll = LoadLibraryEx(dllName, 0, DONT_RESOLVE_DLL_REFERENCES);
	if (dll == 0) {
		cout << "[ ERROR: 4 ]" << endl;
		system("pause");
		return 1;
	}

	HOOKPROC addr = (HOOKPROC)GetProcAddress(dll, "NextHook");
	if (addr == 0) {
		cout << "[ ERROR: 5 ]" << endl;
		system("pause");
		return 1;
	}

	HHOOK handle = SetWindowsHookEx(WH_GETMESSAGE, addr, dll, tid);
	if (handle == 0) {
		cout << "[ ERROR: 6 ]" << endl;
		system("pause");
		return 1;
	}

	PostThreadMessage(tid, 0x0000, 0, 0);
	cout << "[ SUCCESS ] Cheat successfully loaded." << endl;
}

int wmain(int argc, wchar_t* argv[], wchar_t* envp[]) {
	SetConsoleTitleA(skCrypt("Loader"));
	std::cout << skCrypt("\nConnecting to Servers..");
	KeyAuthApp.init();
	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(2000);
		exit(0);
	}
	system("cls");
MainMenu2:
	std::cout << skCrypt("\n Number of users: ") << KeyAuthApp.data.numUsers;

	std::string username;
	std::string password;
	std::string key;

	system("cls");
	std::cout << skCrypt("\n Enter License Key: ");
	std::cin >> key;
	KeyAuthApp.license(key);

	if (!KeyAuthApp.data.success)
	{
		std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
		Sleep(1500);
		exit(0);
	}
	system("cls");

MainMenu3:
	std::cout << skCrypt("\nwelcome to axeprime loader");
	std::cout << skCrypt("\n User data:");
	std::cout << skCrypt("\n Username: ") << KeyAuthApp.data.username;
	std::cout << skCrypt("\n Hardware-ID: ") << KeyAuthApp.data.hwid;
	std::cout << skCrypt("\n Subscription name(s): ");
	std::string subs;
	for (std::string value : KeyAuthApp.data.subscriptions) subs += value + " ";
	std::cout << subs;
	std::cout << skCrypt("\n Subscription expiry: ") << tm_to_readable_time(timet_to_tm(string_to_timet(KeyAuthApp.data.expiry)));

	INJECT();
	
	system("pause > nul");
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); 

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}