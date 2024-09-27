#include <stdio.h>
#include <limits.h>
#define MAX_SIZE 100
#include <string>
#include <iostream>
using namespace std;

string str = "";
int count2=0;

void print_optimal(int s[MAX_SIZE][MAX_SIZE], int i, int j) {
	if (i == j) {
        str += "A";
        char temp[2];
        sprintf(temp, "%d", i);
        str += temp;
    } 
	else {
        str += "(";
        print_optimal(s, i, s[i][j]);
        str += "*";
        print_optimal(s, s[i][j]+1, j);
        str += ")";
    }
} 

void new_str(){
	int i;
	int erase_index[10];
	int erase_count=0; 
	for(i=0;i<str.length();i++){
		if(str[i]=='(' && str[i+6]==')'){
			count2++;
			str[i]='F';
			str[i+1]=char(count2+48);
			erase_index[erase_count]=i+2;
			erase_count++;
		}
	}
	
	for(i=0;i<erase_count;i++){
		if(i==0){
			str.erase(str.begin()+erase_index[i],str.begin()+erase_index[i]+5);
		}
		else{
			str.erase(str.begin()+erase_index[i]-5*i,str.begin()+erase_index[i]-5*i+5);
		}
	}
	
}

void convertExpression(int n,FILE *fp) {
	int l;
	for(l=0;l<str.length();l++){
		fprintf(fp,"%c",str[l]);
	}
	fprintf(fp,"\n");
	int count1=0;
	count2=0;
	while(count1<n-2){
		int i;
		for(i=0;i<str.length();i++){
			if(str[i]=='(' && str[i+6]==')'){
				count1++;
				if(count1!=n-2){
					fprintf(fp,"F%d=",count1);
				}
				int j;
				for(j=i+1;j<=i+5;j++){
					fprintf(fp,"%c",str[j]);
				}
				fprintf(fp,"\n");
			}
		}
		new_str();
	}
}



int matrixChainMultiplication(int p[], int n) {
    int m[MAX_SIZE][MAX_SIZE],s[MAX_SIZE][MAX_SIZE];
    int i, j, k, L, q;
 	for(i=1;i<n;i++){
 		m[i][i]=0;	
	}
	
	for(L=2;L<n;L++){
		for(i=1;i<n-L+1;i++){
			j=i+L-1;
			m[i][j]=INT_MAX;
			for(k=i;k<=j-1;k++){
				q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(q<m[i][j]){
					m[i][j]=q;
					s[i][j]=k;
				}
			}
		}
	}
	
	print_optimal(s,1,n-1);
	return m[1][n-1];
}

int main() {
    int i;
    for(i=0;i<4;i++){
    	FILE *input;
		FILE *output;
    	if(i==0){
			input = fopen("input1.txt", "r+");
			output = fopen("output1.txt","w+");
		}
		else if(i==1){
			input = fopen("input2.txt", "r+");
			output = fopen("output2.txt","w+");
		}
		else if(i==2){
			input = fopen("input3.txt", "r+");
			output = fopen("output3.txt","w+");
		}
		else if(i==3){
			input = fopen("wrong_input.txt", "r+");
			output = fopen("wrong_output.txt","w+");
		}
		int n,j;
		fscanf(input,"%d",&n);
		n++;
		int arr[n],index=0;
		while(fscanf(input,"%d", &arr[index])!=EOF){
			index++;
		}


    	if(index!=n){
    		fprintf(output,"There is an error in the input, please correct it\n");
		}
		else{
			int minOperations = matrixChainMultiplication(arr, n);
    		fprintf(output,"Minimum number of multiplications is %d\n",minOperations);
    		
    		convertExpression(n,output);
		}
    	str="";
	}
    return 0;
}
