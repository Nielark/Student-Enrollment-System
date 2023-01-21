#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <windows.h>

using namespace std;

// NOTE: USERNAME AND PASSWORD FOR ADMIN LOGIN ARE BOTH "admin".
// PROGRAMMED BY NIELARK
// markdanielmagpantay2001@gamail.com

void menu();
void enroll();
void studentLogin();
void studentEdit();
void editInfo();
void admin();
void searchStudents();
void adminDisplayInfo();
void adminUnenroll();
void enrollmentPeriod();
void displayInfo();
void firstname();
void middlename();
void lastname();
void nameExtension();
void age();
void birthdate();
void address();
void selectGender();
void selectCourse();
void selectYearLevel();
void selectSemester();
void username();
void password();
void selectGenderMenu();
void selectCourseMenu();
void selectYearLevelMenu();
void selectSemesterMenu();
void editConfirmMsg();
void enrollLoading();
void loggingInLoading();
void clean();

struct studentInfo{
    int studentNo;
    char firstname[50];
    char middlename[50];
    char lastname[50];
    char nameExtension[50];
    string gender;
    int age;
    char birthdate[50];
    char address[50];
    string course;
    string yearLevel;
    string semester;
    char username[50];
    char password[50];
};

struct studentInfo students[100];
int choice, i, studEnroll = 0, studEnrollHold, studentNo = 0, editNo = -1, foundStudent = 0, studEdit = 0, adminEdit = 0;
bool enrollment = true;

int main()
{
    system("color 0A");
    start:
    menu();

    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;

    system("CLS");
    switch(choice){
        case 1:
            enroll();
            clean();
            goto start;
            break;

        case 2:
            studentLogin();
            clean();
            goto start;
            break;

        case 3:
            admin();
            clean();
            goto start;
            break;

        case 0:
            return 0;
            break;

        default:
            cout << "Invalid input.\n";
            clean();
            goto start;
    }
}

void menu(){
    cout << "================================\n";
    cout << "E N R O L L M E N T  S Y S T E M\n\n";
    cout << "[1] - E N R O L L  N O W\n";
    cout << "[2] - S T U D E N T  L O G I N\n";
    cout << "[3] - A D M I N\n";
    cout << "[0] - E X I T\n";
    cout << "================================\n\n";
}

void enroll(){
    int enroll;

    if(enrollment == true){
        studentNo++;

        cout << "Please fill in the information below\n\n";

        students[studEnroll].studentNo = studentNo; // Generate student number for every enrolled students.
        firstname();
        middlename();
        lastname();
        nameExtension();
        selectGender();
        age();
        birthdate();
        address();
        selectCourse();
        selectYearLevel();
        selectSemester();

        cout << endl;
        cout << "The username and password will be used for your student account.\n\n";
        username();
        password();

        invalid:
        cout << endl;
        cout << "=================\n";
        cout << "[1] - E N R O L L\n";
        cout << "[2] - C A N C E L\n";
        cout << "=================\n\n";

        cout << "Enter your choice: ";
        cin >> enroll;

        if(enroll == 1){
            enrollLoading();

            cout << "You are now enrolled.\n";
            studEnroll++;
            studentInfo students[studEnroll];
        }
        else if(enroll == 2){
            cout << "Enrollment has benn cancelled.\n";
            studentNo--;
        }
        else{
            cout << "Invalid Input.\n";
            system("PAUSE");
            goto invalid;
        }
    }
    else{
        cout << "Enrollment was closed\n";
    }
}

void studentLogin(){
    string username, password;

    if(studEnroll != 0){
        cout << "S T U D E N T  L O G I N\n";
        cout << "========================\n\n";

        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        // Loop for matching the username and password to open and display the student information.
        for(i = 0; i < studEnroll; i++){
            if(students[i].username == username && students[i].password == password){
                editNo = i; // Index location of the matched username and password.
                break;
            }
        }

        loggingInLoading();

        if(editNo != -1){
            cout << "You have successfully login " << students[editNo].firstname << " " << students[editNo].lastname << ".\n";
            system("PAUSE");
        }

        studentEdit(); // Function for students info editing and unerollment.
    }
    else{
        cout << "There are no enrolled students.\n";
    }
}

