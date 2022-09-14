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
			m_LampStatus = (!m_LampStatus);                              //状态取反
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
	PRODATA pro_data_tmp;
	if (component->GetProData(pro_data_tmp))                         //获取预置数据
	{
		if (pro_data_tmp.data & 0x1)                           //判断预置数据最低位
		{
			m_LampCtrl = TRUE;                                 //设置灯泡为点亮状态
		}
		else
		{
			m_LampCtrl = FALSE;                                //设置灯泡为熄灭状态
		}

		PROPCELLS cells = GetRegisterPage();
		component->SetRegMemStatus(&cells, NULL, NULL);            //设置寄存器窗口

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
	return FALSE;
}

PROPCELLS CLamp::GetRegisterPage()
{
	PROPCELLS cellCollection;                            //返回的包括所有状态的链表
	PROPCELL cell;               //包含某个状态的临时单元，填充状态数据后再插入链表
	UINT index = 1;                 //寄存器窗口中每个显示单元的惟一ID（多个状态时）

	char str_name_tmp[512];
	char str_value_tmp[512];
	char str_info_tmp[512];

	sprintf(str_name_tmp, "%s", "LED");                            //第一层级组别名
	sprintf(str_value_tmp, "%s", "");
	sprintf(str_info_tmp, "%s", "");

	cell.id = -1;                                                //创建第一层级组别
	cell.name = component->GetTCHARFromChar(str_name_tmp);
	cell.value = component->GetTCHARFromChar(str_value_tmp);
	cell.description = component->GetTCHARFromChar(str_info_tmp);
	cellCollection.push_back(cell);

	sprintf(str_name_tmp, "%s", "所有");      //创建第二层级组别（非必要，用于演示）
	cell.id = -2;
	cell.name = component->GetTCHARFromChar(str_name_tmp);
	cell.value = component->GetTCHARFromChar(str_value_tmp);
	cell.description = component->GetTCHARFromChar(str_info_tmp);
	cellCollection.push_back(cell);

	sprintf(str_name_tmp, "%s", "STAT");
	sprintf(str_value_tmp, "%s", (m_LampCtrl ? "1" : "0"));
	sprintf(str_info_tmp, "%s", "当前LED的闪烁状态（1为是,0为否）");
	cell.id = index++;                                           //创建具体的状态项
	cell.name = component->GetTCHARFromChar(str_name_tmp);
	cell.value = component->GetTCHARFromChar(str_value_tmp);
	cell.description = component->GetTCHARFromChar(str_info_tmp);
	cellCollection.push_back(cell);

	return cellCollection;
}

