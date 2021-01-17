#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080 
#include<bits/stdc++.h>
#include<iostream>
#include "aesHeaders.h"

using namespace std;

unsigned char key[] = "aAbBcCdDeEfFgGhH";


void SubRoundKey(unsigned char * state, unsigned char * roundKey) {
	for (int i = 0; i < 16; i++)
		state[i] ^= roundKey[i];
	
}


void InverseMixColumns(unsigned char * state) {
	unsigned char tmp[16];

	tmp[0] = (unsigned char)mul14[state[0]] ^ mul11[state[1]] ^ mul13[state[2]] ^ mul9[state[3]];
	tmp[1] = (unsigned char)mul9[state[0]] ^ mul14[state[1]] ^ mul11[state[2]] ^ mul13[state[3]];
	tmp[2] = (unsigned char)mul13[state[0]] ^ mul9[state[1]] ^ mul14[state[2]] ^ mul11[state[3]];
	tmp[3] = (unsigned char)mul11[state[0]] ^ mul13[state[1]] ^ mul9[state[2]] ^ mul14[state[3]];

	tmp[4] = (unsigned char)mul14[state[4]] ^ mul11[state[5]] ^ mul13[state[6]] ^ mul9[state[7]];
	tmp[5] = (unsigned char)mul9[state[4]] ^ mul14[state[5]] ^ mul11[state[6]] ^ mul13[state[7]];
	tmp[6] = (unsigned char)mul13[state[4]] ^ mul9[state[5]] ^ mul14[state[6]] ^ mul11[state[7]];
	tmp[7] = (unsigned char)mul11[state[4]] ^ mul13[state[5]] ^ mul9[state[6]] ^ mul14[state[7]];

	tmp[8] = (unsigned char)mul14[state[8]] ^ mul11[state[9]] ^ mul13[state[10]] ^ mul9[state[11]];
	tmp[9] = (unsigned char)mul9[state[8]] ^ mul14[state[9]] ^ mul11[state[10]] ^ mul13[state[11]];
	tmp[10] = (unsigned char)mul13[state[8]] ^ mul9[state[9]] ^ mul14[state[10]] ^ mul11[state[11]];
	tmp[11] = (unsigned char)mul11[state[8]] ^ mul13[state[9]] ^ mul9[state[10]] ^ mul14[state[11]];

	tmp[12] = (unsigned char)mul14[state[12]] ^ mul11[state[13]] ^ mul13[state[14]] ^ mul9[state[15]];
	tmp[13] = (unsigned char)mul9[state[12]] ^ mul14[state[13]] ^ mul11[state[14]] ^ mul13[state[15]];
	tmp[14] = (unsigned char)mul13[state[12]] ^ mul9[state[13]] ^ mul14[state[14]] ^ mul11[state[15]];
	tmp[15] = (unsigned char)mul11[state[12]] ^ mul13[state[13]] ^ mul9[state[14]] ^ mul14[state[15]];

	for (int i = 0; i < 16; i++)
		state[i] = tmp[i];
	
}

void ShiftRows(unsigned char * state) {
	unsigned char tmp[16];

	/* Column 1 */
	tmp[0] = state[0];
	tmp[1] = state[13];
	tmp[2] = state[10];
	tmp[3] = state[7];

	/* Column 2 */
	tmp[4] = state[4];
	tmp[5] = state[1];
	tmp[6] = state[14];
	tmp[7] = state[11];

	/* Column 3 */
	tmp[8] = state[8];
	tmp[9] = state[5];
	tmp[10] = state[2];
	tmp[11] = state[15];

	/* Column 4 */
	tmp[12] = state[12];
	tmp[13] = state[9];
	tmp[14] = state[6];
	tmp[15] = state[3];

	for (int i = 0; i < 16; i++) {
		state[i] = tmp[i];
	}
}

void SubBytes(unsigned char * state) {
	for (int i = 0; i < 16; i++) 
		state[i] = inv_s[state[i]];
}

void decryptionRound(unsigned char * state, unsigned char * key) {
	SubRoundKey(state, key);
	InverseMixColumns(state);
	ShiftRows(state);
	SubBytes(state);
}

void firstRound(unsigned char * state, unsigned char * key) {
	SubRoundKey(state, key);
	ShiftRows(state);
	SubBytes(state);
}

void AESDecrypt(unsigned char * encryptedMessage, unsigned char * expandedKey, unsigned char * decryptedMessage)
{
	unsigned char state[16];

	for (int i = 0; i < 16; i++) {
		state[i] = encryptedMessage[i];
	}

	firstRound(state, expandedKey+160);

	int numberOfRounds = 9;

	for (int i = 8; i >= 0; i--) {
		decryptionRound(state, expandedKey + (16 * (i + 1)));
	}

	SubRoundKey(state, expandedKey); 

	for (int i = 0; i < 16; i++)
		decryptedMessage[i] = state[i];
}


int main(){
	
	unsigned char expandedKey[176];

	KeyExpansion(key, expandedKey);
	
	int sfd, nsfd, size; 
    struct sockaddr_in address; 
    int opt = 1; 
    int addrlen = sizeof(address); 
    unsigned char buff[17] = {0}; 
       

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
	read(nsfd, buff, sizeof(buff)); 

	buff[16]='\0';
	cout<<"Encrypted message = "<<buff<<"\n";
	unsigned char * decryptedMessage = new unsigned char[17];
	
	AESDecrypt(buff, expandedKey, decryptedMessage);
	
	decryptedMessage[16]='\0';
	cout<<"Decrpyted message = "<<decryptedMessage<<"\n";

	return 0;
}		
	
	
