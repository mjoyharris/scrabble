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

class Graph
{
public:
    map<string, pair<int, int>> wordMap;
    int numResponses;
    vector<char> letterBank;
    vector<string> selectedWords;
    vector<pair<int, int>> selectedScores;

    //number of vertices is equal to amount of words in the data set
    int V;
    //int numVert = 279496;
    //vector<int> vertArr[279496];

    //list<int>* adj;
    vector<vector<int>> adj;

    Graph();
    Graph(int V);

    //adjaceny matrix implementation
    //int vertArr[279496][279496];

    //functions
    void addEdge(string newWordStr, int newWordInt);
    void menu();
    void findCombos(string newWordStr);
    void printResults();
    void BFS(int s);
    void DFS(int s);
    string getKey(int i);
    bool within(string str1, string str2);

    //variables

    string input;
    string importantWord;
    int calcPoints(string word);
    int count;
    int numLetters;
    void readWords();
};

Graph::Graph()
{
    numResponses = 0;
    count = 0;
    this->V = 279496;
    adj.resize(V);
    //adj = new vector<int>[V];
}

Graph::Graph(int V)
{
    numResponses = 0;
    count = 0;
    this->V = V;
    adj.resize(V);
    //adj = new vector<int>[V];
}

//adds edge between vertices
void Graph::addEdge(string newWordStr, int newWordInt) {

    //if something is a subset of newWord
    //if the word is within that word in some combo (aka same letters and <= size)
    //then, [newWord][oldWord] = 1

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

        //it wont be a subset of anything that comes after
        for (int i = 0; i < selectedWords.size(); i++)
        {
            adj[wordMap[selectedWords[i]].first].push_back(newWordInt);
            //adj[wordMap[selectedWords[i]].first]
            //vertArr[wordMap[selectedWords[i]].first].push_back(newWordInt);
        }
    }

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

void Graph::menu()
{
    letterBank.clear();

    cout << "How many of the top responses do you want to hear?" << endl;
    cin >> numResponses;

    cout << "Please type your letters as a string" << endl;
    cin >> input;

    numLetters = input.length();

}

void Graph::findCombos(string target)
{
    selectedWords.clear();

    for (auto it = wordMap.begin(); it != wordMap.end(); it++)
    {
        if (within(target, it->first))
        {
            selectedWords.push_back(it->first);
        }
    }
}

void Graph::printResults()
{
    int numCon = wordMap[importantWord].first;
    int count = numResponses;
    int score = 0;
    int specScore = 0;


    for (int i = 0; i < adj[numCon].size(); i++)
    {
        string keyy = getKey(adj[numCon][i]);
        if (wordMap[keyy].second > score && count<6)
        {
            count++;
            specScore = wordMap[keyy].second;
        }
    }

    for (int i = 0; i < adj[numCon].size(); i++)
    {
        string keyy = getKey(adj[numCon][i]);
        if (wordMap[keyy].second <= specScore)
        {
            cout << "Word: " << keyy << " Scrabble Score: " << wordMap[keyy].second;
        }
    }

}

//second is input
bool Graph::within(string str1, string str2)
{
    bool found = false;
    bool bigFound = false;


    if (str1.length() > str2.length())
    {
        return false;
    }

    if (str1 == str2) {
        return false;
    }

    //not sure if this helps i dont think it does
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

    // Compare sorted strings
    for (int i = 0; i < str1.length(); i++)
    {
        found = false;
        for (int j = 0; j < str2.length(); j++)
        {
            if (toupper(str1[i]) == toupper(str2[j]))
            {
                found = true;
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

void Graph::BFS(int src) {
    // your code
    bool found = false;
    vector<bool> visited(adj.size());

    vector<int> sorted;
    queue<int> q;

    visited[src] = true;
    q.push(src);

    int u;

    while(!q.empty())
    {
       if(adj[q.front()].size() >= 1)
       {
           u = q.front();

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
                cout << importantWord << endl;
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

//helper function of BFS
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

    //first time menu
    graph.menu();

    graph.readWords();

    //user can use program until they decide to quit
    bool continuePlaying = true;
    while (continuePlaying)
    {
        graph.DFS(0);

        graph.printResults();

        string answer;
        cout << "Do you want to ask again? (yes or no)" << endl;
        cin >> answer;

        if (answer == "no")
            continuePlaying = false;
        else
        {
            graph.menu();
        }

    }

    return 0;
}
