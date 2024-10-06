#include <iostream>
#include <fstream>  // For file handling
#include <sstream>  // For parsing the file line by line
#include <vector>   // To store data
using namespace std;

// Define a struct to hold team data
struct Team {
    string name;
    string localTown;
    string stadium;
};

int main() {
    string filename;

    // Ask the user to input the file name
    cout << "Enter the CSV filename (with extension): ";
    cin >> filename;

    cout << "Trying to open file: " << filename << endl;  // Debugging output

    // Open the user-specified CSV file
    ifstream file(filename);

    // Check if the file opened successfully
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return 1;
    }

    // If the file opened successfully, output a message
    cout << "File opened successfully!" << endl;

    string line;
    vector<Team> teams;  // Vector to hold the data for each team

    // Read and print the contents of the file to ensure it's working
    cout << "Reading file contents:" << endl;

    // Skip the first line (header)
    getline(file, line);  // Read and discard the header line

    // Parse each line of the file
    while (getline(file, line)) {
        stringstream ss(line);  // Create a string stream for each line
        Team team;              // Temporary variable to hold one team's info

        // Extract each field separated by commas
        getline(ss, team.name, ',');       // Get team name
        getline(ss, team.localTown, ',');  // Get local town
        getline(ss, team.stadium, ',');    // Get stadium

        teams.push_back(team);  // Add the team data to the main teams vector
    }

    // Use traditional for loop with indexes
    for (size_t i = 0; i < teams.size(); i++) {
        // Output the parsed data using index
        cout << "Team #" << (i + 1) << ": " << endl;
        cout << "Team Name: " << teams[i].name << endl;
        cout << "Local Town: " << teams[i].localTown << endl;
        cout << "Stadium: " << teams[i].stadium << endl;
        cout << "-----------------------------" << endl;
    }

    return 0;
}
