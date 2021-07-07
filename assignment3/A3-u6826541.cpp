#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
// Add additional libraries you need here

using namespace std;




pair<int,vector<vector<pair<int,int>>>> Maximun_Salary(int n, int b, vector<vector<int>> S_ij) {
	vector<vector<int>> MEMO(n + 1 ,vector<int>(b * 10 + 1));
	vector<vector<pair<int,int>>> Applicants(n + 1 ,vector<pair<int,int>>(b * 10 + 1));
	
	for (int i = 1; i < n + 1; i++) {
		for (int j = 10; j < b * 10 + 1; j = j + 1) {

            int parent_j                   = 0;
            int selected_Applicants_K      = 0;

			for (int k = 0; k < S_ij[i - 1].size(); k++) {
				
                int salary_of_k = S_ij[i - 1][k];
                int redundant_budget = ((j * 1000 - salary_of_k) / 1000);
				if (redundant_budget < 0) {
					continue;
				}
				int sub_best_budget  = MEMO[i - 1][redundant_budget];
    
                if (i == 1 && (j * 1000 >= salary_of_k)) {
                   if (MEMO[i][j] < sub_best_budget + salary_of_k) {
						MEMO[i][j]            = sub_best_budget + salary_of_k;
						selected_Applicants_K = k + 1;
					}	 
                }
				else if (sub_best_budget != 0 && (j * 1000 > salary_of_k) && sub_best_budget + salary_of_k <= j * 1000) {
					if (MEMO[i][j] < sub_best_budget + salary_of_k) {
						MEMO[i][j]            = sub_best_budget + salary_of_k;
						selected_Applicants_K = k + 1;
                        parent_j              = redundant_budget;
					}	
				} 
			}
            pair<int,int> select(selected_Applicants_K,parent_j);
            Applicants[i][j] = select;
		}
	}
    int cost = MEMO[n][b * 10];
    pair<int,vector<vector<pair<int,int>>>> answer(cost,Applicants);
    return answer;
}

vector<int> Find_Applicants(vector<vector<pair<int,int>>> Applicants, int n, int b) {
    vector<int> answer(n);
    int parent    = Applicants[n][b * 10].second;
    answer[n - 1] = Applicants[n][b * 10].first;

    for (int pos = n - 1 ; pos > 0; pos--) {
       answer[pos - 1] = Applicants[pos][parent].first;
       parent          = Applicants[pos][parent].second;
    }
    return answer;
}



int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } 
    else { 
		// Read input
		ifstream inFile(argv[1]);
		int B, n;
		inFile >> B >> n;

		vector<vector<int>> S_ij(n);
		int ki,s_ij;

		for (int i = 1; i <= n; i++) {
			inFile  >> ki;
			// Store the #applicants data
			vector<int> tmp(ki);
			S_ij[i - 1] = tmp;

			for (int j = 1; j <= ki ; j++) {
				inFile >> s_ij;
				// Store the salary of each applicant =
				S_ij[i - 1][j - 1] = s_ij * 1000;
			}
		}
		inFile.close();  		

		bool solExists;
		int totSalaries;
		vector<int> selApplicants;

		// Place your algorithm here
		// If you need to create a function, place the function above the main function
		// If there's a solution (i.e., solExists == True), the results of your algorithm 
		//		should be placed in variables totSalaries and selApplicants
		pair<int,vector<vector<pair<int,int>>>> answser = Maximun_Salary(n, B, S_ij);
		solExists = (answser.first != 0);
		selApplicants = Find_Applicants(answser.second, n, B);
		// Print output
		if (solExists) {
			cout << totSalaries << " ";
			for (int i = 0; i < n; i++) {
				cout << selApplicants[i] << " ";
			}
		}
		else {
			cout << "no solution";
		}
		cout << "\n";
    }

    return 0;
}
