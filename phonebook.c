#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct node
{
    struct node *next;
    struct node *prev;
    char *name;
    char *surname;
    char *number;
}node;

//functions prototypes
bool contact_exists(char *name, char *surname, node *list);
void add(node *new_person, node **list);
bool verifynumber(char *number);
bool checknumber(char *number, node *list);
void free_all();
void remove_contact(char *name, char*surname, node **list);
void search_contact(char *name, char *surname);
void look();

node *contact_list = NULL;

int main(int argc, char *argv[])
{
    if (argc != 2 || strcmp(argv[1], "start") != 0)
    {
        printf("Error! use ./phonebook start\n");
        return 1;
    }
    char* command = malloc(10 * sizeof(char));

    do
    {
        printf("\tMenu\t\n");
        printf("add - to add a new person in the phonebook\n");
        printf("remove - to remove a person from the phonebook\n");
        printf("search - to search a person in the phonebook\n");
        printf("look - to look the phonebook\n");
        printf("stop - to stop the program\n");
        printf("Type the command: ");
        scanf("%10s", command);
        while (strcmp(command, "add") != 0 && strcmp(command, "remove") != 0 && strcmp(command, "search") != 0 && strcmp(command, "look") != 0 && strcmp(command, "stop") != 0)
        {
            printf("Error!\n");
            printf("\tMenu\t\n");
            printf("add - to add a new person in the phonebook\n");
            printf("remove - to remove a person from the phonebook\n");
            printf("search - to search a person in the phonebook\n");
            printf("look - to look the phonebook\n");
            printf("stop - to stop the program\n");
            printf("Type the command: ");
            scanf("%10s", command);
        }

        if (strcmp(command, "add") == 0)
        {
            node *new_person = malloc(sizeof(node));
            if (new_person == NULL)
            {
                printf("Error!\n");
                continue;
            }
            new_person->name = malloc(25 * sizeof(char));
            new_person->surname = malloc(25 * sizeof(char));
            new_person->number = malloc(12 * sizeof(char));

            if (new_person->name == NULL || new_person->surname == NULL || new_person->number == NULL)
            {
                printf("Error!\n");
                free(new_person->name);
                free(new_person->surname);
                free(new_person->number);
                free(new_person);
                continue;
            }

            printf("Name: ");
            scanf("%25s", new_person->name);

            printf("Surname: ");
            scanf("%25s", new_person->surname);

            if (contact_exists(new_person->name, new_person->surname, contact_list) == true)
            {
                printf("There is already someone named %s %s\n", new_person->name, new_person->surname);
                free(new_person->name);
                free(new_person->surname);
                free(new_person->number);
                free(new_person);
                continue;
            }
            do
            {
                printf("Phone number: ");
                scanf("%10s", new_person->number);
            }
            while (verifynumber(new_person->number) == false);
            if (checknumber(new_person->number, contact_list) == true)
            {
                printf("There is already a person with this phone number\n");
                free(new_person->name);
                free(new_person->surname);
                free(new_person->number);
                free(new_person);
                continue;
            }
            add(new_person, &contact_list);
            printf("%s %s added to the phonebook\n", contact_list->name, contact_list->surname);
        }
        else if (strcmp(command, "remove") == 0)
        {
            char *name = malloc(25 * sizeof(char));
            char *surname = malloc(25 * sizeof(char));

            if (name == NULL || surname == NULL)
            {
                printf("Error!\n");
                free(name);
                free(surname);
                continue;
            }

            printf("Who do you want to remove from the phonebook?(digit name surname) ");
            scanf("%25s %25s", name, surname);

            if (contact_exists(name, surname, contact_list) == false)
            {
                printf("There is nobody called %s %s in the phonebook\n", name, surname);
                free(name);
                free(surname);
                continue;
            }

            char *control = malloc(5 * sizeof(char));
            do
            {
                printf("Are you sure?(digit Yes/No) ");
                scanf("%3s", control);
            }
            while(strcmp(control, "Yes") != 0 && strcmp(control, "No") != 0);

            if(strcmp(control, "No") == 0)
            {
                free(name);
                free(surname);
                free(control);
                continue;
            }

            remove_contact(name, surname, &contact_list);
            free(name);
            free(surname);
            free(control);
        }
        else if (strcmp(command, "search") == 0)
        {
            char *name = malloc(25 * sizeof(char));
            char *surname = malloc(25 * sizeof(char));

            if (name == NULL || surname == NULL)
            {
                printf("Error!\n");
                free(name);
                free(surname);
                continue;
            }

            printf("Who do you want to search in the phonebook?(digit name surname) ");
            scanf("%25s %25s", name, surname);

            if (contact_exists(name, surname, contact_list) == false)
            {
                printf("Not found, there is nobody called %s %s in the phonebook\n", name, surname);
                free(name);
                free(surname);
                continue;
            }

            search_contact(name, surname);
            free(name);
            free(surname);
        }
        else if (strcmp(command, "look") == 0)
        {
            look();
            char *control = malloc(5 * sizeof(char));
            do
            {
                printf("Do you want to print the phonebook in a phonebook.csv file?(digit Yes/No) ");
                scanf("%3s", control);
            }
            while(strcmp(control, "Yes") != 0 && strcmp(control, "No") != 0);

            if (strcmp(control, "Yes") == 0)
            {
                FILE *file = fopen("phonebook.csv", "a");
                if (file != NULL)
                {
                    for (node *tmp = contact_list; tmp != NULL; tmp = tmp->next)
                    {
                        fprintf(file, "Name: %s \t Surname: %s \t Number: %s\n", tmp->name, tmp->surname, tmp->number);
                    }
                    fclose(file);
                }
                else
                {
                    printf("Error: Could not open phonebook.csv for writing.\n");
                }
            }
            free(control);
        }

    }
    while(strcmp(command, "stop") != 0);

    free_all();
    free(command);
}

