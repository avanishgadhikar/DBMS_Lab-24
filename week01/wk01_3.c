#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INPUTS 17017
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

int main(){
    FILE* fptr;
    //opening the file-
    fptr = fopen("week01.csv", "r");
    char line[2000];
    fgets(line, 2000, fptr);
    p product[INPUTS];
    int i = 0;
    while(fgets(line, 2000, fptr)){//for(int i = 0; i < INPUTS; i++){//
        //fgets(line, 2000, fptr);
        int j = 0;

        //id input
        
        for(j = 0; j < 10; j++){
            if(line[j] == ','){
                product[i].id[j] = '\0';
                //printf("%d\n", product[i].id[j-1]);
                break;
            }
            product[i].id[j] = line[j];
        }j++;

        //date inputs
        for(int k = 0; k < 10; k++){
            char date[2] = {'0', '0'};
            char m[3];
            char y[4];
            char d1, d2;
            d1 = line[j++];
            d2 = line[j++];
            //printf("%c %c\n", d1, d2);
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
        //j++;
        //product[i].type[0] = line[j];
        i++;
    }
    fclose(fptr);


    //checking if the input has been taken correctly-
    fptr = fopen("input.txt", "w");
    for (int j = 0; j < i; j++){
        fprintf(fptr, "%s,", product[j].id);
        for (int k = 0; k < 10; k++){
            fprintf(fptr, "%d-%c%c%c-%d,", product[j].date[k].day, product[j].date[k].mon[0], product[j].date[k].mon[1], product[j].date[k].mon[2], product[j].date[k].year);
        }
        fprintf(fptr, "%c\n", product[j].type);
    }
    fclose(fptr);

    //storing the sorted dates separately-
    int date_store[i][10];
    for(int a = 0; a < i; a++){
        int dates[10];
        for(int k = 0; k < 10; k++){
            dates[k] = date_to_no(product[a].date[k]);
        }
        quickSort(dates, 0, 10);

        //checking the type-
        if(product[a].type == 'N'){
            
        }else if(product[a].type == 'S'){
            array_reverse(dates, 0, 9);
        }else if(product[a].type == 'E'){
            array_reverse(dates, 0 ,9);
            array_reverse(dates, 0, 4);
        }else if(product[a].type == 'W'){
            array_reverse(dates, 0 ,9);
            array_reverse(dates, 5, 9);
        }
        for(int k = 0; k < 10; k++){
            //storing the dates-
            date_store[a][k] = dates[k];            
        }
    }
    fclose(fptr);
    
    //printing the sorted outputs in a file-
    fptr = fopen("output.txt", "w");
    for(int a = 0; a < i; a++){
        fprintf(fptr, "%s,", product[a].id);
        for(int k = 0; k < 10; k++){
            int t; 
            t = date_store[a][k];
            d temp;
            temp = no_to_date(t);
            fprintf(fptr, "%d-%c%c%c-%d,", temp.day, temp.mon[0], temp.mon[1], temp.mon[2], temp.year);
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
    fclose(fptr);

    while(1){
        printf("Enter 1 to search for dates before and after task OR 0 to quit...\n");
        int c; scanf("%d", &c);
        if(c == 1){
            char check_id[10];
            int cc = 0;
            scanf("%s", check_id);
            for(int a = 0; a < i; a++){
                if(!strcmp(check_id, product[a].id)){
                     if(product[a].type == 'N'){
                        printf( "\t  North\n");
                    }else if(product[a].type == 'S'){
                        printf("\t  South\n");
                    }else if(product[a].type == 'W'){
                        printf("\t  West\n");
                    }else if(product[a].type == 'E'){
                        printf("\t  East\n");
                }
                    printf("  Before   \t   After   \n");
                    for(int k = 0; k < 10; k++){
                        int t; 
                        t = date_store[a][k];
                        d temp;
                        temp = no_to_date(t);
                        printf("%d-%c%c%c-%d\t%d-%c%c%c-%d\n", product[a].date[k].day, product[a].date[k].mon[0], product[a].date[k].mon[1], product[a].date[k].mon[2], product[a].date[k].year, temp.day, temp.mon[0], temp.mon[1], temp.mon[2], temp.year);
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