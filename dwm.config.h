/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "inconsolata:size=9", "fontawesome:size=8" };
static const char dmenufont[]       = "inconsolata:size=9";
static const char col_gray1[]       = "#1B1F26";
static const char col_gray2[]       = "#2E3440";
static const char col_gray3[]       = "#4C566A";
static const char col_white[]       = "#EFF2F6";
static const char col_cyan[]        = "#5E81AC";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_gray1, col_gray2 },
	[SchemeSel]  = { col_white, col_gray3, col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "1", "2", "3", "4", "5", "6", "7", "8" };

/* include(s) depending on the tags array */
#include "flextile.h"

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     		NULL,       NULL,       1 << 8,       0,           -1 },
	{ "Lxappearance",  	NULL,       NULL,       0,            1,           -1 },
	{ "gucharmap",		NULL,	    NULL,       0,            1,           -1 },
	{ "mplayer",		NULL,	    NULL,	0,	      1,	   -1 },
	{ "arandr",		NULL,	    NULL, 	0,	      1,	   -1 },
	{ "pcmanfm",		NULL,	    NULL,	0,	      1,	   -1 },
	{ "feh",		NULL,	    NULL,	0,	      1, 	   -1 },
	{ "zoom",		NULL,	    NULL,	0,	      1, 	   -1 },
	{ "Steam",		NULL,	    NULL,	1 << 8,       0,	   -1 }
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int layoutaxis[] = {
	1,    /* layout axis: 1 = x, 2 = y; negative values mirror the layout, setting the master area to the right / bottom instead of left / top */
	2,    /* master axis: 1 = x (from left to right), 2 = y (from top to bottom), 3 = z (monocle) */
	2,    /* stack axis:  1 = x (from left to right), 2 = y (from top to bottom), 3 = z (monocle) */
};
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_f,      togglebar,      {0} },
	{ Mod1Mask,                     XK_j,      focusstack,     {.i = +1 } },
	{ Mod1Mask,                     XK_k,      focusstack,     {.i = -1 } },
	{ Mod1Mask,                     XK_i,      shiftmastersplit, {.i = +1} },   /* increase the number of tiled clients in the master area */
	{ Mod1Mask,                     XK_d,      shiftmastersplit, {.i = -1} },   /* reduce the number of tiled clients in the master area */
	{ Mod1Mask,                     XK_h,      setmfact,       {.f = -0.05} },
	{ Mod1Mask,                     XK_l,      setmfact,       {.f = +0.05} },
	{ Mod1Mask,                     XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_l,      view,           {0} },
	{ MODKEY, 	                XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	//{ MODKEY,                       XK_f,      setlayout,      {0} },
	{ MODKEY,	                XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_Return,                 0)
	TAGKEYS(                        XK_1,                      1)
	TAGKEYS(                        XK_2,                      2)
	TAGKEYS(                        XK_3,                      3)
	TAGKEYS(                        XK_4,                      4)
	TAGKEYS(                        XK_5,                      5)
	TAGKEYS(                        XK_6,                      6)
	TAGKEYS(                        XK_7,                      7)
	TAGKEYS(                        XK_8,                      8)
	{ Mod1Mask|ShiftMask,           XK_q,      quit,           {0} },
	{ Mod1Mask|ControlMask,           XK_t,      rotatelayoutaxis, {.i = 0} },    /* 0 = layout axis */
	{ Mod1Mask|ControlMask,           XK_Tab,    rotatelayoutaxis, {.i = 1} },    /* 1 = master axis */
	{ Mod1Mask|ControlMask|ShiftMask, XK_Tab,    rotatelayoutaxis, {.i = 2} },    /* 2 = stack axis */
	{ Mod1Mask|ControlMask,           XK_Return, mirrorlayout,     {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         Mod1Mask,       Button1,        movemouse,      {0} },
	{ ClkClientWin,         Mod1Mask,       Button2,        togglefloating, {0} },
	{ ClkClientWin,         Mod1Mask,       Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            Mod1Mask,       Button1,        tag,            {0} },
	{ ClkTagBar,            Mod1Mask,       Button3,        toggletag,      {0} },
};

