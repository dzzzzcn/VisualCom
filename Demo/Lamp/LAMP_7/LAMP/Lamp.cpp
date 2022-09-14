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
			m_LampStatus = (!m_LampStatus);                                  //״̬ȡ��
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
	if ((key & VK_KEY_MASK) == 'A')                                    //�жϰ�����
	{
		if (key & MK_KEYDOWN)                                      //�ж��Ƿ�Ϊ����
		{
			m_LampCtrl = (!m_LampCtrl);
			m_RefreshFlag = TRUE;
		}		
	}

	return FALSE;
}


