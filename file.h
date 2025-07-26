#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include "stdtypes.h"
#include "SINGLE_LINKED_LIST.h"

#define CORRECT_PASSWORD 1234

#define TRUE 1
#define FALSE 0 

#define ADMIN_MODE 1
#define USER_MODE 2


#define SLOTSNUM 5

#define SLOT1 1
#define SLOT2 2
#define SLOT3 3
#define SLOT4 4
#define SLOT5 5

#define BLUE 	    1
#define GREEN  		2
#define AQUA   		3
#define RED         4
#define YELLOW      6
#define LIGHTYELLOW 14


#define LIST  AQUA
#define INPUTCol 15

extern u32 Password;
extern u8 check_pass_var;
void print_colored_text(const char* text, int color);
void menu_admin();
void menu_user();
void check_password();
u8 search_ID(u8 id);
void add_new_patient();
void reserve_slots(patient* patientData);
node* find_patient(u8 id);
void Edit_patient_record();
void Cancel_reservation();
void View_patient_record(u8 Mode);
void view_reservations(u8 Mode);

void save_patients_to_file();
void load_patients_from_file();

#endif