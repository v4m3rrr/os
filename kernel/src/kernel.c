#include <stdint.h>
#include "scancode.h"
#include "video.h"
#include "colors.h"
#include "logo.h"

int str_cmp(const char* str0,const char* str1){
    for(;*str0!=0&&*str1!=0;++str0,++str1){
	if(*str0!=*str1){
	    return 0;
	}
    }
    if(*str0==0&&*str1==0){
	return 1;
    }

    return 0;
}

int _start(){
    //print_logo();
    disable_cursor();
    clear();
    print_color("TEst",BLACK_ON_WHITE);
    char buf[512];
    buf[0]=0;

    print_color("command>> ",BLACK_ON_WHITE);
    while(!str_cmp(buf,"exit")){

	uint8_t status;
	do{
	    status=port_in_byte(0x64);
	    status&=1;
	}while(status!=1);
	
	uint8_t ch=port_in_byte(0x60);
	if((ch&0x80)==0){
	    //print_uint_color(ch,BLACK_ON_WHITE);
	    //print_color(" ",BLACK_ON_WHITE);
	    
	    putch_color(sto737[ch],BLACK_ON_WHITE);
	}
    }
    print_color("TEst",BLACK_ON_WHITE);
}
