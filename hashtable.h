#include <vector>
#include <list>
#ifndef UNTITLED_MAIN_H
#define UNTITLED_MAIN_H
#endif
using namespace std;
struct Student{
    unsigned  age;
    unsigned weight;
};
typedef std::string Key;
typedef Student Value;
class HashTable{
    vector<list<pair<Key, Value>>*> arr;
    int cs;
    int us;
    Value ms{};
public:
    HashTable();
    ~HashTable();
    HashTable(const  HashTable& b);
    HashTable(HashTable&& b) noexcept;
    HashTable& operator = (const HashTable& b);
    HashTable& operator = (HashTable&& b);
    void swap(HashTable& b);
    void clear();
    bool erase(const Key& k);
    bool insert(const Key& k, const Value& v);
    bool contains(const Key& k) const;
    Value& operator[](const Key& k);
    Value& at(const Key& k) const;
    size_t size() const;
    bool empty() const;
    friend bool operator == (const HashTable& a, const HashTable& b);
    friend bool operator != (const HashTable& a, const HashTable& b);
    void resize();
};
bool operator == (const HashTable& a, const HashTable& b);
bool operator != (const HashTable& a, const HashTable& b);