#include "StackArray.h" //folosim instanta clasei StackArray pentru a reprezenta in memorie tijele

//Numar de bile pe fiecare tija
int n;

//Cteste de la tastatura numarul bilelor/al tijelor, si culoarea bilelor de pe fiecare tija
void readStacks(Array<StackArray<string>>&stacks) {
	

	cout << "Introduceti numarul de bile: ";
	cin >> n;

	stacks= (Array<StackArray<string>>(n + 1));

	string color;
	//Initializam toate stivele
	for (int i = 0; i < n; i++) {
		stacks[i] = StackArray<string>(n);
		if (i != n) {
			cout << "Ce culoare au bilele de pe tija " << i + 1 << " ?";
			cin >> color;
			for (int j = 0; j < n; j++)
				stacks[i].push(color);
		}
	}

	stacks[n] = StackArray<string>(n * n);
}


//Functie utilizata pentru afisarea tijelor
void displayStacks(Array<StackArray<string>>stacks) {

	cout << '\n';

	for (int i = 0; i < stacks.getSize(); i++) {
		cout << "Stiva " << i + 1 << ":\n";
		cout << stacks[i];
		cout << '\n';
	}
}

//Rezolva prblema propriu-zisa
string Solve(Array<StackArray<string>> &stacks) {

	//Sir de caractere in care vom stoca lista mutarilor
	string operations = "Lista mutarilor: \n";

	//Mutam cele n-1 bile de pe fiecare tija, pe tija auxiliara, in mod ,,asortat" (colorile sa difere) si adaugam in sirul operations operatiile efectuate la nivel de stiva

	for (int i=0; i <n; i++) {

		
		if (stacks[i].getCount() != 1) {
			stacks[n].push(stacks[i].getTop());
			operations += "S-a mutat bila de culoare " + stacks[i].getTop() +  ", de pe tija " + to_string(i + 1) + " pe tija " + to_string(n + 1)+".\n";
			stacks[i].pop();
		}

		//Candu ajungem la numarul de tije-1, reinitializam contorul
		if (i == n - 1) {
			i = -1;
		}

		if (stacks[n].getCount() == pow(n, 2) - n)
			break;
		
	}

	//Mutam pe fiecare tija cate o bila de culoare diferita
	for (int i = 0; i < n; i++) {
		
		//Valoarea unica din tija curenta, inaintea adaugarii bilelor
		string x = stacks[i].getTop();
		
		//Cat timp stiva auxiliara nu este goala, iar culoarea bilei din varful acesteia difera de culoarea bilei din varful tijei pe ca
		while (!stacks[n]. isEmpty() && stacks[n].getTop() != x) {
			stacks[i].push(stacks[n].getTop());
			operations += "S-a mutat bila de culoare " + stacks[n].getTop() + ", cu numarul " + ", de pe tija " + to_string(n+1) + " pe tija " + to_string(i+1) + ".\n";
			stacks[n].pop();
		}

	}

	return operations;
}

//Entry point 
int main() {

	Array<StackArray<string>>stacks;
	readStacks(stacks);
	//displayStacks(stacks);
	string result=Solve(stacks);
	displayStacks(stacks);
	cout << result;
	return 0;
}
