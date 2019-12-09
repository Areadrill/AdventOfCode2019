#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>

#define pairOfShorts pair<int16_t, int16_t>

using namespace std;

vector<pairOfShorts> processMovements(string &movements) {
    vector<pairOfShorts> positions;
    pairOfShorts currentPosition(0, 0);
    positions.push_back(currentPosition);

    while(movements != "") {
        string token = movements.substr(0, movements.find(","));

        char direction = token.at(0);
        int units = stoi(token.substr(1, token.size() - 1));

        switch(direction) {
            case 'U':
                currentPosition = pairOfShorts(currentPosition.first, currentPosition.second + units);
                positions.push_back(currentPosition);
                break;
            case 'R':
                currentPosition = pairOfShorts(currentPosition.first + units, currentPosition.second);
                positions.push_back(currentPosition);
                break;
            case 'D':
                currentPosition = pairOfShorts(currentPosition.first, currentPosition.second - units);
                positions.push_back(currentPosition);
                break;
            case 'L':
                currentPosition = pairOfShorts(currentPosition.first - units, currentPosition.second);
                positions.push_back(currentPosition);
                break;
            default:
                exit(-1);
        }

        movements = movements.find(",") == string::npos ? "" : movements.substr(movements.find(",") + 1, movements.size() - 1);
    }

    return positions;
}

vector<int> locateCrossings(vector<pairOfShorts> &cable1Positions, vector<pairOfShorts> &cable2Poitions) {
    vector<int> crossings;

    for (int i = 0; i < cable1Positions.size() - 1; i++) {
        pairOfShorts pos1 = cable1Positions[i];
        pairOfShorts pos2 = cable1Positions[i+1];

        for (int j = 0; j < cable2Poitions.size()- 1; j++) {
            pairOfShorts otherCablePos1 = cable2Poitions[j];
            pairOfShorts otherCablePos2 = cable2Poitions[j+1];
            
            if (pos1.first != pos2.first) {
                if (otherCablePos1.first != otherCablePos2.first) {
                    continue;
                }

                if (min(otherCablePos1.second, otherCablePos2.second) < pos1.second &&
                    max(otherCablePos1.second, otherCablePos2.second) > pos1.second &&
                    min(pos1.first, pos2.first) < otherCablePos1.first &&
                    max(pos1.first, pos2.first) > otherCablePos1.first) {
                        crossings.push_back(abs(otherCablePos1.first) + abs(pos1.second));
                        continue;
                }
            } else {
                if (otherCablePos1.second != otherCablePos2.second) {
                    continue;
                }

                if (min(otherCablePos1.first, otherCablePos2.first) < pos1.first &&
                    max(otherCablePos1.first, otherCablePos2.first) > pos1.first &&
                    min(pos1.second, pos2.second) < otherCablePos1.second &&
                    max(pos1.second, pos2.second) > otherCablePos1.second) {
                        crossings.push_back(abs(pos1.first) + abs(otherCablePos1.second));
                }
            }
        }
    }

    return crossings;
}

int main() {
    ifstream inputFile("input.txt");

    string cable1Movements;
    getline(inputFile, cable1Movements);
    
    vector<pairOfShorts> cable1Positions = processMovements(cable1Movements);

    string cable2Movements;
    getline(inputFile, cable2Movements);
    
    vector<pairOfShorts> cable2Positions = processMovements(cable2Movements);

    vector<int> crossingPoints = locateCrossings(cable1Positions, cable2Positions);

    cout << "Smallest: " << *min_element(crossingPoints.begin(), crossingPoints.end()) << endl;
}