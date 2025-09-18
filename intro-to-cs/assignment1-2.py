import random
import os
import time

NUM_ROWS = 6
NUM_COLS = 6
NUM_PLAYERS = 2


score_1=0
score_2=0

turn = random.randint(0, NUM_PLAYERS-1)
turn = (turn + 1) % NUM_PLAYERS


hidden_board=[]

joker_remaining=2

characters=['*','*']
remaining_characters=[]
for i in range(int((NUM_ROWS*NUM_COLS)/2)-1):
	characters.append(chr(i+65))
	remaining_characters.append(chr(i+65))
	characters.append(chr(i+97))
for i in range(NUM_ROWS):
	list1= []
	for j in range(NUM_COLS):
		char = characters[random.randint(0,len(characters)-1)]
		list1.append(char)
		characters.remove(char)

	hidden_board.append(list1)

board=[]

for i in range(NUM_ROWS):
	list1= []
	for j in range(NUM_COLS):
		list1.append('#')

	board.append(list1)


for i in range(NUM_COLS):
	print('   '+chr(i+65),end='')
print("\n +" + "---+" * NUM_COLS)

for row in range(NUM_ROWS):
	print(str(row) + '|', end=' ')
	for col in range(NUM_COLS):
		print(hidden_board[row][col] + ' | ', end='')
	print("\n +"+"---+"*NUM_COLS)
#board[][]
game_over=False
total_correct_guesses=0
correct_guesses_required=17
remaining_cards=NUM_ROWS*NUM_COLS
while True:
	print('Player 1 score: ',score_1)
	print('Player 2 score: ',score_2)
	for i in range(NUM_COLS):
		print('   '+chr(i+65),end='')
	print("\n +" + "---+" * NUM_COLS)

	for row in range(NUM_ROWS):
		print(str(row) + '|', end=' ')
		for col in range(NUM_COLS):
			print(board[row][col] + ' | ', end='')
		print("\n +"+"---+"*NUM_COLS)

	x=input('Player '+str(turn+1)+': Enter a coordinate (e.g B3):')
	while len(x)!=2 or (ord(x[0])<65 or ord(x[0])>64+NUM_COLS) or not x[1].isdigit() or int(x[1])<0 or int(x[1])>NUM_ROWS-1 or board[int(x[1])][ord(x[0])-65]==' ':
		print("Please Enter Valid Coordinates")
		x=input('Player '+str(turn+1)+': Enter a coordinate (e.g B3):')

	first_letter=ord(x[0])-65
	second_digit=int(x[1])


	for i in range(NUM_COLS):
		print('   '+chr(i+65),end='')
	print("\n +" + "---+" * NUM_COLS)

	for row in range(NUM_ROWS):
		print(str(row) + '|', end=' ')
		for col in range(NUM_COLS):
			if row==second_digit and col==first_letter:
				print(hidden_board[row][col] + ' | ', end='')
			else:
				print(board[row][col] + ' | ', end='')
		print("\n +"+"---+"*NUM_COLS)



	y=input('Player '+str(turn+1)+': Enter a coordinate (e.g B3):')
	while len(y)!=2 or (ord(y[0])<65 or ord(y[0])>64+NUM_COLS) or not y[1].isdigit() or int(y[1])<0 or int(y[1])>NUM_ROWS-1 or board[int(y[1])][ord(y[0])-65]==' ' or x==y:
		print("Please Enter Valid Coordinates")
		y=input('Player '+str(turn+1)+': Enter a coordinate (e.g B3):')


	previous_first_letter=first_letter
	previous_second_digit=second_digit

	first_letter=ord(y[0])-65
	second_digit=int(y[1])

	for i in range(NUM_COLS):
		print('   '+chr(i+65),end='')
	print("\n +" + "---+" * NUM_COLS)


	for row in range(NUM_ROWS):
		print(str(row) + '|', end=' ')
		for col in range(NUM_COLS):
			if row==second_digit and col==first_letter:
				print(hidden_board[row][col] + ' | ', end='')
			elif row==previous_second_digit and col==previous_first_letter:
				print(hidden_board[row][col] + ' | ', end='')
			else:
				print(board[row][col] + ' | ', end='')
		print("\n +"+"---+"*NUM_COLS)

	if abs(ord(hidden_board[second_digit][first_letter])-ord(hidden_board[previous_second_digit][previous_first_letter]))==32:
		board[second_digit][first_letter]=' '
		board[previous_second_digit][previous_first_letter]=' '
		remaining_cards=remaining_cards-2
		character_removed=hidden_board[second_digit][first_letter].upper()

		if turn==0:
			score_1=score_1+1
		else:
			score_2=score_2+1
		total_correct_guesses=total_correct_guesses+1

	elif hidden_board[second_digit][first_letter] =="*" or hidden_board[previous_second_digit][previous_first_letter] =="*":
		board[second_digit][first_letter]=' '
		board[previous_second_digit][previous_first_letter]=' '
		remaining_cards=remaining_cards-2
		if hidden_board[second_digit][first_letter] =="*" and hidden_board[previous_second_digit][previous_first_letter] =="*":
			correct_guesses_required=18
			joker_remaining=0
		else:
			remaining_cards=remaining_cards-1
			joker_remaining=joker_remaining-1
			if hidden_board[second_digit][first_letter] =="*":
				for i in range(NUM_ROWS):
					for j in range(NUM_COLS):
						if hidden_board[i][j] == hidden_board[previous_second_digit][previous_first_letter].lower() or hidden_board[i][j] == hidden_board[previous_second_digit][previous_first_letter].upper():
							board[i][j]=' '

			else:
				joker_remaining=joker_remaining-1
				for i in range(NUM_ROWS):
					for j in range(NUM_COLS):
						if hidden_board[i][j] == hidden_board[second_digit][first_letter].lower() or hidden_board[i][j] == hidden_board[second_digit][first_letter].upper():
							board[i][j]=' '



		if turn==0:
			score_1=score_1+2
		else:
			score_2=score_2+2
		if remaining_cards<2:
			game_over=True


	else:
		if remaining_cards<2:
			game_over=True
		turn = (turn + 1) % NUM_PLAYERS
		if game_over==True:
			break
		print('Did not find a pair, turn over!')
		time.sleep(2)
		os.system('clear')

if joker_remaining>0:
	if turn==0:
		score_1=score_1+joker_remaining
	else:
		score_2=score_2+joker_remaining

if score_1>score_2:
	print('Player 1 wins!')
elif score_2>score_1:
	print('Player 2 wins!')
else:
	print('Draw!')
print('Player 1 score: ',score_1)
print('Player 2 score: ',score_2)




