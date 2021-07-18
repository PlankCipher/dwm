/* See LICENSE file for copyright and license details. */

static const unsigned int borderpx  = 3;
static const unsigned int snap      = 5;

static const int showbar            = 1;
static const int topbar             = 1;

static const unsigned int systraypinning = 0;
static const unsigned int systrayonleft = 0;
static const unsigned int systrayspacing = 2;
static const int systraypinningfailfirst = 1;
static const int showsystray        = 1;

static const unsigned int gappih    = 10;
static const unsigned int gappiv    = 10;
static const unsigned int gappoh    = 15;
static const unsigned int gappov    = 15;
static const int smartgaps          = 0;

static const char *fonts[]          = { "monospace:size=10", "Font Awesome 5 Free Solid:pixelsize=12" };
static const char dmenufont[]       = "monospace:size=10";

static const char norm_bg[]         = "#222222";
static const char norm_border[]     = "#444444";
static const char norm_fg[]         = "#bbbbbb";
static const char sel_fg[]          = "#eeeeee";
static const char sel_bg_border[]   = "#928374";
static const char col1[]            = "#98971a";
static const char col2[]            = "#d79921";
static const char col3[]            = "#458588";
static const char col4[]            = "#b16286";
static const char col5[]            = "#689d6a";
static const char col6[]            = "#777777";

enum { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
       SchemeCol5, SchemeCol6, SchemeSel }; /* color schemes */

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]  = { norm_fg,   norm_bg,        norm_border },
	[SchemeSel]   = { sel_fg,    sel_bg_border,  sel_bg_border  },
	[SchemeCol1]  = { col1,      norm_bg,        norm_border },
	[SchemeCol2]  = { col2,      norm_bg,        norm_border },
	[SchemeCol3]  = { col3,      norm_bg,        norm_border },
	[SchemeCol4]  = { col4,      norm_bg,        norm_border },
	[SchemeCol5]  = { col5,      norm_bg,        norm_border },
	[SchemeCol6]  = { col6,      norm_bg,        norm_border },
};

static const char *tags[] = { "", "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class              instance          title       tags mask     isfloating   monitor */
	{ "feh",              NULL,             NULL,       0,            1,           -1 },
	{ "xdm",              NULL,             NULL,       0,            1,           -1 },

	{ "Brave-browser",    NULL,             NULL,       1 << 2,       0,           -1 },
	{ NULL,               NULL,             "ncmpcpp",  1 << 3,       0,           -1 },
	{ "vlc",              NULL,             NULL,       1 << 4,       0,           -1 },
	{ "FreeTube",         NULL,             NULL,       1 << 4,       0,           -1 },
	{ "Zathura",          NULL,             NULL,       1 << 5,       0,           -1 },
	{ NULL,               "libreoffice",    NULL,       1 << 5,       0,           -1 },
	{ "discord",          NULL,             NULL,       1 << 6,       0,           -1 },
	{ "TelegramDesktop",  NULL,             NULL,       1 << 6,       0,           -1 },
	{ "Thunderbird",      NULL,             NULL,       1 << 7,       0,           -1 },
	{ "Todoist",          NULL,             NULL,       1 << 8,       0,           -1 },
};

static const float mfact     = 0.66;
static const int nmaster     = 1;
static const int resizehints = 1;

static const Layout layouts[] = {
	{ "[]=",      tile },
	{ "><>",      NULL },
	{ "[M]",      monocle },
};

