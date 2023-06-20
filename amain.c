#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<conio.h>
void addBook();
void booksList();
void del();
void issueBook();
void issueList();
void submit();
struct books
{
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
    int quant;
} b;

struct student
{
    int id;
    char Name[50];
    char Class[50];
    int Roll;
    char bookName[50];
    char date[12];
} s;

FILE *fp;

int main()
{

    int ch;

    while (1)
    {
        system("cls");
        printf("****************************** Library Management System **************************\n******************************                           **************************\n******************************--------------------------**************************\n");
        printf("1.Add Book\n");
        printf("2.Books List\n");
        printf("3.Remove Book\n");
        printf("4.Issue Book\n");
        printf("5.Issued Book List\n");
        printf("6.Submit Book \n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
            exit(0);

        case 1:
            addBook();
            break;

        case 2:
            booksList();
            break;

        case 3:
            del();
            break;

        case 4:
            issueBook();
            break;

        case 5:
            issueList();
            break;

        case 6:
            submit();
            break;

        default:
            printf("Invalid Choice...\n\n");
        }
        printf("\nPress Any Key To Continue...");
        getch();
    }

    return 0;
}

void addBook()
{
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    printf("Enter book id: ");
    scanf("%d", &b.id);

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);
    printf("Enter quantity : ");
    fflush(stdin);
    scanf("%d", &b.quant);
    printf("Book Added Successfully");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

void booksList()
{

    system("cls");
    printf("****************************** Available books **************************\n\n\n");
    printf("%-10s %-30s %-20s %-10s %s\n\n", "Book id", "Book Name", "Author", "Quantity", "Date");

    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        printf("%-10d %-30s %-20s %-10d %s\n", b.id, b.bookName, b.authorName, b.quant, b.date);
    }

    fclose(fp);
}

void del()
{
    int id, f = 0;
    system("cls");
    printf("****************************** Delete books **************************\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (id == b.id)
        {
            f = 1;
        }
        else
        {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1)
    {
        printf("\n\nDeleted Successfully.");
    }
    else
    {
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void issueBook()
{
    FILE *y;
    y = fopen("temp.txt", "wb");

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f = 0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    fp = fopen("books.txt", "a+");

    while (fread(&b, sizeof(b), 1, fp) == 1)
    {
        if (b.id == s.id)
        {      if(b.quant==0){
            printf("Book not available\n");
            return;
            
        }
            strcpy(s.bookName, b.bookName);
            f = 1;
            b.quant = b.quant - 1;
            fwrite(&b, sizeof(b), 1, y);
        }
        else
        {
            fwrite(&b, sizeof(b), 1, y);
        }
    }
    fclose(fp);
    fclose(y);

    remove("books.txt");
    rename("temp.txt", "books.txt");
    if (f == 0)
    {
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.Name);

    printf("Enter Student Class: ");
    fflush(stdin);
    gets(s.Class);

    printf("Enter Student Roll: ");
    scanf("%d", &s.Roll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList()
{
    system("cls");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-20s %-10s %-30s %s\n\n", "S.id", "Name", "Class", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf("%-10d %-30s %-20s %-10d %-30s %s\n", s.id, s.Name, s.Class, s.Roll, s.bookName, s.date);
    }

    fclose(fp);
}
void submit()
{
    system("cls");
    int f = 0;
    FILE *ft;
    ft = fopen("temp.txt", "wb");
    int k;
    FILE *fy, *l;
    l = fopen("tmp.txt", "wb");
    fy = fopen("books.txt", "rb");

    fp = fopen("issue.txt", "rb");
    printf("Enter Book id to submit: ");
    fflush(stdin);
    scanf("%d", &k);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        if (k == s.id&&f!=1)
        {
            f = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, ft);
        }
    }
    while (fread(&b, sizeof(b), 1, fy) == 1)
    {
        if (k == b.id)
        {
            b.quant++;
            fwrite(&b, sizeof(b), 1, l);
        }
        else
        {
            fwrite(&b, sizeof(b), 1, l);
        }
    }
    if (f == 1)
    {
        printf("Book submitted Successfully\n\n");
    }
    else
    {
        printf("Book id not found in issued list \n\n");
        return;
    }

    fclose(fp);
    fclose(ft);
    fclose(l);
    fclose(fy);

    remove("issue.txt");
    rename("temp.txt", "issue.txt");
    remove("books.txt");
    rename("tmp.txt", "books.txt");
    return;
}