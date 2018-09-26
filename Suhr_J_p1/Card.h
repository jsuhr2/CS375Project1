#ifndef DARD_H
#define CARD_H

#include <string>

class Card{
	public:
		std::string name;
		int price;
		int marketprice;
		Card(std::string n, int p, int m){
			name = n;
			price = p;
			marketprice = m;
		};
};

#endif
