

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <time.h> 
#include <thread>
#include <chrono>

using namespace std;

void show_result(clock_t start, clock_t end, pair<int, int> res, vector<int>& v);
void swap(int& a, int& b) {
    //if (a == b) return;
    a += b;
    b = a - b;
    a -= b;
}
void save_states(string s, float time, int n) {
    ofstream f(s, ios_base::app);
    f << n << " " << time << endl;
    f.close();
}

pair<int, int> buble(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n - i; j++) {
            res.first++;
            if (v[j] < v[j - 1]) {
                res.second++;
                swap(v[j], v[j - 1]);
            }
        }
    }
    return res;
}
pair<int, int> buble_with_flag(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        bool flag = 0;
        for (int j = 1; j < n - i; ++j) {
            ++res.first;
            if (v[j] < v[j - 1]) {
                flag = 1;
                ++res.second;
                swap(v[j], v[j - 1]);
            }
        }
        if (!flag)
            break;
    }
    return res;
}
pair<int, int> shaker(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0)
            for (int j = 1 + i / 2; j < n - i / 2; ++j) {
                ++res.first;
                if (v[j] < v[j - 1]) {
                    res.second++;
                    swap(v[j], v[j - 1]);
                }
            }
        else
            for (int j = n - i / 2 - 2 ; j >= i / 2 + 1; --j) {
                ++res.first;
                if (v[j] < v[j - 1]) {
                    ++res.second;
                    swap(v[j], v[j - 1]);
                }
            }
    }
    return res;
}
pair<int, int> shaker_with_flag(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    for (int i = 0; i < n; i++) {
        bool flag = 0;
        
        if (i % 2 == 0)
            for (int j = 1 + i / 2; j < n - i / 2; j++) {
                res.first++;
                if (v[j] < v[j - 1]) {
                    flag = 1;
                    res.second++;
                    swap(v[j], v[j - 1]);
                }
            }
        else
            for (int j = n - i / 2 - 2; j >= 1 + i / 2; j--) {
                res.first++;
                if (v[j] < v[j - 1]) {
                    flag = 1;
                    res.second++;
                    swap(v[j], v[j - 1]);
                }
            }
        if (!flag)
            break;
    }
    return res;
}
pair<int, int> inserts(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    for (int i = 1; i < n; i++) {
        for (int j = i; j >= 1; j--) {
            res.first++;
            if (v[j] < v[j - 1]) {
                res.second++;
                swap(v[j], v[j - 1]);
            }
            else
                break;
        }
    }
    return res;
}
pair<int, int> shell(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    vector<int> steps{203,105, 5,3,1};

    for (auto step : steps) {
        for (int i = step; i < n; i++) {
            for (int j = i - step; j >= 0; j -= step) {
                res.first++;
                if (v[j] > v[j + step]) {
                    res.second++;
                    /*int temp = v[j + step];
                    v[j + step] = v[j];
                    v[j] = temp;*/
                    swap(v[j + step], v[j]);
                }
                else
                    break;
            }
        }
    }
    return res;
}
pair<int, int> mergers(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    queue<queue<int>> q;
    for (auto i : v) {
        queue<int> temp;
        temp.push(i);
        q.push(temp);
    }
    res.second += n;
    while (q.size() > 1) {
        auto q1 = q.front();
        q.pop();
        auto q2 = q.front();
        q.pop();
        queue<int> q3;
        while (!q1.empty() && !q2.empty()) {
            res.first++;
            res.second++;
            if (q1.front() < q2.front()) {
                q3.push(q1.front());
                q1.pop();
            }
            else {
                q3.push(q2.front());
                q2.pop();
            }
        }
        while (!q1.empty()) {
            res.second++;
            q3.push(q1.front());
            q1.pop();
        }
        while (!q2.empty()) {
            res.second++;
            q3.push(q2.front());
            q2.pop();
        }
        q.push(q3);
    }
    v.clear();
    while (!q.front().empty()) {
        v.push_back(q.front().front());
        q.front().pop();
    }
    return res;
}
pair<int, int> qsort(vector<int>& v, int l, int r) {
    auto res = make_pair(0, 0);
    int temp_r = r, temp_l = l;
   /* cout << l << " " << r << " " << endl;
    for (auto i : v) cout << i << " ";
    cout << endl;*/
    if (r - l <= 0)return res;
    else if (r - l == 1) {
        res.first++;
        if (v[l] > v[r]) {
            swap(v[l], v[r]);
            res.second++;
        }
        return res;
    }
    l++;
    int temp = v[temp_l];
    v[temp_l] = v[(temp_l + temp_r) / 2];
    v[(temp_l + temp_r) / 2] = temp;
    res.second++;
    for (; l <= r; l++) {
        int cnt = 0;
        while (r >= l && v[l] > v[temp_l]) {
            cnt++;
            temp = v[l];
            v[l] = v[r];
            v[r] = temp;
            //swap(v[l], v[r]);
           /* if (v[l] == 0 || v[r] == 0) {
                cout << l << " " << r << " " << endl;
            }*/
            r--;
        }
        res.first += cnt + 1;
        res.second += cnt;
    }
    temp = v[temp_l];
    v[temp_l] = v[r];
    v[r] = temp;
    //swap(v[temp_l], v[r]);
    res.second++;
    auto res1 = qsort(v, temp_l, r - 1);
    auto res2 = qsort(v, r + 1, temp_r);
    res.first += res1.first + res2.first;
    res.second += res1.second + res2.second;
    return res;
}
pair<int, int> heap_sort(vector<int>& v) {
    auto res = make_pair(0, 0);
    int n = v.size();
    for (int i = n; i >= 2; --i) {
        res.first++;
        if (v[i - 1] > v[i / 2 - 1]) {
            res.second++;
            swap(v[i - 1], v[i / 2 - 1]);
            int cur = i;
            int cnt = 0;
            while (cur * 2 - 1 < n) {
                ++cnt;
                res.first++;
                if (cur * 2 < n) {
                    res.first += 2;
                    if (v[cur-1] < v[cur * 2-1] || v[cur-1] < v[cur * 2]) {
                        res.first++;
                        if (v[cur * 2-1] > v[cur * 2]) {
                            res.second++;
                            swap(v[cur-1], v[cur * 2-1]);
                            cur *= 2;
                        }
                        else {
                            res.second++;
                            swap(v[cur-1], v[cur * 2]);
                            cur *= 2;
                            ++cur;
                        }
                    }
                    else
                        break;  
                }
                else {
                    res.first++;
                    if (v[cur-1] < v[cur * 2-1]) {
                        res.second++;
                        swap(v[cur-1], v[cur * 2-1]);
                        
                    }
                    cur *= 2;
                }
            }
            res.first += cnt;
            res.first++;
        }
    }
    /*for (auto i : v) cout << i << " ";
    cout << endl;*/
    int temp_n = n;
    while(n > 1) {
        /*for (auto i : v) cout << i << " ";
        cout << endl;*/
        swap(v[0], v[--n]);
        int cur = 1;
        int cnt = 0;
        while (cur * 2 - 1 < n) {
            ++cnt;
            res.first++;
            if (cur * 2 < n) {
                res.first += 2;
                if (v[cur - 1] < v[cur * 2 - 1] || v[cur - 1] < v[cur * 2]) {
                    res.first++;
                    if (v[cur * 2 - 1] > v[cur * 2]) {
                        res.second++;
                        swap(v[cur - 1], v[cur * 2 - 1]);
                        cur *= 2;
                    }
                    else {
                        res.second++;
                        swap(v[cur - 1], v[cur * 2]);
                        cur *= 2;
                        ++cur;
                    }
                }
                else
                    break;
            }
            else {
                res.first++;
                if (v[cur - 1] < v[cur * 2 - 1]) {
                    res.second++;
                    swap(v[cur - 1], v[cur * 2 - 1]);
                }
                cur *= 2;
            }
        }
        res.first += cnt;
        res.first++;
    }
    /*for (auto i : v) cout << i << " ";
    cout << endl;*/
    return res;
}
bool is_sorted(vector<int>& v) {
    for (int i = 1; i < v.size(); i++)
        if (v[i] < v[i - 1])
            return 0;
    return 1;
}
int find_misstake(vector<int>& v) {
    for (int i = 1; i < v.size(); i++)
        if (v[i] < v[i - 1])
            return v[i];
    return 0;
}
void read_arr(ifstream& f, vector<int>& v) {
    int n;
    v.clear();
    f >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) f >> v[i];
}
void check_sorts(string s) {
    ifstream f(s);
    if (!f.is_open()) {
        char err_msg[256];
        strerror_s(err_msg, errno);
        printf("Error message: %s\n", err_msg);
        f.close();
        return;
    }
    vector<int> v, temp;
    read_arr(f, v);
    f.close();
    temp = v;
    //for (auto i : v) cout << i << " ";
    //cout << endl;
    //v = { -5153, -2734, -6035, 9289, 8422, 9562 ,-8346, -3130, 6240, 6942 };
    v = temp;
    cout << "Сортировка пузырьком ";
    clock_t start = clock();
    auto res = buble(v);
    clock_t end = clock();
    show_result(start, end, res, v);

    v = temp;
    start = clock();
    cout << "Сортировка пузырьком с флагом ";
    res = buble_with_flag(v);
    end = clock();
    show_result(start, end, res, v);

    v = temp;
    cout << "Сортировка шейкером ";
    start = clock();
    res = shaker(v);
    end = clock();
    show_result(start, end, res, v);

    v = temp;
    cout << "Сортировка шейкером с флагом ";
    start = clock();
    res = shaker_with_flag(v);
    end = clock();
    show_result(start, end, res, v);

    v = temp;
    start = clock();
    cout << "Сортировка вставками ";
    res = inserts(v);
    end = clock();
    show_result(start, end, res, v);


    v = temp;
    start = clock();
    cout << "Сортировка шела ";
    res = shell(v);
    end = clock();
    show_result(start, end, res, v);

    v = temp;
    start = clock();
    cout << "Сортировка слияниями ";
    res = mergers(v);
    end = clock();
    show_result(start, end, res, v);

    v = temp;
    start = clock();
    cout << "Сортировка Быстрая ";
    res = qsort(v, 0, v.size() - 1);
    end = clock();
    show_result(start, end, res, v);

    v = temp;
    start = clock();
    cout << "Сортировка кучей ";
    res = heap_sort(v);
    end = clock();
    show_result(start, end, res, v);
    cout << "---------------------------------------------------------------------+" << endl;
    //for (auto i : v) cout << i << " ";
}
void show_result(clock_t start, clock_t end, pair<int, int> res, vector<int>& v) {
    cout.precision(5);
    if (is_sorted(v)) {
        cout << "OK" << endl;
        cout << res.first << " сравнений " << res.second << " перестановок " << (double)(end - start) / CLOCKS_PER_SEC << " секунд" << endl << endl;
    }
    else {
        cout << "error" << endl;
        cout << find_misstake(v) << endl;
        for (auto i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

}
void test_arrays() {
    vector<int> names{ 100, 1000, 10000 };
    for (auto i : names) {
        cout << "Проверка на массиве длинной " << i << endl;
        check_sorts(to_string(i) + ".txt");
        cout << "Проверка на обратно упорядоченном массиве длинной " << i << endl;
        check_sorts(to_string(i) + "_b.txt");
        cout << "Проверка на массиве длинной " << i << " с энтропией 10%" << endl;
        check_sorts(to_string(i) + "_10.txt");
    }
}

int main(int argc, char* argv[])
{
    /*vector<int> v;
    ifstream f("100.txt");
    read_arr(f, v);
    f.close();
    heap_sort(v);
    cout << find_misstake(v);*/
    //system("tree");
    ios_base::sync_with_stdio(false);
    cout.tie(0);
    setlocale(LC_ALL, "Russian");
    test_arrays();
    //big_big_test();
    return 0;
}


