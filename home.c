#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <ctime>
typedef struct books book1;
struct books {
    char num[20];
    char ath[60];
    char name[60];
    int q;
    int qs;
};
book1 books[1000];
typedef struct students students1;
struct students {
    char booknum[20];
    char surname[30];
    char name[30];
    char patr[40];
    char fac[5];
    char depart[40];
};
students1 students[1000];
struct stbooks {
    char time[20];
};
stbooks stdbooks[100];
void bookf(FILE* book);
int readb(const char* file);
int readb1(const char* file);
int similar(char num[20]);
void delbook(const char* file);
int similar1(char num[20]);
int similar2(char booknum[15]);
void delstudents(const char* file);
void studentsf(FILE* stdents);
int similarst(char surname[40])
{
    int i;
    int temp = -1;
    for (i = 0; i < readb1("students.csv"); i++)
        if (strcmp(surname, students[i].surname) == 0)
            temp = i;
    return temp;
}
void searchst(const char* filename) {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    FILE* stdents;
    char surname[40];
    char file[5000];
    printf("Enter students surname:");
    scanf("%s", surname);
    stdents = fopen(filename, "r+");
    rewind(stdents);
    int getfile = similarst(surname);
    if (getfile == 0)
    {
    printf("%s;%s;%s;%s;%s;%s\n", students[getfile].booknum, students[getfile].surname, students[getfile].name, students[getfile].patr, students[getfile].fac, students[getfile].depart);
    fclose(stdents);
    }
    else
    {
    printf("There is no this student!");
    fclose(stdents);
    }
}
void back(FILE* backup) {
    char file[5000];
    time_t time;
    struct tm* time_t;
    //strftime(file, 5000, );
}
char state;
char status;
char c[2];
int m;
int count = 0;
int Mainstudents();
int Mainbook();
char* writestr(char str[]);
char* writestr(char str[]) {
    int c, i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        str[i++] = c;
    }str[i] = '\0';
    return str;
}

int Mainbook() {
    printf("Books menu:\n");
    printf("(1) Add new book\n");
    printf("(2) Remove book\n");
    printf("(3) Change books information\n");
    printf("(4) Information about student by ISBN\n");
    printf("(5) Issue/pass books\n");
    printf("(0) Exit\n");
    FILE* book;
    book = fopen("books.csv", "r");
    bookf(book);
    fclose(book);
    return 1;
}

