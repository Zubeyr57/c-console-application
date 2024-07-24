#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#define maxNlength 50
#define maxDlength 50

using namespace std;

class Student {
    public:

    int id;
    char name[maxNlength];
    char surname[maxNlength];
    int bDate;
    char department[maxDlength];
    int room;
    int bed;

};

class Node{
    public:
       string item;
       Node* link;
       Node(){ item = ""; link = NULL; }
};

class Stack {
    public:
        void push(string);
        string pop();
        Stack(){ Stop = NULL; }
    private :
        Node* Stop;
};

void Stack::push(string Sitem){
    Node* newNode = new Node;
    newNode-> item = Sitem;
    newNode-> link = Stop;
    Stop = newNode;
};

string Stack::pop(){
    if (Stop != NULL){
        Node* delNode = Stop;
        Stop = delNode->link;
        string popitem = delNode->item;
        delete delNode;
        return popitem;
    }
    return ""; // stack boşsa boş string döndür
}

int doluluk_kontrol(int id, int room, int bed) {
    ifstream file("students.txt");
    if (!file) {
        cout << "Dosya bulunamadi veya acilamadi." << endl;
        exit(1);
    }

    Student student;
    while (file >> student.id >> student.name >> student.surname >> student.bDate >> student.department >> student.room >> student.bed) {
        if (student.id == id || (student.room == room && student.bed == bed)) {
            file.close();
            return 1; // ID veya Oda ve Yatak zaten var
        }
    }

    file.close();
    return 0; // ID veya Oda ve Yatak yok
}

void dosyaya_kayit_ekle(int id) {
    ofstream file("students.txt", ios::app);
    Student student;

    while (1) {
        if (doluluk_kontrol(student.id, student.room, student.bed)) {
            cout << endl << id << " No'lu ogrenci zaten kayitli. Tekrar girin." << endl << endl;
            cout << "Numarasi: ";
            cin >> student.id;
        } else {
            break;
        }
    }

    cout << "Adi: ";
    cin >> student.name;
    cout << "Soyadi: ";
    cin >> student.surname;
    cout << "Dogum yili: ";
    cin >> student.bDate;
    cout << "Bolumu: ";
    cin >> student.department;

    while (1) {
        cout << "Oda numarasi: ";
        cin >> student.room;
        cout << "Yatak numarasi: ";
        cin >> student.bed;
        if (doluluk_kontrol(student.id, student.room, student.bed)) {
            cout << endl << student.room << " No'lu Oda ve " << student.bed << " No'lu Yatak dolu. tekrar girin." << endl << endl;
        } else if (student.room < 1 || student.room > 10 || student.bed < 1 || student.bed > 3) {
            cout << endl << "Gecersiz oda veya yatak numarasi. tekrar girin." << endl << endl;
        } else {
            break;
        }
    }

    file << student.id << " " << student.name << " " << student.surname << " " << student.bDate << " " << student.department << " " << student.room << " " << student.bed << endl;

    cout << "Ogrenci basarili bir sekilde kaydedildi" << endl << endl;
    file.close();
}

void kayit_listele() {
    ifstream file("students.txt");
    if (!file) {
        cout << "Dosya bulunamadi veya acilamadi." << endl;
        exit(1);
    }

    Student student;

    cout << "-----------------------------" << endl;
    cout << "----- Ogrenci kayitlari -----" << endl;
    cout << "-----------------------------" << endl << endl;

    while (file >> student.id >> student.name >> student.surname >> student.bDate >> student.department >> student.room >> student.bed) {
        cout << "Numarasi: " << student.id << ", Adi: " << student.name << " " << student.surname << ", Dogum yili: " << student.bDate << ", Bolumu: " << student.department << ", Odasi: " << student.room << ", Yatagi: " << student.bed << endl;
        cout << "---------------------------------------------------------------------------------------------------" << endl;
    }

    cout << endl << endl << endl;
    file.close();
}

void arama() {
    ifstream file("students.txt");
    if (!file) {
        cout << "Dosya bulunamadi veya acilamadi." << endl;
        exit(1);
    }
    

    int secim;
    int search_Id;
    char search_name[maxNlength];
    char search_Dep[maxDlength];
    int search_Room;
    Stack isimStack;
    string isim;
    string popIsim;

    Student student;

    while (1) {
        
        cout << "1. Id ile ogrenci arama" << endl;
        cout << "2. Ismi ile ogrenci arama" << endl;
        cout << "3. Oda numarasi ile Ogrenci arama" << endl;
        cout << "4. Bolum adi ile ogrenci arama" << endl;
        cout << "5. Son aranan degerler" << endl;
        cout << "6. Ana menü";
        cout << "Seciminizi yapin: ";
        cin >> secim;

        file.clear();
        file.seekg(0);
        int found = 0;

        switch (secim) {
            case 1:
                system("cls");
                cout << "Aranacak ogrencinin Numarasini girin: ";
                cin >> search_Id;
                isimStack.push("Id: " + to_string(search_Id));
                break;

            case 2:
                system("cls");
                cout << "Aranacak ogrencinin Adini girin: ";
                cin >> search_name;
                isimStack.push(search_name);
                break;

            case 3:
                system("cls");
                cout << "Aranacak ogrencinin oda Numarasini girin: ";
                cin >> search_Room;
                isimStack.push("Oda: " + to_string(search_Room));
                break;

            case 4:
                system("cls");
                cout << "Aranacak ogrencinin Bolumunu girin: ";
                cin >> search_Dep;
                isimStack.push(search_Dep);
                break;

            case 5:
                system("cls");
                cout << "En son aranan degerler: " << endl;
                while ((popIsim = isimStack.pop()) != "") {
                    cout << popIsim << endl;
                    }
                return;

            case 6:
                system("cls");
                return;

            default:
                cout << "Gecersiz secim. Tekrar deneyin." << endl;
                continue;
        }
        while (file >> student.id >> student.name >> student.surname >> student.bDate >> student.department >> student.room >> student.bed) {
            if ((secim == 1 && student.id == search_Id) ||
                (secim == 2 && strstr(student.name, search_name)) ||
                (secim == 3 && student.room == search_Room) ||
                (secim == 4 && strstr(student.department, search_Dep))) {

                cout << "ID: " << student.id << ", Ismi: " << student.name << " " << student.surname << ", Dogum yili: " << student.bDate << ", Bolumu: " << student.department << ", Odasi: " << student.room << ", Yatagi: " << student.bed << endl;
                cout << "--------------------------------------------------" << endl;
                found = 1;
            }
        }
        if (!found) {
            cout << endl << "-------------------" << endl;
            cout << "Ogrenci bulunamadi." << endl;
            cout << "-------------------" << endl << endl;
        }
    }
    file.close();
}

