#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
const int L = 50, R = 11;

bool i_file(string& str, bool flag) {
	char buff;
	ifstream i_file;
	i_file.open("Ex.txt");
	if (!i_file.is_open()) {
		cout << "ошибка! не удалось открыть файл\n";
		return true;
	}
	while (!i_file.eof()) {
		i_file.get(buff);
		if (i_file.eof()) {
			break;
		}
		str += buff;
	}
	i_file.close();
	cout << str << endl;
	return true;
}

bool i_keyb(string& str, bool flag) {
	cin.clear();
	while (cin.get() != '\n');
	getline(cin, str);
	str += '.';
	cout << str << endl;
	return true;
}

char removeExtraChar(string &str) {
	for (int i = 0; i < str.length(); i++) {
		if ((str[i] == ' ') && (str[i + 1] == ' ')) {
			while (!((str[i] == ' ') && (str[i + 1] != ' '))) {
				str.erase(str.begin() + i);
			}
		}
		if ((str[i] == '!') && (str[i + 1] == '!')) {
			while (!((str[i] == '!') && (str[i + 1] != '!'))) {
				str.erase(str.begin() + i);
			}
		}
		if ((str[i] == '?') && (str[i + 1] == '?')) {
			while (!((str[i] == '?') && (str[i + 1] != '?'))) {
				str.erase(str.begin() + i);
			}
		}
		if ((str[i] == ':') && (str[i + 1] == ':')) {
			while (!((str[i] == ':') && (str[i + 1] != ':'))) {
				str.erase(str.begin() + i);
			}
		}
		if ((str[i] == ';') && (str[i + 1] == ';')) {
			while (!((str[i] == ';') && (str[i + 1] != ';'))) {
				str.erase(str.begin() + i);
			}
		}
		if ((str[i] == '"') && (str[i + 1] == '"')) {
			while (!((str[i] == '"') && (str[i + 1] != '"'))) {
				str.erase(str.begin() + i);
			}
		}
		if ((str[i] == ',') && (str[i + 1] == ',')) {
			while (!((str[i] == ',') && (str[i + 1] != ','))) {
				str.erase(str.begin() + i);
			}
		}
		if (str[i] == '.' && i != str.length() - 1) {
			string buff;
			buff = str[i];
			int j = i + 1;
			while (str[j] == '.') {
				buff += str[j];
				j++;
			}
			if (buff.length() < 3) {
				while (!((str[i] == '.') && (str[i + 1] != '.'))) {
					str.erase(str.begin() + i);
				}
			}
			else {
				while (str[i + 3] == '.') {
					str.erase(str.begin() + i);
				}
				i += 3;
			}
		}
	}
	return 0;
}

bool isLetter(char x) {
	return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
}

void caseCorrect(string& str) {
	str[0] = toupper(str[0]);
	for (int i = 1; i < str.length(); i++) {
		if (isLetter(str[i])) {
			while (isLetter(str[i])) {
				str[i] = tolower(str[i]);
				i++;
			}
		}
	}
}

void divIntoWords(string &str, char words[L][R], int *tab) {
	for (int l = 0, r = 0, i = 0, i1 = 0; i < str.length(); i++) {
		if (str[i] != ' ' && str[i] != '.' && str[i] != ',' && r < R) {
			words[l][r] = str[i];
			r++;
		}
		else {
			if (str[i + 1] != '.' && str[i + 1] != ' ') {
				int row = R - r - 1;
				tab[i1] = row;
				i1++;
				row = 0;
				words[l][r] = '\0';
				l++;
				r = 0;
			}
		}
		if (i == str.length() - 1) {
			while (l < L) {
				words[l][0] = '\0';
				l++;
			}
		}
	}
}

void bubbleSort(char words[L][R]) {
	for (int i = 0; i < L; i++) {
		for (int l = 0; l < L - 1; l++) {
			if (words[l][0] > words[l + 1][0]) {
				swap(words[l], words[l + 1]);
			}
		}
	}

}

void alphabet(string &str) {
	char words[L][R];
	int tab[L];
	divIntoWords(str, words, tab);
	words[0][0] = tolower(str[0]);
	bubbleSort(words);
	for (int i = 0; i < L; i++) {
		if (words[i][0] != '\0') {
			cout << words[i] << ' ';
		}
	}
}

