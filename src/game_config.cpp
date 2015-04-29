/* --------------------------------------------------------------------
EXTREME TUXRACER

Copyright (C) 2010 Extreme Tuxracer Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
---------------------------------------------------------------------*/

/*
If you want to add a new option, do this:
First add the option to the TParam struct (game_config.h).

Then edit the below functions:

- LoadConfigFile. Use
	SPIntN for integer and boolean values
	SPStrN for strings.
	The first value is always 'line', the second defines the tag within the
	brackets [ ], and the last value is the default.

- SetConfigDefaults. These values are used as long as no options file exists.
	It's a good idea to use the same values as the defaults in LoadConfigFile.

- SaveConfigFile. See the other entries; it should be self-explanatory.
	If an options file exists, you will have to change any value at runtime
	on the configuration screen to overwrite the file. Then you will see the
	new entry.
*/

#ifdef HAVE_CONFIG_H
#include <etr_config.h>
#endif

#include "game_config.h"
#include "spx.h"
#include "translation.h"
#include "physics.h"

#define DEFAULT_CAMERA_DIST 3.5
#define DEFAULT_CAMERA_ANGLE -26
#define DEFAULT_FLY_AMOUNT 30
#define DEFAULT_FLY_TURN 200
#define DEFAULT_FLY_SPEED 25
#define DEFAULT_SLIDE_DELTA 0.16
#define DEFAULT_ENV 2

TParam param;


void LoadConfigFile () {
	CSPList list(4);
	if (!list.Load (param.configfile)) {
		Message ("Could not load 'options'");
		return;
	}

	for (size_t i=0; i<list.Count(); i++) {
		const string& line = list.Line(i);

		param.fullscreen = SPBoolN (line, "fullscreen", false);
		param.res_type = SPIntN (line, "res_type", 0);
		param.perf_level = SPIntN (line, "detail_level", 0);
		param.language = SPIntN (line, "language", 0);
		param.sound_volume = SPIntN (line, "sound_volume", 100);
		param.music_volume = SPIntN (line, "music_volume", 20);

		param.forward_clip_distance = SPIntN (line, "forward_clip_distance", 80);
		param.backward_clip_distance = SPIntN (line, "backward_clip_distance", 20);
		param.fov = SPIntN (line, "fov", 60);
		param.bpp_mode = SPIntN (line, "bpp_mode", 1);
		param.tree_detail_distance = SPIntN (line, "tree_detail_distance", 20);
		param.tux_sphere_divisions = SPIntN (line, "tux_sphere_divisions", 10);
		param.tux_shadow_sphere_divisions = SPIntN (line, "tux_shadow_sphere_div", 3);
		param.course_detail_level = SPIntN (line, "course_detail_level", 75);

		param.use_papercut_font = SPIntN (line, "use_papercut_font", 1);
		param.ice_cursor = SPBoolN (line, "ice_cursor", true);
		param.full_skybox = SPBoolN (line, "full_skybox", true);
		param.no_skybox = SPBoolN (line, "no_skybox", false);
		param.audio_freq = SPIntN (line, "audio_freq", 22050);
		param.audio_buffer_size = SPIntN (line, "audio_buffer_size", 512);
		param.use_quad_scale = SPBoolN (line, "use_quad_scale", false);

		param.menu_music = SPStrN (line, "menu_music", "start_1");
		param.credits_music = SPStrN (line, "credits_music", "credits_1");
		param.config_music = SPStrN (line, "config_music", "options_1");

		param.no_vsync = SPBoolN(line, "no_vsync", false);
		param.no_prediction = SPBoolN(line, "no_prediction", false);
		param.no_timewarp = SPBoolN(line, "no_timewarp", false);
		param.no_timewarp_spinwaits = SPBoolN(line, "no_timewarp_spinwaits", false);
		param.no_hq_distortion = SPBoolN(line, "no_hq_distortion", true);
		param.no_compute_shader = SPBoolN(line, "no_compute_shader", true);
		param.no_restore = SPBoolN(line, "no_restore", false);
		param.console_dump = SPBoolN(line, "console_dump", false);
		param.use_fxaa = SPBoolN(line, "use_fxaa", true);
		param.ipd_multiplier = SPFloatN(line, "ipd_multiplier", 1);
		//float distance_warp = param.ipd_multiplier/2.0f; // need radius
		param.player_min_speed = SPFloatN(line, "player_min_speed", MIN_TUX_SPEED);
		param.player_frict_speed = SPFloatN(line, "player_frict_speed", MIN_FRICT_SPEED); // * ((float)param.ipd_multiplier/2));
		param.camera_distance = SPFloatN(line, "camera_distance", DEFAULT_CAMERA_DIST);
		param.camera_angle = SPFloatN(line, "camera_angle", DEFAULT_CAMERA_ANGLE);
		param.fly_amount = SPFloatN(line, "fly_amount", DEFAULT_FLY_AMOUNT);
		param.fly_turn = SPFloatN(line, "fly_turn", DEFAULT_FLY_TURN);
		param.fly_speed = SPFloatN(line, "fly_speed", DEFAULT_FLY_SPEED);
		param.slide_delta = SPFloatN(line, "slide_delta", DEFAULT_SLIDE_DELTA);
		param.default_env = SPIntN(line, "default_env", DEFAULT_ENV);
		param.dire_straits_tux = SPBoolN(line, "dire_straits_tux", 1);
	}
}

