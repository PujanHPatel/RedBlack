#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct node {
    int value = 0;
    bool color = true;
    node * parent = NULL;
    node * left = NULL;
    node * right = NULL;
};
node * traverse(node * head, int key);
void print(node * head, int space);
void insert(node *& root, int key);
void rotateL(node *& root, node *& current);
void rotateR(node *& root, node *& current);
void fixInsertion(node *& root, node * current);
bool search(node * head, int key);
node * findNode(node * head, int key);
void deleteNode(node *& root, int key);
node * sibling(node * x);
void replace(node *& p, node * c);
void caseZero(node *& root, node * x);
void caseOne(node *& root, node * x);
void caseTwo(node *& root, node * x);
void caseThree(node *& root, node * x);
void caseFour(node *& root, node * x);
void caseFive(node *& root, node * x);

int main() {
    node * root = NULL;
    int space = 5;
    char * input = new char[999];
    bool running = true;
    while(running) {
        cout << "INITIALIZE, PRINT, SEARCH, DELETE, QUIT" << endl;
        cin >> input;
        if (strcmp("INITIALIZE", input) == 0) {
            cout << "CONSOLE, FILE" << endl;
            cin >> input;
            if(strcmp("CONSOLE", input) == 0) {
                cout << "please input #" << endl;
                int inputNum;
                cin >> inputNum;
                insert(root, inputNum);
                cout << "ADDED" << endl;
            }
            if(strcmp("FILE", input) == 0) {
                int arrayIndex = 0;
                cout << "Please input name of File" << endl;
                cin >> input;
                int num = 0;
                ifstream numFile (input);
                while(numFile >> num) {
                    insert(root, num);
                }
            }
        }
        else if(strcmp("PRINT", input) == 0) {
            print(root, space);
        }
        else if(strcmp("DELETE", input) == 0) {
            int valueFind;
            cout << "Please input # to delete" << endl;
            cin >> valueFind;
            deleteNode(root, valueFind);
        }
        else if(strcmp("SEARCH", input) == 0) {
            int valueFind;
            cout << "Please input # to delete" << endl;
            cin >> valueFind;
            if(search(root, valueFind) == true) {
                cout << "Node Value Exists In Tree" << endl;
            }
            else {
                cout << "Node Value Exists In Tree" << endl;
            };
        }
        else if(strcmp("QUIT", input) == 0) {
            running = false;
        }
    }   
    
    return 0;
}

