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
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    /* Define the logic for print the contacts */
    int i, j;
    for (i = 0; i < addressBook -> contactCount - 1;i++)
    {
        for(j = i + 1;j < addressBook -> contactCount;j++)
        {
            if(strcasecmp(addressBook -> contacts[i].name,addressBook -> contacts[j].name) > 0)
            {
                Contact temp = addressBook -> contacts[i];
                addressBook -> contacts[i] = addressBook -> contacts[j];
                addressBook -> contacts[j] = temp;
            }
        }
    }
    printf("Name\t\tMobilenumber\tEmail address\n");
    for (i = 0; i < addressBook -> contactCount ;i++)
    {
        printf("%s ->",addressBook -> contacts[i].name);
        printf(" %s ->",addressBook -> contacts[i].phone);
        printf(" %s\n",addressBook -> contacts[i].email);
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


int number_valid(char number[12])
{
    int i;
    if (strlen(number)!= 10)// Checking wheathe the number contain 10 digits or not
    {
        printf("Phone number must contain 10 numbers\n");
        return 0;
    } 
    for(i = 0;i < 10;i++)
    {
        if(number[i] < '0' || number[i] > '9')// - Check all 10 characters are digits or not.
        {
            printf("Phone number must contain only digits");
            return 0;
        }
    }

    return 1;

}
//for validate email
int email_valid(const char mail[20])
{
    int len=strlen(mail);
    int i, at_found = 0,dotcom_found = 0,at_index;

     // Check for valid starting character
    if (!((mail[0] >= 'a' && mail[0] <='z') || (mail[0] >='0' && mail[0] <= '9')))
    {
        printf("Email address must start with a lowercase letter or number\n");
        return 0;
    }
    for(i = 0; i < len;i++)
    {
        if (mail[i] >= 'A' && mail[i] <= 'Z') // Check for uppercase
        {
            printf("Email address must not contain uppercase letters\n");
            return 0;
        }
        
    }
    for(i = 0; i < len;i++)
    {
        if(mail[i]=='@')// Count '@' symbols
        {
            at_found++;
            at_index=i;
        }
    }
    for(i = 0; i <= len - 4; i++)
    {
        if ( strncmp(&mail[i], ".com",4) == 0)//end of the email should contain ".com"
        {
            dotcom_found++;
        }
    }
    for (i = at_index + 1; i < len; i++)
    {
        if (!((mail[i] >= 'a' && mail[i] <= 'z') || (mail[i] >= '0' && mail[i] <= '9') || mail[i] == '.' || mail[i] == '-'))
        {
            printf("Invalid character '%c' found in domain part after '@'\n", mail[i]);
            return 0;
        }
    }
    if(at_found != 1) // Only one '@' allowed
    {
        printf("Invalid email: Email address must contain exactly one '@' \n");
        return 0;

    }
    if (dotcom_found !=1 || strcmp(&mail[len - 4], ".com") != 0)// Must end with .com
    {
        printf("Invalid email: must end with .com\n");
        return 0;
    }
      
    return 1;
}
int search_name(AddressBook *addressBook,  char sname[20])
{
    int i;
    int search = 0;
    for (i= 0; i< addressBook -> contactCount ; i++)
    {
        if (strcmp(addressBook->contacts[i].name, sname) == 0)
        {
            printf(" %s", addressBook->contacts[i].name);
            printf(" %s", addressBook->contacts[i].phone);
            printf(" %s\n", addressBook->contacts[i].email);
            search = 1;
        }   
    }
    if(! search)
    {
        printf("Contact not found.\n");
    }
}
int search_phone(AddressBook *addressBook,  char snum[12])
{
     int i;
     int search = 0;
    for (i= 0; i< addressBook -> contactCount ; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, snum) == 0)
        {
            printf(" %s", addressBook->contacts[i].name);
            printf(" %s", addressBook->contacts[i].phone);
            printf(" %s\n", addressBook->contacts[i].email);
            search = 1;
            return i;
        }
    }
    if(!search)
    {
        printf("Contact not found.\n");
        return -1;
    }
    
}
int search_email(AddressBook *addressBook,  char smail[20])
{
    int i;
    int search = 0;
    for (i= 0; i< addressBook -> contactCount ; i++)
    {
        if (strcmp(addressBook->contacts[i].email, smail) == 0)
        {
            printf(" %s", addressBook->contacts[i].name);
            printf(" %s", addressBook->contacts[i].phone);
            printf(" %s\n", addressBook->contacts[i].email);
            search = 1;
            return i;
        }
        
    }
    if(!search)
    {
        printf("Contact not found.\n");
        return -1;
    }
}
void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    // Read the name from the user
    printf("Enter the User name : \n");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
    char number[12];
    // Read the contact
    int res, valid, i;
    do
    {
        printf("Enter the contact number : \n");
        scanf(" %11s", number);

        res = number_valid(number);
        for(i = 0;i < addressBook -> contactCount;i++)
        {
            if(strcmp(addressBook -> contacts[i].phone,number) == 0)    // - Check the given number is already exist or not
            {
                printf("duplicate number is found\n");
                res = 0;
            }
        }

        if(res == 1)
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount].phone,number);
        }
        else
        {
            printf("Please try again\n");
        }

    }
    while(res != 1);     

    char mail[20];
    do
    {
        printf("Enter the email ID : ");//Read the email ID
        scanf("%s",mail);

        valid = email_valid(mail);//Check the email ID is valid or not
        // - Check whether the character array contains lowercase, digits and special characters or not
        for(i = 0;i < addressBook -> contactCount; i++)
    {
        if(strcmp(addressBook -> contacts[i].email,mail) == 0)
        {
            printf("duplicate email is found\n");
            valid = 0;
        }
    }

        if (valid == 1)
        {
            strcpy(addressBook -> contacts[addressBook -> contactCount].email,mail);// If valid, copy the email to the contact
        }
        else
        {
            printf("Please try again");
        }  
    }while(valid != 1);
    addressBook -> contactCount++;// Increment the contact count.  
}