int Mainstudents() {
    printf("\nStudents menu:\n");
    printf("(1) Add new student\n");
    printf("(2) Remove student\n");
    printf("(3) Change students information\n");
    printf("(4) Serach student\n");
    printf("(5) Выдача книг/сдача\n");
    printf("(0) Exit\n");
    FILE* stdents;
    stdents = fopen("students.csv", "r");
    studentsf(stdents);
    fclose(stdents);
    return 2;

}
int readb(const char* file) {
    FILE* book = fopen(file, "r+");
    if (!book)
        return -1;
    rewind(book);
    char str[1000];
    int i = 0;
    while (fgets(str, 1000, book))
    {
        fscanf(book, "%[^;];%[^;];%[^;];%d;%d", books[i].num, books[i].ath, books[i].name, &books[i].q, &books[i].qs);
        i++;
    }
    return i;
}
int readb1(const char* file) {
    FILE* stdents = fopen(file, "r+");
    if (!stdents)
        return -1;
    rewind(stdents);
    char str[1000];
    int i = 0;
    while (fgets(str, 1000, stdents)) {
        fscanf(stdents, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;]", students[i].booknum, students[i].surname, students[i].name, students[i].patr, students[i].fac, students[i].depart);
        i++;
    }
    return i;
}
int similar(char num[20])
{
    int i;
    int temp = -1;
    for (i = 0; i < readb("books.csv"); i++)
        if (strcmp(num, books[i].num) == 0)
            temp = i;
    return temp;
}
int similar2(char booknum[15])
{
    int i;
    int temp = -1;
    for (i = 0; i < readb1("students.csv"); i++)
        if (strcmp(booknum, students[i].booknum) == 0)
            temp = i;
    return temp;
}
void bookf(FILE* book) {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);

    SetConsoleOutputCP(1251);
    FILE* studbooks;
    struct books elem;
    book = fopen("books.csv", "r");
    char file[5000];
    while (fgets(file, 5000, book) != NULL) {
        printf("%s", file);
    }
    fclose(book);
    int add;
    printf("You choosed:");
    scanf("%d", &add);
    if (add == 1) {
        book = fopen("books.csv", "a+");
        printf("Enter ISBN:");
        fflush(stdin);
        scanf("%s", elem.num);
        if (similar(elem.num) != -1)
        {
            printf("This ISBN already exists!\n");
            fclose(book);
        }
        else {
            printf("Enter author:");
            scanf("%s", elem.ath);
            printf("Enter title:");
            scanf("%s", elem.name);
            printf("Enter number:");
            scanf("%d", &elem.q);
            printf("Enter the number of available books:");
            scanf("%d", &elem.qs);
            book = fopen("books.csv", "a+");
            studbooks = fopen("student_books.csv", "a+");
            if (elem.qs != elem.q) {
                fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs);
                fprintf(studbooks, "%s\n", elem.num);
            }
            else fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs);
            fclose(book);
            fclose(studbooks);
        }
    }
    if (add == 2) {
        FILE* stubooks;
        stubooks = fopen("student_books.csv", "r");
        char str[5000];
        while (fgets(str, 5000, stubooks) != NULL)
            printf("%s", str);
        printf("Enter ISBN:");
        scanf("%s", elem.num);
        int l = similar1(elem.num);
        if (l != 1) {
            printf("It can't be removed!\n");
        }
        else
            printf("ISBN is correct!");
            delbook("books.csv");
    }
    if (add == 3) {
        printf("\nEnter ISBN:");
        scanf("%s", elem.num);
        book = fopen("books.csv", "r");
        rewind(book);
        int getfile = similar(elem.num);
        int getfile1 = readb("books.csv");
        fclose(book);
        if (getfile != -1)
        {
            printf("Enter author:");
            scanf("%s", elem.ath);
            printf("Enter title:");
            scanf("%s", elem.name);
            printf("Number:");
            scanf("%d", &elem.q);
            printf("Number of available books:");
            scanf("%d", &elem.qs);
            book = fopen("books.csv", "w");
            int i;
            for (i = 0; i < getfile1; i++)
            {
                if (i != getfile)
                    fprintf(book, "%s;%s;%s;%d;%d\n", books[i].num, books[i].ath, books[i].name, books[i].q, books[i].qs);
                fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs);
            }
            fclose(book);
        }
        else
            printf("\nThere is no this ISBN!\n ");
    }
    if (add == 4) {

    }
    if (add == 5) {
        struct students elem1;
        struct stbooks elem2;
        FILE* book, * studbook, * stdents;
        printf("\nEnter ISBN:");
        scanf("%s", elem.num);
        printf("Enter number of greatbook:");
        scanf("%s", elem1.booknum);
        book = fopen("books.csv", "r");
        stdents = fopen("students.csv", "r");
        rewind(book);
        rewind(stdents);
        int getfile = similar(elem.num);
        int getfile2 = similar2(elem1.booknum);
        int getfile1 = readb("books.csv");
        int getfile12 = readb1("students.csv");
        fclose(book);
        fclose(stdents);
        if (getfile != 1 && getfile2 != 1)
        {
            printf("Enter author:");
            scanf("%s", elem.ath);
            printf("Enter title:");
            scanf("%s", elem.name);
            printf("Number:");
            scanf("%d", &elem.q);
            printf("Number of available books:");
            scanf("%d", &elem.qs);
            printf("Enter date of pass:");
            scanf("%s", elem2.time);
            book = fopen("books.csv", "w");
            stdents = fopen("students.csv", "r");
            studbook = fopen("student_books.csv", "a+");
            int i, j;
            for (i = 0; i < getfile1; i++)
            {
                for (j = 0; j < getfile12; j++)
                    if (i != getfile && j != getfile2)
                        fprintf(book, "%s;%s;%s;%d;%d\n", books[i].num, books[i].ath, books[i].name, books[i].q, books[i].qs);
                fprintf(studbook, "%s;%s;%s\n", books[i].num, students[j].booknum, elem2.time);
            }
            int n;
            printf("1-reduce; 2-increase");
            scanf("%d", &n);
            if (n == 2) {
                if (elem.qs < elem.q) {
                    fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs + 1);
                    fprintf(studbook, "%s;%s;%s\n", elem.num, elem1.booknum, elem2.time);
                }
                else printf("There is no free!");
            }
            else if (n == 1) {
                if (elem.qs > 1) {
                    fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs - 1);
                    fprintf(studbook, "%s;%s;%s\n", elem.num, elem1.booknum, elem2.time);
                }
                else {
                    printf("There is no books\n");
                    printf("Book will be passed at: %s", elem2.time);
                }
                fclose(book);
            }
            else
                    printf("\nThere is no this ISBN or number of greatbook!\n ");
        }
    }
    if (add == 0) {
        exit(0);
    }
}
void studentsf(FILE* stdents) {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    struct students elem;
    FILE* stubooks;
    char file[5000];
    stdents = fopen("students.csv", "r");
    while ((fgets(file, 5000, stdents)) != NULL) {
        printf("\n%s", file);
    }
    fclose(stdents);
    printf("\nYou choosed:");
    int add;
    scanf("%d", &add);
    if (add == 1) {
        printf("\nEnter number of greatbook:");
        scanf("%s", elem.booknum);
        if (similar2(elem.booknum) != -1)
        {
            printf("This number of greatbook isn't available!\n");
            fclose(stdents);
        }
        else {
            printf("Enter surname:");
            scanf("%s", elem.surname);
            printf("Enter name:");
            scanf("%s", elem.name);
            printf("Enter middlename:");
            scanf("%s", elem.patr);
            printf("Enter faculty:");
            scanf("%s", elem.fac);
            printf("Enter department:");
            scanf("%s", elem.depart);
            stdents = fopen("students.csv", "a+");
            fprintf(stdents, "%s;%s;%s;%s;%s;%s\n", elem.booknum, elem.surname, elem.name, elem.patr, elem.fac, elem.depart);
        }
    }
    if (add == 2) {
        stubooks = fopen("student_books.csv", "r");
        char str[5000];
        while (fgets(str, 5000, stubooks) != NULL)
            printf("%s", str);
        printf("Enter number of greatbook:");
        scanf("%s", elem.booknum);
        int l = similar1(elem.booknum);
        if (l != -1) {
            printf("This student can't be removed because he has a books!\n");
        }
        else
            delstudents("students.csv");
    }
    if (add == 3) {
        printf("\nEnter number of greatbook:");
        scanf("%s", elem.booknum);
        stdents = fopen("students.csv", "r");
        rewind(stdents);
        int getfile = similar2(elem.booknum);
        int getfile1 = readb1("students.csv");
        fclose(stdents);
        if (getfile != -1)
        {
            printf("Enter surname:");
            scanf("%s", elem.surname);
            printf("Enter name:");
            scanf("%s", elem.name);
            printf("Enter middlename:");
            scanf("%s", &elem.patr);
            printf("Enter faculty:");
            scanf("%s", &elem.fac);
            printf("Enter department:");
            scanf("%s", elem.depart);
            stdents = fopen("students.csv", "w");
            int i;
            for (i = 0; i < getfile1; i++)
            {
                if (i != getfile)
                    fprintf(stdents, "%s;%s;%s;%s;%s;%s\n", students[i].booknum, students[i].surname, students[i].name, students[i].patr, students[i].fac, students[i].depart);
                fprintf(stdents, "%s;%s;%s;%s;%s;%s\n", elem.booknum, elem.surname, elem.name, elem.patr, elem.fac, elem.depart);
            }
            fclose(stdents);
        }
        else
            printf("\nThere is no this greatbook!\n ");
    }
    if (add == 4) {
        searchst("students.csv");
    }
    if (add == 5) {
        struct books elem1;
        struct stbooks elem2;
        FILE* book, * studbook;
        printf("\nEnter ISBN:");
        scanf("%s", elem1.num);
        printf("Enter number ofgreatbook:");
        scanf("%s", elem.booknum);
        book = fopen("books.csv", "r");
        stdents = fopen("students.csv", "r");
        rewind(book);
        rewind(stdents);
        int getfile = similar(elem1.num);
        int getfile2 = similar2(elem.booknum);
        int getfile1 = readb("books.csv");
        int getfile12 = readb1("students.csv");
        fclose(book);
        fclose(stdents);
        if (getfile == 0 && getfile2 == 0)
        {
            printf("Enter authorа:");
            scanf("%s", elem1.ath);
            printf("Enter title:");
            scanf("%s", elem1.name);
            printf("Number:");
            scanf("%d", &elem1.q);
            printf("Number of available booksг:");
            scanf("%d", &elem1.qs);
            printf("Date of pass:");
            scanf("%s", elem2.time);
            book = fopen("books.csv", "w");
            stdents = fopen("students.csv", "r");
            studbook = fopen("student_books.csv", "a+");
            int i, j;
            for (i = 0; i <

                getfile1; i++)
            {
                for (j = 0; j < getfile12; j++)
                    if (i != getfile && j != getfile2)
                        fprintf(book, "%s;%s;%s;%d;%d\n", books[i].num, books[i].ath, books[i].name, books[i].q, books[i].qs);
                fprintf(studbook, "%s;%s;%s\n", books[i].num, students[j].booknum, elem2.time);
            }
            int m;
            printf("1-issue; 2-take:");
            scanf("%d", &m);
            if (m == 2) {
                if (elem1.qs <= elem1.q) {
                    fprintf(book, "%s;%s;%s;%d;%d\n", elem1.num, elem1.ath, elem1.name, elem1.q, elem1.qs + 1);
                    fprintf(studbook, "%s;%s;\n", books[i].num, students[j].booknum);
                }

                else printf("There is nothing to take!");
            }
            else if (m == 1) {
                if (elem1.qs >= 1) {
                    fprintf(book, "%s;%s;%s;%d;%d\n", books[i].num, books[i].ath, books[i].name, books[i].q, books[i].qs);
                    fprintf(book, "%s;%s;%s;%d;%d\n", elem1.num, elem1.ath, elem1.name, elem1.q, elem1.qs - 1);
                    fprintf(studbook, "%s;%s;%s\n", elem1.num, elem.booknum, elem2.time);
                }
                else printf("There is no books\n"); 
                printf("Book will be passed at: %s", elem2.time);
            }
            fclose(book);
        }
        else
            printf("\nThere is no this ISBN or number of greatbook!\n ");
    }
    if (add == 0) {
        exit(0);
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    FILE* users;
    users = fopen("users.csv", "r+");
    char data[100];
    char book1[5];
    char studs[5];
    char login[100];
    char passwd[100];
    int arr = 0;
    printf("login: ");
    writestr(login);
    while (fgets(data, 100, users)) {
        char cpy[100];
        char* temp;
        strcpy(cpy, data);
        temp = strtok(cpy, ";");
        if (strcmp(login, temp) == 0) {
            printf("password: ");
            arr++;
            temp = strtok(NULL, ";");
            writestr(passwd);
            if (strcmp(passwd, temp) != 0) {
                printf("password is incorrect!");
                return 0;
            }
            else {
                temp = strtok(NULL, ";");
                strcpy(book1, temp);
                temp = strtok(NULL, ";");
                strcpy(studs, temp);
                break;
            }


        }
    }if (arr == 0) {
        printf("incorrect login\n");
        return 0;
    }


    while (status != '0') {
        system("cls");
        if (count != 0) {
            writestr(c);
        }
        if (book1[0] == '1' && studs[0] == '1') {
            printf("Main menu:\n");
            printf("(1) Books\n");
            printf("(2) Students\n");
            printf("(0) Exit\n");
            printf(" Your turn: ");
            status = getc(stdin);
            while (true) {
                if (status == '1') {
                    system("cls");
                    m = Mainbook();
                    break;
                }
                else if (status == '2') {
                    system("cls");
                    m = Mainstudents();
                    break;
                }
                else if (status == '0') {
                    printf("\nGood bye!");
                    return 0;

                }
                else {
                    printf("\nChoose something else: ");
                    status = getc(stdin);
                }
            }
        }
        else if (book1[0] == '1' && studs[0] != '1') {
            m = 1;
        }
        else if (book1[0] != '1' && studs[0] == '1') {
            m = 2;
        }
        if (count != 0) {
            count = 0;
            state = NULL;
        }

        while (state != '0') {
            if (m == 1) {
                if (count != 0 || (book1[0] != '1' || studs[0] != '1')) {
                    Mainbook();
                    state = getc(stdin);
                }
            }
            if (m == 2) {
                if (count != 0 || (book1[0] != '1' || studs[0] != '1')) {
                    Mainstudents();
                    state = getc(stdin);
                }
            }
        }
    }
}
void delbook(const char* file)
{
    FILE* book;
    char dnum[20];
    printf("Enter ISBN:");
    fflush(stdin);
    scanf("%s", dnum);

    book = fopen(file, "r");
    rewind(book);
    int getfile = similar(dnum);
    int getfile1 = readb(file);
    fclose(book);
    if (getfile != -1)
    {
        book = fopen("books.csv", "w");
        int i;
        for (i = 0; i < getfile1; i++)
        {
            if (i != getfile)
                fprintf(book, "%s;%s;%s;%d;%d\n", books[i].num, books[i].ath, books[i].name, books[i].q, books[i].qs);
        }
        fclose(book);

        printf("\nBook removed!\n");
    }
    else
        printf("\nThere is no this ISBN\n");
}
void delstudents(const char* file) {
    FILE* studentsf;
    char dbooknum[15];
    printf("\nEnter number of greatbook:");
    fflush(stdin);
    scanf("%s", dbooknum);
    studentsf = fopen(file, "r");
    rewind(studentsf);
    int getfile = similar2(dbooknum);
    int getfile1 = readb1(file);
    fclose(studentsf);
    if (getfile != -1)
    {
        studentsf = fopen("students.csv", "w");
        int i;
        for (i = 0; i < getfile1; i++)
        {
            if (i != getfile)
                fprintf(studentsf, "%s;%s;%s;%s;%s;%s\n", students[i].booknum, students[i].surname, students[i].name, students[i].patr, students[i].fac, students[i].depart);
        }
        fclose(studentsf);
        printf("\nStudent removed!\n");
    }
    else
        printf("\nThere is no this gratebook!\n");
}
int similar1(char num[20])
{
    int i, j;
    int temp = -1;
    for (i = 0; i < readb("student_books.csv"); i++)
        if (strcmp(num, books[i].num) == 0)
            temp = i;
    temp = i;
    return temp;
}
