/* 
    PROBLEM STATEMENT
    Given a string, find its rank among all its permutations sorted lexicographically. 
    For example, rank of “abc” is 1, rank of “acb” is 2, and rank of “cba” is 6.
    [The String does not contain any duplicate characters.]

    I/P: s="acb"
    O/P: 2
    Explanation:
    1 abc
    2 acb
    3 bac
    4 bca
    5 cab
    6 cba
*/
#include<iostream>
#include<string>
using namespace std;
/** 
 * Function for Calculating factorial
**/
int factorial(int n){
    int p = 1;
    if(n==0 || n==1)
        return 1;
    while(n>=1){
        p = n*p;
        n--;
    }
    return p;
}
// Cumulative Frequency Array to store the frequency of how many charcaters, which are present in the string,
// are smaller than the character.
int *calculateCumulativeFreq(int count[]){
    static int cumulFreq[256] = {0};
    int temp = 0;
    if (count[0] == 1)
        temp = 1;
    for (int i = 1; i < 256; i++){
        if (count[i] == 1){
            cumulFreq[i] = temp;
            temp++;
        }
    }
    return cumulFreq;
}
/** 
 * Function to return Lexographic Rank for strings which contain no Repeating character
**/
int getLexicographicRank(string s){
    // Count array to store which characters are present in the String
    int count[256] = {0};
    for(int i=0;i<s.length();i++)
        count[s[i]]+=1;
    /*
    for(int i=0;i<256;i++)
        cout<<cumulFreq[i]<<" ";
    */
    int *cumulFreq = calculateCumulativeFreq(count);
    int n = s.length();
    int smaller,fact,sum = 0;
    for(int i=0;i<n-1;i++){
        // When s[i] is not put
        smaller = cumulFreq[s[i]];  //Number of elememts smaller than s[i]
        fact = factorial(n-(i+1));  //Factorial of number of spaces left in the string.
        sum = smaller*fact + sum;

        // When s[i] is put at it's position, i.e. is cannot be used further
        count[s[i]] = 0;
        cumulFreq = calculateCumulativeFreq(count);
        /* 
        cout<<"After Deleting "<<s[i];
        for(int i=0;i<256;i++)
            cout<<cumulFreq[i]<<" ";
        */
        continue;
    }
    return sum+1;
}
int main(){
    string str;
    cout<<"Enter String: ";
    getline(cin,str);
    int rank = getLexicographicRank(str);
    cout<<"Lexicographic Rank of String "<<str<<" : "<<rank<<endl;
    return 0;
}


