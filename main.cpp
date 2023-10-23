/*main.cpp*/
//
// Author: Rimsha Rizvi
//
// Project: C++ program for a simple class reservation system
//
// The registration system inputs registration data from a file, and supports 9 commands:
//      1. help: more info
//      2. stats: no. of students enrolled + waitlisted in each class
//      3. list: outputs specific class info
//      4. increase: increases enrollment capacity of specified class
//      5. enroll: enrolls student in specified class
//      6. waitlist: waitlists student in specified class
//      7. process: attempts to open the given filename and input commands from this file
//      8. output: opens the given file for output and writes the current enrollment data to this file
//      9. quit: the program exits the command loop
//

#include <iostream>
#include <string>
#include "classreg.h"
#include <fstream>

using namespace std;


//
// 1. help command
// 
// provides more information to the user
//
void help_command(){
    cout << "stats" << endl;
    cout << "list class" << endl;
    cout << "increase class capacity" << endl;
    cout << "enroll class netid" << endl;
    cout << "waitlist class netid priority" << endl;
    cout << "process filename" << endl;
    cout << "output filename" << endl;
    cout << "quit" << endl;
}


//
// 2. stats command
// 
// the program outputs the number of students currently enrolled and waitlisted in each class.
//
void stats_command(ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251){
    cout << cs111.getName() << ": enrolled=" << cs111.numEnrolled() << ", waitlisted=" << cs111.numWaitlisted() << endl;
    cout << cs141.getName() << ": enrolled=" << cs141.numEnrolled() << ", waitlisted=" << cs141.numWaitlisted() << endl;
    cout << cs151.getName() << ": enrolled=" << cs151.numEnrolled() << ", waitlisted=" << cs151.numWaitlisted() << endl;
    cout << cs211.getName() << ": enrolled=" << cs211.numEnrolled() << ", waitlisted=" << cs211.numWaitlisted() << endl;
    cout << cs251.getName() << ": enrolled=" << cs251.numEnrolled() << ", waitlisted=" << cs251.numWaitlisted() << endl;
}


//
// 3. list function
//

//
// printing_data:
//  
// outputs the information needed for this function given the specific class object
//
void printing_data(ClassReg classreg){
    
    string* enrolled_names = new string[classreg.numEnrolled()]; //storing in a list to sort alphabetically
    
    cout << classreg.getName() << endl;
    cout << "Capacity: " << classreg.getCapacity() << endl;
    
    int N = classreg.numEnrolled();
    
    for (int i = 0; i<N; i++){
        enrolled_names[i] = classreg.retrieveEnrolledStudent(i);
    }
    
    int minIndex; //selection sort

    for (int i = 0; i < N-1; i++)
    {
        minIndex = i;  //to start, assume i is smallest element:
        for (int j = i+1; j < N; j++)
        {
            if (enrolled_names[j] < enrolled_names[minIndex])  // found a smaller one
            {
                minIndex = j;
            }
        }
        string temp; //storing the value in a temp variable to not lose original data

        temp = enrolled_names[i]; //sorting by name
        enrolled_names[i] = enrolled_names[minIndex];
        enrolled_names[minIndex] = temp;
    }

    cout << "Enrolled (" << classreg.numEnrolled() << "): ";
    for (int i = 0; i< N; i++){
        cout << enrolled_names[i] << " ";
    }
    cout << endl;
    
    cout << "Waitlisted (" << classreg.numWaitlisted() << "): ";
    for (int i = 0; i< classreg.numWaitlisted(); i++){
        string name; int priority;
        classreg.retrieveWaitlistedStudent(i, name, priority); 
        cout << name << " (" << priority << ") " ;
    }
    cout << endl;
    
    delete[] enrolled_names;
    
}

//
// lists_command:
//  
// function to output data according to the userinput class
//
void lists_command(string name, ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251){
    if (name == "cs111" or name == "cs141" or name == "cs151" or name == "cs211" or name == "cs251"){
        if (name == "cs111"){
            printing_data(cs111);
        }
        else if (name == "cs141"){
            printing_data(cs141);
        }
        else if (name == "cs151"){
            printing_data(cs151);
        }
        else if (name == "cs211"){
            printing_data(cs211);
        }
        else if (name == "cs251"){
            printing_data(cs251);
        }
    }
    else{
        cout << "**Invalid class name, try again..." << endl;
    }
}


//
// 4. increase function
//

//
// increase_cap:
//  
// the program changes the enrollment capacity of the specified class
//
void increase_cap(ClassReg& classreg, int new_cap){
    if (new_cap >= classreg.getCapacity()){
        classreg.setCapacity(new_cap);
        cout << classreg.getName() << endl;
        cout << "Capacity: " << classreg.getCapacity() << endl;
    }
    else{
        cout << "**Error, cannot decrease class capacity, ignored..." << endl;
    }
}

