#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria

    if (addressBook->contactCount == 0)
    {
        printf("AddressBook is empty!\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%d. Name : %s\t Phone : %s\t Email : %s\n", i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("AddressBook is Full!\n");
        return;
    }
    

    Contact new_contact;
    printf("Enter the name of contact : ");
    scanf(" %[^\n]", new_contact.name);
    printf("Enter the contact number : ");
    scanf(" %[^\n]", new_contact.phone);
    printf("Enter the email ID : ");
    scanf(" %[^\n]", new_contact.email);

    addressBook->contacts[addressBook->contactCount] = new_contact;
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
