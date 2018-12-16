#include<bits/stdc++.h>

using namespace std;

#include <vector>
#include <algorithm>

// Define the structs Workshop and Available_Workshops.

struct Workshop {
    int timeStart, timeEnd, duration;
    Workshop() {
        timeStart = 0;
        timeEnd = 0;
        duration = 0;
    }
};

bool operator< (Workshop a, Workshop b) {
    return (a.timeEnd < b.timeEnd);
}

struct Available_Workshops {
    int n;
    vector<Workshop> arr;

    /* Constructor. */
    Available_Workshops(int n) {
        this->n = n;
        /* Allocate Workshop vector. */
        arr = vector<Workshop>(n);
    }
};

// Implement the functions initialize and CalculateMaxWorkshops

Available_Workshops* initialize(int start_time[], int duration[], int n)
{
    Available_Workshops *aw = new Available_Workshops(n);

    /* Loop through all Workshops. */
    for (int i = 0; i < n; i++) {
        /* Overwrite Workshop structure values in the vector with given ones. */
        aw->arr[i].timeStart = start_time[i];
        aw->arr[i].timeEnd = start_time[i] + duration[i];
        aw->arr[i].duration = duration[i];
    }

    return aw;
}

int CalculateMaxWorkshops(Available_Workshops* ptr) 
{
    int max = 0;
    int timeEndLast = 0;

    /* Workshops will be sorted by their end times
       to solve the problem using "Interval scheduling" algorithm. */

    /* Sort Workshop array using overloaded "<" comparison. */
    std::sort(ptr->arr.begin(), ptr->arr.end());

    /* Loop through Workshop array. */
    for (int i = 0; i < ptr->n; i++) {
        /* Check if this Workshop can be attended. */
        if (ptr->arr[i].timeStart >= timeEndLast) {
            max++;
            timeEndLast = ptr->arr[i].timeEnd;
        }
    }

    /* Clean up. */
    ptr->arr.clear();
    free(ptr);

    return max;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
