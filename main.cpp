//Project 3: Scrabble
//Group 47

#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;


//the graph implementation
class Graph
{
public:
    map<string, pair<int, int>> wordMap;
    int numResponses;
    vector<char> letterBank;
    vector<string> selectedWords;
    vector<pair<int, int>> selectedScores;

    //number of vertices is equal to amount of words in the data set
    //our data set is 279496 words
    int V;

    vector<vector<int>> adj;

    //constructor
    Graph();

    //functions
    void addEdge(string newWordStr, int newWordInt);
    void menu();
    void findCombos(string newWordStr);
    void printResults();
    string getKey(int i);
    bool within(string str1, string str2);
    int calcPoints(string word);
    void readWords();

    //the two algorithms
    void BFS(int s);
    void DFS(int s);

    //variables

    //user entries
    string input;
    string importantWord;
    int count;
    int numLetters;
};

//constructor
Graph::Graph()
{
    numResponses = 0;
    count = 0;
    //number from downloaded data set
    this->V = 279496;
    adj.resize(V);
}

//adds edge between vertices
void Graph::addEdge(string newWordStr, int newWordInt) {

    //a vertex's vector will contain all the words that it itself can create

    //only proceeds if word is a viable candidate (example: longer than number of letters user imputs)
    if ((newWordStr.length() <= input.length()) && (within(newWordStr,input)))
    {
        //calls function to calculate the amount of points that word would attain in the game of scrabble
        int points = calcPoints(newWordStr);

        //map key- word, map value- first: count second: scrabble score
        pair<int, int> myPair;
        myPair.first = count;
        myPair.second = points;

        //stores in a map
        wordMap.insert({ newWordStr, myPair });

        //all matches that appear thus far appear in selectedWords
        findCombos(newWordStr);

        //puts in vertex vector
        for (int i = 0; i < selectedWords.size(); i++)
        {
            adj[wordMap[selectedWords[i]].first].push_back(newWordInt);
        }
    }
}

//converts the word into a scrabble score
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
            case 'D':
                worth = 2;
                break;
            case 'G':
                worth = 2;
                break;
            case 'B':
                worth = 3;
                break;
            case 'C':
                worth = 3;
                break;
            case 'M':
                worth = 3;
                break;
            case 'P':
                worth = 3;
                break;
            case 'F':
                worth = 4;
                break;
            case 'H':
                worth = 4;
                break;
            case 'V':
                worth = 4;
                break;
            case 'W':
                worth = 4;
                break;
            case 'Y':
                worth = 4;
                break;
            case 'K':
                worth = 5;
                break;
            case 'J':
                worth = 8;
                break;
            case 'X':
                worth = 8;
                break;
            case 'Q':
                worth = 10;
                break;
            case 'Z':
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

//asks the user for their input
void Graph::menu()
{
    letterBank.clear();

    cout << "How many of the top responses do you want to hear?" << endl;
    cin >> numResponses;

    cout << "Please type your letters as a string" << endl;
    cin >> input;

    numLetters = input.length();
}

//this finds what words are within another word
void Graph::findCombos(string target)
{
    //empties vector from previous iterations
    selectedWords.clear();

    //loops through map to find them
    for (auto it = wordMap.begin(); it != wordMap.end(); it++)
    {
        if (within(target, it->first))
        {
            selectedWords.push_back(it->first);
        }
    }
}

//prints the possible anagrams with their respective scores
void Graph::printResults()
{
    int numCon = wordMap[importantWord].first;
    int count = numResponses;
    int score = 999;
    int specScore = 0;

    vector<int> scores;

    //find the n top scores out of the vector
    for (int i = 0; i < adj[numCon].size(); i++)
    {
        string keyy = getKey(adj[numCon][i]);
        scores.push_back(wordMap[keyy].second);
    }

    //sorts the vector in order to find the highest
    sort(scores.begin(), scores.end());

    //prints out n highest
    for (int j = 0; j < numResponses; j++)
    {
        string keyy = getKey(adj[numCon][j]);
        cout << "Word: " << keyy << " Scrabble Score: " << wordMap[keyy].second << endl;
    }

}

