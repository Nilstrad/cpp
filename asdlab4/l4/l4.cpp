#include <iostream>
#include <curses.h>
using namespace std;

struct tnode    //структура для дерева
{
    int field;//значение узла
    int number; // номер узла
    int levv; //уровень
    int nChildCount; // количество детей
    tnode* pChildren;
};
struct Node //структура для списка
{
    int val; //значение
    tnode* value; //значение 
    Node* next;
};
//функция проверки ввода данных
int Chek(int enter) {
    cin >> enter;
    while (true) {
        if (cin.fail())
        {
            cout << "Incorrect input. try again" << endl;
            cin.clear(); cin.ignore();
            cin >> enter;
        }
        else  return enter;
    }
}
//класс для списка
class List
{
public:
    Node* head = NULL; //"голова" связанного списка
public:
    List() //конструктор класса
    {
        head = NULL;
    }
    //метод, добавляющий новый узел в список
    void addNode(int zn)
    {
        Node* nd = new Node;
        nd->val = zn;
        nd->next = NULL;
        if (head == NULL) head = nd;
        else
        {
            Node* current = head;
            while (current->next != NULL)
                current = current->next;
            //предшествующий указывает на последний
            current->next = nd;
        }
    }
    void addNode1(tnode* zn)
    {
        Node* nd = new Node; //динамически создаем новый узел
        nd->value = zn;
        nd->next = NULL;
        if (head == NULL) head = nd;
        else
        {
            Node* current = head;
            while (current->next != NULL)
                current = current->next;
            //предшествующий указывает на последний
            current->next = nd;
        }
    }

    //метод,удаляющий элементы
    void Clear() {
        Node* tmp = head;
        Node* p;
        while (tmp != NULL) {
            p = tmp->next;
            delete tmp;
            tmp = p;
        }
        head = NULL;
    }
};

int n = 0;//переменная для пронумеровки узлов дерева
//класс, описывабщий дерево
class Tree
{
public:
    tnode* head = NULL;

    //метод, выводящий дерево на экран
    void treeprint(tnode* tree, int level) {
        if (tree != NULL)
        { //Пока не встретится пустой узел
            for (int i = 0; i < tree->nChildCount; i++)
            {
                treeprint(&tree->pChildren[i], level + 1);
            }
            for (int i = 0; i < level; i++) cout << "   ";
            cout << tree->field << endl;
        }
    }

    //метод, добавляющий элемент в дерево
    struct tnode* addnode(tnode** tree) {
        tnode* cur = *tree;
        if (cur == NULL)  // Если дерева нет, то формируем корень
        {
            cur = new tnode;
            cur->levv = 0;
        }
        cur->number = n++;

        cout << "Node # " << cur->number << "\nEnter the data ";
        cur->field = Chek(cur->field);
        cout << "Number of children ";
        int l = 0;
        l = Chek(l);
        if (l > 0)
        {
            cur->nChildCount = l;
            cur->pChildren = new tnode[l];
            for (int i = 0; i < l; i++)
            {
                tnode* current = &(cur->pChildren[i]);
                addnode(&current);
            }
        }
        else
        {
            cur->nChildCount = 0;
            cur->pChildren = NULL;
        }
        *tree = cur;
        return(*tree);
    }

    //метод, очищающий дерево
    void Clear(tnode* head)
    {
        tnode* tmp = head;
        tnode* p = NULL;
        while (tmp != NULL) {
            for (int i = 0; i < tmp->nChildCount; i++)
            {
                p = &head->pChildren[i];
                Clear(p);
            }
        }
        delete tmp;
        tmp = p;
        head = NULL;
    }
};
List list1;//список, хранящий увовни опреденного узла
List list2; //список, хранящий указатели на нужные узлы
int lev1, lev2; //уровени поиска
//функция, формирующая списки, описывающие каждый узел
void CreatingList(tnode* head)
{
    for (int i = 0; i < head->nChildCount; i++)
    {
        CreatingList(&head->pChildren[i]);
    }
    if (head->nChildCount == 0) list1.addNode(head->levv);
}
//функция, формирующая список с указателями на нужные узлы
void Result(tnode* head)
{
    for (int i = 0; i < head->nChildCount; i++)
    {
        Result(&head->pChildren[i]);
    }
    CreatingList(head);
    cout << endl;
    bool b = true;// переменная отвечающая за необходимость добавлять элемент в список
    Node* cur = list1.head;
    if ((cur->val >= lev1) && (cur->val <= lev2)) //если уровень лежит в заданном диапазоне
    {
        b = true;
        cur = cur->next;
    }
    else b = false;
    if (b == true) list2.addNode1(head);
    list1.Clear();
}
//функция, добавляющая номера уровней в дерево
struct tnode* CreatingLevel(tnode** head) {
    tnode* cur = *head;

    for (int i = 0; i < cur->nChildCount; i++)
    {
        tnode* current = &(cur->pChildren[i]);
        current->levv = (cur->levv + 1);
        CreatingLevel(&current);
    }
    return *head;
}

int main() {
    do {
        system("cls");
        Tree tree; //исходное дерево
        tree.addnode(&tree.head);
        CreatingLevel(&tree.head);
        tree.treeprint(tree.head, 0);
        cout << "Enter level 1:" << endl; //ввод диапазона высот
        lev1 = Chek(lev1);
        cout << "Enter level 2:" << endl;
        lev2 = Chek(lev2);
        Result(tree.head);
        Node* current;
        current = list2.head;
        if (current == NULL) cout << "Result no" << endl;
        else cout << "Result" << endl;
        while (current != NULL) {
            tree.treeprint(current->value, 0);
            current = current->next;
        }
        list2.Clear();
        n = 0;
        cin.ignore();
        cout << "Press any key to continue or esc to finish" << endl;
    } while (_getch() != 27);
    return 0;
}
