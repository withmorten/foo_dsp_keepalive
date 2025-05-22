#include "stdafx.h"
#include "dsp_keepalive.h"

DECLARE_COMPONENT_VERSION("Keep Alive", "0.0.1", "Keep Alive DSP component 0.0.1\nby withmorten");
VALIDATE_COMPONENT_FILENAME("foo_dsp_keepalive.dll");

void dsp_width_params::set_width(audio_sample width) {
	this->width = width;

	if (width < 1.0) {
		this->c1 = 0.5;
		this->c2 = width * width * 0.5;
	}
	else {
		audio_sample tmp;
		tmp = 1 / (1 + width);
		this->c1 = tmp;
		this->c2 = width * tmp;
	}
}

void DspWidth::on_endofplayback(abort_callback&) { }
void DspWidth::on_endoftrack(abort_callback&) { }
void DspWidth::flush() { }
double DspWidth::get_latency() { return 0; }
bool DspWidth::need_track_change_mark() { return false; }

DspWidth::DspWidth(dsp_preset const& in) : m_params{ dsp_width_params(0.5) } {
	parse_preset(m_params, in);
}

GUID DspWidth::g_get_guid() {
	static const GUID guid =
	{ 0x2a8f9c14, 0x6b2e, 0x4d73, { 0x9a, 0x15, 0x7c, 0x8e, 0x4f, 0x91, 0x2b, 0x56 } };
	return guid;
}

void DspWidth::g_get_name(pfc::string_base& p_out) {
	p_out = "Keep Alive";
}

bool DspWidth::g_have_config_popup() { return false; }


bool DspWidth::on_chunk(audio_chunk* chunk, abort_callback&) {
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
	return true;
}

bool DspWidth::g_get_default_preset(dsp_preset& p_out) {
	make_preset(dsp_width_params(1.0), p_out);
	return true;
}

void DspWidth::make_preset(dsp_width_params params, dsp_preset& out) {
	dsp_preset_builder builder;
	builder << params.width;
	builder.finish(g_get_guid(), out);
}

void DspWidth::parse_preset(dsp_width_params& params, const dsp_preset& in) {
	try {
		dsp_preset_parser parser(in);
		parser >> params.width;
		params.set_width(params.width);
	}
	catch (exception_io_data) {
		params.set_width(1.00);
	}
}

void DspWidth::g_show_config_popup(const dsp_preset& p_data, HWND p_parent, dsp_preset_edit_callback& p_callback) {
}

static dsp_factory_t<DspWidth> g_dsp_width_factory;