//helper function for findCombos that sees if one string is in another
bool Graph::within(string str1, string str2)
{
    bool found = false;
    bool bigFound = false;

    //cant be within if longer
    if (str1.length() > str2.length())
    {
        return false;
    }

    //for the purposes of our code design, we dont want it to return itself
    if (str1 == str2) {
        return false;
    }

    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    if (str1.length() == str2.length()) {
        if (str1 == str2) {
            return true;
        }
        else {
            return false;
        }
    }

    // compares sorted strings
    for (int i = 0; i < str1.length(); i++)
    {
        found = false;
        for (int j = 0; j < str2.length(); j++)
        {
            if (toupper(str1[i]) == toupper(str2[j]))
            {
                found = true;
                //this is important for repeated letters
                str2[j] = -1;
            }
        }
        if (!found)
        {
            return false;
        }
    }
    return true;
}

//breadth first search algorithm
void Graph::BFS(int src) {

    //code inspo comes from powerpoint slides
    bool found = false;
    vector<bool> visited(adj.size());

    vector<int> sorted;
    queue<int> q;

    visited[src] = true;
    q.push(src);

    int u;

    //BFS uses a queue
    while(!q.empty())
    {
       if(adj[q.front()].size() >= 1)
       {
           u = q.front();

           //this "important word" is the largest word that can be created by the user's input
           if (getKey(u) != "0" && !found)
           {
               importantWord = getKey(u);
               found = true;
           }

           q.pop();

           for (int v: adj[u])
           {
               if (!visited[v])
               {
                   visited[v] = true;
                   sorted.push_back(v);
               }
           }
           sort(sorted.begin(), sorted.end());
           for (int j = 0; j < sorted.size(); j++)
           {
               q.push(sorted[j]);
           }
           sorted.clear();
       }
       else
       {
           q.pop();
           q.push(u++);
       }
    }

}

//depth first search
void Graph::DFS(int src) {
    // your code
    bool found = false;
    vector<bool> visited(adj.size());

    vector<int> sorted;
    stack<int> s;

    visited[src] = true;
    s.push(src);

    int u;

    while(!s.empty())
    {
        if(adj[s.top()].size() >= 1)
        {
            u = s.top();

            if (getKey(u) != "0" && !found)
            {
                importantWord = getKey(u);
                found = true;
            }

            s.pop();

            for (int v: adj[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    sorted.push_back(v);
                }
            }
            sort(sorted.begin(), sorted.end());
            for (int j = 0; j < sorted.size(); j++)
            {
                s.push(sorted[j]);
            }
            sorted.clear();
        }
        else
        {
            s.pop();
            s.push(u++);
        }
    }

}

//reverse map function
string Graph::getKey(int i)
{
    vector<char> comparing;
    auto it = wordMap.begin();

    while (it != wordMap.end())
    {
        if (it->second.first == i)
        {
            return it->first;
        }
        it++;
    }

    return 0;
}

void Graph::readWords()
{
    ifstream file;

    string word;

    //drag file into "cmake-build-debug" folder
    //downloaded from keggle but then changed into a txt file with only the first column
    //realized ^that keggle data set was flawed and found a new one
    file.open("scrabble_dict.txt");

    //an error associated with opening the file
    if (!file) {
        cout << "Unable to open file";

        //terminate
        exit(1);
    }

    //running count of entry number
    count = 0;

    //loads in each line
    while (file >> word) {

            Graph::addEdge(word, count);

            count++;
    }

    file.close();
}

int main() {

    //calls function to read the txt file
    Graph graph;

    //intro message
    cout << "Welcome to \"That’s So Scrabbulous\"" << endl;

    string answer;
    cout << "For project purposes, should we use DFS or BFS?" << endl;
    cin >> answer;

    //first time menu
    graph.menu();

    //loads words in
    graph.readWords();

    if (answer == "DFS")
    {
        graph.DFS(0);
    }
    else
    {
        graph.BFS(0);
    }

    //shows the anagrams
    graph.printResults();
    

    return 0;
}
