#include "stdafx.h"
using namespace std;

struct WindowVersion{
	DWORD marjorVer; //��汾��
	DWORD minorVer; // С�汾��
	DWORD buildNumber; //�����汾��
};

class SystemInfo{
public:
	SystemInfo();
	~SystemInfo();
	std::wstring GetSystemVersion(); // ��ȡϵͳ�汾
	std::wstring GetComputerName(); // ��ȡ�������
	int GetPhysicalMemorySize(); //��ȡ�����ڴ��С
	int GetCurrentMemoryUsePercent(); //��ȡ��ǰ�û��ڴ�ʹ����1-100;
	int GetDiskC_FreeSpace();   // ��ȡC�������� GB/
	int GetDiskC_UseableSpace();   // ��ȡC�̿������� GB/
	int GetDiskSize(std::wstring disk_path); //��ȡĳ��������
	int GetDiskUseSize(std::wstring disk_path); //��ȡĳ�̿�������
	std::wstring GetCpuName(); // ��ȡCPU����
	std::wstring ViewRegeditValue(HKEY hKey_,std::wstring path_,std::wstring key_); // ��ѯע���ֵ
	bool WriteToRegedit(HKEY hKey_,std::wstring path_,std::wstring key_,std::wstring value_); //д��ע���Ĭ��Ϊд���ַ���
	bool GetScreenResolutionPower(int& cxScreen,int& cyScreen); //��ȡ��ǰ��Ļ�ֱ���

private:
	WindowVersion m_version; //windows�汾
	std::wstring convertVersionToWstring(int majorVer,int minorVer,int buildNumber);
	std::wstring m_computer_name;  // ���������
	int m_memory_size; //�ڴ��С:��λ/GB
	int m_disk_c_size; //C�̴�С:��λ/GB
	int m_disk_c_use_size; //C�̿��ô�С����λ/GB
	std::wstring m_cpu_name; //��ȡCPU����
	int m_x_screen; //��Ļ�ֱ���x
	int m_y_screen; //��Ļ�ֱ���y
};