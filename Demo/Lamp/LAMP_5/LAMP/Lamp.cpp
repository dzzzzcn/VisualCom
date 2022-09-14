#include "Lamp.h"

extern "C" CDSIMMODEL __declspec(dllexport) * CreatedSimModel()
{
	return new CLamp; 
}

extern "C" VOID __declspec(dllexport) DeletedSimModel(CDSIMMODEL * model)
{
	delete (CLamp*)model;
}

CLamp::CLamp()
{
	m_LampStatus = FALSE;
	m_RefreshFlag = FALSE;
	sym1_offset.x = 0;
	sym1_offset.y = 0;
	m_fs.style = HS_SOLID;                                               //ʵ�����
	m_fs.color = BRIGHTRED;                                                  //��ɫ

	m_LampCtrl = FALSE;
	m_SysInvokingCount = 0;
	m_CurrentInvokingCount = 0;
}

CLamp::~CLamp()
{
}

CDSIMMODEL* CLamp::GetSimModel(TCHAR* device)
{
	return this;
}

ICOMPONENT* CLamp::GetComponentPtr()
{
	return component;
}

LONG CLamp::GetTimeInterval(INT dat)
{
	return 100;                                        //���ط���ģ��Ҫ���ʱ����
}

BOOL CLamp::IntervalProcess(RUNMODES mode)
{
	if (m_LampCtrl)
	{
		if (m_CurrentInvokingCount < m_SysInvokingCount)
		{
			m_CurrentInvokingCount++;
		}
		else
		{
			m_CurrentInvokingCount = 0;
			m_LampStatus = (!m_LampStatus);                              //״̬ȡ��
		}
		m_RefreshFlag = TRUE;
	}
	else
	{
		m_CurrentInvokingCount = 0;
		m_LampStatus = FALSE;
	}
	
	return TRUE;
}

VOID CLamp::Initialize(ICOMPONENT* cpt, DSIMMODES smode)
{
	component = cpt;                                           //��ʼ������Ԫ��ָ��

	sym1_offset = component->GetSymbolOffset(1);              //��ȡͼ��1��ƫ��λ��

	COLORREF color = 0;
	if (component->GetColorFiledById(100, color))      //ͨ��IDֵ��ȡ�û��������ɫ
	{
		m_fs.color = color;
	}
}

VOID CLamp::Setup(SIMDATA* sdat)
{
	LONG t = component->GetThreadTimeInterval();
	
	if (t > 10)                                                  //�ж�ϵͳʱ����
	{
		m_SysInvokingCount = 5;
	}
	else if (t > 1)
	{
		m_SysInvokingCount = 50;
	}
	else if (t == 1)
	{
		m_SysInvokingCount = 500;
	}
}

BOOL CLamp::Simulate(ABSTIME time, RUNMODES smode)
{
	PRODATA pro_data_tmp;
	if (component->GetProData(pro_data_tmp))                         //��ȡԤ������
	{
		if (pro_data_tmp.data & 0x1)                           //�ж�Ԥ���������λ
		{
			m_LampCtrl = TRUE;                                 //���õ���Ϊ����״̬
		}
		else
		{
			m_LampCtrl = FALSE;                                //���õ���ΪϨ��״̬
		}

		PROPCELLS cells = GetRegisterPage();
		component->SetRegMemStatus(&cells, NULL, NULL);            //���üĴ�������

		m_RefreshFlag = TRUE;
		return TRUE;
	}
	return FALSE;
}

VOID CLamp::CallBack(ABSTIME time, EVENTID eventid)
{

}

BOOL CLamp::Indicate(REALTIME time, ACTIVEDATA* data)
{
	return FALSE;
}

VOID CLamp::Animate(INT element, ACTIVEDATA* data)
{
	component->BeginCache();                                             //��ʼ����

	if (!m_LampStatus)                                //���ΪϨ��״̬���ͻ���ͼ��1
	{
		component->DrawSymbol(1, NULL, NULL, NULL, sym1_offset.x, sym1_offset.y);
	}
	else                          //���Ϊ����״̬��Ҳ����ͼ��1������ɫΪ�û��Զ���
	{
		component->DrawSymbol(1, NULL, &m_fs, NULL, sym1_offset.x, sym1_offset.y);
	}

	component->EndCache();                                               //��������
}

BOOL CLamp::Plot(ACTIVESTATE state)
{
	if (m_RefreshFlag)
	{
		m_RefreshFlag = FALSE;
		Animate(0, NULL);                                     //����Animate����ͼ��
		return TRUE;
	}
	return FALSE;
}

BOOL CLamp::Actuate(WORD key, DPOINT p, UINT flags)
{
	return FALSE;
}

PROPCELLS CLamp::GetRegisterPage()
{
	PROPCELLS cellCollection;                            //���صİ�������״̬������
	PROPCELL cell;               //����ĳ��״̬����ʱ��Ԫ�����״̬���ݺ��ٲ�������
	UINT index = 1;                 //�Ĵ���������ÿ����ʾ��Ԫ��ΩһID�����״̬ʱ��

	char str_name_tmp[512];
	char str_value_tmp[512];
	char str_info_tmp[512];

	sprintf(str_name_tmp, "%s", "LED");                            //��һ�㼶�����
	sprintf(str_value_tmp, "%s", "");
	sprintf(str_info_tmp, "%s", "");

	cell.id = -1;                                                //������һ�㼶���
	cell.name = component->GetTCHARFromChar(str_name_tmp);
	cell.value = component->GetTCHARFromChar(str_value_tmp);
	cell.description = component->GetTCHARFromChar(str_info_tmp);
	cellCollection.push_back(cell);

	sprintf(str_name_tmp, "%s", "����");      //�����ڶ��㼶��𣨷Ǳ�Ҫ��������ʾ��
	cell.id = -2;
	cell.name = component->GetTCHARFromChar(str_name_tmp);
	cell.value = component->GetTCHARFromChar(str_value_tmp);
	cell.description = component->GetTCHARFromChar(str_info_tmp);
	cellCollection.push_back(cell);

	sprintf(str_name_tmp, "%s", "STAT");
	sprintf(str_value_tmp, "%s", (m_LampCtrl ? "1" : "0"));
	sprintf(str_info_tmp, "%s", "��ǰLED����˸״̬��1Ϊ��,0Ϊ��");
	cell.id = index++;                                           //���������״̬��
	cell.name = component->GetTCHARFromChar(str_name_tmp);
	cell.value = component->GetTCHARFromChar(str_value_tmp);
	cell.description = component->GetTCHARFromChar(str_info_tmp);
	cellCollection.push_back(cell);

	return cellCollection;
}

