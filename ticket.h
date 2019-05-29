#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;


namespace ticket {
  class PowerballTicket{

    private:

      vector <vector<int>> ticketStorage;
      vector <vector<int>> winningTickets;
      vector<int> winningTicket{0,0,0,0,0,0};
      int Price;
      int Money;

    public:

      PowerballTicket(){
        Price = 2;
        Money = 100;
      }

      PowerballTicket(int x){
        Money = x;
        Price = 2;
      }

      PowerballTicket(int y, int z){
        Money = y;
        Price = z;
      }

      void ticketSet(vector<int> input){
        std::sort(input.begin(), input.begin()+5);
        ticketStorage.push_back(input);
        Money -= Price;
      };

      void ticketRandom(){
        vector<int> randomTicket{0,0,0,0,0,0};
        int randNum;
        bool dupe = true;
        Money -= Price;

        for (int i = 0; i < 5; i++){	

          randNum = rand() % 69 + 1; // generates white num

          for(int j = 0; j < 5; j++){
            while(randNum == randomTicket[j]){ // anytime the current num is a duplicate we repeat the step for that num
              randNum = rand() % 69 + 1;
            }
          }

          randomTicket[i] = randNum;
        }

        randomTicket[5] = rand() % 26 + 1; // generates red num
        ticketStorage.push_back(randomTicket);
      }

      int PriceGet(){
        return Price;
      }
      void PriceSet(int a){
        Price = a;
      }

      int MoneyGet(){
        return Money;
      }

      int calcWinning(){

        int prize = 0;
        int whitenum = 0;
        int rednum = 0;
        bool winner = false;

        int randNum;

        for (int i = 0; i < 5; i++){	

          randNum = rand() % 69 + 1;

          for(int j = 0; j < 5; j++){
            if(randNum == winningTicket[j]){
              i--;
            }
          }

          winningTicket[i] = randNum;
        }

        winningTicket[5] = rand() % 26 + 1;
        

        for(int i = 0; i < ticketStorage.size(); i++){
          for(int j = 0; j < 5; j++){
            if(ticketStorage[i][j] == winningTicket[j]){ // checks white balls
              //cout<<ticketStorage[i][j];
              //cout << winningTicket[j];
              whitenum++;
            }
          }
          if(ticketStorage[i][5] == winningTicket[5]){ // checks red ball
            rednum++;
          }

          if(whitenum == 5){
            if(rednum == 1)
              prize += 5000000;
            else
              prize += 1000000;
            winner = true;
          }
          else if(whitenum == 4){
            if(rednum == 1)
              prize += 50000;
            else
              prize += 100;
            winner = true;
          }
          else if(whitenum == 3){
            if(rednum == 1)
              prize += 100;
            else
              prize += 7;
            winner = true;
          }
          else if(whitenum == 2){
            if(rednum == 1){
              prize += 7;
              winner = true;
            }
          }
          else if(whitenum == 1){
            if(rednum == 1){
              prize += 4;
              winner = true;
            }
          }
          else if(whitenum == 0){
            if(rednum == 1){
              prize += 4;
              winner = true;
            }
          }

          if(winner){
            winningTickets.push_back(ticketStorage[i]);
          }

          whitenum = 0;
          rednum = 0;
          winner = false;

        }

        Money += prize;
        return prize;
      }

      vector<int> getWinningLotto(){
        return winningTicket;
      }

      vector<vector<int>> getAllTickets(){
        return ticketStorage;
      }

      vector <vector<int>> getWinningTickets(){
        return winningTickets;
      }

      void resetLotto(){
        ticketStorage.clear();
        ticketStorage.shrink_to_fit();
        winningTickets.clear();
        winningTickets.shrink_to_fit();
      }

      friend ostream &operator<<( ostream &output, const PowerballTicket &P ) { 
        string forOutput;
        for(int i = 0; i < P.ticketStorage.size(); i++){
          forOutput += "Ticket ";
          forOutput +=  std::to_string(i+1);
          forOutput += ": ";
          for(int j = 0; j < P.ticketStorage[i].size(); j++){
            forOutput += std::to_string(P.ticketStorage[i][j]);
            forOutput += "  ";
          }
          forOutput += "\n";
        }
        output << forOutput;
        return output;
      }

  };
}