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
	m_fs.style = HS_SOLID;                                               //实心填充
	m_fs.color = BRIGHTRED;                                                  //红色

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
	return 100;                                        //返回仿真模型要求的时间间隔
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
			m_LampStatus = (!m_LampStatus);                                  //状态取反
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
	component = cpt;                                           //初始化本地元件指针

	sym1_offset = component->GetSymbolOffset(1);              //获取图形1的偏移位置

	COLORREF color = 0;
	if (component->GetColorFiledById(100, color))      //通过ID值获取用户定义的颜色
	{
		m_fs.color = color;
	}
}

VOID CLamp::Setup(SIMDATA* sdat)
{
	LONG t = component->GetThreadTimeInterval();
	
	if (t > 10)                                                  //判断系统时间间隔
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
	component->BeginCache();                                             //开始缓存

	if (!m_LampStatus)                                //如果为熄灭状态，就绘制图形1
	{
		component->DrawSymbol(1, NULL, NULL, NULL, sym1_offset.x, sym1_offset.y);
	}
	else                          //如果为点亮状态，也绘制图形1，但颜色为用户自定义
	{
		component->DrawSymbol(1, NULL, &m_fs, NULL, sym1_offset.x, sym1_offset.y);
	}

	component->EndCache();                                               //结束缓存
}

BOOL CLamp::Plot(ACTIVESTATE state)
{
	if (m_RefreshFlag)
	{
		m_RefreshFlag = FALSE;
		Animate(0, NULL);                                     //调用Animate绘制图形
		return TRUE;
	}
	return FALSE;
}

BOOL CLamp::Actuate(WORD key, DPOINT p, UINT flags)
{
	if ((key & VK_KEY_MASK) == 'A')                                    //判断按键码
	{
		if (key & MK_KEYDOWN)                                      //判断是否为按下
		{
			m_LampCtrl = (!m_LampCtrl);
			m_RefreshFlag = TRUE;
		}		
	}

	return FALSE;
}


