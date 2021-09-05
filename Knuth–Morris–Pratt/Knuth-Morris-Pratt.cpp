#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void display_pattern(const std::string &text, const std::string &pattern, const int &shift) {
	
	std::string pattern_to_display(shift, ' ');

	pattern_to_display += pattern;

	std::cout << "El patron occure en el shift " << shift << std::endl;
	std::cout << text << std::endl;
	std::cout << pattern_to_display << std::endl;
	std::cout << std::endl;

}


std::vector<int> get_lps(const std::string &pattern) { //lps =  longest proper prefix which is also suffix mucho nombre pero asi le dicen
	std::vector<int> lps(pattern.size(), 0);
	// lps[0] siempre es 0, porque un prefijo propio no puede ser todo el substring
	
	int previous_len = 0;// el valor de el prefijo mas largo anterior

	int i = 1;
	while (i < pattern.size()) {
		if (pattern[i] == pattern[previous_len]) { //si son la misma letra, aumenta el lps
			++previous_len;
			lps[i] = previous_len;
			++i;
		}

		else {
			if (previous_len != 0) 
				previous_len = lps[previous_len - 1];

			else {
				lps[i] = 0;
				++i;
			}
		}
	}

	return lps;
}

void search(const std::string &pattern, const std::string &text) {

	std::vector<int> lps = get_lps(pattern);

	int i = 0;
	int j = 0;

	while (i < text.size()) {
		if (pattern[j] == text[i]) {
			++j;
			++i;
		}
		if (j == pattern.size()) { //encontramos patron
			display_pattern(text, pattern, i - j);
			j = lps[j - 1];
		}
		else if (i < text.size() && pattern[j] != text[i]) // si no son iguales
			if (j != 0)
				j = lps[j - 1];
			else
				++i;
	}

}


int main(int arg, char * argv[]){ 

	std::string text = "ANPANMAN";
	std::string pattern = "AN";
	search(pattern, text);

	return 0;
}