bool verifynumber(char *number)
{
    for (int i = 0, k = strlen(number); i < k; i++)
    {
        if (isdigit(number[i]) == 0)
        {
            printf("Error! Phone number must consist of digits\n");
            return false;
        }
    }
    return true;
}

bool checknumber(char *number, node *list)
{
    node *tmp =  list;
    while (tmp != NULL)
    {
        if (strcmp(number, tmp->number) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

bool contact_exists(char *name, char *surname, node *list)
{
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        if (strcmp(name, tmp->name) == 0 && strcmp(surname, tmp->surname) == 0)
        {
            return true;
        }
    }
    return false;
}

void add(node *new_person, node **list)
{
    new_person->next = *list;
    new_person->prev = NULL;
    if (*list != NULL)
    {
        (*list)->prev = new_person;
    }
    *list = new_person;
}

void free_all()
{
    while(contact_list != NULL)
    {
        node *tmp = contact_list;
        contact_list = contact_list->next;
        free(tmp->name);
        free(tmp->surname);
        free(tmp->number);
        free(tmp);
    }
}

void remove_contact(char *name, char*surname, node **list)
{
    node *tmp = *list;
    while (tmp != NULL && (strcmp(name, tmp->name) != 0 || strcmp(surname, tmp->surname) != 0))
    {
        tmp = tmp->next;
    }

    if (tmp == NULL)
    {
        printf("Contact not found\n");
        return;
    }

    if (tmp == *list)
    {
        *list = tmp->next;
    }

    if (tmp->prev != NULL)
    {
        tmp->prev->next = tmp->next;
    }

    if (tmp->next != NULL)
    {
        tmp->next->prev = tmp->prev;
    }

    printf("Removed\n");
    free(tmp->name);
    free(tmp->surname);
    free(tmp->number);
    free(tmp);
    return;
}

void search_contact(char *name, char *surname)
{
    node *tmp = contact_list;

    while (tmp != NULL && (strcmp(name, tmp->name) != 0 || strcmp(surname, tmp->surname) != 0))
    {
        tmp = tmp->next;
    }

    if (tmp == NULL)
    {
        printf("Contact not found\n");
        return;
    }

    printf("Found! Phone number: %s\n", tmp->number);
}

void look()
{
    for(node *tmp = contact_list; tmp != NULL; tmp = tmp->next)
    {
        printf("Name: %s \t Surname: %s \t Number: %s\n", tmp->name, tmp->surname, tmp->number);
    }
}
