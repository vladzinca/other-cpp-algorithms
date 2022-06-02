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

    /* dimensiunile matricei */
    int N, M;

    /* matricea */
    char a[NMAX][NMAX];

    int robotCounter = 0, spotCounter = 0;

    void read_input() {
        ifstream fin("curatare.in");
        fin >> N >> M;
        char x;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) {
                fin >> x;

                /* denumesc robotii A, B, C si D,
                    iar spot-urile murdare M, N, P, Q */
                if (x == 'R') {
                    robotCounter++;
                    if (robotCounter == 1)
                        a[i][j] = 'A';
                    else if (robotCounter == 2)
                        a[i][j] = 'B';
                    else if (robotCounter == 3)
                        a[i][j] = 'C';
                    else if (robotCounter == 4)
                        a[i][j] = 'D';
                } else if (x == 'S') {
                    spotCounter++;
                    if (spotCounter == 1)
                        a[i][j] = 'M';
                    else if (spotCounter == 2)
                        a[i][j] = 'N';
                    else if (spotCounter == 3)
                        a[i][j] = 'P';
                    else if (spotCounter == 4)
                        a[i][j] = 'Q';
                } else {
                    a[i][j] = x;
                }
            }
        fin.close();
    }

    /* definitia unui nod pe care il salvam in coada in BFS */
    typedef struct Node {
        int lin;
        int col;
        int dist;
    } Node;

    /* calculeaza distanta de la un spot la toti
        robotii si toate celelalte spoturi */
    void computeMinimumDistance(char sursa, char a[NMAX][NMAX],
                    int N, int M, int distante[]) {
        Node source;
        bool visited[NMAX][NMAX];

        /* marcam celule 'X' ca vizitate */
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (a[i][j] == 'X')
                    visited[i][j] = true;
                else
                    visited[i][j] = false;

                /* gasim celula matricei din care facem BFS */
                if (a[i][j] == sursa) {
                    source.lin = i;
                    source.col = j;
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
            /* verificam daca am gasit un
                robot sau un spot murdar */
            if (a[nod.lin][nod.col] == 'A')
                distante[0] = nod.dist;
            if (a[nod.lin][nod.col] == 'B')
                distante[1] = nod.dist;
            if (a[nod.lin][nod.col] == 'C')
                distante[2] = nod.dist;
            if (a[nod.lin][nod.col] == 'D')
                distante[3] = nod.dist;
            if (a[nod.lin][nod.col] == 'M')
                distante[4] = nod.dist;
            if (a[nod.lin][nod.col] == 'N')
                distante[5] = nod.dist;
            if (a[nod.lin][nod.col] == 'P')
                distante[6] = nod.dist;
            if (a[nod.lin][nod.col] == 'Q')
                distante[7] = nod.dist;

            /* incercam sa adaugam celula de sus */
            if (nod.lin - 1 >= 0 &&
                visited[nod.lin - 1][nod.col] == false) {
                Node aux;
                aux.lin = nod.lin - 1;
                aux.col = nod.col;
                aux.dist = nod.dist + 1;
                q.push(aux);
                visited[nod.lin - 1][nod.col] = true;
            }

            /* incercam sa adaugam celula din dreapta */
            if (nod.col + 1 < M &&
                visited[nod.lin][nod.col + 1] == false) {
                Node aux;
                aux.lin = nod.lin;
                aux.col = nod.col + 1;
                aux.dist = nod.dist + 1;
                q.push(aux);
                visited[nod.lin][nod.col + 1] = true;
            }

            /* incercam sa adaugam celula de jos */
            if (nod.lin + 1 < N &&
                visited[nod.lin + 1][nod.col] == false) {
                Node aux;
                aux.lin = nod.lin + 1;
                aux.col = nod.col;
                aux.dist = nod.dist + 1;
                q.push(aux);
                visited[nod.lin + 1][nod.col] = true;
            }

            /* incercam sa adaugam celula din stanga */
            if (nod.col - 1 >= 0 &&
                visited[nod.lin][nod.col - 1] == false) {
                Node aux;
                aux.lin = nod.lin;
                aux.col = nod.col - 1;
                aux.dist = nod.dist + 1;
                q.push(aux);
                visited[nod.lin][nod.col - 1] = true;
            }
        }
    }

    /* cauta in vectori distanta dintre sursa
        si destinatie, pentru simplitate */
    int distanceBetween(char sursa, char destinatie, int distanteM[],
                        int distanteN[], int distanteP[], int distanteQ[]) {
        if (sursa == 'M') {
            if (destinatie == 'A')
                return distanteM[0];
            if (destinatie == 'B')
                return distanteM[1];
            if (destinatie == 'C')
                return distanteM[2];
            if (destinatie == 'D')
                return distanteM[3];
            if (destinatie == 'N')
                return distanteM[5];
            if (destinatie == 'P')
                return distanteM[6];
            if (destinatie == 'Q')
                return distanteM[7];
        }
        if (sursa == 'N') {
            if (destinatie == 'A')
                return distanteN[0];
            if (destinatie == 'B')
                return distanteN[1];
            if (destinatie == 'C')
                return distanteN[2];
            if (destinatie == 'D')
                return distanteN[3];
            if (destinatie == 'M')
                return distanteN[4];
            if (destinatie == 'P')
                return distanteN[6];
            if (destinatie == 'Q')
                return distanteN[7];
        }
        if (sursa == 'P') {
            if (destinatie == 'A')
                return distanteP[0];
            if (destinatie == 'B')
                return distanteP[1];
            if (destinatie == 'C')
                return distanteP[2];
            if (destinatie == 'D')
                return distanteP[3];
            if (destinatie == 'M')
                return distanteP[4];
            if (destinatie == 'N')
                return distanteP[5];
            if (destinatie == 'Q')
                return distanteP[7];
        }
        if (sursa == 'Q') {
            if (destinatie == 'A')
                return distanteQ[0];
            if (destinatie == 'B')
                return distanteQ[1];
            if (destinatie == 'C')
                return distanteQ[2];
            if (destinatie == 'D')
                return distanteQ[3];
            if (destinatie == 'M')
                return distanteQ[4];
            if (destinatie == 'N')
                return distanteQ[5];
            if (destinatie == 'P')
                return distanteQ[6];
        }
        return 9999;
    }

    /* calculeaza timpul minim necesar acoperirii tututor spoturilor */
    int get_result() {
        int distanteM[8], distanteN[8], distanteP[8], distanteQ[8];
        if (spotCounter == 1) {
            /* daca exista un singur spot murdar,
                calculeaza distantele catre acesta */
            for (int i = 0; i < 8; i++)
                distanteM[i] = 9999;
            computeMinimumDistance('M', a, N, M, distanteM);

            /* calculeaza timpul cel mai mic */
            int minDist = 9999;
            minDist = min(distanteM[0], min(distanteM[1],
                            min(distanteM[2], distanteM[3])));

            /* daca timpul este 9999 sau mai mare (nu exista
                niciun robot care poate ajunge la spot), scrie -1 */
            return (minDist < 9999) ? minDist : -1;
        } else if (spotCounter == 2) {
            /* daca exista doua spoturi murdare */
            for (int i = 0; i < 8; i++)
                distanteM[i] = 9999;
            computeMinimumDistance('M', a, N, M, distanteM);
            for (int i = 0; i < 8; i++)
                distanteN[i] = 9999;
            computeMinimumDistance('N', a, N, M, distanteN);

            /* ia pe rand toate posibilitatile si salveaza
                varianta optima in minDist */
            int distanta = 9999, minDist = 9999;
            /* A -> M -> N */
            distanta = distanteM[0] + distanteM[5];
            if (distanta < minDist)
                minDist = distanta;
             /* A -> N -> M */
            distanta = distanteN[0] + distanteN[4];
            if (distanta < minDist)
                minDist = distanta;
             /* B -> M -> N */
            distanta = distanteM[1] + distanteM[5];
            if (distanta < minDist)
                minDist = distanta;
             /* B -> N -> M */
            distanta = distanteN[1] + distanteN[4];
            if (distanta < minDist)
                minDist = distanta;
             /* C -> M -> N */
            distanta = distanteM[2] + distanteM[5];
            if (distanta < minDist)
                minDist = distanta;
             /* C -> N -> M */
            distanta = distanteN[2] + distanteN[4];
            if (distanta < minDist)
                minDist = distanta;
             /* D -> M -> N */
            distanta = distanteM[3] + distanteM[5];
            if (distanta < minDist)
                minDist = distanta;
             /* D -> N -> M */
            distanta = distanteN[3] + distanteN[4];
            if (distanta < minDist)
                minDist = distanta;

            /* A -> M; B -> N */
            distanta = max(distanteM[0], distanteN[1]);
            if (distanta < minDist)
                minDist = distanta;
            /* A -> M; C -> N */
            distanta = max(distanteM[0], distanteN[2]);
            if (distanta < minDist)
                minDist = distanta;
            /* A -> M; D -> N */
            distanta = max(distanteM[0], distanteN[3]);
            if (distanta < minDist)
                minDist = distanta;

            /* B -> M; A -> N */
            distanta = max(distanteM[1], distanteN[0]);
            if (distanta < minDist)
                minDist = distanta;
            /* B -> M; C -> N */
            distanta = max(distanteM[1], distanteN[2]);
            if (distanta < minDist)
                minDist = distanta;
            /* B -> M; D -> N */
            distanta = max(distanteM[1], distanteN[3]);
            if (distanta < minDist)
                minDist = distanta;

            /* C -> M; A -> N */
            distanta = max(distanteM[2], distanteN[0]);
            if (distanta < minDist)
                minDist = distanta;
            /* C -> M; B -> N */
            distanta = max(distanteM[2], distanteN[1]);
            if (distanta < minDist)
                minDist = distanta;
            /* C -> M; D -> N */
            distanta = max(distanteM[2], distanteN[3]);
            if (distanta < minDist)
                minDist = distanta;

            /* D -> M; A -> N */
            distanta = max(distanteM[3], distanteN[0]);
            if (distanta < minDist)
                minDist = distanta;
            /* D -> M; B -> N */
            distanta = max(distanteM[3], distanteN[1]);
            if (distanta < minDist)
                minDist = distanta;
            /* D -> M; C -> N */
            distanta = max(distanteM[3], distanteN[2]);
            if (distanta < minDist)
                minDist = distanta;

            return (minDist < 9999) ? minDist : -1;
        } else if (spotCounter == 3) {
            /* daca exista trei spoturi murdare */
            for (int i = 0; i < 8; i++)
                distanteM[i] = 9999;
            computeMinimumDistance('M', a, N, M, distanteM);
            for (int i = 0; i < 8; i++)
                distanteN[i] = 9999;
            computeMinimumDistance('N', a, N, M, distanteN);
            for (int i = 0; i < 8; i++)
                distanteP[i] = 9999;
            computeMinimumDistance('P', a, N, M, distanteP);

            int distanta = 9999, minDist = 9999;
            char vect[3] = {'M', 'N', 'P'};
            do {
                /* ia pe rand toate posibilitatile pentru fiecare permutare
                    si salveaza varianta optima in minDist */

                /* A -> M -> N -> P */
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* B -> M -> N -> P */
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* C -> M -> N -> P */
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* D -> M -> N -> P */
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* A -> M -> N; B -> P */
                int maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; C -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; D -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; A -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; C -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; D -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N; A -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N; B -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N; D -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N; A -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N; B -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N; C -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M; B -> N; C -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[1], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M; B -> N; D -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[1], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M; C -> N; D -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[1], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M; C -> N; D -> P */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[1], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;
            } while (next_permutation(vect, vect + 3));

            return (minDist < 9999) ? minDist : -1;

        } else if (spotCounter == 4) {
            /* daca exista patru spoturi murdare */
            for (int i = 0; i < 8; i++)
                distanteM[i] = 9999;
            computeMinimumDistance('M', a, N, M, distanteM);
            for (int i = 0; i < 8; i++)
                distanteN[i] = 9999;
            computeMinimumDistance('N', a, N, M, distanteN);
            for (int i = 0; i < 8; i++)
                distanteP[i] = 9999;
            computeMinimumDistance('P', a, N, M, distanteP);
            for (int i = 0; i < 8; i++)
                distanteQ[i] = 9999;
            computeMinimumDistance('Q', a, N, M, distanteQ);

            int distanta = 9999, minDist = 9999;
            char vect[4] = {'M', 'N', 'P', 'Q'};
            do {
                /* A -> M -> N -> P -> Q */
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* B -> M -> N -> P -> Q */
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* C -> M -> N -> P -> Q */
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* D -> M -> N -> P -> Q */
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta < minDist)
                    minDist = distanta;

                /* A -> M -> N -> P; B -> Q */
                int maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N -> P; C -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N -> P; A -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N -> P; C -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N -> P; A -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N -> P; B -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N -> P; A -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N -> P; B -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N -> P; C -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[1], vect[2],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; B -> P -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; C -> P -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; D -> P -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; C -> P -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; D -> P -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N; D -> P -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[2], vect[3],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; B -> P; C -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; B -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M -> N; C -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; A -> P; C -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; A -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* B -> M -> N; C -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N; A -> P; B -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N; A -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* C -> M -> N; B -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N; A -> P; B -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N; A -> P; C -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* D -> M -> N; B -> P; C -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                distanta += distanceBetween(vect[0], vect[1],
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;

                /* A -> M; B -> N; C -> P; D -> Q */
                maxDist = -1;
                distanta = distanceBetween(vect[0], 'A',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[1], 'B',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[2], 'C',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                distanta = distanceBetween(vect[3], 'D',
                            distanteM, distanteN, distanteP, distanteQ);
                if (distanta > maxDist)
                    maxDist = distanta;
                if (maxDist < minDist)
                    minDist = maxDist;
            } while (next_permutation(vect, vect + 4));

            return (minDist < 9999) ? minDist : -1;
        }

        return -1;
    }

    /* scrie rezultatul */
    void print_output(int result) {
        ofstream fout("curatare.out");
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
