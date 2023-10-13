#include "QuadraticProbing.h"

using namespace std;

QuadraticProbing::QuadraticProbing(){
	int m = 2 * pow3(10, 5) + 3;
	bankStorage1d.resize(m);
	
	for (int i = 0; i < bankStorage1d.size(); i++){
		bankStorage1d[i].id = "";
		bankStorage1d[i].balance = -2;
	}
	size = 0;
}
int QuadraticProbing::pow3(int a, int b){
        int mul = 1;
        for (int i = 0; i < b; i++){
                mul *= a;
        }
        return mul;
}
void QuadraticProbing::createAccount(std::string id, int count) {
	Account a;
	a.id = id;
	a.balance = count;
	int HTi = hash(id);
        int k = 1;
	size++;
	int m = 2 * pow3(10, 5) + 3;
	while (bankStorage1d[HTi].id != ""){
		HTi = (HTi + k*k) % m;
                k++;
	}
	bankStorage1d[HTi] = a;
}

int QuadraticProbing::find_loc1(vector<int> v, int a){
        int i = -1;
        int j = v.size();
        int mid;
        while (i < j && j-i!=1){
                mid = (i + j) / 2;
                if (v[mid] < a){
                        j = mid;
                }
                else if (v[mid] > a){
                        i = mid;
                }
                else {
                        return mid;
                }
        }
        return j;
}


std::vector<int> QuadraticProbing::getTopK(int k) {
	vector<int> topk;
	for (int i = 0; i < bankStorage1d.size(); i++){
		if (k > topk.size()){
			if (bankStorage1d[i].balance != -1 or bankStorage1d[i].balance != -2){
				int loc = find_loc1( topk, bankStorage1d[i].balance);
				topk.insert( topk.begin() + loc, bankStorage1d[i].balance);
			}
		}
		else{
			if (bankStorage1d[i].balance > topk[topk.size() - 1]){
				topk.pop_back();
				int loc = find_loc1( topk, bankStorage1d[i].balance);
				topk.insert( topk.begin() + loc, bankStorage1d[i].balance);
			}
		}
	}
	return topk;
}

int QuadraticProbing::getBalance(std::string id) {
	if (doesExist(id)){
		int loc = hash(id);
		int m = 2 * pow3(10, 5) + 3;
		int i = loc;
                int k = 1;
		while (true){
			if (bankStorage1d[i].id == id){
				return bankStorage1d[i].balance;
			
			}
			else{
				i = ( i + k*k) % m;
                                k++;
			}
		}	
	}
	return -1;
}


void QuadraticProbing::addTransaction(std::string id, int count) {
	if (doesExist(id)){
		int loc = hash(id);
		int m = 2 * pow3(10, 5) + 3;
		int i = loc;
                int k = 1;
		while (true){
			if (bankStorage1d[i].id == id){
				bankStorage1d[i].balance += count;
				break;
			}
			else{
				i = ( i + k*k) % m;
                                k++;
			}
		}
	}
	else{
		createAccount(id, count);
	}
}



bool QuadraticProbing::doesExist(std::string id) {
	int loc = hash(id);
	int  m = 2 * pow3(10, 5) + 3;
	int i = loc;
        int k = 1;
		while (bankStorage1d[i].balance != -2){
		if (bankStorage1d[i].id == id){
			return true;
		}
		else{
			i = (i + k*k) % m;
                        k++;
		}
	}
	
	return false;
}


bool QuadraticProbing::deleteAccount(std::string id) {
    int loc = hash(id);
	int m = 2 * pow3(10, 5) + 3;
	if (doesExist(id)){
		size--;
		int i = loc;
                int k = 1;
		while (true){
			if (bankStorage1d[i].id == id){
				bankStorage1d[i].balance = -1;
				bankStorage1d[i].id = "";
                                return true;
			}
			else{
				i = ( i + k*k) % m;
                                k++;
			}
		}
	}
	return false;
}

int QuadraticProbing::databaseSize() {
	return size;
}

