#include<bits/stdc++.h>
#define ll long long int
#define ld long double
using namespace std;

// l = no. of ingredients
// idx = index of pizza in original input, as we are sorting it later so we need to keep track of it
// ing vector is ingredients vector

class pizza{
    public:
    ll l;
    ll idx;
    vector<ll> *ing = NULL;
};

// comparator for sorting pizzas according to length descending order

bool comparator(pizza &p1, pizza &p2){
    return p1.l < p2.l;
}

ll intersection(vector<ll> *v1, vector<ll> *v2){
    ll count = 0;
    ll i = 0;
    ll j = 0;
    ll n = v1->size();
    ll m = v2->size();
    while(i<n && j<m){
        ll a1 = v1->at(i);
        ll a2 = v2->at(j);
        if(a1 > a2){
            j++;
        } else if(a1 < a2){
            i++;
        } else {
            count++;
            i++;
            j++;
        }
    }
    return count;
}

vector<ll>* merge2vec(vector<ll> *v1, vector<ll> *v2){
    vector<ll> *merged = new vector<ll>();
    ll i = 0;
    ll j = 0;
    ll n = v1->size();
    ll m = v2->size();
    while(i<n && j<m){
        ll a1 = v1->at(i);
        ll a2 = v2->at(j);
        if(a1 > a2){
            merged->push_back(a2);
            j++;
        } else if(a1 < a2){
            merged->push_back(a1);
            i++;
        } else {
            merged->push_back(a1);
            i++;
            j++;
        }
    }
    if(i<n){
        while(i<n){
            merged->push_back(v1->at(i));
            i++;
        }
    }

    if(j<m){
        while(j<m){
            merged->push_back(v2->at(j));
            j++;
        }
    }

    return merged;
}

void percent_done(ll total_teams, ll d){
    cout<<d<<"/"<<total_teams<<"\n";
}

