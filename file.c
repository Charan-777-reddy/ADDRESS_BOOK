// Name        : Charan Reddy R
// Date        : 04/07/2025
// Sample Input:
//   Name: John Doe
//   Phone: 9876543210
//   Email: john@gmail.com
//
// Sample Output:
//   Contact saved successfully!
//   Total Contacts: 1
//
// Description:
//   A simple Address Book program in C to store and manage contacts.
//   It allows users to create new contacts by entering name, phone number, and email.
//   The program validates phone number (must be 10 digits, numeric, and unique) and email
//   (must be lowercase, contain exactly one '@', end with '.com', and not be duplicate).
#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
   
    FILE *fp = fopen("contacts.csv", "w");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp,"#%d\n",addressBook -> contactCount);
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fp, "%s,%s,%s\n", 
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);        
    }

    fclose(fp);
    printf("Contacts saved to file successfully.\n"); 
}
void loadContactsFromFile(AddressBook *addressBook) 
{
   FILE *fp = fopen("contacts.csv","r");
    if (fp == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }

   fscanf(fp,"#%d\n",&addressBook -> contactCount);

    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n", 
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
            
    }
    fclose(fp);
    printf("Contacts loaded successfully.\n");
}