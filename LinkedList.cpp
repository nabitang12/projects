#include <iostream>

using namespace std;

struct node
{
    int data;
    node *next;
};

class SingleList
{
private:
    node *head;
    int current;

public:
    SingleList()
    {
        head = nullptr;
        current = -1;
    }
    int size()
    {
        return current + 1;
    }
    bool empty()
    {
        return current == -1;
    }
    int value_at(int index)
    {
        if (index > current)
        {
            cout << "out of bounds";
            exit(EXIT_FAILURE);
        }
        node *temp = head;
        for (int i = 0; i < index; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    }
    void push_front(int value)
    {
        node *temp = new node;
        temp->data = value;
        temp->next = head;
        head = temp;
        current++;
    }
    int pop_front()
    {
        if (empty())
        {
            cout << "empty";
            exit(EXIT_FAILURE);
        }
        node *temp = head;
        int result = temp->data;
        head = head->next;
        delete temp;
        current--;
        return result;
    }
    void push_back(int value)
    {
        node* newNode = new node;
        newNode->data = value;
        newNode->next = nullptr;

        if(empty()){
            head = newNode;
        }
        else{
            node* temp = head;
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = newNode;
        }
        current++;
    }
    int pop_back()
    {
        if (empty())
        {
            cout << "empty";
            exit(EXIT_FAILURE);
        }

        node *temp = head;
        node *before = nullptr;
        if (temp->next == nullptr)
        {
            int result = temp->data;
            delete temp;
            head = nullptr;
            return result;
        }

        while (temp->next != NULL)
        {
            before = temp;
            temp = temp->next;
        }
        before->next = nullptr;
        int result = temp->data;
        delete (temp);
        current--;
        return result;
    }

    int front()
    {
        if (head == nullptr)
        {
            cout << "empty";
            exit(EXIT_FAILURE);
        }

        return head->data;
    }

    int back()
    {
        if (head == nullptr)
        {
            cout << "empty";
            exit(EXIT_FAILURE);
        }

        node *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    void insert(int index, int value)
    {
        if (index > current || index < 0)
        {
            cout << "out of bounds";
            exit(EXIT_FAILURE);
        }
        node *prev = nullptr;
        node *temp = head;

        for (int i = 0; i < index; ++i)
        {
            prev = temp;
            temp = temp->next;
        }
        if (prev == nullptr)
        {
            push_front(value);
        }
        else
        {
            node *newNode = new node;
            newNode->data = value;
            newNode->next = temp;
            prev->next = newNode;
        }
        current++;
    }

    void erase(int index)
    {
        if (index > current || index < 0)
        {
            cout << "out of bounds";
            exit(EXIT_FAILURE);
        }

        node *prev = nullptr;
        node *temp = head;

        for (int i = 0; i < index; ++i)
        {
            prev = temp;
            temp = temp->next;
        }

        if (prev == nullptr)
        {
            pop_front();
        }
        prev->next = temp->next;
        delete temp;
        current--;
    }

    int value_n_from_end(int n)
    {
        if (n > current || n < 0)
        {
            cout << "out of bounds";
            exit(EXIT_FAILURE);
        }

        node *temp = head;
        for (int i = 0; i < current - n; ++i)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    void reverse()
    {
        node *prev = nullptr;
        node *next = head;
        node *current;

        while (next != nullptr)
        {
            current = next;
            next = next->next;
            current->next = prev;
            prev = current;
        }

        head = prev;
    }

    void remove_value(int value)
    {
        if (empty())
        {
            cout << "empty";
            exit(EXIT_FAILURE);
        }

        node *prev = nullptr;
        node *target = head;
        
        while(target!=NULL){
            if(target->data == value){
                break;
            }
            prev = target;
            target= target->next;
        }

        if(target != NULL){
            prev->next =target->next;
            delete target;
            current--;
        }
    }
};

int main()
{
    SingleList list;

    // Test push_front
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    cout << "List after push_front (30, 20, 10): ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    // Test push_back
    list.push_back(40);
    list.push_back(50);
    cout << "List after push_back (40, 50): ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    // Test pop_front
    cout << "pop_front: " << list.pop_front() << endl;
    cout << "List after pop_front: ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    // Test pop_back
    cout << "pop_back: " << list.pop_back() << endl;
    cout << "List after pop_back: ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    // Test insert
    list.insert(1, 60);
    cout << "List after insert (60 at index 1): ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    // Test erase
    list.erase(1);
    cout << "List after erase (index 1): ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    // Test value_n_from_end
    cout << "value_n_from_end (n=1): " << list.value_n_from_end(1) << endl;

    // Test reverse
    list.reverse();
    cout << "List after reverse: ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    // Test remove_value
    list.remove_value(20);
    cout << "List after remove_value (10): ";
    for (int i = 0; i < list.size(); ++i)
    {
        cout << list.value_at(i) << " ";
    }
    cout << endl;

    return 0;
}