void SetConfigDefaults () {
	param.fullscreen = false;
	// jdt: default of 1920x1080 causes issues switching to rift.  
	param.res_type = 0; // 0=auto / 1=800x600 / 2=1024x768 ...
	param.perf_level = 1;	// detail level
	param.language = string::npos; // If language is set to npos, ETR will try to load default system language
	param.sound_volume = 100;
	param.music_volume = 0;

	// ---------------------------------------

	param.forward_clip_distance = 80;
	param.backward_clip_distance = 30;
	param.fov = 95;
	param.bpp_mode = 0;
	param.tree_detail_distance = 30;
	param.tux_sphere_divisions = 10;
	param.tux_shadow_sphere_divisions = 3;
	param.course_detail_level = 75;
	param.audio_freq = 22050;
	param.audio_buffer_size = 512;

	param.use_papercut_font = 1;
	param.ice_cursor = true;
	param.full_skybox = true;
	param.no_skybox = false;
	param.use_quad_scale = false;

	param.menu_music = "start_1";
	param.credits_music = "credits_1";
	param.config_music = "options_1";

	param.no_vsync = false;
	param.no_prediction = false;
	param.no_timewarp = false;
	param.no_timewarp_spinwaits = false;
	param.no_hq_distortion = true;
	param.no_compute_shader = true;
	param.no_restore = false;
	param.use_fxaa = true;

	param.ipd_multiplier = 1;
	//float distance_warp = param.ipd_multiplier/2.0f;
	param.player_min_speed = MIN_TUX_SPEED;
	param.player_frict_speed = MIN_FRICT_SPEED; // * distance_warp;
	param.camera_distance = DEFAULT_CAMERA_DIST;
	param.camera_angle = DEFAULT_CAMERA_ANGLE;
	param.fly_amount = DEFAULT_FLY_AMOUNT;
	param.fly_turn = DEFAULT_FLY_TURN;
	param.fly_speed = DEFAULT_FLY_SPEED;
	param.slide_delta = DEFAULT_SLIDE_DELTA;
	param.dire_straits_tux = true;

	param.default_env = DEFAULT_ENV;

	param.console_dump = false; // true for fps,tree,item count dumps.
}


void AddItem (CSPList &list, const string& tag, const string& content) {
	string item = "  [" +tag + "] " + content;
	list.Add (item);
}

void AddIntItem (CSPList &list, const string& tag, int val) {
	string vs = Int_StrN (val);
	AddItem (list, tag, vs);
}

void AddFloatItem (CSPList &list, const string& tag, float val) {
	string vs = Float_StrN (val, 2);
	AddItem (list, tag, vs);
}

void AddComment (CSPList &list, const string& comment) {
	string line = "# " + comment;
	list.Add (line);
}

