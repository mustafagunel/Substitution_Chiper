#include <iostream>
#include <string>
#include <vector>

using namespace std;
bool isContain(int* arr, int size, int t);
int findIndex(char c, string alf); //if index not found will return -1 
void decrypt(string text,string alf);
int countLetter(string text, char ch);
int* sortDensities(float* enDensity);
int match(char c, int* list);

int main()
{
    string text = "I first heard about the bitcoin concept a few years ago, but sometime in January 2013, I received a call from Tim (a fictitious name) saying he started a company in the Bay Area and wanted talk to me about it.I invited him to UC Santa Barbara for a meeting.I've known Tim for a while now but never met him in person before. He was a Stanford graduate and had an impressive resume. He had started a successful company in one of the applications of cryptography and was still running it. There was not a question in my mind that Tim would be very persuasive in his argumentation of the new technology he was working on, whatever it may be. I was excited to meet and talk to him. He arrived after two or three days and told me that he had started a company that would mine bitcoins.He also wanted to make bitcoins more transferable, for example, one could use an Amazon - like e - commerce site to order 'physical things' with bitcoins which is 'virtual money.' Bear in my mind, this is 2013, and only a few thousand people knew about it, as opposed to now.Today a 100 million people know about it and are considering investing in them.";
    string alf = "abcdefghijklmnopqrstuvwxyz"; 
    string encryptedText;
    int* alfE = (int*)malloc(sizeof(int)*26);  // random letters which match w/a-z
    int* p = alfE;
    int t;
    int index;
    srand(time(NULL));
    
    for (int i = 0;i < 26;i++) {    // random alfabe eþleþmesi.
        do {
            t = rand() % 26 + 0;
        } while (isContain(alfE, sizeof(int)*26, t)); 
        *p++ = t;
    }

    for (int i = 0; i < text.length();i++) {    // düzgün metnin random oluþturulan alfabe ile eþleþtirilerek þifrelenmesi.
        char t = tolower(text[i]);
        index = findIndex(t,alf);
        if(index >= 0)
            encryptedText += alf[*(alfE+index)];
        else
            encryptedText += t;
    }

    p = alfE;
    for (int i = 0;i < 26;i++) {
        cout << alf[i] << " : " << (char)(*(p + i)+97) << " : " << *(p+i) << endl; // P |K | Kindex
    }
    cout << "\n****************** Encrypted Text *******************\n" << encryptedText << endl << "*********************************\n";
    decrypt(encryptedText,alf);
   

}
bool isContain(int* arr, int size, int t) {
    int* p = arr;
    while (*p >= 0) {
        if (*p == t)
            return true;
        p++;
    }
    return false;
}

int findIndex(char c,string alf) {  // find index of char in alphabet
    int index=-1;

    for (int i = 0; i < alf.length();i++) {
        if (c == alf[i])
            index = i;
    }

    return index;
}

int countLetter(string text,char ch) {
    int count=0;
    for (int i = 0; i < text.length();i++) {
        text[i] == ch ? count++ : count;
    }
    return count;
}
void decrypt(string encryptedText,string alf) {
    int counts[26]; // a-z 0-25 | count
    char density[26] = {'e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'}; // Decreasing order density ENG ALPH. 
    float enDensity[26]; // a-z 0-25 encrypted text letter densities
    float sortedIndex[26];
    string decryptedText;

    for (int i = 0; i < 26;i++) 
        counts[i] = countLetter(encryptedText, alf[i]);
    for (int i = 0; i < 26;i++) {
        enDensity[i] = ((float)counts[i] / (float)encryptedText.length()) * 100;   // calculate the density of letter in encrypted text        
    }
        
    for (int i = 0; i < 26;i++) {
        printf("\nLetter %c (index %d)density is %f", alf[i], i , enDensity[i]);
    }
    
    int* list = sortDensities(enDensity);
    
    cout << "\nDecreasing order density a-z;\t";
    for (int i = 0; i < 26;i++) {
        cout<< (char)(list[i]+97) <<", ";
    }
    
    for (int i = 0;i < encryptedText.length();i++) {    // Þifrelenmiþ metnin okunmasý
        if (match(encryptedText[i], list) >= 0) //eðer karakter sýklýðý öðrenilmiþ harf listesinde var ise index'ini alarak
            decryptedText += density[match(encryptedText[i], list)];  // sýralanmýþ ingiliz alf.'de sýk kullanýlan dizisindeki index'i ile 
        //karsilastirilarak ayni kullaným yoðunluðuna sahip harfin bulunmasý.
        else
            decryptedText += encryptedText[i];
    }



    cout << "\n\n************* DECRYPTED TEXT ******************** \n" << decryptedText << endl;

}

int match(char c,int* list) {
    int res = -1;
    for (int i = 0;i < 26;i++) {
        if (c == (char)(list[i] + 97)) {
            res = i;
            break;
        }
        else
            res = -1;
    }
    return res;
}


int check(int d, int* list) {

    for (int i = 0; i < 26; i++) {
        if (d == *(list+i))
            return 1;
    }
    return -1;
}

int* sortDensities(float* enDensity) {
    float* p = enDensity;
    float* temp = enDensity;
    int index = -1;
    int* list = (int*)malloc(sizeof(int)*26);

    
    for (int j = 0; j < 26;j++) {
        for (int i = 0; i < 26; i++) {
            if (*p <= *(temp + i) && (check(i,list)== -1)) {
                p = (temp + i);
                index = i;
            }
        }
        list[j] = index;
        *p = -1;
        p = enDensity;
    }
    
    return list;
}