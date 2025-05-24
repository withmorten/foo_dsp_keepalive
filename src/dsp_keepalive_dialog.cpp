#include "stdafx.h"
#include "resource.h"
#include "dsp_keepalive_dialog.h"
#include "dsp_keepalive.h"

static int ClampAmplitude(int amplitude)
{
    if (amplitude < DspKeepAliveDialog::AmplitudeMin) amplitude = DspKeepAliveDialog::AmplitudeMin;
    if (amplitude > DspKeepAliveDialog::AmplitudeMax) amplitude = DspKeepAliveDialog::AmplitudeMax;

    return amplitude;
}

BOOL DspKeepAliveDialog::OnInitDialog(CWindow, LPARAM) {
    // Parse the initial preset data and populate the edit control
    dsp_keepalive_params params(0);
    DspKeepAlive::parse_preset(params, m_initData);
    
    // Set the edit control value
    ::SetDlgItemInt(*this, IDC_EDIT_NUMBER, params.amplitude_source, FALSE);
    
    return TRUE;
}

void DspKeepAliveDialog::OnButton(UINT, int id, CWindow) {
	if (id == IDOK) {
        // Read value from edit control and update preset
        BOOL translated;
        UINT value = ::GetDlgItemInt(*this, IDC_EDIT_NUMBER, &translated, FALSE);
        
        if (translated) {
            dsp_keepalive_params params(ClampAmplitude(value));
            UpdatePreset(params);
        }
    }
	EndDialog(id);
}

void DspKeepAliveDialog::OnEditChange(UINT, int, CWindow) {
    // Update preset in real-time as user types
    BOOL translated;
    UINT value = ::GetDlgItemInt(*this, IDC_EDIT_NUMBER, &translated, FALSE);
    
    if (translated) {
        dsp_keepalive_params params(ClampAmplitude(value));
        UpdatePreset(params);
    }
}

void DspKeepAliveDialog::UpdatePreset(dsp_keepalive_params params) {
	dsp_preset_impl preset;
	DspKeepAlive::make_preset(params, preset);
	m_callback.on_preset_changed(preset);
}
