#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <thread>
#include <chrono>

#define NOTIFY_THRESHOLD 5
#define NOTIFY_INTERVAL 10 // seconds

using namespace std;

// Data structure to hold data
struct DataPoint {
    string label;
    int value;
};

// Function to read data from file
map<string, int> readData(const string& filename) {
    map<string, int> data;
    ifstream file(filename);
    string line, label;
    int value;
    while (getline(file, line)) {
        sscanf(line.c_str(), "%s %d", &label[0], &value);
        data[label] = value;
    }
    file.close();
    return data;
}

// Function to visualize data
void visualizeData(const map<string, int>& data) {
    for (const auto& point : data) {
        cout << point.first << ": " << point.second << endl;
    }
}

// Function to notify if value exceeds threshold
void notify(const string& label, int value) {
    if (value > NOTIFY_THRESHOLD) {
        cout << "Notification: " << label << " has exceeded " << NOTIFY_THRESHOLD << endl;
    }
}

int main() {
    string filename("data.txt");
    map<string, int> data = readData(filename);
    visualizeData(data);

    while (true) {
        this_thread::sleep_for(chrono::seconds(NOTIFY_INTERVAL));
        data = readData(filename);
        for (const auto& point : data) {
            notify(point.first, point.second);
        }
    }

    return 0;
}