void columns(string& str, int *tab) {
	char words[L][R];
	int k = 0;
	divIntoWords(str, words, tab);
	for (int i = 0; i < L; i++) {
		if (words[i][0] != '\0') {
			k++;
		}
	}
	int j = 0, i = 0;
	if (k % 2 == 0) {
		for (; i < L; i++, j++) {
			if (words[i][0] != '\0') {
				cout << setw(tab[j]) << ' ' << words[i] << '\t';
				j++;
				if (words[i + 1][0] != '\0') {
					cout << setw(tab[j]) << ' ' << words[i + 1] << '\n';
					i++;
				}
				else {
					while (words[i + 1][0] == '\0') i++;
					cout << setw(tab[j]) << ' ' << words[i] << '\n';
				}
			}
		}
	}
	else {
		for (; i < L; i++, j++) {
			if (words[i][0] != '\0') {
				cout << setw(tab[j]) << ' ' << words[i] << '\t';
				j++;
				if (words[i + 1][0] != '\0') {
					cout << setw(tab[j]) << ' ' << words[i + 1] << '\t';
					i++;
					j++;
				}
				else {
					while (words[i + 1][0] == '\0') i++;
					cout << setw(tab[j]) << ' ' << words[i] << '\t';
					j++;
					i++;
				}
				if (words[i + 2][0] != '\0') {
					cout << setw(tab[j]) << ' ' << words[i + 1] << '\n';
					i++;
				}
				else {
					while (words[i + 2][0] == '\0') i++;
					cout << setw(tab[j]) << ' ' << words[i] << '\n';
				}
			}
		}
	}
}

void linerSearch(string& str, string &find) {
	int k = 0;
	for (int i = 0, j = 0; i < str.length(); i++) {
		if (str[i] == find[j]) {
			k++;
			j++;
			if (k == find.length()) {
				cout << i + 1 - find.length() << "\n";
			}
		}
		else {
			k = 0;
			j = 0;
		}
	}
}

void algBM(string& str, string& find) {
	int d[256], k = 1, p = 0;
	for (int i = 0; i < 256; i++) {
		d[i] = find.length();
	}
	if (find.length() > 2) {
		while (find.length() - k - 1 > 0) {
			if (d[find[find.length() - k - 1]] == find.length()) {
				d[find[find.length() - k - 1]] = k;
			}
			k += 1;
			if (find.length() - k - 1 == 0) {
				if (d[find[find.length() - k - 1]] == find.length()) {
					d[find[find.length() - k - 1]] = k;
				}
			}
		}
	}
	else {
		d[find[find.length() - k - 1]] = k;
	}
	for (int i = find.length() - 1, j = find.length() - 1; i < str.length();) {
		if (j == 0 && str[i] == find[j]) {
			cout << i << "\n";
			i += find.length();
			j = find.length() - 1;
		}
		if (str[i] == find[j]) {
			i--;
			j--;
		}
		else {
			if (j == find.length() - 1) {
				i += d[str[i]];
			}
			else {
				j = find.length() - 1;
				i += find.length() - j + d[find[find.length() - 1]];
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RUS");
	//1 задание
	cout << "выберите способ ввода последовательности символов\n1.с клавиатуры\t2.с файла\t3. завершить работу программы\n";
	string str;
	char enter;
	bool flag = false;
	int k;
	cin >> k;
	while (!flag)
		switch (k) {
		case(1):
			flag = i_keyb(str, flag);
			break;
		case(2):
			flag = i_file(str, flag);
			break;
		case(3):
			return 0;
		default:
			cout << "введено неизвестное значение\n";
			cin >> k;
			break;
		}
	//2 задание
	cout << "\nЧтобы начать редактирование входного кода нажмите enter\n";
	cin.ignore();
	enter = getchar();
	removeExtraChar(str);
	caseCorrect(str);
	//3 задание
	cout << str << endl << "\nЧтобы вывести на экран слова в алфавитном порядке нажмите enter\n";
	enter = getchar();
	alphabet(str);
	//4 задание
	cout << endl << "\nЧтобы вывести на экран слова в несколько колонк (взависимости от количества слов) нажмите enter\n";
	enter = getchar();
	int tab[L];
	columns(str, tab);
	//5 задание
	cout << endl << "\nЧтобы выполнить поиск подстроки нажмите enter\n";
	enter = getchar();
	cout << endl << "\n1 - поиск алгоритмом Бойера-Мура\t2 - линейный поиск\t0 - остановить цикл\n";
	int alg;
	string find;
	cin >> alg;
	while (alg) {
		switch (alg) {
		case 1: {
			cout << endl << "\nВведите строку которую хотите найти\n";
			cin >> find;
			algBM(str, find); 
			cout << endl << "\n1 - поиск алгоритмом Бойера-Мура\t2 - линейный поиск\t0 - остановить цикл\n";
			cin >> alg;
			break;
		}
		case 2:
			cout << endl << "\nВведите строку которую хотите найти\n";
			cin >> find;
			linerSearch(str, find);
			cout << endl << "\n1 - поиск алгоритмом Бойера-Мура\t2 - линейный поиск\t0 - остановить цикл\n";
			cin >> alg;
			break;
		case 0: return false;
		default:
			cout << "введено неизвестное значение\n";
			break;
		}
	}
	return 0;
}