/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 GPL Source Code ("Doom 3 Source Code").

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#include "sys/platform.h"
#include "framework/Common.h"
#include "framework/KeyInput.h"

#include "sys/win32/win_local.h"

// DG: at least MinGW doesn't like the old scantokey tables, seems to be some kind of charcode-fuckup
//     (no -finput-charset=ISO8859-1 doesn't seem to help, see #238) - so use plain numbers instead

#if 0 // keeping the original for reference
static const unsigned char s_scantokey[256] = {
//  0            1       2          3          4       5            6         7
//  8            9       A          B          C       D            E         F
	0,           27,    '1',       '2',        '3',    '4',         '5',      '6',
	'7',        '8',    '9',       '0',        '-',    '=',          K_BACKSPACE, 9, // 0
	'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
	'o',        'p',    '[',       ']',        K_ENTER,K_CTRL,      'a',      's',   // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      ';',
	'\'',       '`',    K_SHIFT,   '\\',       'z',    'x',         'c',      'v',   // 2
	'b',        'n',    'm',       ',',        '.',    '/',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           0,        K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,      // 7
// shifted
	0,           27,    '!',       '@',        '#',    '$',         '%',      '^',
	'&',        '*',    '(',       ')',        '_',    '+',          K_BACKSPACE, 9, // 0
	'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
	'o',        'p',    '[',       ']',        K_ENTER,K_CTRL,      'a',      's',   // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      ';',
	'\'',       '~',    K_SHIFT,   '\\',       'z',    'x',         'c',      'v',   // 2
	'b',        'n',    'm',       ',',        '.',    '/',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           0,        K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0      // 7
};
#else // the same in numbers, generated by VS2010 Express on WinXP
static const unsigned char s_scantokey[256] = {
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  0,  27,  49,  50,  51,  52,  53,  54,  55,  56,  57,  48,  45,  61, 127,   9,   // 0
	113, 119, 101, 114, 116, 121, 117, 105, 111, 112,  91,  93,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108,  59,  39,  96, 142,  92, 122, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  47, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,   0, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
// shifted
	  0,  27,  33,  64,  35,  36,  37,  94,  38,  42,  40,  41,  95,  43, 127,   9,   // 0
	113, 119, 101, 114, 116, 121, 117, 105, 111, 112,  91,  93,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108,  59,  39, 126, 142,  92, 122, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  47, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,   0, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
};
#endif

#if 0 // keeping the original for reference
static const unsigned char s_scantokey_german[256] = {
//  0            1       2          3          4       5            6         7
//  8            9       A          B          C       D            E         F
	0,           27,    '1',       '2',        '3',    '4',         '5',      '6',
	'7',        '8',    '9',       '0',        '?',    '\'',        K_BACKSPACE, 9,  // 0
	'q',        'w',    'e',       'r',        't',    'z',         'u',      'i',
	'o',        'p',    '=',       '+',        K_ENTER,K_CTRL,      'a',      's',   // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      '[',
	']',        '`',    K_SHIFT,   '#',        'y',    'x',         'c',      'v',   // 2
	'b',        'n',    'm',       ',',        '.',    '-',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,      // 7
// shifted
	0,           27,    '1',       '2',        '3',    '4',         '5',      '6',
	'7',        '8',    '9',       '0',        '?',    '\'',        K_BACKSPACE, 9,  // 0
	'q',        'w',    'e',       'r',        't',    'z',         'u',      'i',
	'o',        'p',    '=',       '+',        K_ENTER,K_CTRL,      'a',      's',   // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      '[',
	']',        '`',    K_SHIFT,   '#',        'y',    'x',         'c',      'v',   // 2
	'b',        'n',    'm',       ',',        '.',    '-',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0      // 7
};
#else // the same in numbers, generated by VS2010 Express on WinXP
static const unsigned char s_scantokey_german[256] = {
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  0,  27,  49,  50,  51,  52,  53,  54,  55,  56,  57,  48,  63,  39, 127,   9,   // 0
	113, 119, 101, 114, 116, 122, 117, 105, 111, 112,  61,  43,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108,  91,  93,  96, 142,  35, 121, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  45, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
// shifted
	  0,  27,  49,  50,  51,  52,  53,  54,  55,  56,  57,  48,  63,  39, 127,   9,   // 0
	113, 119, 101, 114, 116, 122, 117, 105, 111, 112,  61,  43,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108,  91,  93,  96, 142,  35, 121, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  45, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
};
#endif

