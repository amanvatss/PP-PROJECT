#include<iostream>
#include<string>
using namespace std;

class member_node {
    public:
        string member_name;
        long long int phone_no;
        float cost;
        member_node* next;   // Points to the next member

        // Constructor to initialize a member node
        member_node(string name, int ph) {
            member_name = name;
            phone_no = ph;
            cost = 0;
            next = NULL;
        }
};

// Class to hold the collection of functions
class start {
    member_node* head = NULL; // Points to the start of the linked list of members
    public:
        void create_group();
        void display_group();
        void split_expense();
};

// Function to create users for the group
void start::create_group() {
    int yes = 1, i = 1;

    while(yes == 1) {
        // Taking input from user
        string name;
        int ph;
        cout << "Member " << i << " : " << endl;
        cout << "Name: ";
        cin >> name;
        cout << "Phone No.: ";
        cin >> ph;

        // Creating a new node
        member_node* newnode = new member_node(name, ph);

        if (head == NULL) {
            head = newnode; // Initialize head if there are no users
        } else {
            member_node* temp = head; // Temp node pointing to head
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newnode; // Adding new node to the end
        }

        cout << "More members? \nIf yes: 1 \nIf no: 0 \nENTER HERE: ";
        cin >> yes;
        i++;
    }
}

// Function to split the expense among members
void start::split_expense() {
    if (head == NULL) {
        cout << "No members found! Please create a group first." << endl;
        return;
    }

    float total_expense;
    string paid_by;
    
    cout << "Enter total expense: ";
    cin >> total_expense;
    cout << "Who paid the amount? Enter member name: ";
    cin >> paid_by;

    member_node* temp = head;
    int count = 0;

    // Count the total number of members
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    // Calculate the share of each member
    float per_person_share = total_expense / count;

    // Traverse the list of members
    temp = head;
    while (temp != NULL) {
        if (temp->member_name != paid_by) {
            // Subtract the per_person_share for each member who didn't pay
            temp->cost -= per_person_share;
        } else {
            // Add the total expense to the payer
            temp->cost += total_expense;
        }
        temp = temp->next;
    }
}

// Function to display the group and how much each member owes
void start::display_group() {
    if (head == NULL) {
        cout << "No members found! Please create a group first." << endl;
        return;
    }

    member_node* temp = head;

    cout << "Current Group Expenses: " << endl;
    while (temp != NULL) {
        cout << temp->member_name << " owes: " << (temp->cost < 0 ? -temp->cost : 0) << endl;
        temp = temp->next;
    }
}

// Main function with switch case for menu-driven approach
int main() {
    start A;
    int choice;

    do {
        // Menu options
        cout << "\n---- Expense Sharing Menu ----" << endl;
        cout << "1. Create Group" << endl;
        cout << "2. Split Expense" << endl;
        cout << "3. Display Group" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                A.create_group();
                break;
            case 2:
                A.split_expense();
                break;
            case 3:
                A.display_group();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
