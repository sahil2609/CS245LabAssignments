#include <bits/stdc++.h>
using namespace std;

int main(){
    #ifndef ONLINE_JUDGE
        freopen("input1.txt", "r", stdin);
        freopen("output_prac.txt", "w", stdout);
    #endif // ONLINE_JUDGE
    int buff_pages, recperp, tot_rec;
    cin >> buff_pages>> recperp>> tot_rec;

    vector<vector<int>>pages;
    vector<int>rec(tot_rec);
    for(int i=0; i<tot_rec; i++) cin >> rec[i];

    int t = tot_rec/recperp;
    for(int i=0; i<t; i++){
        vector<int>tmp;
        for(int j=0; j<recperp; j++){
            tmp.push_back(rec[i*recperp + j]);
        }
        pages.push_back(tmp);
    }
    vector<int>tmp;
    for(int i= t*recperp; i<tot_rec; i++){
        tmp.push_back(rec[i]);
    }
    pages.push_back(tmp);

    vector<vector<int>>tt;
    t = pages.size()/buff_pages;

    for(int i=0; i<t; i++){
        vector<int>tp;
        for(int j=0; j<buff_pages; j++){
            for(int k=0; k< pages[i*buff_pages + j].size(); k++){
                tp.push_back(pages[i*buff_pages + j][k]);
            }
        }
        sort(tp.begin(), tp.end());
        tt.push_back(tp);
    }
    vector<int>tp2;
    for(int i=t*buff_pages; i<pages.size(); i++){
        for(int j=0; j<pages[i].size(); j++){
            tp2.push_back(pages[i][j]);
        }
        
    }
    sort(tp2.begin(), tp2.end());
    tt.push_back(tp2);
    pages = tt;

    buff_pages--;


    while(pages.size() > 1){
        int x = pages.size();
        vector<vector<int>>ttt;
        int t2 = pages.size()/buff_pages;

        for(int i=0; i<t2; i++){
            vector<int>tp3;
            for(int j=0; j<buff_pages; j++){
                for(int k=0; k< pages[i*buff_pages + j].size(); k++){
                    tp3.push_back(pages[i*buff_pages + j][k]);
                }
            }
            sort(tp3.begin(), tp3.end());
            ttt.push_back(tp3);
        }
        vector<int>tp4;
        for(int i=t2*buff_pages; i<pages.size(); i++){
            for(int j=0; j<pages[i].size(); j++){
                tp4.push_back(pages[i][j]);
            }
            
        }
        sort(tp4.begin(), tp4.end());
        ttt.push_back(tp4);
        pages = ttt;
    }


    for(int i=0; i<pages[0].size(); i++){
        cout << pages[0][i] << endl;
    }
}