#if 0 // keeping the original for reference
static const unsigned char s_scantokey_french[256] = {
//  0            1       2          3          4       5            6         7
//  8            9       A          B          C       D            E         F
	0,           27,    '1',       '2',        '3',    '4',         '5',      '6',
	'7',        '8',    '9',       '0',        ')',    '=',         K_BACKSPACE, 9, // 0
	'a',        'z',    'e',       'r',        't',    'y',         'u',      'i',
	'o',        'p',    '^',       '$',        K_ENTER,K_CTRL,      'q',      's',      // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      'm',
	'�',        '`',    K_SHIFT,   '*',        'w',    'x',         'c',      'v',      // 2
	'b',        'n',    ',',       ';',        ':',    '!',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,      // 7
// shifted
	0,           27,    '&',       '�',        '\"',    '\'',         '(',      '-',
	'�',        '_',    '�',       '�',        '�',    '+',         K_BACKSPACE, 9, // 0
	'a',        'z',    'e',       'r',        't',    'y',         'u',      'i',
	'o',        'p',    '^',       '$',        K_ENTER,K_CTRL,      'q',      's',      // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      'm',
	'�',        0,    K_SHIFT,   '*',        'w',    'x',         'c',      'v',      // 2
	'b',        'n',    ',',       ';',        ':',    '!',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0      // 7
};
#else // the same in numbers, generated by VS2010 Express on WinXP
static const unsigned char s_scantokey_french[256] = {
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  0,  27,  49,  50,  51,  52,  53,  54,  55,  56,  57,  48,  41,  61, 127,   9,   // 0
	 97, 122, 101, 114, 116, 121, 117, 105, 111, 112,  94,  36,  13, 141, 113, 115,   // 1
	100, 102, 103, 104, 106, 107, 108, 109, 249,  96, 142,  42, 119, 120,  99, 118,   // 2
	 98, 110,  44,  59,  58,  33, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
// shifted
	  0,  27,  38, 233,  34,  39,  40,  45, 232,  95, 231, 224, 176,  43, 127,   9,   // 0
	 97, 122, 101, 114, 116, 121, 117, 105, 111, 112,  94,  36,  13, 141, 113, 115,   // 1
	100, 102, 103, 104, 106, 107, 108, 109, 249,   0, 142,  42, 119, 120,  99, 118,   // 2
	 98, 110,  44,  59,  58,  33, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
};
#endif

#if 0 // keeping the original for reference
static const unsigned char s_scantokey_spanish[256] = {
//  0            1       2          3          4       5            6         7
//  8            9       A          B          C       D            E         F
	0,           27,    '1',       '2',        '3',    '4',         '5',      '6',
	'7',        '8',    '9',       '0',        '\'',   '�',         K_BACKSPACE, 9,  // 0
	'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
	'o',        'p',    '`',       '+',        K_ENTER,K_CTRL,      'a',      's',   // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      '�',
	'�',        '�',    K_SHIFT,   '�',        'z',    'x',         'c',      'v',   // 2
	'b',        'n',    'm',       ',',        '.',    '-',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,      // 7
// shifted
	0,           27,    '!',       '\"',        '�',    '$',         '%',      '&',
	'/',        '(',    ')',       '=',        '?',   '�',         K_BACKSPACE, 9,  // 0
	'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
	'o',        'p',    '^',       '*',        K_ENTER,K_CTRL,      'a',      's',   // 1
	'd',        'f',    'g',       'h',        'j',    'k',         'l',      '�',
	'�',        '�',    K_SHIFT,   '�',        'z',    'x',         'c',      'v',   // 2
	'b',        'n',    'm',       ',',        '.',    '-',         K_SHIFT,  K_KP_STAR,
	K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
	K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
	K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
	K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
	K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0,     // 6
	0,          0,      0,         0,          0,      0,           0,        0,
	0,          0,      0,         0,          0,      0,           0,        0      // 7
};
#else // the same in numbers, generated by VS2010 Express on WinXP
static const unsigned char s_scantokey_spanish[256] = {
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  0,  27,  49,  50,  51,  52,  53,  54,  55,  56,  57,  48,  39, 161, 127,   9,   // 0
	113, 119, 101, 114, 116, 121, 117, 105, 111, 112,  96,  43,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108, 241, 180, 186, 142, 231, 122, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  45, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
// shifted
	  0,  27,  33,  34, 183,  36,  37,  38,  47,  40,  41,  61,  63, 191, 127,   9,   // 0
	113, 119, 101, 114, 116, 121, 117, 105, 111, 112,  94,  42,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108, 209, 168, 170, 142, 199, 122, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  45, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
};
#endif