#define WM_MOD Mod4Mask
#define MODIFIER_MOD (Mod4Mask|ControlMask)
#define DMENU_MOD (Mod4Mask|ShiftMask)
#define APPS_MOD (Mod4Mask|Mod1Mask)
#define TAGKEYS(KEY,TAG) \
	{ ControlMask,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ControlMask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", norm_bg, "-nf", norm_fg, "-sb", sel_bg_border, "-sf", sel_fg, NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key                        function        argument */
	{ WM_MOD,                       XK_k,                      focusstack,     {.i = -1 } },
	{ WM_MOD,                       XK_j,                      focusstack,     {.i = +1 } },
	{ WM_MOD|ShiftMask,             XK_k,                      pushup,         {0} },
	{ WM_MOD|ShiftMask,             XK_j,                      pushdown,       {0} },
	{ WM_MOD,                       XK_d,                      incnmaster,     {.i = -1 } },
	{ WM_MOD,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ WM_MOD,                       XK_q,                      killclient,     {0} },
	{ WM_MOD|ShiftMask|ControlMask, XK_q,                      quit,           {0} },
	{ WM_MOD|ShiftMask,             XK_r,                      quit,           {1} },
	{ WM_MOD,                       XK_f,                      togglefullscr,  {0} },
	{ WM_MOD,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ WM_MOD,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ WM_MOD,                       XK_u,                      spawn,          SHCMD("$HOME/.scripts/i3lock_fancy_multimonitor/lock -n -p -g") },
	{ WM_MOD,                       XK_b,                      togglebar,      {0} },
	{ WM_MOD,                       XK_Return,                 zoom,           {0} },
	{ WM_MOD,                       XK_Tab,                    view,           {0} },
	{ WM_MOD|ShiftMask,             XK_space,                  togglefloating, {0} },
	{ WM_MOD,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ WM_MOD,                       XK_period,                 focusmon,       {.i = +1 } },
	{ WM_MOD|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ WM_MOD|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	{ WM_MOD,                       XK_space,                  spawn,          SHCMD("sigdwmblocks 5") },

	{ 0,                            XF86XK_AudioLowerVolume,   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -10% && sigdwmblocks 3")},
	{ 0,                            XF86XK_AudioRaiseVolume,   spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +10% && sigdwmblocks 3")},
	{ 0,                            XF86XK_AudioMute,          spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle && sigdwmblocks 3")},
	{ 0,                            XF86XK_AudioMicMute,       spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle && sigdwmblocks 4")},
	{ 0,                            XF86XK_MonBrightnessDown,  spawn,          SHCMD("brightnessctl set 10%-")},
	{ 0,                            XF86XK_MonBrightnessUp,    spawn,          SHCMD("brightnessctl set +10%")},

	{ MODIFIER_MOD,                 XK_minus,                  spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5% && sigdwmblocks 3")},
	{ MODIFIER_MOD,                 XK_equal,                  spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5% && sigdwmblocks 3")},
	{ MODIFIER_MOD,                 XK_0,                      spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle && sigdwmblocks 3")},
	{ MODIFIER_MOD,                 XK_bracketright,           spawn,          SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle && sigdwmblocks 4")},
	{ MODIFIER_MOD,                 XK_g,                      spawn,          SHCMD("pkill greenclip && greenclip clear && greenclip daemon &")},
	{ MODIFIER_MOD,                 XK_comma,                  spawn,          SHCMD("mpc prev && sigdwmblocks 6")},
	{ MODIFIER_MOD,                 XK_apostrophe,             spawn,          SHCMD("mpc toggle && sigdwmblocks 6")},
	{ MODIFIER_MOD,                 XK_period,                 spawn,          SHCMD("mpc next && sigdwmblocks 6")},
	{ MODIFIER_MOD,                 XK_u,                      spawn,          SHCMD("$HOME/.scripts/toggle_lockscreen_timeout.sh toggle")},

	{ DMENU_MOD,                    XK_a,                      spawn,          {.v = dmenucmd } },
	{ DMENU_MOD,                    XK_e,                      spawn,          SHCMD("$HOME/.scripts/dmenu/dmenu_emoji/dmenu_emoji.sh") },
	{ DMENU_MOD,                    XK_g,                      spawn,          SHCMD("greenclip print | sed '/^$/d' | dmenu -i -l 15 -p 'Clipboard:' | xargs -r -d'\n' -I '{}' greenclip print '{}'") },
	{ DMENU_MOD,                    XK_c,                      spawn,          SHCMD("$HOME/.scripts/dmenu/dmenu_calc.sh") },
	{ DMENU_MOD,                    XK_m,                      spawn,          SHCMD("$HOME/.scripts/dmenu/dmenu_song.sh") },
	{ DMENU_MOD,                    XK_d,                      spawn,          SHCMD("dmenu_et") },

	{ APPS_MOD,                     XK_Return,                 spawn,          SHCMD("st") },
	{ APPS_MOD,                     XK_b,                      spawn,          SHCMD("brave") },
	{ APPS_MOD,                     XK_x,                      spawn,          SHCMD("gksudo /opt/lampp/gui_manager.run") },
	{ APPS_MOD,                     XK_e,                      spawn,          SHCMD("st -e ranger") },
	{ APPS_MOD,                     XK_s,                      spawn,          SHCMD("scrot && notify-send -a 'Scrot' 'Screenshot taken'") },
	{ APPS_MOD,                     XK_m,                      spawn,          SHCMD("st -t ncmpcpp -e ncmpcpp") },
	{ APPS_MOD,                     XK_f,                      spawn,          SHCMD("/opt/FreeTube/freetube") },
	{ APPS_MOD,                     XK_t,                      spawn,          SHCMD("DESKTOPINTEGRATION=false $HOME/Applications/todoist.AppImage") },
	{ APPS_MOD,                     XK_w,                      spawn,          SHCMD("st -e nmtui") },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
};

static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         WM_MOD,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         WM_MOD,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         WM_MOD,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            WM_MOD,         Button1,        tag,            {0} },
	{ ClkTagBar,            WM_MOD,         Button3,        toggletag,      {0} },
};
