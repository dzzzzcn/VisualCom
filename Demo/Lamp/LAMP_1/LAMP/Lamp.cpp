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
	return -1;
}

BOOL CLamp::IntervalProcess(RUNMODES mode)
{
	return TRUE;
}

VOID CLamp::Initialize(ICOMPONENT* cpt, DSIMMODES smode)
{
	component = cpt;                                           //��ʼ������Ԫ��ָ��
}

VOID CLamp::Setup(SIMDATA* sdat)
{

}

BOOL CLamp::Simulate(ABSTIME time, RUNMODES mode)
{
	PRODATA pro_data_tmp;
	component->GetProData(pro_data_tmp);                             //��ȡԤ������
	
	if (pro_data_tmp.data & 0x1)                               //�ж�Ԥ���������λ
	{
		m_LampStatus = TRUE;                                   //���õ���Ϊ����״̬
	}
	else
	{
		m_LampStatus = FALSE;                                  //���õ���ΪϨ��״̬
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

	DPOINT sym1_offset = component->GetSymbolOffset(1);       //��ȡͼ��1��ƫ��λ��

	if (!m_LampStatus)                                //���ΪϨ��״̬���ͻ���ͼ��1
	{
		component->DrawSymbol(1, NULL, NULL, NULL, sym1_offset.x, sym1_offset.y);
	}

	component->EndCache();                                               //��������
}

BOOL CLamp::Plot(ACTIVESTATE state)
{
	Animate(0, NULL);                                         //����Animate����ͼ��

	return TRUE;
}

BOOL CLamp::Actuate(WORD key, DPOINT p, UINT flags)
{
	return FALSE;
}


