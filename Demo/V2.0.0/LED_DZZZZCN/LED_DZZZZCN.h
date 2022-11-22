#pragma once
#include "vsm.h"

class CLED_DZZZZCN :public CDSIMMODEL
{
	BOOL m_Status;          //用于保存当前的广告牌状态
	BOOL m_RefreshCtrl;                 //是否刷新视图
	FILLSTYLE bgfs;                   //矩形的填充样式
	FONTSTYLE fs;                           //文字样式

	ICOMPONENT* component;          //用于保存元件指针
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

