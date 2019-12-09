#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <climits>
#include <tuple>

#define pairOfShorts pair<int16_t, int16_t>
#define crossingInfo tuple<pair<int, int>, pairOfShorts, bool>

using namespace std;

vector<pairOfShorts> processMovements(string movements) {
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

vector<int> sumSteps(string movements) {
    vector<int> stepsAccumulation;

    stepsAccumulation.push_back(0);

    while(movements != "") {
        string token = movements.substr(0, movements.find(","));

        int units = stoi(token.substr(1, token.size() - 1));

        stepsAccumulation.push_back(stepsAccumulation[stepsAccumulation.size() - 1] + units);

        movements = movements.find(",") == string::npos ? "" : movements.substr(movements.find(",") + 1, movements.size() - 1);
    }

    return stepsAccumulation;
}

vector<crossingInfo> locateCrossings(vector<pairOfShorts> &cable1Positions, vector<pairOfShorts> &cable2Poitions) {
    vector<crossingInfo> crossings;

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
                        crossings.push_back(make_tuple(pair<int, int>(i, j), pairOfShorts(otherCablePos1.first, pos1.second), true));
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
                        crossings.push_back(make_tuple(pair<int, int>(i, j), pairOfShorts(pos1.first, otherCablePos1.second), false));
                }
            }
        }
    }

    return crossings;
}

unsigned int calculateShortestDistanceCrossing(vector<crossingInfo> &crossings, 
                                               vector<int> &cable1Steps, vector<int> &cable2Steps,
                                               vector<pairOfShorts> &cable1Positions, vector<pairOfShorts> &cable2Positions) {
    unsigned int shortest = INT_MAX;

    for (auto const &crossing: crossings) {
        unsigned int sumOfSteps = cable1Steps[get<0>(crossing).first + 1] + cable2Steps[get<0>(crossing).second + 1];

        if (get<2>(crossing)) {
            sumOfSteps -= abs(cable1Positions[get<0>(crossing).first + 1].first - get<1>(crossing).first);
            sumOfSteps -= abs(cable2Positions[get<0>(crossing).second + 1].second - get<1>(crossing).second);
        } else {
            sumOfSteps -= abs(cable2Positions[get<0>(crossing).second + 1].first - get<1>(crossing).first);
            sumOfSteps -= abs(cable1Positions[get<0>(crossing).first + 1].second - get<1>(crossing).second);
        }

        shortest = min(shortest, sumOfSteps);
    }

    return shortest;
}

int main() {
    ifstream inputFile("input.txt");

    string cable1Movements;
    getline(inputFile, cable1Movements);
    
    vector<pairOfShorts> cable1Positions = processMovements(cable1Movements);
    vector<int> cable1Steps = sumSteps(cable1Movements);

    string cable2Movements;
    getline(inputFile, cable2Movements);
    
    vector<pairOfShorts> cable2Positions = processMovements(cable2Movements);
    vector<int> cable2Steps = sumSteps(cable2Movements);

    vector<crossingInfo> crossingPoints = locateCrossings(cable1Positions, cable2Positions);

    unsigned int fewestSteps = calculateShortestDistanceCrossing(crossingPoints, cable1Steps, cable2Steps, cable1Positions, cable2Positions);

    cout << "Shortest distance: " << fewestSteps << endl;
}