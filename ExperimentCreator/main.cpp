#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Used to set a boolean for whether or not this is a batch job.
bool batchSet();

//This is likely going to be where most of the output takes place. Depending on the type of experiment and whether or not it's a batch job, it will edit and format the commands accordingly.
//Arg 1: The boolean for whether or not this is a batch job. If false, it will display each command one-per-line.
//Arg 2: The main experiment number
//Arg 3: The sub experiment number
//Arg 4: The length of the experiment
//Arg 5: The type of experiment to be used.
void batchPrint(bool, string, string, string, string);

//Used to return a string that determines which method is used. Loops if an unexpected input is entered.
//Arg 1: The prompt to be displayed.
//Arg 2: The array of strings that are accepted answers.
string evalLoop(string, string[], int);

//Used to setup the strings used to generate file paths or determine the type of experiment to be run.
void expSetup(string&, string&, string&, string&);

//Uses a getline input and returns whatever is entered.
string getUserInput();

//Checks to see that all values are numerical, and there is a predetermined number of values.
string valueCheck(string, int);

int main() {
	cout << ">> Before running this, be sure to use addExp and create the directory to be used.\n";
	cout << ">> Important information from now on will be shown to the user between \"<>\" and in caps.\n";
	bool batch = batchSet();
	//Strings used to hold data for creating directories and determining processes.
	string mainExp, subExp, expLength, decodeMethod;
	expSetup(mainExp, subExp, expLength, decodeMethod);
	batchPrint(batch, mainExp, subExp, expLength, decodeMethod);
	/*
	cout << "\n\n<SECTION 1>\n";
	cout << "cd /mnt/main/Exp/" << mainExp << "/" << subExp << "/\n";
	cout << "makeExp.pl -train\n";
	cout << "<<<<SKIP THIS LINE, USER INPUT REQUIRED>>>>\n";
	//Below are relative links that my "atm1042" home directory. If this is standardized for others, find a way to make these absolute.
	cout << "<<<<EDIT ETC/SPHINX_TRAIN.CFG YOURSELF>>>>\n";
	cout << "cp ~/mlltRandomTemplate.py python/sphinx/mllt.py\n";
	cout << "genFeats.pl -t\n";
	cout << "nohup scripts_pl/RunAll.pl &\n";
	cout << "\n\n<SECTION 2>\n";
	cout << "mkdir LM; cd LM;\n";
	cout << "cp -i /mnt/main/corpus/switchboard/" << expLength << "/train/trans/train.trans trans_unedited\n";
	cout << "parseLMTrans.pl trans_unedited trans_parsed\n";
	cout << "lm_create.pl trans_parsed\n";
	cout << "\n\n<SECTION 3, CURRENTLY ONLY SET TO MATCHING TRAINED LDA DECODE>\n";
	cout << "cd /mnt/main/Exp/" << mainExp << "/" << subExp << "/etc\n";
	cout << "awk \'{print $i}\' /mnt/main/corpus/switchboard/" << expLength << "/test/trans/train.trans >> /mnt/main/Exp/" << mainExp << "/" << subExp << "/etc/" << subExp << "_decode.fileids\n";
	cout << "nohup run_decode_lda.pl " << mainExp << "/" << subExp << " " << mainExp << "/" << subExp << " 1000 &\n";
	cout << "\n\n<SECTION 4>\n";
	cout << "parseDecode.pl decode.log hyp.trans\n";
	cout << "sclite -r " << subExp << "_train.trans -h hyp.trans -i swb >> scoring.log\n";
	*/
	return 0;
}

//Used to set a boolean for whether or not this is a batch job.
bool batchSet() {
	bool boolSet;
	const int optionSize = 2;
	string options[optionSize] = { "y", "n" };
	string result = evalLoop("Is this meant to be run as a batch job?", options, optionSize);
	if (result == "y") {
		boolSet = 1;
	}

	else {
		boolSet = 0;
	}
	return boolSet;
}

