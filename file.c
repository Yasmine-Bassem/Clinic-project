#include "file.h"
#include <windows.h>
#include <stdlib.h>



u8 mode = ADMIN_MODE;
u32 Password;
u8 check_pass_var = FALSE;
patient newPatient;

u8* slots[SLOTSNUM] = {
    "1-->2pm    to 2:30pm",
    "2-->2:30pm to 3pm",
    "3-->3pm    to 3:30pm",
    "4-->4pm    to 4:30pm",
    "5-->4:30pm to 5pm"
};
// initialize 0->not reserved, 1-> reserver
u8 reservedSlots[SLOTSNUM]={0};

void print_colored_text(const char* text, int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	printf("%s", text);
	SetConsoleTextAttribute(hConsole, 7); // reset color
	/*
		Available colors in Windows CMD with SetConsoleTextAttribute:

		0  = Black
		1  = Blue
		2  = Green
		3  = Aqua (Cyan)
		4  = Red
		5  = Purple (Magenta)
		6  = Yellow
		7  = White (Default)
		8  = Gray
		9  = Light Blue
		10 = Light Green
		11 = Light Aqua (Cyan)
		12 = Light Red
		13 = Light Purple (Magenta)
		14 = Light Yellow
		15 = Bright White
		*/
}



void menu_admin(){
	while(1){
		u8 adminChoise;
		print_colored_text("--------------------------------\n",LIGHTYELLOW);
		print_colored_text("1->Add new patient record\n",LIST);
		print_colored_text("2->Edit patient record\n",LIST);
		print_colored_text("3->Cancel reservation\n",LIST);
		print_colored_text("4->View patient record\n",LIST);
		print_colored_text("5->View today's reservations\n",LIST);
		print_colored_text("6->Exit\n",LIST);
		print_colored_text("--------------------------------\n",LIGHTYELLOW);

		
		scanf("%d",&adminChoise);
		switch(adminChoise){
			case 1:
				add_new_patient();
			break;
			case 2:
				Edit_patient_record();
			break;
			case 3:
				Cancel_reservation();
			break;
			case 4:
				View_patient_record(ADMIN_MODE);
			break;
			case 5:
				view_reservations(ADMIN_MODE);
			break;
			
			case 6:
				exit(0);
			break;

			
		}
	}
}
void menu_user(){
	u8 userChoise;
	print_colored_text("--------------------------------\n",LIGHTYELLOW);
	print_colored_text("1->View patient record\n",LIST);
	print_colored_text("2->View today's reservations\n",LIST);
	print_colored_text("3->Exit\n",LIST);
	print_colored_text("--------------------------------\n",LIGHTYELLOW);

	
	scanf("%d",&userChoise);
	switch(userChoise){
		case 1:
			View_patient_record(USER_MODE);
		break;
		case 2:
			view_reservations(USER_MODE);
		break;
		case 3:
			exit(0);
		break;
	}
}


void check_password(){
	u8  tries = 0;	
		while( tries < 3 ){
				print_colored_text("Enter the password : ",INPUTCol);
				scanf("%d",&Password);
			if(Password == CORRECT_PASSWORD){
				check_pass_var = TRUE;
				print_colored_text("Correct Password\n",GREEN);
				Sleep(500);
				return;

			}else{
				print_colored_text("Wrong Password\n",RED);
				tries++;
			}
		}
		if(tries == 3){
			  print_colored_text("Access denied. Too many incorrect attempts.\n",RED);
			  check_pass_var = FALSE; 
			  Sleep(500);
			  return;
		}	
	
}
u8 search_ID(u8 id){
		node* current = head;
		
		while((current!= 0)  && (current-> data.ID != id)){
			current=current ->next;
		}

		if(current == 0){
			return FALSE;
		}else{
			return TRUE;
		}
}

void reserve_slots(patient* patientData){
    u8 chooseSlot, numReserved=0, i;
    
    for(i = 0; i < SLOTSNUM; i++){
        if(reservedSlots[i] == 0){  // Only show available slots
            print_colored_text(slots[i], 10);
            print_colored_text("\n", 10);
        } else {
            numReserved++;
        }
    }
    
    if(numReserved == SLOTSNUM){
        print_colored_text("No Available Slots\n",RED);
        return;
    }
    
    print_colored_text("Choose a slot: ",INPUTCol);
    scanf("%d",&chooseSlot);
    
    if(chooseSlot < 1 || chooseSlot > SLOTSNUM){
        print_colored_text("Invalid slot number\n",RED);
        return;
    }
    
    if(reservedSlots[chooseSlot-1] == 1){
        print_colored_text("Slot already reserved!\n", RED);
        return;
    }
    
    patientData->slot = chooseSlot;
    reservedSlots[chooseSlot-1] = 1;
    print_colored_text("Slot reserved successfully!\n", GREEN);
}