//
// increase_command:
//  
// function to increment enrollment capacity according to the userinput class
//
void increase_command(string name, int new_cap, 
                      ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251){
    
    if (name == "cs111" or name == "cs141" or name == "cs151" or name == "cs211" or name == "cs251"){
        if (name == "cs111"){
            increase_cap(cs111, new_cap);
        }
        else if (name == "cs141"){
            increase_cap(cs141, new_cap);
        }
        else if (name == "cs151"){
            increase_cap(cs151, new_cap);
        }
        else if (name == "cs211"){
            increase_cap(cs211, new_cap);
        }
        else if (name == "cs251"){
            increase_cap(cs251, new_cap);
        }
    }
    else{
        cout << "**Invalid class name, try again..." << endl;
    }
}


//
// 5. enrolling function
//

//
// enroll_names:
//  
// the program attempts to enroll the student in the specified class
//
void enroll_names(ClassReg& classreg, string netid){
    
    int index = classreg.searchEnrolled(netid); //check if student enrolled in class
    
    if (index != -1){  //if they are enrolled
        cout << "Student '" << netid << "' enrolled in " << classreg.getName() << endl; //nothing happens
    }
    else{ //if not enrolled
        int position = classreg.searchWaitlisted(netid); //check waitlist
        if (position != -1){ //if found in waitlist
            if (classreg.getCapacity() > classreg.numEnrolled()){ //is there room in the class?
                classreg.removeWaitlistedStudent(position);
                classreg.enrollStudent(netid);
                cout << "Student '" << netid << "' enrolled in " << classreg.getName() << endl;
            }
            else{ //no room
                cout << "Class full, '" << netid << "' waitlisted for " << classreg.getName() << endl;
            }
        }
        else{ //if not found in waitlist 
            // not enrolled not in waitlist
            if (classreg.getCapacity() > classreg.numEnrolled()){ //is there room in the class?
                classreg.enrollStudent(netid);
                cout << "Student '" << netid << "' enrolled in " << classreg.getName() << endl;
            }
            else{ //no room
                if (classreg.numWaitlisted() == 0){ //priority sets to 1 if no one in waitlist
                    classreg.waitlistStudent(netid, 1);
                } 
                else{ //finding priority
                    string temp; int priority;
                    classreg.retrieveWaitlistedStudent(classreg.numWaitlisted()-1, temp, priority); //last index
                    classreg.waitlistStudent(netid, priority);
                }
                cout << "Class full, '" << netid << "' waitlisted for " << classreg.getName() << endl;
            }
        }
    }   
}

//
// enroll_command:
//  
// function to enroll student into the userinput class
//
void enroll_command(string name, string netid, 
                    ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251){
    
    if (name == "cs111" or name == "cs141" or name == "cs151" or name == "cs211" or name == "cs251"){
        if (name == "cs111"){
            enroll_names(cs111, netid);
        }
        else if (name == "cs141"){
            enroll_names(cs141, netid);
        }
        else if (name == "cs151"){
            enroll_names(cs151, netid);
        }
        else if (name == "cs211"){
            enroll_names(cs211, netid);
        }
        else if (name == "cs251"){
            enroll_names(cs251, netid);
        }
    }
    else{
        cout << "**Invalid class name, try again..." << endl;
    }
}


//
// 6. waitlisting function
//

//
// waitlist_names:
//  
// the program attempts to waitlist the student in the specified class
//
void waitlist_names(ClassReg& classreg, string netid, int priority){
    
    int index = classreg.searchEnrolled(netid); //check if student enrolled in class
    
    if (index != -1){  //if found
        cout << "Student '" << netid << "' enrolled in " << classreg.getName() << endl; //nothing happens
    }
    else{ //if not enrolled
        int position = classreg.searchWaitlisted(netid); //check waitlist
        if (position != -1){ //if found in waitlist
            classreg.removeWaitlistedStudent(position);
            classreg.waitlistStudent(netid, priority);
            cout << "Student '" << netid << "' waitlisted for " << classreg.getName() << endl;
        }
        else{ //if not found in waitlist 
            // not enrolled not in waitlist
            classreg.waitlistStudent(netid, priority);
            cout << "Student '" << netid << "' waitlisted for " << classreg.getName() << endl;
        }
    }   
    
}

//
// waitlist_command:
//  
// function to waitlist student into the userinput class
//
void waitlist_command(string name, string netid, int priority,
                      ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251){
    
    if (name == "cs111" or name == "cs141" or name == "cs151" or name == "cs211" or name == "cs251"){
        if (name == "cs111"){
            waitlist_names(cs111, netid, priority);
        }
        else if (name == "cs141"){
            waitlist_names(cs141, netid, priority);
        }
        else if (name == "cs151"){
            waitlist_names(cs151, netid, priority);
        }
        else if (name == "cs211"){
            waitlist_names(cs211, netid, priority);
        }
        else if (name == "cs251"){
            waitlist_names(cs251, netid, priority);
        }
    }
    else{
        cout << "**Invalid class name, try again..." << endl;
    }
}


