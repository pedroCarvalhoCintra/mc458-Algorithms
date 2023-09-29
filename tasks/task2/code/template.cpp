#include <iostream>
#include <vector>


using namespace std;

struct pizza {
    int s, t, r;
};

int z[1002][1002];
pizza aux[1002];

void mergePizzas(vector<pizza> &pizzas, int left, int middle, int right ){

    for ( int i = left; i <= right; i++ ) {
        aux[i] = pizzas[i];
    }

    int i = left;
    int j = middle+1;
    for ( int k = left; k <= right; k++ ) {
        if ( j <= right ) {
            if ( ((aux[i].r) / (0.0+aux[i].t)) <= ((aux[j].r) / (0.0+aux[j].t)) && i <= middle ) {
               pizzas[k] = aux[i];
                i++;
            } else {
                pizzas[k] = aux[j];
                j++;
            }
        } else {
            pizzas[k] = aux[i];
            i++;
        }
    }
}

void mergeSortPizzas(vector<pizza> &pizzas, int left, int right){

    if (left < right) {
        int middle = (left + right)/2;

        mergeSortPizzas(pizzas, left, middle);
        mergeSortPizzas(pizzas, middle+1, right);
        mergePizzas(pizzas, left, middle, right);   
    }
}



int solve(vector<pizza> &pizzas, int N, int T) {
    
    mergeSortPizzas(pizzas, 0, N-1);

    for ( int i = 0; i <= N; i++ ) z[i][0] = 0;
    for ( int i = 0; i <= T; i++ ) z[0][i] = 0;

    int ti = 0;
    int sabor = 0;
    for ( int i = 1; i <= N; i++ ) {
        for ( int j = 1; j <= T; j++ ) {
            z[i][j] = z[i-1][j];
            
            ti = pizzas[i-1].t;
            sabor = pizzas[i-1].s - pizzas[i-1].r*(T-j + ti);
            if ( pizzas[i-1].t <= j &&  sabor + z[i-1][j-ti] > z[i][j] ) {
                z[i][j] = sabor + z[i-1][j-ti];
            }
        }
    }

    return z[N][T];
}


int main() {

    int N, T;
    cin >> N >> T;

    vector<pizza> pizzas(N);
    for(int i = 0; i < N; ++i)
        cin >> pizzas[i].s >> pizzas[i].t >> pizzas[i].r;

    cout << solve(pizzas, N, T) << endl;
    return 0;
}