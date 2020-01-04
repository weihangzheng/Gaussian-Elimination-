#include <iostream>
#include <vector>
using namespace std;
typedef vector<vector<double>> doublevect;

//displays matrix
void display(doublevect vect) {
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			if (j == vect[i].size() - 2)
				cout << vect[i][j] << "x" << j + 1 << " = ";
			else if (j == vect[i].size() - 1)
				cout << vect[i][j];
			else
				cout << vect[i][j] << "x" << j + 1 << " + ";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int size = 0;
	cout << "Enter size of n x n matrix (n variables and n equations): ";
	cin >> size;
	doublevect vect;
	vect.resize(size);

	//user input into matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size + 1; j++) {
			int number = 0;
			cout << "Enter integer: ";
			cin >> number;
			vect[i].push_back(number);
		}
		cout << endl;
	}
	display(vect);

	for (int i = 0; i < size; i++) {

		//interchange two rows if necessary, throw exception if all possible pivot elements are 0
		try {
			if (vect[i][i] == 0) {
				bool flag = true;
				for (int l = i + 1; l < size; l++) {
					if (vect[l][i] != 0) {
						for (int m = i; m < size + 1; m++) {
							int temp = vect[i][m];
							vect[i][m] = vect[l][m];
							vect[l][m] = temp;
						}
						flag = false;
						break;
					}
				}
				if (flag)
					throw std::runtime_error("");
			}
		}
		catch (...) {
			cout << "all possible pivot elements are 0" << endl;
			char y;
			cout << "enter y to try again: ";
			cin >> y;
			if (y == 'y')
				main();
		}
		display(vect);

		//replace rows by its sum with a multiple of pivot row
		for (int j = i + 1; j < size; j++) {
			if (vect[j][i] != 0) {
				double multiple = vect[j][i] / vect[i][i];
				for (int k = i; k < size + 1; k++)
					vect[j][k] -= (vect[i][k])*multiple;
			}
		}
		display(vect);
	}

	//solves and displays the variables of the equation
	vector<double> sol;
	sol.resize(size);
	double temp;
	for (int i = size - 1; i >= 0; i--) {
		temp = vect[i][size];
		for (int j = size - 1; j > i; j--)
			temp -= vect[i][j] * sol[j];
		sol[i] = temp / vect[i][i];
	}
	for (int i = size; i >= 1; i--)
		cout << "x" << i << " = " << sol[i - 1] << endl;

	char x;
	cout << "enter y to try again: ";
	cin >> x;
	if (x == 'y')
		main();

	return 0;
}
