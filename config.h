/* See LICENSE file for copyright and license details. */

/* appearance */
static const char *fonts[] = {
	"hack:size=11"
};
static const char dmenufont[]       = "hack:size=11";
static const char normbordercolor[] = "#202020";
static const char normbgcolor[]     = "#151515";
static const char normfgcolor[]     = "#d0d0d0";
static const char selbordercolor[]  = "#d28445";
static const char selbgcolor[]      = "#303030";
static const char selfgcolor[]      = "#d0d0d0";
static unsigned int baralpha        = 0xff;
static unsigned int borderalpha     = OPAQUE;
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static unsigned int gappx           = 20;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "♫" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Chromium", NULL,       NULL,       1,            0,            -1 },
	{ "qutebrowser", NULL,       NULL,       1,            0,            -1 },
	{ "Spotify",  NULL,       "Spotify",  2,            0,           -1 }
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */


#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "T ",      tile },    /* first entry is default */
	{ "F ",      NULL },    /* no layout function means floating behavior */
	{ "M ",      monocle },
	{ "H[]",      deck },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { "st", NULL };
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *dmenucmd_res[] = { "/home/adam/.scripts/dmenu_run_res", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL }; 
static const char *lfcmd[] = { "st", "lf", NULL };
static const char *exitprompt[] = { "/home/adam/.scripts/exitprompt", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL }; 
static const char *volumeup[] = { "pulseaudio-ctl", "up", NULL };
static const char *volumedown[] = { "pulseaudio-ctl", "down", NULL };
static const char *volumeUP[] = { "pulseaudio-ctl", "up 25", NULL };
static const char *volumeDOWN[] = { "pulseaudio-ctl", "down 25", NULL };
static const char *volumemute[] = { "pulseaudio-ctl", "mute", NULL };
static const char *printscreen[] = { "/home/adam/.scripts/screenshot", NULL};
static const char *sptrestart[] = {"/home/adam/.scripts/sptrestart", NULL};
static const char *sptshow[] = {"killall", "-SIGUSR1", "spt", NULL};
static const char *sptpause[] = {"killall", "-SIGUSR2", "spt", NULL};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd_res } },
	{ MODKEY,                       XK_r,      spawn,          {.v = lfcmd } },
	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = exitprompt } },
	{ MODKEY,                       XK_s,      spawn,          {.v = volumeup } },
	{ MODKEY,                       XK_x,      spawn,          {.v = volumedown } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = volumeUP } },
	{ MODKEY|ShiftMask,             XK_x,      spawn,          {.v = volumeDOWN } },
	{ MODKEY,                       XK_y,      spawn,          {.v = volumemute } },
	{ MODKEY,                       XK_Print,  spawn,          {.v = printscreen } },
	{ MODKEY,                       XK_Home,   spawn,          {.v = sptrestart } },
	{ MODKEY,                       XK_End,    spawn,          {.v = sptshow } },
	{ MODKEY,                       XK_Pause,  spawn,          {.v = sptpause } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,     	XK_e,      quit,           {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_w,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_i,      incgap,         {.i = +2 } },
	{ MODKEY,                       XK_o,      incgap,         {.i = -2 } },
	{ MODKEY,                       XK_p,      setgapzero,     {0}        },
	TAGKEYS(                        XK_semicolon,                   5)
	TAGKEYS(                        XK_plus,                        0)
	TAGKEYS(                        XK_ecaron,                      1)
	TAGKEYS(                        XK_scaron,                      2)
	TAGKEYS(                        XK_ccaron,                      3)
	TAGKEYS(                        XK_rcaron,                      4)
	TAGKEYS(                        XK_zcaron,                      6)
	TAGKEYS(                        XK_yacute,                      7)
	TAGKEYS(                        XK_aacute,                      8)
	TAGKEYS(                        XK_iacute,                      9)
	{ MODKEY,                   XK_Down,    moveresize,     {.v = (int []){ 0, 25, 0, 0 }}},
	{ MODKEY,                   XK_Up,      moveresize,     {.v = (int []){ 0, -25, 0, 0 }}},
	{ MODKEY,                   XK_Right,   moveresize,     {.v = (int []){ 25, 0, 0, 0 }}},
	{ MODKEY,                   XK_Left,    moveresize,     {.v = (int []){ -25, 0, 0, 0 }}},
	{ MODKEY|ShiftMask,         XK_Down,    moveresize,     {.v = (int []){ 0, 0, 0, 25 }}},
	{ MODKEY|ShiftMask,         XK_Up,      moveresize,     {.v = (int []){ 0, 0, 0, -25 }}},
	{ MODKEY|ShiftMask,         XK_Right,   moveresize,     {.v = (int []){ 0, 0, 25, 0 }}},
	{ MODKEY|ShiftMask,         XK_Left,    moveresize,     {.v = (int []){ 0, 0, -25, 0 }}},
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

