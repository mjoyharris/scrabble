#include <iostream>
#include<fstream>
#include <string>
#include <istream>
#include <map>
#include <vector>
using namespace std;

class Graph
{
public:
    map<string, pair<int,int>> wordMap;
    int numResponses;
    vector<char> letterBank;
    vector<string> selectedWords;
    vector<int> selectedScores;

    //number of vertices is equal to amount of words in the data set
    int numVert = 279496;

    //adjaceny matrix implementation
    string vertArr[279496][279496];

    //functions
    void add_edge(int newWord);
    int readWords();
    void menu();
    int calcPoints(string word);
    void findCombos();
    void printResults();

    //variables
    int count;
};

//adds edge between verties
void Graph::add_edge(int newWord) {

    int oldWord;
    //if something is a subset of newWord
    //if the word is within that word in some combo (aka same letters and <= size)
    //then, [newWord][oldWord] = 1

    //if newWord is a subset of something
    //then, [oldWord][newWorld] = 1;
    vertArr[newWord][oldWord] = 1;
    vertArr[oldWord][newWord] = 1;
}

int Graph::calcPoints(string word)
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

int Graph::readWords()
{
    ifstream file;

    string word;

    //drag file into "cmake-build-debug" folder
    //downloaded from keggle but then changed into a txt file with only the first column
    file.open("scrabble_dict.txt");

    //an error associated with opening the file
    if (!file) {
        cout << "Unable to open file";

        //terminate
        exit(1);
    }

    count = 0;

    //loads in each line
    while (file >> word) {

        //map key- word, map value- first: count second: scrabble score
        int points = calcPoints(word);
        pair<int, int> myPair;
        myPair.first = count;
        myPair.second = points;
        
        wordMap.insert({word, myPair});
        
        Graph::add_edge(count);
        count++;
        //calls function to calculate the amount of points that word would attain in the game of scrabble
        /*int points = calcPoints(word);

        //inserts the word with its score into the map
        pair<string, int> myPair;
        myPair.first = word;
        myPair.second = points;
        wordMap.insert(myPair);*/
    }

    file.close();

    return count;
}

void Graph::menu()
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

void Graph::findCombos()
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

void Graph::printResults()
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

    else
    {
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

}

int main() {

    //calls function to read the txt file
    Words wordObject;
    int count = wordObject.readWords();


    cout << count << endl;

    //intro message
   /* cout << "Welcome to \"That’s So Scrabbulous\"" << endl;

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

    }*/

    return 0;
}