void id_ile_sil(int id) {
    ifstream file("students.txt");
    if (!file) {
        cout << "Dosya bulunamadi veya acilamadi." << endl;
        exit(1);
    }

    ofstream tempFile("temp.txt");

    if (!tempFile) {
        cout << "Gecici dosya olusturulamadi veya acilamadi." << endl;
        exit(1);
    }
    Student student;

    int found = 0;

    while (file >> student.id >> student.name >> student.surname >> student.bDate >> student.department >> student.room >> student.bed) {
        if (student.id == id) {
            found = 1;
            cout << endl << "ID: " << student.id << ", Ismi: " << student.name << " " << student.surname << ", Dogum yili: " << student.bDate << ", Bolumu: " << student.department << ", Oda: " << student.room << ", Yatak: " << student.bed << " silindi." << endl << endl;
        } else {
            tempFile << student.id << " " << student.name << " " << student.surname << " " << student.bDate << " " << student.department << " " << student.room << " " << student.bed << endl;
        }
    }

    if (!found) {
        cout << "Ogrenci bulunamadi." << endl;
    }

    file.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");
}

void guncelleme(int id) {
    id_ile_sil(id);
    cout << "-----------------------------------" << endl;
    cout << "Ogrencinin yeni bilgilerini girin: " << endl;
    dosyaya_kayit_ekle(id);
}

void oda_durumunu_goster(int durum) {
    ifstream file("students.txt");
    if (!file) {
        cout << "Dosya bulunamadi veya acilamadi." << endl;
        exit(1);
    }

    cout << "-----------------------------" << endl;
    cout << "------- Oda Durumu ----------" << endl;
    cout << "-----------------------------" << endl << endl;

    int found = 0;
    int oda[10][3] = {0};

    Student student;

    while (file >> student.id >> student.name >> student.surname >> student.bDate >> student.department >> student.room >> student.bed) {
        if (durum == 0 && student.id != 0) {
            oda[student.room - 1][student.bed - 1] = 1;
        } else if (durum == 1 && student.id != 0) {
            cout << "Oda " << student.room << ", Yatak " << student.bed << " - Ogrenci ID: " << student.id << endl;
        }
    }

    file.close();
    if (durum == 0) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 3; j++) {
                if (!oda[i][j]) {
                    cout << "Oda " << i + 1 << ", Yatak " << j + 1 << " - Bos" << endl;
                }
            }
        }
    }
}

int main() {

    int secim;
    int id;
    int durum;

    while (1) {

        Student student;

        cout << "1. Yeni ogrenci kaydi" << endl;
        cout << "2. Ogrenci bilgilerini guncelle" << endl;
        cout << "3. Ogrenci sil" << endl;
        cout << "4. Ogrenci kayitlarini listele" << endl;
        cout << "5. Ogrenci ara" << endl;
        cout << "6. Oda durumu goster" << endl;
        cout << "7. Cikis" << endl;
        cout << "Seciminizi yapin: ";
        cin >> secim;

        switch (secim) {
            case 1:
                system("cls");
                cout << "Numarasi: ";
                cin >> student.id;
                dosyaya_kayit_ekle(student.id);
                break;

            case 2:
                system("cls");
                cout << "Guncellenecek ogrencinin Numarasini girin: ";
                cin >> id;
                guncelleme(id);
                break;

            case 3:
                system("cls");
                cout << "Silinecek ogrencinin Numarasini girin: ";
                cin >> id;
                id_ile_sil(id);
                break;

            case 4:
                system("cls");
                kayit_listele();
                break;

            case 5:
                system("cls");
                arama();
                break;

            case 6:
                system("cls");
                cout << "Bos oda (0), Dolu oda (1): ";
                cin >> durum;
                oda_durumunu_goster(durum);
                break;

            case 7:
                cout << "Programdan cikiliyor." << endl;
                exit(0);

            default:
                system("cls");
                cout << "Gecersiz secim. Tekrar deneyin." << endl;
        }
    }
    return 0;
}