#include <iostream>
#include<fstream>
#include <string>
#include <istream>
#include <map>
#include <vector>
using namespace std;

class Words
{
private:
    map<string, int> wordMap;
    int numResponses;
    vector<char> letterBank;
    vector<string> selectedWords;
    vector<int> selectedScores;

public:
    void readWords();
    void menu();
    int calcPoints(string word);
    void findCombos();
    void printResults();

};

int Words::calcPoints(string word)
{
    int totalScore = 0;
    int numLength = word.length();

    //adds up all the points each letter in the word would receive
    for (int i = 0; i < numLength; i++) {
        char letter = word[i];
        int worth = 1;

        letter = toupper(letter);

        switch (letter) {
            case 'D' :
                worth = 2;
                break;
            case 'G' :
                worth = 2;
                break;
            case 'B' :
                worth = 3;
                break;
            case 'C' :
                worth = 3;
                break;
            case 'M' :
                worth = 3;
                break;
            case 'P' :
                worth = 3;
                break;
            case 'F' :
                worth = 4;
                break;
            case 'H' :
                worth = 4;
                break;
            case 'V' :
                worth = 4;
                break;
            case 'W' :
                worth = 4;
                break;
            case 'Y' :
                worth = 4;
                break;
            case 'K' :
                worth = 5;
                break;
            case 'J' :
                worth = 8;
                break;
            case 'X' :
                worth = 8;
                break;
            case 'Q' :
                worth = 10;
                break;
            case 'Z' :
                worth = 10;
                break;
            default:
                worth = 1;
        }

        totalScore = totalScore + worth;
    }

    //returns total points
    return totalScore;
}

void Words::readWords()
{
    ifstream file;

    string word;

    //drag file into "cmake-build-debug" folder
    //downloaded from keggle but then changed into a txt file with only the first column
    file.open("my_dictionary.txt");

    //an error associated with opening the file
    if (!file) {
        cout << "Error: unable to open file";

        //terminate
        exit(1);
    }

    //loads in each line
    while (file >> word) {

        //calls function to calculate the amount of points that word would attain in the game of scrabble
        int points = calcPoints(word);

        //inserts the word with its score into the map
        pair<string, int> myPair;
        myPair.first = word;
        myPair.second = points;
        wordMap.insert(myPair);
    }

    file.close();
}

void Words::menu()
{
    letterBank.clear();

    cout << "How many letters do you want to include?" << endl;
    int numLetters;
    cin >> numLetters;

    cout << "How many of the top responses do you want to hear?" << endl;
    cin >> numResponses;

    while (numLetters > 0)
    {
        cout << "Please input a letter" << endl;
        char letter;
        cin >> letter;
        letterBank.push_back(letter);
        numLetters--;
    }
}

void Words::findCombos()
{
    int count = -1;
    vector<char> letterBankCopy = letterBank;
    selectedWords.clear();
    selectedScores.clear();
    map<string, int>::iterator it;
    char selected;
    bool found;
    bool bigFound;

    for (it = wordMap.begin(); it != wordMap.end(); it++)
    {
        bigFound = true;
        //finds key in map
        string target = it->first;

        letterBank = letterBankCopy;

        //sees if all the letters exists
        if (target.length() <= letterBank.size()) {

            for (int i = 0; i < target.length(); i++) {
                char letter = target[i];

                found = false;

                //does that letter exist
                for (int i = 0; i < letterBank.size(); i++) {
                    selected = letterBank[i];

                    if (letter == selected) {
                        found = true;
                        letterBank[i] = 0;
                    }
                }

                if (!found) {
                    bigFound = false;
                }

            }

            //means all the letters were found and target word can be used in the game
            if (bigFound)
            {
                    selectedWords.push_back(target);
                    selectedScores.push_back(wordMap[target]);

            }

        }
    }
    sort(selectedScores.begin(), selectedScores.end());

}

void Words::printResults()
{

    //case that the user wants more results than their letters can make
    if (selectedWords.size() < numResponses)
    {
        for (int i = 0; i < selectedWords.size(); i++)
        {
            cout << "Sorry! There isn't " << numResponses << " possible combos. Here are the " << selectedWords.size() << " we have." << endl;
            cout << selectedWords[i] << " with a score of ";
            cout << wordMap[selectedWords[i]] << endl;
        }
    }

    int bestScore = selectedScores[numResponses];
    int count = 0;

    for (int i = 0; i < selectedWords.size(); i++)
    {
        if (wordMap[selectedWords[i]] >= bestScore && count < numResponses)
        {
            cout << selectedWords[i] << " with a score of ";
            cout << wordMap[selectedWords[i]] << endl;
            count++;
        }
    }

}

int main() {

    //calls function to read the txt file
    Words wordObject;
    wordObject.readWords();

    //intro message
    cout << "Welcome to \"That’s So Scrabbulous\"" << endl;

    //first time menu
    wordObject.menu();

    //user can use program until they decide to quit
    bool continuePlaying = true;
    while (continuePlaying)
    {
        wordObject.findCombos();

        wordObject.printResults();

        string answer;
        cout << "Do you want to ask again? (yes or no)" << endl;
        cin >> answer;

        if (answer == "no")
            continuePlaying = false;
        else
        {
            wordObject.menu();
        }

    }

    return 0;
}
