#pragma once
#include "vsm.h"

class CIF6800 :public CDSIMMODEL
{
	SIMPIN d0, d1, d2, d3, d4, d5, d6, d7;  //引脚声明
	SIMPIN rs, rw, e;
	SIMBUS bus;                             //总线声明
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
	CIF6800();
};

