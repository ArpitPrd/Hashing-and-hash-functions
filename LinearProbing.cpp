#include "LinearProbing.h"
using namespace std;
LinearProbing::LinearProbing(){
	int m = 2 * pow2(10, 5) + 3;
	bankStorage1d.resize(m);
	
	for (int i = 0; i < bankStorage1d.size(); i++){
		bankStorage1d[i].id = "";
		bankStorage1d[i].balance = -2;
	}
	size = 0;
}

int LinearProbing::pow2(int a, int b){
	int mul = 1;
	for (int i = 0; i < b; i++){
		mul *= a;
	}
	return mul;
}

void LinearProbing::createAccount(std::string id, int count) {
	Account a;
	a.id = id;
	a.balance = count;
	int HTi = hash(id);
	size++;
	int m = 2 * pow2(10, 5) + 3;
	while (bankStorage1d[HTi].id != ""){
		HTi = (HTi + 1) % m;
	}
	bankStorage1d[HTi] = a;
}

int LinearProbing::find_loc1(vector<int> v, int a){
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

std::vector<int> LinearProbing::getTopK(int k) {
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

int LinearProbing::getBalance(std::string id) {
	if (doesExist(id)){
		int loc = hash(id);
		int m = 2 * pow2(10, 5) + 3;
		int i = loc;
		while (true){
			if (bankStorage1d[i].id == id){
				return bankStorage1d[i].balance;
			}
			else{
				i = ( i + 1) % m;
			}
		}	
	}
	return -1; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
	if (doesExist(id)){
		int loc = hash(id);
		int m = 2 * pow2(10, 5) + 3;
		int i = loc;
		/*
		do{
			if (bankStorage1d[i].id == id){std::cout<<bankStorage1d[i].id<<std::endl;
				bankStorage1d[i].balance += count;
				break;
			}
			else{
				i = (i+1)%m;
			}
		}
		while (i != loc);
		*/
		while (true){
			if (bankStorage1d[i].id == id){
				bankStorage1d[i].balance += count;
				break;
			}
			else{
				i = ( i + 1) % m;
			}
		}
	}
	else{
		createAccount(id, count);
	}
}

bool LinearProbing::doesExist(std::string id) {
	int loc = hash(id);
	int  m = 2 * pow2(10, 5) + 3;
	int i = loc;
	while (bankStorage1d[i].balance != -2){
		if (bankStorage1d[i].id == id){
			return true;
		}
		else{
			i = (i + 1) % m;
		}
	}
	return false;
}

bool LinearProbing::deleteAccount(std::string id) {
    int loc = hash(id);
	int m = 2 * pow2(10, 5) + 3;
	if (doesExist(id)){
		size--;
		int i = loc;
		while (true){
			if (bankStorage1d[i].id == id){
				bankStorage1d[i].balance = -1;
				bankStorage1d[i].id = "";
				return true;
			}
			else{
				i = ( i + 1) % m;
			}
		}
	}
	return false;
}

int LinearProbing::databaseSize() {
    // IMPLEMENT YOUR CODE HERE
    return size; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
     int p = 47;
     int res;
        int po =1;
        int m = 2 * pow2(10, 5) + 3;
     for (int i = 0; i < id.size(); i++){
        res = (id[i] * po) % m;
        po = (po * p) % m;
     }
     return res;

}
/*
int main(){
        BaseClass* db=new LinearProbing();
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
