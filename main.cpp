
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>  // for shuffle
#include <random>     // for random generator


// Structure for a Team
struct Team {
    std::string name;
    std::string town;
    std::string stadium;
};

// Structure for a Match
struct Match {
    Team home;
    Team away;
    bool derby;  // Local town match flag
    int leg;     // 1 for first leg, 2 for second leg
};

// Structure for a Weekend
struct Weekend {
    Match matches[2];  // 2 matches per weekend
};

// Utility class for generating and managing fixtures
class Util {
private:
    bool havePlayedBefore(Team a, Team b);

public:
    std::vector<Team> teams;
    std::vector<Match> matches;
    std::vector<Weekend> weekendGames;

    void readFile(std::string filename);
    void writeFile(std::string filename);

    void createMatches();
    void createWeekendGames();
    void shuffleMatches();
    void sortMatches();

    void displayFixtures();
    void displayMatches();
    void printTeams();
    int getFixturesCount();
    int getTeamCount();
};

// Check if teams have played each other before
bool Util::havePlayedBefore(Team a, Team b) {
    for (auto match : matches) {
        if ((match.home.name == a.name && match.away.name == b.name) ||
            (match.home.name == b.name && match.away.name == a.name)) {
            return true;
        }
    }
    return false;
}

// Read teams from a CSV file
void Util::readFile(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string name, town, stadium;
        while (file >> name >> town >> stadium) {
            teams.push_back({name, town, stadium});
        }
        file.close();
    }
}

// Write fixtures to a CSV file
void Util::writeFile(std::string filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& weekend : weekendGames) {
            for (const auto& match : weekend.matches) {
                file << match.home.name << " vs " << match.away.name << ", "
                     << "Leg " << match.leg << "\n";
            }
        }
        file.close();
    }
}

// Create match pairings for teams
void Util::createMatches() {
    for (size_t i = 0; i < teams.size(); ++i) {
        for (size_t j = i + 1; j < teams.size(); ++j) {
            Match match1 = {teams[i], teams[j], teams[i].town == teams[j].town, 1};
            Match match2 = {teams[j], teams[i], teams[i].town == teams[j].town, 2};
            matches.push_back(match1);
            matches.push_back(match2);
        }
    }
}

// Shuffle matches using Fisher-Yates algorithm
void Util::shuffleMatches() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(matches.begin(), matches.end(), g);
}

// Sort matches by leg (1 first, then 2)
void Util::sortMatches() {
    std::sort(matches.begin(), matches.end(), [](Match a, Match b) {
        return a.leg < b.leg;
    });
}

// Create weekend games (2 matches per weekend)
void Util::createWeekendGames() {
    for (size_t i = 0; i < matches.size(); i += 2) {
        Weekend weekend = {matches[i], matches[i + 1]};
        weekendGames.push_back(weekend);
    }
}

// Display fixtures on the console
void Util::displayFixtures() {
    for (const auto& weekend : weekendGames) {
        for (const auto& match : weekend.matches) {
            std::cout << match.home.name << " vs " << match.away.name
                      << " (Leg " << match.leg << ")\n";
        }
        std::cout << "----------\n";
    }
}

// Display matches on the console
void Util::displayMatches() {
    for (const auto& match : matches) {
        std::cout << match.home.name << " vs " << match.away.name
                  << " (Leg " << match.leg << ")\n";
    }
}

// Display teams on the console
void Util::printTeams() {
    for (const auto& team : teams) {
        std::cout << team.name << " from " << team.town << " at " << team.stadium << "\n";
    }
}

// Get the number of fixtures
int Util::getFixturesCount() {
    return matches.size();
}

// Get the number of teams
int Util::getTeamCount() {
    return teams.size();
}

// Main function
int main() {
    Util util;
    util.readFile("teams.csv");  // Read teams from a file
    util.createMatches();        // Generate match pairings
    util.shuffleMatches();       // Shuffle the matches
    util.sortMatches();          // Sort matches by leg
    util.createWeekendGames();   // Create weekend games

    util.displayFixtures();      // Display fixtures on the console
    util.writeFile("fixtures.csv");  // Write fixtures to a CSV file

    return 0;
}
