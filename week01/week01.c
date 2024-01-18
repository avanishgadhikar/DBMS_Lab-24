#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define int long long int
#define INPUTS 17017//this value is not hard coded, but this is the maximum size of the inputs possible. the number of inputs is determined using the fgets and it not returning a NULL value after encountering an EOF character.

//NOTE: Ideal inputs to check task 05:
//P0001 for WEST + bordercase
//P0004 for EAST + bordercase
//P17013 for SOUTH
//P17017 for NORTH
typedef struct d{
    int day;
    char mon[4];
    int year;
}d;

typedef struct p{
    char id[7];
    d date[10];
    char type;
}p;

int date_to_no(d date){
    int dat = 0;
	int m = 0;
	if(date.mon[0] == 'J' && date.mon[1] == 'a' && date.mon[2] == 'n'){
		m = 1;
	}else if (date.mon[0] == 'F' && date.mon[1] == 'e' && date.mon[2] == 'b'){
		m = 2;
	}else if (date.mon[0] == 'M' && date.mon[1] == 'a' && date.mon[2] == 'r'){
		m = 3;
	}
	else if (date.mon[0] == 'A' && date.mon[1] == 'p' && date.mon[2] == 'r'){
		m = 4;
	}
	else if (date.mon[0] == 'M' && date.mon[1] == 'a' && date.mon[2] == 'y'){
		m = 5;
	}
	else if (date.mon[0] == 'J' && date.mon[1] == 'u' && date.mon[2] == 'n'){
		m = 6;
	}
	else if (date.mon[0] == 'J' && date.mon[1] == 'u' && date.mon[2] == 'l'){
		m = 7;
	}
	else if (date.mon[0] == 'A' && date.mon[1] == 'u' && date.mon[2] == 'g'){
		m = 8;
	}
	else if (date.mon[0] == 'S' && date.mon[1] == 'e' && date.mon[2] == 'p'){
		m = 9;
	}
	else if (date.mon[0] == 'O' && date.mon[1] == 'c' && date.mon[2] == 't'){
		m = 10;
	}
	else if (date.mon[0] == 'N' && date.mon[1] == 'o' && date.mon[2] == 'v'){
		m = 11;
	}else if(date.mon[0] == 'D' && date.mon[1] == 'e' && date.mon[2] == 'c'){
		m = 12;
	}
	dat = date.year*10000 + m*100 + date.day;
	return dat;
}

int partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = (low - 1);
  for (int j = low; j <= high; j++) {
    if (arr[j] < pivot) {
      i++;
      int temp;
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int temp;
      temp = arr[i+1];
      arr[i+1] = arr[high];
      arr[high] = temp;
  return (i + 1);
}

void quickSort(int arr[], int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void bubbleSort(int arr[], int n){
	for(int a = 0; a < n; a++){
		for(int b = 0; b < n - a - 1; b++){
			if(arr[b] > arr[b+1]){
				int temp; 
				temp = arr[b];
				arr[b] = arr[b+1];
				arr[b+1] = temp;		
			}
		}
	}
}

d no_to_date(int a){
    d dat;
    dat.day = a%100;
    dat.year = (a - a%10000)/10000;
    if((a%10000 - a%100)/100 == 1){
        dat.mon[0] = 'J'; dat.mon[1] = 'a'; dat.mon[2] = 'n';
    }else if((a%10000 - a%100)/100 == 2){
        dat.mon[0] = 'F'; dat.mon[1] = 'e'; dat.mon[2] = 'b';
    }else if((a%10000 - a%100)/100 == 3){
        dat.mon[0] = 'M'; dat.mon[1] = 'a'; dat.mon[2] = 'r';
    }else if((a%10000 - a%100)/100 == 4){
        dat.mon[0] = 'A'; dat.mon[1] = 'p'; dat.mon[2] = 'r';
    }else if((a%10000 - a%100)/100 == 5){
        dat.mon[0] = 'M'; dat.mon[1] = 'a'; dat.mon[2] = 'y';
    }else if((a%10000 - a%100)/100 == 6){
        dat.mon[0] = 'J'; dat.mon[1] = 'u'; dat.mon[2] = 'n';
    }else if((a%10000 - a%100)/100 == 7){
        dat.mon[0] = 'J'; dat.mon[1] = 'u'; dat.mon[2] = 'l';
    }else if((a%10000 - a%100)/100 == 8){
        dat.mon[0] = 'A'; dat.mon[1] = 'u'; dat.mon[2] = 'g';
    }else if((a%10000 - a%100)/100 == 9){
        dat.mon[0] = 'S'; dat.mon[1] = 'e'; dat.mon[2] = 'p';
    }else if((a%10000 - a%100)/100 == 10){
        dat.mon[0] = 'O'; dat.mon[1] = 'c'; dat.mon[2] = 't';
    }else if((a%10000 - a%100)/100 == 11){
        dat.mon[0] = 'N'; dat.mon[1] = 'o'; dat.mon[2] = 'v';
    }else if((a%10000 - a%100)/100 == 12){
        dat.mon[0] = 'D'; dat.mon[1] = 'e'; dat.mon[2] = 'c';
    }
    return dat;
}

void array_reverse(int arr[], int start, int end){
    int s = start;
    int e = end;
    for(int i = 0; i <= (end - start)/2; i++){
        int temp;
        temp = arr[s];
        arr[s] = arr[e];
        arr[e] = temp;
        s++;
        e--;
    }
}

int check_border(int arr[], int border, int end){
	int res = border;
	for(int a = border + 1; a <= end; a++){
		if(arr[a] == arr[border]){
			res = a;
		}
	}
	return res;
}

int main(){
    FILE* fptr;
    //opening the file-
    fptr = fopen("week01.csv", "r");
    char line[2000];
    fgets(line, 2000, fptr);
    p product[INPUTS];
    
    //i loops over all the products, j loops over the entire string input taken.
    int i = 0;
    while(fgets(line, 2000, fptr)){
        int j = 0;

        //id input-
        //taking input until comma encountered and then adding string terminator.
        for(j = 0; j < 10; j++){
            if(line[j] == ','){
                product[i].id[j] = '\0';
                break;
            }
            product[i].id[j] = line[j];
        }j++;

        //date inputs-
        //for loop of 10 for 10 inputs.
        for(int k = 0; k < 10; k++){
            char date[2] = {'0', '0'};
            char m[3];
            char y[4];
            char d1, d2;
            d1 = line[j++];
            d2 = line[j++];
            //handling the case of single digit and double digit entries differently.
            if(d2 != '-'){
                date[0] = d1;
                date[1] = d2;
                j++;
            }else{
                date[1] = d1;			
            }
            m[0] = line[j++];
            m[1] = line[j++];
            m[2] = line[j++];
            j++;
            y[0] = line[j++];
            y[1] = line[j++];
            y[2] = line[j++];
            y[3] = line[j++];
            j++;
            int yr;
            yr = (y[0] - 48)*1000 + (y[1] - 48)*100 + (y[2] - 48)*10 + (y[3] - 48);
            int da;
            da = (date[0] - 48)*10 + (date[1] - 48);
            product[i].date[k].day = da;
            product[i].date[k].year = yr;
            product[i].date[k].mon[0] = m[0];
            product[i].date[k].mon[1] = m[1];
            product[i].date[k].mon[2] = m[2];
        }
        product[i].type = line[j++];
        i++;
    }
    fclose(fptr);//closing week01.csv


    //checking if the input has been taken correctly-
    //storing the input in a file named input.txt
    fptr = fopen("input.txt", "w");
    for (int j = 0; j < i; j++){
        fprintf(fptr, "%s,", product[j].id);
        for (int k = 0; k < 10; k++){
            fprintf(fptr, "%lld-%c%c%c-%lld,", product[j].date[k].day, product[j].date[k].mon[0], product[j].date[k].mon[1], product[j].date[k].mon[2], product[j].date[k].year);
        }
        if(product[j].type == 'N'){
            fprintf(fptr, "North\n");
        }else if(product[j].type == 'S'){
            fprintf(fptr, "South\n");
        }else if(product[j].type == 'W'){
            fprintf(fptr, "West\n");
        }else if(product[j].type == 'E'){
            fprintf(fptr, "East\n");
        }
    }
    fclose(fptr);//closing input.txt

    //storing the sorted dates separately-
    //storing as an integer array for task 5.
    int date_store[i][10];
    for(int a = 0; a < i; a++){
        int dates[10];
        for(int k = 0; k < 10; k++){
            dates[k] = date_to_no(product[a].date[k]);
        }    
        
        
        //sorting the dates as needed-        
        //can use either of the below 2 sorting methods.
        quickSort(dates, 0, 10);
        //bubbleSort(dates, 10);
		
		//checking the type-
        if(product[a].type == 'N'){
            //already sorted in this case.
        }else if(product[a].type == 'S'){
            array_reverse(dates, 0, 9);
            //arranging in descending order.
        }else if(product[a].type == 'E'){
            array_reverse(dates, 0, 9);
            int cb = check_border(dates, 4, 9);//this gives the same border cases upto which array needs to be reversed.
            array_reverse(dates, 0, cb);
            //arranging in descending first.
            //sorting the first 5 in ascending order.
        }else if(product[a].type == 'W'){
            array_reverse(dates, 0, 9);
            int cb = check_border(dates, 4, 9);//this gives the same border cases from where array need to be reversed.
            array_reverse(dates, cb + 1, 9);
            //arranging in descending order first.
            //sorting the last 5 in ascending order.
        }
        
        for(int k = 0; k < 10; k++){
            //storing the dates-
            date_store[a][k] = dates[k];   
            //storing the dates as an integer of the form YYYYMMDD for further use.         
        }
    }
    
    //printing the sorted outputs in a file-
    fptr = fopen("output.txt", "w");
    for(int a = 0; a < i; a++){
        fprintf(fptr, "%s,", product[a].id);
        for(int k = 0; k < 10; k++){
            int t; 
            t = date_store[a][k];
            d temp;
            temp = no_to_date(t);
            fprintf(fptr, "%lld-%c%c%c-%lld,", temp.day, temp.mon[0], temp.mon[1], temp.mon[2], temp.year);
        }
        if(product[a].type == 'N'){
            fprintf(fptr, "North\n");
        }else if(product[a].type == 'S'){
            fprintf(fptr, "South\n");
        }else if(product[a].type == 'W'){
            fprintf(fptr, "West\n");
        }else if(product[a].type == 'E'){
            fprintf(fptr, "East\n");
        }
        
    }
    fclose(fptr);//closing output.txt


	//taking user input until 'quit' to provide before and after of a product id-
    while(1){
        printf("Enter 1 to search for dates before and after task OR 0 to quit...\n");
        int c; scanf("%lld", &c);
        if(c == 1){
            char check_id[10];
            int cc = 0;//check to see if user provided id found or not.
            scanf("%s", check_id);
            for(int a = 0; a < i; a++){
                if(!strcmp(check_id, product[a].id)){
                     if(product[a].type == 'N'){
                        printf( "Region:\t  North\n");
                    }else if(product[a].type == 'S'){
                        printf("Region:\t  South\n");
                    }else if(product[a].type == 'W'){
                        printf("Region:\t  West\n");
                    }else if(product[a].type == 'E'){
                        printf("Region:\t  East\n");
                }
                    printf("  Before   \t   After   \n");
                    for(int k = 0; k < 10; k++){
                        int t; 
                        t = date_store[a][k];
                        d temp;
                        temp = no_to_date(t);
                        printf("%lld-%c%c%c-%lld\t%lld-%c%c%c-%lld\n", product[a].date[k].day, product[a].date[k].mon[0], product[a].date[k].mon[1], product[a].date[k].mon[2], product[a].date[k].year, temp.day, temp.mon[0], temp.mon[1], temp.mon[2], temp.year);
                    }
                    cc = 1;
                    
                }else{
                    continue;
                }
            }
            if(cc == 0){
                printf("ID not found\n");
            }
        }else{
            break;
        }
    }

    return 0;
}



/*


		//trial block-
        ////////////////////////////////
        for(int m = 0; m < 10; m++){
        	if(a == 0){
        		printf("%d--", dates[m]);printf("\n");
        	}
        }
        ////////////////////////////////
        
        
            
    //trial block
    //////////////////////////////////////
    for(int m = 0; m < 10; m++){
    	for(int q = 0; q < 10; q++){
    		printf("%d--", date_store[m][q]);
    	}printf("\n");
    }
    
    
    //////////////////////////////////////
    
    
            //trial block-
        ////////////////////////////////
        for(int m = 0; m < 10; m++){
        	if(a == 0){
        		printf("%d--", dates[m]);printf("\n");
        	}
        }
        ////////////////////////////////
        
        
        //trial block
        ////////////////////////
        for(int m = 0; m < 10; m++){
        	if(a == 0){
        		printf("%lld--", dates[m]);printf("\n");
        	}
        }
        ////////////////////////

*/        












