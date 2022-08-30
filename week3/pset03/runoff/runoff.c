#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
int first_non_eliminated_candidate(int voter);
int count_non_eliminated_candidates(void);
int find_candidate(string name);
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}


int find_candidate(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    int position = find_candidate(name);
    if (position == -1)
    {
        return false;
    }

    preferences[voter][rank] = position;
    return true;
}

int first_non_eliminated_candidate(int voter)
{
    for (int i = 0; i < candidate_count; i++)
        if (!candidates[preferences[voter][i]].eliminated)
        {
            return i;
        }
    return -1;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int voter = 0; voter < voter_count; voter++)
    {
        int first_non_eliminated = first_non_eliminated_candidate(voter);

        if (!candidates[preferences[voter][first_non_eliminated]].eliminated)
        {
            candidates[preferences[voter][first_non_eliminated]].votes++;
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (voter_count / 2 < candidates[i].votes)
        {
            printf("winner: %s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int least_votes = candidates[0].votes;
    for (int i = 1; i < candidate_count; i++)
    {
        if (least_votes > candidates[i].votes && candidates[i].eliminated == false)
        {
            least_votes = candidates[i].votes;
        }
    }
    return least_votes;
}

int count_non_eliminated_candidates(void)
{
    int n = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
        {
            n++;
        }
    }
    return n;
}
// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int non_eliminated_candidates = count_non_eliminated_candidates();
    int equals_counter = 0;
    int mini = find_min();
    for (int i = 0; i < non_eliminated_candidates; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes == mini)
        {
            equals_counter++;
        }
    }

    if (equals_counter == non_eliminated_candidates)
    {
        return true;
    }

    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
}