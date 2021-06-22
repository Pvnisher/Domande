#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void write_headers(const string& output_file, const string& = "headers.html");

int main(int argc, char **argv) {
    string file_domande;
    string file_output;
    string header;
    string aus;
    bool flags[]{false, false, false};
    char aus2;
    if (argc > 1) {
        int i;
        for (i = 0; i < argc; i++) {
            string s1(argv[i]);
            if (s1[0] == '-' && s1.length() > 1) {
                if ((s1[1] == 'h' || s1 == "--help")){
                    cout << argv[0] << " is a tool to auto generates html documents for study\n";
                    cout << "Options : \n";
                    cout << "\t-h\t--help\tShow this help\n";
                    cout << "\t-f\t--file\tFollowed by the path set the path to the txt file to convert\n";
                    cout << "\t-o\t--output\tFollowed by the path set the path to output file (specify .html in the name)\n";
                    cout << "\t-t\t--template\tFollowed by the path set the path to the template files containing headers to be printed before the contents\n";
                    cout << "\n You can also use the interactive mode running " << argv[0] << "whitout arguments\n";
                    cout << "\n Example usage:" << argv[0] <<  "-h headers.html -f file.txt -o out.html\n";
                    return 0;
                }
                if(i+1 < argc){
                    string s2(argv[i+1]);
                    if ((s1[1] == 'f' || s1 == "--file") && s2.length() > 0) {
                        flags[0] = true;
                        file_domande = s2;

                    }
                    if ((s1[1] == 't' || s1 == "--template") && s2.length() > 0) {
                        flags[1] = true;
                        header = s2;

                    }
                    if ((s1[1] == 'o' || s1 == "--output") && s2.length() > 0) {
                        flags[2] = true;
                        file_output = s2;
                        cout << file_output << " " << argv[i] << '\n';
                    }
                }
            }
        }
    }
    if(file_domande.empty())
    {
        cout << "Inserire il nome del file \n";
        cin >> file_domande;
    }
    if (file_output.empty())
    {
        file_output = file_domande;
        file_output.append(".html");
    }

    cout << "File Domande: " << file_domande << '\n';
    cout << "Header File: " << ((header.empty()) ? "Default Headers" : header) << '\n';
    cout << "Output File: " << file_output << '\n';

    fstream stream_input;
    fstream stream_output;

    stream_input.open(file_domande, ios::in);

    write_headers(file_output, header);
    stream_output.open(file_output, std::ios_base::app);

    int id = 1;
    int risposta = 0;
    int domanda = 0;
    int sdrogo = 0;
    stream_output << "<div id='main'>";
    while (!stream_input.eof())
    {
        stream_input >> aus2;

        if (aus2 == '@')
        {
            sdrogo = 1;
            if (risposta == 1){
                stream_output << "</div>";
                risposta = 0;
                if(sdrogo)
                    stream_output << "</div>";
            }
            domanda = 1;
            stream_output << "<div id='" << id++ << "' class='sdrogo'><div class='domanda'>";
            getline(stream_input, aus, '\n');
            stream_output << aus << "<br>\n";
        }
        if (aus2 == '!')
        {
            if(domanda == 1){
                stream_output << "</div>";
                domanda = 0;
            }
            risposta = 1;
            stream_output << "<div class='risposta'>";

            getline(stream_input, aus, '\n');
            stream_output << aus << "<br>\n";
        }
        if (aus2 != '@' && aus2 != '!')
        {
            stream_output << aus2;
            getline(stream_input, aus, '\n');
            stream_output << aus << "<br>\n";
        }
    }

    stream_output << "</div></div></div></div></div></body></html>";
    stream_input.close();
    stream_output.close();
    cout << "GENERAZIONE COMPLETATA CON SUCCESSO\n";

    return 0;
}

void write_headers(const string& output_file, const string& headers_file)
{
    fstream file;
    fstream input;
    file.open(output_file, std::ios_base::out);
    if (file.is_open()){
        input.open(headers_file, ios::in);
        if (input.is_open()) {
            string str;
            while (input >> str)
                file << str << " ";
            input.close();
        }
        else
        {
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
        file.close();
    }
}
