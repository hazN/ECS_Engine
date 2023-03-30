#include "FMODManager.h"

FModManager::FModManager()
{
	last_result_ = FMOD_OK;
	system_ = nullptr;

	Fmod_init(MAX_CHANNEL, FMOD_INIT_NORMAL);
	create_channel(MASTER_CH);
	create_channel(FX1_CH);
	set_channel_parent(FX1_CH, MASTER_CH);

}

FModManager::~FModManager()
{
}

bool FModManager::Fmod_init(const int num_channel, const int system_flag)
{
	last_result_ = System_Create(&system_);
	if (!is_Fmod_ok())
	{
		return false;
	}

	last_result_ = system_->init(num_channel, system_flag, nullptr);

	return is_Fmod_ok();

}

void FModManager::shutdown()
{
	for (auto i = dsp_.begin(); i != dsp_.end(); ++i)
	{
		i->second->release();
	}
	dsp_.clear();

	for (auto i = sound_.begin(); i != sound_.end(); ++i)
	{
		i->second->release();
	}
	sound_.clear();

	for (auto i = channel_group_.begin(); i != channel_group_.end(); ++i)
	{
		i->second->group_ptr->release();
	}
	channel_group_.clear();

	if (system_)
	{
		system_->release();
		system_ = nullptr;
	}
}

void FModManager::update()
{
	system_->update();
}

bool FModManager::create_channel(const std::string& CH_name)
{
	FMOD::ChannelGroup* channel_group;

	last_result_ = system_->createChannelGroup(CH_name.c_str(), &channel_group);
	if (!is_Fmod_ok())
	{
		return false;
	}

	auto* exparam = new CHgroup();
	exparam->group_ptr = channel_group;

	channel_group_.try_emplace(CH_name, exparam); //add channel name to map with CHgroup structure

	return true;
}

bool FModManager::find_channel_group(const std::string& CH_name, CHgroup** channel_group)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}
	*channel_group = i->second;

	return true;
}


void FModManager::remove_channel(const std::string& CH_name)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return;
	}
	i->second->group_ptr->release();
	channel_group_.erase(i);
}

bool FModManager::set_channel_parent(const std::string& child_name, const std::string& parent_name)
{
	const auto child = channel_group_.find(child_name);
	const auto parent = channel_group_.find(parent_name);
	if (child == channel_group_.end() || parent == channel_group_.end())
	{
		return false;
	}

	last_result_ = parent->second->group_ptr->addGroup(child->second->group_ptr);

	return is_Fmod_ok();
}

bool FModManager::get_channel_vol(const std::string& CH_name, float* vol)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->getVolume(vol);

	return is_Fmod_ok();
}

bool FModManager::set_channel_vol(const std::string& CH_name, float vol)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->setVolume(vol);

	return is_Fmod_ok();
}

bool FModManager::get_channel_group_pan(const std::string& CH_name, float* pan)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	*pan = i->second->current_pan;

	return true;
}

bool FModManager::set_channel_group_pan(const std::string& CH_name, float pan)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->setPan(pan);
	i->second->current_pan = pan;

	return is_Fmod_ok();
}

bool FModManager::get_channel_group_enabled(const std::string& CH_name, bool* enabled)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->getMute(enabled);


	*enabled = !(*enabled);

	return is_Fmod_ok();
}

bool FModManager::set_channel_group_enabled(const std::string& CH_name, bool enabled)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->setMute(!enabled);

	return is_Fmod_ok();
}

bool FModManager::get_channel_pitch(const std::string& CH_name, float* pitch)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->getPitch(pitch);

	return is_Fmod_ok();
}

bool FModManager::set_channel_pitch(const std::string& CH_name, float pitch)
{
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->setPitch(pitch);

	return is_Fmod_ok();
}

bool FModManager::get_channel_freq(const std::string& CH_name, float* freq)
{
	bool isplaying = false;
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}
	last_result_ = i->second->group_ptr->isPlaying(&isplaying);
	if (isplaying)
	{
		last_result_ = i->second->chn_ptr->getFrequency(freq);
	}
	else
	{
		*freq = NULL;
	}
	return is_Fmod_ok();
}

