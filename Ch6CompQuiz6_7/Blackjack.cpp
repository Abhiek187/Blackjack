/* Let's Play Blackjack!
 * Blackjack.cpp
 *
 *  Created on: May 25, 2017
 *      Author: Abhiek187
 */

#include <iostream>
// #include <array> for std::array if C++11
#include <vector>
#include <ctime>
#include <cstdlib>

// Each card rank is displayed below
enum Rank
{
	RANK_2,
	RANK_3,
	RANK_4,
	RANK_5,
	RANK_6,
	RANK_7,
	RANK_8,
	RANK_9,
	RANK_10,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING,
	RANK_ACE,
	MAX_RANKS,
};

// Each card suit is displayed below
enum Suit
{
	SUIT_CLUB,
	SUIT_DIAMOND,
	SUIT_HEART,
	SUIT_SPADE,
	MAX_SUITS,
};

// Cards are identified by their rank and suit
struct Card
{
	Rank rank;
	Suit suit;
};

// Every card is labeled below
void printCard(const Card &card)
{
	using namespace std;

	switch (card.rank)
	{
		case RANK_2:	 cout << '2'; break;
		case RANK_3:	 cout << '3'; break;
		case RANK_4:	 cout << '4'; break;
		case RANK_5:	 cout << '5'; break;
		case RANK_6:	 cout << '6'; break;
		case RANK_7:	 cout << '7'; break;
		case RANK_8:	 cout << '8'; break;
		case RANK_9:	 cout << '9'; break;
		case RANK_10:	 cout << 'T'; break; // Note: T = 10
		case RANK_JACK:  cout << 'J'; break;
		case RANK_QUEEN: cout << 'Q'; break;
		case RANK_KING:	 cout << 'K'; break;
		case RANK_ACE:	 cout << 'A'; break;
		default:         cout << '?'; break;
	}

	switch (card.suit)
	{
		case SUIT_CLUB:	   cout << 'C'; break;
		case SUIT_DIAMOND: cout << 'D'; break;
		case SUIT_HEART:   cout << 'H'; break;
		case SUIT_SPADE:   cout << 'S'; break;
		default:           cout << '?'; break;
	}
}

// The deck is labeled below
void printDeck(const std::vector<Card> &deck)
{
	for (int card = 0; card < 52; ++card)
	{
		printCard(deck[card]);
		std::cout << ' ';
	}

	std::cout << '\n';
}

// The value of two cards are swapped
void swapCard(Card &card1, Card &card2)
{
	Card temp_card = card1;
	card1 = card2;
	card2 = temp_card;
}

// A random number generator is used for shuffling the deck
int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// Each card is swapped by a random card to shuffle the deck
void shuffleDeck(std::vector<Card> &deck)
{
	for (int card = 0; card < 52; ++card)
	{
		int randomCard = getRandomNumber(0,51);
		swapCard(deck[card],deck[randomCard]);
	}
}

// Each card is worth a certain amount of points
int getCardValue(const Card &card)
{
	switch (card.rank)
	{
	case RANK_2:     return 2;
	case RANK_3:	 return 3;
	case RANK_4:	 return 4;
	case RANK_5:	 return 5;
	case RANK_6:	 return 6;
	case RANK_7:	 return 7;
	case RANK_8:	 return 8;
	case RANK_9:	 return 9;
	case RANK_10:	 return 10;
	case RANK_JACK:	 return 10;
	case RANK_QUEEN: return 10;
	case RANK_KING:	 return 10;
	case RANK_ACE:	 return 11; // ace can be 1 depending on game
	default:         return 0;
	}
}

// 1 = player won, 0 = dealer won
bool playBlackjack(const std::vector<Card> &deck)
{
	// Set up the initial game state
	const Card *cardPtr = &deck[0];
	int playerScore(0);
	int dealerScore(0);
	char response = 'h';

	dealerScore += getCardValue(*cardPtr++);
	playerScore += getCardValue(*cardPtr++);

	while (response == 'h')
	{
		playerScore += getCardValue(*cardPtr++);
		std::cout << "Your total score is " << playerScore;
		std::cout << "\nWill you hit or stand (h/s)? ";
		std::cin >> response;
	}

	// Players that go over 21 get busted
	if (playerScore > 21)
		return false;

	// Dealer must stop when value is at least 17
	while (dealerScore < 17)
		dealerScore += getCardValue(*cardPtr++);

	std::cout << "The dealer's score is " << dealerScore << '\n';

	return playerScore > dealerScore || dealerScore > 21;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	// Vectors are much safer to work with than pointers
	std::vector<Card> deck;
	deck.resize(52);
	int card = 0;

	for (int rank = 0; rank < MAX_RANKS; ++rank)
	{
		for (int suit = 0; suit < MAX_SUITS; ++suit)
		{
			deck[card].rank = static_cast<Rank>(rank);
			deck[card].suit = static_cast<Suit>(suit);
			++card;
		}
	}

	// Actual deck is printed, then a random deck is printed
	printDeck(deck);
	shuffleDeck(deck);

	if (playBlackjack(deck))
		std::cout << "You win.\n";
	else
		std::cout << "You lose.\n";

	return 0;
}
