#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdint.h>
#include<stdbool.h>

#define MAX_CREDIT_HOUR 48


//Struct for courses.
typedef struct{
    char name[50];
    int sub_atten;
    int sub_ses;
    int sub_final;
    int sub_tot_marks;
    float GPA;
}courses;


//Struct for students.
typedef struct{
    char roll[8];
    char name[50];
    courses subject[5];
    int tot_atten;
    float CGPA;
    char backlogs[5][50];
}student;


//Function prototypes.
void menu();
void update_menu();
void adding_student();
void retrieve_student();
void update_student_marks();
void update_student_attendence();
void remove_student();
void printer(student ss);
void print_all_students();
void sort_students();


//Main Function.
int main(){
    int choice, choice2;
    do{
        menu();
        printf("Enter choice: ");
        scanf("%i",&choice);
        printf("\n");
        switch(choice){
            case(1):{
                adding_student();
                break;
            }
            case(2):{
                retrieve_student();
                break;
            }
            case(3):{
                do{
                    update_menu();
                    printf("Enter choice: ");
                    scanf("%i",&choice2);
                    switch(choice2){
                        case(1):{
                            update_student_attendence();
                            break;
                        }
                        case(2):{
                            update_student_marks();
                            break;
                        }
                        case(3):{
                            remove_student();
                            break;
                        }
                    }
                }while(choice2!=4);
                break;
            }
            case(4):{
                print_all_students();
                break;
            }
            case(5):{
                sort_students();
                break;
            }
            case(6):{
                exit(1);
            }
        }
    }while(1);
}


//Function to print main menu.
void menu(){
    printf("+--------------------------------------+\n");
    printf("|          STUDENT's DATABASE          |\n");
    printf("|--------------------------------------|\n");
    printf("| %-5s  | %-28s|\n", "S#.", "Options");
    printf("|--------+-----------------------------|\n");
    printf("| %-5s  | %-28s|\n", "1.", "Enter a new student.");
    printf("| %-5s  | %-28s|\n", "2.", "Retrieve Student's Data.");
    printf("| %-5s  | %-28s|\n", "3.", "Update Student's Data.");
    printf("| %-5s  | %-28s|\n", "4.", "Print All Students' Data.");
    printf("| %-5s  | %-28s|\n", "5.", "Sort Data by Roll No.");
    printf("| %-5s  | %-28s|\n", "6.", "Exit.");
    printf("+--------------------------------------+\n");
}

//function to print update menu.
void update_menu(){
    printf("+----------------------------+\n");
    printf("| %-5s | %-18s|\n", "Option", "Update");
    printf("|--------+-------------------|\n");
    printf("| %-5s  | %-18s|\n", "1.", "Attendance");
    printf("| %-5s  | %-18s|\n", "2.", "Marks");
    printf("| %-5s  | %-18s|\n", "3.", "Remove Student");
    printf("| %-5s  | %-18s|\n", "4.", "Exit");
    printf("+----------------------------+\n");
}

