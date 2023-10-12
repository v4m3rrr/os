#ifndef __COLORS
#define __COLORS

#define BLACK 0x0
#define BLUE 0x1
#define GREEN 0x2
#define CYAN 0x3
#define RED 0x4
#define MAGENTA 0x5
#define BROWN 0x6
#define GRAY 0x7
#define DARK_GREY 0x8
#define BRIGHT_BLUE 0x9
#define BRIGHT_GREEN 0xa
#define BRIGHT_CYAN 0xb
#define BRIGHT_RED 0xc
#define BRIGHT_MAGENTA 0xd
#define YELLOW 0xe
#define WHITE 0xf

#define MAKE_COLOR(bg,fg) fg|(bg<<4)

#endif
