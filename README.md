# Domande

Simple application to automate the generation of html files starting from file.txt of questions - answers for training exams.

## Usage

In a console use `domande.exe -h` to show the help for the program.

```text
Simple application to automate the generation of html files starting from file.txt of questions - answers for training exams.

Options :
        -h      --help  Show this help
        -f      --file  Followed by the path set the path to the txt file to convert
        -o      --output        Followed by the path set the path to output file (specify .html in the name)
        -t      --template      Followed by the path set the path to the template files containing headers to be printed before the contents

 You can also use the interactive mode running .\a.exe whitout arguments

 Example usage: .\a.exe -t headers.html -f file.txt -o out.html`
```

## Input File

Below a sample input file.

```text
@ #1 Question
! #1 Answer
@ #2 Question
! #2 Answer
```

### Symbols

- '@' is used to indicate the start of a question
- '!' to indicate the start of a response

Question - Answer pairs must be sequential.
