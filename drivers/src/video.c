#include <stdint.h>
#include "video.h"
#include "colors.h"

//Odzielnie put_color putch bo KEEP_BACKGROUND dziala tylko dla pierwszego ch w stringu potem nie ma sensu
//Clear nie usuwa migajacego kursora

uintptr_t VIDEO_OFFSET=0;

void new_line(){
    
}

void disable_cursor(){
    uint16_t r;
    if(port_in_byte(0x3cc)&1){ //one if color mode
	    r=0x3d4;
    }else{
	    r=0x3b4;
    }
    uint8_t prev_index=port_in_byte(r);
    port_out_byte(r,0x0a);
    uint8_t prev_data=port_in_byte(r+1);
    port_out_byte(r+1,prev_data|=0x20);
    port_out_byte(r,prev_index); 
}

void port_out_byte(uint16_t port, uint8_t data){
    asm volatile("outb %%al,%%dx"
		:
		:"a"(data),"d"(port));
}

uint8_t port_in_byte(uint16_t port){
    uint8_t data;
    asm volatile("inb %%dx,%%al"
		:"=a"(data)
		:"d"(port));
}

void putch_color(char ch,uint8_t color){
    if(VIDEO_OFFSET==VIDEO_MEMORY_END-VIDEO_MEMORY){
	// scrolling to inplement
	return;
    }

    *(VIDEO_MEMORY+VIDEO_OFFSET++)=ch;
    *(VIDEO_MEMORY+VIDEO_OFFSET++)=color;
}

void putch(char ch){
    putch_color(ch,*(VIDEO_MEMORY+VIDEO_OFFSET+1));
}

void print(const char* str){
    while(*str!=0){
	putch(*str++);
    }
}

void print_uint(uint32_t x){
    uint8_t buf[MAX_DIGIT_SIZE+1];

    uint8_t size=0;
    uint8_t* ptr=buf;
    while(x!=0){
	++size;
	*ptr++=x%10+'0';	
	x/=10;
    }
    *ptr=0;

    for(uint8_t* p_b=buf,*p_e=ptr-1;p_b<p_e;++p_b,--p_e){
	uint8_t temp=*p_b;
	*p_b=*p_e;
	*p_e=temp;
    }
    
    print(buf);
}

void print_color(const char* str, uint8_t color){
    while(*str!=0){
	putch_color(*str++,color);
    }
}

void print_uint_color(uint32_t x,uint8_t color){
    uint8_t buf[MAX_DIGIT_SIZE+1];

    uint8_t size=0;
    uint8_t* ptr=buf;
    while(x!=0){
	++size;
	*ptr++=x%10+'0';	
	x/=10;
    }
    *ptr=0;

    for(uint8_t* p_b=buf,*p_e=ptr-1;p_b<p_e;++p_b,--p_e){
	uint8_t temp=*p_b;
	*p_b=*p_e;
	*p_e=temp;
    }

    print_color(buf,color);
}

void set_bg(uint8_t color){
    uintptr_t temp=VIDEO_OFFSET;
    VIDEO_OFFSET=0;
    while(VIDEO_OFFSET!=VIDEO_MEMORY_END-VIDEO_MEMORY){
	putch_color(*(VIDEO_MEMORY+VIDEO_OFFSET),color);
    }
    VIDEO_OFFSET=temp;
}

void clear(){
    uintptr_t temp=VIDEO_OFFSET;
    VIDEO_OFFSET=0;
    while(VIDEO_OFFSET!=VIDEO_MEMORY_END-VIDEO_MEMORY){
	putch_color(' ',MAKE_COLOR(BLACK,BLACK));
    }
    VIDEO_OFFSET=temp;
}



