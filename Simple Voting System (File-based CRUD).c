#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTERS 1000
#define FILE_NAME "votes.txt"
#define MAX_CANDIDATES 3

typedef struct {
    char studentID[20];
    char candidate[50];
} Voter;

Voter voters[MAX_VOTERS];
int voterCount = 0;

const char* candidates[MAX_CANDIDATES] = {
    "Alice Santos",
    "Bryan Cruz",
    "Carla Reyes"
};

// 🔍 Load votes from file
void loadVotes() {
    FILE* file = fopen(FILE_NAME, "r");
    if (!file) return;

    voterCount = 0;
    while (fscanf(file, "%[^|]|%[^\n]\n", voters[voterCount].studentID, voters[voterCount].candidate) == 2) {
        voterCount++;
    }

    fclose(file);
}

// 💾 Save votes to file
void saveVotes() {
    FILE* file = fopen(FILE_NAME, "w");
    for (int i = 0; i < voterCount; i++) {
        fprintf(file, "%s|%s\n", voters[i].studentID, voters[i].candidate);
    }
    fclose(file);
}

// ✅ Check if Student ID already voted
int hasVoted(char* id) {
    for (int i = 0; i < voterCount; i++) {
        if (strcmp(voters[i].studentID, id) == 0) return i;
    }
    return -1;
}

// ➕ Register and vote
void registerAndVote() {
    char id[20];
    int choice;

    loadVotes();
    printf("Enter Student ID: ");
    scanf("%s", id);

    if (hasVoted(id) != -1) {
        printf("Error: You have already voted.\n");
        return;
    }

    printf("Candidates:\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%d. %s\n", i + 1, candidates[i]);
    }

    printf("Enter Candidate Number: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_CANDIDATES) {
        printf("Error: Invalid candidate number.\n");
        return;
    }

    strcpy(voters[voterCount].studentID, id);
    strcpy(voters[voterCount].candidate, candidates[choice - 1]);
    voterCount++;

    saveVotes();
    printf("Vote successfully recorded for %s!\n", candidates[choice - 1]);
}

// 📋 Admin: View all votes
void viewAllVotes() {
    loadVotes();
    printf("\nStudent ID      Candidate\n------------------------------\n");
    for (int i = 0; i < voterCount; i++) {
        printf("%-15s %s\n", voters[i].studentID, voters[i].candidate);
    }
}

// ✏️ Admin: Update vote
void updateVote() {
    char id[20];
    int choice;

    loadVotes();
    printf("Enter Student ID to update: ");
    scanf("%s", id);

    int index = hasVoted(id);
    if (index == -1) {
        printf("Error: Voter not found.\n");
        return;
    }

    printf("Candidates:\n");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%d. %s\n", i + 1, candidates[i]);
    }

    printf("Enter new Candidate Number: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_CANDIDATES) {
        printf("Error: Invalid candidate number.\n");
        return;
    }

    strcpy(voters[index].candidate, candidates[choice - 1]);
    saveVotes();
    printf("Vote updated successfully!\n");
}

// ❌ Admin: Delete voter record
void deleteVoter() {
    char id[20];
    loadVotes();
    printf("Enter Student ID to delete: ");
    scanf("%s", id);

    int index = hasVoted(id);
    if (index == -1) {
        printf("Error: Voter not found.\n");
        return;
    }

    for (int i = index; i < voterCount - 1; i++) {
        voters[i] = voters[i + 1];
    }
    voterCount--;

    saveVotes();
    printf("Voter record deleted successfully!\n");
}

// 🗳️ Admin: Display election results
void displayResults() {
    loadVotes();
    int counts[MAX_CANDIDATES] = {0};

    for (int i = 0; i < voterCount; i++) {
        for (int j = 0; j < MAX_CANDIDATES; j++) {
            if (strcmp(voters[i].candidate, candidates[j]) == 0) {
                counts[j]++;
            }
        }
    }

    printf("\nElection Results:\n");
    int maxVotes = 0;
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        printf("%s : %d votes\n", candidates[i], counts[i]);
        if (counts[i] > maxVotes) maxVotes = counts[i];
    }

    printf("-----------------------------\nWinner(s): ");
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        if (counts[i] == maxVotes) {
            printf("%s ", candidates[i]);
        }
    }
    printf("\n");
}

// 🔐 Admin menu
void adminMenu() {
    int choice;
    do {
        printf("\nAdmin Menu:\n");
        printf("1. View All Votes\n");
        printf("2. Update Vote\n");
        printf("3. Delete Voter Record\n");
        printf("4. Display Election Results\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewAllVotes(); break;
            case 2: updateVote(); break;
            case 3: deleteVoter(); break;
            case 4: displayResults(); break;
        }
    } while (choice != 5);
}

// 📌 Main menu
int main() {
    int choice;
    do {
        printf("\nWelcome to the Voting System\n");
        printf("1. Register & Vote\n");
        printf("2. Admin Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerAndVote(); break;
            case 2: adminMenu(); break;
        }
    } while (choice != 3);

    return 0;
}