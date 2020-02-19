// SystemInfo.cpp : �������̨Ӧ�ó������ڵ㡣
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

// ��ȡϵͳ�汾
// �����ַ�����ʽ L'xx.xx.xxxx'
std::wstring SystemInfo::GetSystemVersion()
{
	WindowVersion wv;
	OSVERSIONINFOW ver_info;
	ver_info.dwOSVersionInfoSize = sizeof(ver_info); //��ʼ���ṹ���С
	GetVersionEx(&ver_info);
	wv.marjorVer = ver_info.dwMajorVersion;
	wv.minorVer = ver_info.dwMinorVersion;
	wv.buildNumber = ver_info.dwBuildNumber;
	m_version = wv;
	std::wstring version_ = convertVersionToWstring(wv.marjorVer,wv.minorVer,wv.buildNumber);
	return version_;
}

// ����ϵͳ����
std::wstring SystemInfo::GetComputerName()
{
	DWORD size_ = 0;
    TCHAR ComputerName[MAX_COMPUTERNAME_LENGTH]; 
	::GetComputerNameW(ComputerName,&size_);
	m_computer_name=ComputerName;
	return m_computer_name;
}

// ��Ҫ��x64�������У� x86ƽ̨���� ���ֻ�ܻ�ȡ2gb(Ϊɶԭ��δ֪̽)
// ���� ��λgb
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

// ��ȡC������
int SystemInfo::GetDiskC_FreeSpace()
{
	// ��Ҫ�ȳ�ʼ��
	DWORD dwTotalClusters = 0;//�ܵĴ�
	DWORD dwFreeClusters =  0;//���õĴ�
	DWORD dwSectPerClust = 0;//ÿ�����ж��ٸ�����
	DWORD dwBytesPerSect = 0;//ÿ�������ж��ٸ��ֽ�
	BOOL bResult = GetDiskFreeSpace(TEXT("C:"),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int c_free_size = 	dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		m_disk_c_size = c_free_size;
		return c_free_size;
	}
	cout << "����" << endl;
	return 0;
}

int SystemInfo::GetDiskC_UseableSpace()
{
	// ��Ҫ�ȳ�ʼ��
	DWORD dwTotalClusters = 0;//�ܵĴ�
	DWORD dwFreeClusters =  0;//���õĴ�
	DWORD dwSectPerClust = 0;//ÿ�����ж��ٸ�����
	DWORD dwBytesPerSect = 0;//ÿ�������ж��ٸ��ֽ�
	BOOL bResult = GetDiskFreeSpace(TEXT("C:"),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int c_use_size = 	dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		m_disk_c_use_size = c_use_size;
		return c_use_size;
	}
	cout << "����" << endl;
	return 0;
}

int SystemInfo::GetDiskSize(std::wstring disk_path)
{
	// ��Ҫ�ȳ�ʼ��
	DWORD dwTotalClusters = 0;//�ܵĴ�
	DWORD dwFreeClusters =  0;//���õĴ�
	DWORD dwSectPerClust = 0;//ÿ�����ж��ٸ�����
	DWORD dwBytesPerSect = 0;//ÿ�������ж��ٸ��ֽ�
	BOOL bResult = GetDiskFreeSpace(disk_path.c_str(),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int _free_size = 	dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		return _free_size;
	}
	cout << "����" << endl;
	return 0;
}

int SystemInfo::GetDiskUseSize(std::wstring disk_path)
{
	// ��Ҫ�ȳ�ʼ��
	DWORD dwTotalClusters = 0;//�ܵĴ�
	DWORD dwFreeClusters =  0;//���õĴ�
	DWORD dwSectPerClust = 0;//ÿ�����ж��ٸ�����
	DWORD dwBytesPerSect = 0;//ÿ�������ж��ٸ��ֽ�
	BOOL bResult = GetDiskFreeSpace(disk_path.c_str(),&dwSectPerClust, &dwBytesPerSect, &dwFreeClusters, &dwTotalClusters);
	if (bResult)
	{
		int _use_size = 	dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect /(1024*1024*1024);
		return _use_size;
	}
	cout << "����" << endl;
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

