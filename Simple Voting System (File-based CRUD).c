#include <stdio.h>
#include <string.h>
#define MAX 1000

typedef struct { char id[20], vote[30]; } Voter;
Voter v[MAX]; int n;
char *cand[] = {"Alice Santos", "Bryan Cruz", "Carla Reyes"};

void load() {
    FILE *f = fopen("votes.txt", "r"); n = 0;
    if (!f) return;
    while (fscanf(f, "%[^|]|%[^\n]\n", v[n].id, v[n].vote) == 2) n++;
    fclose(f);
}

void save() {
    FILE *f = fopen("votes.txt", "w");
    for (int i = 0; i < n; i++)
        fprintf(f, "%s|%s\n", v[i].id, v[i].vote);
    fclose(f);
}

int exists(char *id) {
    for (int i = 0; i < n; i++)
        if (!strcmp(v[i].id, id)) return i;
    return -1;
}

void vote() {
    load(); Voter t;
    printf("Student ID: "); gets(t.id);
    if (exists(t.id) >= 0) { printf("Already voted.\n"); return; }
    printf("Candidates:\n1. %s\n2. %s\n3. %s\nChoose: ", cand[0], cand[1], cand[2]);
    int c; scanf("%d"); getchar();
    if (c < 1 || c > 3) { printf("Invalid.\n"); return; }
    strcpy(t.vote, cand[c - 1]);
    FILE *f = fopen("votes.txt", "a");
    fprintf(f, "%s|%s\n", t.id, t.vote);
    fclose(f);
    printf("Vote recorded for %s!\n", t.vote);
}

void view() {
    load(); if (!n) { printf("No votes.\n"); return; }
    for (int i = 0; i < n; i++)
        printf("%s -> %s\n", v[i].id, v[i].vote);
}

void update() {
    load(); char id[20]; printf("ID to update: "); gets(id);
    int i = exists(id);
    if (i < 0) { printf("Not found.\n"); return; }
    printf("New vote (1-3): "); int c; scanf("%d"); getchar();
    if (c < 1 || c > 3) { printf("Invalid.\n"); return; }
    strcpy(v[i].vote, cand[c - 1]); save(); printf("Updated!\n");
}

void del() {
    load(); char id[20]; printf("ID to delete: "); gets(id);
    int i = exists(id);
    if (i < 0) { printf("Not found.\n"); return; }
    for (int j = i; j < n - 1; j++) v[j] = v[j + 1];
    n--; save(); printf("Deleted!\n");
}

void results() {
    load(); int c[3] = {0};
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 3; j++)
            if (!strcmp(v[i].vote, cand[j])) c[j]++;
    printf("Election Results:\n");
    for (int i = 0; i < 3; i++)
        printf("%s : %d votes\n", cand[i], c[i]);
    int max = (c[0] > c[1]) ? ((c[0] > c[2]) ? 0 : 2) : ((c[1] > c[2]) ? 1 : 2);
    printf("Winner: %s\n", cand[max]);
}

void admin() {
    int ch;
    while (1) {
        printf("\nAdmin Menu:\n1.View 2.Update 3.Delete 4.Results 5.Exit\nChoose: ");
        scanf("%d"); getchar();
        if (ch == 1) view();
        else if (ch == 2) update();
        else if (ch == 3) del();
        else if (ch == 4) results();
        else break;
    }
}

int main() {
    int ch;
    while (1) {
        printf("\nVoting System\n1.Vote 2.Admin 3.Exit\nChoose: ");
        scanf("%d"); getchar();
        if (ch == 1) vote();
        else if (ch == 2) admin();
        else break;
    }
    return 0;
}