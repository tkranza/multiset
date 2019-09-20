#include <stdio.h>
#include <stdlib.h>
#define MAXLENGTH 1000

typedef int elementtype;

typedef struct {
int last;
elementtype elements[MAXLENGTH];
int kratnost[MAXLENGTH];
} MultiSet;

void SeMakeNull(MultiSet *A){
A->last = -1;
}

int SeMember(elementtype x, MultiSet A){
int i;
for(i = 0; i <= A.last; i++){
    if(A.elements[i] == x) return 1;
}
return 0;
}

void SeInsert(elementtype x, MultiSet *A){
int i;
if(SeMember(x, *A)){
for(i = 0; i <= A->last; i++){
    if(A->elements[i] == x){
        (A->kratnost[i])++;
        return;
    }
}
} else {
(A->last)++;
A->elements[A->last] = x;
A->kratnost[A->last] = 1;
}
}

void SeDelete(elementtype x, MultiSet *A){
if(!(SeMember(x, *A))) return;
int i;
for(i = 0; i <= A->last; i++){
    if(A->elements[i] == x){
        (A->kratnost[i])--;
        if(A->kratnost[i] == 0){
            int j;
            for(j = i; j < A->last; j++){
                A->elements[j] = A->elements[j+1];
                A->kratnost[j] = A->kratnost[j+1];
            }
            (A->last)--;
        }
    }
}
}

elementtype SeMin(MultiSet A){
if(A.last == -1) {
    printf("Skup je prazan");
    exit(1);
} else {
int i, j;
elementtype min;
min = A.elements[0];
for(i = 0; i <= A.last; i++){
    if(A.elements[i] < min) min = A.elements[i];
}
return min;
}
}

elementtype SeMax(MultiSet A){
if(A.last == -1) {
    printf("Skup je prazan");
    exit(2);
} else {
int i, j;
elementtype max;
max = A.elements[0];
for(i = 0; i <= A.last; i++){
    if(A.elements[i] > max) max = A.elements[i];
}
return max;
}
}

int SeSubset(MultiSet A, MultiSet B){
int i, j;
if(A.last == -1) return 1;
for(i = 0; i <= A.last; i++){
    if(!(SeMember(A.elements[i], B))) return 0;
    for(j = 0; j <= B.last; j++){
        if(A.elements[i] == B.elements[j]) break;
    }
    if(A.kratnost[i] > B.kratnost[j]) return 0;
}
return 1;
}

void SeUnion(MultiSet A, MultiSet B, MultiSet *C){
int i, j, b=0;
C->last = A.last;
for(i = 0; i <= A.last; i++){
    C->elements[i] = A.elements[i];
    C->kratnost[i] = A.kratnost[i];
}
for(i = 0; i <= B.last; i++){
    if(SeMember(B.elements[i], *C)){
        for(j = 0; j <= C->last; j++){
            if(B.elements[i] == C->elements[j]){ C->kratnost[j] += B.kratnost[i];
            break;
            }
            }
    } else {
        b++;
    C->elements[C->last + b] = B.elements[i];
    C->kratnost[C->last + b] = B.kratnost[i];
    }
}
C->last += b;
}

void SeIntersection(MultiSet A, MultiSet B, MultiSet *C){
int i, j, b = 0;
for(i = 0; i <= A.last; i++){
    if(SeMember(A.elements[i], B)){
        C->elements[b] = A.elements[i];
        for(j = 0; j <= B.last; j++){
            if(A.elements[i] == B.elements[j]){
                C->kratnost[b] = (A.kratnost[i] < B.kratnost[j] ? A.kratnost[i] : B.kratnost[j]);
                b++;
                break;
            }
            }
    }
}
C->last = b-1;
}

void SeDifference(MultiSet A, MultiSet B, MultiSet *C){
int i, j, b = 0;
for(i = 0; i <= A.last; i++){
if(!(SeMember(A.elements[i], B))){
    C->elements[b] = A.elements[i];
    C->kratnost[b] = A.kratnost[i];
    b++;
} else {
for(j=0; j<=B.last; j++){
    if(A.elements[i] == B.elements[j] && A.kratnost[i] > B.kratnost[j]){
    C->elements[b] = A.elements[i];
    C->kratnost[b] = A.kratnost[i] - B.kratnost[j];
    b++;
    }
}
}
}
C->last = (b > 0 ? b-1 : -1);
}

void ispis(MultiSet A){
int i;
printf("Multiskup :\n");
for(i = 0; i <= A.last; i++){
    printf(" %d %d\n", A.elements[i], A.kratnost[i]);
}
}

int prost(int i){
if(i < 2) return 0;
if(i == 2) return 1;
int j;
for(j=2; j<i; j++){
    if(i % j == 0) return 0;
}
return 1;
}

void prostimultiskup(int a, MultiSet *A){
int i=2;
        while(a > 1){
        if(prost(i)){
        while(a % i == 0){
            SeInsert(i, A);
            a /= i;
        }
        }
        i++;
        }
}

int calc(MultiSet A){
int i, rez = 1;
for(i = 0; i <= A.last; i++){
    while(A.kratnost[i]) {
    rez *= A.elements[i];
    A.kratnost[i]--;
    }
}
return rez;
}

int main(void){

MultiSet A, B, C, D, E;
int a, b;

SeMakeNull(&A);
SeMakeNull(&B);
SeMakeNull(&C);
SeMakeNull(&D);
SeMakeNull(&E);

printf("Ucitaj prvi prirodni broj : \n");
scanf(" %d", &a);
printf("Ucitaj drugi prirodni broj : \n");
scanf(" %d", &b);

prostimultiskup(a, &A);
prostimultiskup(b, &B);

SeIntersection(A, B, &C);
SeUnion(A, B, &D);
SeDifference(D, C, &E);

printf("Najveci zajednicki djelitelj je %d\n", calc(C));

printf("Najmanji zajednicki visekratnik je %d\n", calc(E));

return 0;
}