void searchContact(AddressBook *addressBook) 
{
    int option,index;
    do
    {
        printf("\nSearch contanct menu:\n");
        printf("\t1. Search using name \n");
        printf("\t2. Search using number\n ");
        printf("\t3. Search using email ID\n");
        printf("\t4. Main menu\n");
        printf("Enter your option: ");
	    scanf("%d", &option);
        char sname[20];
        char snum[12];
        char smail[20];
        switch(option)
        {
            case 1:
                    printf("Enter search name\n");
                    scanf(" %[^\n]",sname);
                    search_name(addressBook,sname);
                    break;

            case 2:
                    printf("Enter searching number\n");
                    scanf("%s",snum);
                    number_valid(snum);
                    search_phone(addressBook,snum);
                    break;

            case 3:
                    printf("Enter searching email ID\n");
                    scanf("%s",smail);
                    number_valid (smail);
                    search_email(addressBook,smail);
                    break;

            case 4:
                    printf("Return to Main menu\n");
                    break;

            default:
		            printf("Invalid choice. Please try again.\n");
        }   
    }while( option != 4);

}
int search_ename(AddressBook *addressBook,  char sname[20])
{
    int i,count = 1;
    int search = 0;
    int found_index[100]; // Array to store index    of found contacts
    int choice;

    for (i= 0; i< addressBook -> contactCount ; i++)
    {
        if (strcmp(addressBook->contacts[i].name, sname) == 0)
        {
            printf(" %d %s", count, addressBook->contacts[i].name);
            printf(" %s", addressBook->contacts[i].phone);
            printf(" %s\n", addressBook->contacts[i].email);
            search = 1;
            found_index[count - 1] = i; // Store the index of the found contact
            count++;
        }   
    }
    if(! search)
    {
        printf("Contact not found.\n");
        return -1; // Return -1 if no contact is found
    }
    printf("enter the serial number of the contact you want to edit: ");
    scanf("%d",&choice);
    if (choice < 1 || choice >= count)
    {
        printf("Invalid choice. Please try again.\n");
        return 0; // Return -1 for invalid choice
    }
    i = found_index[choice - 1]; // Get the index of the chosen contact
    return i; // Return the index of the contact to be edited
}
int edit_contact_fields(AddressBook *addressBook, int i)
{
 int editoption;
 char uphone[12];
 char uemail[20];
 int res, j;
    printf("Edit contact menu:\n");
    printf("\t1. Edit name\n");
    printf("\t2. Edit phone number\n");
    printf("\t3. Edit email ID\n");
    printf("\t4. Main menu\n");
    printf("Enter your option: ");
    scanf("%d", &editoption);
    do
    {
        switch(editoption)
        {
            case 1:
                printf("Enter new name: ");
                scanf(" %[^\n]", addressBook->contacts[i].name);
                res = 1;
                break;

            case 2:
                {
                    printf("Enter new phone number: ");
                    scanf(" %11s", uphone);
                    res = number_valid(uphone);
                    for(j = 0;j < addressBook -> contactCount;j++)
                    {
                        if(strcmp(addressBook -> contacts[j].phone,uphone) == 0)
                        {
                            printf("duplicate number is found\n");
                            res = 0;
                        }
                    }
                    if(res == 1)
                    {
                        strcpy(addressBook -> contacts[i].phone,uphone);
                    }
                    else
                    {
                        printf("Please try again invalid phone number\n");
                    }
                break;
                }

            case 3:
                {
                    printf("Enter new email ID: ");
                    scanf("%s", uemail);
                    res = email_valid(uemail);
                    for(j = 0;j < addressBook -> contactCount; j++)
                    {
                        if(strcmp(addressBook -> contacts[j].email,uemail) == 0 && j != i)
                        {
                            printf("duplicate email is found\n");
                            res = 0;
                        }
                    }
                    if (res == 1)
                    {
                        strcpy(addressBook -> contacts[i].email,uemail);
                    }
                    else
                    {
                        printf("Please try again");
                    }  
                break;
                }

            case 4:
                printf("Return to Main menu\n");
                return -1; // Return -1 to indicate exit from edit menu

            default:
                printf("Invalid choice. Please try again.\n");
        }
        /* code */
    }while (res != 1);

    //show updated contact details
    printf("Updated contact details:\n");
    printf("Name: %s\n", addressBook->contacts[i].name);
    printf("Phone: %s\n", addressBook->contacts[i].phone);
    printf("Email: %s\n", addressBook->contacts[i].email);
    
}
void editContact(AddressBook *addressBook)
{
    int option, index;
    do
    {
        printf("search contact menu:\n");
        printf("\t1. Search using name \n");
        printf("\t2. Search using number\n ");
        printf("\t3. Search using email ID\n");
        printf("\t4. Main menu\n");
        printf("Enter your option: ");
        scanf("%d", &option);
        char sname[20];
        char snum[12];
        char smail[20];
    if(option == 1)
    {
        printf("Enter search name\n");
        scanf(" %[^\n]", sname);
        index = search_ename(addressBook, sname);
        if(index >= 0)
        {
            edit_contact_fields(addressBook, index);
        }
    }
    else if(option == 2)
    {
        printf("Enter search number\n");
        scanf(" %[^\n]", snum);
        index = search_phone(addressBook, snum);
        if(index >= 0)
        {
            edit_contact_fields(addressBook, index);
        }
    }
    else if(option == 3)
    {
        printf("Enter search email\n");
        scanf(" %[^\n]", smail);
        index = search_email(addressBook, smail);
        if(index >= 0)
        {
            edit_contact_fields(addressBook, index);
        }
    }
    else if(option == 4)
    {
        printf("Return to Main menu\n");
        return; // Exit the edit contact menu
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    } 
    }while (option != 4);
}
int delete(AddressBook *addressBook, int i)
{
    // Shift contacts to the left to remove the contact at index i
    for (int j = i; j < addressBook->contactCount - 1; j++) 
    {
        addressBook->contacts[j] = addressBook->contacts[j + 1];
    }
    addressBook->contactCount--; // Decrease the contact count
    printf("Contact deleted successfully.\n");
    return 0; // Return 0 to indicate successful deletion
}
void deleteContact(AddressBook *addressBook)
{
    int option, index;
    do  
    {
        printf("search contact menu:\n");
        printf("\t1. Search using name \n");
        printf("\t2. Search using number\n ");
        printf("\t3. Search using email ID\n");
        printf("\t4. Main menu\n");
        printf("Enter your option: ");
        scanf("%d", &option);
        char dname[20];
        char dnum[12];
        char dmail[20];
    if(option == 1)
    {               
        printf("Enter search name\n");
        scanf(" %[^\n]", dname);
        index = search_ename(addressBook, dname);
        if(index >= 0)
        {
            delete(addressBook, index);
        }
    }
    else if(option == 2)
    {
        printf("Enter search number\n");
        scanf(" %[^\n]", dnum);
        index = search_phone(addressBook, dnum);
        if(index >= 0)
        {
            delete(addressBook, index);
        }
    }
    else if(option == 3)
    {
        printf("Enter search email\n");
        scanf(" %[^\n]", dmail);
        index = search_email(addressBook, dmail);
        if(index >= 0)
        {
            delete(addressBook, index);
        }
    }
    else if(option == 4)
    {
        printf("Return to Main menu\n");
        return; // Exit the delete contact menu
    }
    else
    {
        printf("Invalid choice. Please try again.\n");
    }
    }while (option != 4);
    /* Define the logic for deletecontact */

}
