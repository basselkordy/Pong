#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

sf::String playerInput;
sf::Text playerText;
sf::Text playerNameLeader;
sf::Text playerScoreLeader;
sf::Font font;
const int LEADERBOARD_SIZE = 5;

//Read leaderboard from text file named "leaderboard.txt" and save the data into a vector of pairs
//First = Name of player
//Second = # of wins for that player
vector <pair<string, int>> leaderboard;

void getLeaderboard()
{
    ifstream infile;
    infile.open("leaderboard.txt");
    string user;
    int score;
    while (infile >> user >> score)
    {
        leaderboard.push_back({ user,score });
    }
    infile.close();
}

//Use the get leaderboard function to load updated text file into a vector of pairs
//Iterate over the first five elements and draw them to the screen, altering their positions by
// 100 every time

void viewLeaderboard(RenderWindow& window)
{
    font.loadFromFile("resources/fonts/Pacifico.ttf");
    getLeaderboard();
    playerNameLeader.setFont(font);
    playerNameLeader.setCharacterSize(40);
    playerNameLeader.setPosition(100.f, 100.f);
    playerNameLeader.setFillColor(Color::White);

    playerScoreLeader.setFont(font);
    playerScoreLeader.setCharacterSize(40);
    playerScoreLeader.setFillColor(Color::White);
    int currentLeaderBoardSize = leaderboard.size();
    for (int i = 1; i <= min(LEADERBOARD_SIZE, currentLeaderBoardSize); i++)
    {
        playerNameLeader.setPosition(100.f, 100.f * i);
        playerNameLeader.setString(leaderboard[i-1].first);

        std::ostringstream scores;
        scores << leaderboard[i-1].second;
        playerScoreLeader.setPosition(400.f, 100.f * i);
        playerScoreLeader.setString(scores.str());

        window.draw(playerNameLeader);
        window.draw(playerScoreLeader);
    }
    leaderboard.clear();
}

//Sorting function to sort the vector of pairs in descending order, according to the second variable (score)
bool sortBySec(const pair <string, int>& a, const pair <string, int>& b)
{
    return a.second < b.second;
}


//Sort the vector of pairs(leaderboard) and print it's output in a temporary file named "leaderboardTemp.txt"
//Delete "leaderboard.txt"
//Rename "leaderboardTemp.txt" to "leaderboard.txt"
void updateLeaderboard()
{
    ofstream outfile;
    outfile.open("leaderboardTemp.txt");
    sort(leaderboard.rbegin(), leaderboard.rend(), sortBySec);
    for (auto it : leaderboard)
    {
        outfile << it.first << " " << it.second << endl;
    }
    outfile.close();
    remove("leaderboard.txt");
    rename("leaderboardTemp.txt", "leaderboard.txt");
}

//Get player name and search in leaderboard, if it doesn't exist, add it to the leaderboard with a score of 0
void addPlayers(string player)
{
    getLeaderboard();
    bool isFound = false;
    for (int i = 0; i < player.size(); i++)
    {
        player[i] = tolower(player[i]);
    }
    for (int i = 0; i < leaderboard.size(); i++)
    {
        if (player.compare(leaderboard[i].first) == 0)
        {
            isFound = true;
        }
    }
    if (!isFound)
    {
        leaderboard.push_back({ player, 0 });
    }
    updateLeaderboard();
    leaderboard.clear();
}


//Load the latest leaderboard into a vector of pairs
//Add a win to the player's score variable
//print the leaderboard into the the text file
//clear the leaderboard from memory
void gameOver(string player)
{
    getLeaderboard();
    for (int i = 0; i < player.size(); i++)
    {
        player[i] = tolower(player[i]);
    }
    for (int i = 0; i < leaderboard.size(); i++)
    {
        if (player.compare(leaderboard[i].first) == 0)
        {
            leaderboard[i].second++;
        }
    }
    updateLeaderboard();
    leaderboard.clear();
}

