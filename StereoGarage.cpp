#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include<queue>
#include<map>
using namespace std;


template <typename T>
void elem_swap(T& a, T& b) {
    T c = a;
    a = b;
    b = c;
}
class minimum_heap {
public:
    minimum_heap() {
        heap.clear();
        len = 0;
    }

    ~minimum_heap() {
        heap.clear();
    }

    void insert_value(int val) {
        if (len + 1 > heap.size()) {
            heap.push_back(val);
        }
        else {
            heap[len] = val;
        }
        ++len;
        up_adjust(len - 1);
    }

    int size() {
        return len;
    }

    int top() {
        return heap[0];
    }

    void clear() {
        len = 0;
    }

    void delete_value() {
        swap(heap[0], heap[len - 1]);
        --len;
        down_adjust(0);
    }

private:
    vector<int> heap;
    int len;

    void down_adjust(int pos) {
        while (2 * pos + 1 < len) {
            int left = pos * 2 + 1;
            int right = pos * 2 + 2;
            int minium = pos;
            if (left < len && heap[left] < heap[minium])
                minium = left;
            if (right < len && heap[right] < heap[minium])
                minium = right;
            if (minium != pos) {
                ::elem_swap(heap[pos], heap[minium]);
                pos = minium;
            }
            else {
                break;
            }
        }
    }

    void up_adjust(int pos) {
        if (pos >= len) return;
        while (pos > 0) {
            int father = (pos - 1) / 2;
            if (heap[father] > heap[pos]) {
                ::elem_swap(heap[father], heap[pos]);
                pos = father;
            }
            else {
                break;
            }
        }
    }
};

struct car {
    string id;
    int in_time;
    int out_time;
};

class parking_lot {
public:
    parking_lot() :car_base(NULL) {
        empty_pos.clear();
        car_info.clear();
    }

    ~parking_lot() {
        empty_pos.clear();
        delete[] car_base;
        car_base = NULL;
    }

    void run() {
        show();
        setting();
        for (int tem;;) {
            display_menu();
            cout << "������ѡ�";
            cin >> tem;
            switch (tem) {
            case 1:setting(); break;
            case 2:car_in(); break;
            case 3:car_out(); break;
            case 4:system("cls"); break;
            case 5:cout << "ллʹ��" << endl; return;
            }
        }
    }
private:
    const int row = 2;
    int coloum;
    int average;
    int number;
    int price;
    int total;
    minimum_heap empty_pos;
    map<string, int> car_info;
    car* car_base;

    void show() {//����ʼascii��ӭ����
        puts("");
        puts("************************************************");
        puts("************************************************");
        puts("**                                            **");
        puts("**  ****************************************  **");
        puts("**  ****************************************  **");
        puts("**  ****************************************  **");
        puts("**  ********��ӭ�������峵�⳵λ����*******  **");
        puts("**  ****************************************  **");
        puts("**  ****************************************  **");
        puts("**  ****************************************  **");
        puts("**                                            **");
        puts("************************************************");
        puts("************************************************");
        puts("");
    }

    void display_menu() {//�˵�
        puts("///////////////////�˵�/////////////////");
        puts("\t1.�������峵�������");
        puts("\t2.���복��");
        puts("\t3.�뿪����");
        puts("\t4.����");
        puts("\t5.�뿪");
        puts("////////////////////////////////////////");
    }

    bool empty() {
        return empty_pos.size() == total;
    }

    void setting() {
        cout << "������˫��ѭ�����峵���������";
        cin >> coloum;
        cout << "������˫��ѭ�����峵���������";
        cin >> number;
        cout << "������˫��ѭ�����峵��ļ۸�/Сʱ��";
        cin >> price;
        average = row * coloum - 1;
        total = average * number;
        empty_pos.clear();
        for (int i = 0; i < total; ++i)
            empty_pos.insert_value(i + 1);
        if (car_base != NULL) {
            delete[] car_base;
            car_base = NULL;
        }
        car_base = new car[total];
    }

    void car_in() {
        if (empty_pos.size() == 0) {
            cout << "���󣺳�������" << endl;
            return;
        }
        int tem = empty_pos.top();
        empty_pos.delete_value();
        cout << "�뵽��" << tem << "��λ�ã���" << (tem - 1) / average + 1 << "����ͣ��." << endl;
        cout << "�����복�ƺţ�";
        cin >> car_base[tem - 1].id;
        car_base[tem - 1].in_time = (int)time(0);
        car_info[car_base[tem - 1].id] = tem;
        return;
    }

    void car_out() {
        if (empty_pos.size() == total) {
            cout << "���󣺳����޳�" << endl;
            return;
        }
        string id;
        int tem;
        cout << "�����복�ƺţ�";
        cin >> id;
        if (car_info.count(id) == 0) {
            cout << "����ͣ�������޴˳�." << endl;
            return;
        }
        else {
            tem = car_info[id];
            car_base[tem - 1].out_time = (int)time(0);
            cout << "��" << tem << "��λ�õĳ�����." << endl;
            calculate(car_base[tem - 1]);
            empty_pos.insert_value(tem);
        }
    }

    void calculate(const car& tem) {
        //cout<<tem.out_time<<' '<<tem.in_time<<endl;
        int t = tem.out_time - tem.in_time;
        int h = t / 3600;
        int m = (t - h * 3600) / 60;
        int s = t % 60;
        int money = (h + (m > 0 || s > 0)) * price;
        cout << "�ó���ͣ��" << h << "ʱ" <<
            m << "��" <<
            s << "�룬������" <<
            money << "Ԫ" << endl;
    }
};

void test_heap() {// test minimum_heap
    minimum_heap a;
    priority_queue<int, vector<int>, greater<int> > b;
    srand(time(0));
    for (int i = 0; i < 10; ++i) {
        int t = rand() % 1000;
        cout << i << endl;
        a.insert_value(t);
        b.push(t);
    }

    while (b.size()) {
        cout << b.top() << ' ';
        b.pop();
    }
    cout << endl;
    while (a.size()) {
        cout << a.top() << ' ';
        a.delete_value();
    }
    cout << endl;
}

int main() {
    //test_heap();
    parking_lot a;
    a.run();
    return 0;
}
