#include <iostream>
#include <vector>
#include <list>
#include "hashtable.h"

using namespace std;
int HashFunction(const Key& x, int tsize){
    int res = 0;
    for(char i : x)
        res = (res + i);
    res = (res * 2) % tsize;
}
HashTable::HashTable(){
    ms.weight = 100;
    ms.age  = 75;
    us = 10;
    cs = 0;
    list<pair<Key, Value>>*k = nullptr;
    arr.resize(us, k);
}

HashTable::~HashTable() {
    arr.clear();
    us = 0;
    cs = 0;
}

HashTable::HashTable(const HashTable& b): HashTable(){
    us = b.us;
    cs = b.cs;
    arr = vector<list<pair<Key, Value>>*>(us);
    for(int i = 0; i < b.arr.size(); i++)
        arr[i] = b.arr[i];
}

HashTable::HashTable(HashTable &&b) noexcept{
    arr = b.arr;
    us  = b.us;
    cs = b.cs;
    for(auto & i : b.arr){
        i = nullptr;
    }
    b.us = 0;
    b.cs = 0;
}

HashTable& HashTable::operator=(const HashTable& b){
    if(this == &b){
        return *this;
    }
    us = b.us;
    cs = b.cs;
    arr.clear();
    arr = b.arr;
    return *this;
}

HashTable& HashTable::operator=(HashTable &&b){
    if(this == &b){
        return *this;
    }
    us = b.us;
    cs = b.cs;
    arr.clear();
    arr = b.arr;
    for(auto & i : b.arr){
        i = nullptr;
    }
}

void HashTable::swap(HashTable &b){
    int tmp = cs;
    cs = b.cs;
    b.cs = tmp;
    tmp = us;
    us = b.us;
    b.us = tmp;
    arr.swap(b.arr);
}

void HashTable::clear(){
    list<pair<Key, Value>>* emList = nullptr;
    arr.clear();
    arr.resize(us, emList);
}

bool HashTable::erase(const Key& k){
    if(!contains(k))
        return false;
    int hash = HashFunction(k, us);
    for(auto t = arr[hash]->begin(); t != arr[hash]->end(); t++){
        if(t->first == k){
            arr[hash]->erase(t);
            cs--;
            return true;
        }
    }
}

bool HashTable::insert(const Key& k, const Value& v){
    if(contains(k))
        return false;
    int hash = HashFunction(k, us);
    if(arr[hash] == nullptr){
        arr[hash] = new list<pair<Key, Value>>;
    }
    arr[hash]->push_front(make_pair(k, v));
    if(cs/us > 0.75){
        resize();
    }
    cs++;
}

void HashTable::resize(){
    vector<list<pair<Key, Value>>*> copy = arr;
    arr.clear();
    us *= 2;
    list<pair<Key, Value>>* emList = nullptr;
    arr.resize(us, emList);
    for(int i = 0; i < us/2; i++){
        if(!copy[i]->empty()){
            for(auto & t : *copy[i]){
                insert(t.first, t.second);
            }
        }
    }
}

bool HashTable::contains(const Key& k)const{
    int hash = HashFunction(k, us);
    if(arr[hash] == nullptr){
        return false;
    }
    for(const auto & t : *arr[hash]){
        if(t.first == k){
            return true;
        }
    }
    return false;
}

Value& HashTable::operator[](const Key &k){
    if(contains(k)){
        int hash = HashFunction(k, us);
        for(auto & t : *arr[hash]){
            if(t.first == k){
                return t.second;
            }
        }
    }
    insert(k, ms);
    return ms;
}

Value& HashTable::at(const Key &k){
    if(contains(k)){
        int hash = HashFunction(k, us);
        for(auto & t : *arr[hash]){
            if(t.first == k){
                return t.second;
            }
        }
    }
    else{
        throw invalid_argument("No such element");
    }
}

size_t HashTable::size() const{
    return cs;
}

bool HashTable::empty()const{
    for(const auto t : arr){
        if(t != nullptr){
            return false;
        }
    }
    return true;
}

bool operator == (const HashTable& a, const HashTable& b){
    return a.arr == b.arr;
}

bool operator != (const HashTable& a, const HashTable& b){
    return a.arr != b.arr;
}