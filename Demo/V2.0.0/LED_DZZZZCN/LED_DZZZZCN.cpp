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
	component->GetColorFiledById(100, col);         //��ȡ������ɫֵ
	bgfs.style = HS_SOLID;                                //ʵ�����
	bgfs.color = col;

	component->GetColorFiledById(101, col);         //��ȡ������ɫֵ
	char tmp[50] = "dzzzzcn"; //�����������ݣ��޸Ĵ˴��ɸ�����ʾ����
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
	
		m_RefreshCtrl = TRUE;                  //����һ�ξ�����TRUE
		return TRUE;
	}
	return FALSE;
}

void CLED_DZZZZCN::Animate(INT element, ACTIVEDATA* newstate)
{
	DPOINT pos;

	component->BeginCache();

	//��ȡ����ͼ��1��������½ǵ�ƫ�����꣬�ٵ���X��Y����
	//����ƫ����Ҫ����ʵ��Ч������
	pos = component->GetSymbolOffset(1);
	pos.x += 70;
	pos.y += 10;

	//����ͼ��1���������������ɫ
	component->DrawSymbol(1, NULL, &bgfs, NULL, pos.x, pos.y);
	
	//������׼����������ͼ��2��ֱ����ǰ������Ļ����ϸģ�
	//Ҳ�����Ȼ�ȡƫ����������޸�
	pos.x -= 24;
	pos.y -= 5;

	//ֻ��״̬Ϊ����״̬���Ž����ֻ��ƣ����򲻻��ƣ�Ҳ����Ϩ��״̬��
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
	
	if (m_RefreshCtrl)         //����ˢ�¿��Ʊ��������Ƿ������ͼ 
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