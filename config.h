/* taken from https://github.com/djpohly/dwl/issues/466 */
#define color(hex)    { ((hex >> 24) & 0xff) / 255.0f, \
                        ((hex >> 16) & 0xff) / 255.0f, \
                        ((hex >> 8) & 0xff) / 255.0f, \
                        (hex & 0xff) / 255.0f }
/* appearance */
static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 2;  /* border pixel of windows */
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"jetbrainsmono nerd font:style=bold:size=12"};
static const float rootcolor[]             = color(0x000000ff);
/* this conforms to the xdg-protocol. set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.0f, 0.0f, 0.0f, 1.0f}; /* you can also use glsl colors */
static uint32_t colors[][3]                = {
    /*               fg          bg          border    */
    [schemenorm] = { 0xbbbbbbff, 0x222222ff, 0x595959aa },
    [schemesel]  = { 0xeeeeeeff, 0x005577ff, 0x33ccffee },
    [schemeurg]  = { 0,          0,          0x770000ff },
};

/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* logging */
static int log_level = wlr_error;

static const rule rules[] = {
	/* app_id             title       tags mask     isfloating   monitor */
	{ "gimp_example",     null,       0,            1,           -1 }, /* start on currently visible tags floating, not tiled */
	{ "firefox_example",  null,       1 << 8,       0,           -1 }, /* start on only tag "9" */
    /* default/example rule: can be changed but cannot be eliminated; at least one rule must exist */
};

/* layout(s) */
static const layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      null },    /* no layout function means floating behavior */
	{ "[m]",      monocle },
};

/* monitors */
/* (x=-1, y=-1) is reserved as an "autoconfigure" monitor position indicator
 * warning: negative values other than (-1, -1) cause problems with xwayland clients due to
 * https://gitlab.freedesktop.org/xorg/xserver/-/issues/899 */
static const monitorrule monrules[] = {
   /* name        mfact  nmaster scale layout       rotate/reflect                x    y
    * example of a hidpi laptop monitor:
    { "edp-1",    0.5f,  1,      2,    &layouts[0], wl_output_transform_normal,   -1,  -1 }, */
	{ null,       0.55f, 1,      1,    &layouts[0], wl_output_transform_normal,   -1,  -1 },
	/* default monitor rule: can be changed but cannot be eliminated; at least one monitor rule must exist */
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    .layout = "us,ru",
    .options = "grp:caps_toggle",
};

static const int repeat_rate = 25;
static const int repeat_delay = 500;

/* trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* you can choose between:
libinput_config_scroll_no_scroll
libinput_config_scroll_2fg
libinput_config_scroll_edge
libinput_config_scroll_on_button_down
*/
static const enum libinput_config_scroll_method scroll_method = libinput_config_scroll_2fg;

/* you can choose between:
libinput_config_click_method_none
libinput_config_click_method_button_areas
libinput_config_click_method_clickfinger
*/
static const enum libinput_config_click_method click_method = libinput_config_click_method_button_areas;

/* you can choose between:
libinput_config_send_events_enabled
libinput_config_send_events_disabled
libinput_config_send_events_disabled_on_external_mouse
*/
static const uint32_t send_events_mode = libinput_config_send_events_enabled;

/* you can choose between:
libinput_config_accel_profile_flat
libinput_config_accel_profile_adaptive
*/
static const enum libinput_config_accel_profile accel_profile = libinput_config_accel_profile_adaptive;
static const double accel_speed = 0.0;

/* you can choose between:
libinput_config_tap_map_lrm -- 1/2/3 finger tap maps to left/right/middle
libinput_config_tap_map_lmr -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = libinput_config_tap_map_lrm;

/* if you want to use the windows key for modkey, use wlr_modifier_logo */
#define modkey wlr_modifier_logo

