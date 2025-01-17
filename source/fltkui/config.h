#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct {

	// Video
	int video_filter;
	int video_scale_factor;
	int video_palette_mode;
	int video_decoder;
	int video_brightness;
	int video_saturation;
	int video_contrast;
	int video_hue;
	int video_ntsc_mode;
	int video_ntsc_sharpness;
	int video_ntsc_resolution;
	int video_ntsc_bleed;
	int video_ntsc_artifacts;
	int video_ntsc_fringing;
	int video_xbr_corner_rounding;
	bool video_linear_filter;
	bool video_tv_aspect;
	bool video_unmask_overscan;
	bool video_fullscreen;
	bool video_stretch_aspect;
	bool video_unlimited_sprites;
	bool video_xbr_pixel_blending;

	// Audio
	bool audio_stereo;
	int audio_sample_rate;
	int audio_volume;
	int audio_vol_sq1;
	int audio_vol_sq2;
	int audio_vol_tri;
	int audio_vol_noise;
	int audio_vol_dpcm;
	int audio_vol_fds;
	int audio_vol_mmc5;
	int audio_vol_vrc6;
	int audio_vol_vrc7;
	int audio_vol_n163;
	int audio_vol_s5b;

	// Timing
	int timing_speed;
	int timing_ffspeed;
	int timing_turbopulse;

	// Split Timer
	bool autorun_timer;

	// Misc
	int misc_default_system;
	bool misc_soft_patching;
	bool misc_genie_distortion;
	bool misc_disable_cursor;
	bool misc_disable_cursor_special;
	bool misc_config_pause;
	int misc_power_state;
	int misc_homebrew_exit;
	int misc_homebrew_stdout;
	int misc_homebrew_stderr;
} settings_t;

void config_file_read(const char *nstdir);
void config_file_write(const char *nstdir);
void config_set_default();
static int config_match(void* user, const char* section, const char* name, const char* value);

extern settings_t conf;
#endif
