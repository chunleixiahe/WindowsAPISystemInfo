#include "stdafx.h"
using namespace std;

struct WindowVersion{
	DWORD marjorVer; //大版本号
	DWORD minorVer; // 小版本号
	DWORD buildNumber; //构建版本号
};

class SystemInfo{
public:
	SystemInfo();
	~SystemInfo();
	std::wstring GetSystemVersion(); // 获取系统版本
	std::wstring GetComputerName(); // 获取计算机名
	int GetPhysicalMemorySize(); //获取物理内存大小
	int GetCurrentMemoryUsePercent(); //获取当前用户内存使用率1-100;
	int GetDiskC_FreeSpace();   // 获取C盘总容量 GB/
	int GetDiskC_UseableSpace();   // 获取C盘可用容量 GB/
	int GetDiskSize(std::wstring disk_path); //获取某盘总容量
	int GetDiskUseSize(std::wstring disk_path); //获取某盘可用容量
	std::wstring GetCpuName(); // 获取CPU名称
	std::wstring ViewRegeditValue(HKEY hKey_,std::wstring path_,std::wstring key_); // 查询注册表值
	bool WriteToRegedit(HKEY hKey_,std::wstring path_,std::wstring key_,std::wstring value_); //写入注册表，默认为写入字符串
	bool GetScreenResolutionPower(int& cxScreen,int& cyScreen); //获取当前屏幕分辨率

private:
	WindowVersion m_version; //windows版本
	std::wstring convertVersionToWstring(int majorVer,int minorVer,int buildNumber);
	std::wstring m_computer_name;  // 计算机名称
	int m_memory_size; //内存大小:单位/GB
	int m_disk_c_size; //C盘大小:单位/GB
	int m_disk_c_use_size; //C盘可用大小，单位/GB
	std::wstring m_cpu_name; //获取CPU名称
	int m_x_screen; //屏幕分辨率x
	int m_y_screen; //屏幕分辨率y
};