void SaveConfigFile () {
	CSPList liste (512);

	liste.Add ("# ------------------------------------------------------------------");
	liste.Add ("#   The first group of params can be adjusted ");
	liste.Add ("#   on the configuration screen, too");
	liste.Add ("# ------------------------------------------------------------------");
	liste.Add ("");

	AddComment (liste, "Full-screen mode [0...1]");
	AddIntItem (liste, "fullscreen", param.fullscreen);
	liste.Add ("");

	AddComment (liste, "Screen resolution [0...9]");
	AddComment (liste, "0 = auto, 1 = 800x600, 2 = 1024x768");
	AddComment (liste, "3 = 1152x864, 4 = 1280x960, 5 = 1280x1024");
	AddComment (liste, "6 = 1360x768, 7 = 1400x1050, 8 = 1440x900, 9=1680x1050");
	AddIntItem (liste, "res_type", (int)param.res_type);
	liste.Add ("");

	AddComment (liste, "Level of details [1...3]");
	AddComment (liste, "1 = best performance, 3 = best appearance");
	AddIntItem (liste, "detail_level", param.perf_level);
	liste.Add ("");

	AddComment (liste, "Language code [0...]");
	AddComment (liste, "0 = English etc.");
	AddIntItem (liste, "language", (int)param.language);
	liste.Add ("");

	AddComment (liste, "Sound volume [0...120]");
	AddComment (liste, "Sounds are the terrain effects or the pickup noise.");
	AddIntItem (liste, "sound_volume", param.sound_volume);
	liste.Add ("");

	AddComment (liste, "Volume of the background music [0...120]");
    AddIntItem (liste, "music_volume", param.music_volume);
	liste.Add ("");

	liste.Add ("# ------------------------------------------------------------------");
	liste.Add ("#   The second group of params must be adjusted in this file.");
	liste.Add ("# ------------------------------------------------------------------");
	liste.Add ("");

	AddComment (liste, "Forward clipping distance");
	AddComment (liste, "Controls how far ahead of the camera the course");
	AddComment (liste, "is rendered. Larger values mean that more of the course is");
	AddComment (liste, "rendered, resulting in slower performance. Decreasing this ");
	AddComment (liste, "value is an effective way to improve framerates.");
	AddIntItem (liste, "forward_clip_distance", param.forward_clip_distance);
	liste.Add ("");

	AddComment (liste, "Backward clipping distance");
	AddComment (liste, "Some objects aren't yet clipped to the view frustum, ");
	AddComment (liste, "so this value is used to control how far up the course these ");
	AddComment (liste, "objects are drawn.");
	AddIntItem (liste, "backward_clip_distance", param.backward_clip_distance);
	liste.Add ("");

	AddComment (liste, "Field of View of the camera");
	AddIntItem (liste, "fov", param.fov);
	liste.Add ("");

	AddComment (liste, "Bpp mode - bits per pixel [0...2]");
	AddComment (liste, "Controls the color depth of the OpenGL window");
	AddComment (liste, "0 = use current bpp setting of operating system,");
	AddComment (liste, "1 = 16 bpp, 2 = 32 bpp");
	AddIntItem (liste, "bpp_mode", param.bpp_mode);
	liste.Add ("");

	AddComment (liste, "Tree detail distance");
	AddComment (liste, "Controls how far up the course the trees are drawn crosswise.");
	AddIntItem (liste, "tree_detail_distance", param.tree_detail_distance);
	liste.Add ("");

	AddComment (liste, "Tux sphere divisions");
	AddComment (liste, "Controls how detailled the character is drawn");
	AddIntItem (liste, "tux_sphere_divisions", param.tux_sphere_divisions);
	liste.Add ("");

	AddComment (liste, "Tux shadow sphere divisions");
	AddComment (liste, "The same but for the shadow of the character");
	AddIntItem (liste, "tux_shadow_sphere_div", param.tux_shadow_sphere_divisions);
	liste.Add ("");

	AddComment (liste, "Detail level of the course");
	AddComment (liste, "This param is used for the quadtree and controls the");
	AddComment (liste, "LOD of the algorithm. ");
	AddIntItem (liste, "course_detail_level", param.course_detail_level);
	liste.Add ("");

	AddComment (liste, "Font type [0...2]");
	AddComment (liste, "0 = always arial-like font,");
	AddComment (liste, "1 = papercut font on the menu screens");
	AddComment (liste, "2 = papercut font for the hud display, too");
	AddIntItem (liste, "use_papercut_font", param.use_papercut_font);
	liste.Add ("");

	AddComment (liste, "Cursor type [0...1]");
	AddComment (liste, "0 = normal cursor (arrow), 1 = icicle");
	AddIntItem (liste, "ice_cursor", param.ice_cursor);
	liste.Add ("");

	AddComment (liste, "Draw full skybox [0...1]");
	AddComment (liste, "A normal skybox consists of 6 textures. In Tuxracer");
	AddComment (liste, "3 textures are invisible (top, bottom and back).");
	AddComment (liste, "These textures needn't be drawn.");
	AddIntItem (liste, "full_skybox", param.full_skybox);
	AddIntItem (liste, "no_skybox", param.no_skybox);
	liste.Add ("");

	AddComment (liste, "Audio frequency");
	AddComment (liste, "Typical values are 11025, 22050 ...");
	AddIntItem (liste, "audio_freq", param.audio_freq);
	liste.Add ("");

	AddComment (liste, "Size of audio buffer");
	AddComment (liste, "Typical values are 512, 1024, 2048 ...");
	AddIntItem (liste, "audio_buffer_size", param.audio_buffer_size);
	liste.Add ("");

	AddComment (liste, "Select the music:");
	AddComment (liste, "(the racing music is defined by a music theme)");
	AddItem (liste, "menu_music", param.menu_music);
	AddItem (liste, "credits_music", param.credits_music);
	AddItem (liste, "config_music", param.config_music);
	liste.Add ("");

	AddComment (liste, "Use sqare root of scale factors for menu screens [0...1]");
	AddComment (liste, "Exprimental: these factors reduce the effect of screen scaling.");
	AddComment (liste, "The widgets are closer to their default sizes.");
	AddIntItem (liste, "use_quad_scale", param.use_quad_scale);
	liste.Add ("");

	AddComment (liste, "Oculus Rift settings.");
	AddIntItem(liste, "no_vsync", param.no_vsync);
	AddIntItem(liste, "no_prediction", param.no_prediction);
	AddIntItem(liste, "no_timewarp", param.no_timewarp);
	AddIntItem(liste, "no_timewarp_spinwaits", param.no_timewarp_spinwaits);
	AddIntItem(liste, "no_hq_distortion", param.no_hq_distortion);
	AddIntItem(liste, "no_compute_shader", param.no_compute_shader);
	AddIntItem(liste, "no_restore", param.no_restore);
	liste.Add ("");

	AddComment (liste, "Antialiasing.");
	AddIntItem(liste, "use_fxaa", param.use_fxaa);
	liste.Add ("");

	AddComment (liste, "Gameplay settings.");
	AddFloatItem(liste, "ipd_multiplier", param.ipd_multiplier);
	AddFloatItem(liste, "player_frict_speed", param.player_frict_speed);
	AddFloatItem(liste, "camera_distance", param.camera_distance);
	AddFloatItem(liste, "camera_angle", param.camera_angle);
	AddFloatItem(liste, "fly_amount", param.fly_amount);
	AddFloatItem(liste, "fly_turn", param.fly_turn);
	AddFloatItem(liste, "fly_speed", param.fly_speed);
	AddFloatItem(liste, "slide_delta", param.slide_delta);
	liste.Add ("");

	AddComment (liste, "Render Tux with cubes to reduce polygon count [0,1]:");
	AddIntItem(liste, "dire_straits_tux", param.dire_straits_tux);
    liste.Add("");

	AddIntItem(liste, "default_env", param.default_env);
    liste.Add("");

	AddComment (liste, "Dump extra debug info to the console.");
	AddIntItem(liste, "console_dump", param.console_dump);
	liste.Add ("");



	// ---------------------------------------
	liste.Save (param.configfile);
}

