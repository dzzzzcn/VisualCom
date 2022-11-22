#pragma once
#include "vsm.h"

class CLED_DZZZZCN :public CDSIMMODEL
{
	BOOL m_Status;          //���ڱ��浱ǰ�Ĺ����״̬
	BOOL m_RefreshCtrl;                 //�Ƿ�ˢ����ͼ
	FILLSTYLE bgfs;                   //���ε������ʽ
	FONTSTYLE fs;                           //������ʽ

	ICOMPONENT* component;          //���ڱ���Ԫ��ָ��
public:
	virtual CDSIMMODEL* GetSimModel(TCHAR* device);
	virtual ICOMPONENT* GetComponentPtr();
	virtual LONG GetTimeInterval(INT dat);
	virtual BOOL IntervalProcess(RUNMODES mode);
	virtual VOID Initialize(ICOMPONENT* cpt, DSIMMODES smode);
	virtual VOID Setup(SIMDATA* sdat);
	virtual BOOL Simulate(ABSTIME time, RUNMODES mode);
	virtual VOID CallBack(ABSTIME time, EVENTID eventid);
	virtual VOID Animate(INT element, ACTIVEDATA* newstate);
	virtual BOOL Indicate(REALTIME time, ACTIVEDATA* data);
	virtual BOOL Plot(ACTIVESTATE state);
	virtual BOOL Actuate(WORD key, DPOINT p, UINT flags);
	CLED_DZZZZCN();
};

