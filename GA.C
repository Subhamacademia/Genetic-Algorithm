// This program uses Genetic Algorithm to find the maximum value of y = f(x) = sin(x) / x
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Size_Of_Chromosome 6
struct Genotype{ 					// defines the structure of Chromosome
	short constituent[Size_Of_Chromosome];
	double fitness_Value;
};
void population_Evaluation(struct Genotype *current_Population, int size_Of_Population);
double x(struct Genotype current_Population) ;
double y(double x);
void crossover(struct Genotype *current_Population, struct Genotype *next_Population, float probability_Of_Crossover, int size_Of_Population) ;
void mutation(struct Genotype *current_Population, float probability_Of_Mutation, int size_Of_Population) ;
int main(){
	int number_Of_Generations, size_Of_Population, i, j;
	float probability_Of_Crossover, probability_Of_Mutation;
	printf("Enter the number of Generations : ");
	scanf("%d", &number_Of_Generations);
	printf("Enter the Size of Population : ");
	scanf("%d", &size_Of_Population);
	printf("Enter the Probability of Crossover : ");
	scanf("%f", &probability_Of_Crossover);
	printf("Enter the Probability of Mutation : ");
	scanf("%f", &probability_Of_Mutation);
  
  printf("Generation		f(x)\n");
  
	struct Genotype current_Population[size_Of_Population], next_Population[size_Of_Population] ;
	population_Evaluation(current_Population, size_Of_Population); // This function will create population
	
	for(i = 0 ; i < number_Of_Generations ; i++ ){ 
		for( j = 0 ; j < size_Of_Population ; j++){ // Creates new Population by taking two Chromosomes & selecting the best among them
			int random_Number_1 , random_Number_2 ;
			Line1 :
			random_Number_1 = rand() % size_Of_Population ;
			random_Number_2 = rand() % size_Of_Population ;
			// A corner case
			if(random_Number_1 == random_Number_2){
				goto Line1  ;
			}
			if(current_Population[random_Number_1].fitness_Value >  current_Population[random_Number_2].fitness_Value){
				next_Population[j] = current_Population[random_Number_1] ;
			}
			else
			{
				next_Population[j] = current_Population[random_Number_2] ;
			}
		}
		// Implementing Elitism
		double max = current_Population[0].fitness_Value ;
		struct Genotype temp =  current_Population[0] ;
		for(j = 1 ; j < size_Of_Population ; j++){
			if(current_Population[j].fitness_Value > max){
				max = current_Population[j].fitness_Value ;
				temp = current_Population[j] ;
			}
		}		
		crossover(current_Population, next_Population, probability_Of_Crossover, size_Of_Population) ;
		mutation(current_Population, probability_Of_Mutation, size_Of_Population) ;
		double max1 = current_Population[0].fitness_Value ;
		struct Genotype temp1 =  current_Population[0] ;
		for(j = 1 ; j < size_Of_Population ; j++){
			if(current_Population[j].fitness_Value > max){
				max1 = current_Population[j].fitness_Value ;
				temp1 = current_Population[j] ;
			}	
		} 
    printf("%8d		", i+1) ;
		if(max > max1 ){
      printf("%8.9lf\n",max);
			double min = current_Population[0].fitness_Value;
			int q;
			for(j = 1 ; j < size_Of_Population ; j++){
					if(current_Population[j].fitness_Value < min){
			      min = current_Population[j].fitness_Value ;
				    q = j;				
					}		
			}
			current_Population[q] = temp ;
		}
    else
			printf("%lf\n",max1);
		
	}
	return 0;
  }
void population_Evaluation(struct Genotype *current_Population, int size_Of_Population){
	int i, j ;
	for(i = 0 ; i < size_Of_Population ; i++){
		for(j = 0 ; j < Size_Of_Chromosome ; j++){
			current_Population[i].constituent[j] = abs(rand()  % 2 ) ; // Assignment of 0 or 1			
		}
		current_Population[i].fitness_Value = y ( x ( current_Population[i] ) ) ; // Calculates the Fitness Value		
	}
}
double x(struct Genotype current_Population){
	int V = 0 , i ;
	for(i = 0 ; i < Size_Of_Chromosome ; i++){
		V = V * 2 + current_Population.constituent[i];	
	}
	return  V;
}

double y(double x){	
	return (sin(x) / x);
}
void crossover(struct Genotype *current_Population, struct Genotype *next_Population, float probability_Of_Crossover,int size_Of_Population){
	int new_Probability = probability_Of_Crossover * 100 ;
	int i = 0, j ;
	int random_Number_1 , random_Number_2, random_Number_3 = rand() % 100 ;
	int crossover_Point ;
	while(i < size_Of_Population){	
			Line2 :
					random_Number_1 = rand() % size_Of_Population ;
					random_Number_2 = rand() % size_Of_Population ;
					// A corner case
					if(random_Number_1 == random_Number_2){
						goto Line2  ;
					}
			if (random_Number_3 <= new_Probability){  // Crossover will happen							
					crossover_Point = rand() % Size_Of_Chromosome ;
					for(j = 0 ; j < crossover_Point ; j ++){
						next_Population[random_Number_2].constituent[j] = next_Population[random_Number_1].constituent[j];
					}
					for(j = crossover_Point ; j < Size_Of_Chromosome ; j++){
						next_Population[random_Number_1].constituent[j] = next_Population[random_Number_2].constituent[j];
					}
			}
			current_Population[i] = next_Population[random_Number_1];
			current_Population[i].fitness_Value = y ( x (current_Population[i]) ) ;
			i++;	
			current_Population[i] = next_Population[random_Number_2];
			current_Population[i].fitness_Value = y ( x (current_Population[i]) ) ;
			i++;		
		}
}
void mutation(struct Genotype *current_Population, float probability_Of_Mutation, int size_Of_Population){
	int i, j, new_Probability = 100 * probability_Of_Mutation, random_Number ;
	for(i = 0 ; i < size_Of_Population ; i++){
		for(j = 0 ; j < Size_Of_Chromosome ; j++){
			random_Number = rand() % 100 ;
			if(random_Number <= new_Probability){
				if(current_Population[i].constituent[j] == 0){	
					current_Population[i].constituent[j] = 1 ;
				}
				else
				{
					current_Population[i].constituent[j] = 0 ;
				}
			}
		}
		current_Population[i].fitness_Value = y( x( current_Population[i])) ;
	}
}