bool FModManager::set_channel_freq(const std::string& CH_name, float freq)
{
	bool isplaying = false;
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->isPlaying(&isplaying);
	if (isplaying)
	{
		last_result_ = i->second->chn_ptr->setFrequency(freq);
	}
	return is_Fmod_ok();
}

bool FModManager::get_playback_pos(const std::string& CH_name, unsigned int* pos)
{
	//FMOD::Channel* channel;
	bool isplaying = false;
	const auto i = channel_group_.find(CH_name);
	if (i == channel_group_.end())
	{
		return false;
	}

	last_result_ = i->second->group_ptr->isPlaying(&isplaying);
	if (isplaying)
	{
		last_result_ = i->second->chn_ptr->getPosition(pos, FMOD_TIMEUNIT_MS);
	}
	return is_Fmod_ok();
}

bool FModManager::create_sound(const std::string& Sound_name, const std::string& path, const int mode, const bool iscompress)
{
	FMOD::Sound* sound;
	int option = mode;

	if (!iscompress)
	{

		option |= FMOD_CREATESAMPLE;
	}
	else
	{

		option |= FMOD_CREATECOMPRESSEDSAMPLE;
	}

	last_result_ = system_->createSound(path.c_str(), option, nullptr, &sound);
	if (!is_Fmod_ok())
	{
		return false;
	}

	sound_.try_emplace(Sound_name, sound); //add to sound map

	return true;
}

bool FModManager::remove_sound(const std::string& Sound_name)
{
	const auto sound_i = sound_.find(Sound_name);
	if (sound_i == sound_.end())
	{
		return false;
	}

	last_result_ = sound_i->second->release();
	sound_.erase(sound_i);

	return is_Fmod_ok();
}

bool FModManager::play_sound(const std::string& Sound_name, const std::string& CH_name)
{
	FMOD::Channel* channel;

	const auto sound_i = sound_.find(Sound_name);
	const auto channel_i = channel_group_.find(CH_name);

	if (sound_i == sound_.end() || channel_i == channel_group_.end())
	{
		return false;
	}

	last_result_ = system_->playSound(sound_i->second, channel_i->second->group_ptr, true, &channel);
	if (!is_Fmod_ok())
	{
		return false;
	}
	channel_i->second->chn_ptr = channel;
	last_result_ = (*channel).setPaused(false);

	return is_Fmod_ok();
}

bool FModManager::stop_sound(const std::string& CH_name)
{
	FMOD::Channel* channel;

	const auto channel_i = channel_group_.find(CH_name);

	if (channel_i == channel_group_.end())
	{
		return false;
	}

	last_result_ = channel_i->second->group_ptr->stop();

	return is_Fmod_ok();
}

bool FModManager::get_speed(const std::string& Sound_name, float* speed)
{
	const auto sound_i = sound_.find(Sound_name);
	if (sound_i == sound_.end())
	{
		return false;
	}

	last_result_ = sound_i->second->getMusicSpeed(speed);

	return is_Fmod_ok();
}

bool FModManager::set_speed(const std::string& Sound_name, float speed)
{
	const auto sound_i = sound_.find(Sound_name);
	if (sound_i == sound_.end())
	{
		return false;
	}

	last_result_ = sound_i->second->setMusicSpeed(speed);

	return is_Fmod_ok();
}

bool FModManager::get_sound_name(const std::string& Sound_name, std::string* fname)
{
	char cname[512];
	const auto sound_i = sound_.find(Sound_name);
	if (sound_i == sound_.end())
	{
		return false;
	}

	last_result_ = sound_i->second->getName(cname, 512);
	fname->assign(cname);

	return is_Fmod_ok();
}

bool FModManager::get_sound_format(const std::string& Sound_name, std::string* type, std::string* format, int* chn, int* bit)
{
	const auto sound_i = sound_.find(Sound_name);
	FMOD_SOUND_TYPE t;
	FMOD_SOUND_FORMAT f;

	if (sound_i == sound_.end())
	{
		return false;
	}

	last_result_ = sound_i->second->getFormat(&t, &f, chn, bit);
	*type = FmodTypeEnumtoChar(t);
	*format = FmodFormatEnumtoChar(f);

	return is_Fmod_ok();
}

