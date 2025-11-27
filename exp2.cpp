#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    Node(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};

struct cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

map<char, string> codeMap;
void buildCode(Node* root, string cur) {
    if (!root) return;
    if (!root->left && !root->right) {
        codeMap[root->ch] = cur;
        return;
    }
    buildCode(root->left,  cur + "0");
    buildCode(root->right, cur + "1");
}

int main() {
    string text =
        "I have a dream that one day this nation will rise up and live out the true "
        "meaning of its creed: \"We hold these truths to be self-evident: that all "
        "men are created equal.\"";

    int freq[26] = {0};
    for (char c : text) {
        if (isalpha(c)) {
            c = tolower(c);
            freq[c - 'a']++;
        }
    }

    priority_queue<Node*, vector<Node*>, cmp> pq;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            pq.push(new Node('a' + i, freq[i]));
        }
    }

    while (pq.size() > 1) {
        Node* a = pq.top(); pq.pop();
        Node* b = pq.top(); pq.pop();

        Node* parent = new Node('#', a->freq + b->freq);
        parent->left = a;
        parent->right = b;

        pq.push(parent);
    }

    Node* root = pq.top();
    buildCode(root, "");
    cout << "Huffman 编码表（只列出出现的字母）:\n";
    for (auto& p : codeMap) {
        cout << p.first << " : " << p.second << "\n";
    }
    
    cout << "\n";
    string word = "dream";
    cout << "编码 dream:\n";
    for (char c : word) {
        cout << codeMap[c];
    }
    cout << endl;
    return 0;
}
