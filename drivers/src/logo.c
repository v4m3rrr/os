#include "video.h"
#include "colors.h"

uint8_t logo[][2]={
    {0,18},{0,19},{0,20},{0,29},{0,36},{0,42},
    {0,51},{0,52},{0,53},{0,60},{0,61},{0,62},
    
    {1,17},{1,28},{1,30},{1,37},
    {1,41},{1,50},{1,54},{1,59},{1,63},

    {2,16},{2,28},{2,30},{2,38},
    {2,40},{2,49},{2,55},{2,59},

    {3,16},{3,20},{3,21},{3,22},{3,27},{3,31},
    {3,39},{3,49},{3,55},{3,60},{3,61},{3,62},

    {4,16},{4,22},{4,26},{4,27},{4,28},{4,29},
    {4,30},{4,31},{4,32},{4,39},{4,49},{4,55},{4,63},

    {5,17},{5,21},{5,26},{5,32},
    {5,39},{5,50},{5,54},{5,59},{5,63},

    {6,18},{6,19},{6,20},{6,25},{6,33},{6,39},
    {6,51},{6,52},{6,53},{6,60},{6,61},{6,62}
};

void print_logo(){
    clear();
    set_bg(MAKE_COLOR(MAGENTA,MAGENTA));
    for(int i=0;i<9;++i){
        for(int j=0;j<80;++j){
            putch(' ');
        }   
    } 
    for(int i=0;i<sizeof(logo)/sizeof(logo[0]);++i){
	uint32_t index=(logo[i][0]*80+logo[i][1])*2;
	*(VIDEO_MEMORY+VIDEO_OFFSET+index)=' ';
	*(VIDEO_MEMORY+VIDEO_OFFSET+index+1)=MAKE_COLOR(WHITE,WHITE);
    }
}
