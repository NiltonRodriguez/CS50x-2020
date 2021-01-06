#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Check if the candidate name is valid.
    int get_index = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        // Find the index of the candidates.
        if (strcmp(candidates[i], name) == 0)
        {
            get_index = i;
        }
        // Update ranks[] of each voter with the candidate index.
        if (get_index > -1)
        {
            ranks[rank] = get_index;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Preferences array stores the number of voters who prefer i over j.
    // This function compares each element on the array with the ones on the right.
    for (int i = 0; i < candidate_count; i++)
    {
        // Update preferences array.
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iteration to compare a pair of candidates in both ways i-j and j-i. using preferences.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Store the winner pair.
            // Update the pair count to be the total of pairs.
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Apply a sorting algorithm. (Insertion sort)
    for (int i = 0; i < pair_count; i++)
    {
        pair to_sort = pairs[i];
        int j = i - 1;
        // Set the algorithm in decreasing order.
        while (j >= 0 && preferences[pairs[j].winner][pairs[j].loser] < preferences[to_sort.winner][to_sort.loser])
        {
            pairs[j + 1] = pairs[j];
            j--;
        }
        pairs[j + 1] = to_sort;
    }
    return;
}
// Function to check if there's a cycle between the candidates.
bool cycle_chk(int winner, int loser)
{
    // Store the loser of the pair to compare at the end of the iterarion.
    while (winner != -1 && winner != loser)
    {
        bool visited = false;
        // Iteration to check for a visited candidate.
        for (int i = 0; i < candidate_count; i++)
        {
            // If the winner candidate is locked, mark it as visited.
            // Change the Winner.
            if (locked[i][winner])
            {
                visited = true;
                winner = i;
            }
            if (!visited)
            {
                winner = -1;
            }
        }
        // If the winner of the iteration matches the stored loser a cycle is confirmed.
        if (winner == loser)
        {
            return true;
        }
    }
    // If the winner of the iteration don't match, there is no cycle.
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // Compare the winner and loser on each pair.
        locked[pairs[i].winner][pairs[i].loser] = false;
        // Check for a cycle between the candidates.
        // If there's no cycle add the edges to a locked graph.
        // If there's a cycle, skip.
        if (!cycle_chk(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // The winner is the source of the graph.
    // Iteration to find the source.
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // If the candidate is locked, skip.
            if (locked[j][i] == true)
            {
                source = false;
                break;
            }
        }
        // If a non locked candidate is found, that's the source.
        // When a source is found, print it as the winner of the election.
        if (source == true)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }

    return;
}