void add_new_patient(){
	u8 id,checkGender,now;
	print_colored_text("Enter patient's ID: ",INPUTCol);
	scanf("%d",&id);
	if(search_ID(id)){
		print_colored_text("This Patient Is Already Exist In The System\n",RED);
		Sleep(500);
		menu_admin();
		return;
	}
	newPatient.ID=id;
	print_colored_text("Enter patient's Name: ",INPUTCol);
	scanf(" %[^\n]", newPatient.name);
	
	print_colored_text("Enter patient's Age: ",INPUTCol);
	while(1){
    scanf("%d",&newPatient.age);
    if(newPatient.age > 0 && newPatient.age < 120) break;
    print_colored_text("Please enter a valid age (1-120): ",4);
	}
	
	print_colored_text("Enter patient's Gender: F->Female  M->Male :",INPUTCol);
	scanf(" %c",&checkGender);
	if(checkGender == 'F' || checkGender == 'f'  ){
	newPatient.gender = 'F';
	}else if(checkGender == 'M' || checkGender == 'm'  ){
	newPatient.gender = 'M';
	}else{
		print_colored_text("Invalid Input\n",4);
		Sleep(500);
		return;
	}
	
	print_colored_text("Do You Want To Reserve Now?(y/n):",INPUTCol);
	scanf(" %c",&now);
	if(now == 'y' || now == 'Y'){
		 reserve_slots(&newPatient);
	}
	insertAtLast(newPatient);
	save_patients_to_file();
	menu_admin();
	return;
	

}
node* find_patient(u8 id) {
    node* current = head;
    while (current != NULL) {
        if (current->data.ID == id) {
            return current; 
        }
        current = current->next;
    }
    return NULL; 
}


void Cancel_reservation(){
	u8 id;
	print_colored_text("Enter Patient's ID: ",INPUTCol);
	scanf("%d",&id);
	if(!search_ID(id)){
		print_colored_text("This Patient Is Not Exist In The System\n",RED);
		menu_admin();
		return;
	}
	node* oldPatient = find_patient(id);
	if(oldPatient->data.slot != 0){
		reservedSlots[oldPatient->data.slot - 1] = 0;
	}
	oldPatient->data.slot= 0 ;
	deleteElement(oldPatient->data);
	save_patients_to_file();
	print_colored_text("Reservation Cancelled\n",GREEN);

	menu_admin();
	return;
		
}

void Edit_patient_record(){
	u8 id;
	print_colored_text("Enter Patient's ID: ",INPUTCol);
	scanf("%d",&id);
	if(!search_ID(id)){
		print_colored_text("This Patient Is Not Exist In The System\n",RED);
		Sleep(500);
		menu_admin();
	}
	node* oldPatient = find_patient(id);
	if(oldPatient->data.slot != 0){
		reservedSlots[oldPatient->data.slot - 1] = 0;
	}
	oldPatient->data.slot= 0 ;
	reserve_slots(&oldPatient->data);
	printf("Done\n");

	save_patients_to_file();
	menu_admin();
	return;
	}

void View_patient_record(u8 Mode){
	u8 id;
	print_colored_text("Enter Patient's ID: ",INPUTCol);
	scanf("%d",&id);
	if(!search_ID(id)){
		print_colored_text("This Patient Is Not Exist In The System\n",RED);
		Sleep(500);
	}else{
	node* viewPatient = find_patient(id);
	
		print_colored_text("--------------------------------\n",LIGHTYELLOW);
		printf("Patiant's ID :%d \n",viewPatient -> data.ID);
		printf("Patiant's Name :%s \n",viewPatient -> data.name);
		printf("Patiant's Age :%d \n",viewPatient -> data.age);
		if(viewPatient -> data.gender == 'M'){
		printf("Patiant's gender :Male \n");
		}else if(viewPatient -> data.gender == 'F'){
		printf("Patiant's gender :Female \n");
		}
		if(viewPatient->data.slot == 0){
			printf("No reservation\n");
		} else {
			printf("Reserved %s\n", slots[viewPatient->data.slot - 1]);
		}
		print_colored_text("--------------------------------\n",LIGHTYELLOW);

	}
	if(Mode == ADMIN_MODE){
	menu_admin();
	}else{
	menu_user();}
	return;

	
}
void view_reservations(u8 Mode){
    FILE *file = fopen("patients.csv", "r");
    if(file == NULL){
        print_colored_text("Error opening file.\n", RED);
        return;
    }

    char line[100];
    u8 found = 0;

    
    fgets(line, sizeof(line), file);

    while(fgets(line, sizeof(line), file)) {
        int id, age, slot;
        char name[50], gender;
        
      
        if(sscanf(line, "%d,%49[^,],%d,%c,%d", &id, name, &age, &gender, &slot) == 5) {
            if(slot != 0){
                printf("Patient ID: %d\t", id);
                printf("%s\n", slots[slot - 1]);
                found = 1;
            }
        }
    }

    fclose(file);

    if(!found){
        print_colored_text("No reservations yet.\n", RED);
    }

    Sleep(500);
    if(Mode == ADMIN_MODE){
        menu_admin();
    } else {
        menu_user();
    }
}



void save_patients_to_file(){
    FILE *file = fopen("patients.csv", "w");
    if (file == NULL) {
        printf("Error opening file to write.\n");
        return;
    }

    fprintf(file, "ID,Name,Age,Gender,Slot\n");

    node *temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%d,%c,%d\n", temp->data.ID, temp->data.name, temp->data.age, temp->data.gender, temp->data.slot);
        temp = temp->next;
    }

    fclose(file);
}
void load_patients_from_file() {
    FILE *fp = fopen("patients.csv", "r");
    if (fp == NULL) {
        printf("File not found. Starting with empty list.\n");
        return;
    }

    char line[100];
    fgets(line, sizeof(line), fp); 

    while (fgets(line, sizeof(line), fp)) {
        patient p;
        sscanf(line, "%d,%19[^,],%d,%c,%d", &p.ID, p.name, &p.age, &p.gender, &p.slot);
        
        insertAtLast(p);

        if(p.slot >= 1 && p.slot <= SLOTSNUM){
            reservedSlots[p.slot - 1] = 1;
        }
    }

    fclose(fp);
}



