#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria)
{

    if (addressBook->contactCount == 0)
    {
        printf("AddressBook is empty!\n");
        return;
    }

    printf("--------------------------------------------------\n");
    printf("Name              Phone No.        Email ID       \n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d) %s\t %s\t %s\t \n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
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

int validate_name(const char *name) {
    regex_t regex;
    const char *NAME_PATTERN = "^[A-Za-z]+([ .-][A-Za-z]+)*$"; // pattern to handle dots, spaces, and hyphens
    if (regcomp(&regex, NAME_PATTERN, REG_EXTENDED) != 0) {
        return 0; // Regex compilation failed
    }
    int result = regexec(&regex, name, 0, NULL, 0);
    regfree(&regex); // Free regex memory
    return (result == 0); // Return 1 if valid, 0 if invalid
}

int validate_email(const char *email) {
        regex_t regex;
        const char *EMAIL_PATTERN = "^[a-zA-Z0-9_]+[@][a-z]+[\\.][a-zA-Z]{2,3}$";
        if (regcomp(&regex, EMAIL_PATTERN, REG_EXTENDED) != 0) {
                return 0; // Regex compilation failed
        }
        int result = regexec(&regex, email, 0, NULL, 0);
        regfree(&regex); // Free regex memory
        return (result == 0); // Return 1 if valid, 0 if invalid
}

int validate_mobile(const char *mobile) {
        regex_t regex;
        const char *MOBILE_PATTERN = "^[0-9]{10}$";
        if (regcomp(&regex, MOBILE_PATTERN, REG_EXTENDED) != 0) {
                return 0; // Regex compilation failed
        }
        int result = regexec(&regex, mobile, 0, NULL, 0);
        regfree(&regex); // Free regex memory
        return (result == 0); // Return 1 if valid, 0 if invalid

}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("AddressBook is Full!\n");
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
            } else
            {
                printf("Error : Entered name should only contain alphabets!\n");
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
            } else
            {
                printf("Error : Mobile number must be 10 digits only!\n");
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
            } else
            {
                printf("Error : Invalid email format!\n");
            }
        }
        
    }

    addressBook->contactCount++;
    printf("Contact successfully added!\n");
}

void searchContact(AddressBook *addressBook)
{
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
}

void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
}
