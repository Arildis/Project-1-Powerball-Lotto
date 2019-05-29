#include <iostream>
#include <vector>
#include <algorithm> 
#include <ticket.h>
using namespace std;
using namespace ticket;

// Mohamed Khalil

int main() {

  int retry = 1;
  PowerballTicket lotto;
  int tixBought;
  int choice;
  int w1;
  int rNum;
  int tempMoney;
  int moneyWon;
  int totalGain;
  int displayTix;
  bool duplicate = false;
  bool redBallCheck = true;
  vector<vector<int>> winningTix;
  vector<int> inputLot{0,0,0,0,0,0};
  vector<int> winningLot;

  while(retry == 1){
    cout << "Welcome to the PowerBall Lottery." << endl;
    cout << "Pricing for Tickets: " << lotto.PriceGet() << " dollars." << endl;
    tempMoney = lotto.MoneyGet();
    cout << "You have " << lotto.MoneyGet() << " dollars." << endl;
    cout << "How many tickets would you like to buy? (Select a number between 1-1000) ";
    cin >> tixBought;
    cout << "Would you like to manually insert numbers or random tickets? (Select 1 for manual insert. Select 2 for random tickets.) ";
    cin >> choice;
    cout << endl;

    if(choice == 1){
      for(int i = 0; i < tixBought; i++){
        cout << "\nTicket " << i+1 << ": ";
        for(int j = 0; j < 5; j++){
          cout << endl;
          cout << "Input white number " << j+1 << " (Must be between 1-69): ";
          cin >> w1;

          if(w1 < 1 || w1 > 69){
            cout << "\nInvalid number, please input again.";
            j--;
          }
          else{
            for(int k = 0; k < inputLot.size(); k++){
              if(w1 == inputLot[k]){
                duplicate = true;
              }
            }
            if(duplicate){
              cout << "\nYou cannot input duplicate white numbers.";
              j--;
            }
            else{
              inputLot[j] = w1;
            }
          }
          duplicate = false;
        }

        while(redBallCheck){
          cout << "\nInput red ball number (Must be between 1-26):";
          cin >> rNum;
          if(rNum < 1 || rNum > 26){
            cout << "\nRed ball number invalid. Please input again.";
          }
          else{
            inputLot[5] = rNum;
            redBallCheck = false;
          }
        }

        lotto.ticketSet(inputLot);
        inputLot = {0,0,0,0,0,0};
        redBallCheck = true;
      }
    }
    else{
      for(int i = 0; i < tixBought; i++){
        lotto.ticketRandom();
      }
    }

    moneyWon = lotto.calcWinning(); // winnings
    totalGain = lotto.MoneyGet() - tempMoney; // profit

    cout << endl;

    cout << "You won " << moneyWon << " dollars." << endl;
    cout << "Your net gains are " << totalGain << " dollars." << endl;
    cout << "Would you like to see the tickets: (1 for yes, 2 for only winning tickets, 3 for no) ";
    cin >> displayTix;
    cout << "\n";

    winningLot = lotto.getWinningLotto();
    cout << "The Winning Ticket is: \n";
    for(int j = 0; j < winningLot.size(); j++){
      cout << winningLot[j];
      cout << " ";
    }
    cout << endl;
    

    cout << "\n\n";
    
    if(displayTix == 1){
      cout << lotto;
    }
    else if(displayTix == 2){
      winningTix = lotto.getWinningTickets();
      string forOutput;
      for(int i = 0; i < winningTix.size(); i++){
        forOutput += "Ticket ";
        forOutput +=  std::to_string(i+1);
        forOutput += ": ";
        for(int j = 0; j < winningTix[i].size(); j++){
          forOutput += std::to_string(winningTix[i][j]);
          forOutput += "  ";
        }
        forOutput += "\n";
      }
      cout << forOutput;
    }
    
    cout << "\n\n";
    cout << "Would you like to play again? (1 for yes, 2 for no) ";
    cin >> retry;
    lotto.resetLotto();
  }

  return 0;
}