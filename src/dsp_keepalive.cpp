#include "stdafx.h"
#include "dsp_keepalive.h"

DECLARE_COMPONENT_VERSION("Keep Alive", "0.0.1", "Keep Alive DSP component 0.0.1\nby withmorten");
VALIDATE_COMPONENT_FILENAME("foo_dsp_keepalive.dll");

void DspKeepAlive::on_endofplayback(abort_callback&) { }
void DspKeepAlive::on_endoftrack(abort_callback&) { }
void DspKeepAlive::flush() { }
double DspKeepAlive::get_latency() { return 0; }
bool DspKeepAlive::need_track_change_mark() { return false; }

DspKeepAlive::DspKeepAlive(dsp_preset const& in) {
}

GUID DspKeepAlive::g_get_guid() {
	static const GUID guid =
	{ 0x2a8f9c14, 0x6b2e, 0x4d73, { 0x9a, 0x15, 0x7c, 0x8e, 0x4f, 0x91, 0x2b, 0x56 } };
	return guid;
}

void DspKeepAlive::g_get_name(pfc::string_base& p_out) {
	p_out = "Keep Alive";
}

bool DspKeepAlive::g_have_config_popup() { return false; }


bool DspKeepAlive::on_chunk(audio_chunk* chunk, abort_callback&) {
	// do nothing mono or surround audio
	if (chunk->get_channel_config() != audio_chunk::channel_config_stereo) return true;

#if 0
	// do nothing mono or surround audio
	if (chunk->get_channel_config() != audio_chunk::channel_config_stereo) return true;

	audio_sample* samples = chunk->get_data();
	audio_sample m, s;
	t_size count = chunk->get_sample_count();
	for (t_size i = 0; i < count; i++) {
		m = (samples[i * 2 + 1] + samples[i * 2]) * m_params.c1;
		s = (samples[i * 2 + 1] - samples[i * 2]) * m_params.c2;
		samples[i * 2] = m - s;
		samples[i * 2 + 1] = m + s;
	}
	chunk->set_data(samples, count, 2, chunk->get_srate());
#endif
	return true;
}

bool DspKeepAlive::g_get_default_preset(dsp_preset& p_out) {
	return true;
}

void DspKeepAlive::g_show_config_popup(const dsp_preset& p_data, HWND p_parent, dsp_preset_edit_callback& p_callback) {
}

static dsp_factory_t<DspKeepAlive> g_dsp_width_factory;
