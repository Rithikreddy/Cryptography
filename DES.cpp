//actually i have stored the keys and reversed the order just to make it simple
//That's why i didn't use ipc
// I took s-box values from geeks for geeks as i didnt find it in slides

#include<bits/stdc++.h>
#define rnd 16
using namespace std;

int bin_to_int(string a){
    int i=0,m=0;
    for(i=a.size()-1;i>=0;i--){
        m+= (a[i]-'0')*pow(2,a.size()-1-i);
    }
    return m;
}
//hexadecimal to binary and binary to hexadecimal are used to make efficient while working on examples

string hex2bin(string s) 
{ 
    // hexadecimal to binary conversion 
    unordered_map<char, string> mp; 
    mp['0'] = "0000"; 
    mp['1'] = "0001"; 
    mp['2'] = "0010"; 
    mp['3'] = "0011"; 
    mp['4'] = "0100"; 
    mp['5'] = "0101"; 
    mp['6'] = "0110"; 
    mp['7'] = "0111"; 
    mp['8'] = "1000"; 
    mp['9'] = "1001"; 
    mp['A'] = "1010"; 
    mp['B'] = "1011"; 
    mp['C'] = "1100"; 
    mp['D'] = "1101"; 
    mp['E'] = "1110"; 
    mp['F'] = "1111"; 
    string bin = ""; 
    for (int i = 0; i < s.size(); i++) { 
        bin += mp[s[i]]; 
    } 
    return bin; 
}

string bin_to_hex(string a){
    unordered_map<string, string> mp;
    mp["0000"] = "0"; 
    mp["0001"] = "1"; 
    mp["0010"] = "2"; 
    mp["0011"] = "3"; 
    mp["0100"] = "4"; 
    mp["0101"] = "5"; 
    mp["0110"] = "6"; 
    mp["0111"] = "7"; 
    mp["1000"] = "8"; 
    mp["1001"] = "9"; 
    mp["1010"] = "A"; 
    mp["1011"] = "B"; 
    mp["1100"] = "C"; 
    mp["1101"] = "D"; 
    mp["1110"] = "E"; 
    mp["1111"] = "F";
    string hex = ""; 
    for (int i = 0; i < a.length(); i += 4) { 
        string ch = ""; 
        ch += a[i]; 
        ch += a[i + 1]; 
        ch += a[i + 2]; 
        ch += a[i + 3]; 
        hex += mp[ch]; 
    } 
    return hex;
}

string int_to_bin(int a){
    string x="";
    while(a){
        x+= char((a&1)+48);
        a>>=1;
    }
    int m = x.size();       //making all string sizes as 4
    for(int i=0;i<4-m;i++){
        x+='0';
    }
    reverse(x.begin(),x.end());
    return x;
}

string PC1_KEY(string key){
    int i=0;
    int v[7][8] =  { 57, 49, 41, 33, 25, 17, 9, 
                     1, 58, 50, 42, 34, 26, 18, 
                     10, 2, 59, 51, 43, 35, 27, 
                     19, 11, 3, 60, 52, 44, 36, 
                     63, 55, 47, 39, 31, 23, 15, 
                     7, 62, 54, 46, 38, 30, 22, 
                     14, 6, 61, 53, 45, 37, 29, 
                     21, 13, 5, 28, 20, 12, 4 };
    string x="";
    for(int i=0;i<7;i++){
        for(int j=0;j<8;j++){
            x+=key[v[i][j]-1];       //-1 because as it starts from 1
        }
    }
    return x;
}

string rotate(string a,int k){
    string x="";
    char ch;
    for(int i=0;i<k;i++){
        ch=a[0];
        x=a.substr(1);
        x+=ch;
        a=x;
    }
    return x;
}

string PC2_KEY(string a){
    int v[6][8] = { 14, 17, 11, 24, 1, 5,
                    3, 28, 15, 6, 21, 10,
                    23, 19, 12, 4, 26, 8,
                    16, 7, 27, 20, 13, 2,
                    41, 52, 31, 37, 47, 55,
                    30, 40, 51, 45, 33, 48,
                    44, 49, 39, 56, 34, 53,
                    46, 42, 50, 36, 29, 32 };
    string x="";
    for(int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            x+=a[v[i][j]-1];        //-1 is required as it starts from 0
        }
    }
    return x;
}

string key_iteration(string &a,int n){
    int k;
    if(n == 1 || n == 2 || n == 9 || n == 16){
        k=1;
    }
    else
        k=2;
    string lh = a.substr(0,28);
    string rh = a.substr(28);
    lh = rotate(lh,k);
    lh += rotate(rh,k);
    a.clear();
    a=lh;               //new key of size 56bits
    string x =PC2_KEY(a);
    //now size of x is 48bits but sizeof a is 56bits and it remains same
    return x;
}

string XOR(string a,string b){
    string x="";
    for(int i=0;i<a.size();i++){
        x+=char((a[i] != b[i])+48);
    }
    return x;
}

string expansion(string a){
    int v[48] = { 32, 1, 2, 3, 4, 5, 4, 5, 
                      6, 7, 8, 9, 8, 9, 10, 11, 
                      12, 13, 12, 13, 14, 15, 16, 17, 
                      16, 17, 18, 19, 20, 21, 20, 21, 
                      22, 23, 24, 25, 24, 25, 26, 27, 
                      28, 29, 28, 29, 30, 31, 32, 1 };
    string x = "";
    for(int i=0;i<48;i++){
        x+=a[v[i]-1];
    }
    return x;
}