int main(){
    // ***** INPUT CODE START ************ //
    fstream fin;
    string line;
    // ingredients to number map
    unordered_map<string,ll> indices;
    // fin.open("a_example");
    // fin.open("b_little_bit_of_everything.in");
    // fin.open("c_many_ingredients.in");
    // fin.open("d_many_pizzas.in");
    fin.open("e_many_teams.in");
    // first line inputs m,t1,t2,t3
    ll m,t2,t3,t4;
    getline(fin,line);
    // stringstream
    stringstream ss(line);
    string s;
    // res to store the 4 numbers
    vector<string> res;
    while(getline(ss, s, ' ')){
        res.push_back(s);
    }
    // convert those string numbers to long long int
    m = stoll(res.at(0));
    t2 = stoll(res.at(1));
    t3 = stoll(res.at(2));
    t4 = stoll(res.at(3));
    ll total_teams = t2 + t3 + t4;
    unordered_set<ll> all_pizzas;
    for(ll i=0;i<m;i++){
        all_pizzas.insert(i);
    }
    // vector of pizza objects
    vector<pizza> pizzas;
    int i = 0;
    ll ingredients_index = 0;
    while(getline(fin,line)){
        stringstream ss(line);
        string s;
        // l is size of ingredients in pizza
        ll l = -1;
        // pizza object to be pushed in vector later
        pizza mypizza;
        // ing vector is ingredients vector, isko mypizza object ke vector mei daal denge
        vector<ll> *ing = new vector<ll>();
        while(getline(ss, s, ' ')){
            if(l == -1){
                l = stoll(s);
            } else {
                if(indices.count(s) == 0){
                    indices[s] = ingredients_index;
                    ingredients_index++;
                }
                ing->push_back(indices.at(s));
            }
        }
        // sort the ing vector
        sort(ing->begin(), ing->end());
        mypizza.l = l;
        mypizza.ing = ing;
        mypizza.idx = i;
        // pushing mypizza in vector pizzas
        pizzas.push_back(mypizza);
        i++;
    }

    fin.close();

    // ***** INPUT CODE END *****

    // vector pizzas has all the pizzas

    // ***** Algo ***** //
    sort(pizzas.begin(), pizzas.end(), comparator);
    // answer 2D vector, isko output .txt file mei write karwa denge
    vector<vector<ll>> ans;

    ll p = pizzas.size()-1;
    // d = number of pizzas delivered 
    ll d = 0;

    while(t4 > 0 && all_pizzas.size() >= 4){
        if(all_pizzas.count(pizzas.at(p).idx) == 0){
            p--;
            continue;
        }
        pizza mypizza = pizzas.at(p);
        ll fi = p;
        ll si = -1;
        ll currint = INT_MAX;
        ll uni = INT_MIN;
        ll fact = INT_MIN;
        for(ll i=fi-1;i>=0;i--){
            if(all_pizzas.count(pizzas.at(i).idx) > 0){
                ll temp = intersection(pizzas.at(fi).ing , pizzas.at(i).ing);
                ll u = pizzas.at(fi).ing->size() + pizzas.at(i).ing->size() - temp;
                ll f = u - temp;
                // cout<<f<<"\n";
                if(f > fact){
                    uni = u;
                    currint = temp;
                    fact = f;
                    si = i;
                }
            }
        }

        vector<ll> vec;
        all_pizzas.erase(pizzas.at(fi).idx);
        all_pizzas.erase(pizzas.at(si).idx);
        ll third_pizza = -1;
        vector<ll> *mvec1 = merge2vec(pizzas.at(fi).ing , pizzas.at(si).ing);
        currint = INT_MAX;
        uni = INT_MIN;
        fact = INT_MIN;
        for(ll i=0;i<pizzas.size();i++){
            if(all_pizzas.count(pizzas.at(i).idx) > 0){
                ll temp = intersection(mvec1 , pizzas.at(i).ing);
                ll u = pizzas.at(i).ing->size() + mvec1->size() - temp;
                ll f = u - temp;
                if(f > fact){
                    uni = u;
                    currint = temp;
                    fact = f;
                    third_pizza = i;
                }
            }
        }

        all_pizzas.erase(pizzas.at(third_pizza).idx);
        ll fourth_pizza = -1;
        vector<ll> *mvec2 = merge2vec(mvec1 , pizzas.at(third_pizza).ing);
        currint = INT_MAX;
        uni = INT_MIN;
        fact = INT_MIN;
        for(ll i=0;i<pizzas.size();i++){
            if(all_pizzas.count(pizzas.at(i).idx) > 0){
                ll temp = intersection(mvec2 , pizzas.at(i).ing);
                ll u = pizzas.at(i).ing->size() + mvec2->size() - temp;
                ll f = u - temp;
                if(f > fact){
                    uni = u;
                    currint = temp;
                    fact = f;
                    fourth_pizza = i;
                }
            }
        }

        all_pizzas.erase(pizzas.at(fourth_pizza).idx);

        vec.push_back(4);
        vec.push_back(pizzas.at(fi).idx);
        vec.push_back(pizzas.at(si).idx);
        vec.push_back(pizzas.at(third_pizza).idx);
        vec.push_back(pizzas.at(fourth_pizza).idx);
        ans.push_back(vec);
        delete mvec1;
        delete mvec2;
        t4--;
        d++;
        percent_done(total_teams,d);
    }

    while(t3 > 0 && all_pizzas.size() >= 3){
        if(all_pizzas.count(pizzas.at(p).idx) == 0){
            p--;
            continue;
        }
        pizza mypizza = pizzas.at(p);
        ll fi = p;
        ll si = -1;
        ll currint = INT_MAX;
        ll uni = INT_MIN;
        ll fact = INT_MIN;
        for(ll i=fi-1;i>=0;i--){
            if(all_pizzas.count(pizzas.at(i).idx) > 0){
                ll temp = intersection(pizzas.at(fi).ing , pizzas.at(i).ing);
                ll u = pizzas.at(fi).ing->size() + pizzas.at(i).ing->size() - temp;
                ll f = u - temp;
                if(f > fact){
                    uni = u;
                    currint = temp;
                    fact = f;
                    si = i;
                }
            }
        }
        all_pizzas.erase(pizzas.at(fi).idx);
        all_pizzas.erase(pizzas.at(si).idx);

        ll third_pizza = -1;
        vector<ll> *mvec1 = merge2vec(pizzas.at(fi).ing , pizzas.at(si).ing);
        currint = INT_MAX;
        uni = INT_MIN;
        fact = INT_MIN;
        for(ll i=0;i<pizzas.size();i++){
            if(all_pizzas.count(pizzas.at(i).idx) > 0){
                ll temp = intersection(mvec1 , pizzas.at(i).ing);
                ll u = mvec1->size() + pizzas.at(i).ing->size() - temp;
                ll f = u - temp;
                if(f > fact){
                    uni = u;
                    currint = temp;
                    fact = f;
                    third_pizza = i;
                }
            }
        }

        all_pizzas.erase(pizzas.at(third_pizza).idx);

        vector<ll> vec;
        
        vec.push_back(3);
        vec.push_back(pizzas.at(fi).idx);
        vec.push_back(pizzas.at(si).idx);
        vec.push_back(pizzas.at(third_pizza).idx);
        ans.push_back(vec);
        delete mvec1;
        t3--;
        d++;
        percent_done(total_teams,d);
    }

    while(t2 > 0 && all_pizzas.size() >= 2){
        if(all_pizzas.count(pizzas.at(p).idx) == 0){
            p--;
            continue;
        }
        pizza mypizza = pizzas.at(p);
        ll fi = p;
        ll si = -1;
        ll currint = INT_MAX;
        ll uni = INT_MIN;
        ll fact = INT_MIN;
        for(ll i=fi-1;i>=0;i--){
            if(all_pizzas.count(pizzas.at(i).idx) > 0){
                ll temp = intersection(pizzas.at(fi).ing , pizzas.at(i).ing);
                ll u = pizzas.at(fi).ing->size() + pizzas.at(i).ing->size() - temp;
                ll f = u - temp;
                if(f > fact){
                    uni = u;
                    currint = temp;
                    fact = f;
                    si = i;
                }
            }
        }
        vector<ll> vec;
        vec.push_back(2);
        vec.push_back(pizzas.at(fi).idx);
        vec.push_back(pizzas.at(si).idx);
        ans.push_back(vec);
        all_pizzas.erase(pizzas.at(fi).idx);
        all_pizzas.erase(pizzas.at(si).idx);
        t2--;
        d++;
        percent_done(total_teams,d);
    }

    

    // ***** OUTPUT WRITE CODE START ***** //

    fstream fout;
    fout.open("o5.txt", ios::out);
    // outputting d in file to indicate number of deliveries made
    fout<<d<<"\n";
    // iterations to write the 2D vector ans to the output .txt file
    for(auto it = ans.begin();it != ans.end();it++){
        vector<ll> vec = (*it);
        for(ll j = 0;j<vec.size();j++){
            ll ele = vec.at(j);
            if(j == vec.size()-1){
                fout<<ele;
            } else {
                fout<<ele<<" ";
            }
        }
        fout<<"\n";
    }
    
    fout.close();
    return 0;
}