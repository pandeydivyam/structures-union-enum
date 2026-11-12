// Structures - 2
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
#define TOL 0.0001f

typedef struct {
    int id;
    float width, height, area, perimeter;
} Rectangle;

void calculate_area(Rectangle *r) {
    r->area = r->width * r->height;
    r->perimeter = 2 * (r->width + r->height);
}

Rectangle* create_rectangle_array(int n) {
    return malloc(n * sizeof(Rectangle));
}

int valid(float x) {
    return x > 0 && x <= 1e15f;
}

int find(Rectangle *r, int n, int id) {
    for (int i = 0; i < n; i++)
        if (r[i].id == id) return i;
    return -1;
}

void display_rectangles(Rectangle *r, int n) {
    if (!n) { printf("Empty list\n"); return; }
    for (int i = 0; i < n; i++)
        printf("ID:%d W:%.2f H:%.2f Area:%.2f Perimeter:%.2f %s\n",
        r[i].id, r[i].width, r[i].height, r[i].area, r[i].perimeter,
        (r[i].width > r[i].height ? r[i].width-r[i].height :
        r[i].height-r[i].width) <= TOL * (r[i].width > r[i].height ?
        r[i].width : r[i].height) ? "Square" : "Non-square");
}

void add_rectangle(Rectangle **r, int *n, int *cap) {
    int id; float w, h;
    if (*n == MAX) { printf("Full\n"); return; }
    printf("Enter ID, width, height: ");
    if (scanf("%d%f%f", &id, &w, &h) != 3 ||
        id <= 0 || find(*r, *n, id) != -1 || !valid(w) || !valid(h)) {
        printf("Invalid input\n"); return;
    }
    if (*n == *cap) {
        int c = *cap * 2 > MAX ? MAX : *cap * 2;
        Rectangle *t = realloc(*r, c * sizeof(Rectangle));
        if (!t) { printf("Allocation failed\n"); return; }
        *r = t; *cap = c;
    }
    (*r)[*n] = (Rectangle){id, w, h};
    calculate_area(&(*r)[(*n)++]);
}

void search_rectangle(Rectangle *r, int n) {
    int id;
    printf("Enter ID: ");
    if (scanf("%d", &id) != 1) return;
    int i = find(r, n, id);
    if (i == -1) printf("Not found\n");
    else display_rectangles(&r[i], 1);
}

void update_rectangle(Rectangle *r, int n) {
    int id; float w, h;
    printf("Enter ID: ");
    if (scanf("%d", &id) != 1) return;
    int i = find(r, n, id);
    if (i == -1) { printf("Not found\n"); return; }
    printf("Enter new width and height: ");
    if (scanf("%f%f", &w, &h) != 2 || !valid(w) || !valid(h)) {
        printf("Invalid dimensions\n"); return;
    }
    r[i].width = w; r[i].height = h;
    calculate_area(&r[i]);
}

void delete_rectangle(Rectangle *r, int *n) {
    int id;
    printf("Enter ID: ");
    if (scanf("%d", &id) != 1) return;
    int i = find(r, *n, id);
    if (i == -1) { printf("Not found\n"); return; }
    for (; i < *n-1; i++) r[i] = r[i+1];
    (*n)--;
}

void statistics(Rectangle *r, int n) {
    if (!n) { printf("Empty list\n"); return; }
    float total = 0; int max = 0, min = 0;
    for (int i = 0; i < n; i++) {
        total += r[i].area;
        if (r[i].area > r[max].area) max = i;
        if (r[i].area < r[min].area) min = i;
    }
    printf("Largest: ID %d Area %.2f\nSmallest: ID %d Area %.2f\nTotal: %.2f\nAverage: %.2f\n",
    r[max].id, r[max].area, r[min].id, r[min].area, total, total/n);
}

void sort_rectangles(Rectangle *r, int n) {
    Rectangle *t = create_rectangle_array(n);
    if (!t) { printf("Allocation failed\n"); return; }
    for (int i = 0; i < n; i++) t[i] = r[i];
    for (int i = 1; i < n; i++) {
        Rectangle x = t[i]; int j = i-1;
        while (j >= 0 && (t[j].area > x.area ||
              (t[j].area == x.area && t[j].id > x.id)))
            t[j+1] = t[j--];
        t[j+1] = x;
    }
    display_rectangles(t, n);
    free(t);
}

void filter_rectangles(Rectangle *r, int n) {
    float x; int found = 0;
    printf("Enter area threshold: ");
    if (scanf("%f", &x) != 1 || !(x >= 0)) return;
    for (int i = 0; i < n; i++)
        if (r[i].area > x) display_rectangles(&r[i], ++found);
    if (!found) printf("No matching rectangles\n");
}

int main() {
    int n, cap, ch;
    printf("Enter number of rectangles (1-1000): ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) return 1;
    cap = n;
    Rectangle *r = create_rectangle_array(cap);
    if (!r) return 1;

    for (int i = 0; i < n; i++) {
        int id; float w, h;
        printf("Enter ID, width, height: ");
        if (scanf("%d%f%f", &id, &w, &h) != 3 ||
            id <= 0 || find(r, i, id) != -1 || !valid(w) || !valid(h)) {
            printf("Invalid input\n"); i--; continue;
        }
        r[i] = (Rectangle){id, w, h};
        calculate_area(&r[i]);
    }

    do {
        printf("\n1.Add 2.Display 3.Search 4.Update 5.Delete\n6.Statistics 7.Sort 8.Filter 0.Exit\n");
        if (scanf("%d", &ch) != 1) break;
        switch (ch) {
            case 1: add_rectangle(&r, &n, &cap); break;
            case 2: display_rectangles(r, n); break;
            case 3: search_rectangle(r, n); break;
            case 4: update_rectangle(r, n); break;
            case 5: delete_rectangle(r, &n); break;
            case 6: statistics(r, n); break;
            case 7: sort_rectangles(r, n); break;
            case 8: filter_rectangles(r, n); break;
        }
    } while (ch != 0);

    free(r);
    return 0;
}
