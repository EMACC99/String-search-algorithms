#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>

#define ALPHABET_LEN 256


void display_pattern(const std::string &txt, const std::string &pattern, const int &shift) {
	std::string pattern_to_display (shift, ' ');

	pattern_to_display += pattern;

	std::cout << txt << std::endl;
	std::cout << pattern_to_display << std::endl;
	std::cout << std::endl;
}

std::vector<int> init_bad_char_rule(std::string pattern, int size){

	//en el preprocesamiento, llenamos las ultimas occurecncias 

	std::vector<int> badchar(ALPHABET_LEN, -1);
	
	for (int i = 0; i < size; ++i)
		badchar[(int)pattern[i]] = i;


	return badchar;
}

void search(const std::string &text, const std::string &pattern) {
	
	int m = pattern.size();
	int n = text.size();


	std::vector<int> badchar = init_bad_char_rule(pattern, m);

	int shift = 0; // the shift ot the pattern with respect of the text

	while (shift <= (n - m)) {
		int j = m - 1;

		while (j >= 0 && pattern[j] == text[shift + j]) //aqui revisamos en orden descendente, que el patron vaya cumplimendo
			--j;

		if (j < 0) { //si todo es un match
			std::cout << "El patron occurre en el shift  " << shift << std::endl;
			display_pattern(text, pattern, shift);

			shift += (shift + m < n) ? m - badchar[text[shift + m]] : 1; //regresa el shift para que siga buscando despues de la ultima ocurrencia el uno es por si occure al final del texto 
			// shift += m - badchar[text[shift + m]] if shift + m < n else 1
		}
		else
			shift += std::max(1, j - badchar[text[shift + j]]); //si no, tenemos que saltar a la posicion despues de donde aparecio el caracter que no aparece en el patron (o uno si la resta es negativa)

	}	
}


int main(int arg, char* argv[]) {
	std::string text = "ANPANMAN";
	std::string pattern = "AN";
	search(text, pattern);
	return 0;
}