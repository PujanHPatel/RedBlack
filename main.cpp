#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct node {//true = Black, false = Red
    int value = 0; 
    bool color = false;
    node * parent = NULL;
    node * left = NULL;
    node * right = NULL;
};

void rotateL(node * head, node * originalHead) {
    node * right = head -> right;
    head -> right = right -> left;
    if(head -> right != NULL) {
        head -> right -> parent = head;
    }
    right -> parent = head -> parent;
    if(head -> parent == NULL) {
        originalHead = right;
    }
    else if(head == head -> parent -> left) {
        head -> parent -> left = right;
    }
    else {
        head -> parent -> right = right;
    }
    right -> left = head;
    head -> parent = right;
}

void rotateR(node * head, node * originalHead) {
    node * left = head -> left;
    head -> left = left -> right;
    if(head -> left != NULL) {
        head -> left -> parent = head;
    }
    left -> parent = head -> parent;
    if(head -> parent == NULL) {
        originalHead = left;
    }
    else if(head == head -> parent -> left) {
        head -> parent -> left = left;
    }
    else {
        head -> parent -> right = left;
    }
    left -> right = head;
    head -> parent = left;
}

node * fix(node * head, node * originalHead) {
    node * parent = NULL;
    node * grandparent = NULL;
    while(head != originalHead && head -> color != true && head -> parent -> color == false) {
        parent = head -> parent;
        grandparent = head -> parent -> parent;
        if(parent == grandparent -> left) {
            node * uncle = grandparent -> right;
            if(uncle != NULL && uncle -> color == false) {
                grandparent -> color = false;
                parent -> color = true;
                uncle -> color = true;
                head = grandparent;
            }
            else {
                if(head == parent -> right) {
                    rotateL(parent, originalHead);
                    head = parent;
                    parent = head -> parent;
                }
                rotateR(grandparent, originalHead);
                swap(parent -> color, grandparent -> color);
                head = parent;
            }
        }
        else { 
            node * uncle = grandparent -> left;
            if(uncle != NULL && uncle -> color == false) {
                grandparent -> color = false;
                parent -> color = true;
                uncle -> color = true;
                head = grandparent;
            }
            else {
                if(head == parent -> left) {
                    rotateR(parent, originalHead);
                    head = parent;
                    parent = head -> parent;
                }
                rotateL(grandparent, originalHead);
                swap(parent -> color, grandparent -> color);
                head = parent;
            }
        }
    }
    originalHead -> color = true;
    return head;
}

node * add(int addValue, node * head, node * originalHead) {
    node * temp = new node;
    temp -> value = addValue;
    if(head == NULL) {
        head = temp;
        head -> color = true;
    }
    else if(addValue <= head -> value && head -> left != NULL) {
        add(addValue, head -> left, originalHead);
    }
    else if(addValue > head -> value && head -> right != NULL) {
        add(addValue, head -> right, originalHead);
    }
    else if(addValue <= head -> value) {
        temp -> parent = head;
        head -> left = temp;
        head = fix(head -> left, originalHead);
    }
    else if(addValue > head -> value) {
        temp -> parent = head;
        head -> right = temp;
        head = fix(head -> right, originalHead);
    }
    return head;
}
void print(node * head, int space) {//print tree visually
    if(head == NULL) {
        return;
    }
    space += 10;
    print(head -> right, space);
    cout << " " << endl;
    for (int i = 10; i < space; i++) {
        cout << " ";
    }
    if(head -> color == true) {
        cout << head -> value << "," << "B" << endl;
    }
    else if(head -> color == false) {
        cout << head -> value << "," << "R" << endl;
    }
    print(head -> left, space);

}

int main() {
    int space = 0;
    char * input = new char[999];
    node * head = NULL;
    bool running = true;
    while(running) {
        cout << "INITIALIZE, PRINT, QUIT" << endl;
        cin >> input;
        if (strcmp("INITIALIZE", input) == 0) {
            cout << "CONSOLE, FILE" << endl;
            cin >> input;
            if(strcmp("CONSOLE", input) == 0) {
                cout << "Please input #" << endl;
                int inputNum;
                cin >> inputNum;
                head = add(inputNum, head, head);
                cout << "ADDED" << endl;
            }
            if(strcmp("FILE", input) == 0) {
                int arrayIndex = 0;
                cout << "Please input name of File" << endl;
                cin >> input;
                int num = 0;
                ifstream numFile (input);
                while(numFile >> num) {
                    head = add(num, head, head);
                }
            }
        }
        else if(strcmp("PRINT", input) == 0) {
            print(head, space);
        }
        else if(strcmp("QUIT", input) == 0) {
            running = false;
        }
    }   
    
    return 0;
}