int QuadraticProbing::hash(std::string id) {
/*
        int num1 = 0;
        int num2 = 0;
        int num3 = 0;
        int num4 = 0;
        int num5 = 0;
        char a;
        int temp;

        for (int i = 0; i < 4; i++){
                a = id[i];
                if ( a < 91 ){
                        temp = id[i] - 'A' + 1;
                }
                else{
                        temp = id[i] - 'a' + 1;
                }
                num1 += temp * pow3 ( 53, 3-i);
        }
        int fnum1 = num1;
        int t;
        do{
                t = fnum1;
                fnum1 = 0;
                while ( t != 0 ){
                        fnum1 += t % 10;
                        t /= 10;
                }
        }
        while ( fnum1 / 10 != 0 );

        for (int j = 4; j < 8; j++){
                num2 += id[j] * pow3(11, 3-j);
        }
        int fnum2 = num2;
        do{
                t = fnum2;
                fnum2 = 0;
                while ( t != 0 ){
                        fnum2 += t % 10;
                        t /= 10;
                }
        }
        while ( fnum2 / 10 != 0 );

        num3 = id[8]*pow3(11,3) + id[9]*pow3(11, 2)+id[10]*pow3(11,1)+id[12];
        int fnum3 = num3;
        do{
                t = fnum3;
                fnum3 = 0;
                while ( t != 0 ){
                        fnum3 += t % 10;
                        t /= 10;
                }
        }
        while ( fnum3 / 10 != 0 );

        num4 = id[13]*pow3(11,3) + id[14]*pow3(11, 2)+id[15]*pow3(11,1)+id[16];
        int fnum4 = num4;
        do{
                t = fnum4;
                fnum4 = 0;
                while ( t != 0 ){
                        fnum4 += t % 10;
                        t /= 10;
                }
        }
        while ( fnum4 / 10 != 0 );

        num5 = id[17]*pow3(11,4) + id[18]*pow3(11,3)+id[19]*pow3(11,2)+id[20]*11+id[21];
        int fnum5 = num5;
        do{
                t = fnum5;
                fnum5 = 0;
                while ( t != 0 ){
                        fnum5 += t % 10;
                        t /= 10;
                }
        }
        while ( fnum5 / 10 != 0 );
        int f = fnum5*pow3(10,4)+fnum4*pow3(10,3)+fnum3*pow3(10,2)+fnum2*pow3(10,1)+fnum1;
        //cout << f << endl;
        return f; // Placeholder return value
      */
     int p = 47;
     int res;
        int po =1;
        int m = 2 * pow3(10, 5) + 3;
     for (int i = 0; i < id.size(); i++){
        res = (id[i] * po) % m;
        po = (po * p) % m;
     }
     return res;
}
/*
int main(){
        BaseClass* db=new QuadraticProbing();
db->createAccount( "CDAD7786825_7990768648", 648);
db->createAccount( "DCDA7547234_9919615552", 552);
db->createAccount ("AACB1850545_7974534788", 788);
cout << db->databaseSize() << endl;
db->createAccount ("CDBD5250777_1124276711" ,711);
db->createAccount( "ABCB8377155_0656808575", 575);
vector<int> a1 = db->getTopK( 1);
int i = 0;
for (i = 0; i<a1.size(); i++){
	cout << a1[i] << " ";
}
cout << endl;
db->createAccount ("CDDC3792028_3313680038", 38);
db->createAccount ("CBBA9574444_7470182321", 321);
db->createAccount ("DBCC4334636_8057544188", 188);
vector<int> a2 = db->getTopK (3);
for (i = 0; i<a2.size(); i++){
        cout << a2[i] << " ";
}       
cout << endl;

db->createAccount ("BABD5741078_5109455304", 304);
db->createAccount ("BCBA7529510_0817878868", 868);
cout << db->databaseSize() << endl;
vector<int> a3 = db->getTopK (1);
for (i = 0; i<a3.size(); i++){
        cout << a3[i] << " ";
}       
cout << endl;

db->addTransaction ("BCBA7529510_0817878868", -860);
cout << db->getBalance ("BCBA7529510_0817878868") << endl;
vector<int> a4 =  db->getTopK (1);
for (i = 0; i<a4.size(); i++){
        cout << a4[i] << " ";
}       
cout << endl;

db->addTransaction ("DCDA7547234_9919615552", 592);
vector<int> a5 = db->getTopK (5);
for (i = 0; i<a5.size(); i++){
        cout << a5[i] << " ";
}       
cout << endl;

db->deleteAccount ("DCDA7547234_9919615552");
vector<int> a6 = db->getTopK (4);
for (i = 0; i<a6.size(); i++){
        cout << a6[i] << " ";
}       
cout << endl;

cout << db->databaseSize() << endl;
}
*/