void studentEdit(){
    char unenroll;

    top:
    system("CLS");
    if(editNo != -1){
        cout << "============================\n";
        cout << "[1] - E D I T\n";
        cout << "[2] - U N E N R O L L\n";
        cout << "[3] - D I S P L A Y  I N F O\n";
        cout << "[4] - L O G  O U T\n";
        cout << "============================\n\n";

        cout << "Enter yout choice: ";
        cin >> choice;

        system("CLS");
        if(choice == 1){
            studEdit++;
            studEnrollHold = studEnroll; // Temporarily holds the value of studEnroll.
            studEnroll = editNo; // Stores the value of the editNo to locate the desired student info to edit.
            editInfo(); // calls the editInfo function.
        }
        else if(choice == 2){
            cout << "Are you sure you want to unenroll, [Y] or [N]? ";
            cin >> unenroll;

            if(unenroll == 'Y' || unenroll == 'y'){
                // Loop for deleting the student information and shifting of elements.
                for(i = editNo; i < (studEnroll - 1); i++){
                    students[i] = students[i + 1];
                }

                studEnroll--; // Decrementing the size of the array.
                editNo = -1;
                cout << "Unenrollment Succesful\n";
            }
            else if(unenroll == 'N' || unenroll == 'n'){
                goto top;
            }
            else{
                cout << "Invalid input.\n";
                goto top;
            }
        }
        else if(choice == 3){
            displayInfo();
            clean();
            goto top;
        }
        else if(choice == 4){
            cout << "Loging out......" << endl;
            Sleep(1000);
            editNo = -1;
            Sleep(1000);
            system("CLS");
            main();
        }
    }
    else{
        cout << "Username and password not found.\n";
    }
}

void editInfo(){
    cout << endl;
    cout << "========================================================================\n";
    cout << "[1] - F I R S T N A M E         \t[8] - A D D R E S S\n";
    cout << "[2] - M I D D L E N A M E       \t[9] - C O U R S E\n";
    cout << "[3] - L A S T N A M E           \t[10] - Y E A R  L E V E L\n";
    cout << "[4] - N A M E  E X T E N S I O N\t[11] - S E M E S T E R\n";
    cout << "[5] - G E N D E R               \t[12] - U S E R N A M E\n";
    cout << "[6] - A G E                     \t[13] - P A S S W O R D\n";
    cout << "[7] - B I R T H  D A T E        \t[14] - D I S P L A Y  Y O U R  I N F O\n";
    cout << "\t\t\t[0] - B A C K\n";
    cout << "========================================================================\n";

    invalid:
    cout << "\nEnter your choice to edit the information: ";
    cin >> choice;
    cout << endl;

    switch(choice){
        case 1:
            firstname();
            editConfirmMsg();
            goto invalid;
            break;

        case 2:
            middlename();
            editConfirmMsg();
            goto invalid;
            break;

        case 3:
            lastname();
            editConfirmMsg();
            goto invalid;
            break;

        case 4:
            nameExtension();
            editConfirmMsg();
            goto invalid;
            break;

        case 5:
            selectGender();
            editConfirmMsg();
            goto invalid;
            break;

        case 6:
            age();
            editConfirmMsg();
            goto invalid;
            break;

        case 7:
            birthdate();
            editConfirmMsg();
            goto invalid;
            break;

        case 8:
            address();
            editConfirmMsg();
            goto invalid;
            break;

        case 9:
            selectCourse();
            editConfirmMsg();
            goto invalid;
            break;

        case 10:
            selectYearLevel();
            editConfirmMsg();
            goto invalid;
            break;

        case 11:
            selectSemester();
            editConfirmMsg();
            goto invalid;
            break;

        case 12:
            username();
            editConfirmMsg();
            goto invalid;
            break;

        case 13:
            password();
            editConfirmMsg();
            goto invalid;
            break;

        case 14:
            displayInfo();
            goto invalid;
            break;

        case 0:
            studEnroll = studEnrollHold; // Stores back the previous value of studEnroll that is temporily stored in studEnrollHold.
            if(studEdit != 0){
                studEdit = 0;
                studentEdit();
            }
            break;

         default:
            cout << "Invalid Input.\n";
            clean();
            goto invalid;
            break;
    }
}

