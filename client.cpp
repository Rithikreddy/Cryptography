#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include<bits/stdc++.h> 
#include<iostream>
#include<algorithm>
#define PORT 8080
using namespace std;

string removeSpaces(string str) { 
    string ns="";

    for (int i = 0; i < str.length();i++) 
        if (str[i] != ' ') 
            ns.push_back(str[i]);
                                 
    return ns;
} 

string toLowerCase(string str) {
    int i; 
    for (i = 0; i < str.length(); i++) { 
        if (str[i] > 64 && str[i] < 91) 
            str[i] += 32; 
    }

    return str; 
} 

string makeEven(string s) {
	if(s.length() % 2 != 0){
	   s.push_back('z');
	}
        return s;
}

vector<vector<char>>  generateKeyTable(string key) {
  
   map<char,int> mp;
   vector<vector<char> > ktable(5, vector<char>(5,'0'));
   
   int k;
   for(k=0;k<key.length();k++){
	    if(key[k] != 'j')
           mp[key[k]] = 2;
    }

   mp['j'] = 1;

   int i=0, j=0;

   for(k=0;k<key.length();k++){
      if(mp[key[k]] == 2){
         mp[key[k]] -= 1;
         ktable[i][j] = key[k]; 
         j++;
         if(j == 5){
             i++;
             j=0;
         }

      }
   }

   for(k=0;k<26;k++){
	   if(mp[char(k+97)] == 0){
		ktable[i][j] = (char)(k + 97); 
		j++;
        if(j == 5){
          i++;
	  	j=0;
	  	}
	  }
   }

//    for(int i=0;i<5;i++){
//       vector<char> a;
//       for(int j=0;j<5;j++){
//         a.push_back(kt[i][j]);

//       }
//       ktable.push_back(a);

//     } 

   return ktable;
}

vector<int> search(vector<vector<char> > kt,char a,char b,int x[4]){

    int i, j; 

    vector<int> result;
    if (a == 'j') 
        a = 'i'; 
    else if (b == 'j') 
        b = 'i'; 
    for (i = 0; i < 5; i++) { 
        for (j = 0; j < 5; j++) { 
            if (kt[i][j] == a) { 
                 x[0] = i;
				 x[1] = j;
            } 
            else if (kt[i][j] == b) { 
                x[2] = i;
                x[3] = j;
            } 
        } 
    }
    for(int i=0;i<4;i++){
       result.push_back(x[i]);
    }

    return result;
}

string encryptUtil(string str, vector<vector<char> > kt){
   int i;
   int a[4];

   string cipher="";
   for(int i=0;i<str.length();i=i+2){

		vector<int> x = search(kt,str[i],str[i+1],a);
		if(x[0] == x[2]){
		cipher.push_back(kt[x[0]][(x[1]+1)%5]);
		cipher.push_back(kt[x[0]][(x[3]+1)%5]);   

		}
		else if(x[1] == x[3]){

		cipher.push_back(kt[(x[0]+1)%5][x[1]]);
		cipher.push_back(kt[(x[2]+1)%5][x[1]]); 

		}
		else{

		cipher.push_back(kt[x[0]][x[3]]);
		cipher.push_back(kt[x[2]][x[1]]); 

		}

   }
   return cipher;


}

void printKeyTable(vector<vector<char> > k){
   for(int i=0;i<k.size();i++){
     
		for(int j=0;j<k[i].size();j++){
		cout<<k[i][j]<<" ";

		}
		cout<<endl;

    } 
}
  
string encryptMsg(string str, string key) 
{ 
    vector<vector<char> > k;
   
    key = removeSpaces(key);
    key = toLowerCase(key);

    str = removeSpaces(str);
    str = toLowerCase(str);
    
    str = makeEven(str);

    k = generateKeyTable(key);

    cout<<"Print the Key Table: \n";
    printKeyTable(k);

    string ciph = encryptUtil(str,k);

    return ciph;
} 

int main() 
{ 
  string message, key;

    int sock = 0,valread;
    struct sockaddr_in serv_addr; 
   
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        cout<<"\n Error in Creating Socket \n"; 
        return -1; 
    } 

    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  { 
        cout<<"\nAddress Not Supported \n"; 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
        cout<<"\nConnection Failed \n"; 
        return -1; 
    }

    cout<<"Enter the message : "<<endl;
    getline(cin,message);

    cout<<"Enter the key :"<<endl;
    cin>>key;

    string encryptStr = encryptMsg(message,key);
    cout<<"Encrypted message : "<<encryptStr<<endl;
    encryptStr = encryptStr + "|" + key;

    char *cipher = const_cast<char *>(encryptStr.c_str());

    send(sock , cipher , strlen(cipher) , 0 );
    cout<<"Encrypted Message Sent to Server\n";
    return 0;
}

