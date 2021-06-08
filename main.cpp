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
node * getSibling(node * Node) {
    node * sibling = Node -> parent;
    if(sibling == NULL) {
        return NULL;
    }
    else if(Node == sibling -> left) {
        sibling = sibling -> right;
        return sibling;
    }
    else if(Node == sibling -> right) {
        sibling = sibling -> left;
        return sibling;
    }
    return NULL;
}   
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
void caseFive(node *& head, node * Node) {
    node * sibling = getSibling(Node);
    sibling -> color = Node -> parent -> color;
    Node -> parent -> color = true;
    if(Node == Node -> parent -> left) {
        sibling -> right -> color = true;
        rotateL(Node -> parent, head);
    }
    else {
        sibling -> right -> color = true;
        rotateL(Node -> parent, head);
    }
}
void caseFour(node *& head, node * Node) {
    node * sibling = getSibling(Node);
    if(sibling -> color == true) {
        if((Node == Node -> parent -> left) && (sibling -> right == NULL || sibling -> right -> color == true)
                && (sibling -> left != NULL && sibling -> left -> color == false)) {
            sibling -> color = false;
            sibling -> left -> color = true;
            rotateR(sibling, head);
        }
        else if((Node == Node -> parent -> right) && (sibling -> left == NULL || sibling -> left -> color
                    == true) && (sibling -> right != NULL && sibling -> right -> color == false)) {
            sibling -> color = false;
            sibling -> right -> color = true;
            rotateL(sibling, head);
        }
    }
    caseFive(head, sibling);
}
void caseThree(node *& head, node * Node) {
    node * sibling = getSibling(Node);
    if((Node -> parent -> color == false) && (sibling -> color == true) && (sibling -> left == NULL ||
                sibling -> left -> color == true) && (sibling -> right == NULL || sibling -> right -> 
                    color == true)) {
        sibling -> color = false;
        Node -> parent -> color = true;
    }
    else {
        caseFour(head, Node);
    }
}
void caseChecker(node *& head, node * Node); 
void caseTwo(node *& head, node * Node) {
    node * sibling = getSibling(Node);
    if((Node -> parent -> color == false) && (sibling -> color == true) && (sibling -> left == NULL ||
                sibling -> left -> color == true) && (sibling -> right == NULL || sibling -> right -> 
                    color == true)) {
        sibling -> color = false;
        caseChecker(head, Node -> parent);
    }
    else {
        caseThree(head, Node);
    }
}
void caseOne(node *& head, node * Node) {
    node * sibling = getSibling(Node);
    if(sibling -> color == false) {
        Node -> parent -> color = false;
        sibling -> color = true;
        if(Node == Node -> parent -> left) {
            rotateL(Node -> parent, head);
        }
        else {
            rotateR(Node -> parent, head);
        }
    }
    caseTwo(head, Node);
}
void caseChecker(node *& head, node * Node) {
    if(Node -> parent != NULL) {
        caseOne(head, Node);
    }
}
bool search(node * head, int valueFind) {
    if(head != NULL) {
        if(head -> value == valueFind) {
            return true;
        }Node
        else {
            if(search(head -> right, valueFind)) {
                return true;
            }
        }
    }
    return false;
}

void replaceTwo(node *& Node, node * child) {
    if(Node -> parent != NULL) {
        child -> parent = Node -> parent;
        if(Node == Node -> parent -> left) {
            Node -> parent -> left = child;
        }
        else {
            Node -> parent -> right = child;
        }
    }
    else {
        Node -> value = child -> value;
        Node -> left = child -> left;
        Node -> right = child -> right;
    }
}
node * findNode(node * head, int valueFind) {
    if(valueFind > head -> value) {
        return findNode(head -> right, valueFind);
    }   
    else if(valueFind < head -> value) {
        return findNode(head -> left, valueFind);
    }
    else if(valueFind == head -> value) {
        return head;
    }
    return NULL;
}
void deleteNode(node * head, int valueFind) {
    if(search(head, valueFind) == false) {
        return;
    }
    node * nodeToDelete = findNode(head, valueFind);
    if(nodeToDelete -> left != NULL && nodeToDelete -> right != NULL) {
        node * successor = nodeToDelete -> right;
        while(successor -> left != NULL) {
            successor = successor -> left;
        }
        nodeToDelete -> value = successor -> value;
        nodeToDelete = successor;
    }
    if(nodeToDelete -> color == false) {
        if(nodeToDelete -> parent != NULL) {
            if(nodeToDelete -> parent -> left == nodeToDelete) {
                nodeToDelete -> parent -> left = NULL;
            }
            else {
                nodeToDelete -> parent -> right = NULL;
            }
        }
        else {

        }
    }
    else if(nodeToDelete -> left != NULL) {
        nodeToDelete -> left -> color = true;
        replaceTwo(nodeToDelete, nodeToDelete -> left);
    }
    else if(nodeToDelete -> right != NULL) {
        nodeToDelete -> right -> color = true;
        replaceTwo(nodeToDelete, nodeToDelete -> right);
    }   
    else {
        if(head == nodeToDelete) {
            head = NULL;
        }
        else {
            caseChecker(head, nodeToDelete);
            if(nodeToDelete -> parent -> left == nodeToDelete) {
                nodeToDelete -> parent -> left = NULL;
            }
            else {
                nodeToDelete -> parent -> right = NULL;
            }
        }
    }
    return;
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
    while(originalHead -> parent) {
        originalHead = originalHead -> parent;
    }
    originalHead -> color = true;
    return head;
}

node * add(int addValue, node * head, node * originalHead) {
    if(head == NULL) {
        node * temp = new node;
        temp -> value = addValue;
        head = temp;
        head -> color = true;
    }
    else if(addValue < head -> value && head -> left != NULL) {
        add(addValue, head -> left, originalHead);
    }
    else if(addValue > head -> value && head -> right != NULL) {
        add(addValue, head -> right, originalHead);
    }
    else if(addValue < head -> value && head -> left == NULL) {
        node * temp = new node;
        temp -> value = addValue;
        temp -> parent = head;
        head -> left = temp;
        head = fix(head -> left, originalHead);
    }
    else if(addValue > head -> value && head -> right == NULL) {
        node * temp = new node;
        temp -> value = addValue;
        temp -> parent = head;
        head -> right = temp;
        head = fix(head -> right, originalHead);
    }
    return head;
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
                cout << "please input #" << endl;
                int inputnum;
                cin >> inputnum;
                head = add(inputnum, head, head);
                if(head -> parent != NULL) {
                    head = head -> parent;
                }
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
                    if(head -> parent != NULL) {
                        head = head -> parent;
                    }
                }
            }
        }
        else if(strcmp("PRINT", input) == 0) {
            print(head, space);
        }
        else if(strcmp("DELETE", input) == 0) {
            int valueFind;
            cout << "Please input # to delete" << endl;
            cin >> valueFind;
            deleteNode(head, valueFind);
        }
        else if(strcmp("SEARCH", input) == 0) {
        }
        else if(strcmp("QUIT", input) == 0) {
            running = false;
        }
    }   
    
    return 0;

}
