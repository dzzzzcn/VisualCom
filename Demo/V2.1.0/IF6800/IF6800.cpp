#include "IF6800.h"

extern "C" CDSIMMODEL __declspec(dllexport) * CreatedSimModel()
{
	return new CIF6800; 
}

extern "C" VOID __declspec(dllexport) DeletedSimModel(CDSIMMODEL * model)
{
	delete (CIF6800*)model; 
}

CIF6800::CIF6800()
{
}

CDSIMMODEL* CIF6800::GetSimModel(TCHAR* device)
{
	return this;
}

LONG CIF6800::GetTimeInterval(INT dat)
{
	return -1;
}


BOOL CIF6800::IntervalProcess(RUNMODES mode)
{
	return FALSE;
}
void CIF6800::Initialize(ICOMPONENT* cpt, DSIMMODES smode)
{
	component = cpt;
}

void CIF6800::Setup(SIMDATA* sdat)
{
	char str_d0[50] = "D0";                     //注意字符串区分大小写
	char str_d1[50] = "D1";
	char str_d2[50] = "D2";
	char str_d3[50] = "D3";
	char str_d4[50] = "D4";
	char str_d5[50] = "D5";
	char str_d6[50] = "D6";
	char str_d7[50] = "D7";
	char str_rs[50] = "RS";
	char str_rw[50] = "RW";
	char str_e[50] = "E";

	//以下根据引脚名称查找元件对应的引脚
	component->GetSimPinByName(d0, component->GetTCHARFromChar(str_d0));
	component->GetSimPinByName(d1, component->GetTCHARFromChar(str_d1));
	component->GetSimPinByName(d2, component->GetTCHARFromChar(str_d2));
	component->GetSimPinByName(d3, component->GetTCHARFromChar(str_d3));
	component->GetSimPinByName(d4, component->GetTCHARFromChar(str_d4));
	component->GetSimPinByName(d5, component->GetTCHARFromChar(str_d5));
	component->GetSimPinByName(d6, component->GetTCHARFromChar(str_d6));
	component->GetSimPinByName(d7, component->GetTCHARFromChar(str_d7));
	component->GetSimPinByName(rs, component->GetTCHARFromChar(str_rs));
	component->GetSimPinByName(rw, component->GetTCHARFromChar(str_rw));
	component->GetSimPinByName(e, component->GetTCHARFromChar(str_e));

	//以下将数据线引脚添加到总线方便后续操作
	component->AddPinToBus(bus, d0);
	component->AddPinToBus(bus, d1);
	component->AddPinToBus(bus, d2);
	component->AddPinToBus(bus, d3);
	component->AddPinToBus(bus, d4);
	component->AddPinToBus(bus, d5);
	component->AddPinToBus(bus, d6);
	component->AddPinToBus(bus, d7);
}

ICOMPONENT* CIF6800::GetComponentPtr()
{
	return component;
}

BOOL CIF6800::Simulate(ABSTIME time, RUNMODES mode)
{
	PRODATA pro_data_tmp;
	
	if (component->GetProData(pro_data_tmp))
	{
		if (PRODATA_TYPE_CMD == pro_data_tmp.type)
		{
			component->SetPinDataLow(rs);            //发送指令时应该将RS拉低
		}
		else
		{
			component->SetPinDataHigh(rs);           //发送数据时应该将RS拉高
		}
		component->SetPinDataLow(rw);                      //RW拉低表示写数据
		component->SetPinBusData(bus, pro_data_tmp.data & 0xFF);   //设置数据

		//以下驱动E引脚产生正脉冲
		component->SetPinDataLow(e);                                  //E拉低
		component->SetPinDataDelay(10);                     //添加延时（可选）
		component->SetPinDataHigh(e);                                 //E拉高
		component->SetPinDataDelay(10);               //增加正脉冲宽度（可选）
		component->SetPinDataLow(e);                                  //E拉低
		return TRUE;
	}
	return FALSE;
}

void CIF6800::Animate(INT element, ACTIVEDATA* newstate)
{
}

BOOL CIF6800::Indicate(REALTIME time, ACTIVEDATA* data)
{
	return FALSE;
}

BOOL CIF6800::Plot(ACTIVESTATE state)
{
	return FALSE;
}

BOOL CIF6800::Actuate(WORD key, DPOINT p, UINT flags)
{
	return FALSE;
}

VOID CIF6800::CallBack(ABSTIME time, EVENTID eventid)
{

}