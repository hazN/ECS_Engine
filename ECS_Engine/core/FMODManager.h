#pragma once
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>
#include <iostream>
#include <string>
#include <map>

#define MAX_CHANNEL 5
#define MASTER_CH	"Master"
#define BGM_CH1		"BGM1"
#define BGM_CH2		"BGM2"
#define BGM_CH3		"BGM3"
#define	FX1_CH		"fx1"
#define FX2_CH		"fx2"

class FModManager
{
public:
	FModManager();
	~FModManager();

	struct CHgroup
	{
		FMOD::ChannelGroup* group_ptr;
		float current_pan;
		float dsp_pitch;
		FMOD::Channel* chn_ptr;

		CHgroup();
	};

	bool Fmod_init(const int num_channel, const int system_flag);
	void shutdown();
	void update();

	bool create_channel(const std::string& CH_name);
	bool find_channel_group(const std::string& CH_name, CHgroup** channel_group);
	void remove_channel(const std::string& CH_name);
	bool set_channel_parent(const std::string& child_name, const std::string& parent_name);

	bool get_channel_vol(const std::string& CH_name, float* vol);
	bool set_channel_vol(const std::string& CH_name, float vol);

	bool get_channel_group_pan(const std::string& CH_name, float* pan);
	bool set_channel_group_pan(const std::string& CH_name, float pan);

	bool get_channel_group_enabled(const std::string& CH_name, bool* enabled);
	bool set_channel_group_enabled(const std::string& CH_name, bool enabled);

	bool get_channel_pitch(const std::string& CH_name, float* pitch);
	bool set_channel_pitch(const std::string& CH_name, float pitch);

	bool get_channel_freq(const std::string& CH_name, float* freq);
	bool set_channel_freq(const std::string& CH_name, float freq);

	bool get_playback_pos(const std::string& CH_name, unsigned int* pos);


	//bool create_sound(const std::string& Sound_name, const cXML::MyMusic path,const int mode, const bool is_compress);
	bool create_sound(const std::string& Sound_name, const std::string& path, const int mode, const bool iscompress);
	//bool create_stream(const std::string& stream_name, const cXML::MyMusic path, const int mode, const bool is_compress);
	bool remove_sound(const std::string& Sound_name);
	bool play_sound(const std::string& Sound_name, const std::string& CH_name);
	bool stop_sound(const std::string& CH_name);
	bool get_speed(const std::string& Sound_name, float* speed);
	bool set_speed(const std::string& Sound_name, float speed);
	bool get_sound_name(const std::string& Sound_name, std::string* fname);
	bool get_sound_format(const std::string& Sound_name, std::string* type, std::string* format, int* chn, int* bit);
	bool get_sound_defualt(const std::string& Sound_name, float* freq, int* priority);
	bool get_sound_lengh(const std::string& Sound_name, unsigned int* length);


	//dsp
	bool add_dsp(const std::string& CH_name, const std::string& fx_name);
	bool remove_dsp(const std::string& CH_name, const std::string& fx_name);
	//bool create_dsp(const std::string& DSP_name, FMOD_DSP_TYPE DSP_type, const float value);
	bool create_dsp(const std::string& DSP_name, FMOD_DSP_TYPE DSP_type);
	bool get_dsp(const std::string& DSP_name, FMOD::DSP** dsp);
	bool get_dsp_param(const std::string& DSP_name, const int index, float* value, char* valuestr, const int valuestrlen);
	

	//bool get_dsp_param(const std::string& DSP_name, const int index, const float* value);
	bool set_dsp_param(const std::string& DSP_name, const int index, const float value);

protected:
	FMOD_RESULT last_result_;
	FMOD::System* system_;

	std::map<std::string, CHgroup*> channel_group_;
	std::map<std::string, FMOD::Sound*> sound_;
	std::map<std::string, FMOD::DSP*> dsp_;


	bool is_Fmod_ok(const bool show_error = true) const;
	const char* FmodTypeEnumtoChar(FMOD_SOUND_TYPE t) noexcept;
	const char* FmodFormatEnumtoChar(FMOD_SOUND_FORMAT f) noexcept;


};