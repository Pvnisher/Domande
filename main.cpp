#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

void scriviinizio(string nomefile);

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
    fileinput.open(nomefile, ios::in);

    scriviinizio(nomeout);

    fstream fileoutput;
    fileoutput.open(nomeout, std::ios_base::app);

    int id=1;
    while (!fileinput.eof()){
        fileinput>>aus2;
        if (aus2 == '@'){
            if(risposta==1)
                 fileoutput << "</div>";
            risposta=0;
            fileoutput << "</div></div><div id='"<<id<<"' class='sdrogo'><div class='domanda'>";
            id++;
            getline(fileinput, aus, '\n');
            fileoutput << aus << "<br>\n";
        }

        if (aus2 == '!'){
            if(risposta==1)
                fileoutput << "</div>";
            risposta=1;
            fileoutput << "</div><div class='container'><div class='risposta'>";

            getline(fileinput, aus, '\n');
            fileoutput << aus << "<br>\n";
        }
        if (aus2 != '@' && aus2 != '!'){
            fileoutput << aus2;
            getline(fileinput, aus, '\n');
            fileoutput << aus << "<br>\n";
        }

    }

    fileoutput << "</body></html>";
    fileinput.close();
    fileoutput.close();

    return 0;
}

void scriviinizio(string nomefile){
    fstream file;
    file.open(nomefile, ios::out);
    //inizio e script w3school
    file << "<html><head><script src='https://www.w3schools.com/lib/w3.js'></script>";
    //mio script
    file << "<script>var x;var num;\nfunction cambia(t){\nif(t=='a' && x<document.querySelectorAll('.sdrogo').length){\ndocument.getElementById(x).style=\"display:none;\"\n";
    file << "if(rand==true)\nx=Math.floor((Math.random() * num) + 1);\nelse\nx++;\ndocument.getElementById(x).style=\"display:inline-block;\"}\nif(t=='i' && x>1){\ndocument.getElementById(x).style=\"display:none;\"\n";
    file << "if(rand==true)\nx=Math.floor((Math.random() * num) + 1);\nelse\nx--;\ndocument.getElementById(x).style=\"display:inline-block;\"}}\nfunction start(){\n";
    file << "x=1;num=document.querySelectorAll('.sdrogo').length;\ndocument.getElementById(1).style=\"display:inline-block;\";\nw3.toggleShow('.risposta');}\n";
    file << "function toggleRand(){\nif(rand==true){\ndocument.getElementById('rand').value=\"rand disattivo\";\nrand=false;}\n";
    file << "else{\ndocument.getElementById('rand').value=\"rand attivo\";\nrand=true;}}\n</script>\n";
    //css e chiudo head
    file << "<style>.container {height:85%; max-height:85%; display: inline-block; overflow: scroll; width: 100%;}.domanda{font-weight: bold;}.sdrogo{width: 100%; display:none;}</style></head>";
    //bottoni
    file << "<body onload='start()'><button id='bottone' style='position:fixed; margin-left: 80%' onclick=\"w3.toggleShow('.risposta')\">Mostra/nascondi riposte</button>";
    file << "<input type=button id='nascondimostra' style='position:fixed; margin-left: 80%' onclick=\"w3.toggleShow('.risposta')\" value='Mostra/nascondi riposte'>";
    file << "<input type=button id='next' style='position:fixed; margin-left: 80%; margin-top: 10%;' onclick=\"cambia('a')\" value='Prossimo'>";
    file << "<input type=button id='back' style='position:fixed; margin-left: 80%; margin-top: 12%;' onclick=\"cambia('i')\" value='Indietro'>";
    file << "<input type=button id='rand' style='position:fixed; margin-left: 80%; margin-top: 5%;' onclick='toggleRand()'  value='rand disattivo'>";
}


