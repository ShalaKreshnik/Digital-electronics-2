
#ifndef KEYPAD_H_
#define KEYPAD_H_

int correct;
int correct_1;
int correct_2;
int count_1;
int count;
int time_check;
char pass[4];
int password[4];
int position;
int countdown;
int countdown_1;
int countdown_2;
int countdown_flag;
int password_1[4];
int password_2[4];
int column;
int cols;
volatile uint8_t i;
int char_flag;

void keypad();

void Check_password();

void Check_password_1();

void Check_password_2();

void reset();

void entry_denied();

void entry_accepted();


#endif /* KEYPAD_H_ */