bool FModManager::get_sound_defualt(const std::string& Sound_name, float* freq, int* priority)
{
	const auto sound_i = sound_.find(Sound_name);
	if (sound_i == sound_.end())
	{
		return false;
	}

	last_result_ = sound_i->second->getDefaults(freq, priority);

	return is_Fmod_ok();
}

bool FModManager::get_sound_lengh(const std::string& Sound_name, unsigned int* length)
{
	const auto sound_i = sound_.find(Sound_name);
	if (sound_i == sound_.end())
	{
		return false;
	}

	last_result_ = sound_i->second->getLength(length, FMOD_TIMEUNIT_MS);

	return is_Fmod_ok();
}

bool FModManager::add_dsp(const std::string& CH_name, const std::string& fx_name)
{
	int num_dsp;
	const auto CH_i = channel_group_.find(CH_name);
	const auto dsp_i = dsp_.find(fx_name);

	if (CH_i == channel_group_.end() || dsp_i == dsp_.end())
	{
		return false;
	}

	last_result_ = CH_i->second->group_ptr->getNumDSPs(&num_dsp);
	if (!is_Fmod_ok())
	{
		return false;
	}

	last_result_ = CH_i->second->group_ptr->addDSP(num_dsp, dsp_i->second);

	return is_Fmod_ok();
}

bool FModManager::remove_dsp(const std::string& CH_name, const std::string& fx_name)
{
	const auto CH_i = channel_group_.find(CH_name);
	const auto dsp_i = dsp_.find(fx_name);

	if (CH_i == channel_group_.end() || dsp_i == dsp_.end())
	{
		return false;
	}

	last_result_ = CH_i->second->group_ptr->removeDSP(dsp_i->second);

	return is_Fmod_ok();
}

bool FModManager::create_dsp(const std::string& DSP_name, FMOD_DSP_TYPE DSP_type)
{
	FMOD::DSP* dsp;
	last_result_ = system_->createDSPByType(DSP_type, &dsp);
	if (!is_Fmod_ok())
	{
		return false;
	}

	dsp_.try_emplace(DSP_name, dsp);

	return true;
}

bool FModManager::get_dsp(const std::string& DSP_name, FMOD::DSP** dsp)
{
	const auto dsp_i = dsp_.find(DSP_name);
	if (dsp_i == dsp_.end())
	{
		return false;
	}

	*dsp = dsp_i->second;

	return true;
}

bool FModManager::get_dsp_param(const std::string& DSP_name, const int index, float* value, char* valuestr, const int valuestrlen)
{
	const auto dsp_i = dsp_.find(DSP_name);
	if (dsp_i == dsp_.end())
	{
		return false;
	}
	last_result_ = dsp_i->second->getParameterFloat(index, value, valuestr, valuestrlen);

	return is_Fmod_ok();
}

bool FModManager::set_dsp_param(const std::string& DSP_name, const int index, const float value)
{
	const auto dsp_i = dsp_.find(DSP_name);
	if (dsp_i == dsp_.end())
	{
		return false;
	}
	last_result_ = dsp_i->second->setParameterFloat(index, value);

	return is_Fmod_ok();
	return false;
}

bool FModManager::is_Fmod_ok(const bool show_error) const
{
	if (last_result_ != FMOD_OK)
	{
		std::cout << "FMOD Error: " << last_result_ << " error code: " << FMOD_ErrorString(last_result_) << std::endl;
	}
	return last_result_ == FMOD_OK;
}

FModManager::CHgroup::CHgroup()
{
	group_ptr = nullptr;
	current_pan = 0.0f;
	dsp_pitch = 1.0f;
	chn_ptr = nullptr;
}