//
// input file
// 
// function to input file data into variables
//
void inputFile(ClassReg& classreg, ifstream& infile){
    
    string name;
    infile >> name;
    classreg.setName(name);
    
    int capacity;
    infile >> capacity;
    classreg.setCapacity(capacity);
    
    string netid;
    infile >> netid;
    
    while (netid != "#"){
        classreg.enrollStudent(netid);
        infile >> netid;
    }
    
    string wait_netid; int priority;
    infile >> wait_netid;
    
    while (wait_netid != "#"){
        infile >> priority;
        classreg.waitlistStudent(wait_netid, priority);
        infile >> wait_netid;
    }
}


//
// 8. output file
// 

//
// output_classreg:
// 
// opens the given file for output and writes the current enrollment data to this file
//
void output_classreg(ofstream& outfile, ClassReg classreg){
    
    outfile << classreg.getName() << endl;
    outfile << classreg.getCapacity() << endl;
    
    for (int i = 0; i < classreg.numEnrolled(); i++){
        outfile << classreg.retrieveEnrolledStudent(i) << " ";
    }
    outfile << "#" << endl;
    
    for (int i = 0; i < classreg.numWaitlisted(); i++){
        string netid; int priority;
        classreg.retrieveWaitlistedStudent(i, netid, priority);
        outfile << netid << " " << priority << " "; 
    }
    outfile << "#" << endl;
}

//
// output_function:
// 
// function to output all 5 ClassReg objects into the file
//
void output_function(ofstream& outfile, 
                     ClassReg cs111, ClassReg cs141, ClassReg cs151, ClassReg cs211, ClassReg cs251){
    
    output_classreg(outfile, cs111);
    output_classreg(outfile, cs141);
    output_classreg(outfile, cs151);
    output_classreg(outfile, cs211);
    output_classreg(outfile, cs251);
}


//
// 7. process command
// 
// the program attempts to open the given filename and input commands from this file 
// this occurs until “q” or “quit” is encountered.
//
void processCommands (istream& input, bool promptUser, 
                      ClassReg& cs111, ClassReg& cs141, ClassReg& cs151, ClassReg& cs211, ClassReg& cs251)
{
    string command;
    if(promptUser)// prompt user at the keyboard:
    {
        cout << endl;
        cout << "Enter a command (help for more info, quit to stop)>" << endl;
    }
    input >> command;
    
    while (command != "q" and command != "quit"){ //9. quit/q stops the loop, meaning it returns to main
        
        if (command == "h" or command == "help"){
            help_command();
        }
        else if (command == "stats" or command == "s"){
            stats_command(cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "list" or command == "l"){
            string name;
            input >> name;
            lists_command(name, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "increase" or command == "i"){
            string name; int new_cap;
            input >> name >> new_cap;
            increase_command(name, new_cap, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "enroll" or command == "e"){
            string netid; string name;
            input >> name >> netid;
            enroll_command(name, netid, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "waitlist" or command == "w"){
            string name; string netid; int priority;
            input >> name >> netid >> priority;
            waitlist_command(name, netid, priority, cs111, cs141, cs151, cs211, cs251);
        }
        else if (command == "process" or command == "p"){
            string newfile; //user enter new file in order to process commands
            input >> newfile;
            
            ifstream infile;
            infile.open(newfile);

            if (infile.good()) 
            {
                cout << "**Processing commands from '" << newfile << "'" << endl;
                processCommands (infile, false, cs111, cs141, cs151, cs211, cs251); 
                cout << "**Done processing '" << newfile << "'" << endl;
            }
            else{
                cout << "**Unable to open command file '" << newfile << "'" << endl;
            }
        }
        else if (command == "output" or command == "o"){
            string filename;
            input >> filename;
            
            ofstream outfile;
            outfile.open(filename); //if file doesn't exist, a new file is created of that name
            
            output_function(outfile, cs111, cs141, cs151, cs211, cs251);
            cout << "Enrollment data output to '" << filename << "'" << endl;
            outfile.close();
        }
        else{
            cout << "**Invalid command, please try again..." << endl;
        }
        
        if(promptUser)// prompt user at the keyboard:
        {
            cout << endl;
            cout << "Enter a command (help for more info, quit to stop)>" << endl;
        }
        input >> command;
    }
}


//
// main function
//
int main(){
    
    ClassReg cs111, cs141, cs151, cs211, cs251; //class objects
    
    cout << "**CS Enrollment System**" << endl; 
    
    string filename; 
    cout << "Enter enrollments filename>" <<endl;
    cin >> filename;
    
    ifstream infile;
    infile.open(filename);

    if (!infile.good()) 
    {
        cout << "**Error: unable to open enrollments file '" << filename << "'" << endl;
        return 0;
    }
    
    inputFile(cs111, infile);
    inputFile(cs141, infile);
    inputFile(cs151, infile);
    inputFile(cs211, infile);
    inputFile(cs251, infile);
    
    infile.close();
    
    processCommands(cin, true, cs111, cs141, cs151, cs211, cs251);
    
    cout << "**Done**" << endl;
    
    return 0;
}
    
    
    