#define tagkeys(key,skey,tag) \
	{ modkey,                    key,            view,            {.ui = 1 << tag} }, \
	{ modkey|wlr_modifier_ctrl,  key,            toggleview,      {.ui = 1 << tag} }, \
	{ modkey|wlr_modifier_shift, skey,           tag,             {.ui = 1 << tag} }, \
	{ modkey|wlr_modifier_ctrl|wlr_modifier_shift,skey,toggletag, {.ui = 1 << tag} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define shcmd(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, null } }

/* commands */
static const char *termcmd[] = { "foot", null };
static const char *filemanager[] = { "pcmanfm", null };
static const char *menucmd[] = { "wmenu-run", "-f", "jetbrainsmono nerd font 12", "-l", "10", null };
static const char *browser[] = { "librewolf", null };
static const char *lockscreen[] = { "hyprlock", null };
static const char *screenshotcmd[] = { "sh", "-c", "grim -g \"$(slurp)\" - | tee /home/nikolas/pictures/screenshots/$(date +'%y-%m-%d_%h-%m-%s').png | wl-copy", null };
static const char *screenshotfcmd[] = { "sh", "-c", "grim -o \"$(slurp -p -f %o | tr -d '\"')\" - | tee /home/nikolas/pictures/screenshots/$(date +'%y-%m-%d_%h-%m-%s').png | wl-copy", null };
static const char *volupcmd[]       = { "wpctl", "set-volume", "-l", "1", "@default_audio_sink@", "5%+", null };
static const char *voldowncmd[]     = { "wpctl", "set-volume", "@default_audio_sink@", "5%-", null };
static const char *volmutecmd[]     = { "wpctl", "set-mute", "@default_audio_sink@", "toggle", null };
static const char *micmutecmd[]     = { "wpctl", "set-mute", "@default_audio_source@", "toggle", null };
static const char *brightupcmd[]    = { "brightnessctl", "-e4", "-n2", "set", "5%+", null };
static const char *brightdowncmd[]  = { "brightnessctl", "-e4", "-n2", "set", "5%-", null };

