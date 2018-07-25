#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void transmission(int **matrix, int size, int aaa, int bbb);
void printTable(int **matrix, int size);
double mean(int sum, int times, int size);
double standartdev(int sum, int times, int size, int *counts);

int main(int argc,char *argv[]){
	FILE *file;
	file=fopen("output.txt", "a");
	argc=2;
	int size=atoi(argv[1]);										/* size is bountry of matrix */
	int times=atoi(argv[2]);									/* times is iteration round */
	time_t t;
	int end=0;	int aaa=0;	int bbb=0; 	int counter=0; int sum=0; int i,j,k;
	int **matrix;	int *counts;
	counts=(int*)calloc(times,sizeof(int));						/* counts array save the count numbers for every iteration round */
		/*	call to  matrix from memory	*/
	matrix=(int**)calloc(size,sizeof(int));							
	for(i=-1; i<size; i++){							
		matrix[i]=(int*)calloc(size,sizeof(int));			
	}
		/*	call to  matrix from memory	*/
	srand(time(&t));
	/*	process for all loops	*/
	for(k=0; k<times; k++){
		end=0; counter=0;
		/*	process for one loop	*/
		while(end==0){
			aaa = rand()%size;	bbb = rand()%size;				/* aaa and bbb are random values */
			if(matrix[aaa][bbb]!=1 || matrix[aaa][bbb]!=2){			/* If the location has been founded at matrix for the first time, it can go in */
				if (matrix[aaa][bbb]==0){			
					matrix[aaa][bbb]=1;	
					counter++;									/* increase the counter after every changing open cells */
				}
				transmission(matrix, size, aaa, bbb);			
				for (i=0; i<size; i++){						/* if water reach the last line, end will be equal to 1 */
					if(matrix[size-1][i]==2){
						end = 1;
					}
				}
			}
		}
		/*	process for one loop	*/
		sum+=counter;
		counts[k]=counter;
		/*printf("counter%d: %d \n",k,counts[k]);	*/
		if(k!=times-1){
			for(i=0; i<size; i++){					/* chance to 0 every cells at matrix after finished one iteration */
				for(j=0; j<size; j++){
					matrix[i][j]=0;
				}
			}	
		}						
	}
	/*	process for all loops	*/
	printTable(matrix,size);
	fprintf(file,"last iteration finished after %d steps.\n", counter);	  	/* print this on file */
	fprintf(file,"mean(): %f\n",mean(sum, times, size));			/* print mean on file */
	fprintf(file,"standartddev(): %f\n",standartdev(sum, times, size, counts));			/* print standart deviation on file */
	/*free(counts);						*/				/* free to memory */
	/*for(i=0; i<size; i++)	free( matrix[i] );*/
	/*free(matrix);*/
	fclose(file);					/* close file */
	return 0;	
}

double mean(int sum, int times, int size){			/* calculate to mean */
	float mean=0.0; 			
	mean=(float)sum/(times*size*size);
	return mean;
}

double standartdev(int sum, int times, int size, int *counts){				/* calculate to standart deviation */
	int i;	float std;	float mean=1.0;	float deviation=1.0;	float total=1.0;
	mean=(float)sum/(times*size*size);
	for(i=0; i<times; i++){
		total+=(counts[i]-mean)*(counts[i]-mean);
	}
    std=(total/(times*size*size-1));
	
	for(i=0;i<1000;i++){ /* Here i used "babylonian method" */
		deviation=0.5*(deviation+(std/deviation));
	}
	return deviation;
}

void transmission(int **matrix, int size, int aaa, int bbb){
	if(aaa==0){			/* if the location in the first line, full with water */
		matrix[aaa][bbb]=2;			
		if(matrix[aaa+1][bbb]==1){
			matrix[aaa+1][bbb]=2;
			transmission(matrix, size, aaa+1, bbb);	
		}	
	}
	else if(aaa!=0 && aaa!=size-1){				/* if the location in the middle(not first not last), */
		if(matrix[aaa-1][bbb]==2 || matrix[aaa+1][bbb]==2 || matrix[aaa][bbb-1]==2 || matrix[aaa][bbb+1]==2){	/* check around of this location */	
			matrix[aaa][bbb]=2;								/* if around has water, full with water this location */
			switch(matrix[aaa-1][bbb]){						
				case 1:		matrix[aaa-1][bbb]=2;	transmission(matrix, size, aaa-1, bbb);	break;
			}
			switch(matrix[aaa+1][bbb]){
				case 1:		matrix[aaa+1][bbb]=2;	transmission(matrix, size, aaa+1, bbb);	break;
			}
			switch(matrix[aaa][bbb-1]){
				case 1:		matrix[aaa][bbb-1]=2;	transmission(matrix, size, aaa, bbb-1);	break;
			}
			switch(matrix[aaa][bbb+1]){
				case 1:		matrix[aaa][bbb+1]=2;	transmission(matrix, size, aaa, bbb+1);	break;
			}
		}
	}
	else if(aaa==size-1){				/* if the location in last line */
		if(matrix[aaa-1][bbb]==2 || matrix[aaa][bbb-1]==2 || matrix[aaa][bbb+1]==2){		/* check the up line */
			matrix[aaa][bbb]=2;					/* if up line has water, full with water this location */
			switch(matrix[aaa-1][bbb]){
				case 1:		matrix[aaa-1][bbb]=2;	transmission(matrix, size, aaa-1, bbb);	break;
			}
			switch(matrix[aaa][bbb-1]){
				case 1:		matrix[aaa][bbb-1]=2;	transmission(matrix, size, aaa, bbb-1);	break;
			}
			switch(matrix[aaa][bbb+1]){
				case 1:		matrix[aaa][bbb+1]=2;	transmission(matrix, size, aaa, bbb+1);	break;
			}
		}	
	}
}


void printTable(int **matrix, int size){
	int j,k;
	FILE *file;
	file=fopen("output.txt", "w+");
	
	for(j=0;j<size; j++){	
		for(k=0; k<size; k++){			
			fprintf(file,"%2d",matrix[j][k]);
		}
		fprintf(file,"\n");
	}
	fclose(file);	/* close file */
}