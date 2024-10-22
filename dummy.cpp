#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class member_node
{
public:
    // Data Members: Name, Phone_no, Cost
    string member_name;
    string phone_no;
    float cost;
    member_node *next; // node for users
    member_node *owes; // node for storing cost to be given to other user

    member_node(string name, string ph)
    { // constructor to initializing default setting of a node
        member_name = name;
        phone_no = ph;
        cost = 0;
        next = NULL;
        owes = NULL;
    }
};

bool isValidPhoneNumber(string phoneNumber)
{
    int length = phoneNumber.length();
    int digitCount = 0;

    // Use traditional for loop instead of range-based for loop
    for (int i = 0; i < length; ++i)
    {
        char c = phoneNumber[i];
        if (isdigit(c))
        {
            ++digitCount;
        }
        else if (c != '+' && c != '-' && c != ' ')
        {
            return false; // Invalid character found
        }
    }

    // Check if the phone number has exactly 10 digits (excluding symbols)
    return (digitCount == 10);
}

// class for all collection of functions
class group
{
protected:
    member_node *head = NULL;
    member_node *temp = NULL;

public:
    void create_group();
    void display_group();
    int total_Members();
};

// Function to create users of one group only
void group::create_group()
{
    int yes = 1, i = 1; // 'yes' for checking if we have more nodes to add and 'i' is total number of user

    cout << "\n-----------------------------\n";
    cout << "    CREATE A NEW GROUP   \n";
    cout << "-----------------------------\n";

    while (yes == 1)
    {
        // Taking input from user
        string name;
        string ph;
        cout << "\nMember " << i << " : " << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Phone No.: ";
        cin >> ph;
        while (!isValidPhoneNumber(ph))
        {
            cout << "Enter 10 digit phone number.\n";
            cout << "Phone No.: ";
            cin >> ph;
        }

        // creating a new node
        member_node *newnode = new member_node(name, ph);

        if (head == NULL)
        {
            head = newnode; // If their is no user then newnode is directly initialized to head
        }
        else
        {
            temp = head; // temp node pointing to head
            while (temp->next != NULL)
            { // loop to reach at last node (temp will point to last node)
                temp = temp->next;
            }
            temp->next = newnode; // Adding newnode(user) to last node
        }
        cout << "\nAdd more members? \n1: Yes\n0: No\nENTER HERE: ";
        cin >> yes;
        i++; // Addition of users till yes becomes zero
    }

    member_node *temp = head; // here temp for iterating user
    member_node *j = head;    // j to point the current node in which we need to add owes
    while (--i)
    {
        member_node *temp_owes = j; // temp_owes to iterate over owes
        while (temp != NULL)
        {
            if (j->member_name != temp->member_name)
            {
                string n = j->member_name + " owes to " + temp->member_name; // string in form "A owes to B"
                member_node *newowes = new member_node(n, temp->phone_no);   // make newnode with the name as the above string
                temp_owes->owes = newowes;                                   // Add newnode to current temp_owes
                temp_owes = temp_owes->owes;                                 // temp_owes points to last node
                temp = temp->next;                                           // goes to next user(this node "temp" is needed because we want to add name of member in string "n")
            }
            else
            {
                temp = temp->next; // "A owes to A" does make sense so when "same_name owes to same_name" then we are ignoring it
            }
        }
        temp = head; // Pointing temp to head so in next iteration it will give us all user again
        j = j->next; // j will go to next user and all the owes for next user will be added further
    }

    cout << "\n\nGroup successfully created!\n";
}

void group::display_group()
{
    cout << "\n-----------------------------------" << endl;
    cout << setw(20) << "GROUP EXPENSES SUMMARY" << endl;
    cout << "-----------------------------------" << endl;

    member_node *temp = head;

    while (temp != NULL)
    {
        member_node *temp_owes = temp->owes;

        while (temp_owes != NULL)
        {
            cout << left << setw(25) << temp_owes->member_name << "= " << fixed << setprecision(2) << temp_owes->cost << endl;
            temp_owes = temp_owes->owes;
        }
        temp = temp->next;
    }

    cout << "-----------------------------------\n"
         << endl;
}

