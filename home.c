#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>

char state;
char status;
char c[2];
int m;
int kaunt = 0;
int MainMenustd();
int MainMenu();
char* writestr(char str[]);
char* writestr(char str[]) {
    int c, i = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        str[i++] = c;
    }str[i] = '\0';
    return str;
}

int MainMenu() {
    printf("-------Книжное меню-------\n\n");
    printf("(1) Добавить новую книгу\n");
    printf("(2) Удалить книгу\n");
    printf("(3) Редактировать информацию по книге\n");
    printf("(4) Изменить количество книг по номеру ISBN\n");
    printf("(5) Просмотреть информацию студентов по номеру ISBN\n");
    printf("(6) Выдача книг\n");
    printf("(7) Сдача книги\n");
    printf("(0) Выйти\n");
    printf(" Ваш выбор: ");
    return 1;
}

int MainMenustd() {
    printf("\n-------Студентечское меню-------\n\n");
    printf("(1) Добавить нового студента\n");
    printf("(2) Удалить студента\n");
    printf("(3) Редактировать информацию по студенту\n");
    printf("(4) Посмотреть информацию по студенту\n");
    printf("(5) Просмотреть информацию книг по номеру зачетной книжки\n");
    printf("(6) Выдача книг\n");
    printf("(7) Сдача книги\n");
    printf("(0) Выйти\n");
    printf(" Ваш выбор: ");
    return 2;

}
typedef struct books book1;
struct books {
    char num[20];
    char ath[60];
    char name[60];
    int q;
    int qs;
};
book1 books[1000];
void delbook(const char* file);
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
int similar(char num[20])
{
    int i;
    int temp = -1;
    for (i = 0; i < readb("books.csv"); i++)
        if (strcmp(num, books[i].num) == 0)
            temp = i;
    return temp;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    //FILE* book;
    struct books elem;
    FILE* users;
    users = fopen("users.csv", "r+");
    char data[100];
    char book1[5];
    char studs[5];
    char login[100];
    char passwd[100];
    int arr = 0;
    printf("Введите логин(log): ");
    writestr(login);
    while (fgets(data, 100, users)) {
        char cpy[100];
        char* tmp;
        strcpy(cpy, data);
        tmp = strtok(cpy, ";");
        if (strcmp(login, tmp) == 0) {
            printf("Введите пароль(pas): ");
            arr++;
            tmp = strtok(NULL, ";");
            writestr(passwd);
            if (strcmp(passwd, tmp) != 0) {
                printf("Пароль неверный, попробуйте еще раз(inpas): ");
                return 0;
            }
            else {
                tmp = strtok(NULL, ";");
                strcpy(book1, tmp);
                tmp = strtok(NULL, ";");
                strcpy(studs, tmp);
                break;
            }


        }
    }if (arr == 0) {
        printf("Данного пользователя нет\n\nПопробуйте еще раз!(inlog)\n\n");
        return 0;
    }


    while (status != '0') {
        system("cls");
        if (kaunt != 0) {
            writestr(c);
        }
        if (book1[0] == '1' && studs[0] == '1') {
            printf("----------Главное меню-------------\n");
            printf("(1) Меню книг\n");
            printf("(2) Меню студентов\n");
            printf("(0) Выйти\n");
            printf(" Ваш Выбор: ");
            status = getc(stdin);
            while (true) {
                if (status == '1') {
                    system("cls");
                    m = MainMenu();
                    break;
                }
                else if (status == '2') {
                    system("cls");
                    m = MainMenustd();
                    break;
                }
                else if (status == '0') {
                    printf("\n----------До связи----------");
                    return 0;

                }
                else {
                    printf("\nВведите другую цифру: ");
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
        if (kaunt != 0) {
            kaunt = 0;
            state = NULL;
        }

        while (state != '0') {
            if (m == 1) {
                if (kaunt != 0 || (book1[0] != '1' || studs[0] != '1')) {
                    MainMenu();
                    state = getc(stdin);
                }
            }

            if (m == 2) {
                if (kaunt != 0 || (book1[0] != '1' || studs[0] != '1')) {
                    MainMenustd();
                    state = getc(stdin);
                }
            }
        }
    }
    FILE* book;
    book = fopen("books.csv", "r");
    char file[5000];
    while (fgets(file, 5000, book) != NULL) {
        printf("%s", file);
    }
    fclose(book);
    char add;
    printf("\nВыберете операцию:\n");
    printf("**********Чтобы добавить, нажмите A**********\n");
    printf("**********Чтобы удалить, нажмите D***********\n");
    printf("**********Чтобы забрать/выдать, нажмите G****\n");
    printf("**********Чтобы выйти, нажмите E*************\n");
    scanf("%c", &add);
    if (add == 'A') {
        book = fopen("books.csv", "a+");
        printf("Введите ISBN:");
        fflush(stdin);
        scanf("%s", elem.num);
        if (similar(elem.num) != -1)
        {
            printf("Такой ISBN ужу есть!\n");
            fclose(book);
        }
        else {
            printf("Введите автора:");
            scanf("%s", elem.ath);
            printf("Введите название:");
            scanf("%s", elem.name);
            printf("Введите количество:");
            scanf("%d", &elem.q);
            printf("Введите количество доступных книг:");
            scanf("%d", &elem.qs);
            book = fopen("books.csv", "a+");
            fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs);
            fclose(book);
        }
    }
    if (add == 'D') {
        delbook("books.csv");
    }
    if (add == 'G') {
        printf("\nВведите ISBN:");
        scanf("%s", elem.num);
        book = fopen("books.csv", "r");
        rewind(book);
        int getfile = similar(elem.num);
        int getfile1 = readb("books.csv");
        fclose(book);
        if (getfile != -1)
        {
            printf("Введите автора:");
            scanf("%s", elem.ath);
            printf("Введите название:");
            scanf("%s", elem.name);
            printf("Количество книг:");
            scanf("%d", &elem.q);
            printf("Количество доступных книг:");
            scanf("%d", &elem.qs);
            book = fopen("books.csv", "w");
            int i;
            for (i = 0; i < getfile1; i++)
            {
                if (i != getfile)
                    fprintf(book, "%s;%s;%s;%d;%d\n", books[i].num, books[i].ath, books[i].name, books[i].q, books[i].qs);
            }
            int n;
            printf("1-уменьшить; 2-увеличить");
            scanf("%d", &n);
            if (n == 2) {
                if (elem.qs < elem.q)
                    fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs + 1);
                else printf("Нечего забирать!");
            }
            else if (n == 1) {
                if (elem.qs > 1)
                    fprintf(book, "%s;%s;%s;%d;%d\n", elem.num, elem.ath, elem.name, elem.q, elem.qs - 1);
                else printf("Недостаточно книг");
            }
            fclose(book);
        }
        else
            printf("\nНет такого ISBN!\n ");
    }
    if (add == 'E') {
        exit(0);
    }
}
void delbook(const char* file)
{
    FILE* book;
    char dnum[20];
    printf("Введите ISBN:");
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
        printf("\nКнига удалена!");
    }
    else
        printf("\nНет такого ISBN\n");
}
