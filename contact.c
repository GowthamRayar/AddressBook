#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void swap_contacts(Contact *a, Contact *b)
{
    Contact temp = *a;
    *a = *b;
    *b = temp;
}

void sort_contacts(AddressBook *addressBook, int criteria)
{
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            int compare = 0;
            if (criteria == 1)
            {
                compare = strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
            }
            else if (criteria == 2)
            {
                compare = strcasecmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
            }
            else if (criteria == 3)
            {
                compare = strcasecmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
            }

            if (compare > 0)
            {
                swap_contacts(&addressBook->contacts[j], &addressBook->contacts[j + 1]);
            }
        }
    }
}

void listContacts(AddressBook *addressBook, int sortCriteria)
{

    if (addressBook->contactCount == 0)
    {
        printf("AddressBook is empty!\n\n");
        return;
    }

    // Sort contacts based on the chosen criteria using bubble sort
    sort_contacts(addressBook, sortCriteria);

    printf("--------------------------------------------------\n");
    printf("Name              Phone No.        Email ID       \n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d) %s\t %s\t %s\t \n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("\n\n");
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

int validate_name(const char *name)
{
    regex_t regex;
    const char *NAME_PATTERN = "^[A-Za-z]+([ .-][A-Za-z]+)*$"; // pattern to handle dots, spaces, and hyphens
    if (regcomp(&regex, NAME_PATTERN, REG_EXTENDED) != 0)
    {
        return 0; // Regex compilation failed
    }
    int result = regexec(&regex, name, 0, NULL, 0);
    regfree(&regex);      // Free regex memory
    return (result == 0); // Return 1 if valid, 0 if invalid
}

int validate_email(const char *email)
{
    regex_t regex;
    const char *EMAIL_PATTERN = "^[a-zA-Z0-9_]+[@][a-z]+[\\.][a-zA-Z]{2,3}$";
    if (regcomp(&regex, EMAIL_PATTERN, REG_EXTENDED) != 0)
    {
        return 0; // Regex compilation failed
    }
    int result = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);      // Free regex memory
    return (result == 0); // Return 1 if valid, 0 if invalid
}

int validate_mobile(const char *mobile)
{
    regex_t regex;
    const char *MOBILE_PATTERN = "^[0-9]{10}$";
    if (regcomp(&regex, MOBILE_PATTERN, REG_EXTENDED) != 0)
    {
        return 0; // Regex compilation failed
    }
    int result = regexec(&regex, mobile, 0, NULL, 0);
    regfree(&regex);      // Free regex memory
    return (result == 0); // Return 1 if valid, 0 if invalid
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("AddressBook is Full!\n\n");
        return;
    }

    int num_contacts;
    printf("How many contacts you want to create : ");
    scanf("%d", &num_contacts);
    getchar(); // consume newline left by scanf

    // The address where we want to add new contact
    Contact *contact_ptr = &addressBook->contacts[addressBook->contactCount];

    while (num_contacts--)
    {
        // Loop to validate name and run infinitely if input is invalid
        while (1)
        {
            printf("Enter the name of contact : ");
            scanf("%[^\n]", contact_ptr->name);
            getchar(); // consume newline left by scanf
            if (validate_name(contact_ptr->name))
            {
                break;
            }
            else
            {
                printf("Error : Entered name should only contain alphabets!\n\n");
            }
        }

        // Loop to validate phone number and run infinitely if input is invalid
        while (1)
        {
            printf("Enter the phone number : ");
            scanf("%[^\n]", contact_ptr->phone);
            getchar(); // consume newline left by scanf
            if (validate_mobile(contact_ptr->phone))
            {
                break;
            }
            else
            {
                printf("Error : Mobile number must be 10 digits only!\n\n");
            }
        }

        // Loop to validate email and run infinitely if input is invalid
        while (1)
        {
            printf("Enter the email : ");
            scanf("%[^\n]", contact_ptr->email);
            getchar(); // consume newline left by scanf
            if (validate_email(contact_ptr->email))
            {
                break;
            }
            else
            {
                printf("Error : Invalid email format!\n\n");
            }
        }
    }

    addressBook->contactCount++;
    printf("Contact successfully added!\n\n");
}

void displayContacts(int *indices, int count, AddressBook *addressBook)
{
    if (count == 1)
    {
        int index = indices[0];
        printf("--------------------------------------------------\n");
        printf("Name              Phone No.        Email ID       \n");
        printf("--------------------------------------------------\n");
        printf("%d) %s\t %s\t %s\t \n", 1, addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
        printf("\n\n");
    }
    else if (count > 1)
    {
        printf("--------------------------------------------------\n");
        printf("Name              Phone No.        Email ID       \n");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < count; i++)
        {
            int index = indices[i];
            printf("%d) %s\t %s\t %s\t \n", i + 1, addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
        }
        printf("\n\n");
    }
    else
    {
        printf("No contacts found with provided Name!\n\n");
    }
}

void searchContact(AddressBook *addressBook)
{
    int option;
    int indices[MAX_CONTACTS];
    int count;

    while (1)
    {
        printf("How do you want to search : \n1. Using Name\n2. Using Phone\n3. Using Email\n4. Exit\n\n");
        scanf("%d", &option);
        getchar(); // consume newline left by scanf
        printf("\n");
        count = 0; // reset count for every search
        switch (option)
        {
        case 1:
        {
            char name[50];
            printf("Enter name to search : ");
            scanf("%[^\n]", name);
            getchar(); // consume newline left by scanf

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].name, name) != 0)
                {
                    indices[count++] = i;
                }
            }
            displayContacts(indices, count, addressBook);
            break;
        }
        case 2:
        {
            char phone[20];
            printf("Enter the phone number : ");
            scanf("%[^\n]", phone);
            getchar(); // consume newline left by scanf

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].phone, phone) != 0)
                {
                    indices[count++] = i;
                }
            }
            displayContacts(indices, count, addressBook);
            break;
        }
        case 3:
        {
            char email[50];
            printf("Enter the Email : ");
            scanf("%[^\n]", email);
            getchar(); // consume newline left by scanf

            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].email, email) != 0)
                {
                    indices[count++] = i;
                }
            }
            displayContacts(indices, count, addressBook);
            break;
        }
        case 4:
            printf("Exiting!..\n\n");
            return;
        default:
            printf("Invalid Option!, try again.\n\n");
        }
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
}
