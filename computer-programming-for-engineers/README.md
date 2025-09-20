# Sota Card Game

## Overview
A C++ implementation of the Moroccan card game "Sota".  
Features dynamic memory allocation, object-oriented design, and all game rules:
- Normal play by matching number or suit.
- How to play 
Each player receives 5 cards dealt to them by the dealer, which is determined between the players; after giving out cards, the dealer puts a card on the table.
The person to the right of the dealer starts to play. The rule is that you can put down a card if either it has the same suit as the card in the middle or the same number.
 For instance, if the card is the 5 of clubs, then the only cards that can be played are any 5 card from the remaining suits or any other card with clubs.
If it is a players' turn and they don't have a card to play, they have to pick up from the remaining deck.The objective of the game is to get rid of all your cards.
If all of the remaining cards in the deck are used up and the game is still going, the existing cards on the table get reshuffled into a new deck leaving the last card played to continue the game.
-Special Cards 
There are 3 special cards: the ace (1), two (2), and seven (7).
Ace (1)- If this card is put down, it skips the turn of the next player in the loop. The player that is skipped can't play or draw cards. This card is stackable, potentially leading to multiple skips.
For instance, if player 1 skips player 2 and, by chance, player 2 has a skip, they can put their card down and skip player 3.
Two (2)- This card forces the player after them to draw two cards. If a player receiving a 2 has another 2 in their hand, they can stack it, potentially increasing the draw to 4; every 2 stacks the total draw by 2.
For example, if player three places a 2 for player 1 and player 1 has another 2, this forces player 2 to draw 4 cards.
Seven (7) - The seven card is the most powerful in the deck as it can be placed on the table no matter the suit or number on the table.
The person who places this card then needs to announce what suit they would like to change it to.
For instance, if player 2 plays a 7 of coins, they then have to decide what suit they would like.
They can pick any of the 4 suits previously mentioned. Another seven card can be played on an existing one as well.
#Usage

Run the executable and follow the main menu:

./sota_game

1 Play: start a new game (2–4 players).

2 Help: display game rules.

3 Exit: quit.

During play:

- You will be prompted to enter each player's name.

- Each turn, your hand is listed; type the number of the card to play.

- If you have no playable cards, the game automatically draws for you.

-When playing a 7, choose your new suit by selecting from the displayed options.

Enjoy the game!
