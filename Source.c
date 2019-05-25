#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef unsigned char boolean;
void partitionNumber(int n);
void printPartitionNumber(const int *S, const int *R, const int d);
void partitionSet(int n);
void printPartitionSet(const int *array, const int size_of_array);
int main()
{
	int n = 0;
	printf("Partition number\n");
	printf("Enter number : ");
	scanf_s("%d", &n);
	partitionNumber(n);
	printf("\nPartition set\n");
	printf("Enter number : ");
	scanf_s("%d", &n);
	partitionSet(n);
	system("pause");
	return 0;
}
void printPartitionNumber(const int *S, const int *R, const int d)
{
	for (int i = 0; i <= d; ++i) {
		for (int j = 0; j < R[i]; ++j) {
			printf(" %d ", S[i]);
		}
	}
	putchar('\n');
	return;
}

void partitionNumber(const int n)
{
	int d = 0;
	int l = 0;
	int sum = 0;
	int *S = (int*)calloc(n / 2, sizeof(int));
	int *R = (int*)calloc(n / 2, sizeof(int));
	*S = n;
	*R = 1;
	printPartitionNumber(S, R, d);
	while (*S > 1) {
		sum = 0;
		if (S[d] == 1) {
			sum += R[d];
			--d;
		}
		sum += S[d];
		--R[d];
		l = S[d] - 1;
		if (R[d] > 0) {
			++d;
		}
		S[d] = l;
		R[d] = sum / l;
		l = sum % l;
		if (l != 0) {
			++d;
			S[d] = l;
			R[d] = 1;
		}
		printPartitionNumber(S, R, d);
	}
	free(R); R = NULL;
	free(S); S = NULL;
	return;
}

void partitionSet(int n)
{
	int *block = (int*)calloc(n, sizeof(int));
	boolean *isForward = (boolean*)calloc(n, sizeof(boolean));
	int *next = (int*)calloc(n, sizeof(int));
	int *prev = (int*)calloc(n, sizeof(int));
	for (int i = 0; i < n; ++i) {
		isForward[i] = TRUE;
	}
	printPartitionSet(block, n);
	int j = n - 1;
	int k = 0;
	while (j > 0) {
		k = block[j] ;
		if (isForward[j]) {
			if (next[k] == 0) {
				next[k] = j;
				prev[j] = k;
				next[j] = 0;
			}
			if (next[k] > j) {
				prev[j] = k;
				next[j] = next[k];
				prev[next[j]] = j;
				next[k] = j;
			}
			block[j] = next[k];
		}
		else {
			block[j] = prev[k];
			if (k == j) {
				if (next[k] == 0) {
					next[prev[k]] = 0;
				}
				else {
					next[prev[k]] = next[k];
					prev[next[k]] = prev[k];
				}
			}
		}
		printPartitionSet(block, n);
		j = n - 1;
		while ((j > 0) &&
			(isForward[j] && (block[j] == j)) || (!isForward[j] && (block[j] == 0))) {
			isForward[j] = !isForward[j];
			--j;
		}
	}
	free(prev);
	free(next);
	free(isForward);
	free(block);
	return;
}

void printPartitionSet(const int *block, const int n)
{
	for (int i = 0; i < n; ++i) {
		if (block[i] == i) {
			putchar('(');
			for (int k = 0; k < n; ++k) {
				if (block[k] == i) {
					printf(" %d ", k + 1);
				}
			}
			printf(") ");
		}
	}
	putchar('\n');
	return;
}