#include <iostream>
#include <fstream>
//#include<conio.h>
#include <string.h>
#include <stdlib.h>

// define maximum number of patients in a queue
#define MAXPATIENTS 100
using namespace std;
// define structure for patient data
struct patient
{
char FirstName[50];
char LastName[50];
char ID[20];
};
// define class for queue
class queue
{
public:
queue (void);
int AddPatientAtEnd (patient p);
int AddPatientAtBeginning (patient p);
patient GetNextPatient (void);
int RemoveDeadPatient (patient * p);
void OutputList (void);
char DepartmentName[50];
private:
int NumberOfPatients;
patient List[MAXPATIENTS];
};
// declare member functions for queue
queue::queue ()
{
// constructor
NumberOfPatients = 0;
}
int queue::AddPatientAtEnd (patient p)
{
// adds a normal patient to the end of the queue.
// returns 1 if successful, 0 if queue is full.
if (NumberOfPatients >= MAXPATIENTS)
{
// queue is full
return 0;
}
// put in new patient
else
List[NumberOfPatients] = p;  NumberOfPatients++;
return 1;
}
int queue::AddPatientAtBeginning (patient p)
{
// adds a critically ill patient to the beginning of the queue.
// returns 1 if successful, 0 if queue is full.
int i;
if (NumberOfPatients >= MAXPATIENTS)
{
// queue is full
return 0;
}
// move all patients one position back in queue
for (i = NumberOfPatients-1; i >= 0; i--)
{
List[i+1] = List[i];
}
// put in new patient
List[0] = p;  NumberOfPatients++;
return 1;
}
patient queue::GetNextPatient (void)
{
// gets the patient that is first in the queue.
// returns patient with no ID if queue is empty
int i;  patient p;
if (NumberOfPatients == 0) {
// queue is empty
strcpy(p.ID,"");
return p;}
// get first patient
p = List[0];
// move all remaining patients one position forward in queue
NumberOfPatients--;
for (i=0; i<NumberOfPatients; i++)
{
List[i] = List[i+1];
}
// return patient
return p;
}
int queue::RemoveDeadPatient (patient * p)
{
// removes a patient from queue.
// returns 1 if successful, 0 if patient not found
int i, j, found = 0;
// search for patient
for (i=0; i<NumberOfPatients; i++)
{
if (strcmp(List[i].ID, p->ID) == 0)
{
// patient found in queue
*p = List[i];  found = 1;
// move all following patients one position forward in queue
NumberOfPatients;
for (j=i; j<NumberOfPatients; j++)
{
List[j] = List[j+1];
}
}
}
return found;
}
void queue::OutputList (void)
{
// lists entire queue on screen
int i;
if (NumberOfPatients == 0)
{
cout << "Queue is empty";
}
else
{
ofstream outfile;
outfile.open("patientsDetails.txt");

for (i=0; i<NumberOfPatients; i++)
{
cout<< "\n" << List[i].FirstName;
outfile << List[i].FirstName << " ";
cout<< "\n " << List[i].LastName;
outfile << List[i].LastName << " ";
cout<< "\n " << List[i].ID;
outfile << List[i].ID << "\n";
}
outfile.close();
}
}
// declare functions used by main:
patient InputPatient (void)
{
// this function asks user for patient data.
patient p;
cout << "\n Please enter data for new patient First name: ";
cin.getline(p.FirstName, sizeof(p.FirstName));
cout << "\n Last name: ";
cin.getline(p.LastName, sizeof(p.LastName));
cout << "\n Social security number: ";
cin.getline(p.ID, sizeof(p.ID));
// check if data valid
if (p.FirstName[0]==0 || p.LastName[0]==0 || p.ID[0]==0)
{
// rejected
strcpy(p.ID,"");
cout << "Error: Data not valid. Operation cancelled.";
//getch();
}
return p;
}
void OutputPatient (patient * p)
{
// this function outputs patient data to the screen
if (p == NULL || p->ID[0]==0)
{
cout << "No patient";
return;
}
else
cout << "\n Patient data:";
cout << "\n First name: " << p->FirstName;
cout << "\n Last name: " << p->LastName;
cout << "\n Social security number: " << p->ID;
}
int ReadNumber()
{
// this function reads an integer number from the keyboard.
// it is used because input with cin >> doesn’t work properly!
char buffer[20];
cin.getline(buffer, sizeof(buffer));
return atoi(buffer);
}
void DepartmentMenu (queue * q)
{
// this function defines the user interface with menu for one department
int choice = 0, success;  patient p;
while (choice != 6)
{
// clear screen

// print menu
cout << "\n Welcome to department: " << q->DepartmentName;
cout << "\n  Please enter your choice:";
cout << "\n  1:  Add normal patient";
cout << "\n  2:  Add critically ill patient";
cout << "\n  3:  Take out patient for operation";
cout << "\n  4:  Remove dead patient from queue";
cout << "\n  5:  List queue";
cout << "\n  6:  Change department or exit";
// get user choice
choice = ReadNumber();
// do indicated action
switch (choice)
{
case 1:   // Add normal patient
p = InputPatient();
if (p.ID[0])
{
success = q->AddPatientAtEnd(p);

if (success)
{
cout << "Patient added:";
}
else
{
// error
cout << "Error: The queue is full. Cannot add patient:";
}
OutputPatient(&p);
cout << "Press any key";
//getch();
}
break;
case 2:   // Add critically ill patient
p = InputPatient();
if (p.ID[0])
{
success = q->AddPatientAtBeginning(p);

if (success)
{
cout << "Patient added:";
}
else
{
// error
cout << "Error: The queue is full. Cannot add patient:";
}
OutputPatient(&p);
cout << "Press any key";
//getch();
}
break;
case 3:   // Take out patient for operation
p = q->GetNextPatient();

if (p.ID[0])
{
cout << "Patient to operate:";
OutputPatient(&p);}
else
{
cout << "There is no patient to operate.";
}
cout << "Press any key";
//getch();
break;
case 4:   // Remove dead patient from queue
p = InputPatient();
if (p.ID[0])
{
success = q->RemoveDeadPatient(&p);

if (success)
{
cout << "Patient removed:";
}
else
{
// error
cout << "Error: Cannot find patient:";
}
OutputPatient(&p);
cout << "Press any key";
//getch();
}
break;
case 5:   // List queue

q->OutputList();
cout << "Press any key";
//getch();  break;
}
}
}
// main function defining queues and main menu
int main()
{
int i, MenuChoice = 0;
// define three queues
queue departments[3];
// set department names
strcpy (departments[0].DepartmentName, "\n Heart clinic");
strcpy (departments[1].DepartmentName, "\n Lung clinic");
strcpy (departments[2].DepartmentName, "\n Plastic surgery");
while (MenuChoice != 4)
{
// clear screen

// print menu
cout << "Welcome to Vamsi Krishna Hospital";
cout << "\n Please enter your choice:";
for (i = 0; i < 3; i++)
{
// write menu item for department i
cout << "" << (i+1) << ":  " << departments[i].DepartmentName;
}
cout << "4:  Exit";
// get user choice
MenuChoice = ReadNumber();
// is it a department name?
if (MenuChoice >= 1 && MenuChoice <= 3)
{
// call submenu for department
// (using pointer arithmetics here:)
DepartmentMenu (departments + (MenuChoice-1));
}
}
}
