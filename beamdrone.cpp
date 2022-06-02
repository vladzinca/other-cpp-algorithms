#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    /* marimea maxima a matricei */
    static constexpr int NMAX = (int)1e3 + 5;

    /* dimensiunile matricei si pozitiile dronei si a sosirii */
    int N, M, xi, xf, yi, yf;

    /* matricea */
    char a[NMAX][NMAX];

    /* citeste din fisier si marcheaza pe matrice sursa si destinatia */
    void read_input() {
        ifstream fin("beamdrone.in");
        fin >> N >> M >> xi >> xf >> yi >> yf;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                fin >> a[i][j];
        a[xi][xf] = 'S';
        a[yi][yf] = 'D';
        fin.close();
    }

    /* definitia unui nod pe care il salvam in coada in BFS */
    typedef struct Node {
        int lin;
        int col;
        char dir;
        int dist;
    } Node;

    /* calculeaza distanta de la drona la sosire */
    int computeMinimumDistance(char a[NMAX][NMAX], int N, int M) {
        Node source;
        bool visited[NMAX][NMAX];
        int distances[NMAX][NMAX];
        int minDist = 9999, partialMin = 9999;

        /* marcam celulele 'W' ca vizitate */
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (a[i][j] == 'W') {
                    visited[i][j] = true;
                    distances[i][j] = -1;
                } else {
                    visited[i][j] = false;
                    distances[i][j] = 9999;
                }

                /* gasim celula matricei din care facem BFS si
                    o marcam ca ANY direction */
                if (a[i][j] == 'S') {
                    source.lin = i;
                    source.col = j;
                    source.dir = 'A';
                }
            }
        }

        /* BFS din sursa pe matrice */
        queue<Node> q;
        q.push(source);
        visited[source.lin][source.col] = true;
        while (!q.empty()) {
            Node nod = q.front();
            q.pop();

            distances[nod.lin][nod.col] = nod.dist;

            if (a[nod.lin][nod.col] == 'D') {
                if (nod.dist < minDist) {
                    minDist = nod.dist;
                    partialMin = nod.dist;
                }
            }

            if (a[nod.lin][nod.col] != 'D' && nod.dist <= partialMin) {
                /* daca directia de data trecuta fusese in sus */
                if (nod.dir == 'N') {
                    /* incercam sa adaugam celula de sus */
                    if (nod.lin - 1 >= 0 &&
                        ((visited[nod.lin - 1][nod.col] == false) ||
                        (nod.dist <= distances[nod.lin - 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin - 1;
                        aux.col = nod.col;
                        aux.dir = 'N';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin - 1][nod.col] != 'D')
                            visited[nod.lin - 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula din dreapta */
                    if (nod.col + 1 < M &&
                        ((visited[nod.lin][nod.col + 1] == false) ||
                        (nod.dist + 1 <= distances[nod.lin][nod.col + 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col + 1;
                        aux.dir = 'E';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col + 1] != 'D')
                            visited[nod.lin][nod.col + 1] = true;
                    }

                    /* incercam sa adaugam celula din stanga */
                    if (nod.col - 1 >= 0 &&
                        ((visited[nod.lin][nod.col - 1] == false) ||
                        (nod.dist + 1 <= distances[nod.lin][nod.col - 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col - 1;
                        aux.dir = 'W';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col - 1] != 'D')
                            visited[nod.lin][nod.col - 1] = true;
                    }

                    /* incercam sa adaugam celula de jos */
                    if (nod.lin + 1 < N &&
                        ((visited[nod.lin + 1][nod.col] == false) ||
                        (nod.dist + 2 <= distances[nod.lin + 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin + 1;
                        aux.col = nod.col;
                        aux.dir = 'S';
                        aux.dist = nod.dist + 2;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin + 1][nod.col] != 'D')
                            visited[nod.lin + 1][nod.col] = true;
                    }
                /* daca directia de data trecuta fusese inspre dreapta */
                } else if (nod.dir == 'E') {
                    /* incercam sa adaugam celula din dreapta */
                    if (nod.col + 1 < M &&
                        ((visited[nod.lin][nod.col + 1] == false) ||
                        (nod.dist <= distances[nod.lin][nod.col + 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col + 1;
                        aux.dir = 'E';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col + 1] != 'D')
                            visited[nod.lin][nod.col + 1] = true;
                    }

                    /* incercam sa adaugam celula de sus */
                    if (nod.lin - 1 >= 0 &&
                        ((visited[nod.lin - 1][nod.col] == false) ||
                        (nod.dist + 1 <= distances[nod.lin - 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin - 1;
                        aux.col = nod.col;
                        aux.dir = 'N';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin - 1][nod.col] != 'D')
                            visited[nod.lin - 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula de jos */
                    if (nod.lin + 1 < N &&
                        ((visited[nod.lin + 1][nod.col] == false) ||
                        (nod.dist + 1 <= distances[nod.lin + 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin + 1;
                        aux.col = nod.col;
                        aux.dir = 'S';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin + 1][nod.col] != 'D')
                            visited[nod.lin + 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula din stanga */
                    if (nod.col - 1 >= 0 &&
                        ((visited[nod.lin][nod.col - 1] == false) ||
                        (nod.dist + 2 <= distances[nod.lin][nod.col - 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col - 1;
                        aux.dir = 'W';
                        aux.dist = nod.dist + 2;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col - 1] != 'D')
                            visited[nod.lin][nod.col - 1] = true;
                    }
                /* daca directia de data trecuta fusese in jos */
                } else if (nod.dir == 'S') {
                    /* incercam sa adaugam celula de jos */
                    if (nod.lin + 1 < N &&
                        ((visited[nod.lin + 1][nod.col] == false) ||
                        (nod.dist <= distances[nod.lin + 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin + 1;
                        aux.col = nod.col;
                        aux.dir = 'S';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin + 1][nod.col] != 'D')
                            visited[nod.lin + 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula din dreapta */
                    if (nod.col + 1 < M &&
                        ((visited[nod.lin][nod.col + 1] == false) ||
                        (nod.dist + 1 <= distances[nod.lin][nod.col + 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col + 1;
                        aux.dir = 'E';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col + 1] != 'D')
                            visited[nod.lin][nod.col + 1] = true;
                    }

                    /* incercam sa adaugam celula din stanga */
                    if (nod.col - 1 >= 0 &&
                        ((visited[nod.lin][nod.col - 1] == false) ||
                        (nod.dist + 1 <= distances[nod.lin][nod.col - 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col - 1;
                        aux.dir = 'W';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col - 1] != 'D')
                            visited[nod.lin][nod.col - 1] = true;
                    }

                    /* incercam sa adaugam celula de sus */
                    if (nod.lin - 1 >= 0 &&
                        ((visited[nod.lin - 1][nod.col] == false) ||
                        (nod.dist + 2 <= distances[nod.lin - 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin - 1;
                        aux.col = nod.col;
                        aux.dir = 'N';
                        aux.dist = nod.dist + 2;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin - 1][nod.col] != 'D')
                            visited[nod.lin - 1][nod.col] = true;
                    }
                /* daca directia de data trecuta fusese inspre stanga */
                } else if (nod.dir == 'W') {
                    /* incercam sa adaugam celula din stanga */
                    if (nod.col - 1 >= 0 &&
                        ((visited[nod.lin][nod.col - 1] == false) ||
                        (nod.dist <= distances[nod.lin][nod.col - 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col - 1;
                        aux.dir = 'W';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col - 1] != 'D')
                            visited[nod.lin][nod.col - 1] = true;
                    }

                    /* incercam sa adaugam celula de sus */
                    if (nod.lin - 1 >= 0 &&
                        ((visited[nod.lin - 1][nod.col] == false) ||
                        (nod.dist + 1 <= distances[nod.lin - 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin - 1;
                        aux.col = nod.col;
                        aux.dir = 'N';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin - 1][nod.col] != 'D')
                            visited[nod.lin - 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula de jos */
                    if (nod.lin + 1 < N &&
                        ((visited[nod.lin + 1][nod.col] == false) ||
                        (nod.dist + 1 <= distances[nod.lin + 1][nod.col]))) {
                        Node aux;
                        aux.lin = nod.lin + 1;
                        aux.col = nod.col;
                        aux.dir = 'S';
                        aux.dist = nod.dist + 1;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin + 1][nod.col] != 'D')
                            visited[nod.lin + 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula din dreapta */
                    if (nod.col + 1 < M &&
                        ((visited[nod.lin][nod.col + 1] == false) ||
                        (nod.dist + 2 <= distances[nod.lin][nod.col + 1]))) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col + 1;
                        aux.dir = 'E';
                        aux.dist = nod.dist + 2;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col + 1] != 'D')
                            visited[nod.lin][nod.col + 1] = true;
                    }
                /* daca e nodul sursa cu directia ANY */
                } else {
                    /* incercam sa adaugam celula de sus */
                    if (nod.lin - 1 >= 0 &&
                        visited[nod.lin - 1][nod.col] == false) {
                        Node aux;
                        aux.lin = nod.lin - 1;
                        aux.col = nod.col;
                        aux.dir = 'N';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin - 1][nod.col] != 'D')
                            visited[nod.lin - 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula din dreapta */
                    if (nod.col + 1 < M &&
                        visited[nod.lin][nod.col + 1] == false) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col + 1;
                        aux.dir = 'E';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col + 1] != 'D')
                            visited[nod.lin][nod.col + 1] = true;
                    }

                    /* incercam sa adaugam celula de jos */
                    if (nod.lin + 1 < N &&
                        visited[nod.lin + 1][nod.col] == false) {
                        Node aux;
                        aux.lin = nod.lin + 1;
                        aux.col = nod.col;
                        aux.dir = 'S';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin + 1][nod.col] != 'D')
                            visited[nod.lin + 1][nod.col] = true;
                    }

                    /* incercam sa adaugam celula din stanga */
                    if (nod.col - 1 >= 0 &&
                        visited[nod.lin][nod.col - 1] == false) {
                        Node aux;
                        aux.lin = nod.lin;
                        aux.col = nod.col - 1;
                        aux.dir = 'W';
                        aux.dist = nod.dist;
                        q.push(aux);
                        distances[aux.lin][aux.col] = aux.dist;
                        if (a[nod.lin][nod.col - 1] != 'D')
                            visited[nod.lin][nod.col - 1] = true;
                    }
                }
            }
        }

        return (minDist < 9999) ? minDist : -1;
    }

    /* calculeaza numarul minim de turn-uri necesare dronei */
    int get_result() {
        return computeMinimumDistance(a, N, M);
    }

    /* scrie rezultatul */
    void print_output(int result) {
        ofstream fout("beamdrone.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto *task = new (nothrow) Task();
    if (!task) {
        cerr << "new failed: WTF are you doing? Throw your PC!\n";
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
