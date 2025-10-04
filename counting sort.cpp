#include <iostream>
#include <vector>
using namespace std;

void countingSort(vector<int>& arr)
{
    int n = arr.size();
    int maxElement = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > maxElement)
            maxElement = arr[i];
    }

    vector<int> count(maxElement + 1, 0);
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    int index = 0;
    for (int i = 0; i <= maxElement; i++)
    {
        while (count[i] > 0)
        {
            arr[index++] = i;
            count[i]--;
        }
    }
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    countingSort(arr);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

