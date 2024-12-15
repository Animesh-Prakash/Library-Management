#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct book_details
{
    char book_names[100];
    char author_name[100];
    int price;
    int avai;
    char cate[100];
};

void load_books(struct book_details book[100])
{
    FILE *ptr;
    ptr = fopen("Book_details.txt", "r");
    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), ptr) != NULL && i < 25)
    {
        if (strstr(line, "Book name") != NULL)
        {
            strcpy(book[i].book_names, strchr(line, ':') + 1);
        }
        else if (strstr(line, "Author name") != NULL)
        {
            strcpy(book[i].author_name, strchr(line, ':') + 1);
        }
        else if (strstr(line, "Price") != NULL)
        {
            book[i].price = atoi(strchr(line, ':') + 1);
        }
        else if (strstr(line, "Available") != NULL)
        {
            book[i].avai = atoi(strchr(line, ':') + 1);
            i++;
        }
    }

    fclose(ptr);
}

void book1(struct book_details book[100])
{
    load_books(book);
    for (int i = 0; i < 25; i++)
    {
        printf("%d).Book name:%sAuthor name:%sPrice:%d\nAvailable:%d\n\n", i + 1, book[i].book_names, book[i].author_name, book[i].price, book[i].avai);
    }
}

struct card
{
    char lname[100];
    int lroll_no;
    int semester;
    char branch[20];
    int phone_no;
};

