/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 12;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const int user_bh            = 10;        /* 2 is the default spacing for font */
static const char *fonts[]          = { "monospace:size=14" };
static const char dmenufont[]       = "monospace:size=14";
static const char col_gray1[]       = "#12100f";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#9a8a6f";
static const char col_gray4[]       = "#9a8a6f";
static const char col_cyan[]        = "#363636";
static const char *colors[][3]      = {
  /*               fg         bg         border   */
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel]  = { col_gray4, col_cyan,  col_gray4  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6" };

static const Rule rules[] = {
  /* xprop(1):
   *	WM_CLASS(STRING) = instance, class
   *	WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Gimp",     NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG)                                                              \
        { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenu[]         = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

static const char *terminal[]    =     { "alacritty", NULL };
static const char *browser[]     =     { "firefox", NULL };
static const char *filemng[]     =     { "thunar", NULL };
static const char *upvol[]       =     { "pamixer", "-i", "5", "--allow-boost", NULL };
static const char *downvol[]     =     { "pamixer", "-d", "5", NULL };
static const char *mutevol[]     =     { "pamixer", "-t", NULL };
static const char *screenshot[]  =     { "flameshot", "gui", "-p", "/home/jose/Pictures/screenshots", NULL };
static const char *sound[]       =     { "pavucontrol", NULL };
static const char *bluetooth[]   =     { "blueman-manager", NULL };
static const char *mon1off[]     =     { "xrandr", "--output", "eDP-1", "--off", NULL };
static const char *emacsclient[] =     { "emacsclient", "-c", NULL };

static const char *dwmbs11[]     =     { "pkill", "-RTMIN+11", "dwmblocks", NULL };
static const char *dwmbs12[]     =     { "pkill", "-RTMIN+12", "dwmblocks", NULL };
static const char *dwmbs13[]     =     { "pkill", "-RTMIN+13", "dwmblocks", NULL };
static const char *dwmbs14[]     =     { "pkill", "-RTMIN+14", "dwmblocks", NULL };
    
#include "shiftview.c"
static Key keys[] = {

  /* modifier                     key        function        argument */

  // System
  { MODKEY,                       XK_space,   spawn,          {.v = dmenu } },
  { MODKEY,                       XK_Return,  spawn,          {.v = terminal } },
  { MODKEY,                       XK_e,       spawn,          {.v = emacsclient } },
  { MODKEY|ShiftMask,             XK_m,       spawn,          {.v = mon1off } },
  
  // Volume setting
  { MODKEY,                       XK_i,       spawn,          {.v = upvol } },
  { MODKEY,                       XK_i,       spawn,          {.v = dwmbs11 } },
  { MODKEY,                       XK_d,       spawn,          {.v = downvol } },
  { MODKEY,                       XK_d,       spawn,          {.v = dwmbs11 } },
  { MODKEY,                       XK_m,       spawn,          {.v = mutevol } },
  { MODKEY,                       XK_m,       spawn,          {.v = dwmbs11 } },

  // Applications
  { MODKEY,                       XK_b,       spawn,          {.v = browser } },
  { MODKEY,                       XK_f,       spawn,          {.v = filemng } },
  { MODKEY,                       XK_s,       spawn,          {.v = sound } },
  { MODKEY|ShiftMask,             XK_b,       spawn,          {.v = bluetooth } },
  
  // Start Pomodoro
  { MODKEY,                       XK_p,       spawn,          {.v = dwmbs13 } },
  { MODKEY,                       XK_p,       spawn,          {.v = dwmbs12 } },
  
  // Stop Pomodoro
  { MODKEY|ShiftMask,             XK_p,       spawn,          {.v = dwmbs14 } },
  { MODKEY|ShiftMask,             XK_p,       spawn,          {.v = dwmbs12 } },
  { MODKEY|ShiftMask,             XK_s,       spawn,          {.v = screenshot } },

  // System workflow
  { MODKEY,                       XK_g,       togglebar,      {0} },
  { MODKEY,                       XK_Left,    focusstack,     {.i = -1 } },
  { MODKEY,                       XK_Right,   focusstack,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_i,       incnmaster,     {.i = +1 } },
  { MODKEY|ShiftMask,             XK_d,       incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,       setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,       setmfact,       {.f = +0.05} },
  { MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
  { MODKEY,                       XK_Tab,     view,           {0} },
  { MODKEY|ShiftMask,             XK_c,       killclient,     {0} },
  { MODKEY,                       XK_t,       setlayout,      {.v = &layouts[0]} },
  { MODKEY|ShiftMask,             XK_f,       setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_0,       view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,   focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period,  focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,   tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period,  tagmon,         {.i = +1 } },
  { MODKEY,                       XK_minus,   setgaps,        {.i = -1 } },
  { MODKEY,                       XK_equal,   setgaps,        {.i = +1 } },
  { MODKEY|ShiftMask,             XK_equal,   setgaps,        {.i = 0  } },
  { MODKEY,                       XK_Up,      shiftview,      {.i = +1 } },
  { MODKEY,                       XK_Down,    shiftview,      {.i = -1 } },
  { MODKEY|ShiftMask,             XK_Right,   rotatestack,    {.i = +1 } },
  { MODKEY|ShiftMask,             XK_Left,    rotatestack,    {.i = -1 } },
  TAGKEYS(                        XK_1,                       0)
  TAGKEYS(                        XK_2,                       1)
  TAGKEYS(                        XK_3,                       2)
  TAGKEYS(                        XK_4,                       3)
  TAGKEYS(                        XK_5,                       4)
  TAGKEYS(                        XK_6,                       5)
  TAGKEYS(                        XK_7,                       6)
  TAGKEYS(                        XK_8,                       7)
  TAGKEYS(                        XK_9,                       8)
  { MODKEY|ShiftMask,             XK_q,       quit,          {0} },

  // Not used (for now)
  //{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  //{ MODKEY,                       XK_space,  setlayout,      {0} },
  //{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = terminal } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

