#include "Comp.h"
using namespace std;

Comp::Comp(){
    bankStorage2d.resize(2 * pow5(10, 5) + 3);
    size = 0;
}

int Comp::pow5(int a, int b){
    int mul = 1;
    for (int i = 0; i < b; i++){
        mul *= a;
    }
    return mul;
}

int Comp::find_loc1(vector<int> v, int a){
	int i = -1;
    int j = v.size();
    int mid;
	int loc;
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
void Comp::createAccount(std::string id, int count) {
	Account a;
	a.id = id;
	a.balance = count;
	int HTi = hash(id);
	size++;
	bankStorage2d[HTi].push_back(a);
}

std::vector<int> Comp::getTopK(int k) {
	vector<int> v;
	int loc;
	for (int i = 0; i < bankStorage2d.size(); i++){
		for (int j = 0; j < bankStorage2d[i].size(); j++){
			if (k > v.size()){
				int loc = find_loc1(v, bankStorage2d[i][j].balance);
				v.insert(v.begin() + loc, bankStorage2d[i][j].balance);
			}
			else{
				if ( bankStorage2d[i][j].balance > v[v.size() - 1] ){
					v.pop_back();
					int loc = find_loc1(v, bankStorage2d[i][j].balance);
					v.insert(v.begin() + loc, bankStorage2d[i][j].balance);
				}
			}
		}
	}
	return v;
}

int Comp::getBalance(std::string id) {
	if (doesExist(id)){
		int loc = hash(id);
		for (int i = 0; i < bankStorage2d[loc].size(); i++){
			if (id == bankStorage2d[loc][i].id){
				int y = bankStorage2d[loc][i].balance;
				return y;
			}
		}
	}
	return -1;
}

void Comp::addTransaction(std::string id, int count) {
	if (doesExist(id)){
		int loc = hash(id);
		for (int i = 0; i < bankStorage2d[loc].size(); i++){
			if (id == bankStorage2d[loc][i].id){
				bankStorage2d[loc][i].balance += count;
				break;
			}
		}
	}
	else{
		createAccount(id, count);
	}
}

bool Comp::doesExist(std::string id) {
	int loc = hash(id);
	for (int i = 0; i< bankStorage2d[loc].size(); i++){
		if (bankStorage2d[loc][i].id == id){
			return true;
		}
	}
	return false;
}

bool Comp::deleteAccount(std::string id) {
	if (doesExist(id)){
		int loc = hash(id);
		for (int i = 0; i < bankStorage2d[loc].size(); i++){
			if (bankStorage2d[loc][i].id == id){
				bankStorage2d[loc].erase(bankStorage2d[loc].begin()+i);
				size--;
				return true;
			}
		}
	}
	return false;
}
int Comp::databaseSize() {
    return size; // Placeholder return value
}

int Comp::hash(std::string id) {
     int p = 47;
     int res;
        int po =1;
        int m = 2 * pow5(10, 5) + 3;
     for (int i = 0; i < id.size(); i++){
        res = (id[i] * po) % m;
        po = (po * p) % m;
     }
     return res;
}
/*
int main(){
BaseClass* db=new Comp();
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




// Feel free to add any other helper functions you need
// Good Luck!