#include <iostream>
using namespace std;

int main() {
    system("cls"); 

    int n;
    cout << "masukkan jumlah karyawan: "; cin >> n;

    int minGrup = 0; // penghitung karyawan yg tidak memiliki manajer langsung (p = -1)
    for (int i = 0; i < n; i++) {
        int p;
        cout << " ";
        cin >> p;

        if (p == -1)
            minGrup++; // jika p = -1, karyawan tidak memiliki manajer langsung
    }

    cout << minGrup << "\n";
    return 0;
}