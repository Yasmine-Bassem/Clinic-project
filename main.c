#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include "file.h"
#include"STDTYPES.h"
#include"SINGLE_LINKED_LIST.h"



void main(){
	load_patients_from_file();

    while(1) {
        u8 mode;
        print_colored_text("--------------------------------\n",LIGHTYELLOW);
        print_colored_text("1->For Admin Mode\n",LIST);
        print_colored_text("2->For User Mode\n",LIST);
        print_colored_text("--------------------------------\n",LIGHTYELLOW);

        scanf("%d",&mode);
        
        switch(mode) {
            case ADMIN_MODE:
                check_password();
                if(!check_pass_var) {
                    return;  
                }
                menu_admin();  
                break;
            case USER_MODE:
                menu_user();  
                break;
            default:
                print_colored_text("Invalid Input\n",RED);
                Sleep(500);
        }
    }
}