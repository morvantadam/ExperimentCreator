#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//This is a useless comment.

void expSetup(string&, string&, string&, string&);
string getUserInput();

void main() {
	cout << "Before running this, be sure to use addExp and create the directory to be used.\n";
	cout << "Important information from now on will be shown to the user between \"<>\" and in caps.\n";
	string mainExp;
	string subExp;
	string expLength;
	string decodeMethod;
	expSetup(mainExp, subExp, expLength, decodeMethod);	
	cout << "\n\n<SECTION 1>\n";
	cout << "cd /mnt/main/Exp/" << mainExp << "/" << subExp << "/\n";
	cout << "makeExp.pl -train\n";
	cout << "<<<<SKIP THIS LINE, USER INPUT REQUIRED>>>>\n";
	cout << "cp ~/sphinx_LDA_Random.cfg etc/sphinx_train.cfg\n";
	cout << "cp ~/mlltRandomTemplate.py python/sphinx/mllt.py\n";
	cout << "genFeats.pl -t\n";
	cout << "nohup scripts_pl/RunAll.pl &\n";
	cout << "\n\n<SECTION 2>\n";
	cout << "mkdir LM; cd LM;\n";
	cout << "cp -i /mnt/main/corpus/switchboard/" << expLength << "train/trans.train trans_unedited\n";
	cout << "parseLMTrans.pl trans_unedited trans_parsed\n";
	cout << "lm_create.pl trans_parsed\n";
	cout << "\n\n<SECTION 3, CURRENTLY ONLY SET TO MATCHING TRAINED LDA DECODE>\n";
	cout << "cd etc\n";
	cout << "awk {print $i} /mnt/main/corpus/switchboard/" << expLength << "test/trans/train.trans >> /mnt/main/Exp/" << mainExp << "/" << subExp << "/etc/" << subExp << "_decode.fileids\n";
	cout << "nohup run_decode_lda.pl " << mainExp << "/" << subExp << " " << mainExp << "/" << subExp << " 1000 &\n";
	cout << "\n\n<SECTION 4>\n";
	cout << "parseDecode.pl decode.log hyp.trans\n";
	cout << "sclite -r " << subExp << "_train.trans -h hyp.trans -i swb >> scoring.log\n";
}

void expSetup(string &mainExp, string &subExp, string &expLength, string &decodeMethod) {
	//Get main exp number; implement error checking to see if input it 4 digits long and all numbers.
	cout << "Please enter the main experiment number: ";
	mainExp = getUserInput();
	//Get sub-exp number; implement error checking to see if input it 3 digits long and all numbers.
	cout << "Please enter the sub-experiment number: ";
	subExp = getUserInput();
	cout << "Please enter the length of the experiment you want to run (e.g. \"1hr\", \"5hr\", \"30hr\"...)";
	expLength = getUserInput();
	cout << "Please enter the form of decode you wish to perform.";
	decodeMethod = getUserInput();
}

string getUserInput() {
	string userInput;
	getline(cin, userInput);
	return userInput;
}