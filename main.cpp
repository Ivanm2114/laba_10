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
        while (current_index < count) {
            prev = created;
            created = new node;
            if (!first) {
                first = created;
            }
            rfile >> created->student.fio.name;
            rfile >> created->student.fio.surname;
            rfile >> created->student.fio.otchestvo;
            rfile >> created->student.group;
            created->student.group = delete_n(created->student.group);
            for (int i = 0; i < 5; i++) {
                rfile >> created->student.score.B[i];
                sum += created->student.score.B[i];
            }
            created->student.score.avg = sum / 5;
            created->prev = prev;
            if (first!=created) {
                prev->next = created;
            }
            current_index++;
        }
        created->next = first;
        first->prev = created;
    }
    return first;
}

void print_node(node *first) {
    node *cur;
    cur = first;
    cout << "Node queue\n";
    while (cur->next != first) {
        cout << cur->student.fio.surname << ' ' << cur->student.fio.name << '\n';
        cur=cur->next;
    }
    cout << cur->student.fio.surname << ' ' << cur->student.fio.name << '\n';

}

int main() {
    setlocale(LC_ALL, "Russian");
    string file;
    node *list;
      cin >> file;

    list = make_stak(file);
    print_node(list);
    return 0;
}
