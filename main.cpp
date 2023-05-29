#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct fio {
    string surname;
    string name;
    string otchestvo;
};

struct score {
    int B[5];
    float avg;
};

struct student {
    struct fio fio;
    string group;
    struct score score;

};

string delete_n(string str) {
    str.erase(str.end() - 1);
    return str;
}


struct node {
    node *next;
    node *prev;
    struct student student;
};


node *make_stak(string file) {
    node *created = NULL, *prev = NULL, *first = NULL, *last = NULL;
    ifstream rfile;
    int count = 0, current_index = 0;
    float sum = 0;
    rfile.open(file);
    if (rfile) {
        rfile >> count;
        if (count) {
            while (current_index < count) {
                prev = created;
                sum = 0;
                created = new node;
                if (!first) {
                    first = created;
                }
                rfile >> created->student.fio.name;
                rfile >> created->student.fio.surname;
                rfile >> created->student.fio.otchestvo;
                rfile >> created->student.group;
                created->student.group = created->student.group;
                for (int i = 0; i < 5; i++) {
                    rfile >> created->student.score.B[i];
                    sum += created->student.score.B[i];
                }
                created->student.score.avg = sum / 5;
                created->prev = prev;
                if (first != created) {
                    prev->next = created;
                }
                current_index++;
            }
            created->next = first;
            first->prev = created;
        }
    }
    return first;
}

void delete_node(node *first){
    node *temp, *cur=first;
    while(cur && cur->next!=first){
        temp = cur;
        cur = cur->next;
        delete temp;
    }
    cout << "Memory cleared\n";
}

void print_node(node *first) {
    node *cur;
    cur = first;
    cout << "Nodes list\n";
    while (cur && cur->next != first) {
        cout << cur->student.fio.surname << ' ' << cur->student.fio.name << ' ' << cur->student.score.avg << '\n';
        cur = cur->next;
    }
    if (cur)
        cout << cur->student.fio.surname << ' ' << cur->student.fio.name << ' ' << cur->student.score.avg << '\n';

}


node *form_new_stak(node *lst) {
    float score;
    node *created = NULL, *first = NULL, *cur, *next = NULL;
    cout << "¬ведите средний балл:\n";
    cin >> score;
    cur = lst;
    while (cur->next != lst) {
        if (cur->student.score.avg < score) {
            next = created;
            created = new node;
            created->student = cur->student;
            created->next = next;
        }
        cur = cur->next;
    }
    if (cur->student.score.avg < score) {
        next = created;
        created = new node;
        created->student = cur->student;
        created->next = next;
    }
    return created;
}

void write_to_file(string file, node *lst) {
    ofstream wfile;
    node *cur;
    wfile.open(file);
    cur = lst;
    while (cur) {
        wfile << cur->student.fio.name << ' ' << cur->student.fio.surname << ' ' << cur->student.fio.otchestvo << ' '
              << cur->student.group << '\n';
        wfile << cur->student.score.avg << '\n';
        cur = cur->next;
    }

}


int main() {
    setlocale(LC_ALL, "Russian");
    string file;
    node *list, *new_list;
    cout << "¬ведите название входного файла:\n";
    cin >> file;
    list = make_stak(file);
    if (list) {
        print_node(list);
        new_list = form_new_stak(list);
        cout << "¬ведите название выходного файла:\n";
        cin >> file;
        print_node(new_list);
        if(!new_list) cout << "—писок пустой";
        write_to_file(file, new_list);
        delete_node(new_list);
        delete_node(list);
    } else {
        cout << "‘айл пустой или отсутвует";
    }

    return 0;
}