#if 0 // keeping the original for reference
static const unsigned char s_scantokey_italian[256] = {
//  0            1       2          3          4       5            6         7
//  8            9       A          B          C       D            E         F
		0,           27,    '1',       '2',        '3',    '4',         '5',      '6',
		'7',        '8',    '9',       '0',        '\'',   '�',         K_BACKSPACE, 9,  // 0
		'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
		'o',        'p',    '�',       '+',        K_ENTER,K_CTRL,      'a',      's',   // 1
		'd',        'f',    'g',       'h',        'j',    'k',         'l',      '�',
		'�',        '\\',    K_SHIFT,   '�',        'z',    'x',         'c',      'v',   // 2
		'b',        'n',    'm',       ',',        '.',    '-',         K_SHIFT,  K_KP_STAR,
		K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
		K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
		K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
		K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
		K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
		0,          0,      0,         0,          0,      0,           0,        0,
		0,          0,      0,         0,          0,      0,           0,        0,     // 6
		0,          0,      0,         0,          0,      0,           0,        0,
		0,          0,      0,         0,          0,      0,           0,        0,      // 7
// shifted
		0,           27,    '!',       '\"',        '�',    '$',         '%',      '&',
		'/',        '(',    ')',       '=',        '?',   '^',         K_BACKSPACE, 9,  // 0
		'q',        'w',    'e',       'r',        't',    'y',         'u',      'i',
		'o',        'p',    '�',       '*',        K_ENTER,K_CTRL,      'a',      's',   // 1
		'd',        'f',    'g',       'h',        'j',    'k',         'l',      '�',
		'�',        '|',    K_SHIFT,   '�',        'z',    'x',         'c',      'v',   // 2
		'b',        'n',    'm',       ',',        '.',    '-',         K_SHIFT,  K_KP_STAR,
		K_ALT,      ' ',    K_CAPSLOCK,K_F1,       K_F2,   K_F3,        K_F4,     K_F5,  // 3
		K_F6,       K_F7,   K_F8,      K_F9,       K_F10,  K_PAUSE,     K_SCROLL, K_HOME,
		K_UPARROW,  K_PGUP, K_KP_MINUS,K_LEFTARROW,K_KP_5, K_RIGHTARROW,K_KP_PLUS,K_END, // 4
		K_DOWNARROW,K_PGDN, K_INS,     K_DEL,      0,      0,           '<',      K_F11,
		K_F12,      0,      0,         K_LWIN,     K_RWIN, K_MENU,      0,        0,     // 5
		0,          0,      0,         0,          0,      0,           0,        0,
		0,          0,      0,         0,          0,      0,           0,        0,     // 6
		0,          0,      0,         0,          0,      0,           0,        0,
		0,          0,      0,         0,          0,      0,           0,        0		 // 7
};
#else // the same in numbers, generated by VS2010 Express on WinXP
static const unsigned char s_scantokey_italian[256] = {
//	 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  0,  27,  49,  50,  51,  52,  53,  54,  55,  56,  57,  48,  39, 236, 127,   9,   // 0
	113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 232,  43,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108, 242, 224,  92, 142, 249, 122, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  45, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
// shifted
	  0,  27,  33,  34, 163,  36,  37,  38,  47,  40,  41,  61,  63,  94, 127,   9,   // 0
	113, 119, 101, 114, 116, 121, 117, 105, 111, 112, 233,  42,  13, 141,  97, 115,   // 1
	100, 102, 103, 104, 106, 107, 108, 231, 176, 124, 142, 167, 122, 120,  99, 118,   // 2
	 98, 110, 109,  44,  46,  45, 142, 183, 140,  32, 129, 149, 150, 151, 152, 153,   // 3
	154, 155, 156, 157, 158, 132, 130, 147, 133, 146, 179, 135, 169, 136, 181, 148,   // 4
	134, 145, 143, 144,   0,   0,  60, 159, 160,   0,   0, 137, 138, 139,   0,   0,   // 5
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 6
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   // 7
};
#endif

