#include "lib.hpp"
#include <iostream>
#include <vector>

using namespace std;

void combineRoutes(vector<int> &path, int left, int middle, int right){

    int aux[path.size()];
    for (int m = left; m <= right; m++){
        aux[m] = path[m];
    }

    int j = left;
    int i = middle + 1;
    for ( int k = left; k <= right; k++ ){
        if ( i <= right ) {
            if ( has_edge(aux[j], aux[i]) && j <= middle ) {
                path[k] = aux[j];
                j++;
            } else {
                path[k] = aux[i];
                i++;
            }
        } else {
            path[k] = aux[j];
            j++;
        }
    }
}

void excursionRoute(vector<int> &path, int left, int right){
    
    if ( left < right ){
        int middle = (left + right)/2;
        
        excursionRoute(path, left, middle);
        excursionRoute(path, middle+1, right);
        combineRoutes(path, left, middle, right);
    }
}

vector<int> createVertexVector(int n){
    
    vector<int> path;
    path.resize(n);
    for ( int i = 0; i < n; i++ ) path[i] = i+1;
    return path;
}

vector<int> solve(int n) {
    
    vector<int> path = createVertexVector(n);
    excursionRoute(path, 0, n-1);
    return path;
}


int main(int argc, char *argv[]) {

    char *filename = NULL;
    if(argc > 1)
        filename = argv[1];

    int n;
    initialize_has_edge(n, filename);

    vector<int> path = solve(n);
    int result = check_path(path, n);
    cout << result << '\n';
    return result;
}