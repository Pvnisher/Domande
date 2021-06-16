#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main()
{
    string nomefile;
    string nomeout;
    string aus;
    char aus2;
    cout<<"Inserire il nome del file \n";
    cin >> nomefile;
    nomeout=nomefile;
    int risposta=0;

    nomeout.append(".html");

    fstream fileinput;
    fstream fileoutput;
    fileinput.open(nomefile, ios::in);
    fileoutput.open(nomeout, ios::out);

    fileoutput << "<html><head><script src='https://www.w3schools.com/lib/w3.js'></script><style>.container {height:10%; max-height:15%; display: inline-block;}.domanda{font-weight: bold;}</style></head><body><button id='bottone' style='position:fixed; margin-left: 80%' onclick=\"w3.toggleShow('.risposta')\">Mostra/nascondi riposte</button>";

    while (!fileinput.eof()){
        fileinput>>aus2;
        if (aus2 == '@'){
            if(risposta==1)
                 fileoutput << "</div>";
            risposta=0;
            fileoutput << "</div><div class='domanda'>";

            getline(fileinput, aus, '\n');
            fileoutput << aus;
        }

        if (aus2 == '!'){
            if(risposta==1)
                fileoutput << "</div>";
            risposta=1;
            fileoutput << "</div><div class='container'><div class='risposta'>";

            getline(fileinput, aus, '\n');
            fileoutput << aus;
        }
        if (aus2 != '@' && aus2 != '!'){
            fileoutput << aus;
            getline(fileinput, aus, '\n');
            fileoutput << aus;
        }

    }

    fileoutput << "</body></html>";
    fileinput.close();
    fileoutput.close();

    return 0;
}
