#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

struct Ögrenci {
    char no[25];
    char isim[50];
    int vize;
    int final;
    double ort;
    struct Ögrenci* next;
};
typedef Ögrenci Node;

Node* ekle(Node* head)
{
    Node* ogr = (Node*)malloc(sizeof(Node));
    if (ogr == NULL) {
        printf("Bellek tahsisi başarısız!\n");
        return head;
    }

    printf("Ögrenci No (11 haneli) : ");
    fgets(ogr->no, sizeof(ogr->no), stdin);
    ogr->no[strcspn(ogr->no, "\n")] = 0;

    printf("Ögrenci İsmi : ");
    fgets(ogr->isim, sizeof(ogr->isim), stdin);
    ogr->isim[strcspn(ogr->isim, "\n")] = 1;

    printf("Ögrenci Vize Notu : ");
    scanf_s("%d", &ogr->vize);
    getchar();

    printf("Ögrenci Final Notu : ");
    scanf_s("%d", &ogr->final);
    getchar();

    ogr->ort = (ogr->vize * 0.4) + (ogr->final * 0.6);

    if (head == NULL) {
        head = ogr;
        head->next = NULL;
        printf("Liste Oluşturuldu. İlk Ögrenci Eklendi.\n");
    }
    else {
        ogr->next = head;
        head = ogr;
        printf("Ögrenci Eklendi.\n");
    }
    return head;
}

Node* Sil(Node* head)
{
    if (head == NULL) {
        printf("Liste Boş, Silinecek Ögrenci Yok\n");
        return head;
    }

    char ogrno[12];
    printf("Silmek İstediginiz Ögrencinin Numarasını Giriniz : ");
    fgets(ogrno, sizeof(ogrno), stdin);
    ogrno[strcspn(ogrno, "\n")] = 0;

    Node* temp = head;
    Node* root = NULL;

    if (strcmp(head->no, ogrno) == 0) {
        head = head->next;
        free(temp);
        printf("%s Numaralı Ögrenci Silindi.\n", ogrno);
        return head;
    }

    while (temp != NULL && strcmp(temp->no, ogrno) != 0) {
        root = temp;
        temp = temp->next;
    }

    if (temp != NULL) {
        root->next = temp->next;
        free(temp);
        printf("%s Numaralı Ögrenci Silindi.\n", ogrno);
    }
    else {
        printf("Ögrenci bulunamadı.\n");
    }

    return head;
}

Node* Yazdır(Node* head)
{
    system("cls");
    if (head == NULL) {
        printf("Liste Boş\n");
        return head;
    }

    Node* temp = head;
    while (temp != NULL) {
        printf("************************************************\n");
        printf("No : %s   İsim : %s    Vize : %d    Final : %d    Ortalama : %.2f \n", temp->no, temp->isim, temp->vize, temp->final, temp->ort);
        temp = temp->next;
    }
    return head;
}

Node* EnYükesekOrtalama(Node* head)
{
    system("cls");
    if (head == NULL) {
        printf("Liste Boş\n");
        return head;
    }

    double buyukort = head->ort;
    Node* Buyukdüğüm = head;

    Node* p = head;
    while (p != NULL) {
        if (buyukort < p->ort) {
            buyukort = p->ort;
            Buyukdüğüm = p;
        }
        p = p->next;
    }

    printf("En Yüksek Ortalaması Olan Ögrenci : \n");
    printf("No : %s \n", Buyukdüğüm->no);
    printf("İsim : %s \n", Buyukdüğüm->isim);
    printf("Final : %d \n", Buyukdüğüm->final);
    printf("Vize : %d \n", Buyukdüğüm->vize);
    printf("Ortalama : %.2f \n", Buyukdüğüm->ort);

    return head;
}

int main()
{
    SetConsoleOutputCP(65001);
    system("cls");

    int seçim;
    Node* head = NULL;

    while (1) {
        printf("\n********************** Tek Yönlü Doğrusal Bağlı Liste İle Öğrenci Kayıt Projesi **********************\n\n");
        printf("1--EKLE \n");
        printf("2--SİL \n");
        printf("3--YAZDIR \n");
        printf("4--EN YÜKSEK ORTALAMA BUL \n");
        printf("0--ÇIKIŞ \n");
        printf("Seçiminizi Yapınız [0-4]: ");
        scanf_s("%d", &seçim);
        getchar();

        switch (seçim) {
        case 1:
            head = ekle(head);
            break;
        case 2:
            head = Sil(head);
            break;
        case 3:
            head = Yazdır(head);
            break;
        case 4:
            head = EnYükesekOrtalama(head);
            break;
        case 0:
            exit(0);
        default:
            printf("Hatalı Seçim !!!\n");
        }
    }
}
