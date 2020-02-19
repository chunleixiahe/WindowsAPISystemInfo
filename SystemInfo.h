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
	int GetCurrentMemoryUsePercent(); //��ȡ��ǰ�û��ڴ�ʹ����
	int GetDiskC_FreeSpace();   // ��ȡC�������� GB/
	int GetDiskC_UseableSpace();   // ��ȡC�̿������� GB/
	int GetDiskSize(std::wstring disk_path); //��ȡĳ��������
	int GetDiskUseSize(std::wstring disk_path); //��ȡĳ�̿�������

private:
	WindowVersion m_version; //windows�汾
	std::wstring convertVersionToWstring(int majorVer,int minorVer,int buildNumber);
	std::wstring m_computer_name;  // ���������
	int m_memory_size; //�ڴ��С:��λ/GB
	int m_disk_c_size; //C�̴�С:��λ/GB
	int m_disk_c_use_size; //C�̿��ô�С����λ/GB
};