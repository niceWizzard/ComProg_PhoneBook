#include <iostream>
#include <vector>
#include <algorithm>
#include "./src/utils.h"
#include "./src/contact.h"
#include "./src/file_save.h"

using namespace std;

void HomePage();
void ViewAllContactsPage();
void DeleteContactPage();
void AddContactPage();
void FindContactPage();
void DeleteAllPage();

vector<Contact> allContacts;

int main()
{

    allContacts = RetrieveData();
    HomePage();
    SaveToFile(allContacts);
    cout << endl
         << endl
         << "Good Bye!" << endl
         << endl;
    return 0;
}

void HomePage()
{
    int a = InteractiveInput(
        "PhoneBook \n \nWhat would you like to do?",
        {"View All Contacts", "Find contact", "Add Contact", "Delete Contact", "Delete All", "Quit"});
    switch (a)
    {
    case 0:
        ViewAllContactsPage();
        break;
    case 1:
        FindContactPage();
        break;
    case 2:
        AddContactPage();
        break;
    case 3:
        DeleteContactPage();
        break;
    case 4:
        DeleteAllPage();
    }
}
void DeleteAllPage()
{
    ClearScreen();
    cout << "Delete all?" << endl
         << endl;
    if (allContacts.size() > 0)
    {
        int res = InteractiveInput("Are you sure you want to delete everything?", {"No", "Yes"});
        cout << endl
             << endl;
        if (res == 1)
        {
            allContacts.clear();
            acout("Deletion succesfull!");
        }
        else
        {
            acout("Deletion aborted.");
        }
    }
    else
    {
        acout("No contacts to delete!");
    }
    Pause();
    HomePage();
}

void ViewAllContactsPage()
{
    ClearScreen();
    cout << "All contacts list" << endl
         << endl;
    if (allContacts.size() == 0)
    {
        acout("No contacts to show :( \n");
    }
    sort(allContacts.begin(), allContacts.end(), ContactCompare);
    int index = 0;
    for (Contact h : allContacts)
    {
        cout << index + 1 << ".) ";
        cout << h.GetDisplayText() << endl;
        index++;
        Sleep(70);
    }

    Pause();
    HomePage();
}

void AddContactPage()
{
    ClearScreen();
    cout << "Create a new contact\n\n";
    Contact newContact;
    GetLine("Enter name: ", newContact.name);
    GetLine("Enter Number: ", newContact.number, IsNotValidPhoneNumber);
    GetLine("Enter Address: ", newContact.address);
    cout << endl;

    bool isUsed = false;
    for (Contact c : allContacts)
    {
        if (c.number == newContact.number)
        {
            acout("Contact number is already in used.");
            isUsed = true;
            break;
        }
    }
    if (!isUsed)
    {
        newContact.TrimMembers();
        allContacts.push_back(newContact);
        cout << "Added sucessfully!";
    }

    Pause();
    HomePage();
}

void FindContactPage()
{
    ClearScreen();
    cout << "Find a contact\n\n";
    string name = "";
    vector<Contact> contactsFound;

    GetLine("Enter name: ", name);
    cout << endl;
    for (Contact c : allContacts)
    {
        if (IsEqual(c.name, name))
        {
            contactsFound.push_back(c);
        }
    }

    if (contactsFound.size() > 0)
    {
        cout << "Here are the contacts with the name: " << endl
             << endl;
        for (Contact c : contactsFound)
        {
            cout << c.GetDisplayText() << endl;
        }
    }
    else
    {
        acout("No contact found with the name. :(");
    }
    Sleep(300);
    Pause();
    HomePage();
}

void DeleteContactPage()
{
    ClearScreen();
    cout << "Delete a contact\n\n";
    string name = "";
    vector<Contact> contactsFound;
    vector<int> indexes;
    int index = 0;
    GetLine("Enter name: ", name);
    for (Contact c : allContacts)
    {
        if (IsEqual(c.name, name))
        {
            contactsFound.push_back(c);
            indexes.push_back(index);
        }
        index++;
    }

    if (contactsFound.size() > 0)
    {
        if (contactsFound.size() == 1)
        {
            Contact n = contactsFound[0];
            cout << n.GetDisplayText();
            int res = InteractiveInput(
                "Are you sure you want to delete \n\n" + n.GetDisplayText(),
                {"Back", "Delete"});
            if (res == 1)
            {
                allContacts.erase(allContacts.begin() + indexes[0]);
                cout << endl;
                acout("Contact deleted!");
            }
        }
        else
        {
            vector<string> choices = {"Back"};
            for (Contact c : contactsFound)
            {
                choices.push_back(c.GetDisplayText());
            }

            int res = InteractiveInput("Select contact to delete: ", choices);
            switch (res)
            {
            case 0:
                break;
            default:
                Contact n = contactsFound[res - 1];
                cout << n.GetDisplayText();
                int res1 = InteractiveInput(
                    "Are you sure you want to delete \n\n" + n.GetDisplayText(),
                    {"Back", "Delete"});
                if (res1 == 1)
                {
                    allContacts.erase(allContacts.begin() + indexes[res - 1]);
                    cout << endl;
                    acout("Contact deleted!");
                }
                break;
            }
        }
    }
    else
    {
        acout("No contact found with the name. :(");
    }

    Pause();
    HomePage();
}
