#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <mysql.h>

#define MAX_USERS 100
#define MAX_ATTEMPTS 3
#define _CRT_SECURE_NO_WARNINGS

int count_attempt = 0;
int curr_user = 0;
char loggedin_user[100] = "";

void showtime()
{
    time_t now = time(0);
    char dt[26];
    ctime_s(dt, sizeof(dt), &now);
    printf("\t\t\t\t\t\t @copyassignment %s\n\n", dt);
}

void showDoctorsDetails()
{
    system("cls");
    showtime();
    printf("<==========================================================>\n");
    printf("                     Dr. Waqar                              \n");
    printf("           -----------Timing-----------                     \n");
    printf("           Monday To Friday        9AM - 5PM                \n");
    printf("           Saturday                10AM - 1PM               \n");
    printf("           Sunday                  OFF                      \n");
    printf("<==========================================================>\n");
}

struct User
{
    char username[100];
    char password[100];
};

struct User users[MAX_USERS];

void login()
{
    if (curr_user == 1)
    {
        printf("\t\t\t\t\t\t Already logged in\n");
        return;
    }
    if (count_attempt == MAX_ATTEMPTS)
    {
        printf("\n\n\t\t\t\t\t\t No more attempts\n");
        exit(0);
    }

    printf("Enter Username and Password to Login\n");
    char user_name[100];
    char pass_word[100];

    printf("Username: ");
    scanf_s("%s", user_name, (unsigned)_countof(user_name));
    printf("Password: ");
    scanf_s("%s", pass_word, (unsigned)_countof(pass_word));
    fflush(stdin);
    system("cls");

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "Mission@2025", "hospitalmanagement", 0, NULL, 0);

    if (conn)
    {
        int qstate = mysql_query(conn, "SELECT username, password FROM users");
        int flag = 0;

        if (!qstate)
        {
            res = mysql_store_result(conn);

            while (row = mysql_fetch_row(res))
            {
                if (strcmp(row[0], user_name) == 0 && strcmp(row[1], pass_word) == 0)
                {
                    strcpy_s(loggedin_user, sizeof(loggedin_user), row[0]);
                    showtime();
                    printf("\t\t\t\t\t\t\t Login Successful\n\n");
                    printf("\t\t\t===============================================================\n");
                    printf("\t\t\t                         Welcome Admin                         \n");
                    printf("\t\t\t===============================================================\n");
                    curr_user = 1;
                    flag = 1;
                    break;
                }
            }

            if (!flag)
            {
                printf("\t\t\t\t\t\t Incorrect Username or Password\n");
                printf("\t\t\t\t\t\t Press Enter and Try again\n");
                getchar();
                system("cls");
                count_attempt++;
                login();
            }
        }
        else
        {
            printf("\t\t\t\t\t\t No Accounts Registered\n");
        }
    }
}

void logout()
{
    printf("Logout Successful\n");
    curr_user = 0;
}

struct Appointment
{
    char doctor[100];
    char patientname[100];
    char time[100];
    long long int age;
    long long int contactno;
    char symptoms[100];
};

void allAppointment()
{
    if (strcmp(loggedin_user, "") == 0)
    {
        printf("\t\t\t\t\t\t Please Login\n");
        return;
    }

    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, "localhost", "root", "Mission@2025", "hospitalmanagement", 0, NULL, 0);

    if (conn)
    {
        int qstate = mysql_query(conn, "SELECT doctor, patientname, time, age, contactno, symptoms FROM appointment");

        if (!qstate)
        {
            res = mysql_store_result(conn);
            system("cls");
            showtime();
            printf("Appointments for today are:\n\n");

            while (row = mysql_fetch_row(res))
            {
                printf("Doctor: %s\n", row[0]);
                printf("Patient Name: %s\n", row[1]);
                printf("Appointment Time: %s\n", row[2]);
                printf("Age: %s\n", row[3]);
                printf("Contact No: %s\n", row[4]);
                printf("Symptoms: %s\n", row[5]);
                printf("\n");
            }
        }
    }
    else
    {
        printf("Failed\n");
    }
}