void admin(){
    string adminUsername = "admin", adminPassword = "admin", getAdminUser, getAdminPass;

    cout << "A D M I N  L O G I N\n";
    cout << "====================\n\n";
    cout << "Enter username: ";
    cin >> getAdminUser;

    cout << "Enter passsword: ";
    cin >> getAdminPass;

    loggingInLoading();

    system("CLS");
    top:
    if(getAdminUser == adminUsername && getAdminPass == adminPassword){
        cout << "==============================================\n";
        cout << "A D M I N I S T R A T O R  M A N A G E M E N T\n\n";
        cout << "[1] - S E A R C H  S T U D E N T\n";
        cout << "[2] - D I S P L A Y  S T U D E N T  I N F O\n";
        cout << "[3] - E D I T  S T U D E N T  I N F O\n";
        cout << "[4] - U N E N R O L L  S T U D E N T\n";

        // Change the display of the text either enrollment is open or closed.
        if(enrollment == true){
            cout << "[5] - C L O S E D  E N R O L L M E N T\n";
        }
        else{
            cout << "[5] - O P E N  E N R O L L M E N T\n";
        }
        cout << "[0] - L O G  O U T\n";
        cout << "==============================================\n\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        system("CLS");
        if(choice == 1){
            searchStudents();
            clean();
            goto top;
        }
        else if(choice == 2){
            adminDisplayInfo();
            clean();
            goto top;
        }
        else if(choice == 3){
            searchStudents();

            if(foundStudent != 0){
                studEnrollHold = studEnroll; // Temporarily holds the value of studEnroll.
                studEnroll = editNo; // Stores the value of the editNo to locate the desired student info to edit.
                    if(studEnrollHold != 0){
                    adminEdit++;
                    editInfo();
                    adminEdit = 0;
                }
            }

            editNo = -1;
            clean();
            goto top;
        }
        else if(choice == 4){
            adminUnenroll();
            clean();
            goto top;
        }
        else if(choice == 5){
            enrollmentPeriod();
            clean();
            goto top;
        }
        else if(choice == 0){
            cout << "Logging out...\n";
            Sleep(1000);
            system("CLS");
            main();

        }
        else{
            cout << "Invalid input.\n";
            clean();
            goto top;
        }
    }
    else{
        cout << "Password and username not found\n";
    }
}

void searchStudents(){
    string search, convertOutput;
    stringstream convert; // String object.

    if(studEnroll != 0){
        cout << "Enter a student information(Ex: Student No./Firstname/Lastname) to search for student: ";
        cin.ignore();
        getline(cin, search);
        cout << endl;

        // Loop for finding the matched information in the enrolled students.
        for(i = 0; i < studEnroll; i++){
            convert<<students[i].studentNo; // Insert the value of student number in struct into the steam.
            convert>>convertOutput; // Extract the converted data out of the stream and store it in a string variable.

            if(search == convertOutput ||
            search == students[i].firstname ||
            search == students[i].middlename ||
            search == students[i].lastname)
            {
                displayInfo();
                editNo = i;
                foundStudent++; // Increments when the information matches from the enrolled students.\n;
                break;
            }
        }

        if(foundStudent == 0){
            cout << "Information doesn't match with the enrolled students.\n";
        }

        foundStudent = 0;
    }
    else{
        cout << "There are no enrolled student\n";
    }
}

