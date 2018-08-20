#pragma once

#pragma once
enum DignityCard
{
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	TEN = 10,
	JACK = 11,
	LADY = 12,
	KING = 13,
	ACE = 14
};

enum Suit
{
	HEARTS = 1,
	PEAKS = 2,
	DEAMONDS = 3,
	CLUBS = 4
};


class CardClient
{
private:
	DignityCard dignity;
	Suit suit;
	bool trump;
public:
	CardClient(DignityCard dignity, Suit suit, bool isTrump);
	CardClient();
	~CardClient();
	//true - ���� ������� Card ���� �������� Card card
	bool beats(CardClient card);
	//������������� ������
	void setTrupm(bool isTrump);
	//�������� �� ����� ��������
	bool isTrump();
	//���������� �� �����
	bool equals(CardClient card);

	DignityCard getDignity();

	Suit getSuit();

	char* toUchars();
};

