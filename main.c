#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#include<sys/time.h>
#define MAX 500
int t[MAX],cntr=0;
	
//horspool algorithm's shift table:
void shifttable(char p[])
{
 int i,j,m;
 m=strlen(p);
 for(i=0;i<MAX;i++)
  t[i]=m;
 for(j=0;j<m-1;j++)
  t[p[j]]=m-1-j;
}

//horspool algorithm:
int horspool(char src[],char p[],char nWord[])
{
 int i,j,k,m,n,l;
 n=strlen(src);
 m=strlen(p);
 l=strlen(nWord);
 printf("\nLength of text=%d",n);
 printf("\nLength of pattern=%d",m);
 printf("\nLength of new word=%d",l);

 i=m-1;
 while(i<n) //continue till the text is over
 {
  k=0;
  while((k<m)&&(p[m-1-k]==src[i-k])) //if they match, keep moving
   k++;
   //if the word is found:
  if(k==m){ 
  	cntr++;
  	int a,b;
  	
  	
  	//diziyi kaydýrma:
  	
  	//shift right = if the new word is bigger
  	if(l>m){
  		n+=l-m;
  		for(b=0;b<l-m;b++){
  			for (a = n; a >= i+1; a--) {
      			src[a] = src[a - 1];
        	}
    	}
	}
	//shift left = if the new word is smaller
	else{
		n-=m-l;
		for(b=0;b<m-l;b++){
  			for (a = i-b; a <= n; a++) {
      			src[a] = src[a + 1];
        	}
    	}
	}
    //put the new word
  	for(a=0;a<l;i++,a++){
  		src[i-m+1]=nWord[a];
	}
	i++;
  }
  //if the word can not find yet, skip by using shift table
  else
   i+=t[src[i]];
 }
 
 
 return 0;
}


int main()
{
	//the beginning of the clock
    clock_t start_t, end_t, total_t;
    start_t = clock();

 char src[500000],p[100],fileName[50],nWord[100];
 int pos;
 
 printf("Enter the name of the file in which pattern is to be searched:");
 gets(fileName);
    //read the file into a string
 	FILE *myFile = NULL;
    myFile = fopen(fileName , "r");
    
    if (myFile == NULL){
        printf("Could not open file %s",fileName);
        return 1;
    }
    
    int i=0;
    src[i]= fgetc(myFile); 
    while (src[i] != EOF) 
    { 
    
        i++;
        src[i] = fgetc(myFile); 
    } 
    
    printf ("\n%s", src);
  
    fclose(myFile);
    
 printf("\n\n\nEnter the pattern to be searched:");
 gets(p);
 printf("\nEnter the name of the new word you want to put:");
 gets(nWord);
 shifttable(p);
 pos=horspool(src,p,nWord);
 if(cntr>=0)
 	printf("\nThe desired pattern was founded %d times\n",cntr);
 else
  	printf("\nThe pattern was not found in the given text\n");
 
 myFile = fopen(fileName, "w+"); 	
 fputs(src, myFile);
 fclose(myFile);
 
 printf ("\n%s\n", src);
 printf("%d word founded",cntr);
  end_t = clock();
   total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
 printf("Total time taken by CPU: %f\n", total_t  );
   
   
 printf("\nPress any button to end up the program.");
 getch();
 return 0;
}
