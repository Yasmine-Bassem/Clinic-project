# Patient Management System

This project implements a simple Patient Management System in C, utilizing a single linked list to manage patient records. It provides both an administrator mode for managing patient data and a user mode for viewing records and reservations. The system allows for adding new patients, editing existing records, canceling reservations, and viewing patient and reservation details. Patient data is persisted by saving and loading from a CSV file.

## Features

- Admin Mode: Secure access with password authentication to manage patient records.
- User Mode: Allows patients to view their records and reservations.
- Patient Records: Add, edit, and view patient details including ID, name, age, gender, and reservation slot.
- Appointment Reservation: Reserve and cancel appointment slots.
- Linked List Implementation: Patient data is managed using a single linked list.
- Data Persistence: Patient records are saved to and loaded from a patients.csv file.
- Colored Console Output: Enhances user experience with colored text in the console.

## How to Compile and Run

To compile this project, you will need a C compiler (e.g., GCC). The project uses windows.h for colored console output, so it is primarily designed for Windows environments.

1. Compile the source files:
2. Run the executable:

## Project Structure

- main.c: Contains the main application logic, including mode selection (Admin/User) and password checking.
- file.h: Header file for file.c, defining constants, function prototypes, and global variables related to the patient management system.
- file.c: Implements core functionalities such as admin and user menus, password checking, adding/editing/viewing patient records, and managing reservations.
- SINGLE_LINKED_LIST.h: Header file for SINGLE_LINKED_LIST.c, defining the patient and node structures and prototypes for linked list operations.
- SINGLE_LINKED_LIST.c: Implements the single linked list data structure and its operations (insert, delete, get size, search).
- stdtypes.h: Defines custom data types (e.g., u8, u16, u32) for better code readability and portability.
- patients.csv: (Generated) Stores patient data for persistence.
