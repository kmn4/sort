#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/** 要素数5以下の配列の中でk+1番目に小さい値を返す */
int leqfive(int a[], int n, int k)
{
    int i, j, l, z;
    for (i = 1; i < n; i++) {
        for (j = 0; j < i && a[j] < a[i]; j++);
        z = a[i];
        for (l = i; l > j; l--) a[l] = a[l-1];
        a[j] = z;
    }

    return a[k];
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  //int i, j, pivot;
  int i, l, r, pivot;
  int Ap[(n+4)/5];

  if (n <= 5) return leqfive(A, n, k);

  for (i = 0; i < n/5; i++) Ap[i] = leqfive(A+i*5, 5, 2);
  if (n % 5) Ap[i] = leqfive(A+i*5, n-i*5, (n-i*5)/2);

  pivot = quick_select(Ap, (n+4)/5, (n+4)/5/2);
  //for(i = j = 0; i < n; i++){
  //  if(A[i] <= pivot){
  //    int z = A[j];
  //    A[j] = A[i];
  //    A[i] = z;
  //    j++;
  //  }
  //}

  //if(j == k+1) return pivot;
  //else if(j < k+1) return quick_select(A+j, n-j, k-j);
  //else return quick_select(A, j-1, k);

  for(i = l = 0, r = n; i < r; i++){
    if(A[i] < pivot){
      int z = A[l];
      A[l] = A[i];
      A[i] = z;
      l++;
    } else if (A[i] > pivot) {
        r--;
        int z = A[r];
        A[r] = A[i];
        A[i] = z;
        i--;
    } 
  }

  if (l > k) return quick_select(A, l, k);
  else if (r < k+1) return quick_select(A+r, n-r, k-r);
  else return pivot;
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N/100;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