void print(node * head, int space) {
    
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

node * traverse(node * head, int key) {
    if(key > head -> value && head -> right != NULL) {
        return traverse(head -> right, key);
    }
    else if(key < head -> value && head -> left != NULL) {
        return traverse(head -> left, key);
    }
    return head;
}

void insert(node *& root, int key) {
    node * temp = new node;
    temp -> value = key;
    temp -> color = false;
    if(root != NULL) {
        node * current = traverse(root, key); 
        temp -> parent = current;
        if(current -> value > key) {
            current -> left = temp;
            fixInsertion(root, current -> left);
        }
        else {
            current -> right = temp;
            fixInsertion(root, current -> right);
        }
    }
    else {
        root = temp;
        root -> color = true;
    }
}

void rotateL(node *& root, node *& current) {
     node * pRight = current -> right;
    current -> right = pRight -> left;
    if(current -> right != NULL) {
        current -> right -> parent = current;
    }
    pRight -> parent = current -> parent;
    if(current -> parent == NULL) {
        root = pRight;
    }
    else if(current == current -> parent -> left) {
        current -> parent -> left = pRight;
    }
    else {
        current -> parent -> right = pRight;
    }
    pRight -> left = current;
    current -> parent = pRight;
}

void rotateR(node *& root, node *& current) {
    node * pLeft = current -> left;
    current -> left = pLeft -> right;
    if(current -> left != NULL) {
        current -> left -> parent = current;
    }
    pLeft -> parent = current -> parent;
    if(current -> parent == NULL) {
        root = pLeft;
    }
    else if(current == current -> parent -> left) {
        current -> parent -> left = pLeft;
    }
    else {
        current -> parent -> right = pLeft;
    }
    pLeft -> right = current;
    current -> parent = pLeft;
}

void fixInsertion(node *& root, node * current) {
    node * p = NULL;
    node * g = NULL;
    node * u = NULL;
    while(current != root && current -> color != true && current -> parent -> color == false) {
        p = current -> parent;
        g = current -> parent -> parent;
        if(p == g -> left) {
            u = g -> right;
            if(u != NULL && u -> color == false) {
                g -> color = false;
                p -> color = true;
                u -> color = true;
                current = g;
            }
            else {
                if(current == p -> right) {
                    rotateL(root, p);
                    current = p;
                    p = current -> parent;
                }
                rotateR(root, g);
                swap(p -> color, g -> color);
                current = p;
            }
        }
        else {
            u = g -> left;
            if((u != NULL) && (u -> color == false)) {
                g -> color = false;
                p -> color = true;
                u -> color = true;
                current = g;
            }
            else {
                if(current == p -> left) {
                    rotateR(root, p);
                    current = p;
                    p = current -> parent;
                }
                rotateL(root, g);
                swap(p -> color, g -> color);
                current = p;
            }
        }
    }
    root -> color = true;
}

bool search(node * head, int key) {
    if(head == NULL) {
        return false;
    }
    else if(key > head -> value && head -> right != NULL) {
        return search(head -> right, key);
    }
    else if(key < head -> value && head -> left != NULL) {
        return search(head -> left, key);
    }
    else if(key == head -> value) {
        return true;
    }
    else {
        return false;
    }


}

node * findNode(node * head, int key) {
    if(key > head -> value && head -> right != NULL) {
        return findNode(head -> right, key);
    }
    else if(key < head -> value && head -> left != NULL) {
        return findNode(head -> left, key);
    }
    else if(key == head -> value) {
        return head;
    }
}

void deleteNode(node *& root, int key) {
    if (search(root, key) == false) {
        cout << "Node Value Does Not Exist" << endl;
        return; 
    }
    node* deleteN = findNode(root, key);

    if (deleteN == NULL) {
        return; 
    }

    if (deleteN -> left != NULL && deleteN -> right != NULL) {
        node* successor = deleteN -> right;
        while (successor -> left != NULL) {
            successor = successor -> left; 
        }
        deleteN -> value = successor -> value;
        deleteN = successor; 
    }
    if (deleteN -> color == false) {
        if(deleteN -> parent != NULL) {
            if (deleteN -> parent -> left == deleteN) {
	            deleteN -> parent -> left = NULL;
            }
            else {
                deleteN -> parent -> right = NULL; 
            }
        }
        else {

        }
    }
    else if (deleteN -> left != NULL) {
        deleteN -> left -> color = true;
        replace(deleteN, deleteN -> left);  
    }
    else if (deleteN -> right != NULL) {
        deleteN -> right -> color = true;
        replace(deleteN, deleteN -> right); 
    }
    else {
        if (root == deleteN) {
	        root = NULL; 
        }
        else {
	        caseZero(root, deleteN); 
	        if (deleteN -> parent -> left == deleteN) {
	            deleteN -> parent -> left = NULL; 
	        }
	        else {
            deleteN -> parent -> right = NULL; 
	        }
        }
    }
    return; 
}

node * sibling(node * x) {
    if(x == x -> parent -> right) {
        return x -> parent -> left;
    }
    else {
        return x -> parent -> right;
    }
}

void caseZero(node *& root, node * x) {
    if(x -> parent != NULL) {
        caseOne(root, x); 
    }
}

void caseOne(node *& root, node * x) {
    node * sib = sibling(x);
    if (sib -> color == false) {
        x -> parent -> color = false;
        sib -> color = true;
        if (x == x -> parent -> left) {
            rotateL(root, x -> parent); 
        }
        else {
            rotateR(root, x -> parent); 
        }
    }
    caseTwo(root, x); 
}

void caseTwo(node *& root, node * x) {
    node * sib = sibling(x);
    if ((x -> parent -> color == true) && (sib -> color == true) && (sib -> left == NULL || sib -> left -> color == true) && (sib -> right == NULL || sib -> right -> color == true)) {
        sib -> color = false;
        caseZero(root, x -> parent); 
    }
    else {
        caseThree(root, x); 
    }
}

void caseThree(node *& root, node * x) {
    node* sib = sibling(x);
    if ((x -> parent -> color == false) && (sib -> color == true) && (sib -> left == NULL || sib -> left -> color == true) && (sib -> right == NULL || sib -> right -> color == true)) {
        sib -> color = false;
        x -> parent -> color = true; 
    }
    else {
        caseFour(root, x); 
    }
}

void caseFour(node *& root, node * x) {
    node* sib = sibling(x);
    if (sib -> color == true) {
        if ((x == x -> parent -> left) && (sib -> right == NULL || sib -> right -> color == true) && (sib -> left != NULL && sib -> left -> color == false)) {
            sib -> color = false;
            sib -> left -> color = true;
            rotateR(root, sib); 
        }
        else if ((x == x -> parent -> right) && (sib -> left == NULL || sib -> left -> color == true) && (sib -> right != NULL && sib -> right -> color == true)) {
            sib -> color = false;
            sib -> right -> color = true;
            rotateL(root, sib); 
        }
    }
    caseFive(root, sib);
}

void caseFive(node *& root, node * x) {
    node* sib = sibling(x);   
    sib -> color = x -> parent -> color;
    x -> parent -> color = true;
    if (x == x -> parent -> left) {
        sib -> right -> color = true;
        rotateL(root, x -> parent); 
    }
    else {
        sib -> right -> color = true;
        rotateL(root, x -> parent); 
    }
}

void replace(node *& p, node * c) {
    if(p -> parent != NULL) {
        c -> parent = p -> parent;
        if(p == p -> parent -> left) {
            p -> parent -> left = c;
        }
        else {
            p -> parent -> right = c;
        }
    }
    else {
        p -> value = c -> value;
        p -> left = c -> left;
        p -> right = c -> right;
    }
} 