#include <iostream>
#include <algorithm> 
#include <math.h>    
using namespace std;

int main() {
    system("cls");

    int n;
    cout << "masukkan jumlah kursi tersedia: "; cin >> n;
    int kursi[n];   
    for (int i = 0; i < n; i++) {
        cin >> kursi[i];
    }
    sort(kursi, kursi + n);

    int m;
    cout << "masukkan nomor kursi yang dicari: "; cin >> m;
    int low = 0, high = n - 1, flag = 0;
    int posisi;
    float posisi1;

    cout << "\nHasil: ";
    if (flag == 1) {
        cout << "Nomor kursi " << m << " ditemukan!" << endl;
        cout << "Posisi Index: " << posisi << endl;
        cout << "Nomor Kursi: " << kursi[posisi] << endl;
    }
    else {
        cout << "Nomor kursi " << m << " tidak tersedia." << endl;
        cout << "\n=== Opsi Kursi Terdekat yang Tersedia ===" << endl;
        
        //mencari kursi terdekat sebelumnya
        int terdekatBefore = -1;
        for (int i = 0; i < n; i++) {
            if (kursi[i] < m) {
                terdekatBefore = i;
            } else {
                break;
            }
        }
        
        //mencari kursi terdekat sesudahnya
        int terdekatAfter = -1;
        for (int i = 0; i < n; i++) {
            if (kursi[i] > m) {
                terdekatAfter = i;
                break;
            }
        }
        
        //menampilkan opsi terdekat
        if (terdekatBefore != -1) {
            int selisih = m - kursi[terdekatBefore];
            cout << "Kursi " << kursi[terdekatBefore] << " (Index: " << terdekatBefore 
                 << ") - Selisih: " << selisih << " lebih kecil" << endl;
        }
        
        if (terdekatAfter != -1) {
            int selisih = kursi[terdekatAfter] - m;
            cout << "Kursi " << kursi[terdekatAfter] << " (Index: " << terdekatAfter 
                 << ") - Selisih: " << selisih << " lebih besar" << endl;
        }
        
        if (terdekatBefore == -1 && terdekatAfter == -1) {
            cout << "Tidak ada kursi tersedia!" << endl;
        }
    }
    return 0;
}