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
	component = cpt;                                           //初始化本地元件指针
}

VOID CLamp::Setup(SIMDATA* sdat)
{

}

BOOL CLamp::Simulate(ABSTIME time, RUNMODES mode)
{
	PRODATA pro_data_tmp;
	component->GetProData(pro_data_tmp);                             //获取预置数据
	
	if (pro_data_tmp.data & 0x1)                               //判断预置数据最低位
	{
		m_LampStatus = TRUE;                                   //设置灯泡为点亮状态
	}
	else
	{
		m_LampStatus = FALSE;                                  //设置灯泡为熄灭状态
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
	component->BeginCache();                                             //开始缓存

	DPOINT sym1_offset = component->GetSymbolOffset(1);       //获取图形1的偏移位置

	if (!m_LampStatus)                                //如果为熄灭状态，就绘制图形1
	{
		component->DrawSymbol(1, NULL, NULL, NULL, sym1_offset.x, sym1_offset.y);
	}

	component->EndCache();                                               //结束缓存
}

BOOL CLamp::Plot(ACTIVESTATE state)
{
	Animate(0, NULL);                                         //调用Animate绘制图形

	return TRUE;
}

BOOL CLamp::Actuate(WORD key, DPOINT p, UINT flags)
{
	return FALSE;
}


