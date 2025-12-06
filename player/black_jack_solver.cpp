#include "black_jack_solver.hpp"
#include <array>
#include <set>


BlackJackSolver::BlackJackSolver(
    uint64_t number_of_decks,
    float reshuffle_percentage,
    uint64_t number_of_rounds,
    chip_t chips,
    chip_t table_min,
    chip_t table_max):
    number_of_decks(number_of_decks),
    reshuffle_percentage(reshuffle_percentage),
    number_of_rounds(number_of_rounds),
    chips(chips),
    table_min(table_min),
    table_max(table_max)
{
    cardCount = 0;
    // BlackJackSolver* ptr = this;
    // BlackJackSolver& self = *this;
    // ptr->number_of_decks = number_of_decks;
    // self.number_of_decks = number_of_decks;
    // this->number_of_decks = number_of_decks;
}

BlackJackSolver::~BlackJackSolver() {}

chip_t BlackJackSolver::get_bet() {
    if (chips < table_min){
        return chips;
    }
    if (cardCount < 0){
        int amt = chips*.005;
        if (amt < table_min){
            return table_min;
        }
        return amt;
    }
    return table_min;
 }


BlackJackAction handleNormalHand(Card dealer_up_card, int handTotal,int numCards){
    if (handTotal <= 7){
        return BlackJackAction::HIT;
    }
    if (dealer_up_card.rank == Rank::TWO){
        if (handTotal >= 13){
            return BlackJackAction::STAND;
        }
        else if (handTotal == 8 || handTotal == 9 || handTotal == 12){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 10 || handTotal == 11){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
    else if (dealer_up_card.rank == Rank::THREE){
        if (handTotal >= 13){
            return BlackJackAction::STAND;
        }
        else if (handTotal == 8 || handTotal == 12){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 9 || handTotal == 10 || handTotal == 11){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
    else if (dealer_up_card.rank == Rank::FOUR || dealer_up_card.rank == Rank::FIVE || dealer_up_card.rank == Rank::SIX){
        if (handTotal >= 12){
            return BlackJackAction::STAND;
        }
        else if (handTotal == 8){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 9 || handTotal == 10 || handTotal == 11){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
    else if (dealer_up_card.rank == Rank::SEVEN || dealer_up_card.rank == Rank::EIGHT || dealer_up_card.rank == Rank::NINE){
        if (handTotal >= 12){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 8 || handTotal == 9){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 10 || handTotal == 11){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
    else if (dealer_up_card.rank == Rank::TEN || dealer_up_card.rank == Rank::JACK || 
        dealer_up_card.rank == Rank::QUEEN || dealer_up_card.rank == Rank::KING || dealer_up_card.rank == Rank::ACE){
        if (handTotal >= 12){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 8 || handTotal == 9 || handTotal == 10){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 11){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
    
    // Default fallback - handles any case not covered above
    return BlackJackAction::HIT;
}

BlackJackAction handleAceHand(Card dealer_up_card, int handTotal,int numCards){
    if (handTotal == 0){
        // if it is two aces
        return BlackJackAction::HIT;
    }
    if (dealer_up_card.rank == Rank::TWO){
        if (handTotal >= 8){
            return BlackJackAction::STAND;
        }
        else if (handTotal <= 6){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 7){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::STAND;
        }
    }
   if (dealer_up_card.rank == Rank::THREE){
        if (handTotal >= 8){
            return BlackJackAction::STAND;
        }
        else if (handTotal <= 5){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 7){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::STAND;
        }
        else if (handTotal == 6){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
   if (dealer_up_card.rank == Rank::FOUR){
        if (handTotal >= 8){
            return BlackJackAction::STAND;
        }
        else if (handTotal <= 3){
            return BlackJackAction::HIT;
        }
        else if (handTotal == 7){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::STAND;
        }
        else if (handTotal == 6 || handTotal == 5 || handTotal == 4){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
   if (dealer_up_card.rank == Rank::FIVE){
        if (handTotal >= 8){
            return BlackJackAction::STAND;
        }
        else if (handTotal == 7){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::STAND;
        }
        else{
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
   if (dealer_up_card.rank == Rank::SIX){
        if (handTotal == 9){
            return BlackJackAction::STAND;
        }
        else if (handTotal == 7 || handTotal == 8){
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::STAND;
        }
        else{
            if (numCards == 2)
                return BlackJackAction::DOUBLE_DOWN;
            return BlackJackAction::HIT;
        }
    }
   if (dealer_up_card.rank == Rank::SEVEN || dealer_up_card.rank == Rank::EIGHT){
        if (handTotal >= 7){
            return BlackJackAction::STAND;
        }
        else{
            return BlackJackAction::HIT;
        }
    }

   if (dealer_up_card.rank == Rank::NINE || dealer_up_card.rank == Rank::TEN || dealer_up_card.rank == Rank::JACK || 
        dealer_up_card.rank == Rank::QUEEN || dealer_up_card.rank == Rank::KING || dealer_up_card.rank == Rank::ACE){
        if (handTotal >= 8){
            return BlackJackAction::STAND;
        }
        else{
            return BlackJackAction::HIT;
        }
    }
    // Default fallback - handles any case not covered above (Shouldn't happen but ^)
    return BlackJackAction::HIT;
}

bool checkSplit(Card dealer_up_card, std::span<const Card> cards, BlackJackHandStatus status){

    if (cards.size() > 2 || cards[0].rank != cards[1].rank || status == BlackJackHandStatus::SPLIT){
        return false;
    }
    
    if (cards[0].rank == Rank::ACE || cards[0].rank == Rank::EIGHT){
        return true;
    }
    if (to_int(cards[0].rank) == 10 || cards[0].rank == Rank::FIVE){
        return false;
    }
    if (to_int(cards[0].rank) == 9){
        if (dealer_up_card.rank == Rank::SEVEN || to_int(dealer_up_card.rank) == 10 || dealer_up_card.rank == Rank::ACE){
            return false;
        }
        return true;
    }
    if (to_int(cards[0].rank) == 7){
        if (to_int(dealer_up_card.rank) <= 7){
            return true;
        }
        return false;
    }
    if (to_int(cards[0].rank) == 6){
        if (to_int(dealer_up_card.rank) <= 6){
            return true;
        }
        return false;
    }
    if (to_int(cards[0].rank) == 4){
        if (to_int(dealer_up_card.rank) == 5 || to_int(dealer_up_card.rank) == 6){
            return true;
        }
        return false;
    }
    if (to_int(cards[0].rank) == 3 || to_int(cards[0].rank) == 2){
        if (to_int(dealer_up_card.rank) <= 7){
            return true;
        }
        return false;
    }
    // shouldn't happen
    return false;



}

bool checkSurrender(Card dealer_up_card, int handTotal){
    if (handTotal == 16){
        if (to_int(dealer_up_card.rank) == 9 || to_int(dealer_up_card.rank) == 10 || to_int(dealer_up_card.rank) == 0) 
            return true;
    }
    else if (handTotal == 15){
        // any face card or ten will be 10
        if (to_int(dealer_up_card.rank) == 10){
            return true;
        }
    }
    return false;

}

bool containsRank(std::span<const Card> cards, Rank rank){
    for(const Card& card : cards){
        if (card.rank == rank){
            return true;
        }
    }
    return false;
}
int addToCardCount(std::span<const Card> cards, BlackJackHandStatus status){
    int numToAdd = 0;

    if (status == BlackJackHandStatus::SPLIT){
        // Always just only add the second card since we saw the first
        Card card = cards[cards.size()-1];
        if (to_int(card.rank) <= 6 && to_int(card.rank) != 0){
            numToAdd ++;
        }
        else if (to_int(card.rank) == 0 || to_int(card.rank) == 10){
            numToAdd --;
        }
    }
    else if (cards.size() == 2){
        // if fresh deck with only 1 card
        for (const Card& card : cards){
        if (to_int(card.rank) <= 6 && to_int(card.rank) != 0){
            numToAdd ++;
        }
        else if (to_int(card.rank) == 10 || to_int(card.rank) == 0){
            numToAdd --;
        }
    }
    }
    else {
        // used deck with 2 or more cards (just add the last card)
        Card card = cards[cards.size()-1];
        if (to_int(card.rank) <= 6 && to_int(card.rank) != 0){
            numToAdd ++;
        }
        else if (to_int(card.rank) == 0 || to_int(card.rank) == 10){
            numToAdd --;
        }
    }


    return numToAdd;
}
BlackJackAction
    BlackJackSolver::handle_hand(Card dealer_up_card, std::span<const Card> cards, BlackJackHandStatus status)
{   
    // Hand total doesn't include the value of the ace
    int handTotal = 0;
    for (const Card& card : cards){
        handTotal += to_int(card.rank);
    }

    cardCount += addToCardCount(cards,status);

    
    if (handTotal >= 17) {
        return BlackJackAction::STAND;
    }

    if (status == BlackJackHandStatus::NONE && cards.size() == 2 && checkSurrender(dealer_up_card,handTotal)){
        return BlackJackAction::SURRENDER;
    }
    if (checkSplit(dealer_up_card,cards,status)){
        if (chips >= get_bet()*2){
            return BlackJackAction::SPLIT;
        }   
    }

    if (containsRank(cards, Rank::ACE)){
        BlackJackAction toReturn = handleAceHand(dealer_up_card,handTotal,cards.size());
        if (toReturn == BlackJackAction::DOUBLE_DOWN && chips < get_bet()*2){
            return BlackJackAction::HIT;
        }
        return toReturn;
    }
    else{
        BlackJackAction toReturn = handleNormalHand(dealer_up_card,handTotal,cards.size());
        if (toReturn == BlackJackAction::DOUBLE_DOWN && chips < get_bet()*2){
            return BlackJackAction::HIT;
        }
        return toReturn;
        
    }
    
    return BlackJackAction::STAND;
}

void BlackJackSolver::take_payout(chip_t payout, std::span<const Card> dealer_cards) {
    // Update our chip count with the payout (can be positive or negative)
    this->chips += payout;
    for (const Card& card : dealer_cards){
        if (to_int(card.rank) <= 6 && to_int(card.rank) != 0){
            cardCount ++;
        }
        else if (to_int(card.rank) == 0 || to_int(card.rank) == 10){
            cardCount --;
        }
    }
}

void BlackJackSolver::on_reshuffle() {
    cardCount = 0;
}
