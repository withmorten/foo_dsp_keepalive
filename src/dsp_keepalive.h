#pragma once
#include "stdafx.h"

static void RunDSPConfigPopup(const dsp_preset& p_data, HWND p_parent, dsp_preset_edit_callback& p_callback);

struct dsp_keepalive_params {
	dsp_keepalive_params(int amplitude) { set_amplitude(amplitude); }
	int amplitude_source;
	audio_sample amplitude;
	void set_amplitude(int amplitude);
};

class DspKeepAlive : public dsp_impl_base {
public:
	DspKeepAlive(dsp_preset const& in);
	static GUID g_get_guid();
	static void g_get_name(pfc::string_base&);
	static bool g_have_config_popup();
	void on_endofplayback(abort_callback&);
	void on_endoftrack(abort_callback&);
	void flush();
	double get_latency();
	bool need_track_change_mark();
	bool on_chunk(audio_chunk*, abort_callback&);
	static bool g_get_default_preset(dsp_preset&);
	static void g_show_config_popup(const dsp_preset&, HWND, dsp_preset_edit_callback&);
	static void make_preset(dsp_keepalive_params, dsp_preset&);
	static void parse_preset(dsp_keepalive_params&, const dsp_preset&);

private:
	dsp_keepalive_params m_params;
};
