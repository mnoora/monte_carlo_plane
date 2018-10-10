#include <iostream>
#include <random>
#include <vector>
#include <utility> 
#include <algorithm> 

using namespace std;

class Passenger {
	public:
	pair<int,int> seatCoordinates;
	int place;
	int timer;
	int row;
	bool wait;
	Passenger(pair<int,int>,int,int,int,bool);
	pair<int,int> getSeatCoordinates();
	void setTimer(int time);
	int getTimer();
	int getPlace();
	void setPlace(int step);
	int getRow();
	void setRow(int step);
	bool getWait();
	void setWait(bool waited);
};

Passenger::Passenger(pair<int,int> s,int o,int p,int r,bool w) {
	seatCoordinates=s;
	timer = o;
	place = p;
	row = r;
	wait=w;
}

pair<int,int> Passenger::getSeatCoordinates() {
	return seatCoordinates;
}
void Passenger::setTimer(int time) {
	timer+=time;
}
int Passenger::getTimer(){
	return timer;
}
int Passenger::getPlace(){
	return place;
}
void Passenger::setPlace(int  step){
	place+=step;
}
int Passenger::getRow(){
	return row;
}
void Passenger::setRow(int step){
	row+=step;
}
bool Passenger::getWait(){
	return wait;
}
void Passenger::setWait(bool w){
	wait=w;
}


void printSeats(vector<pair<int,int>> N){
 for (int i = 0; i <= N.size() - 1; i++){
        cout << N[i].first << " , " << N[i].second << endl;
    }
}

vector<pair<int,int>> randSeats(int N){
	vector<pair< int, int > > seats;
	for(int i =0;i<N/4;i++){
		for(int j= 0;j<4;j++){
			seats.push_back(make_pair(i,j));
		}
	}
	return seats;
}

int main(){
	vector<pair< int, int > > seats = randSeats(100);
    // Shuffling seats
	auto rng = default_random_engine {};
    shuffle(std::begin(seats), std::end(seats), rng);
    vector<Passenger> passengers;

	float timestep = 0.0;
    vector<float> timeTofindSeat;
	// assigning passengers shuffled seats
	for(int i=0;i<100;i++){
		passengers.push_back(Passenger(seats[i],0,0,0,false));
	}
	int plane[24][3]= {{0}};

	// start filling the plane
		for(int i=0;i<10000;i++){
			for(int j=0;j<passengers.size();j++){
				timestep +=0.5;
				if(passengers.empty()){
					break;
				}
				if(passengers[j].getTimer() > 0){
					passengers[j].setTimer(-1);
				}
				else if(passengers[j].getSeatCoordinates().second == 0 || passengers[j].getSeatCoordinates().second== 1 ){
					if(passengers[j].getPlace()>=50 && passengers[j].getTimer()==0 && passengers[j].getRow() == passengers[j].getSeatCoordinates().first && plane[passengers[j].getRow()][1] == 0 ) {
						plane[passengers[j].getRow()][passengers[j].getSeatCoordinates().second] = 1;
						passengers.erase(passengers.begin()+j);
						timeTofindSeat.push_back(timestep);
						continue;
					}else if(passengers[j].getPlace()>=50 && passengers[j].getWait() ==false && passengers[j].getTimer()==0 && passengers[j].getRow() == passengers[j].getSeatCoordinates().first && plane[passengers[j].getRow()][1] == 1){
						passengers[j].setTimer(15);
						passengers[j].setWait(true);
					}else if(passengers[j].getPlace()>=50 && passengers[j].getWait() ==true && passengers[j].getTimer()==0 && passengers[j].getRow() == passengers[j].getSeatCoordinates().first && plane[passengers[j].getRow()][1] == 1){
						plane[passengers[j].getRow()][passengers[j].getSeatCoordinates().second] = 1;
						passengers.erase(passengers.begin()+j);
						timeTofindSeat.push_back(timestep);
						continue;
					}
					else if( j==0){
						if(passengers[j].getPlace()>50){
							passengers[j].setRow(1);
						}
						passengers[j].setPlace(1);
					}else if(passengers[j-1].getPlace()-passengers[j].getPlace()>1){
						if(passengers[j].getPlace()>50){
							passengers[j].setRow(1);
						}
						passengers[j].setPlace(1);
					}
				}else if(passengers[j].getSeatCoordinates().second == 2 || passengers[j].getSeatCoordinates().second== 3 )
					if(passengers[j].getPlace()>=50 && passengers[j].getTimer()==0 && passengers[j].getRow() == passengers[j].getSeatCoordinates().first && plane[passengers[j].getRow()][1] == 0 ) {
							plane[passengers[j].getRow()][passengers[j].getSeatCoordinates().second] = 1;
							passengers.erase(passengers.begin()+j);
							timeTofindSeat.push_back(timestep);
							continue;
						}else if(passengers[j].getPlace()>=50 && passengers[j].getWait() ==false && passengers[j].getTimer()==0 && passengers[j].getRow() == passengers[j].getSeatCoordinates().first && plane[passengers[j].getRow()][2] == 1){
							passengers[j].setTimer(15);
							passengers[j].setWait(true);
						}else if(passengers[j].getPlace()>=50 && passengers[j].getWait() ==true && passengers[j].getTimer()==0 && passengers[j].getRow() == passengers[j].getSeatCoordinates().first && plane[passengers[j].getRow()][2] == 1){
							plane[passengers[j].getRow()][passengers[j].getSeatCoordinates().second] = 1;
							passengers.erase(passengers.begin()+j);
							timeTofindSeat.push_back(timestep);
							continue;
						}
						else if( j==0){
						if(passengers[j].getPlace()>50){
							passengers[j].setRow(1);
						}
						passengers[j].setPlace(1);
						}else if(passengers[j-1].getPlace()-passengers[j].getPlace()>1){
							if(passengers[j].getPlace()>50){
								passengers[j].setRow(1);
							}
						passengers[j].setPlace(1);
					}
			}
		}
    
	float sum = 0;
	for(int i=0;i<timeTofindSeat.size();i++){
		sum+=timeTofindSeat[i];
	}
	float mean = sum /timeTofindSeat.size();

	float var = 0.0;
	for(int i=0;i<timeTofindSeat.size();i++){
		var+=pow(timeTofindSeat[i]-mean,2);
	}
	var = var /(timeTofindSeat.size()-1.0);
	cout<<"mean: "<<mean<<endl;
	cout<<"standard deviation: "<<sqrt(var)<<endl;
	return 0;
}


  