void card_details(struct card *s1, struct book_details bookss[], int num_books, int num_students, int book_selec[num_books])
{
    time_t current_time;
    struct tm *timeinfo;

    time(&current_time);
    timeinfo = localtime(&current_time);

    FILE *fptr;
    char filename[50];

    for (int i = 0; i < num_students; i++)
    {
        printf("Enter your name :");
        fgets(s1[i].lname, sizeof(s1[i].lname), stdin);

        printf("Enter the roll no.:");
        scanf("%d", &s1[i].lroll_no);
        getchar();

        printf("Semester :");
        scanf("%d", &s1[i].semester);
        getchar();

        printf("In which branch are you :");
        fgets(s1[i].branch, sizeof(s1[i].branch), stdin);

        printf("Enter your mobile number: ");
        scanf("%d", &s1[i].phone_no);
        getchar();

        sprintf(filename, "Students_detail.txt");
        fptr = fopen(filename, "a");

        if (fptr == NULL)
        {
            printf("Error opening file %s for writing.\n", filename);
            continue;
        }
        fprintf(fptr, "Student roll no :%d\n", s1[i].lroll_no);
        fprintf(fptr, "Student name :%s", s1[i].lname);
        fprintf(fptr, "Semester :%d\n", s1[i].semester);
        fprintf(fptr, "Student branch :%s", s1[i].branch);
        fprintf(fptr, "Student phone number :%d\n", s1[i].phone_no);
        fprintf(fptr, "Books issued successfully\n");
        fprintf(fptr, "Total Books :%d\n", num_books);

        for (int j = 0; j < num_books; j++)
        {
            fprintf(fptr, "Book name :%sBook serial no. :%d\nAuthor name :%sPrice :%d\n", bookss[j].book_names, book_selec[j], bookss[j].author_name, bookss[j].price);
        }

        fprintf(fptr, "Date :%d/%d/%d\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, 1900 + timeinfo->tm_year);
        fprintf(fptr, "Time :%d:%d:%d\n\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

        fclose(fptr);
    }
    printf("\nBook issued successfully\n");
    printf("Current time and date: %s", asctime(timeinfo));
    printf("Instruction\nYou have to return this book within 15 days\n");
    printf("If you don't return the book within 15 days then you have to pay a fine\n");
    printf("Fine :15/day\n");
}

void recur(char x[30], struct book_details book[100], int book_selec[], int num_books, struct card *s1, struct book_details bookss[])
{
    char de[10] = "yes", on[10] = "no";
    time_t currentTime;
    struct tm *localTime;
    currentTime = time(NULL);
    localTime = localtime(&currentTime);

    printf("Do you really want to issue this book :");
    scanf("%s", x);
    getchar(); // to consume the newline character left by scanf

    if (strcmp(x, de) == 0)
    {
        for (int i = 0; i < num_books; i++)
        {
            --book[book_selec[i] - 1].avai;
        }

        FILE *ptr = fopen("Book_details.txt", "w");
        for (int i = 0; i < 25; i++)
        {
            fprintf(ptr, "%d).Book name :%s Author name :%s Price :%d\nAvailable :%d\n", i + 1, book[i].book_names, book[i].author_name, book[i].price, book[i].avai);
        }
        fclose(ptr);

        printf("\nMake a library card for issue the book\n");
        card_details(s1, bookss, num_books, 1, book_selec); // Call card_details function here
    }
    else if (strcmp(x, on) == 0)
    {
        printf("Book issue canceled");
    }
    else
    {
        recur(x, book, book_selec, num_books, s1, bookss);
    }
}

void book2(struct book_details book[100], struct book_details bookss[], int num_books)
{
    char x[30];
    FILE *ptr;
    struct card s1;

    if (num_books >= 1 && num_books <= 5)
    {
        int book_selec[num_books];
        printf("Enter the serial no. which book you want :");
        for (int i = 0; i < num_books; i++)
        {
            scanf("%d", &book_selec[i]);
        }
        getchar();
        for (int i = 0; i < num_books; i++)
        {
            if (book_selec[i] > 25)
            {
                printf("We don't have more than 25 books\n");
                scanf("%d", &book_selec[i]);
                getchar();
            }
        }
        ptr = fopen("Book_details.txt", "w");
        for (int i = 0; i < 25; i++)
        {
            fprintf(ptr, "%d).Book name: %s\nAuthor name: %s\tPrice: %d\nAvailable: %d\n",
                    i + 1, book[i].book_names, book[i].author_name, book[i].price, book[i].avai);
        }
        fclose(ptr);
        struct book_details bookss[num_books];

        printf("\nBooks selected\n");
        for (int i = 0; i < num_books; i++)
        {
            strcpy(bookss[i].book_names, book[book_selec[i] - 1].book_names);
            strcpy(bookss[i].author_name, book[book_selec[i] - 1].author_name);
            bookss[i].price = book[book_selec[i] - 1].price;
            bookss[i].avai = book[book_selec[i] - 1].avai;
            printf("Book name :%sAuthor name :%sPrice:%d\n", bookss[i].book_names, bookss[i].author_name, bookss[i].price);
        }

        recur(x, book, book_selec, num_books, &s1, bookss);
    }
    else
    {
        printf("You can't choose more than 5 books\n");
        book2(book, bookss, num_books);
    }
}

// The remaining code remains the same

void return_book(struct book_details book[100])
{
    char read_name[100], read_branch[20];
    int read_rollno, read_sem, next_numbooks, next_rollno, fine;
    FILE *str;
    char next_name[100];

    printf("Enter your roll no.: ");
    scanf("%d", &read_rollno);
    getchar(); // consume newline character

    str = fopen("Students_detail.txt", "r");
    if (str == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    char line[500];
    int return_numbooks;
    int days_difference = 0;

    int total_books = 0;
    int book_serial_numbers[100]; // Array to store book serial numbers
    int serial_index = 0;
    char choice[20];
    char de[10] = "yes", on[10] = "no";
    int roll_no_found = 0;
    int found_roll_no = 0;

    while (fgets(line, sizeof(line), str) != NULL)
    {
        if (strstr(line, "Student roll no") != NULL)
        {
            // Extract the next student roll number from the line
            next_rollno = atoi(strchr(line, ':') + 1);
            if (next_rollno == read_rollno)
            {
                roll_no_found = 1;
                printf("You must return all the books together\n\n");

                while (fgets(line, sizeof(line), str) != NULL)
                {
                    if (strstr(line, "Book name") != NULL)
                    {
                        printf("%s", line); // Print book name
                        total_books++;
                    }
                    else if (strstr(line, "Book serial no.") != NULL)
                    {
                        int serial_number = atoi(strchr(line, ':') + 1);
                        printf("Serial No.: %d\n", serial_number);         // Print book serial number
                        book_serial_numbers[serial_index] = serial_number; // Assign serial number to array
                        serial_index++;                                    // Increment index
                    }
                    else if (strstr(line, "Author name") != NULL)
                    {
                        printf("%s", line); // Print author name
                    }
                    else if (strstr(line, "Price") != NULL)
                    {
                        printf("%s", line); // Print price
                    }
                    else if (strstr(line, "Date") != NULL)
                    {
                        // Extract the date from the line
                        int file_day, file_month, file_year;
                        sscanf(line, "Date :%d/%d/%d", &file_day, &file_month, &file_year);

                        // Get current date
                        time_t now;
                        struct tm *current;
                        time(&now);
                        current = localtime(&now);
                        int current_day = current->tm_mday;
                        int current_month = current->tm_mon + 1;    // Month is 0-indexed
                        int current_year = current->tm_year + 1900; // Years since 1900

                        // Calculate the difference in days
                        days_difference = (current_year - file_year) * 365 + (current_month - file_month) * 30 + (current_day - file_day);

                        printf("Difference in days: %d\n", days_difference);

                        if (days_difference >= 15)
                        {
                            printf("It has been 15 days or more since you issued the books.\n");
                            printf("Please return the books to avoid fines.\n");
                        }

                        break; // Exit the loop after processing the date
                    }
                    else if (strcmp(line, "\n") == 0)
                    {

                        break; // Exit the loop after finding a gap between lines
                    }
                }
                break;
            }
        }
    }

    fclose(str);
    if (!roll_no_found)
    {
        printf("Roll number not found. Please enter a valid roll number.\n");
        return_book(book); // Recall the function recursively
        return;            // Exit the function
    }
    printf("Check details if it is correct then return the book :");
    scanf("%s", choice);
    getchar();
    if (strcmp(choice, de) == 0)
    {
        if (days_difference >= 15)
        {
            printf("\n");
            printf("You return the book after 15 days, so you have to pay fine\n");
            printf("If you don't pay fine then books will not be returned\n");
            printf("Fine: 15/days\n");
            printf("Your total fine is %d\n", days_difference * 15);
            printf("Pay fine :");
            scanf("%d", &fine);
            getchar();
            if (fine == (days_difference * 15))
            {
                printf("Your payment was successful\n");
                printf("Book returned successfully\n");
                str = fopen("Book_details.txt", "r");
                if (str == NULL)
                {
                    printf("Error opening file!\n");
                    return;
                }
                char line3[256];
                int x = 0;
                while (fgets(line3, sizeof(line3), str) != NULL && x < 25)
                {
                    if (strstr(line3, "Book name") != NULL)
                    {
                        strcpy(book[x].book_names, strchr(line3, ':') + 1);
                    }
                    else if (strstr(line3, "Author name") != NULL)
                    {
                        strcpy(book[x].author_name, strchr(line3, ':') + 1);
                    }
                    else if (strstr(line3, "Price") != NULL)
                    {
                        book[x].price = atoi(strchr(line3, ':') + 1);
                    }
                    else if (strstr(line3, "Available") != NULL)
                    {
                        book[x].avai = atoi(strchr(line3, ':') + 1);
                        x++;
                    }
                }
                fclose(str);
                for (int a = 0; a < serial_index; a++)
                {
                    ++book[book_serial_numbers[a] - 1].avai;
                }
                str = fopen("Book_details.txt", "w");
                for (int i = 0; i < 25; i++)
                {
                    fprintf(str, "%d).Book name :%s Author name :%sPrice :%d\nAvailable :%d\n", i + 1, book[i].book_names, book[i].author_name, book[i].price, book[i].avai);
                }
                fclose(str);
                int delete_roll;
                FILE *fp, *temp;
                char student[256];
                int found = 0;
                // int student_line = "\n";

                fp = fopen("Students_detail.txt", "r+");
                if (fp == NULL)
                {
                    printf("Error opening file");
                }

                temp = fopen("temp.txt", "w");
                if (temp == NULL)
                {
                    printf("Error creating file");
                    fclose(fp);
                }

                while (fgets(student, sizeof(student), fp) != NULL)
                {
                    int roll;
                    sscanf(student, "Student roll no : %d", &roll);

                    if (roll == read_rollno)
                    {
                        found = 1;
                        while (fgets(student, sizeof(student), fp) != NULL && strcmp(student, "\n") != 0)
                            continue;
                        continue;
                    }
                    fputs(student, temp);
                }
                fclose(fp);
                fclose(temp);
                remove("Students_detail.txt");
                rename("temp.txt", "Students_detail.txt");
            }
            else
            {
                printf("You haven't paid all the money\n");
                printf("You have to fill your details again\n");
                return_book(book);
            }
        }
        else
        {
            printf("Book returned successfully\n");
            str = fopen("Book_details.txt", "r");
            if (str == NULL)
            {
                printf("Error opening file!\n");
                return;
            }
            char line2[256];
            int j = 0;
            while (fgets(line2, sizeof(line2), str) != NULL && j < 25)
            {
                if (strstr(line2, "Book name") != NULL)
                {
                    strcpy(book[j].book_names, strchr(line2, ':') + 1);
                }
                else if (strstr(line2, "Author name") != NULL)
                {
                    strcpy(book[j].author_name, strchr(line2, ':') + 1);
                }
                else if (strstr(line2, "Price") != NULL)
                {
                    book[j].price = atoi(strchr(line2, ':') + 1);
                }
                else if (strstr(line2, "Available") != NULL)
                {
                    book[j].avai = atoi(strchr(line2, ':') + 1);
                    j++;
                }
            }
            fclose(str);
            for (int a = 0; a < serial_index; a++)
            {
                ++book[book_serial_numbers[a] - 1].avai;
            }
            str = fopen("Book_details.txt", "w");
            for (int i = 0; i < 25; i++)
            {
                fprintf(str, "%d).Book name :%s Author name :%sPrice :%d\nAvailable :%d\n", i + 1, book[i].book_names, book[i].author_name, book[i].price, book[i].avai);
            }
            fclose(str);

            int delete_roll;
            FILE *fp, *temp;
            char student[256];
            int found = 0;
            // int student_line = "\n";

            fp = fopen("Students_detail.txt", "r+");
            if (fp == NULL)
            {
                printf("Error opening file");
            }

            temp = fopen("temp.txt", "w");
            if (temp == NULL)
            {
                printf("Error creating file");
                fclose(fp);
            }

            while (fgets(student, sizeof(student), fp) != NULL)
            {
                int roll;
                sscanf(student, "Student roll no : %d", &roll);

                if (roll == read_rollno)
                {
                    found = 1;
                    while (fgets(student, sizeof(student), fp) != NULL && strcmp(student, "\n") != 0)
                        continue;
                    continue;
                }
                fputs(student, temp);
            }
            fclose(fp);
            fclose(temp);
            remove("Students_detail.txt");
            rename("temp.txt", "Students_detail.txt");
        }
    }
    else if (strcmp(choice, on) == 0)
    {
        printf("Book return canceled");
    }
    else
    {
        printf("Fill details properly\n");
        return_book(book);
    }
}

void choose(int *option)
{
    struct book_details book[100];
    FILE *ptr;
    int num_books;
    struct book_details bookss[100];
    struct card s1;
    printf("Enter your choice :");
    scanf("%d", option);
    getchar();
    if ((*option) == 1)
    {

        book1(book);

        printf("Enter the number of books you want: ");
        scanf("%d", &num_books);
        getchar();
        book2(book, bookss, num_books);
    }
    else if ((*option) == 2)
    {
        return_book(book);
    }

    else if ((*option) == 3)
    {
        printf("Thank you\n");
    }
    else
    {
        choose(option);
    }
}

int main()
{
    char name[50];
    int roll_no;
    int option;
    struct book_details book[100];
    struct book_details bookss;
    FILE *ptr;
    struct card s1;

    printf("WELCOME TO OUR LIBRARY\n");
    printf("Please Enter you Details\n");

    printf("Enter your Name:");
    fgets(name, sizeof(name), stdin);
    printf("Enter your roll no.:");
    scanf("%d", &roll_no);
    printf("Welcome %s\n", name);

    printf("1).Issue book\n");
    printf("2).Return a book\n");
    printf("3).Exit\n");

    choose(&option);

    return 0;
}