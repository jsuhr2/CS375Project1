#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>

#include "Card.h"

using namespace std;

void printToOutputFile(int sizeOfInput, int maxProf, int numCards, double elapsed_secs, vector<Card> cardV){

	ofstream output;
	output.open("output.txt", ios_base::app);
	output << sizeOfInput << " " << maxProf << " " << numCards << " " << elapsed_secs << endl;
	for(auto i = cardV.begin(); i !=cardV.end(); i++){
		output << (*i).name << endl;
	}
	output << endl;
}

int main(int argc, char** argv){
	
	ofstream clear;
	clear.open("output.txt", ofstream::out | ofstream::trunc);
	clear.close();

	int budget = 0;
	int numBuyCards = 0;
	int numSellCards = 0;
	int maxProfit = 0;
	string nameBuy;
	int priceBuy = 0;
	string nameSell;
	int priceSell = 0;
	int possibleCost = 0;
	vector<Card> max;
	vector<Card> possibleBuy;
	int possibleBuyProfit = 0;
	vector<Card> cardsSold;

	if(argc != 5){
		cerr << "Incorrect command line arguments" << endl;
		return 0;
	}

	ifstream pricelistfile(argv[4], ios::in);
	if(!pricelistfile){
		cerr << "Cannot open price list file for input" << endl;
		return 0;
	}

	while(!pricelistfile.eof()){
		clock_t begin = clock();
		ifstream marketpricefile(argv[2], ios::in);
		if(!marketpricefile){
			cerr << "Cannot open market price file for input" << endl;
			return 0;
		}

		pricelistfile >> numBuyCards;
		pricelistfile >> budget;

		for(int i = 0; i < numBuyCards; i++){
			pricelistfile >> nameBuy;
			pricelistfile >> priceBuy;
			Card c(nameBuy, priceBuy, 0);
			cardsSold.push_back(c);
		}

		marketpricefile >> numSellCards;

		for(int i = 0; i < numSellCards; i++){
			marketpricefile >> nameSell;
			marketpricefile >> priceSell;
			for(auto i = cardsSold.begin(); i != cardsSold.end(); i++){
				if(!nameSell.compare((*i).name)){
					(*i).marketprice = priceSell;
				}
//				cout << (*i).name << " " << (*i).marketprice << endl;
			}
		}

		if(numSellCards < numBuyCards){
			cerr << "Gertrude is selling cards that don't exist on the market" << endl;
			return 0;
		}
		
		for(int i = 0; i < pow(2, numBuyCards); i++){
			for(int j = 0; j <= numBuyCards; j++){
				if(i & (1 << j)){
					possibleBuy.push_back(cardsSold[j]);
//					cout << cardsSold[j].name << endl;
				}
			}
			for(auto k = possibleBuy.begin(); k != possibleBuy.end(); k++){
				possibleBuyProfit += (*k).marketprice - (*k).price;
				possibleCost += (*k).price;
//				cout << (*k).price << " " << possibleCost << " " << possibleBuyProfit << endl;
			}
			if(possibleBuyProfit > maxProfit && possibleCost <= budget){
				maxProfit = possibleBuyProfit;
				max = possibleBuy;
			}
			possibleBuyProfit = 0;
			possibleCost = 0;
			possibleBuy.clear();
		}
/*
		for(auto i = max.begin(); i != max.end(); i++){
			cout << (*i).name << " " << maxProfit << endl;
		}
*/		
		
		clock_t end = clock();
		double elapsed = double(end - begin) / CLOCKS_PER_SEC;
		printToOutputFile(numBuyCards, maxProfit, max.size(), elapsed, max);
		
		max.clear();
		maxProfit = 0;
		cardsSold.clear();

		pricelistfile >> numBuyCards;
		pricelistfile >> budget;
	
		for(int i = 0; i < numBuyCards; i++){
			pricelistfile >> nameBuy;
			pricelistfile >> priceBuy;
			Card c(nameBuy, priceBuy, 0);
			cardsSold.push_back(c);
		}
		marketpricefile.close();
	}

/*
	marketpricefile >> numSellCards;
	pricelistfile >> numBuyCards;
	pricelistfile >> budget;
	cout << "sell: " << numSellCards << " buy: " << numBuyCards << " budget: " << budget << endl;
*/
	pricelistfile.close();
	return 0;

}