void addappointment()
{
    char doc[100], name[100], time[100], symptoms[100];
    int age;
    long long int contactno;

    if (loggedin_user[0] == '\0')
    {
        printf(" \t \t \t \t \t Please Login\n");
        return;
    }

    printf("Choose Doctor from the list of available doctors:\n");
    printf("1. Dr. Waqar\n");
    printf("2. Dr. Shankar\n");
    printf("3. Dr. Krishna\n");
    printf("4. Dr. Roy\n");
    printf("Enter Doctor Name:\n");
    getchar();
    fgets(doc, sizeof(doc), stdin);
    doc[strcspn(doc, "\n")] = '\0';

    printf("Enter Patient Name:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter Appointment Time:\n");
    getchar();
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\n")] = '\0';

    printf("Enter Patient Age:\n");
    scanf_s("%d", &age);

    printf("Enter Patient Contact no:\n");
    scanf_s("%lld", &contactno);

    printf("Enter Patient Symptoms:\n");
    getchar();
    fgets(symptoms, sizeof(symptoms), stdin);
    symptoms[strcspn(symptoms, "\n")] = '\0';

    MYSQL* conn;
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, "localhost", "root", "Mission@2025", "hospitalmanagement", 0, NULL, 0);
    char query[500];
    snprintf(query, sizeof(query), "INSERT INTO appointment(doctor, patientname, time, age, contactno, symptoms) "
        "VALUES('%s', '%s', '%s', %d, %lld, '%s')",
        doc, name, time, age, contactno, symptoms);
    int qstate = 0;
    if (mysql_query(conn, query) == 0)
    {
        printf(" \t \t \t \t \t Appointment added Successfully!\n");
    }
    else
    {
        printf(" \t \t \t \t \t Failed\n");
    }
    mysql_close(conn);
}
void addstaff()
{
    char name[100], position[100];
    long long int age, contactno, salary;

    if (loggedin_user[0] == '\0')
    {
        printf(" \t \t \t \t \t Please Login\n");
        return;
    }

    printf("Enter Staff Name:\n");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter Staff Age:\n");
    scanf_s("%lld", &age);

    printf("Enter Staff Salary:\n");
    scanf_s("%lld", &salary);

    printf("Enter Staff Contact No:\n");
    scanf_s("%lld", &contactno);

    printf("Enter Staff Position:\n");
    getchar();
    fgets(position, sizeof(position), stdin);
    position[strcspn(position, "\n")] = '\0';

    MYSQL* conn;
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, "localhost", "root", "Mission@2025", "hospitalmanagement", 0, NULL, 0);
    char query[500];
    snprintf(query, sizeof(query), "INSERT INTO staff(name, age, salary, contactno, position) "
        "VALUES('%s', %lld, %lld, %lld, '%s')",
        name, age, salary, contactno, position);
    int qstate = 0;
    if (mysql_query(conn, query) == 0)
    {
        printf(" \t \t \t \t \t Staff Information added Successfully!\n");
    }
    else
    {
        printf(" \t \t \t \t \t Failed\n");
    }
    mysql_close(conn);
}

void allstaff()
{
    if (loggedin_user[0] == '\0')
    {
        printf(" \t \t \t \t \t Please Login\n");
        return;
    }
    showtime();

    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, "localhost", "root", "Mission@2025", "hospitalmanagement", 0, NULL, 0);
    if (conn)
    {
        char query[200];
        snprintf(query, sizeof(query), "SELECT name, age, salary, contactno, position FROM staff");
        if (mysql_query(conn, query) == 0)
        {
            res = mysql_store_result(conn);
            system("cls");
            printf("--------------All Staffs Details------------\n");
            printf("\n");
            while ((row = mysql_fetch_row(res)))
            {
                printf("Name: %s\n", row[0]);
                printf("Age: %s\n", row[1]);
                printf("Salary: %s\n", row[2]);
                printf("Contact No: %s\n", row[3]);
                printf("Position: %s\n\n", row[4]);
            }
        }
        else
        {
            printf("Failed\n");
        }
    }
    else
    {
        fprintf(stderr, "mysql_real_connect() failed\n");
    }
    mysql_close(conn);
}

void checkBeds()
{
    if (loggedin_user[0] == '\0')
    {
        printf(" \t \t \t \t \t Please Login\n");
        return;
    }

    system("cls");
    showtime();
    printf("\n");

    int random_no_of_beds = 0;
    int N = 200;

    srand((unsigned int)time(NULL));

    random_no_of_beds = rand() % N;

    printf("Number of beds available today are: %d\n", random_no_of_beds);
}

int main()
{

    system("Color DE");
    showtime();
    printf("\t\t\t==============================================================================\n");
    printf("\t\t\t                          Hospital Management System                            \n");
    printf("\t\t\t==============================================================================\n");

    int x;
    int choice = 0;
    do
    {
        printf("\n");
        printf("\t----------choose from below----------\n");
        printf("\t1. Login\n");
        printf("\t2. Available Doctors\n");
        printf("\t3. Check All Appointments\n");
        printf("\t4. Add new Doctor Appointment\n");
        printf("\t5. Check no of beds available\n");
        printf("\t6. Store new Staff Information\n");
        printf("\t7. Check all Staff Information\n");
        printf("\t8. Logout\n");
        printf("\t0 to exit\n");
        printf("\t-------------------------------------\n");
        scanf_s("%d", &x);

        switch (x)
        {
        case 1:
            login();
            break;
        case 2:
            showDoctorsDetails();
            break;
        case 3:
            allAppointment();
            break;
        case 4:
            addappointment();
            break;
        case 5:
            checkBeds();
            break;
        case 6:
            addstaff();
            break;
        case 7:
            allstaff();
            break;
        case 8:
            logout();
            break;
        case 0:
            choice = 1;
        }
    } while (choice == 0);

    return 0;
}
