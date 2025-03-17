#include <iostream>
#include <vector>

using namespace std;

class Hash
{
private:
    struct Object
    {
        string key;
        int value;
        bool occupied;
        bool deleted;

        Object()
        {
            key = "";
            value = 0;
            occupied = false;
            deleted = false;
        }
        Object(string k, int v)
        {
            key = k;
            value = v;
            occupied = true;
            deleted = false;
        }
    };

    Object *table;
    int size;

    int hash(const string &key)
    {
        unsigned long hashValue = 0;
        for (char ch : key)
        {
            hashValue = hashValue * 31 + ch;
        }
        return hashValue % size;
    }

public:
    Hash(int s)
    {
        size = s;
        table = new Object[size];
    }

    ~Hash()
    {
        delete[] table;
    }

    void add(const string &key, int value)
    {
        int index = hash(key);
        int originalIndex = index;
        while (table[index].occupied)
        {
            if (table[index].key == key)
            {
                table[index].value = value;
                return;
            }
            index = (index + 1) % size;
            if (index == originalIndex)
                return;
        }
        table[index] = Object(key, value);
    }

    bool exists(const string &key)
    {
        int index = hash(key);
        int originalIndex = index;

        while (table[index].occupied || table[index].deleted)
        {
            if (table[index].occupied && table[index].key == key)
                return true;
            index = (index + 1) % size;
            if (index == originalIndex)
                break;
        }
        return false;
    }

    int get(const string &key)
    {
        int index = hash(key);
        int originalIndex = index;

        while (table[index].occupied || table[index].deleted)
        {
            if (table[index].occupied && table[index].key == key)
                return table[index].value;
            index = (index + 1) % size;
            if (index == originalIndex)
                break;
        }
        cout << "key not found\n";
        exit(EXIT_FAILURE);
    }

    void remove(const string &key)
    {
        int index = hash(key);
        int originalIndex = index;

        while (table[index].occupied || table[index].deleted){
            if(table[index].occupied && table[index].key == key){
                table[index].occupied = false;
                table[index].deleted = true;
                return;
            }
            index = (index+1)%size;
            if(index == originalIndex)break;
        }
    }
};

int main() {
    Hash ht(10);
    ht.add("apple", 100);
    ht.add("banana", 200);
    ht.add("orange", 300);

    cout << "Exists 'apple': " << ht.exists("apple") << endl;
    cout << "Get 'banana': " << ht.get("banana") << endl;

    ht.remove("banana");
    cout << "Exists 'banana' after removal: " << ht.exists("banana") << endl;

    return 0;
}