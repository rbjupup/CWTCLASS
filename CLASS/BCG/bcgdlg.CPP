#include "StdAfx.h"
#include "CLASSTEST.h"
#include "CLASS\BCG\BCGdlg.h"
#include "afxdialogex.h"


// ABCGDlg 对话框

IMPLEMENT_DYNAMIC(ABCGDlg, CDialog)

	ABCGDlg::ABCGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ABCGDlg::IDD, pParent)
{
}

ABCGDlg::~ABCGDlg()
{
}

void ABCGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART, m_wndChart);
}


BEGIN_MESSAGE_MAP(ABCGDlg, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &ABCGDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// ABCGDlg 消息处理程序

BOOL ABCGDlg::OnInitDialog()
{

	CDialog::OnInitDialog();
#ifdef BCG
	CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
#endif
	EnableVisualManagerStyle();
	// 异常: OCX 属性页应返回 FALSE



	//波形图绘制
	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);

	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_X_PRIMARY_AXIS, FALSE);

	pChart->SetChartType (BCGPChartHistoricalLine, BCGP_CT_SIMPLE, FALSE);
	pChart->SetLegendPosition(BCGPChartLayout::LP_TOPRIGHT);

	CBCGPChartAxis* pXAxis = pChart->GetChartAxis(BCGP_CHART_X_PRIMARY_AXIS);
	ASSERT_VALID(pXAxis);

	pXAxis->m_axisLabelType = CBCGPChartAxis::ALT_NO_LABELS;
	pXAxis->m_majorTickMarkType = CBCGPChartAxis::TMT_NO_TICKS;
	pXAxis->SetFixedIntervalWidth(40, 10);

	CBCGPChartAxis* pYAxis = pChart->GetChartAxis(BCGP_CHART_Y_PRIMARY_AXIS);
	ASSERT_VALID(pYAxis);

	pYAxis->SetFixedDisplayRange(0., 100, 1);

	pYAxis->m_bDisplayAxisName = FALSE;

	pChart->ShowAxisIntervalInterlacing(BCGP_CHART_Y_PRIMARY_AXIS);
	for (int i = 0; i < 1; i++)
	{

		CString strLabel;
		strLabel.Format(_T("OutTime"), i + 1);

		m_arSeries[i] = pChart->CreateSeries(strLabel);

		if (i > 0)
		{
			pChart->ShowSeries(FALSE, i);
		}
	}


//波形图绘制End


	return TRUE;  // return TRUE unless you set the focus to a control
}


void ABCGDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	CBCGPChartExampleView::OnTimer(nIDEvent);

	

	CBCGPChartVisualObject* pChart = m_wndChart.GetChart();
	ASSERT_VALID(pChart);

	for (int i = 0; i < 1; i++)
	{
		const double d = 100 ;
		const double dblDelta = rand()%(int)d;

		m_arSeries[i]->AddDataPoint(dblDelta);
	}

	pChart->SetDirty();
	pChart->Redraw();
	CDialog::OnTimer(nIDEvent);
}


void ABCGDlg::OnBnClickedButtonStart()
{
	SetTimer(0, 100, NULL);

	m_wndChart.SetFocus();
}
