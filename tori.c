
//  tori.c
//
//  Created by Chris Becker on 4/20/18.
//
/*
 this program reads information from a file, computes the volumes for the file and sorts the data entries by volume
 */
#include <stdio.h>
#include <math.h>

struct torus{
    double minorR; double majorR; double vol;
};


void selection_sort(struct torus _array_tori[], int n);
int process_file(FILE *_pFile, struct torus _tori[]);
void getVol(struct torus _tori[], int n);
void save_file(FILE *_pFile, struct torus _tori[] , int n);



int main(void ){
    //declare variables ill need
    struct torus tori[1000];
    
    //open file
    FILE *pointyFile = NULL;
    int amt = process_file(pointyFile, tori);
    //compute volume
    getVol(tori, amt);
    
    printf("------ unsorted -----\n");
    int i;
    for(i = 0; i < amt; i++){
        printf("%.4lf    %.4lf    %.4lf \n", tori[i].minorR, tori[i].majorR, tori[i].vol);
    }
    //sort
    selection_sort(tori, amt);
    
    //verify sorted list
    printf("--------sorted--------\n");

    for(i = 0; i < amt; i++){
        printf("%.4lf    %.4lf    %.4lf \n", tori[i].minorR, tori[i].majorR, tori[i].vol);
    }
    
    save_file(pointyFile, tori, amt);

    
    return 0;
}



int process_file(FILE *_pFile, struct torus _tori[]){
    //open file
    _pFile = fopen("tori.txt","r");
    if(_pFile == NULL){
        printf("Error reading file /n");
        return 1;
    }
    
    //read contents into array tori
    int i = 0;
    while(fscanf(_pFile,"%lf %lf", &_tori[i].minorR, &_tori[i].majorR) != EOF){
        i++;
    }
    //set amt = to the amount of numbers the array has
    return i;
}



void selection_sort(struct torus array_tori[], int n){
    
    int i, j;
    struct torus tempTorus;
    
    
    
    for(i = 0; i < n-1; i++){
        for(j = i+1; j < n; j++){
            //compare the every volume to the first volume; if its less than the first volume swap those data members
            if(array_tori[j].vol < array_tori[i].vol){
        
                tempTorus = array_tori[i];
                array_tori[i] =  array_tori[j];
                array_tori[j] = tempTorus;
                
            }
        }
    }
    
}


void getVol(struct torus _tori[], int n){
    //compute volume for every item using M_PI for the value of pi
    int i;
    for(i = 0; i < n; i++){
        _tori[i].vol = (2*(M_PI*M_PI)*(_tori[i].majorR*(_tori[i].minorR*_tori[i].minorR)));
    }
}

void save_file(FILE *_pFile, struct torus _tori[], int n){
 
    _pFile = fopen("sorted.txt", "w");
    if(_pFile == NULL){
        printf("file could not be opened");
        
    }
    
    int i;
    fprintf(_pFile, "%s \t %s \t %s \t %s \n","#","minor_rad", "major_rad", "volume");

    for(i = 0; i < n; i++){
        
    fprintf(_pFile, "%d \t %lf \t %lf \t %lf \n",i+1,_tori[i].minorR, _tori[i].majorR, _tori[i].vol);
    
    }
    
    
    fclose(_pFile);
    printf("sorted.txt written \n");
}