static const key keys[] = {
	/* note that shift changes certain key codes: 2 -> at, etc. */
	/* modifier                  key                  function          argument */
	{ modkey,                    xkb_key_r,           spawn,            {.v = menucmd} },
	{ modkey,                    xkb_key_q,           spawn,            {.v = termcmd} },
	{ modkey,                    xkb_key_n,           spawn,            {.v = lockscreen} },
	{ modkey,                    xkb_key_e,           spawn,            {.v = filemanager} },
    { modkey,                    xkb_key_w,           spawn,            shcmd("~/.scripts/wallpaper.sh") },
	{ modkey,                    xkb_key_b,           spawn,            {.v = browser} },
	{ modkey,                    xkb_key_i,           incnmaster,       {.i = +1} },
	{ modkey,                    xkb_key_u,           incnmaster,       {.i = -1} },
	{ modkey,                    xkb_key_h,           setmfact,         {.f = -0.05f} },
	{ modkey,                    xkb_key_l,           setmfact,         {.f = +0.05f} },
	{ modkey,                    xkb_key_return,      zoom,             {0} },
	{ modkey,                    xkb_key_tab,         view,             {0} },
	{ modkey,                    xkb_key_c,           killclient,       {0} },
	{ modkey,                    xkb_key_t,           setlayout,        {.v = &layouts[0]} },
	{ modkey|wlr_modifier_shift, xkb_key_f,           setlayout,        {.v = &layouts[1]} },
	{ modkey,                    xkb_key_m,           setlayout,        {.v = &layouts[2]} },
	{ modkey,                    xkb_key_space,       setlayout,        {0} },
	{ modkey,                    xkb_key_v,           togglefloating,   {0} },
	{ modkey,                    xkb_key_f,           togglefullscreen, {0} },
	{ modkey,                    xkb_key_0,           view,             {.ui = ~0} },
	{ modkey|wlr_modifier_shift, xkb_key_parenright,  tag,              {.ui = ~0} },
	{ modkey,                    xkb_key_comma,       focusmon,         {.i = wlr_direction_left} },
	{ modkey,                    xkb_key_period,      focusmon,         {.i = wlr_direction_right} },
	{ modkey|wlr_modifier_shift, xkb_key_less,        tagmon,           {.i = wlr_direction_left} },
	{ modkey|wlr_modifier_shift, xkb_key_greater,     tagmon,           {.i = wlr_direction_right} },
	{ modkey,                    xkb_key_j,           focusstack,       {.i = +1} },
	{ modkey,                    xkb_key_k,           focusstack,       {.i = -1} },
	tagkeys(          xkb_key_1, xkb_key_exclam,                        0),
	tagkeys(          xkb_key_2, xkb_key_at,                            1),
	tagkeys(          xkb_key_3, xkb_key_numbersign,                    2),
	tagkeys(          xkb_key_4, xkb_key_dollar,                        3),
	tagkeys(          xkb_key_5, xkb_key_percent,                       4),
	tagkeys(          xkb_key_6, xkb_key_asciicircum,                   5),
	tagkeys(          xkb_key_7, xkb_key_ampersand,                     6),
	tagkeys(          xkb_key_8, xkb_key_asterisk,                      7),
	tagkeys(          xkb_key_9, xkb_key_parenleft,                     8),
	{ modkey|wlr_modifier_shift, xkb_key_q,           quit,             {0} },
    { wlr_modifier_ctrl|wlr_modifier_alt,   xkb_key_s,                      spawn,          {.v = screenshotcmd } },
    { modkey|wlr_modifier_alt,              xkb_key_s,                      spawn,          {.v = screenshotfcmd } },
	{ 0,                                    xkb_key_xf86audioraisevolume,   spawn,          {.v = volupcmd } },
	{ 0,                                    xkb_key_xf86audiolowervolume,   spawn,          {.v = voldowncmd } },
	{ 0,                                    xkb_key_xf86audiomute,          spawn,          {.v = volmutecmd } },
	{ 0,                                    xkb_key_xf86audiomicmute,       spawn,          {.v = micmutecmd } },
	{ 0,                                    xkb_key_xf86monbrightnessup,    spawn,          {.v = brightupcmd } },
	{ 0,                                    xkb_key_xf86monbrightnessdown,  spawn,          {.v = brightdowncmd } },

	/* ctrl-alt-backspace and ctrl-alt-fx used to be handled by x server */
	{ wlr_modifier_ctrl|wlr_modifier_alt,xkb_key_terminate_server, quit, {0} },
	/* ctrl-alt-fx is used to switch to another vt, if you don't know what a vt is
	 * do not remove them.
	 */
#define chvt(n) { wlr_modifier_ctrl|wlr_modifier_alt,xkb_key_xf86switch_vt_##n, chvt, {.ui = (n)} }
	chvt(1), chvt(2), chvt(3), chvt(4), chvt(5), chvt(6),
	chvt(7), chvt(8), chvt(9), chvt(10), chvt(11), chvt(12),
};

static const button buttons[] = {
	{ clkltsymbol, 0,      btn_left,   setlayout,      {.v = &layouts[0]} },
	{ clkltsymbol, 0,      btn_right,  setlayout,      {.v = &layouts[2]} },
	{ clktitle,    0,      btn_middle, zoom,           {0} },
	{ clkstatus,   0,      btn_middle, spawn,          {.v = termcmd} },
	{ clkclient,   modkey, btn_left,   moveresize,     {.ui = curmove} },
	{ clkclient,   modkey, btn_middle, togglefloating, {0} },
	{ clkclient,   modkey, btn_right,  moveresize,     {.ui = curresize} },
	{ clktagbar,   0,      btn_left,   view,           {0} },
	{ clktagbar,   0,      btn_right,  toggleview,     {0} },
	{ clktagbar,   modkey, btn_left,   tag,            {0} },
	{ clktagbar,   modkey, btn_right,  toggletag,      {0} },
};