//Function to add new students to the file.
void adding_student(){
    student s, temp;
    int sum=0;
    float sumofgpa=0;
    FILE *students;
    char file_name[30] = "students.csv";
    char input_roll[10];

    students = fopen(file_name,"ab");
    if(students == NULL){
        printf("\nCould not open file %s\n",file_name);
        exit(0);
    }

        printf("Enter Roll No: ");
    scanf(" %s", input_roll);

    students = fopen(file_name,"rb");
    if(students == NULL){
        printf("\nCould not open file %s\n",file_name);
        exit(0);
    }

    while (fread(&temp, sizeof(student), 1, students) == 1) {
        if (strcmp(temp.roll, input_roll) == 0) {
            printf("\nThis roll number is already present.\n\n");
            fclose(students);
            return;
        }
    }

    fclose(students);


    students = fopen(file_name,"ab");
    if(students == NULL){
        printf("\nCould not open file %s\n",file_name);
        exit(0);
    }

    strcpy(s.roll, input_roll);



    printf("\nEnter Student's Name: ");
    scanf(" %[^\n]",s.name);


    strcpy(s.subject[0].name,"Functional English");
    strcpy(s.subject[1].name,"Programming Fundamentals");
    strcpy(s.subject[2].name,"Fundamentals of IT");
    strcpy(s.subject[3].name,"Applied Physics");
    strcpy(s.subject[4].name,"Islamiyat");


    for (int i = 0; i < 5; i++) {
       
        do{
            printf("\nEnter %s Sessional Marks (out of 40): ", s.subject[i].name);
            scanf("%i", &s.subject[i].sub_ses);
            if(s.subject[i].sub_ses<0 || s.subject[i].sub_ses>40){
                printf("Enter marks out of 40.\n");
            }
        }while(s.subject[i].sub_ses<0 || s.subject[i].sub_ses>40);


        do{
            printf("\nEnter %s Finals Marks (out of 60): ", s.subject[i].name);
            scanf("%i", &s.subject[i].sub_final);
            if(s.subject[i].sub_final<0 || s.subject[i].sub_final>60){
                printf("Enter marks out of 60.\n");
            }
        }while(s.subject[i].sub_final<0 || s.subject[i].sub_final>60);


        do{
            printf("\nEnter %s Attendance (out of 48): ", s.subject[i].name);
            scanf("%i", &s.subject[i].sub_atten);
            if(s.subject[i].sub_atten<0 || s.subject[i].sub_atten>MAX_CREDIT_HOUR){
                printf("Enter Attendence out of %i.\n", MAX_CREDIT_HOUR);
            }
        }while(s.subject[i].sub_atten<0 || s.subject[i].sub_atten>MAX_CREDIT_HOUR);    


        s.subject[i].sub_tot_marks=s.subject[i].sub_ses+s.subject[i].sub_final;
    }


    for(int i=0;i<5;i++){
        if(s.subject[i].sub_tot_marks>=85){
            s.subject[i].GPA=4.0;
        }
        else if(s.subject[i].sub_tot_marks>=80 && s.subject[i].sub_tot_marks<85){
            s.subject[i].GPA=3.7;
        }
        else if(s.subject[i].sub_tot_marks>=75 && s.subject[i].sub_tot_marks<80){
            s.subject[i].GPA=3.4;
        }
        else if(s.subject[i].sub_tot_marks>=70 && s.subject[i].sub_tot_marks<75){
            s.subject[i].GPA=3.0;
        }
        else if(s.subject[i].sub_tot_marks>=67 && s.subject[i].sub_tot_marks<70){
            s.subject[i].GPA=2.7;
        }
        else if(s.subject[i].sub_tot_marks>=64 && s.subject[i].sub_tot_marks<67){
            s.subject[i].GPA=2.4;
        }
        else if(s.subject[i].sub_tot_marks>=60 && s.subject[i].sub_tot_marks<64){
            s.subject[i].GPA=2.0;
        }
        else if(s.subject[i].sub_tot_marks>=57 && s.subject[i].sub_tot_marks<60){
            s.subject[i].GPA=1.7;
        }
        else if(s.subject[i].sub_tot_marks>=54 && s.subject[i].sub_tot_marks<57){
            s.subject[i].GPA=1.4;
        }
        else if(s.subject[i].sub_tot_marks>=50 && s.subject[i].sub_tot_marks<54){
            s.subject[i].GPA=1.0;
        }
        else{
            s.subject[i].GPA=0.0;
        }
    }


    for(int k=0;k<5;k++){
        sumofgpa += (s.subject[k].GPA*MAX_CREDIT_HOUR);
    }


    s.CGPA=sumofgpa/(5*MAX_CREDIT_HOUR);


    for(int i=0;i<5;i++){
        sum+=s.subject[i].sub_atten;
    }
    s.tot_atten=round((sum/5));


    fwrite(&s, sizeof(student),1,students);
    fclose(students);
}

