#include <bits/stdc++.h>
using namespace std;

long long getMinMul(const vector<int> &numbers, vector<int> &result){
    multiset<int> maxs;
    multiset<int, bool(*)(int,int)> mins([](int l, int r){ return l>r; });
    for(auto i:numbers){
        mins.insert(i);
        maxs.insert(i);
        if(maxs.size()>2){
            maxs.erase(maxs.begin());
        }
        if(mins.size()>3){
            mins.erase(mins.begin());
        }
    }
    
    vector<int> maxsVector;
    vector<int> minsVector;
    std::copy_n(maxs.rbegin(), maxs.size(), std::back_inserter(maxsVector));
    std::copy_n(mins.rbegin(), mins.size(), std::back_inserter(minsVector));
    assert(mins.size()==3);
    assert(maxs.size()==2);
    
    long long first = static_cast<long long>(minsVector[0]) * minsVector[1] * minsVector[2];
    long long second = static_cast<long long>(minsVector[0]) * maxsVector[0] * maxsVector[1];
    
    if(first<second){
        result = vector<int>({minsVector[0], minsVector[1], minsVector[2]});
        return first;
    } else{
        result = vector<int>({minsVector[0], maxsVector[0], maxsVector[1]});
        return second;
    }
}

int main(){
    vector<int> tmp;
    assert(-60 == getMinMul(vector<int>({ 1, 2,-3, -4,-5}),tmp));
    assert(-60 == getMinMul(vector<int>({ 1, 2, 3,  4,-5}),tmp));
    assert(-40 == getMinMul(vector<int>({ 1,-2, 3, -4,-5}),tmp));
    assert(-20 == getMinMul(vector<int>({-1, 2, 3,  4, 5}),tmp));
    assert(  6 == getMinMul(vector<int>({ 1, 2, 3,  4, 5}),tmp));
    
    assert(1000000000000000LL == getMinMul(vector<int>({ 100000, 100000, 100000}),tmp));
    
    int n;
    cin>>n;
    vector<int> numbers;
    for(int i=0; i<n; ++i){
        int a;
        cin>>a;
        numbers.push_back(a);
    }
    vector<int> result;
    long long ans = getMinMul(numbers, result);
    for(auto i:result){
        cout<<i<<" ";
    }
}
