#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>
#define _CRT_SECURE_NO_WARNINGS
#define D_CRT_NONSTDC_NO_WARNINGS
#define size 50
#define MAX 100
#pragma warning(disable : 4996) 

struct student
{
    char gradebook[8];
    char name[15];
    char lastname[15];
    char f_name[20];
    char facult[5];
    char departr[MAX];
};

struct student student[MAX];

struct books
{
    unsigned long long int ISBN;
    char Author[size];
    char title[size];
    int total;
    int available;
};

struct books books[MAX];

struct user
{
    char login[20];
    char password[20];
    int student;
    int book;
};
struct user user[MAX];
//подсчет количества элементов в файлах
void open_files();
int Students = 0;//количество студентов
int Books = 0;//количество книг
int Users = 0;//количсевто юзеров
//функции книг
void b_add();
void b_del();
void b_give();
void b_take();
//функции студентов
void st_add();
void st_del();
void st_backup();
void st_restore();
void st_find();

int main()
{
    int add = 0;
    int add_menu = 0;
    open_files();

    int user_num = 0;
    char login[20];
    char password[20];
    printf("Enter login: ");
    scanf("%s", login);

    for (int st = 0; st < (Users - 1); st++)
    {
        if (strcmp(login, user[st].login) == 0)
        {
            printf("Enter password: ");
            scanf("%s", password);
            if ((password == user[st].password)) {
                user_num = st; break;
            }
        }
    }
    
    if ((user[user_num].student == 1) && (user[user_num].book == 1))
    {
        printf("<1>student menu \n");
        printf("<2>book menu \n");
        printf("\nYour choice: ");
        scanf("%d", &add_menu);
    }

    if ((add_menu == 1) || ((user[user_num].student == 1) && (user[user_num].book == 0)))
    {
        printf("\n<1>Add_student \n");
        printf("<2>Del_student \n");
        printf("<3>Backup_student \n");
        printf("<4>Restore_student \n");
        printf("<5>Find_student \n");
        printf("<6>Exit \n");
        while(TRUE)
        {
            scanf("%d", &add);
            if (add == 1)
                st_add();
            else if (add == 2)
                st_del();
            else if (add == 3)
                st_backup();
            else if (add == 4)
                st_restore();
            else if (add == 5)
                st_find();
            else if (add == 6)
                break;
            else
                printf("Smth is wrong!\n");
        }
    }
    if ((add_menu == 2) || ((user[user_num].student == 0) && (user[user_num].book == 1)))    
    {
        printf("\n<1>Add new book \n");
        printf("<2>Delete book \n");
        printf("<3>Give book \n");
        printf("<4>Take book \n");
        printf("<5>Exit \n");
        printf("Your choice: ");
        while(TRUE)
        {
            scanf("%d", &add);  
            if (add == 1)
                b_add();
            else if (add == 2)
                b_del();
            else if (add == 3)
                b_give();
            else if (add == 4)
                b_take();
            else if (add == 5)
                break;
            else {
                printf("Smth is wrong!\n");
            }
        }
    }

    return 0;
}

void open_files()
{
    FILE* file;
    int i;

    if ((file = fopen("students.csv", "r")) == 0)
    {
        printf("Can't open students.csv!");
        exit(300);
    }
    for (i = 0; !feof(file); i++)
    {
        fscanf(file, "%[^;]%*c", student[i].gradebook);
        fscanf(file, "%[^;]%*c", student[i].lastname);
        fscanf(file, "%[^;]%*c", student[i].name);
        fscanf(file, "%[^;]%*c", student[i].f_name);
        fscanf(file, "%[^;]%*c", student[i].facult);
        fscanf(file, "%[^'\n']%*c", student[i].departr);
    }
    fclose(file);
    Students = i;

    if ((file = fopen("books.csv", "r")) == 0)
    {
        printf("Can't open books.csv");
        exit(100);
    }
    for (i = 0; !feof(file); i++)
    {
        fscanf(file, "%lld", &books[i].ISBN);
        getc(file);
        fscanf(file, "%[^;]%*c", books[i].Author);
        fscanf(file, "%[^;]%*c", books[i].title);
        fscanf(file, "%d", &books[i].total);
        getc(file);
        fscanf(file, "%d", &books[i].available);
        getc(file);
    }
    fclose(file);
    Books = i;

    if ((file = fopen("users.csv", "r")) == 0)
    {
        printf("Can't open users.csv!");
        exit(1);
    }
    for (i = 0; !feof(file); i++)
    {
        fscanf(file, "%[^;]%*c", user[i].login);
        fscanf(file, "%[^;]%*c", user[i].password);
        fscanf(file, "%d", &user[i].student);
        getc(file);
        fscanf(file, "%d", &user[i].book);
        getc(file);
    }
    fclose(file);
    Users = i;
}