//Function to retrieve previous records.
void retrieve_student(){
    char req_roll[10];
    student s;
    FILE *students;
    char file_name[30]="students.csv";
    int found;
    int choice;

    students=fopen(file_name,"rb+");
    if(students==NULL){
        printf("\nCould not open file %s\n",file_name);
        exit(0);
    }

    printf("Enter Roll No: ");
    scanf(" %s", req_roll);

    printf("\n1. Retrieve all data\n2. Retrieve GPA\n3. Retrieve Attendance\n4. Retrieve Marks\n");
    printf("Enter your choice (1/2/3/4): ");
    scanf("%d", &choice);

    printf("\n");

    while(fread(&s, sizeof(student), 1, students)==1){
        if(strcmp(s.roll,req_roll)==0){
            found=1;
            switch(choice) {
                case 1:
                    printer(s);
                    break;
                case 2:
                    printf("GPA: %.2f\n", s.CGPA);
                    break;
                case 3:
                    printf("Attendance: %d\n", s.tot_atten);
                    break;
                case 4:
                    for(int i=0; i<5; i++) {
                        printf("%s - Sessional Marks: %d, Final Marks: %d\n", s.subject[i].name, s.subject[i].sub_ses, s.subject[i].sub_final);
                    }
                    break;
                default:
                    printf("Invalid choice\n");
                    break;
            }
            fseek(students, -sizeof(student), SEEK_CUR);
            fwrite(&s, sizeof(student), 1, students);
            break;
        }
    }
    if(!found){
        printf("\nRecord for Roll No: %s does not exist.\n\n",req_roll);
    }

    fclose(students);
}




//Function to update student marks.
void update_student_marks(){
     char req_roll[10], req_course[30];
    student s;
    FILE *students;
    char file_name[30]="students.csv";
    int found;
    float sumofgpa=0;


    students=fopen(file_name,"rb");
    if(students==NULL){
        printf("\nCould not open file %s\n",file_name);
        exit(0);
    }


    printf("\nEnter Roll No: ");
    scanf(" %s", req_roll);
    fflush(stdin);
    printf("\nEnter Course Name to be Updated:\n1. Functional English\n2. Programming Fundamentals\n3. Fundamentals of IT\n4. Applied Physics\n5. Islamiyat\n==> ");
    scanf(" %[^\n]",req_course);
    fflush(stdin);


    while(fread(&s, sizeof(student), 1, students)==1){


        if(strcmp(s.roll,req_roll)==0){
            for(int i=0;i<5;i++){
                if(strcmp(s.subject[i].name,req_course)==0){
                    do{
                        printf("\nEnter Updated Sessional Marks: ");
                        scanf("%i",&s.subject[i].sub_ses);
                        if(s.subject[i].sub_ses < 0 || s.subject[i].sub_ses > 40){
                            printf("Enter Marks out of 40.\n");
                        }
                    }while(s.subject[i].sub_ses < 0 || s.subject[i].sub_ses > 40);


                    do{
                        printf("\nEnter Updated Final Marks: ");
                        scanf("%i",&s.subject[i].sub_final);
                        if(s.subject[i].sub_final < 0 || s.subject[i].sub_final > 60){
                            printf("Enter marks out of 60.\n");
                        }
                    }while(s.subject[i].sub_final < 0 || s.subject[i].sub_final > 60);


                    s.subject[i].sub_tot_marks=s.subject[i].sub_ses+s.subject[i].sub_final;

                    for(int j=0;j<5;j++){
                        if(s.subject[j].sub_tot_marks>=85){
                            s.subject[j].GPA=4.0;
                        }
                        else if(s.subject[j].sub_tot_marks>=80 && s.subject[j].sub_tot_marks<85){
                            s.subject[j].GPA=3.7;
                        }
                        else if(s.subject[j].sub_tot_marks>=75 && s.subject[j].sub_tot_marks<80){
                            s.subject[j].GPA=3.4;
                        }
                        else if(s.subject[j].sub_tot_marks>=70 && s.subject[j].sub_tot_marks<75){
                            s.subject[j].GPA=3.0;
                        }
                        else if(s.subject[j].sub_tot_marks>=67 && s.subject[j].sub_tot_marks<70){
                            s.subject[j].GPA=2.7;
                        }
                        else if(s.subject[j].sub_tot_marks>=64 && s.subject[j].sub_tot_marks<67){
                            s.subject[j].GPA=2.4;
                        }
                        else if(s.subject[j].sub_tot_marks>=60 && s.subject[j].sub_tot_marks<64){
                            s.subject[j].GPA=2.0;
                        }
                        else if(s.subject[j].sub_tot_marks>=57 && s.subject[j].sub_tot_marks<60){
                            s.subject[j].GPA=1.7;
                        }
                        else if(s.subject[j].sub_tot_marks>=54 && s.subject[j].sub_tot_marks<57){
                            s.subject[j].GPA=1.4;
                        }
                        else if(s.subject[j].sub_tot_marks>=50 && s.subject[j].sub_tot_marks<54){
                            s.subject[j].GPA=1.0;
                        }
                        else{
                            s.subject[j].GPA=0.0;
                        }
                    }


                    for(int k=0;k<5;k++){
                        sumofgpa += (s.subject[k].GPA*MAX_CREDIT_HOUR);
                    }


                    s.CGPA=sumofgpa/(5*MAX_CREDIT_HOUR);

                    fseek(students, sizeof(student), SEEK_CUR);


                    fwrite(&s,sizeof(student),1,students);


                    fseek(students,0,SEEK_SET);
                    break;
                }
            }
            fclose(students);


            students = fopen(file_name,"rb+");


            fwrite(&s,sizeof(student),1,students);
            break;
        }
    }
    fclose(students);

}

