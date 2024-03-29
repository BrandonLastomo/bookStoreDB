#include <iostream>
using namespace std;

const int maxCategory = 10;
int amountOfCategory = 3;
string categoriesList[maxCategory] = {"Fiction", "Horror", "Science"};

struct Book {
    string ID, title, author;
    int categoryIndex, page;
    double price;
};

struct Node {
    Book BookData;
    Node *prev, *next;
} *head = NULL, *newNode = NULL, *temp;

// function for adding new category if user wants to
void addCategory(){
    char isAdd;
    cout << "Do you want to add new category? (y/n)\n> ";
    cin >> isAdd;
    if (isAdd == 'y'){
        cout << "Insert new category's name\n> ";
        cin.ignore();
        getline(cin, categoriesList[amountOfCategory]);
        if (amountOfCategory == maxCategory){
            cout << "Sorry, the categories list is full";
        } else {
            cout << "A new category has been added.\n\n";
            amountOfCategory++;
        }
    }
}
// endof addCategory function

void displayCategories(){
    cout << "Avalaible categories are:\n";
    for (int i = 0; i < amountOfCategory; i++){
        cout << i+1 << ". " << categoriesList[i] << endl;
    }
}

// function to check if the ID is double or not
void insertID(Node *Book){
    temp = new Node;
    temp = head;
    string doubleID;

    cin >> Book->BookData.ID;
    while (temp != NULL){
        if (Book->BookData.ID == temp->BookData.ID && Book != temp){
            doubleID = temp->BookData.ID;
            while (Book->BookData.ID == doubleID){
                cout << "The ID has been taken. Please insert another ID\n> ";
                cin >> Book->BookData.ID;
            }
            break;
        }
        temp = temp->next;
    }
}
// endof function to check ID

// function for adding datas of the new book and automatically insert it alphabetically based on book's title
void addBookAlphabetically(){
    newNode = new Node;
    newNode->prev = NULL;
    newNode->next = NULL;

    // inserting book's datas
    cout << "Insert the book's ID\n> ";
    insertID(newNode);
    cout << "Insert the book's title\n> ";
    cin.ignore();
    getline(cin, newNode->BookData.title);
    cout << "Insert the book's author\n> ";
    getline(cin, newNode->BookData.author);
    cout << "Choose the book's category (number)\n";
    displayCategories();
    addCategory();
    displayCategories();
    cout << "> ";
    cin >> newNode->BookData.categoryIndex;
    cout << "Insert how much pages does the book contain\n> ";
    cin >> newNode->BookData.page;
    cout << "Insert the book's price (IDR)\n> ";
    cin >> newNode->BookData.price;
    // endof insert datas

    if (head == NULL){
        head = newNode;
    } else {
        temp = new Node;
        temp = head;
        // insert alphabetically based on book's title
        while (temp != NULL){
            if (newNode->BookData.title[0] < temp->BookData.title[0]){
                if (temp->prev == NULL){
                    newNode->next = temp;
                    newNode->prev = NULL;
                    temp->prev = newNode;
                } else if (temp->next != NULL && temp->prev != NULL){
                    newNode->prev = temp->prev;
                    temp->prev->next = newNode;
                    newNode->next = temp;
                    temp->prev = newNode;
                }
            } else if (newNode->BookData.title[0] > temp->BookData.title[0]){
                if (temp->next == NULL){
                    newNode->next = NULL;
                    newNode->prev = temp;
                    temp->next = newNode;
                } else if (temp->next != NULL && temp->prev != NULL){
                    newNode->next = temp->next;
                    temp->next->prev = newNode;
                    newNode->prev = temp;
                    temp->next = newNode;
                }
            }
            temp = temp->next;
        }
        // endof insert alphabetically

        // place head on the first node
        if (head->prev != NULL){
            while (head->prev != NULL){
                head = head->prev;
            }
        }
        // endof head placement
    }
    cout << "The book has been added.\n\n";
}
// endof adding book datas function

void displayBookData(Node *book){
    cout << "\nID\t\t: " << book->BookData.ID << endl;
    cout << "Title\t\t: " << book->BookData.title << endl;
    cout << "Author\t\t: " << book->BookData.author << endl;
    cout << "Category\t: " << categoriesList[book->BookData.categoryIndex-1] << endl;
    cout << "Pages\t\t: " << book->BookData.page << endl;
    cout << "Price (IDR)\t: " << book->BookData.price << endl << endl;
}

