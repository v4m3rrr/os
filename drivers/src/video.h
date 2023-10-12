#include <stdint.h>

#ifndef __VIDEO
#define __VIDEO

#define VIDEO_MEMORY (uint8_t*)0xb8000
#define VIDEO_WIDTH 80
#define VIDEO_HEIGHT 25
#define VIDEO_MEMORY_END VIDEO_MEMORY+VIDEO_WIDTH*VIDEO_HEIGHT*2
#define BLACK_ON_WHITE MAKE_COLOR(BLACK,WHITE)
#define MAX_DIGIT_SIZE 10

extern uintptr_t VIDEO_OFFSET;
void disable_cursor();
void port_out_byte(uint16_t,uint8_t);
uint8_t port_in_byte(uint16_t);
void new_line();
void putch(char);
void putch_color(char,uint8_t);
void print(const char*);
void print_uint(uint32_t); 
void print_color(const char*,uint8_t);
void print_uint_color(uint32_t,uint8_t);
void set_bg(uint8_t);
void clear();
#endif


