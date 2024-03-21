#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 100

struct Car {
    char model[50];
    int year;
    float price;
};

int getUserChoice() {
    int choice;
    do {
        printf("\n============== MENU CAR MANAGEMENT ================\n");
        printf("| 1. Xem danh sach xe                             |\n");
        printf("| 2. Them xe                                      |\n");
        printf("| 3. Tim kiem xe                                  |\n");
        printf("| 4. Cap nhat thong tin xe                        |\n");
        printf("| 5. Xoa xe                                       |\n");
        printf("| 6. Luu danh sach xe vao tep tin                 |\n");
        printf("| 7. Tai danh sach xe tu tep tin                  |\n");
        printf("| 8. Thoat                                        |\n");
        printf("====================================================\n");
        printf("Chon mot lua chon (1-8): ");
        scanf("%d", &choice);
        getchar();  
        if (choice < 1 || choice > 8) {
            printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
    } while (choice < 1 || choice > 8);
    return choice;
}


void printCar(struct Car car) {
    printf("Model: %s\n", car.model);
    printf("Nam san xuat: %d\n", car.year);
    printf("Gia: %.2f\n", car.price);
}

void printCarList(struct Car cars[], int n) {
    printf("\nDanh sach xe:\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("Xe thu %d:\n", i + 1);
        printCar(cars[i]);
        printf("\n");
    }
}

void addCar(struct Car cars[], int *pn) {
    if (*pn >= MAX_CARS) {
        printf("Danh sach xe da day. Khong the them xe.\n");
        return;
    }

    struct Car newCar;
    printf("\nNhap thong tin ve xe:\n");
    printf("Nhap model: ");
    fgets(newCar.model, sizeof(newCar.model), stdin);
    newCar.model[strcspn(newCar.model, "\n")] = '\0';  
    printf("Nhap nam san xuat: ");
    scanf("%d", &newCar.year);
    printf("Nhap gia: ");
    scanf("%f", &newCar.price);
    getchar();  

    cars[*pn] = newCar;
    (*pn)++;
    printf("Them xe thanh cong.\n");
}

int searchCar(struct Car cars[], int n, char model[]) {
	int i;
    for (i = 0; i < n; i++) {
        if (strcmp(cars[i].model, model) == 0) {
            return i;
        }
    }
    return -1;
}

void updateCar(struct Car cars[], int n, char model[]) {
    int index = searchCar(cars, n, model);
    if (index == -1) {
        printf("Khong tim thay xe co model \"%s\".\n", model);
        return;
    }

    printf("\nCap nhat thong tin ve xe:\n");
    printf("Nhap model moi: ");
    fgets(cars[index].model, sizeof(cars[index].model), stdin);
    cars[index].model[strcspn(cars[index].model, "\n")] = '\0'; 
    printf("Nhap nam san xuat moi: ");
    scanf("%d", &cars[index].year);
    printf("Nhap gia moi: ");
    scanf("%f", &cars[index].price);
    getchar();  // Ð?c ký t? newline t? l?nh scanf tru?c dó

    printf("Cap nhat thong tin xe thanh cong.\n");
}

void removeCar(struct Car cars[], int *pn, char model[]) {
    int index = searchCar(cars, *pn, model);
    if (index == -1) {
        printf("Khong tim thay xe co model \"%s\".\n", model);
        return;
    }
    int i;
    for (i = index; i < *pn - 1; i++) {
        cars[i] = cars[i + 1];
    }
    (*pn)--;
    printf("Xoa xe thanh cong.\n");
}

void saveToFile(struct Car cars[], int n) {
    FILE *file = fopen("car_list.txt", "w");
    if (file == NULL) {
        printf("Khong the mo tep tin de luu tru danh sach xe.\n");
        return;
    }
    int i;
    for ( i = 0; i < n; i++) {
        fprintf(file, "%s\n", cars[i].model);
        fprintf(file, "%d\n", cars[i].year);
        fprintf(file, "%.2f\n", cars[i].price);
    }

    fclose(file);
    printf("Luu danh sach xe vao tep tin thanh cong.\n");
}

int loadFromFile(struct Car cars[], int *pn)
{FILE *file = fopen("car_list.txt", "r");
    if (file == NULL) {
        printf("Khong the mo tep tin de tai danh sach xe.\n");
        return 0;
    }

    *pn = 0;
    while (*pn < MAX_CARS && fscanf(file, "%s", cars[*pn].model) == 1) {
        fscanf(file, "%d", &cars[*pn].year);
        fscanf(file, "%f", &cars[*pn].price);
        (*pn)++;
    }

    fclose(file);
    printf("Tai danh sach xe tu tep tin thanh cong.\n");
    return 1;
}

int main() {
    struct Car cars[MAX_CARS];
    int carCount = 0;

    int choice;
    do {
        choice = getUserChoice();

        switch (choice) {
            case 1:
                printCarList(cars, carCount);
                break;
            case 2:
                addCar(cars, &carCount);
                break;
            case 3: {
                char model[50];
                printf("\nNhap model xe can tim: ");
                fgets(model, sizeof(model), stdin);
                model[strcspn(model, "\n")] = '\0'; 
                int index = searchCar(cars, carCount, model);
                if (index == -1) {
                    printf("Khong tim thay xe co model \"%s\".\n", model);
                } else {
                    printf("\nThong tin ve xe co model \"%s\":\n", model);
                    printCar(cars[index]);
                }
                break;
            }
            case 4: {
                char model[50];
                printf("\nNhap model xe can cap nhat: ");
                fgets(model, sizeof(model), stdin);
                model[strcspn(model, "\n")] = '\0';  
                updateCar(cars, carCount, model);
                break;
            }
            case 5: {
                char model[50];
                printf("\nNhap model xe can xoa: ");
                fgets(model, sizeof(model), stdin);
                model[strcspn(model, "\n")] = '\0';
                removeCar(cars, &carCount, model);
                break;
            }
            case 6:
                saveToFile(cars, carCount);
                break;
            case 7:
                if (loadFromFile(cars, &carCount)) {
                    printCarList(cars, carCount);
                }
                break;
            case 8:
                printf("Tam biet.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 8);

    return 0;
}