void displayAllBooks(){
    if (head == NULL){
        cout << "\nThe shelf is empty. Please add some books first.\n\n";
        return;
    }

    cout << "\n===Books on the Shelf===" << endl;

    temp = new Node;
    temp = head;
    while (temp != NULL){
        displayBookData(temp);
        temp = temp->next;
    }
}

void editBook(){
    if (head == NULL){
        cout << "\nThe shelf is empty. Please add some books first.\n\n";
        return;
    }

    string findID;
    int option;
    temp = new Node;
    temp = head;

    cout << "Insert book's ID\n> ";
    cin >> findID;

    while (findID != temp->BookData.ID && temp->next != NULL){
        temp = temp->next;
    }

    while (findID != temp->BookData.ID && temp->next == NULL){
        cout << "The ID isn't found. Please reinsert the ID\n> ";
        cin >> findID;
    }

    cout << "Datas of the book that you searched for are: \n";
    displayBookData(temp);

    cout << "\nWhich property do you want to edit?\n";
    cout << "1. Title\n";
    cout << "2. Author's name\n";
    cout << "3. Category\n";
    cout << "4. Amount of page\n";
    cout << "5. Price\n> ";
    cin >> option;

    switch (option){
    case 1:
        cout << "Insert the book's new title\n> ";
        cin.ignore();
        getline(cin, temp->BookData.title);
        cout << "The property has been edited.\n\n";
        break;

    case 2:
        cout << "Insert author's name\n> ";
        cin.ignore();
        getline(cin, temp->BookData.author);
        cout << "The property has been edited.\n\n";
        break;

    case 3:
        cout << "Choose the book's category (number)\n";
        displayCategories();
        cout << "> ";
        cin >> temp->BookData.categoryIndex;
        cout << "The property has been edited.\n\n";
        break;

    case 4:
        cout << "Insert how much pages does the book contain\n> ";
        cin >> temp->BookData.page;
        cout << "The property has been edited.\n\n";
        break;

    case 5:
        cout << "Insert the book's price (IDR)\n> ";
        cin >> temp->BookData.price;
        cout << "The property has been edited.\n\n";
        break;

    default:
        cout << "Your choice of menu is invalid.\n\n";
        break;
    }
}

void deleteBook(){
    if (head == NULL){
        cout << "\nThe shelf is empty. Please add some books first.\n\n";
        return;
    }

    string findID;
    temp = new Node;
    temp = head;

    cout << "Insert book's ID\n> ";
    cin >> findID;

    while (findID != temp->BookData.ID && temp->next != NULL){
        temp = temp->next;
        if (findID != temp->BookData.ID && temp->next == NULL){
            cout << "The ID isn't found. Please reinsert the ID\n> ";
            cin >> findID;
            temp = head;
        }
    }

    if (temp->prev == NULL){
        if (temp->next != NULL){
            head = head->next;
            head->prev = NULL;
        } else {
            head = NULL;
        }
        free(temp);
    } else if (temp->next == NULL){
        temp->prev->next = NULL;
        free(temp);
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        free(temp);
    }

    cout << "the book has been deleted\n\n";
}

// free memory from node(s)
void deAlloc(){
    free(head);
    free(newNode);
    free(temp);
}
// endof free memory function

int main(){

    int option;

    do {
        cout << "===Paulownia Bookstore===\n";
        cout << "1. Add new book.\n";
        cout << "2. Display all books.\n";
        cout << "3. Edit a book.\n";
        cout << "4. Delete a book.\n";
        cout << "5. Exit.\n> ";
        cin >> option;

        switch (option){
        case 1:
            system("cls");
            addBookAlphabetically();
            break;

        case 2:
            system("cls");
            displayAllBooks();
            break;

        case 3:
            system("cls");
            editBook();
            break;

        case 4:
            system("cls");
            deleteBook();
            break;

        case 5:
            system("cls");
            cout << "Thank you!";
            deAlloc();
            break;

        default:
            cout << "Your choice of menu is invalid.";
            break;
        }
    } while (option != 5);

    return 0;
}