void b_add()
{
    open_files();

    unsigned long long int ISBN;
    char author[size];
    char booktitle[size];
    int total;
    int available;

    FILE* file;
    if ((file = fopen("books.csv", "a")) == 0)
    {
        printf("Can't open books.csv!");
        exit(1);
    }

    printf("ISBN: ");
    scanf("%lld", &ISBN);

    for (int i = 0; i < Books; i++)
    {
        if (ISBN == books[i].ISBN)
        {
            printf("This book already exists\n");
            exit(100);
        }
    }

    printf("Author: ");
    scanf("%s", author);
    printf("Title: ");

    char c = getchar();
    int n = 0;

    while ((c = getchar()) != '\n')
    {
        booktitle[n] = c;
        n++;
    }
    booktitle[n] = '\0';

    printf("Number of books: ");
    scanf("%d", &total);

    printf("Available: ");
    scanf("%d", &available);

    fprintf(file, "\n%lld;", ISBN);
    fprintf(file, "%s;", author);
    fprintf(file, "%s;", booktitle);
    fprintf(file, "%d;", total);
    fprintf(file, "%d", available);

    fclose(file);
    printf("\nAdded\n");

}

void b_del()
{
    open_files();
    unsigned long long int ISBN;

    FILE* file;
    if ((file = fopen("books.csv", "r")) == 0)
    {
        printf("Can't open books.csv");
        exit(1);
    }

    char* buf = (char*)malloc((Books + 1) * (sizeof(struct books)));

    printf("ISBN: ");
    scanf("%lld", &ISBN);

    int n = 0;
    for (int i = 0; i < Books; i++)
    {
        if (ISBN != books[i].ISBN)
        {
            buf[n] = getc(file);
            for (; (buf[n] != '\n') && (!feof(file));)
            {
                n++;
                buf[n] = getc(file);
            }
            buf[n] = '\n';
            n++;
        }
        if (ISBN == books[i].ISBN)
        {
            for (; (getc(file) != '\n') && (!feof(file));){ }
        }
    }
    buf[n - 1] = '\0';
    fclose(file);

    file = fopen("books.csv", "w");
    for (int e = 0; buf[e] != '\0'; e++)
        fprintf(file, "%c", buf[e]);
    fclose(file);
    free(buf);
    printf("Removed!\n");
}


void b_give()
{
    open_files();

    unsigned long long int ISBN;

    FILE* file;
    if ((file = fopen("books.csv", "r")) == 0)
    {
        printf("Can't open books.csv!");
        exit(103);
    }

    printf("ISBN: ");
    scanf("%lld", &ISBN);

    int fl = 0;
    int i;
    for (i = 0; i < Books; i++)
    {
        if ((ISBN == books[i].ISBN) && (books[i].available > 0))
        {
            books[i].available = books[i].available - 1;
            fl = 1;
        }
    }
    fclose(file);

    if (fl == 1)
    {
        file = fopen("books.csv", "w");
        for (int c = 0; c < Books; c++)
        {
            fprintf(file, "%lld;", books[c].ISBN);
            fprintf(file, "%s;", books[c].Author);
            fprintf(file, "%s;", books[c].title);
            fprintf(file, "%d;", books[c].total);
            if (c == (Books - 1))
                fprintf(file, "%d", books[c].available);
            else
                fprintf(file, "%d\n", books[c].available);
        }
        printf("OK\n");
        fclose(file);
    }
    else printf("Smth is wrong!\n");
}

void b_take()
{
    open_files();

    unsigned long long int ISBN;

    FILE* file;
    if ((file = fopen("books.csv", "r")) == 0)
    {
        printf("Can't open books.csv!");
        exit(104);
    }

    printf("ISBN: ");
    scanf("%lld", &ISBN);

    int t = 0;
    int i = 0;
    for (i; i < Books; i++)
    {
        if ((ISBN == books[i].ISBN) && (books[i].available < books[i].total))
        {
            books[i].available = books[i].available + 1;
            t = 1;
        }
    }
    fclose(file);

    if (t == 1)
    {
        file = fopen("books.csv", "w");
        for (int c = 0; c < Books; c++)
        {
            fprintf(file, "%lld;", books[c].ISBN);
            fprintf(file, "%s;", books[c].Author);
            fprintf(file, "%s;", books[c].title);
            fprintf(file, "%d;", books[c].total);
            if (c == (Books - 1))
                fprintf(file, "%d", books[c].available);
            else
                fprintf(file, "%d\n", books[c].available);
        }
        printf("OK\n");
        fclose(file);
    }
    else printf("Smth is wrong!");
}

