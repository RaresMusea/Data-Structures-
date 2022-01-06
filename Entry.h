#pragma once
//Fisier Entry.h->Header file ce implementeaza clasa Entry, ce corespunde unei intrari in lista de tipul (linie, coloana, valoare).
//Aceasta clasa va fi mai departe utilizata in implementarea matricei rare (clasa SMatrix).

//Clasa generica Entry:
template <class T>
class Entry {
public:
	//Linia, coloana
	unsigned int row, col; 
	//valoarea
	T val;

	//Constructori:
	//Constructorul implicit
	Entry(){}

	//Constructorul inline de initializare
	Entry(unsigned int r, unsigned int c, T const& value) :row(r), col(c), val(value) {
		
		//Posibilitatea introducerii unei valori nule->Mesaj de eroare
		if (value == 0)
			cout << "Eroare! S-a incercat introducerea unei valori nule la linia " << row << " , coloana " << col << "!\n";
	}

	//Constructorul de copiere
	Entry(Entry<T> const& e) {
		
		if(e.val==0)
			//Posibilitatea introducerii unei valori nule->Mesaj de eroare
			cout << "Eroare! S-a incercat introducerea unei valori nule la linia " << row << " , coloana " << col << "!\n";
		
		val = e.val;
		col = e.col;
		row = e.row;
	}

	//Setter pentru stabilirea unei intrari de tipul (linie, coloana, valoare).
	void setVal(unsigned int row, unsigned int col, T const& v) {
		
		//Setare valori
		this->row = row;
		this->col = col;
		this->val = v;

		//Posibilitatea introducerii unei valori nule
		if(v==0.0)
			cout << "Eroare! S-a incercat introducerea unei valori nule la linia " << row << " , coloana " << col << "!\n";
	}


	//Metoda ce verifica daca valoarea aferenta unei intrari este sau nu nula
	bool isNull()const {
	
		return (val == 0.0);
	}

	//Metoda ce utilizeaza supraincarcarea operatorului mai mic pentru a stabili daca un triplet este mai mic sau nu decat altul din punct de vedere al valorilor linie-coloana
	bool operator < (Entry<T> const& e) {
		return ((row < e.row) || ((row == e.row) && (col < e.col)));
	}


	//Metoda ce utilizeaza supraincarcarea operatorului mai mic sau egal pentru a stabili daca un triplet este mai mic sau egal ori nu decat altul, din punct de vedere al valorilor linie-coloana
	bool operator<=(Entry<T> const& e)
	{
		return ((row < e.row) || ((row == e.row) && (col <= e.col)));
	}

	//Metoda ce utilizeaza supraincarcarea operatorului mai mare pentru a stabili daca un triplet este sau nu mai mare decat altul, din punct de vedere al valorilor linie-coloana
	bool operator>(Entry<T> const& e)
	{
		return ((row > e.row) || ((row == e.row) && (col > e.col)));
	}

	//Metoda ce utilizeaza supraincarcarea operatorului mai mare sau egal pentru a stabili daca un triplet este sau nu mai mare sau egal decat altul, din punct de vedere al valorilor linie-coloana
	bool operator>=(Entry<T> const& e)
	{
		return ((row > e.row) || ((row == e.row) && (col >= e.col)));
	}

	//Metoda ce utilizeaza supraincarcarea operatorului de egalitate pentru a stabili daca un triplet este sau nu mai mare decat un altul, din punct de vedere al numarului liniei si coloanei
	bool operator==(Entry<T> const& e)
	{
		return ((row == e.row) && (col == e.col));
	}

	//Metoda ce verifica daca doua intrari sunt sau nu identice
	bool eq(Entry<T> const& e)
	{
		return ((row == e.lin) && (col == e.col) && (val == e.val));
	}

	//Metoda ce foloseste supraincarcarea operatorului de atribuire in vederea copierii in obiectul entry curent a unui alt entry, pasat ca si parametru de intrare.
	Entry<T>& operator = (Entry<T> const& e) {
		
		//Posibilitatea introducerii unei valori nule
		if(e.val==0.0)
			cout << "Eroare! S-a incercat introducerea unei valori nule la linia " << row << " , coloana " << col << "!\n";
	
		//Copierea propriu-zisa:
		val = e.val;
		row = e.row;
		col = e.col;
	
		//Returnam valoarea obiectului curent
		return *this;
	}

};