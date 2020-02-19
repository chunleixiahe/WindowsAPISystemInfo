// SystemInfo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SystemInfo.h"
#include <iosfwd>
#include <sstream>

using namespace std;

SystemInfo::SystemInfo()
{

}

SystemInfo::~SystemInfo()
{

}

// 获取系统版本
// 返回字符串格式 L'xx.xx.xxxx'
std::wstring SystemInfo::GetSystemVersion()
{
	WindowVersion wv;
	OSVERSIONINFOW ver_info;
	ver_info.dwOSVersionInfoSize = sizeof(ver_info); //初始化结构体大小
	GetVersionEx(&ver_info);
	wv.marjorVer = ver_info.dwMajorVersion;
	wv.minorVer = ver_info.dwMinorVersion;
	wv.buildNumber = ver_info.dwBuildNumber;
	m_version = wv;
	std::wstring version_ = convertVersionToWstring(wv.marjorVer,wv.minorVer,wv.buildNumber);
	return version_;
}

// 返回系统名称
std::wstring SystemInfo::GetComputerName()
{
	DWORD size_ = 0;
    TCHAR ComputerName[MAX_COMPUTERNAME_LENGTH]; 
	::GetComputerNameW(ComputerName,&size_);
	m_computer_name=ComputerName;
	return m_computer_name;
}

// 需要在x64里面运行， x86平台运行 最多只能获取2gb(为啥原因未探知)
// 返回 单位gb
int SystemInfo::GetPhysicalMemorySize()
{
	MEMORYSTATUS   Mem;
	GlobalMemoryStatus(&Mem);
	int memory_use = (double)(Mem.dwTotalPhys)/(double)(1024*1024*1024);
	m_memory_size = memory_use;
	return memory_use;
}

int SystemInfo::GetCurrentMemoryUsePercent()
{
	MEMORYSTATUS   Mem;
	GlobalMemoryStatus(&Mem);
	return Mem.dwMemoryLoad; 
}

std::wstring SystemInfo::convertVersionToWstring(int majorVer,int minorVer,int buildNumber)
{
	std::wstringstream oss_;
	oss_ <<majorVer<< L"."<<minorVer<<L"."<<buildNumber;
	std::wstring wstr=oss_.str();
	return wstr;
}

// 获取C盘容量
int SystemInfo::GetDiskC_FreeSpace()
{
	// 需要先初始化
	DWORD dwTotalClusters = 0;//总的簇
	DWORD dwFreeClusters =  0;//可用的簇
	DWORD dwSectPerClust = 0;//每个簇有多少个扇区
	DWORD dwBytesPerSect = 0;//每个扇区有多少个字节
	BOOL bResult = GetDiskFreeSpace(TEXT("C:"),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int c_free_size = 	dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		m_disk_c_size = c_free_size;
		return c_free_size;
	}
	cout << "错误" << endl;
	return 0;
}

int SystemInfo::GetDiskC_UseableSpace()
{
	// 需要先初始化
	DWORD dwTotalClusters = 0;//总的簇
	DWORD dwFreeClusters =  0;//可用的簇
	DWORD dwSectPerClust = 0;//每个簇有多少个扇区
	DWORD dwBytesPerSect = 0;//每个扇区有多少个字节
	BOOL bResult = GetDiskFreeSpace(TEXT("C:"),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int c_use_size = 	dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		m_disk_c_use_size = c_use_size;
		return c_use_size;
	}
	cout << "错误" << endl;
	return 0;
}

int SystemInfo::GetDiskSize(std::wstring disk_path)
{
	// 需要先初始化
	DWORD dwTotalClusters = 0;//总的簇
	DWORD dwFreeClusters =  0;//可用的簇
	DWORD dwSectPerClust = 0;//每个簇有多少个扇区
	DWORD dwBytesPerSect = 0;//每个扇区有多少个字节
	BOOL bResult = GetDiskFreeSpace(disk_path.c_str(),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int _free_size = 	dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		return _free_size;
	}
	cout << "错误" << endl;
	return 0;
}

int SystemInfo::GetDiskUseSize(std::wstring disk_path)
{
	// 需要先初始化
	DWORD dwTotalClusters = 0;//总的簇
	DWORD dwFreeClusters =  0;//可用的簇
	DWORD dwSectPerClust = 0;//每个簇有多少个扇区
	DWORD dwBytesPerSect = 0;//每个扇区有多少个字节
	BOOL bResult = GetDiskFreeSpace(disk_path.c_str(),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int _use_size = 	dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		return _use_size;
	}
	cout << "错误" << endl;
	return 0;
}

std::wstring SystemInfo::GetCpuName()
{
	HKEY hKey;
	LONG nRet;
	nRet = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey); 
	std::wstring key_ = L"ProcessorNameString";
	TCHAR CPUNAME[250];
	DWORD dwType;
	DWORD nLen = 0;
	::RegQueryValueEx(hKey,key_.c_str(),0, &dwType, (LPBYTE)CPUNAME, &nLen);
	m_cpu_name = CPUNAME;
	return m_cpu_name;
}

std::wstring SystemInfo::ViewRegisterValue(HKEY hKey_,std::wstring path_,std::wstring key_)
{
	HKEY hKey;
	LONG nRet;
	nRet = ::RegOpenKeyEx(hKey_, path_.c_str(), 0, KEY_READ, &hKey); 
	TCHAR RegisterValue[250];
	DWORD dwType;
	DWORD nLen = 0;
	::RegQueryValueEx(hKey,key_.c_str(),0, &dwType, (LPBYTE)RegisterValue, &nLen);
	std::wstring Key_Value = RegisterValue;
	return Key_Value;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SystemInfo sys;
	std::wstring system_version_ = sys.GetSystemVersion();
	sys.GetCpuName();
	system("pause");
	return 0;
}

