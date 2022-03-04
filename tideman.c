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
bool check_cycle(int check_winner, int loser);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // store candidate's index (i) in rank[ranking 0 = 1st, 1 = 2nd, etc]
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int candidate_winner_idx;
    int candidate_loser_idx;
    for (int i = 0; i < candidate_count; i++)
    {
        candidate_winner_idx = ranks[i];
        // check the ranks below (starting at the candidate ranked after candidate[i])
        for (int j = i + 1; j < candidate_count; j++)
        {
            candidate_loser_idx = ranks[j];
            preferences[candidate_winner_idx][candidate_loser_idx]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] == preferences[j][i])
            {
                // tied
            }
            else if (preferences[i][j] > preferences[j][i])
            {
                // not tied
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
                // note: there isn't a if statement checking for preferences[i][j] < preferences[j][i] because that would mean that there would be duplicate pairs
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength1;
    int strength2;
    pair temp;
    for (int i = 0; i < pair_count - 1; i++)
    {
        strength1 = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        strength2 = preferences[pairs[i + 1].winner][pairs[i + 1].loser] - preferences[pairs[i + 1].loser][pairs[i + 1].winner];
        if (strength1 < strength2)
        {
            // swap them
            temp = pairs[i];
            pairs[i] = pairs[i + 1];
            pairs[i + 1] = temp;
            i = 0;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // add edge from a to b so long as b doesn't point to something that points to a
    bool unlooped;
    //lock first pair
    locked[pairs[0].winner][pairs[0].loser] = true;
    //Process the rest of them
    for (int i = 1; i < pair_count; i++)
    {
        // check edging for loops
        if (check_cycle(pairs[i].winner, pairs[i].loser))
        {
            // cycle found
        }
        else
        {
            // no cycle
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool winner;
    // loop through pairs, if locked: add it to the count (a has __ wins, b has __ wins, etc)
    for (int i = 0; i < candidate_count; i++)
    {
        winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // if the [i] candidate lost, try the next one
            if (locked[j][i])
            {
                winner = false;
            }
        }
        if (winner)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

bool check_cycle(int check_winner, int loser)
{
    // loop through all pairs
    // if the loser is the winner (and locked), check all of those pairs
    // if any of the losers win against the winner return true --> a cycle will be created
    bool cycle = false;
    for (int i = 0; i < pair_count; i++)
    {
        if (pairs[i].winner == loser && locked[pairs[i].winner][pairs[i].loser])
        {
            if (pairs[i].loser == check_winner)
            {
                return true;
            }
            else
            {
                cycle = check_cycle(check_winner, pairs[i].loser);
                if (cycle)
                {
                    return true;
                }
            }
        }
    }
    return false;
}