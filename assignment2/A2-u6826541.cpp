#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <string>
// Add additional libraries you need here
using namespace std;

int RandomizedPartition (int a[],int p,int r) {	
	srand((unsigned)time(NULL));
	int pivot = rand() % (r - p + 1) + p;
	int tmp = a[pivot];
	a[pivot] = a[r];
	a[r] = tmp;

	int x = a[r];
	
	int i = p-1;
	for (int j = p;j < r;j++) {
		if(a[j] <= x) {
			i++;
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
		}		
	}	
	i++;
	tmp = a[i];
	a[i] = a[r];
	a[r] = tmp;	
	return i;
}

int RandomizedSelect (int a[],int p,int r,int i) {	
	if (p == r) {
		return a[p];
	}	
	int pivot_index = RandomizedPartition(a,p,r);	
	int i_smallest = pivot_index - p + 1;
	
	if (i_smallest == i) {
		return a[pivot_index];
	} else if (i < i_smallest) {
		return RandomizedSelect(a, p, pivot_index-1, i);
	} else {
		return RandomizedSelect(a, pivot_index+1, r, i-i_smallest);
	}		
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } 
    else { 
		// Read input
		ifstream inFile(argv[1]);
		int n, x, y;

		inFile >> n;

		int *all_Xs = new int[n];

		int *all_Ys = new int[n];

		for (int i = 0; i < n; i++) {
			inFile  >> x >> y;
			// Store x and y data
			all_Xs[i] = x;
			all_Ys[i] = y;
		}
		
		inFile.close();  		

		int xh, yh;
		// Place your algorithm here
		// If you need to create a function, place the function above the main function
		// The results of your algorithm should be placed in variable xh and yh
		xh = RandomizedSelect(all_Xs, 0, n - 1, (n + 1) / 2);
		delete [] all_Xs;
		yh = RandomizedSelect(all_Ys, 0, n - 1, (n + 1) / 2);
		delete [] all_Ys;
		
		// Print output
        cout << xh << " " << yh << "\n";
    }

    return 0;
}
