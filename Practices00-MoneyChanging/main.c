#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int solve(int m, int cnt){
	if( m>=6 && m % 6 != 3 && m % 6 != 2 ){
		// mod 6을 했을때 2나 3이 되면 다른 조합이 더 최소가 된다. 
		cnt += m/6;
		m = m % 6;
	}
	else if( m >= 4 && m % 4 < 2){
		// 마찬가지로 m mod 4가 2가 되면 4+2= 6이 되어서 n이 최솟값에서 멀어진다. 
		cnt += m/4;
		m = m % 4;
	}
	else {
		return cnt + m;
	}
	solve(m, cnt);
}

int main(int argc, char *argv[]) {
	int M;
	printf("Amount of money? ");
	scanf("%d", &M);
	int n = solve(M,0);
	printf("%d coins",n);
	return 0;
}
