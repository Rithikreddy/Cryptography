#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<bits/stdc++.h>
#include<iostream>
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

int mod(int a){
	if(a<0){
		return (5 - abs(a)%5);
	}
    return a%5;

}

string decryptUtil(string str, vector<vector<char> > kt){
   int i;
   int a[4];

   string cipher="";
   for(int i=0;i<str.length();i=i+2){

        vector<int> x = search(kt,str[i],str[i+1],a);


        if(x[0] == x[2]){

        cipher.push_back(kt[x[0]][mod(x[1]-1)]);
        cipher.push_back(kt[x[0]][mod(x[3]-1)]);   

        } else if(x[1] == x[3]){

        cipher.push_back(kt[mod(x[0]-1)][x[1]]);
        cipher.push_back(kt[mod(x[2]-1)][x[1]]); 

        } else {

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
  
string decryptMsg(string str, string key) 
{ 
    vector<vector<char> > k;
    char kt[5][5];
   
    key = removeSpaces(key);
    key = toLowerCase(key);

    str = removeSpaces(str);
    str = toLowerCase(str);


    k = generateKeyTable(key);

    cout<<"Printing the Key Table: \n";
    printKeyTable(k);

    string ciph = decryptUtil(str,k);

    return ciph;
} 



int main(int argc, char const *argv[]) 
{ 
    // int sfd, nsfd, valread; 
    // struct sockaddr_in address; 
    // int opt = 1; 
    // int addrlen = sizeof(address); 
    // char buffer[1024] = {0}; 
    // char *status = "Message Decrypted Successfully at Server!"; 
       

    // if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    // { 
    //     perror("Socket Failed"); 
    //     exit(EXIT_FAILURE); 
    // } 
       
    // if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
    //                                               &opt, sizeof(opt))) 
    // { 
    //     perror("Setsockopt Error"); 
    //     exit(EXIT_FAILURE); 
    // } 
    // address.sin_family = AF_INET; 
    // address.sin_addr.s_addr = INADDR_ANY; 
    // address.sin_port = htons( PORT ); 
       
 
    // if (bind(sfd, (struct sockaddr *)&address,  
    //                              sizeof(address))<0) 
    // { 
    //     perror("Bind Failed"); 
    //     exit(EXIT_FAILURE); 
    // } 
    // if (listen(sfd, 3) < 0) 
    // { 
    //     perror("Listen Error"); 
    //     exit(EXIT_FAILURE); 
    // } 
    // if ((nsfd = accept(sfd, (struct sockaddr *)&address,  
    //                    (socklen_t*)&addrlen))<0) 
    // { 
    //     perror("Accept Error"); 
    //     exit(EXIT_FAILURE); 
    // } 
    // valread = read( nsfd , buffer, 1024); 
    // std::string ciph(buffer); 
    // string ci,key;

    // int ctr = 0; 
    // while(ciph[ctr]!= '|') ctr++;

    // ci = ciph.substr(0,ctr);
    // key = ciph.substr(ctr+1,ciph.length()-1);
    

    // cout<<"Cipher Text From Client : "<<ci<<endl;

    // cout<<"Key from Client : "<<key<<endl;
	

    // string decstr = dec(ci,key);

    // cout<<"Decrypted Message : "<<decstr<<endl;
    // send(nsfd , status , strlen(status) , 0 );  
    // return 0; 


    //////


    int sfd, nsfd, size; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    char buffer[1024] = {0}; 
       

    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("Socket Failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("Setsockopt Error"); 
        exit(EXIT_FAILURE); 
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons( PORT ); 
       
 
    if (bind(sfd, (struct sockaddr *)&address, sizeof(address))<0) { 
        perror("Bind Failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(sfd, 3) < 0) { 
        perror("Listen Error"); 
        exit(EXIT_FAILURE); 
    } 
    if ((nsfd = accept(sfd, (struct sockaddr *)&address,  (socklen_t*)&addrlen))<0) { 
        perror("Accept Error"); 
        exit(EXIT_FAILURE); 
    } 
    size = read(nsfd, buffer, 1024); 
    std::string recv(buffer);

    string ci,key;

    int ctr = 0; 
    while(recv[ctr]!= '|') ctr++;

    ci = recv.substr(0,ctr);
    key = recv.substr(ctr+1,recv.length()-1);
    
    cout<<"Message Received from Client : "<<recv.substr(0,recv.length()-1)<<endl;
    cout<<"Key from Client : "<<key<<endl;

    string decryptStr = decryptMsg(ci, key);

    cout<<"Decrypted Message : "<<decryptStr;

    return 0; 
} 