const char* FModManager::FmodTypeEnumtoChar(FMOD_SOUND_TYPE t) noexcept
{
	switch (t)
	{
	case FMOD_SOUND_TYPE_UNKNOWN:				return "FMOD_SOUND_TYPE_UNKNOWN";
	case FMOD_SOUND_TYPE_AIFF:					return "FMOD_SOUND_TYPE_AIFF";
	case FMOD_SOUND_TYPE_ASF:					return "FMOD_SOUND_TYPE_ASF";
	case FMOD_SOUND_TYPE_DLS:					return "FMOD_SOUND_TYPE_DLS";
	case FMOD_SOUND_TYPE_FLAC:					return "FMOD_SOUND_TYPE_FLAC";
	case FMOD_SOUND_TYPE_FSB:					return "FMOD_SOUND_TYPE_FSB";
	case FMOD_SOUND_TYPE_IT:					return "FMOD_SOUND_TYPE_IT";
	case FMOD_SOUND_TYPE_MIDI:					return "FMOD_SOUND_TYPE_MIDI";
	case FMOD_SOUND_TYPE_MOD:					return "FMOD_SOUND_TYPE_MOD";
	case FMOD_SOUND_TYPE_MPEG:					return "FMOD_SOUND_TYPE_MPEG";
	case FMOD_SOUND_TYPE_OGGVORBIS:				return "FMOD_SOUND_TYPE_OGGVORBIS";
	case FMOD_SOUND_TYPE_PLAYLIST:				return "FMOD_SOUND_TYPE_PLAYLIST";
	case FMOD_SOUND_TYPE_RAW:					return "FMOD_SOUND_TYPE_RAW";
	case FMOD_SOUND_TYPE_S3M:					return "FMOD_SOUND_TYPE_S3M";
	case FMOD_SOUND_TYPE_USER:					return "FMOD_SOUND_TYPE_USER";
	case FMOD_SOUND_TYPE_WAV:					return "FMOD_SOUND_TYPE_WAV";
	case FMOD_SOUND_TYPE_XM:					return "FMOD_SOUND_TYPE_XM";
	case FMOD_SOUND_TYPE_XMA:					return "FMOD_SOUND_TYPE_XMA";
	case FMOD_SOUND_TYPE_AUDIOQUEUE:			return "FMOD_SOUND_TYPE_AUDIOQUEUE";
	case FMOD_SOUND_TYPE_AT9:					return "FMOD_SOUND_TYPE_AT9";
	case FMOD_SOUND_TYPE_VORBIS:				return "FMOD_SOUND_TYPE_VORBIS";
	case FMOD_SOUND_TYPE_MEDIA_FOUNDATION:		return "FMOD_SOUND_TYPE_MEDIA_FOUNDATION";
	case FMOD_SOUND_TYPE_MEDIACODEC:			return "FMOD_SOUND_TYPE_MEDIACODEC";
	case FMOD_SOUND_TYPE_FADPCM:				return "FMOD_SOUND_TYPE_FADPCM";
	case FMOD_SOUND_TYPE_OPUS:					return "FMOD_SOUND_TYPE_OPUS";
	case FMOD_SOUND_TYPE_MAX:					return "FMOD_SOUND_TYPE_MAX";
	case FMOD_SOUND_TYPE_FORCEINT:				return "";
	default:									return "";
	}
}

const char* FModManager::FmodFormatEnumtoChar(FMOD_SOUND_FORMAT f) noexcept
{
	switch (f)
	{
	case FMOD_SOUND_FORMAT_NONE:				return "FMOD_SOUND_FORMAT_NONE";
	case FMOD_SOUND_FORMAT_PCM8:				return "FMOD_SOUND_FORMAT_PCM8";
	case FMOD_SOUND_FORMAT_PCM16:				return "FMOD_SOUND_FORMAT_PCM16";
	case FMOD_SOUND_FORMAT_PCM24:				return "FMOD_SOUND_FORMAT_PCM24";
	case FMOD_SOUND_FORMAT_PCM32:				return "FMOD_SOUND_FORMAT_PCM32";
	case FMOD_SOUND_FORMAT_PCMFLOAT:			return "FMOD_SOUND_FORMAT_PCMFLOAT";
	case FMOD_SOUND_FORMAT_BITSTREAM:			return "FMOD_SOUND_FORMAT_BITSTREAM";
	case FMOD_SOUND_FORMAT_MAX:					return "FMOD_SOUND_FORMAT_MAX";
	case FMOD_SOUND_FORMAT_FORCEINT:			return "";
	default:									return "";
	}
}