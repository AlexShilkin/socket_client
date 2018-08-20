#include "CardClient.h"


CardClient::CardClient(DignityCard dignity, Suit suit, bool isTrump)
{
	this->dignity = dignity;
	this->suit;
	this->trump = isTrump;
}

CardClient::CardClient()
{
}

CardClient::~CardClient()
{

}

bool CardClient::beats(CardClient card)
{
	bool isBeats = false;

	if (this->trump == true) {
		if (card.isTrump() == true) {
			if (this->dignity - card.dignity > 0) {
				isBeats = true;
			}
			else {
				isBeats = false;
			}
		}
		else {
			isBeats = true;
		}
	}
	else {
		if (this->suit == card.suit) {
			if (this->dignity - card.dignity > 0) {
				isBeats = true;
			}
			else {
				isBeats = false;
			}
		}
		else {
			isBeats = false;
		}
	}
	return isBeats;
}

void CardClient::setTrupm(bool isTrump)
{
	this->trump = isTrump;
}

bool CardClient::isTrump()
{
	return this->trump;
}

bool CardClient::equals(CardClient card)
{
	bool isEquals = false;
	if (this->suit == card.suit&&this->dignity == card.dignity) {
		isEquals = true;
	}
	return isEquals;
}

DignityCard CardClient::getDignity()
{
	return dignity;
}

Suit CardClient::getSuit()
{
	return suit;
}

char * CardClient::toUchars()
{
	char* uchars = new char[3];
	uchars[0] = dignity;
	uchars[1] = suit;
	uchars[2] = trump;

	return uchars;
}