// --------------------------------------------------------------------

void InitConfig (const char *arg0) {
	// the progdir is always the current dir.
	// jdt: TODO: change for proper distribution.
	param.config_dir = "config";
	param.data_dir = "data";
	param.configfile = param.config_dir + SEP + "options.txt";

#if 0
	char buff[256];

	if (strcmp (arg0, "./etr") == 0) {		// start from work directory
		char *s = getcwd (buff, 256);
		if (s==NULL) {};
	} else {                                        // start with full path
		strcpy (buff, arg0);
		if (strlen (buff) > 5) {
                  buff[strlen(buff)-3] = 0;
                }
	}

	param.prog_dir = buff;

	struct passwd *pwent = getpwuid (getuid ());
	param.config_dir = pwent->pw_dir;
	param.config_dir += SEP;
	param.config_dir += CONFIG_DIR;
	// or: param.config_dir = param.prog_dir + SEP + "config";
    if (!DirExists (param.config_dir.c_str()))
		mkdir (param.config_dir.c_str(), 0775);
	// jdt: frustrated trying to figure out how this was supposed to work
    //if (!DirExists (param.data_dir.c_str())) {
        param.data_dir = ETR_DATA_DIR;
        //param.data_dir += SEP;
        //param.data_dir += "etr";
	//}
	// param.data_dir = param.prog_dir + SEP + "data";
	param.configfile = param.config_dir + SEP + "options";
#endif

	param.screenshot_dir = param.data_dir + SEP + "screenshots";
	param.obj_dir = param.data_dir + SEP + "objects";
	param.env_dir2 = param.data_dir + SEP + "env";
	param.char_dir = param.data_dir + SEP + "char";
	param.terr_dir = param.data_dir + SEP + "terrains";
	param.tex_dir = param.data_dir + SEP + "textures";
	param.common_course_dir = param.data_dir + SEP + "courses";
	param.sounds_dir = param.data_dir + SEP + "sounds";
	param.music_dir = param.data_dir + SEP + "music";
	param.font_dir = param.data_dir + SEP + "fonts";
	param.trans_dir = param.data_dir + SEP + "translations";
	param.player_dir = param.data_dir + SEP + "players";

	param.ui_snow = true;
	param.view_mode = FOLLOW;
	param.display_fps = false;
	param.show_hud = false;
	param.attach_hud_to_face = false;

	if (FileExists (param.configfile)) {
		LoadConfigFile ();
	} else {
		SetConfigDefaults ();
		SaveConfigFile ();
	}
	/*string playerfile = param.config_dir + SEP + PLAYER_FILE;
	if (FileExists (playerfile)) {
	} else {
	}*/
}
