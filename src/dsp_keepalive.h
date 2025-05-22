#pragma once
#include "stdafx.h"

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

private:
};