//This is likely going to be where most of the output takes place. Depending on the type of experiment and whether or not it's a batch job, it will edit and format the commands accordingly.
//Arg 1: The boolean for whether or not this is a batch job. If false, it will display each command one-per-line.
//Arg 2: The main experiment number
//Arg 3: The sub experiment number
//Arg 4: The length of the experiment
//Arg 5: The type of experiment to be used.
void batchPrint(bool batch, string mainExp, string subExp, string expLength, string decodeMethod) {
	//The constant number of commands used to create the output. Different experiments may need to interject their content after certain lines.
	const int COMMANDS = 21;
	//The array of strings used to generate the output.
	string commands[COMMANDS] = {
		"cd /mnt/main/Exp/" + mainExp + "/" + subExp + "/",
		"makeExp.pl -train",
		"",
		"!",
		"<<BE SURE TO EDIT THE SPHINX CONFIG FILE>>",
		"cp ~/mlltRandomTemplate.py python/sphinx/mllt.py",
		"genFeats.pl -t",
		"!",
		"nohup scripts_pl/RunAll.pl &",
		"",
		"mkdir LM; cd LM",
		"cp -i /mnt/main/corpus/switchboard/" + expLength + "/train/trans/train.trans trans_unedited",
		"parseLMTrans.pl trans_unedited trans_parsed",
		"lm_create.pl trans_parsed",
		"cd /mnt/main/Exp/" + mainExp + "/" + subExp + "/etc",
		"awk \'{print $i}\' /mnt/main/corpus/switchboard/" + expLength + "/test/trans/train.trans /mnt/main/Exp/" + mainExp + "/" + subExp + "/etc/" + subExp + "_decode.fileids",
		"!",
		"nohup run_decode_lda.pl " + mainExp + "/" + subExp + " " + mainExp + "/" + subExp + " 1000 &",
		"",
		"parseDecode.pl decode.log hyp.trans",
		"sclite -r " + subExp + "_train.trans -h hyp.trans -i swb >> scoring.log"
	};
	//Determines if the output is a batch output 
	if (batch == 1) {
		//Cycles through each of the commands listed above.
		for (int i = 0; i < COMMANDS; i++) {
			//If the command is empty, it is output at two new lines.
			if (commands[i] == "") {
				cout << "\n\n";
			}
			//If the command has an exclamation point, the next line is printed without a semicolon ";".
			else if (commands[i] == "!") {
				i++;
				cout << commands[i] << "\n";
			}
			//Otherwise, each command will be output with a semicolon ";".
			else {
				cout << commands[i] + "; ";
			}
		}
	}
	//The methodology for this set is the same as the last, except that instead of semicolons, new lines are outputted instead.
	else {
		for (int i = 0; i < COMMANDS; i++) {
			if (commands[i] == "") {
				cout << "\n\n";
			}
			else if (commands[i] == "!") {
				i++;
				cout << commands[i] << "\n";
			}
			else {
				cout << commands[i] + "\n";
			}
		}
	}
}

//Used to return a string that determines which method is used. Loops if an unexpected input is entered.
//Arg 1: The prompt to be displayed.
//Arg 2: The array of strings that are accepted answers.
string evalLoop(string prompt, string options[], int optionSize) {
	bool loop = 1;
	string input;
	while (loop == 1) {
		cout << prompt << "\n> ";
		input = getUserInput();
		for (int i = 0; i < optionSize; i++) {
			if (input == options[i]) {
				loop = 0;
			}
		}
		if (loop == 1) {
			cout << "ERROR: Invalid input! Expected responses: ";
			for (int i = 0; i < optionSize; i++) {
				if (i == optionSize - 1) {
					cout << "\"" << options[i] << "\". " << endl;
				}
				else {
					cout << "\"" << options[i] << "\", ";
				}
			}
		}
	}
	return input;
}

//Used to setup the strings used to generate file paths or determine the type of experiment to be run.
void expSetup(string& mainExp, string& subExp, string& expLength, string& decodeMethod) {
	//Gets main exp number.
	mainExp = valueCheck("Please enter the main experiment number: ", 4);
	//Gets sub-exp number.
	subExp = valueCheck("Please enter the sub-experiment number: ", 3);
	const int lengthOptionsSize = 3;
	string lengthOptions[lengthOptionsSize] = { "1hr", "5hr", "30hr" };
	//Get experiment length, error check to see if input matches list of possible experiments.
	expLength = evalLoop("Please enter the length of the experiment you want to run (e.g. \"1hr\", \"5hr\", \"30hr\"...)", lengthOptions, lengthOptionsSize);
	const int decodeOptionsSize = 1;
	string decodeOptions[decodeOptionsSize] = { "RandomLDAExperiment" };
	decodeMethod = evalLoop("Please enter the form of decode you wish to perform.", decodeOptions, decodeOptionsSize);
}

//Uses a getline input and returns whatever is entered.
string getUserInput() {
	string userInput;
	getline(cin, userInput);
	return userInput;
}

//Checks to see that all values are numerical, and there is a predetermined number of values.
string valueCheck(string prompt, int numOfValues) {
	string input;
	bool loop = 1;
	while (loop == 1) {
		loop = 0;
		cout << prompt << "\n> ";
		input = getUserInput();
		if (input.size() == numOfValues) {
			for (int i = 0; i < input.size(); i++) {
				if (!isdigit(input[i])) {
					loop = 1;
				}
			}
		}
		else {
			loop = 1;
		}
		if (loop == 1) {
			cout << "ERROR: invalid input. Input should be all numbers and " << numOfValues << " digits long.\n";
		}
	}
	return input;
}