void adminDisplayInfo(){
    int age, course, yearLevel, sem, filterCtr = 0;
    char gender;

    if(studEnroll != 0){
        top:
        cout << "==========================================\n";
        cout << "[1] - D I S P L A Y  A L L\n";
        cout << "[2] - F I L T E R  B Y  G E N D E R\n";
        cout << "[3] - F I L T E R  B Y  A G E\n";
        cout << "[4] - F I L T E R  B Y  C O U R S E\n";
        cout << "[5] - F I L T E R  B Y  Y E A R  L E V E L\n";
        cout << "[6] - F I L T E R  B Y  S E M E S T E R\n";
        cout << "[0] - B A C K\n";
        cout << "==========================================\n\n";

        cout << "Enter your choice to filter the students: ";
        cin >> choice;
        cout << endl;

        switch(choice){
            case 1:
                for(i = 0; i < studEnroll; i++){
                    displayInfo();
                }
                clean();
                goto top;
                break;

            case 2:
                gender:
                selectGenderMenu();

                cout << "Enter your choice to filter the students: ";
                cin >> gender;
                cout << endl;

                for(i = 0; i < studEnroll; i++){
                    if(gender == 'M' || gender == 'm'){
                        if(students[i].gender == "Male"){
                            filterCtr++; // Count if the data matches any student information.
                            displayInfo();
                        }
                    }
                    else if(gender == 'F' || gender == 'f'){
                        if(students[i].gender == "Female"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else{
                        cout << "Invalid input\n";
                        goto gender;
                    }
                }

                if(filterCtr == 0){
                    cout << "The data did not matched any student information.\n";
                }

                filterCtr = 0;
                clean();
                goto top;
                break;

            case 3:
                cout << "Enter the age to filter the students: ";
                cin >> age;
                cout << endl;

                for(i = 0; i < studEnroll; i++){
                    if(age == students[i].age){
                        filterCtr++;
                        displayInfo();
                    }
                }

                if(filterCtr == 0){
                    cout << "The data did not matched any student information.\n";
                }

                filterCtr = 0;
                clean();
                goto top;
                break;

            case 4:
                course:
                selectCourseMenu();

                cout << "Enter the course to filter the students: ";
                cin >> course;
                cout << endl;

                for(i = 0; i < studEnroll; i++){
                    if(course == 1){
                        if(students[i].course == "Bs Computer Engineering"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(course == 2){
                        if(students[i].course == "Bs Mechanical Engineering"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(course == 3){
                        if(students[i].course == "Bs Chemical Engineering"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(course == 4){
                        if(students[i].course == "Bs Electrical Engineering"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(course == 5){
                        if(students[i].course == "Bs Electronic Engineering"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(course == 5){
                        if(students[i].course == "Bs Software Engineering"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else{
                        cout << "Invalid input\n";
                        goto course;
                    }
                }

                if(filterCtr == 0){
                    cout << "The data did not matched any student information.\n";
                }

                filterCtr = 0;
                clean();
                goto top;
                break;

            case 5:
                yearLevel:
                selectYearLevelMenu();

                cout << "Enter the year level to filter the students: ";
                cin >> yearLevel;
                cout << endl;

                for(i = 0; i < studEnroll; i++){
                    if(yearLevel == 1){
                        if(students[i].yearLevel == "1st year"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(yearLevel == 2){
                        if(students[i].yearLevel == "2nd year"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(yearLevel == 3){
                        if(students[i].yearLevel == "3rd year"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(yearLevel == 4){
                        if(students[i].yearLevel == "4th year"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else{
                        cout << "Invalid input\n";
                        goto yearLevel;
                    }
                }

                if(filterCtr == 0){
                    cout << "The data did not matched any student information.\n";
                }

                filterCtr = 0;
                clean();
                goto top;
                break;

            case 6:
                sem:
                selectSemesterMenu();

                cout << "Enter the semester to filter the students: ";
                cin >> sem;
                cout << endl;

                for(i = 0; i < studEnroll; i++){
                    if(sem == 1){
                        if(students[i].semester == "1st Semester"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(sem == 2){
                        if(students[i].semester == "2nd Semester"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else if(sem == 3){
                        if(students[i].semester == "Summer"){
                            filterCtr++;
                            displayInfo();
                        }
                    }
                    else{
                        cout << "Invalid input\n";
                        goto sem;
                    }
                }

                if(filterCtr == 0){
                    cout << "The data did not matched any student information.\n";
                }

                filterCtr = 0;
                clean();
                goto top;
                break;

            case 0:
                break;

            default:
                cout << "Invalid input.\n";
                system("PAUSE");
                goto top;
        }
    }
    else{
        cout << "There are no enrolled student\n";
    }
}

void adminUnenroll(){
    char unenroll;
    string search, convertOutput;
    stringstream convert; // String object.

    if(studEnroll != 0){
        top:
        cout << "Enter a student information(Ex: Student No./Firstname/Lastname) to search for student to unenroll: ";
        cin >> search;
        cout << endl;

        // Loop for finding the matched information in the enrolled students.
        for(i = 0; i < studEnroll; i++){
            convert<<students[i].studentNo; // Insert the value of student number in struct into the steam.
            convert>>convertOutput; // Extract the converted data out of the stream and store it in a string variable.

            if(search == convertOutput ||
            search == students[i].firstname ||
            search == students[i].middlename ||
            search == students[i].lastname)
            {
                displayInfo();
                editNo = i;
                foundStudent++; // Increments when the information matches from the enrolled students.\n;
                break;
            }
        }

        cout << "Are you sure you want to unenroll, [Y] or [N]? ";
        cin >> unenroll;

        if(unenroll == 'Y' || unenroll == 'y'){
            // Loop for deleting the student information and shifting of elements.
            for(i = editNo; i < (studEnroll - 1); i++){
                students[i] = students[i + 1];
            }

            studEnroll--; // Decrementing the size of the array.
            editNo = -1;
            cout << "Unenrollment Succesful\n";
        }
        else if(unenroll == 'N' || unenroll == 'n'){
            // Back.
        }
        else{
            cout << "Invalid input.\n";
            goto top;
        }

        if(foundStudent == 0){
            cout << "Information doesn't match with the enrolled students.\n";
        }

        foundStudent = 0;
    }
    else{
        cout << "There are no enrolled student\n";
    }
}

void enrollmentPeriod(){
    if(enrollment == true){
        enrollment = false;
        cout << "Enrollment period is now close.\n";
    }
    else{
        enrollment = true;
        cout << "Enrollment period is now open.\n";
    }
}

void displayInfo(){
    cout << "----- Student Information -----\n\n";
    cout << "Student No: " << students[i].studentNo << endl;
    cout << "Firstname: " << students[i].firstname << endl;
    cout << "Middlename: " << students[i].middlename << endl;
    cout << "Lastname: " << students[i].lastname << endl;
    cout << "Name Ext: " << students[i].nameExtension << endl;
    cout << "Gender: " << students[i].gender << endl;
    cout << "Age: " << students[i].age << endl;
    cout << "Birthdate: " << students[i].birthdate << endl;
    cout << "Address: " << students[i].address << endl;
    cout << "Course: " << students[i].course << endl;
    cout << "Year Level: " << students[i].yearLevel << endl;
    cout << "Semester: " << students[i].semester << endl;
    cout << "Username: " << students[i].username << endl;
    cout << "Password: " << students[i].password << endl;
    cout << endl;
}

void firstname(){
    cout << "Enter firstname: ";
    cin.ignore();
    cin.getline(students[studEnroll].firstname, 100);
}

void middlename(){
    cout << "Enter middlename: ";
    cin >> students[studEnroll].middlename;
}

void lastname(){
    cout << "Enter lastname: ";
    cin >> students[studEnroll].lastname;
}

void nameExtension(){
    cout << "Enter name extension(Sr, Jr, II): ";
    cin >> students[studEnroll].nameExtension;
}

void age(){
    cout << "Enter age: ";
    cin >> students[studEnroll].age;
}

void birthdate(){
    cout << "Enter birthdate: ";
    cin.ignore();
    cin.getline(students[studEnroll].birthdate, 100);
}

void address(){
    cout << "Enter Address: ";
    cin.ignore();
    cin.getline(students[studEnroll].address, 50);
}

void selectGender(){
    char gender;

    invalid:
    selectGenderMenu();

    cout << "Enter your gender: ";
    cin >> gender;

    if(gender == 'M' || gender == 'm'){
        students[studEnroll].gender = "Male";
    }
    else if(gender == 'F' || gender == 'f'){
        students[studEnroll].gender = "Female";
    }
    else{
        cout << "Invalid Input.\n";
        system("PAUSE");
        goto invalid;
    }
}

void selectCourse(){
    int course;

    invalid:
    selectCourseMenu();

    cout << "Enter your course to enroll: ";
    cin >> course;

    if(course == 1){
        students[studEnroll].course = "Bs Computer Engineering";
    }
    else if(course == 2){
        students[studEnroll].course = "Bs Mechanical Engineering";
    }
    else if(course == 3){
        students[studEnroll].course = "Bs Chemical Engineering";
    }
    else if(course == 4){
        students[studEnroll].course = "Bs Electrical Engineering";
    }
    else if(course == 5){
        students[studEnroll].course = "Bs Electronic Engineering";
    }
    else if(course == 6){
        students[studEnroll].course = "Bs Software Engineering";
    }
    else{
        cout << "Invalid Input.\n";
        system("PAUSE");
        goto invalid;
    }
}

void selectYearLevel(){
    int yearLevel;

    invalid:
    selectYearLevelMenu();

    cout << "Enter year level: ";
    cin >> yearLevel;

    if(yearLevel == 1){
        students[studEnroll].yearLevel = "1st year";
    }
    else if(yearLevel == 2){
        students[studEnroll].yearLevel = "2nd year";
    }
    else if(yearLevel == 3){
        students[studEnroll].yearLevel = "3rd year";
    }
    else if(yearLevel == 4){
        students[studEnroll].yearLevel = "4th year";
    }
    else{
        cout << "Invalid Input.\n";
        system("PAUSE");
        goto invalid;
    }
}

void selectSemester(){
    int sem;

    invalid:
    selectSemesterMenu();

    cout << "Enter the semester to enroll: ";
    cin >> sem;

    if(sem == 1){
        students[studEnroll].semester = "1st Semester";
    }
    else if(sem == 2){
        students[studEnroll].semester = "2nd Semester";
    }
    else if(sem == 3){
        students[studEnroll].semester = "Summer";
    }
    else{
        cout << "Invalid Input.\n";
        system("PAUSE");
        goto invalid;
    }
}

void selectGenderMenu(){
    cout << endl;
    cout << "================\n";
    cout << "[M / m] - Male\n";
    cout << "[F / f] - Female\n";
    cout << "================\n\n";
}

void selectCourseMenu(){
    cout << endl;
    cout << "===============================\n";
    cout << "[1] - Bs Computer Engineering\n";
    cout << "[2] - Bs Mechanical Engineering\n";
    cout << "[3] - Bs Chemical Engineering\n";
    cout << "[4] - Bs Electrical Engineering\n";
    cout << "[5] - Bs Electronic Engineering\n";
    cout << "[6] - Bs Software Engineering\n";
    cout << "===============================\n\n";
}

void selectYearLevelMenu(){
    cout << endl;
    cout << "==============\n";
    cout << "[1] - 1st year\n";
    cout << "[2] - 2nd year\n";
    cout << "[3] - 3rd year\n";
    cout << "[4] - 4th year\n";
    cout << "==============\n\n";
}

void selectSemesterMenu(){
    cout << endl;
    cout << "==================\n";
    cout << "[1] - 1st Semester\n";
    cout << "[2] - 2nd Semester\n";
    cout << "[3] - Summer\n";
    cout << "==================\n\n";
}

void username(){
    cout << "Enter your username: ";
    cin >> students[studEnroll].username;
}

void password(){
    cout << "Enter your password: ";
    cin >> students[studEnroll].password;
}

void editConfirmMsg(){
    cout << "The information has benn edited\n";
    Sleep(1000);
    cout << "Saving information.....\n";
    Sleep(1000);
    cout << "The information has been successfully saved.\n\n";
}

void enrollLoading(){
    system("CLS");
    cout << "Saving information\n";
    cout << "[#...............................................................]\n";
    Sleep(1000);
    system("CLS");
    cout << "Saving information\n";
    cout << "[########........................................................]\n";
    Sleep(1000);
    system("CLS");
    cout << "Saving information\n";
    cout << "[#########.......................................................]\n";
    Sleep(1000);
    system("CLS");
    cout << "Saving information\n";
    cout << "[##################..............................................]\n";
    Sleep(1000);
    system("CLS");
    cout << "Saving information\n";
    cout << "[######################..........................................]\n";
    Sleep(1000);
    system("CLS");
    cout << "Saving information\n";
    cout << "[##############################..................................]\n";
    Sleep(1000);
    system("CLS");
    cout << "Saving information\n";
    cout << "[###################################.............................]\n";
    Sleep(1000);
    system("CLS");
    cout << "Enrolling\n";
    cout << "[####################################################............]\n";
    Sleep(1000);
    system("CLS");
    cout << "Enrolling\n";
    cout << "[###########################################################.....]\n";
    Sleep(1000);
    system("CLS");
    cout << "Enrolling\n";
    cout << "[################################################################]\n";
    Sleep(1000);
    system("CLS");
}

void loggingInLoading(){
    system("CLS");
    for(int ctr = 0; ctr < 2; ctr++){
        cout << "Logging in\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "lOgging in\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "loGging in\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "logGing in\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "loggIng in\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "loggiNg in\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "logginG in\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "logging In\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "logging iN\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "logging in.\b\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "logging in..\b\b\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
        cout << "logging in...\b\b\b\b\b\b\b\b\b\b\b\b\b";
        Sleep(500);
        system("CLS");
    }
}

void clean(){
    system("PAUSE");
    system("CLS");
}