int group::total_Members()
{
    int count = 1;
    member_node *temp = head;
    while (temp->next != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

class category_node
{
public:
    string category;
    float amt;
    category_node *next;

    category_node(string name, float amount)
    {
        category = name;
        amt = amount;
        next = NULL;
    }
};

class manageExpenses : public group
{
public:
    string who_paid;
    float amount;
    int flag;
    string categoryName;
    category_node *first = NULL; // Node for storing categories

    void getdata()
    {
        cout << "\nWho paid the amount? : ";
        cin >> who_paid;
        cout << "How much was the transaction? : ";
        cin >> amount;
        cout << "What was the expense for (e.g., movie, grocery, etc.)? : ";
        cin >> categoryName;

        flag = 0;
        category_node *t = first;
        category_node *newnode = new category_node(categoryName, amount);
        if (first == NULL)
        {
            first = newnode;
            cout << "Inside first" << endl;
        }
        else
        {

            while (t != NULL)
            {
                cout << t->category << " : " << categoryName << endl;
                if (t->category == categoryName)
                {
                    t->amt += amount;
                    flag = 1;
                    cout << "1" << endl;
                    break;
                }
                t = t->next;
            }
            if (flag != 1)
            {
                t = first;
                while (t->next != NULL)
                {
                    t = t->next;
                }
                t->next = newnode;
                cout << "Done" << endl;
            }
        }
        cout << "OK" << endl;
    }
    void split(string who_paid, float amount, string m1);
    void split(string who_paid, float amount);
};

void manageExpenses::split(string who_paid, float amount, string m1)
{
    member_node *temp = head;
    while (temp != NULL)
    {
        if (temp->member_name != who_paid)
        {
            member_node *temp_owes = temp; // goes to owes node for the given user node which here we named as "temp"
            cout<<temp_owes->member_name<<endl;
            while (temp_owes != NULL)
            {
                string n = m1 + " owes to " + who_paid;
                if (temp_owes->member_name == n)
                {
                    temp_owes->cost += amount;
                }
                temp_owes = temp_owes->owes;
            }
        }
        temp = temp->next;
    }
    cout<<"Expense Added"<<endl;
}

void manageExpenses::split(string who_paid, float amount)
{
    member_node *temp = head;
    int member_count = total_Members();
    float divideEqually = amount / member_count;

    while (temp != NULL)
    {
        if (temp->member_name != who_paid)
        {
            member_node *temp_owes = temp; // goes to owes node for the given user node which here we named as "temp"
            while (temp_owes != NULL)
            {
                string n = temp->member_name + " owes to " + who_paid;
                if (temp_owes->member_name == n)
                {
                    temp_owes->cost += divideEqually;
                }
                temp_owes = temp_owes->owes;
            }
        }
        temp = temp->next;
    }

    cout<<"Expense Added"<<endl;
}

class analysis : public manageExpenses
{
public:
    float group_Expenditure();
    void categorical_Cost();
};

float analysis::group_Expenditure()
{
    category_node *temp = first;
    float total = 0;
    while (temp != NULL)
    {
        total += temp->amt;
        temp = temp->next;
    }
    return total;
}

void analysis::categorical_Cost()
{
    category_node *temp = first;
    float t = group_Expenditure();
    cout << setw(20) << "Categories" << setw(20) << "Cost Spend" << setw(20) << "Percentage" << endl;
    while (temp != NULL)
    {
        cout << setw(20) << temp->category << setw(20) << temp->amt << setw(20) << (temp->amt * 100) / t << endl;
        temp = temp->next;
    }
}

int main()
{
    analysis A;
    int operation = 100;

    while (operation)
    {
        cout << "\n\n-----------------------------------\n";
        cout << setw(25) << "EXPENSE EASE" << endl;
        cout << setw(27) << "Your expense tracker" << endl;
        cout << "------------------------------------\n";

        cout << "Enter the operation you want to perform\n";
        cout << "1. Create Group" << endl;
        cout << "2. Display Group" << endl;
        cout << "3. Add Expense" << endl;
        cout << "\nAnalysis\n" << endl;
        cout << "4. Display Groups Expenditure till now" << endl;
        cout << "5. Categorical Analysis" << endl;
        cout << "EXIT = 0" << endl;
        cout << "Enter the number given in front of the operation: ";
        cin >> operation;
        
        switch (operation)
        {
        case 0:
            cout << "PROGRAM ENDED" << endl;
            break;
        case 1:
            A.create_group();
            break;
        case 2:
            A.display_group();
            break;
        case 3:
        {
            A.getdata(); // Gather who_paid and amount inside the object
            int choice;
            cout << "\nDo you want to split equally or unequally?" << endl;
            cout << "1. Equally" << endl;
            cout << "2. Unequally (between two members)" << endl;
            cout << "Enter choice: ";
            cin >> choice;
            while(choice < 1 && choice > 2){
                cout << "Invalid choice. Try entering choice again" << endl;
                cin >> choice;
            }
            if (choice == 1)
            {
                A.split(A.who_paid, A.amount); // Pass the member variables as arguments
            }
            else if (choice == 2)
            {
                string member_name;
                cout << "Enter the member who owes: ";
                cin >> member_name;
                A.split(A.who_paid, A.amount, member_name); // Pass the member variables and the specific member name
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
            break;
        }
        case 4:
            cout << A.group_Expenditure() << endl;
            break;
        case 5:
            A.categorical_Cost();
            cout << endl;
            break;
        case 6:
            cout << "\nPROGRAM ENDED" << endl;
            break;
        default:
            cout << "\nInvalid operation. Please try again." << endl;
            break;
        }
    }

    return 0;
}
