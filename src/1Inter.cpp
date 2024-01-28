#include <bits/stdc++.h>
using namespace std;

const int MAX_ITERATIONS = 50;

class ACO {
public:
    ACO(int num_papers, int num_reviewers, int b, const vector<vector<int>>& reviewers_list)
        : num_papers(num_papers), num_reviewers(num_reviewers), b(b), reviewers_list(reviewers_list) {
        pheromone_matrix.resize(num_papers, vector<double>(num_reviewers, 1.0));
    }

    vector<vector<int>> solve() {
        vector<vector<int>> best_solution(num_papers, vector<int>(b, 0));
        double best_solution_quality = numeric_limits<double>::max();

        for (int iteration = 0; iteration < MAX_ITERATIONS; ++iteration) {
            vector<vector<int>> solutions;

            for (int ant = 0; ant < num_papers; ++ant) {
                vector<int> solution = generate_solution(ant);
                solutions.push_back(solution);

                double solution_quality = evaluate_solution(solution);
                if (solution_quality < best_solution_quality) {
                    best_solution_quality = solution_quality;
                    best_solution = solutions;
                }
            }

            update_pheromone(solutions);

            cout << "Iteration " << iteration + 1 << ": Best Solution Quality: " << best_solution_quality << endl;
        }

        return best_solution;
    }

private:
    int num_papers;
    int num_reviewers;
    int b;
    vector<vector<int>> reviewers_list;
    vector<vector<double>> pheromone_matrix;

    vector<int> generate_solution(int paper) {
    vector<int> solution(b, 0);
    vector<int> unassigned_reviewers = reviewers_list[paper];

    // Kiểm tra xem có đủ số lượng reviewers cho paper hay không
    if (unassigned_reviewers.size() < b) {
        cerr << "Not enough reviewers for paper " << paper + 1 << ". Exiting..." << endl;
        exit(EXIT_FAILURE);
    }

    random_shuffle(unassigned_reviewers.begin(), unassigned_reviewers.end());

    for (int i = 0; i < b; ++i) {
        solution[i] = unassigned_reviewers[i];
    }

    return solution;
}


    vector<double> calculate_probabilities(int paper, const vector<int>& unassigned_reviewers) {
        vector<double> probabilities;

        double total_pheromone = 0.0;
        for (int reviewer : unassigned_reviewers) {
            total_pheromone += pheromone_matrix[paper][reviewer - 1];
        }

        for (int reviewer : unassigned_reviewers) {
            double pheromone = pheromone_matrix[paper][reviewer - 1];
            double heuristic = 1.0 / (1.0 + evaluate_reviewer_load(reviewer, paper));
            double probability = (pheromone / total_pheromone) * heuristic;
            probabilities.push_back(probability);
        }

        return probabilities;
    }

    int select_reviewer(const vector<double>& probabilities) {
        double random_value = (double)rand() / RAND_MAX;
        double cumulative_probability = 0.0;

        for (int i = 0; i < probabilities.size(); ++i) {
            cumulative_probability += probabilities[i];
            if (random_value <= cumulative_probability) {
                return i;
            }
        }

        return probabilities.size() - 1;
    }

    double evaluate_reviewer_load(int reviewer, int paper) {
        return 0.0;
    }

    double evaluate_solution(const vector<int>& solution) {
        return accumulate(solution.begin(), solution.end(), 0.0);
    }

    void update_pheromone(const vector<vector<int>>& solutions) {
        for (const auto& solution : solutions) {
            double pheromone_increase = 1.0 / evaluate_solution(solution);

            for (int i = 0; i < b; ++i) {
                int paper = solution[i] - 1;
                int reviewer = reviewers_list[paper][i];
                pheromone_matrix[paper][reviewer - 1] += pheromone_increase;
            }
        }

        for (int paper = 0; paper < num_papers; ++paper) {
            for (int reviewer = 0; reviewer < num_reviewers; ++reviewer) {
                pheromone_matrix[paper][reviewer] *= 0.9;
            }
        }
    }
};

int main() {
    srand(time(0));

    int num_papers, num_reviewers, b;
    cout << "Enter the number of papers, reviewers, and b: ";
    cin >> num_papers >> num_reviewers >> b;

    vector<vector<int>> reviewers_list(num_papers);
    for (int i = 0; i < num_papers; ++i) {
        int k;
        cout << "Enter the number of reviewers for paper " << i + 1 << ": ";
        cin >> k;
        reviewers_list[i].resize(k);
        cout << "Enter the reviewers for paper " << i + 1 << ": ";
        for (int j = 0; j < k; ++j) {
            cin >> reviewers_list[i][j];
        }
    }

    ACO aco_solver(num_papers, num_reviewers, b, reviewers_list);
    vector<vector<int>> best_solution = aco_solver.solve();

    cout << "Final Best Solution:" << endl;
    for (int paper = 0; paper < num_papers; ++paper) {
        cout << b << " ";
        for (int reviewer = 0; reviewer < b; ++reviewer) {
            cout << best_solution[paper][reviewer] << " ";
        }
        cout << endl;
    }

    return 0;
}