void st_add()
{
    open_files();

    char zachet_book[8];
    char name[15];
    char lastname[15];
    char f_name[20];
    char faculty[5];
    char prof[size];

    FILE* file;
    if ((file = fopen("students.csv", "a")) == 0)
    {
        printf("Can't open students.csv!");
        exit(301);
    }
    printf("Number of gradebook: ");
    scanf("%s", zachet_book);

    for (int n = 0; n <= Students; n++)
    {
        if (strcmp(zachet_book, student[n].gradebook) == 0)
        {
            printf("You can't add this student!");
            exit(400);
        }
    }

    printf("Lastname: ");
    scanf("%s", lastname);

    printf("Name: ");
    scanf("%s", name);

    printf("Fathername: ");
    scanf("%s", f_name);

    printf("Faculty: ");
    scanf("%s", faculty);

    printf("Department: ");
    int n = 0;
    char c = getchar();
    while ((c = getchar()) != '\n')
    {
        prof[n] = c; n++;
    }
    prof[n] = '\0';

    fprintf(file, "\n%s;", zachet_book);
    fprintf(file, "%s;", lastname);
    fprintf(file, "%s;", name);
    fprintf(file, "%s;", f_name);
    fprintf(file, "%s;", faculty);
    fprintf(file, "%s", prof);

    fclose(file);

    printf("OK\n");
}



void st_del()
{
    open_files();

    char gradebook[8];

    FILE* file;
    if ((file = fopen("students.csv", "r")) == 0)
    {
        printf("Can't open students.csv");
        exit(302);
    }
    printf("Number of greatbook: ");

    scanf("%s", gradebook);

    char* buf = (char*)malloc((Students + 1) * (sizeof(struct student)));
    int n = 0;

    for (int i = 0; i < Students; i++)
    {
        if (strcmp(gradebook, student[i].gradebook) != 0)
        {
            buf[n] = getc(file);
            while ((buf[n] != '\n') && (!feof(file)))
            {
                n++;
                buf[n] = getc(file);
            }
            buf[n] = '\n';
            n++;
        }
        if (strcmp(gradebook, student[i].gradebook) == 0)
        {
            while ((getc(file) != '\n') && (!feof(file))){}
        }
    }
    buf[n - 1] = '\0';
    fclose(file);

    file = fopen("students.csv", "w");

    for (int e = 0; buf[e] != '\0'; e++)
        fprintf(file, "%c", buf[e]);

    fclose(file);
    free(buf);

    printf("OK!\n");
}

void st_backup()
{
    open_files();

    int n;
    FILE* file;
    if ((file = fopen("students.csv", "r")) == 0)
    {
        printf("Can't open students.csv!");
        exit(303);
    }
    char* buf = (char*)malloc((Students + 1) * (sizeof(struct student)));

    for (n = 0; !feof(file); n++)
    {
        buf[n] = getc(file);
    }
    buf[n - 1] = '\0';

    fclose(file);

    struct tm* u;
    const time_t timer = time(NULL);
    u = localtime(&timer);

    char array[50];

    for (int i = 0; i < 50; i++)
        array[i] = 0;

    int len = strftime(array, 50, "%d.%m.%Y %H-%M", u);

    char f_title[32] = "students";
    int r = 8;
    int i = 0;
    for (r; array[i] != '\0'; i++, r++)
    {
        f_title[r] = array[i];
    }
    f_title[r] = '.';
    f_title[r + 1] = 'c';
    f_title[r + 2] = 's';
    f_title[r + 3] = 'v';
    f_title[r + 4] = '\0';

    file = fopen(f_title, "w");

    for (int e = 0; (buf[e] != '\0'); e++)
        fprintf(file, "%c", buf[e]);

    fclose(file);
    free(buf);

    printf("Bacup %s created.\n", f_title);
}

void st_restore()
{

    char backup_name[100];
    int bu = 0;

    printf("\nName of backup(studentsXX.XX.XXXX TT-TT.csv): ");

    char c = getchar();
    c = getchar();
    while (c != '\n')
    {
        backup_name[bu] = c;
        bu++;
        c = getchar();
    }
    backup_name[bu] = '\0';

    FILE* file;
    if ((file = fopen(backup_name, "r")) == 0)
    {
        printf("Can't open students.csv!");
        exit(304);
    }

    char* buf = (char*)malloc((Students + 1) * (sizeof(struct student)));
    int n = 0;

    for (n; !feof(file); n++)
    {
        buf[n] = getc(file);
    }
    buf[n - 1] = '\0';

    fclose(file);

    file = fopen("students.csv", "w");
    for (int e = 0; (buf[e] != '\0'); e++)
        fprintf(file, "%c", buf[e]);

    fclose(file);
    free(buf);

    printf("File students.csv restored!\n");
}

void st_find()
{
    open_files();

    char lastname[15];

    printf("Lastname: ");
    scanf("%s", lastname);
    int t = 0;

    for (int i = 0; i < Students; i++)
    {
        if (strcmp(lastname, student[i].lastname) == 0)
        {
            t = 1;
            printf("Greatbook: %s \t ", student[i].gradebook);
            printf("Lastname: %s \t", student[i].lastname);
            printf("Name: %s \t", student[i].name);
            printf("Fathername: %s \t", student[i].f_name);
            printf("Faculty: %s\t", student[i].facult);
            printf("Department: %s\n", student[i].departr);
        }
    }
    if (t == 0)
        printf("There is no this student!\n");
}