string s_box(string x){
    int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }, 
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }, 
                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }, 
                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }, 
                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }, 
                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }, 
                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }, 
                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
    string op = "";
    for (int i = 0; i < 8; i++){
        int row = 2 * int(x[i * 6] - '0') + int(x[i * 6 + 5] - '0'); 
        int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0');
        col+= 2 * int(x[i * 6 + 3] - '0') + int(x[i * 6 + 4] - '0'); 
        int val = s[i][row][col];
        op += char(val / 8 + '0'); 
        val = val % 8; 
        op += char(val / 4 + '0'); 
        val = val % 4; 
        op += char(val / 2 + '0'); 
        val = val % 2; 
        op += char(val + '0'); 
    }
    return op;
    //size is 4bits for everystring
}

string permutation(string x){
    //Here x is of size32 bits
    int per[32] = { 16, 7, 20, 21, 
                    29, 12, 28, 17, 
                    1, 15, 23, 26, 
                    5, 18, 31, 10, 
                    2, 8, 24, 14, 
                    32, 27, 3, 9, 
                    19, 13, 30, 6, 
                    22, 11, 4, 25 };
    string l="";
    for(int i=0;i<32;i++){
        l+=x[per[i]-1];     //-1 is required as it starts from 1
    }
    return l;
}

string func(string a,string key){
    //4 steps
    //now the key is 48bits
    //But a is of size 32 bits we require expansion here which is first step
    string x = expansion(a);
    //now x is 48bits and key is 48bits
    //step-2 XOR
    string p = XOR(x,key);
    //step-3
    //s-box
    string l=s_box(p);
    //4th step
    return permutation(l);  //of size 32bits
}

string round(string a,string key){
    string li,lh = a.substr(0,32);
    string rh = li = a.substr(32,32);   //as li = ri-1
    string p = func(rh,key);        //here key is 48bit
    string ri = XOR(p,lh);
    string x=li;
    x+=ri;
    return x;
}

void swapping(string &x){
    string s = x.substr(0,32);
    x=x.substr(32,32);
    x+=s;
}

string initial_permutation(string in){
    int v[8][8] =     { 58, 50, 42, 34, 26, 18, 10, 2,
                        60, 52, 44, 36, 28, 20, 12, 4,
                        62, 54, 46, 38, 30, 22, 14, 6,
                        64, 56, 48, 40, 32, 24, 16, 8,
                        57, 49, 41, 33, 25, 17, 9, 1,
                        59, 51, 43, 35, 27, 19, 11, 3,
                        61, 53, 45, 37, 29, 21, 13, 5,
                        63, 55, 47, 39, 31, 23, 15, 7 };
    string x="";
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            x+=in[v[i][j]-1];   //-1 because as it starts from 1
        }
    }
    //cout<<"The string after permutation is "<<bin_to_hex(x)<<endl;
    return x;
}

string final_permutation(string in){
    int v[64] =        { 40, 8, 48, 16, 56, 24, 64, 32, 
                           39, 7, 47, 15, 55, 23, 63, 31, 
                           38, 6, 46, 14, 54, 22, 62, 30, 
                           37, 5, 45, 13, 53, 21, 61, 29, 
                           36, 4, 44, 12, 52, 20, 60, 28, 
                           35, 3, 43, 11, 51, 19, 59, 27, 
                           34, 2, 42, 10, 50, 18, 58, 26, 
                           33, 1, 41, 9, 49, 17, 57, 25 };
    string x="";
    for(int i=0;i<64;i++){
        x+=in[v[i]-1];   //-1 because as it starts from 1
    }
    //cout<<"The string after permutation is "<<x<<endl;
    return x;
}

string encrypt(string in,string key,vector<string>&keys){
    key = PC1_KEY(key);
    string x = initial_permutation(in);
    for(int i=1;i<=16;i++){
        string p = key_iteration(key,i);       //Round 1-16
        //but key changes after every iteration as we have passed the address
        // p is 48bits but key is 56bits after every iteration
        keys.push_back(p);
        cout<<"Key after every iteration is        "<<bin_to_hex(p)<<endl;
        x = round(x,p);
        cout<<"After each round the cipher text is "<<bin_to_hex(x)<<endl;
    }
    swapping(x);
    return final_permutation(x);
}

string decrypt(string in,vector<string>keys){
    //In feisel structures only key schedule has to be changed everything else remains same
    reverse(keys.begin(),keys.end());
    string x = initial_permutation(in);
    for(int i=1;i<=16;i++){
        x = round(x,keys[i-1]);
        cout<<"After each round the cipher text is "<<bin_to_hex(x)<<endl;
    }
    swapping(x);
    return final_permutation(x);
}

int main(){
    cout<<"Enter the key\n";
    string key,in;
    key = hex2bin("AABB09182736CCDD");
    in = hex2bin("123456ABCD132536");
    //cin>>key;
    cout<<"Enter the input text\n";
    vector<string>keys;
    //cin>>in;
    string cipher = encrypt(in,key,keys);
    cout<<"Cipher text is "<<bin_to_hex(cipher)<<endl;
    cout<<"Now decryption of cipher text is "<<endl;
    cout<<bin_to_hex(decrypt(cipher,keys))<<endl;
}