//Function to update students attendence.
void update_student_attendence(){
    char req_roll[10], req_course[30];
    int sum=0;
    student s;
    FILE *students;
    char file_name[30]="students.csv";


    students=fopen(file_name,"rb");
    if(students==NULL){
        printf("\nCould not open file %s\n",file_name);
        exit(0);
    }


    printf("\nEnter Roll No: ");
    scanf(" %s", req_roll);
    fflush(stdin);
    printf("\nEnter Course Name to be Updated:\n1. Functional English\n2. Programming Fundamentals\n3. Fundamentals of IT\n4. Applied Physics\n5. Islamiyat\n==> ");
    scanf(" %[^\n]",req_course);
    fflush(stdin);


    while(fread(&s, sizeof(student), 1, students)==1){


        if(strcmp(s.roll,req_roll)==0){
            for(int i=0;i<5;i++){
                if(strcmp(s.subject[i].name,req_course)==0){
                    do{
                        printf("\nEnter Updated Attendence: ");
                        scanf("%i",&s.subject[i].sub_atten);
                        if(s.subject[i].sub_atten < 0 || s.subject[i].sub_atten > MAX_CREDIT_HOUR){
                            printf("Enter Attendence out of %i.\n",MAX_CREDIT_HOUR);
                        }
                    }while(s.subject[i].sub_atten < 0 || s.subject[i].sub_atten > MAX_CREDIT_HOUR);


                    fseek(students, sizeof(student), SEEK_CUR);


                    fwrite(&s,sizeof(student),1,students);


                    fseek(students,0,SEEK_SET);
                    break;
                }
            }


            for(int j=0;j<5;j++){
                sum+=s.subject[j].sub_atten;
            }
            s.tot_atten=round((sum/5));


            fclose(students);


            students = fopen(file_name,"rb+");
            fwrite(&s,sizeof(student),1,students);
            break;
        }
    }


    fclose(students);
}

