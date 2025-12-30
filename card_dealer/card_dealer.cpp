#include <random>
#include <ctime>
#include <iostream>

/* This card dealer will create a shuffled deck, then deal out cards as requested by the user.
Internally, this will be done with an array of integers, the card's details will be determined as such:
value % 4 = suit, value % 13 = rank
*/
enum Suit{
    HEART,
    CLUB,
    DIAMOND,
    SPADE
};
enum Rank{
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};


const int DECK_SIZE = 52;

void draw_card(int &top_index, int (&deck)[DECK_SIZE]);
void seed_random();
int get_card_index();

int main(){
    seed_random();

    int deck[DECK_SIZE];   //this is a for each loop, equivalent to python "for card in deck:"
    for(int& card : deck){ // the & here is needed to specify that card should be the int in the array and not a copy
        card = -1;         //this loop is just to initialize each card to an impossible value
    }

    for(int i = 0; i < DECK_SIZE; i++){  //since each card is represented by an int from 0-51, the randomness will
        int idx = get_card_index();          //be granted via ordered assignment to a random index
        std::cout << "i=" << i<<"; idx="<<idx<<"deck[idx]="<<deck[idx]<<"\n";
        if (deck[idx] == -1){
            deck[idx] = i;
        }
        else {                           //if there is a collision, the next index will be checked until an empty spot is found
            while (!(deck[idx] == -1)){    //it will wrap around to the 0th index if it needs to
                idx ++;
                if (idx >= DECK_SIZE){
                    idx = 0;
                }
            }
            deck[idx] = i;
        }
    
    for (int card : deck){
        std::cout << card << " ";
    }
    std::cout << std::endl;
    }

    int top_card_index = 0;
    while (top_card_index <= DECK_SIZE){
        std::cout << "\n\n\n\n Press Enter to deal card!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n'); //https://stackoverflow.com/questions/5131647/why-would-we-call-cin-clear-and-cin-ignore-after-reading-input
        //std::cin.get();              //https://stackoverflow.com/questions/13556890/why-do-i-have-to-press-enter-twice
        draw_card(top_card_index, deck);
    }




}

void draw_card(int &top_index, int (&deck)[DECK_SIZE]){
    int drawn_card = deck[top_index];
    top_index ++;
    std::cout << "Your card is a: ";
    switch (drawn_card % 13) {
        case Rank::ACE:
            std::cout << "Ace of ";
            break;
        case Rank::JACK:
            std::cout << "Jack of ";
            break;
        case Rank::QUEEN:
            std::cout << "Queen of ";
            break;
        case Rank::KING:
            std::cout << "King of ";
            break;
        default:
            std::cout << (drawn_card%13 + 1) << " of ";
    }
    switch (drawn_card % 4) {
        case Suit::HEART:
            std::cout << "Hearts\n";
            break;
        case Suit::CLUB:
            std::cout << "Clubs\n";
            break;
        case Suit::DIAMOND:
            std::cout << "Diamonds\n";
            break;
        case Suit::SPADE:
            std::cout << "Spades\n";
            break;
    }
}

void seed_random(){         //rand is pseudo-deterministic, given the same seed, it will generate the same sequence of numbers every time.
    std::srand(time(0));    // to obfuscate this, you seed with srand(), and can use time() to get a different seed each time the program runs.
    for (int i = 51; i > 0; i--){
        std::rand();        //I don't have a source, but I saw something once that said you get better 'randomness' if you generate and discard the initial values of rand after seeding
    }                       //maybe true, maybe not...
}


int get_card_index(){
    return rand() % DECK_SIZE+1;
}