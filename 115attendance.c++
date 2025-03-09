#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int x){
        data = x;
        next = nullptr;
    }
};

void Insertwithpointer(int x, Node** current) {
    if (*current == nullptr) {
        *current = new Node(x);
        return;
    }
    Insertwithpointer(x, &((*current)->next));
}

void Insertwithreference(int x, Node*& current) {
    if (current == nullptr) {
        current = new Node(x);
        return;
    }
    Insertwithreference(x, current->next);
}

Node* Insertwithreturn(int x, Node* current) {
    if (current == nullptr) {
        return new Node(x);
    }
    current->next = Insertwithreturn(x, current->next);
    return current;
}

void PrintList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " -> ";
        head = head->next;
    }
    cout << "NULL" << endl;
}

int main() {
    Node* head1 = nullptr;
    Node* head2 = nullptr;
    Node* head3 = nullptr;

    Insertwithpointer(1, &head1);
    Insertwithpointer(2, &head1);
    Insertwithpointer(3, &head1);
    cout << "Pointer List: ";
    PrintList(head1);

    Insertwithreference(1, head2);
    Insertwithreference(2, head2);
    Insertwithreference(3, head2);
    cout << "Reference List: ";
    PrintList(head2);

    head3 = Insertwithreturn(1, head3);
    head3 = Insertwithreturn(2, head3);
    head3 = Insertwithreturn(3, head3);
    cout << "Return List: ";
    PrintList(head3);

    return 0;
}
