#include <bits/stdc++.h>
using namespace std;
#include <fstream>
using std::ifstream;
#include <cstdlib>
typedef long long ll;
ll ct = 0;

void merge(ll a[], ll beg, ll mid, ll end) {
   ll i, j, k, lbound, rbound;
   lbound = mid-beg+1; rbound = end-mid;
   ll lefta[lbound], righta[rbound];
   for(i = 0; i<lbound; i++)
      lefta[i] = a[beg+i];
   for(j = 0; j<rbound; j++)
      righta[j] = a[mid+1+j];
   i = 0; j = 0; k = beg;
   while(i < lbound && j<rbound) {
      if(lefta[i] < righta[j]) {
         a[k] = lefta[i];    
         i++;
      }
      else{
         a[k] = righta[j];
         j++;
         ct += lbound-i; 
      }
      k++;
   }
   while(i<lbound) {  
      a[k] = lefta[i];
      i++; k++;
   }
   while(j<rbound) { 
      a[k] = righta[j];
      j++; k++;
   }
}

void sortMerge(ll a[],ll beg, ll end){
    if(beg >= end){return ;}  
    auto mid = beg + (end - beg) / 2;
    sortMerge(a, beg, mid);
    sortMerge(a, mid + 1, end);
    merge(a, beg, mid, end);
}

int main(){

    ifstream datainp;
    datainp.open("tstcase2.txt");
    ll n;
    vector<ll>v;
    // datainp >> n;
    // v.push_back(n);
    while (datainp >> n) { 
      v.push_back(n);
   }
    datainp.close();
    // v.pop_back();
    // cout << v.size() << endl;
    // for(int i=0; i<v.size(); ++i){cout << v[i] << endl;}
    ll b = v.size();
    ll a[b];
    sort(v.begin(), v.end(), greater<ll>());
    for(ll i=0; i<v.size(); i++){
        a[i] = v[i];
    }
    sortMerge(a, 0, b - 1);
    
    cout << ct << endl;    
}