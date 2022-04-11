#include <bits/stdc++.h>
using namespace std;

int t,d;


class Node;

class key
{
    public:
        int data;
        Node * leftChild;

        key()
        {
            leftChild = NULL;
        }
};

class Node
{
public:
    bool isDataNode;
    Node * parent;
    vector<key *>values;
    int cap;
    Node * rightmostchild;
    Node(bool leaf, int capacity) {
        isDataNode = leaf;
        parent = NULL;
        cap = capacity;
        rightmostchild = NULL;
    }
};


bool comp(key *a, key*b){
   return a->data < b->data ;
}

Node * root = NULL;

void insert(int val){


    //First value

    if(root == NULL){
        Node * curr = NULL;
        curr = new Node(1 , 2*d);
        key * n = NULL;
        n = new key();
        n->data = val;
        curr->values.push_back(n);
        root = curr;
        return;
    }

    //No Index

    if(root->isDataNode){

        if(root->values.size() < 2*d){
            key * n1 = NULL;
            n1 = new key();
            n1->data = val;
            root->values.push_back(n1);
            sort(root->values.begin(), root->values.end(), comp);
            return;
        }

        else{
            key * n2 = NULL;
            n2 = new key();
            n2->data = val;
            root->values.push_back(n2);
            sort(root->values.begin(), root->values.end(), comp);
            Node * temp = NULL;
            temp = new Node(1 , 2*d);
            for(int i= d; i<2*d + 1; i++){
                key * n3 = NULL;
                n3 = new key();
                n3->data = root->values[i]->data;
                temp->values.push_back(n3);
            }
            for(int i=0; i<d+1; i++){
                root->values.pop_back();
            }

            Node * index = NULL;
            index = new Node(0, 2*t+1);
            key * n3 = NULL;
            n3 = new key();
            n3->data = temp->values[0]->data;
            n3->leftChild = root;
            index->values.push_back(n3);
            index->rightmostchild = temp;
            root->parent = index;
            temp->parent = index;
            root = index;
            return;
        }
    }

    // Indexes

    Node * trav = root;
    while(!(trav->isDataNode)){
        int f = 0;
        for(int i=0;i< trav->values.size();i++){
            if(val < trav->values[i]->data){
                f= 1;
                trav = trav->values[i]->leftChild;
                break;
            }
        }

        if(!f){
            trav = trav->rightmostchild;
        }
    }

    key *n4 = new key();
    n4->data = val;
    trav->values.push_back(n4);
    sort(trav->values.begin(), trav->values.end(), comp);

    if(trav->values.size() <= 2*d){
        return;
    }

    Node * temp = NULL;
    temp = new Node(1 , 2*d);
    for(int i= d; i<2*d + 1; i++){
        key * n3 = NULL;
        n3 = new key();
        n3->data = trav->values[i]->data;
        n3->leftChild = trav->values[i]->leftChild;
        temp->values.push_back(n3);
    }
    for(int i=0; i<d+1; i++){
        trav->values.pop_back();
    }
    temp->parent = trav->parent;
    key * sep = new key();
    sep->data = temp->values[0]->data;
    sep->leftChild = trav;


    if(temp->values[0]->data > trav->parent->values[trav->parent->values.size()-1]->data){
        trav->parent->values.push_back(sep);
        trav->parent->rightmostchild = temp;
    }
    else{
        trav->parent->values.push_back(sep);
        sort(trav->parent->values.begin(), trav->parent->values.end(), comp);
        int i=0;
        while(trav->parent->values[i]->data != sep->data){
            i++;
        }
        i++;
        trav->parent->values[i]->leftChild = temp;

    }

    trav = trav->parent;

    if(!trav) return;

    
    while(trav->values.size() > 2*t + 1){
        if(trav == root || trav == NULL){

            break;
        }

        Node * right = new Node(0, 2*t + 1);
        int sendup = trav->values[t]->data;
        for(int i=t+1; i<=2*t + 1; i++){
            key * k = new key();
            k->data = trav->values[i]->data;
            k->leftChild = trav->values[i]->leftChild;
            right->values.push_back(k);
        }
        right->rightmostchild = trav->rightmostchild;
        right->parent = trav->parent;
        trav->rightmostchild = trav->values[t]->leftChild;

        for(int i=0; i<t+1; i++) trav->values.pop_back();

        for(auto it : right->values){
            it->leftChild->parent = right;
        }
        right->rightmostchild->parent = right;

        key * k1 = new key();
        k1->data = sendup;
        k1->leftChild = trav;

        if(k1->data > trav->parent->values[trav->parent->values.size()-1]->data){
            trav->parent->values.push_back(k1);
            trav->parent->rightmostchild = right;
        }
        else{
            trav->parent->values.push_back(k1);
            Node * currParent = trav->parent;
            sort(currParent->values.begin(), currParent->values.end(), comp);
            int j = 0;
            while(currParent->parent->values[j]->data != k1->data){
                j++;
            }
            currParent->values[j+1]->leftChild = right;
        }
        trav= trav->parent;
    }


    if(trav == root && trav->values.size() > 2*t +1){
        Node * right = new Node(0, 2*t +1);
        int sendup = trav->values[t]->data;

        for(int i=t+1; i<=2*t + 1; i++){
            key * k = new key();
            k->data = trav->values[i]->data;
            k->leftChild = trav->values[i]->leftChild;
            right->values.push_back(k);
        }
        right->rightmostchild = trav->rightmostchild;
        trav->rightmostchild = trav->values[t]->leftChild;

        for(int i=0; i<=t+1; i++) trav->values.pop_back();

        for(auto it : right->values){
            it->leftChild->parent = right;
        }
        right->rightmostchild->parent = right;

        Node * newRoot = new Node(0, 2*t +1);

        key * k2 = new key();
        k2->data = sendup;
        k2->leftChild = root;
        newRoot->rightmostchild = right;
        newRoot->values.push_back(k2);
        right->parent = newRoot;
        root->parent = newRoot;
        root = newRoot;

    }
}


int indexNodes(Node* z)
{
    if (z== NULL) 
        return 0;
    
    if(z->isDataNode)
        return 0;
    
    int ans = 1;
    for (auto x : z->values)
    {
        ans += indexNodes(x->leftChild);
    }
    ans += indexNodes(z->rightmostchild);

    return ans;
}

int  dataNodes(Node* z)
{
    if(z == NULL)
        return 0;

    if(z->isDataNode)
        return 1;
    
    int ans = 0;
    for (auto x : z->values)
    {
        ans += dataNodes(x->leftChild);
    }
    ans += dataNodes(z->rightmostchild);

    return ans;
}

void display()
{
    if(root == NULL)
        return;
    
    cout << indexNodes(root) << " " << dataNodes(root) << " ";
    for (auto x : root->values)
    {
        cout << x->data << " ";
    }
    cout<<endl;
    return;
}


int main(){
    #ifndef ONLINE_JUDGE
        freopen("input1.txt", "r", stdin);
        freopen("output_prac.txt", "w", stdout);
    #endif // ONLINE_JUDGE

    
    cin >> d >> t;


    bool flag  = true;
    while(flag){
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            /* code */
            {int key1;
            cin >> key1;
            insert(key1);}
            break;
        
        case 2:
            /* code */
            {display();}
            break;
        
        case 3:
            /* code */
            {
            flag = 0;}
            break;
        
        default:
            break;
        }
    }



}