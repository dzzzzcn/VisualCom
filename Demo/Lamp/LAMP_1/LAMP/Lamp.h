#pragma once
#include "vsm.h"

class CLamp : public CDSIMMODEL
{
	ICOMPONENT* component;                         //����Ԫ��
	BOOL m_LampStatus;  //������ݵ�״̬��FALSEΪ��TRUEΪ��       
public:
	CLamp();                                       //���캯��
	~CLamp();                                      //��������
public:                    //����Ϊ����ģ�Ϳ�����Ҫʵ�ֵĽӿ�
	CDSIMMODEL* GetSimModel(TCHAR* device);
	ICOMPONENT* GetComponentPtr();
	LONG GetTimeInterval(INT dat);
	BOOL IntervalProcess(INT mode);
	VOID Initialize(ICOMPONENT* cpt, INT smode);
	VOID Setup(SIMDATA* sdat);
	BOOL Simulate(ABSTIME time, RUNMODES smode);
	VOID CallBack(ABSTIME time, EVENTID eventid);
	BOOL Indicate(REALTIME time, ACTIVEDATA* data);
	VOID Animate(INT element, ACTIVEDATA* data);
	BOOL Plot(ACTIVESTATE state);
	BOOL Actuate(WORD key, DPOINT p, UINT flags);
};


