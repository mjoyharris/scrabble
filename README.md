# scrabble

Group 47 Project 3a Proposal
Team Name: Sesquipedalophobes 
Team Members: Noah Harris, Jose Rivas, and Maya Harris
Project Title: That’s So Scrabbulous™ (trademark pending)
Problem: The board game and several app implementations of Scrabble are commonly played by people around the world. Our program will assist users in generating all possible word combinations from imputing their set of letters into an anagram solver. 
Motivation: There are thousands of different combinations of letters that a player can make with their hand. It’s a difficult task to quickly distinguish not only what arrangement would form a word but also what would maximize their score.  
Features: The program will print all the possible words that can be formed by the user’s input onto the screen sorted by its accompanying Scrabble score.
Data: We will be using a public data set from the online site, Kaggle. This collection has the top ⅓ million of most frequently used English words, though the frequency will not be used in the scope of this project. https://www.kaggle.com/rtatman/english-word-frequency/version/1
Tools: C++
Visuals: Menu driven program where user inputs the number of letters, the letters they want to include, and the number of top scoring responses.
Strategy: Our plan is to use a map and a graph to store our nodes of words. The first data structure, map, will have each word in our dataset as the key and its corresponding Scrabble score as its value. Secondly, our graph will be unweighted and connected with each node adjacent solely to its preceding node. The Scrabble score for the nodes in the graph will be calculated after we’ve found the matching word.
Distribution of responsibility and roles: We are going to split up main responsibilities to each member of the group but will meet online to work collaboratively on each topic. 
Jose - graph code, timing graph code, visuals
Noah - graph code, reading in database and anagram solving code
Maya - map code, timing map code, menu
References: Canvas files and our data set acquired from Kaggle, https://www.kaggle.com/rtatman/english-word-frequency/version/1

#
