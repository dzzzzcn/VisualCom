#pragma once
#include "vsm.h"

class CLamp : public CDSIMMODEL
{
	ICOMPONENT* component;                         //代表元件
	BOOL m_LampStatus;  //代表灯泡的状态，FALSE为灭，TRUE为亮       
public:
	CLamp();                                       //构造函数
	~CLamp();                                      //析构函数
public:                    //以下为仿真模型开发需要实现的接口
	CDSIMMODEL* GetSimModel(TCHAR* device);
	ICOMPONENT* GetComponentPtr();
	LONG GetTimeInterval(INT dat);
	BOOL IntervalProcess(RUNMODES mode);
	VOID Initialize(ICOMPONENT* cpt, DSIMMODES smode);
	VOID Setup(SIMDATA* sdat);
	BOOL Simulate(ABSTIME time, RUNMODES mode);
	VOID CallBack(ABSTIME time, EVENTID eventid);
	BOOL Indicate(REALTIME time, ACTIVEDATA* data);
	VOID Animate(INT element, ACTIVEDATA* data);
	BOOL Plot(ACTIVESTATE state);
	BOOL Actuate(WORD key, DPOINT p, UINT flags);
};


