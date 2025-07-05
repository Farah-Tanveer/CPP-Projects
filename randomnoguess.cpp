#include<iostream>
#include<time.h>
using namespace std;

int main()
{
    int random,guess;
    int count_guess=0;
    srand(time(NULL));
    random=rand()%101;
    cout<<"Welcome to the Number Guessing game!!";
    do
    {
        cout<<"\nPlease enter a number (between 0 and 100) : ";
        cin>>guess;
        count_guess++;

        if(guess<random)
        {
            cout<<"Guess a larger number.\n";
        }
        else if(guess>random)
        {
            cout<<"Guess a smaller number.\n";
        }
        else if(guess==random)
        {
            cout<<"Congratulations!!!You have successfully guessed the correct number in "<<count_guess<<" turn.";
        }
    }
    while(guess!=random);
    cout<<"\nThanks for Playing!!!\nDeveloped by: Farah Tanveer";
    return 0;
}