#include <bits/stdc++.h>
using namespace std;

int pagesize;

class page{
public:
    int remsize;
    int totrecords;
    vector<int>candikey;
    page * prevpage;
    page * nxtpage;
    int pagenumber;

    page(){
        prevpage = NULL;
        nxtpage = NULL;
        remsize = pagesize - 16;
        totrecords = 0;
        pagenumber = 0;
    }
};

class heapFile{
public:
    int totpages;
    page * head;

    heapFile(){
        totpages = 0;
        head = NULL;
    }

    void insert(int val, int candi){
        page * curr = head;
        page * last = curr;
        if(head == NULL){
            head = new page();
            totpages++;
            head->remsize = head->remsize - 4 - val;
            head->candikey.push_back(candi);
            head->totrecords++;
            return;
        }

        while(curr){
            if(curr->remsize >= 4 + val){
                curr->candikey.push_back(candi);
                curr->remsize -= 4 + val;
                curr->totrecords++;
                return;
            }
            last = curr;
            curr = curr->nxtpage;
        }

        page * newpage = new page();
        totpages++;
        newpage->candikey.push_back(candi);
        newpage->remsize -= 4 + val;
        newpage->totrecords++;
        newpage->prevpage = last;
        last->nxtpage = newpage;
        newpage->pagenumber = last->pagenumber + 1;
        return;

    }

    void status(){
        cout << totpages << " ";
        page * curr = head;
        while(curr){
            cout << curr->totrecords << " ";
            curr = curr->nxtpage;
        }
        cout << endl;
        return;
    }


    void search(int key){
        page * curr = head;
        while(curr){
            for(int i=0; i<curr->candikey.size(); i++){
                if(key == curr->candikey[i]){
                    cout << curr->pagenumber <<  " " << i << endl;
                    return;
                }
            }
            curr = curr->nxtpage;
        }
        cout << "-1 - 1\n";
        return;
    }

};




int main(){
    // #ifndef ONLINE_JUDGE
    //     freopen("input1.txt", "r", stdin);
    //     freopen("output_prac.txt", "w", stdout);
    // #endif // ONLINE_JUDGE
    cin >> pagesize;
    heapFile * file = new heapFile();


    bool flag  = true;
    while(flag){
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            /* code */
            {int s, candi;
            cin >> s >> candi;
            file->insert(s, candi);}
            break;
        
        case 2:
            /* code */
            {file->status();}
            break;

        case 3:
            /* code */
            {
            int k; cin >> k; file->search(k);}
            break;
        
        
        case 4:
            /* code */
            {
            flag = 0;}
            break;
        
        default:
            break;
        }
    }
}