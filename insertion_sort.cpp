#include<iostream>
using namespace std;
void insertion_sort(int arr[],int n){
	int i,j;
	for(i=1;i<n;i++){
		int key=arr[i];
		j=i-1;
		while(key<arr[j] && j>=0){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
} 

int main(){
	int a[]={5,3,2,1,4};
	insertion_sort(a,5);
	int i;
	for(i=0;i<5;i++)
		cout<<a[i]<<" ";
}
