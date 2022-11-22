#include "LED_DZZZZCN.h"

extern "C" CDSIMMODEL __declspec(dllexport) * CreatedSimModel()
{
	return new CLED_DZZZZCN; 
}

extern "C" VOID __declspec(dllexport) DeletedSimModel(CDSIMMODEL * model)
{
	delete (CLED_DZZZZCN*)model; 
}

CLED_DZZZZCN::CLED_DZZZZCN()
{
	m_Status = FALSE;
	m_RefreshCtrl = FALSE;
}



CDSIMMODEL* CLED_DZZZZCN::GetSimModel(TCHAR* device)
{
	return this;
}

LONG CLED_DZZZZCN::GetTimeInterval(INT dat)
{
	return 10;
}
BOOL CLED_DZZZZCN::IntervalProcess(RUNMODES mode)
{
	return FALSE;
}
void CLED_DZZZZCN::Initialize(ICOMPONENT* cpt, DSIMMODES smode)
{
	component = cpt;

	COLORREF col;
	component->GetColorFiledById(100, col);         //获取背景颜色值
	bgfs.style = HS_SOLID;                                //实心填充
	bgfs.color = col;

	component->GetColorFiledById(101, col);         //获取文字颜色值
	char tmp[50] = "dzzzzcn"; //设置文字内容，修改此处可更改显示文字
	fs.color = col;
	fs.str = component->GetTCHARFromChar(tmp);
}

void CLED_DZZZZCN::Setup(SIMDATA* sdat)
{
}

ICOMPONENT* CLED_DZZZZCN::GetComponentPtr()
{
	return component;
}
BOOL CLED_DZZZZCN::Simulate(ABSTIME time, RUNMODES mode)
{
	char tmp[1024];
	sprintf(tmp, "Enter Simulate\n");
	component->SetOutputInfo(component->GetTCHARFromChar(tmp));

	PRODATA pro_data_tmp;
	if (component->GetProData(pro_data_tmp))
	{
		if (pro_data_tmp.data & 0x1)
		{
			m_Status = TRUE;
		}
		else
		{
			m_Status = FALSE;
		}
	
		m_RefreshCtrl = TRUE;                  //调用一次就设置TRUE
		return TRUE;
	}
	return FALSE;
}

void CLED_DZZZZCN::Animate(INT element, ACTIVEDATA* newstate)
{
	DPOINT pos;

	component->BeginCache();

	//获取矩形图形1相对于右下角的偏移坐标，再调整X与Y坐标
	//具体偏移需要根据实际效果来定
	pos = component->GetSymbolOffset(1);
	pos.x += 70;
	pos.y += 10;

	//绘制图形1，并且设置填充颜色
	component->DrawSymbol(1, NULL, &bgfs, NULL, pos.x, pos.y);
	
	//接下来准备绘制文字图形2，直接在前面坐标的基础上改，
	//也可以先获取偏移坐标后再修改
	pos.x -= 24;
	pos.y -= 5;

	//只有状态为点亮状态，才将文字绘制，否则不绘制（也就是熄灭状态）
	if (m_Status)
	{
		component->DrawSymbol(2, NULL, NULL, &fs, pos.x, pos.y);
	}

	component->EndCache();

}

BOOL CLED_DZZZZCN::Indicate(REALTIME time, ACTIVEDATA* data)
{
	return FALSE;
}

BOOL CLED_DZZZZCN::Plot(ACTIVESTATE state)
{
	
	if (m_RefreshCtrl)         //根据刷新控制变量决定是否更新视图 
	{
		m_RefreshCtrl = FALSE;
		Animate(0, NULL);
		return TRUE;
	}
	return FALSE;
}

BOOL CLED_DZZZZCN::Actuate(WORD key, DPOINT p, UINT flags)
{
	return FALSE;
}

VOID CLED_DZZZZCN::CallBack(ABSTIME time, EVENTID eventid)
{

}