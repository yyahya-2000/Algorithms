#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

/*
*Ф.И.Г: Яхя Янал, БПИ197, ДЗ_3
*/

//creat byte type
typedef unsigned char byte;

//same m, n in conditions file
static int m, n;
//where the result of hash will be saved
unsigned int i1, i2, i;
//fingerprint
byte f;
//how many times do we try to move items around?
const int MaxNumKicks = 500;
const float fpr = 0.06;

// class represent a bucket in the table of the algorithm
class Bucket {
private:

	//----------------IMPORTANT INSTRUCTION, PLEASE TAKE A LOOK----------------------------
	//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	/*
	*here are two options to create the bucket
	* 1- static array (it's faster and needs less memory)
	* 2- dynamic array (it's slower and needs more memory)
	* please choose one before starting, and if you want to choose the static array,
	* please don't forget to comment the destructor of this class, otherwise you should uncomment the constructer
	*/
	//byte fingerprints[4] = { 0,0,0,0 };
	byte* fingerprints = new byte[4]{ 0,0,0,0 };//dynamic arraty of 4 bytes
public:
	Bucket() {}
	//get specific fingerprint
	byte get(short index) {
		//true if in *(fingerprints + index) was saved fingerprint equal to zero 
		if (*(fingerprints + index)/*fingerprints[index]*/ == 128)
			return *(fingerprints + index) & 0u;
		return (*(fingerprints + index));
	}
	//set fingerprint in specific byte
	void set(short index, byte fingerprint) {
		//true if we want to save zero fingerprint
		if (fingerprint == 0)
			fingerprints[index] = 128;
		else
			fingerprints[index] = fingerprint;
	}
	//cleaning memory, by deleting the dynamic array fingerprints
	~Bucket() {
		delete[]fingerprints;
	}
};

//class represent single cuckoo filter
class CuckooFilter {
private:

	//Reserve 4*m bytes of memory(dynamic array type Bucket(^_^)) 
	Bucket* buckets;

	//Rounding (1 + fpr) * n up to next power of 2 and set it to m
	//void set_buckets_num() {
	//	m = (1 + fpr) * n;//pow(2, ceil(log((1 + fpr) * n) / log(2)));
	//	buckets = new Bucket[m];
	//}

public:
	CuckooFilter() {
		buckets = new Bucket[m];
	}
	//supports getting fingerprint from some buchek, by return address of that bucket
	Bucket& get(int index) {
		return *(buckets + index);
	}
	//supports adding fingerprint into some buchek
	void set(int bucketIndex, short fingerIndex, byte fingerprint) {
		buckets[bucketIndex].set(fingerIndex, fingerprint);
	}

	//our hero :) dedicated to cleaning up memory
	~CuckooFilter() {
		delete[]buckets;
	}
};

//a class represent an user
class User {
private:
	//user's filter
	CuckooFilter cuckooFilter;

public:
	User() : cuckooFilter(CuckooFilter()) {}
	//supports getting fingerprint from the filter, by return address of that filter
	CuckooFilter& get() {
		return cuckooFilter;
	}
	//supports adding fingerprint into the filter
	void set(int bucketIndex, short fingerIndex, byte fingerprint) {
		cuckooFilter.set(bucketIndex, fingerIndex, fingerprint);
	}
};

// map<username, user's filter>
map<string, User> users;

//hashing input for fingerprint
byte hash_of_fingerprint(const string& st) {
	return (byte)(hash<string>{}(st) & 0x7F);
}

// my second hashfunction 
unsigned int fnv_hush_for_indexes(const string& str) {
	const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash *= fnv_prime;
		hash ^= (str[i]);
	}

	return hash % m;

	//alternative function )))
	//return hash<string>{}(str) % m;
}


//check if bucket contain empty place to save fingerprint
short check_bucket(User& user, int bucketIndex) {
	for (short i = 0; i < 4; i++)
	{
		if ((user).get().get(bucketIndex).get(i) == 0)
			return i;
	}
	return -1;
}

//inserting element in specific filter
void insert(User& user, string input) {
	f = hash_of_fingerprint(input);
	i1 = fnv_hush_for_indexes(input);
	i2 = (i1 ^ fnv_hush_for_indexes(string(1, f)));
	short indexOfEmptyEntry;
	if (!((indexOfEmptyEntry = check_bucket(user, i1)) == -1)) {
		(user).set(i1, indexOfEmptyEntry, f);
		return;
	}
	else if (!((indexOfEmptyEntry = check_bucket(user, i2)) == -1)) {
		(user).set(i2, indexOfEmptyEntry, f);
	}
	i = (rand() % 2) == 0 ? i1 : i2;
	for (size_t n = 0; n < MaxNumKicks; n++)
	{
		int temp_finger_index = rand() % 4;
		byte temp = user.get().get(i).get(temp_finger_index);
		user.set(i, temp_finger_index, f);
		f = temp;
		i ^= fnv_hush_for_indexes(string(1, f));
		if (!((indexOfEmptyEntry = check_bucket(user, i)) == -1)) {
			user.set(i, indexOfEmptyEntry, f);
			return;
		}
	}
	//if cuckoo filter full
	throw exception("Hashtable is considered full");
}

//try to find specific fingerprint in specific bucket
bool check_finger_in_bucket(User& user, int bucketIndex) {
	for (size_t i = 0; i < 4; i++)
	{
		if (user.get().get(bucketIndex).get(i) == f)
			return true;
	}
	return false;
}

// look if some element exist in specific cuckoo filter
bool lookup(User& user, string input) {
	f = hash_of_fingerprint(input);
	i1 = fnv_hush_for_indexes(input);
	i2 = (i1 ^ fnv_hush_for_indexes(string(1, f)));
	size_t indexOfEmptyEntry;
	if (check_finger_in_bucket(user, i1) || check_finger_in_bucket(user, i1)) {
		return true;
	}
	return false;
}

//function help in split the test lines
void split_line(string& line, string* subline) {
	if (line[line.length() - 1] == ' ') {
		line = line.substr(0, line.length() - 1);
	}
	size_t current, previous = 0;
	current = line.find(' ');

	size_t index = 0;
	while (current != string::npos) {
		*(subline + index) = line.substr(previous, current - previous);
		previous = current + 1;
		current = line.find(' ', previous);
		index++;
	}
	*(subline + index) = line.substr(previous, current - previous);
}

//reading test from the test file
void read_test_and_write_result_immediately(string testPath, string answerPath) {
	try {
		ifstream myTest;
		myTest.open(testPath);

		ofstream myAnswer;
		myAnswer.open(answerPath);

		string line = "";

		if (!myTest) {
			cout << "Unable to open file";
			exit(1);
		}

		getline(myTest, line);
		string firstsubline[2];
		split_line(line, firstsubline);
		n = stoi(firstsubline[1]);

		m = ceil((1 + fpr) * n);

		myAnswer << "Ok" << endl;

		string subline[3];
		while (getline(myTest, line))
		{
			split_line(line, subline);
			switch (subline[0] == "watch") {
			case 0:
				if (users.find(subline[1]) == users.end()) {
					myAnswer << "No" << endl;
				}
				else {
					myAnswer << (lookup((users[subline[1]]), subline[2]) ? "Probably" : "No") << endl;
				}
				break;
			case 1:
				insert(users[subline[1]], subline[2]);
				myAnswer << "Ok" << endl;
				break;
			}
		}

		myTest.close();
		myAnswer.close();
	}
	catch (exception e) {
		cout << e.what() << endl;
	}
}

//main function
int main(int argc, char** args)
{
	try {
		read_test_and_write_result_immediately(args[1], args[2]);
	}
	catch (exception) {
		cout << "wrong input!" << endl;
		cout << "the right input is: input/test{1-5}.txt output/answer{1-5}.txt " << endl;
	}
	return 0;
}