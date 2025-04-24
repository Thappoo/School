#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <climits>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
    Node(char ch, int freq, Node* left, Node* right): ch(ch), freq(freq), left(left), right(right){}
};

typedef double MyType;

class MyQueue {
public:
    ~MyQueue() {
        delete [] q;
    }

    MyQueue(int capacity1) {
        capacity = capacity1;
        front = size = 0;
        rear = 0;
        q = new MyType[capacity];
    }

    bool IsFull() {
        return (size == capacity);
    }

    bool IsEmpty() {
        return (size == 0);
    }

    void Enqueue(MyType x) {
        if (!IsFull()) {
            q[rear] = x;
            rear = (rear + 1) % capacity;
            size = size + 1;
        } else {
            cout << " Queue is full" << endl;
        }
    }

    MyType Dequeue() {
        if (IsEmpty()) {
            return INT_MIN;
        }
        MyType item = q[front];
        front = (front + 1) % capacity;
        size = size - 1;
        return item;
    }

private:
    int front, rear, size;
    int capacity;
    MyType* q;
};

class PriorityQueue {
private:
    vector<Node*> heap;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (heap[index]->freq < heap[parent]->freq) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap.size() && heap[left]->freq < heap[smallest]->freq) {
            smallest = left;
        }
        if (right < heap.size() && heap[right]->freq < heap[smallest]->freq) {
            smallest = right;
        }
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    bool empty() const {
        return heap.empty();
    }

    size_t size() const {
        return heap.size();
    }

    Node* top() const {
        return heap.front();
    }

    void push(Node* node) {
        heap.push_back(node);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
    }
};

void printCodes(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    printCodes(root->left, str + "0", huffmanCode);
    printCodes(root->right, str + "1", huffmanCode);
}

void decodeHuffman(Node* root, const string& encodedStr) {
    cout << "\nDecoded string:\n";
    Node* curr = root;
    for (char bit : encodedStr) {
        curr = (bit == '0') ? curr->left : curr->right;

        if (!curr->left && !curr->right) {
            cout << curr->ch;
            curr = root;
        }
    }
    cout << "\n";
}

void buildHuffmanTree(string text) {
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    PriorityQueue pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    printCodes(root, "", huffmanCode);

    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " " << pair.second << "\n";
    }

    cout << "\nOriginal string:\n" << text << "\n";

    string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }
    cout << "\nEncoded string:\n" << encodedStr << "\n";

    decodeHuffman(root, encodedStr);
}

int main() {

    string text = "CODING";
    buildHuffmanTree(text);
    
    string text1 = "JAPANESE";
    buildHuffmanTree(text1);

    return 0;
}