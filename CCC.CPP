#include <stdio.h>
#include <string.h>

#define MAX 100

/* ---------- DATA TYPES ---------- */
typedef struct {
    char username[20];
    char password[20];
    char role[10];
} User;

typedef struct {
    int  id;
    char name[50];
    float marks;
} Student;

/* ---------- GLOBALS ---------- */
Student students[MAX];
int studentCount = 0;

/* ---------- STUDENT FUNCTIONS ---------- */
void displayStudents() {
    if (studentCount == 0) {
        printf("\nNo students available.\n");
        return;
    }
    printf("\nID\tNAME\tMARKS\n");
    for (int i = 0; i < studentCount; i++)
        printf("%d\t%s\t%.2f\n", students[i].id, students[i].name, students[i].marks);
}

void addStudent() {
    if (studentCount >= MAX) {
        printf("\nStudent list is full.\n");
        return;
    }
    Student s;
    printf("\nEnter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    students[studentCount++] = s;
    printf("\nStudent added successfully.\n");
}

int findStudentIndexById(int id) {
    for (int i = 0; i < studentCount; i++)
        if (students[i].id == id)
            return i;
    return -1;
}

void searchStudent() {
    int id;
    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    int idx = findStudentIndexById(id);
    if (idx == -1) {
        printf("\nStudent not found.\n");
    } else {
        printf("\nStudent found:\n");
        printf("ID: %d\nName: %s\nMarks: %.2f\n",
               students[idx].id, students[idx].name, students[idx].marks);
    }
}

void updateStudent() {
    int id;
    printf("\nEnter ID to update: ");
    scanf("%d", &id);

    int idx = findStudentIndexById(id);
    if (idx == -1) {
        printf("\nStudent not found.\n");
        return;
    }

    printf("Enter new Name: ");
    scanf("%s", students[idx].name);
    printf("Enter new Marks: ");
    scanf("%f", &students[idx].marks);

    printf("\nStudent updated successfully.\n");
}

void deleteStudent() {
    int id;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    int idx = findStudentIndexById(id);
    if (idx == -1) {
        printf("\nStudent not found.\n");
        return;
    }

    for (int i = idx; i < studentCount - 1; i++)
        students[i] = students[i + 1];

    studentCount--;
    printf("\nStudent deleted successfully.\n");
}

/* ---------- MENUS ---------- */
void adminMenu() {
    int ch;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Logout\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
        }
    } while (ch != 6);
}

void staffMenu() {
    int ch;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n2. Search\n3. Update\n4. Logout\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
        }
    } while (ch != 4);
}

void userMenu() {
    int ch;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n2. Search Student\n3. Logout\nEnter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
        }
    } while (ch != 3);
}

void guestMenu() {
    int ch;
    do {
        printf("\n===== GUEST MENU =====\n");
        printf("1. Display Students\n2. Logout\nEnter choice: ");
        scanf("%d", &ch);

        if (ch == 1) displayStudents();
    } while (ch != 2);
}

/* ---------- LOGIN ---------- */
int login(User users[], int n, User *logged) {
    char u[20], p[20];

    printf("\n===== LOGIN =====\n");
    printf("Username: ");
    scanf("%s", u);
    printf("Password: ");
    scanf("%s", p);

    for (int i = 0; i < n; i++)
        if (!strcmp(u, users[i].username) &&
            !strcmp(p, users[i].password)) {
            *logged = users[i];
            return 1;
        }

    return 0;
}

/* ---------- MAIN ---------- */
int main() {
    User users[] = {
        {"admin", "admin123", "ADMIN"},
        {"staff", "staff666", "STAFF"},
        {"guest", "guest111", "GUEST"},
        {"user",  "user123",  "USER"}
    };

    students[0]=(Student){1001,"Ajay",560};
    students[1]=(Student){1002,"Rahul",580};
    students[2]=(Student){1003,"Kiran",590};
    studentCount = 3;

    while (1) {
        User current;
        if (!login(users, 4, &current)) {
            printf("\nInvalid login. Try again.\n");
            continue;
        }

        printf("\nLogged in as: %s (%s)\n", current.username, current.role);

        if (!strcmp(current.role, "ADMIN")) adminMenu();
        else if (!strcmp(current.role, "STAFF")) staffMenu();
        else if (!strcmp(current.role, "USER")) userMenu();
        else guestMenu();
    }

    return 0;
}