#include <bits/stdc++.h>
using namespace std;


int global_depth, bucket_capacity;
struct Bucket {
    // public:

        int local_depth;
        int capacity;
        int hashval;
        vector<int>bucket;

            
        // Bucket(int local, int hash){
        //     local_depth = local;
        //     hashval = hash;
        //     capacity = bucket_capacity;
        // }
};


map<int, Bucket *> bucket_directory;
vector<int> buckets;

void display(){
    cout << global_depth << endl;
    cout << buckets.size() << endl;
    for(int i=0; i<buckets.size(); i++){
        cout <<bucket_directory[buckets[i]]->bucket.size() << " " << bucket_directory[buckets[i]]->local_depth << endl;
    }
}

int hash_func(int val){
    return val & ((1 << global_depth) -1) ;
}

int search(int key){
    int f = 0;
    int h = hash_func(key);

    for(int i=0; i<bucket_directory[h]->bucket.size(); i++){
        if(key == bucket_directory[h]->bucket[i]){
            f=1;
            return f;
        }
    }


    return f;
}

void split(int hash_value, int key){
    int l = bucket_directory[hash_value]->local_depth + 1; 
    int h = bucket_directory[hash_value]->hashval;
    bucket_directory[hash_value]->local_depth = l;

    // Bucket t = new Bucket(l, h + pow(2, l) -1);
    Bucket * t = new Bucket;
    t->local_depth = l;
    t->hashval =  h + pow(2, l-1);
    t->capacity = bucket_capacity;

    vector<int>t1 = bucket_directory[hash_value]->bucket;
    bucket_directory[hash_value]->bucket.clear();
    for(int i=0; i<t1.size(); i++){
        if(hash_func(t1[i]) > h){
            t->bucket.push_back(t1[i]);
        }
        else{
            bucket_directory[h]->bucket.push_back(t1[i]);
        }
    }
    buckets.push_back(h + pow(2, l-1) );
    bucket_directory[h + pow(2, l-1) ] = t;
    
    
}

void split2(int hsh){
    int x = pow(2, global_depth);
    global_depth++;
    int y = pow(2 , global_depth);
    for(int i=x; i< 2*x; i++){
        bucket_directory[i] = bucket_directory[i - x];
    }
}

void insert(int key){
    if(search(key)){
        cout <<"Key value (" << key << ") already exists!\n";
        return;
    }

    int h = hash_func(key);
    if(bucket_directory[h]->bucket.size()  < bucket_directory[h]->capacity){
        bucket_directory[h]->bucket.push_back(key);
        cout << "Number inserted successfully " << key << " \n";
        return;
    }

    else if(bucket_directory[h]->local_depth < global_depth){
        cout << "split " << key << endl;
        split(h, key);
        insert(key);

        return;
    }

    else if(bucket_directory[h]->local_depth == global_depth){
        cout << "split2 " << key << endl;
        split2(bucket_directory[h]->hashval);
        split(h, key);
        insert(key);
        return;
    }

}


// void merge()
// {
// 	for(int i = 0; i<(1<<(global_depth-1));i++)
// 	{
// 		int h = i & ( ( 1<< ((bmap[i]->ld)-1) ) - 1);
// 		/*Current and Matched are pair of matching data buckets having ld-1 common suffix*/
// 		Bucket *curr = bmap[i];
// 		Bucket *matched = bmap[ i ^ (1<<(bmap[i]->ld-1)) ];
// 		if(curr != matched)
// 		{
// 			int sz = curr->a.size() + matched->a.size();
// 			if(sz <= bucket_capacity)
// 			{
// 				copy(all(matched->a),back_inserter(curr->a));
// 				vector<int>inds;
// 				for(auto i : bmap)
// 				{
// 					if(i.second==matched)
// 						inds.pb(i.first);
// 				}
// 				delete matched;
// 				for(auto j : inds)
// 					bmap[j] = bmap[i];
// 				bmap[i]->ld --;
// 			}
// 		}
// 	}
// }

void shrink()
{
	set <Bucket *>buck;
	for(auto i : bucket_directory)
		buck.insert(i.second);
	int count = 0;
	int sz = buck.size();
	for(auto i : buck)
		if ( (global_depth - (i->local_depth)) == 1)
			count++;
	if(count==sz)
		global_depth--;
}

void del(int n)
{
	if(search(n))
	{
		int hs = hash_func(n);
        int i = -1;
        for(i=0; i<bucket_directory[hs]->bucket.size(); i++){
            if(bucket_directory[hs]->bucket[i] == n){
                bucket_directory[hs]->bucket.erase(bucket_directory[hs]->bucket.begin()  + i);
                break;
            }
        }

		/*Merging the pair of data buckets if possible*/
		// merge();

		// /*If all the buckets have local depth less than global depth then shrink the directory*/
		// shrink();

		cout<<"Number deleted successfully " << n <<" \n";
	}
	else
		cout<<"Element not found : \n";
}


int main(){
    #ifndef ONLINE_JUDGE
        freopen("input1.txt", "r", stdin);
        freopen("output_prac.txt", "w", stdout);
    #endif // ONLINE_JUDGE

    
    cin >> global_depth;
    cin >> bucket_capacity;

    int tot_init = (1 << global_depth);

    for(int i=0; i < tot_init; i++){
        // Bucket temp = new Bucket(global_depth, i);
        Bucket * temp = new Bucket;
        temp->local_depth = global_depth;
        temp->hashval =  i;
        temp->capacity = bucket_capacity;
        buckets.push_back(i);
        bucket_directory[i] = temp;
    }

    /*
First two lines describe the initialization parameters for your extendible hash table.
Line 1: Global depth
Line 2: Bucket capacity
Remaining lines of the input file describe the operations to be performed on the hash table.
2: Insert new value
3: Search a value
4: Delete a value
5: Display status of the hash table
6: Quit
*/
    bool flag  = true;
    while(flag){
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 2:
            /* code */
            {int key1;
            cin >> key1;
            insert(key1);}
            break;
        
        case 3:
            /* code */
            {int key; 
            cin >> key;
            int f1 = search(key);
            if(f1){
                cout << "Key value(" << key << ") found\n";
            }
            else{
                cout << "Key value(" << key << ") not found\n";
            }}
            break;
        
        case 4:
            /* code */
            {
                int n; cin >> n;
                del(n);
            }
            break;
        
        case 5:
            /* code */
            {display();}
            break;
        
        case 6:
            /* code */
            {cout << "Exiting...\n";
            flag = 0;}
            break;
        
        default:
            break;
        }
    }

    


}