static const unsigned char *keyScanTable = s_scantokey;

// this should be part of the scantables and the scan tables should be 512 bytes
// (256 scan codes, shifted and unshifted).  Changing everything to use 512 byte
// scan tables now might introduce bugs in tested code.  Since we only need to fix
// the right-alt case for non-US keyboards, we're just using a special-case table
// for it.  Eventually, the tables above should be fixed to handle all possible
// scan codes instead of just the first 128.
static unsigned char	rightAltKey = K_ALT;

/*
===========
Sys_InitScanTable
===========
*/
void Sys_InitScanTable( void ) {
	idStr lang = cvarSystem->GetCVarString( "sys_lang" );
	if ( lang.Length() == 0 ) {
		lang = "english";
	}
	if ( lang.Icmp( "english" ) == 0 ) {
		keyScanTable = s_scantokey;
		// the only reason that english right alt binds as K_ALT is so that
		// users who were using right-alt before the patch don't suddenly find
		// that only left-alt is working.
		rightAltKey = K_ALT;
	} else if ( lang.Icmp( "spanish" ) == 0 ) {
		keyScanTable = s_scantokey_spanish;
		rightAltKey = K_RIGHT_ALT;
	} else if ( lang.Icmp( "french" ) == 0 ) {
		keyScanTable = s_scantokey_french;
		rightAltKey = K_RIGHT_ALT;
	} else if ( lang.Icmp( "german" ) == 0 ) {
		keyScanTable = s_scantokey_german;
		rightAltKey = K_RIGHT_ALT;
	} else if ( lang.Icmp( "italian" ) == 0 ) {
		keyScanTable = s_scantokey_italian;
		rightAltKey = K_RIGHT_ALT;
	}
}

/*
==================
Win_GetScanTable
==================
*/
const unsigned char *Win_GetScanTable( void ) {
	return keyScanTable;
}

/*
=======
Win_MapKey

Map from windows to Doom keynums
=======
*/
int Win_MapKey (int key)
{
	int result;
	int modified;
	bool is_extended;

	modified = ( key >> 16 ) & 255;

	if ( modified > 127 )
		return 0;

	if ( key & ( 1 << 24 ) ) {
		is_extended = true;
	}
	else {
		is_extended = false;
	}

	//Check for certain extended character codes.
	//The specific case we are testing is the numpad / is not being translated
	//properly for localized builds.
	if(is_extended) {
		switch(modified) {
			case 0x35: //Numpad /
				return K_KP_SLASH;
		}
	}

	const unsigned char *scanToKey = Win_GetScanTable();
	result = scanToKey[modified];

	// common->Printf( "Key: 0x%08x Modified: 0x%02x Extended: %s Result: 0x%02x\n", key, modified, (is_extended?"Y":"N"), result);

	if ( is_extended ) {
		switch ( result )
		{
		case K_PAUSE:
			return K_KP_NUMLOCK;
		case 0x0D:
			return K_KP_ENTER;
		case 0x2F:
			return K_KP_SLASH;
		case 0xAF:
			return K_KP_PLUS;
		case K_KP_STAR:
			return K_PRINT_SCR;
		case K_ALT:
			return K_RIGHT_ALT;
		}
	}
	else {
		switch ( result )
		{
		case K_HOME:
			return K_KP_HOME;
		case K_UPARROW:
			return K_KP_UPARROW;
		case K_PGUP:
			return K_KP_PGUP;
		case K_LEFTARROW:
			return K_KP_LEFTARROW;
		case K_RIGHTARROW:
			return K_KP_RIGHTARROW;
		case K_END:
			return K_KP_END;
		case K_DOWNARROW:
			return K_KP_DOWNARROW;
		case K_PGDN:
			return K_KP_PGDN;
		case K_INS:
			return K_KP_INS;
		case K_DEL:
			return K_KP_DEL;
		}
	}

	return result;
}
