/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Liam Brew, Robert Schaedler III
 * Date        : March 2nd, 2020
 * Description : Solves the water jug puzzle using breadth-first search.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int jugs[3];
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) : jugs{_a, _b, _c}, directions{_directions}, parent{nullptr} {}

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << jugs[0] << ", " << jugs[1] << ", " << jugs[3] << ")";
        return oss.str();
    }

    bool is_equal(const State &state) const {
        for (int i = 0; i < 3; i++) {
            if (jugs[i] != state.jugs[i]) {
                return false;
            }
        }
        return true;
    }
};

State ***matrix;
const State *jug_sizes;

/* Returns the resulting state from a given pour (updates matrix), 
 * nullptr if resulting state already exists. */
State *pour(State *curr, const char from, const char to) {
    // Assignments.
    int from_curr = curr->jugs[from - 'A'];
    int to_curr = curr->jugs[to - 'A'];
    int to_cap = jug_sizes->jugs[to - 'A'];
    int delta;

    if (from_curr >= to_cap - to_curr) {  // 'from' will have excess after filling 'to'
        from_curr = from_curr - (to_cap - to_curr);
        delta = to_cap - to_curr;
        to_curr = to_cap;
    } else {  // 'from' will be empty after filling 'to'
        to_curr = to_curr + from_curr;
        delta = from_curr;
        from_curr = 0;
    }

    int a = curr->jugs[0], b = curr->jugs[1], c = curr->jugs[2];

    // set the new 'from' jug
    if (from == 'A') {
        a = from_curr;
    } else if (from == 'B') {
        b = from_curr;
    } else {
        c = from_curr;
    }

    // set the 'to' jug
    if (to == 'A') {
        a = to_curr;
    } else if (to == 'B') {
        b = to_curr;
    } else {
        c = to_curr;
    }

    if (matrix[a][b] == nullptr) {
        char buff[100];
        string plural = (delta > 1) ? "s " : " ";
        snprintf(buff, sizeof(buff), "Pour %d gallon%sfrom %c to %c. (%d, %d, %d)", delta, plural.c_str(), from, to, a, b, c);

        string str = buff;
        State *state = new State(a, b, c, str);
        state->parent = curr;
        matrix[a][b] = state;
        return state;
    }
    return nullptr;
}

State *bfs(State *initial_state, const State &goal) {
    queue<State *> q;
    State *curr = initial_state;
    State *temp;
    q.push(initial_state);
    char from, to;
    while (!q.empty() && !curr->is_equal(goal)) {
        curr = q.front();
        q.pop();

        // Generates combinations of 'A', 'B', 'C' in the correct pour order
        for (int i = 0; i < 3; i++) {
            to = 'A' + i;
            for (int j = 2; j >= 0; j--) {
                from = 'A' + j;

                if (from != to && (temp = pour(curr, from, to)) != nullptr) {
                    q.push(temp);
                    if (temp->is_equal(goal)) {
                        return temp;
                    }
                }
            }
        }
    }
    return (q.empty()) ? nullptr : curr;
}

void display_path(State *state) {
    if (state->parent != nullptr) {
        display_path(state->parent);
    }
    printf("%s\n", state->directions.c_str());
}

void clean_up() {
    for (int i = 0; i < jug_sizes->jugs[0] + 1; i++) {
        for (int j = 0; j < jug_sizes->jugs[1] + 1; j++) {
            if (matrix[i][j] != nullptr) {
                delete matrix[i][j];
            }
        }
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main(int argc, char *const argv[]) {
    if (argc != 7) {
        printf("Usage: %s <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>\n", argv[0]);
        return 0;
    }

    int vals[6];
    istringstream iss;

    char jug;
    string error_type;
    for (int i = 0; i < 6; i++) {
        jug = 'A' + (i % 3);

        error_type = (i < 3) ? "capacity" : "goal";
        iss.str(argv[i + 1]);
        if (!(iss >> vals[i]) || vals[i] < 0 || (i == 2 && vals[2] == 0)) {
            fprintf(stderr, "Error: Invalid %s '%s' for jug %c.\n", error_type.c_str(), argv[i + 1], jug);
            return 1;
        }
        iss.clear();
    }

    // Goal cannot exceed capacity of jug i
    for (int i = 0; i < 6; i++) {
        jug = 'A' + (i % 3);
        if (i > 2 && vals[i] > vals[i - 3]) {
            fprintf(stderr, "Error: Goal cannot exceed capacity of jug %c.\n", jug);
            return 1;
        }
    }

    // Total gallons in goal state must be equal to the capacity of jug C.
    if (vals[3] + vals[4] + vals[5] != vals[2]) {
        fprintf(stderr, "Error: Total gallons in goal state must be equal to the capacity of jug C.\n");
        return 1;
    }

    State goal(vals[3], vals[4], vals[5], "goal");

    jug_sizes = new State(vals[0], vals[1], vals[2], "jug sizes");

    matrix = new State **[vals[0] + 1];
    for (int i = 0; i < vals[0] + 1; i++) {
        matrix[i] = new State *[vals[1] + 1];
        for (int j = 0; j < vals[1] + 1; j++) {
            matrix[i][j] = nullptr;
        }
    }

    char buff[100];
    snprintf(buff, sizeof(buff), "Initial state. (0, 0, %d)", vals[2]);
    string str = buff;

    State *initial_s = new State(0, 0, vals[2], str);
    State *solution = bfs(initial_s, goal);

    if (solution == nullptr) {
        printf("No solution.");
    } else {
        display_path(solution);
    }

    clean_up();

    delete initial_s;
    delete jug_sizes;

    return 0;
}
