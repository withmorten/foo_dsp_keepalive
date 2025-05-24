#pragma once
#include "stdafx.h"
#include "resource.h"
#include "dsp_keepalive.h"

class DspKeepAliveDialog : public CDialogImpl<DspKeepAliveDialog> {
public:
	DspKeepAliveDialog(const dsp_preset& initData, dsp_preset_edit_callback& callback) : m_initData(initData), m_callback(callback) { }

	enum { IDD = IDD_DSP };

	enum {
		AmplitudeMin = 0,
		AmplitudeMax = 1000,
	};

	BEGIN_MSG_MAP_EX(DspKeepAliveDialog)
		MSG_WM_INITDIALOG(OnInitDialog)
		COMMAND_HANDLER_EX(IDOK, BN_CLICKED, OnButton)
		COMMAND_HANDLER_EX(IDCANCEL, BN_CLICKED, OnButton)
		COMMAND_HANDLER_EX(IDC_EDIT_NUMBER, EN_CHANGE, OnEditChange)
	END_MSG_MAP()

private:

	BOOL OnInitDialog(CWindow, LPARAM);
	void OnButton(UINT, int, CWindow);
	void OnEditChange(UINT, int, CWindow);
	void UpdatePreset(dsp_keepalive_params);

	const dsp_preset& m_initData;
	dsp_preset_edit_callback& m_callback;
};
