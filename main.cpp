#include <iostream>
#include <vector>
#include <regex>

int numTotGrams;
int numProds;
int numStrings;
using namespace std;

void cyk(const vector<string>& gram, string strPr){
    int N = strPr.length();
    string matriz[N][N];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matriz[i][j] = "0";
        }
    }

    for(int i = 0; i < N; i++ ){
        for (const auto& prods : gram) {
            regex regexletter(string(1, strPr[i]));
            if (regex_search(prods, regexletter)) {
                matriz[i][i] = prods[0];
                continue;
            }
        }
    }

    for (int j = 1; j < N; j++){
        for (int i=0; i<(N-j); i++){
            for(int k=i; k<=((i+j)-1); k++) {
                string prodToSearch = matriz[k][i] + matriz[j+i][k+1];
                for (const auto& prods : gram) {
                    regex regexForProd("\\b" + prodToSearch + "\\b");
                    if (regex_search(prods, regexForProd)){
                        matriz[j+i][i]= prods[0];
                        break;
                    }
                }
            }
        }
    }

    if(matriz[N-1][0]=="S"){cout << "yes" << endl;} else {cout << "no" << endl;}

}

int main() {
    scanf("%d", &numTotGrams);
    for(int i = 0; i<numTotGrams; i++){
        scanf("%d", &numProds);
        scanf("%d", &numStrings);
        vector<string> lines;

        for(int j = 0; j<numProds+1; j++){
            string line;
            getline(cin, line);
            lines.push_back(line);
        }

        for(int z=0; z<numStrings; z++){
            string tryStr;
            getline(cin, tryStr);
            cyk(lines, tryStr);
        }
    }
}