//Function to remove students.
void remove_student() {
    char req_roll[10];
    student s;
    FILE *students, *temp;
    char file_name[30] = "students.csv";
    char temp_file_name[30] = "temp.csv";

    students = fopen(file_name, "rb");
    temp = fopen(temp_file_name, "wb");
    if (students == NULL || temp == NULL) {
        printf("\nCould not open file\n");
        exit(0);
    }

    printf("Enter Roll No: ");
    scanf(" %s", req_roll);

    while (fread(&s, sizeof(student), 1, students) == 1) {
        if (strcmp(s.roll, req_roll) != 0) {
            fwrite(&s, sizeof(student), 1, temp);
        }
    }

    fclose(students);
    fclose(temp);

    remove(file_name);
    rename(temp_file_name, file_name);

    printf("\nRecord for Roll No: %s has been deleted if it existed.\n\n", req_roll);
}

//Function to print the retrieved student's data.
void printer(student ss){
    printf("====================================================================================================================================================================\n");


    printf("\n");


    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  ROLL NO: %s  |   NAME: %-125s|\n", ss.roll, ss.name);
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|      %s      |   %s   |      %s      |      %s         |          %s           |\n", "Functional English","Programming Fundamentals","Fundamentals of IT","Applied Physics","Islamiyat");
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| Sessionals|Finals|Attendence | Sessionals|Finals|Attendence | Sessionals|Finals|Attendence | Sessionals|Finals|Attendence | Sessionals|Finals|Attendence |\n");
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|    %i     |  %i  |    %i     |    %i     |  %i  |    %i     |     %i    |  %i  |    %i     |     %i    |  %i  |    %i     |     %i    |  %i  |    %i     |\n",ss.subject[0].sub_ses,ss.subject[0].sub_final,ss.subject[0].sub_atten,ss.subject[1].sub_ses,ss.subject[1].sub_final,ss.subject[1].sub_atten,ss.subject[2].sub_ses,ss.subject[2].sub_final,ss.subject[2].sub_atten,ss.subject[3].sub_ses,ss.subject[3].sub_final,ss.subject[3].sub_atten,ss.subject[4].sub_ses,ss.subject[4].sub_final,ss.subject[4].sub_atten);
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|  GPA: %-98.2f                                                 |\n",ss.CGPA);
    printf("+----------------------------------------------------------------------------------------------------------------------------------------------------------+\n");


    printf("\n");


    printf("====================================================================================================================================================================\n\n");

}


//Function to print all student's data present in the file 
void print_all_students(){
    student s;
    FILE *students;
    char file_name[30] = "students.csv";
    char printed_roll_numbers[100][8];  
    int count = 0;

    students = fopen(file_name, "rb");
    if (students == NULL) {
        printf("\nCould not open file %s\n", file_name);
        exit(0);
    }

    while (fread(&s, sizeof(student), 1, students) == 1) {
        int already_printed = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(printed_roll_numbers[i], s.roll) == 0) {
                already_printed = 1;
                break;
            }
        }

        if (!already_printed) {
            printer(s);
            strcpy(printed_roll_numbers[count], s.roll);
            count++;
        }
    }

    fclose(students);

    
}


//Function to sort the students in the file.
void sort_students(){
    student s[100]; 
    student temp;
    int count = 0;
    FILE *students;
    char file_name[30] = "students.csv";

    students = fopen(file_name, "rb");
    if (students == NULL) {
        printf("\nCould not open file %s\n", file_name);
        exit(0);
    }

    while (fread(&s[count], sizeof(student), 1, students) == 1) {
        count++;
    }

    fclose(students);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(s[j].roll, s[j + 1].roll) > 0) {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }

    students = fopen(file_name, "wb");
    if (students == NULL) {
        printf("\nCould not open file %s\n", file_name);
        exit(0);
    }

    for (int i = 0; i < count; i++) {
        fwrite(&s[i], sizeof(student), 1, students);
    }

    fclose(students);
}