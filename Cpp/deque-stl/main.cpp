#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

void printKMax(int arr[], int n, int k)
{
    deque<int> dq;
    int max;

    /* Check boundaries. */
    if (n <= 0 || k <= 0 || k > n) {
        return;
    }

	/* Init max with first array item. */
    max = arr[0];

    /* Fill up deque with "k" elements. */
    for (int i = 0; i < k; i++) {
        /* Add the item to deque. */
        dq.push_back(arr[i]);
        /* Calculate max. */
        if (max < arr[i]) {
            max = arr[i];
        }
    }

    /* Loop through array's items starting from "k". */
    for (int i = k; i < n; i++) {
        /* Print out "k"-sized array max value. */
		cout << max << " ";
        /* Remember oldest item in deque. */
        int pop = dq.front();
        /* Remove oldest item from deque. */
        dq.pop_front();
        /* If popped item was "max" value and deque is not empty. */
        if ((pop == max) && (dq.size() > 0)) {
			/* Overwrite max with first deque item. */
            max = dq[0];
            /* Loop through deque items. */
            for (int j = 1; j < dq.size(); j++) {
                /* Find new max. */
                if (dq[j] > max) {
                    max = dq[j];
                }
            }
        }
        /* Add current item to deque. */
        dq.push_back(arr[i]);
        /* If current item is greater than "max" or deque has only one item now. */
        if ((arr[i] > max) || (dq.size() == 1)) {
			/* Overwrite max. */
            max = arr[i];
        }
    }

    /* There will be "k" last items left in deque after the loop. */
    /* Print out "k"-sized array max value. */
	cout << max << endl;

	/* Clean up. */
    dq.clear();
}

int main()
{
    int t;
    cin >> t;
    while(t > 0) {
        int n, k;
        cin >> n >> k;
        int i;
        int *arr = new int[n];
        for (i = 0; i < n; i++)
            cin >> arr[i];
        printKMax(arr, n, k);
        t--;
        delete[] arr;
    }
    return 0;
}
