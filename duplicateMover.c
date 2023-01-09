#include <stdio.h>
#include <limits.h>
#include<stdlib.h>


// merge function used in merge sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = malloc(n1 * sizeof(int));  // dynamically allocate memory for L
    int* R = malloc(n2 * sizeof(int));  // dynamically allocate memory for R
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);  // free memory allocated for L
    free(R);  // free memory allocated for R
}

// merge sort function
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// binary search function
int binarySearch(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] < target) {
            low = mid + 1;
        }
        else if (arr[mid] > target) {
            high = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1;
}

int moveDuplicates(int arr[],int size){
    int res = 0;
    int duplicates = 0;
    int* dummy = malloc(2*size * sizeof(int));
    int dummySize = 1;
    int front = 0;
    int i = 0;
    int back = size - 1;
    int counter = 0;
  
    for (i; i < size; i++)
    {
        if (i == 0)
        {
            dummy[front] = arr[i];
            front++;
           
        }
        else
        {
            mergeSort(dummy, 0, dummySize-1);
            if (binarySearch(dummy,front, arr[i]) != -1)  //duplicate
            {
                dummy[back] = arr[i];
                back--;
                duplicates=duplicates+1;
                
            }
            else
            {
                dummy[front] = arr[i];
                front++;
                dummySize++;
                dummy[size + counter] = arr[i];
                counter++;
            }
        }

       
    }

 
    res = duplicates;
    back = size - 1;
     while (duplicates > 0)
     {
         arr[back] = dummy[back];
         back-- ;
         duplicates--;


     }

     i = 1;
  
    for (i; i < counter; i++)
     {
        
         arr[i]=dummy[i+size];
     }

    free(dummy);
    return counter;
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}




int main(void) {
    int arr[] = { 7,3,1,2,7,9,3,2,5,9,6,2 };
    printf("%s", "Input array: ");
    printArray(arr, 12);

    int duplicates = moveDuplicates(arr, 12);
  
    printf("%s", "Output: ");
    printArray(arr, 12);
       

   
}
