#include <bits/stdc++.h>

using namespace std;

/*------------------------------------RESOURCES------------------------------------*/

static const uint8_t sbox[256] = {
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

static const uint8_t rsbox[256] = {
	  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
	  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
	  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
	  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
	  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
	  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
	  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
	  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
	  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
	  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
	  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
	  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
	  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

static const uint8_t rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

/*------------------------------------RESOURCES------------------------------------*/

/*------------------------------------START DATA PROCESSING FUNCTIONS------------------------------------*/

int hexToDec(string hexVal){ //Convert Hex to Dec
    int len = hexVal.size();
    int base = 1;
    int dec_val = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {				//Convert num to hex value 
            dec_val += (int(hexVal[i]) - 48) * base;			//Num's in Dec - 48 hex normalization {0 - 9}
             base = base * 16;
        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {   		//Convert char to hex value 
            dec_val += (int(hexVal[i]) - 55) * base;			//Num's in Dec - 55 hex normalization {10 - 15}
            base = base * 16;
        }
    }
    return dec_val;
}


void fromHex(string str, uint8_t ret[4][4]){	//Convert 16 bytes Hex of Key to Dec, input to 4 x 4 matrix
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			ret[i][j] = hexToDec(str.substr((2*j)+(8*i), 2));	// each element is 1 byte
		}
	}
}

void copyColumn(uint8_t a[4], uint8_t b[4]){
	for (int i = 0; i < 4; i++){
		b[i] = a[i];
	}
}

/*------------------------------------END DATA PROCESSING FUNCTIONS------------------------------------*/

/*------------------------------------START FUNCTION KEY INITIALIZATION------------------------------------*/

void rotWord(uint8_t a[4]){		
	uint8_t b[4];
	for (int i = 0; i < 4; i++){
		b[i] = a[(i + 1) % 4];
	}
	copy(&b[0], &b[0]+4, &a[0]);
}

void subBytesRow(uint8_t a[4])
{
	for (int i = 0; i < 4; i++){
		stringstream stream;
		stream << hex << (int)a[i];	//input Hex form of a[i] to streamstring
		string result(stream.str());	//return result to string

		int left, right;					

		stringstream().swap(stream);	//Swap stringstream with empty string

		if (result.length() < 2)     		//If the result in hex has 1 char then left character = 0
		{
			left = 0;
		}
		else
		{
			stream << result[0];	
			stream >> hex >> left;		
		}

		stringstream().swap(stream);	//Swap stringstream with empty string

		stream << result.back();
		stream >> hex >> right;

		a[i] = sbox[right + (16 * left)];	//Replace bytes with S-box
	}

}

void keyExpansion(uint8_t cipherKey[4][4], uint8_t extensionKey[44][4])	//Generate the expansion key as a 44 x 4 matrix
{
	for (int i = 0; i < 4; i++){		//input cipherkey to extensionKey
		for (int j = 0; j < 4; j++){
			extensionKey[i][j] = cipherKey[i][j]; 
		}
	}

	for (int i = 4; i < 44; i++)
	{
		uint8_t tempRcon[4] = {0, 0, 0, 0};
		uint8_t temp[4];
		copyColumn(extensionKey[i - 1], temp); //get last column of extensionKey to calculate Zi = (XorRcon(sw, RC[i]))

		if (i % 4 == 0)
		{
			tempRcon[0] = rcon[(i/4) - 1];	 	//change rcon with i
			rotWord(temp);						//1 byte left round shift
			subBytesRow(temp);					//Replace each bytes with S-box
		}
		
		for (int j = 0; j < 4; j++)
		{
			extensionKey[i][j] = (i % 4 == 0) ? (extensionKey[i - 4][j] ^ temp[j] ^ tempRcon[j]) : (extensionKey[i - 4][j] ^ temp[j]); //Generate new round key and add to extensionKey
		}
	}
}

void updateRoundKey(uint8_t a[44][4], uint8_t b[4][4], unsigned int round) //Convert each 16-byte key in a 44 x 4 matrix to a 4 x 4 matrix
{
	if (round > 10)
	{
		cout << "The round cannot be larger than 10" << endl;
		exit(1);
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b[i][j] = a[i + (4*round)][j];	
		}
	}
}

/*------------------------------------END FUNCTION KEY INITIALIZATION------------------------------------*/

/*------------------------------------START ENCRYPTION FUNCTION------------------------------------*/

void addRoundKey(uint8_t a[4][4], uint8_t b[4][4]) //XOR 
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			a[i][j] ^= b[i][j];
		}
	}
}

void subBytes(uint8_t a[4][4])					//
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			stringstream stream;
			stream << hex << (int)a[i][j];	//input Hex form of a[i][j] to streamstring
			string result(stream.str());	//return result to string

			int left, right;
			stringstream().swap(stream);	//Swap stringstream with empty string

			if (result.length() < 2)			//If the result in hex has 1 char then left character = 0
			{
				left = 0;
			}
			else
			{
				stream << result[0];
				stream >> hex >> left;
			}

			stringstream().swap(stream);	//Swap stringstream with empty string

			stream << result.back();
			stream >> hex >> right;
			a[i][j] = sbox[right + (16 * left)];	//Replace bytes with S-box
		}
	}
}

void shiftRows(uint8_t a[4][4])						
{
	uint8_t b[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			b[j][i] = a[(j + i) % 4][i]; 			//Because the key is stored in a column matrix, shiftRows is stored as a column
		}
	}

	copy(&b[0][0], &b[0][0]+4*4,&a[0][0]);
}

void mixColumns(uint8_t a[4][4])					//Mix bytes in state
{
	for (int i = 0; i < 4; i++)
	{
		uint8_t temp[4];
		uint8_t multi[4];
		for (int j = 0; j < 4; j++)
		{
			temp[j] = a[i][j];
			uint8_t h = (unsigned char)((signed char)a[i][j] >> 7);  //get leftmost bit
			multi[j] = a[i][j] << 1;								 //1 bit left shift
			multi[j] ^= 0x1B & h;									 // XOR 1B and bitwise AND with h
		}

		a[i][0] = multi[0] ^ temp[3] ^ temp[2] ^ multi[1] ^ temp[1];
		a[i][1] = multi[1] ^ temp[0] ^ temp[3] ^ multi[2] ^ temp[2];
		a[i][2] = multi[2] ^ temp[1] ^ temp[0] ^ multi[3] ^ temp[3];
		a[i][3] = multi[3] ^ temp[2] ^ temp[1] ^ multi[0] ^ temp[0];
	}
}

/*------------------------------------END ENCRYPTION FUNCTION------------------------------------*/

void printResult(uint8_t arr[4][4])
{
	cout << "hex: ";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if ((int)arr[i][j] - 10 < 0)
			{
				cout << "0";
			}
			cout << hex << (int)arr[i][j];
		}
	}
	cout << endl;
}

int main(){
	string text, key;
	cout << "Text input: "; cin >> text;
	if (text.size() > 32)
	{
		cout << "The text in hex format cannot be more than 32 characters." << endl;
		return 0;
	}

	cout << "Key input: "; cin >> key;
	if (key.size() > 32)
	{
		cout << "The text in hex format cannot be more than 32 characters." << endl;
		return 0;
	}

	uint8_t fullKey[44][4];
	uint8_t state[4][4];
	uint8_t roundKey[4][4];

	fromHex(text, state);
	fromHex(key, roundKey);
	cout << "-------- Encryptng --------" << endl;
	cout << "Text: " << text << endl;
	cout << "Key:  " << key << endl;

	keyExpansion(roundKey, fullKey);			//Generate the expansion key
	updateRoundKey(fullKey, roundKey, 0); 		//Convert 16-byte key round 0 in Expansion key to Round key
	addRoundKey(state, roundKey);				//XOR Origin State (M) with Origin roundKey (K)

	for (int i = 1; i <= 9; i++)				//10 Rounds
	{
		subBytes(state);						//Replace each byte in state with S-box
		shiftRows(state);						//ShiftRows left-shift bytes in state
		mixColumns(state);						//Mixbytes in state
		updateRoundKey(fullKey, roundKey, i);	//Convert 16-byte key round i in Expansion key to Round key ( i = {1 -> 9})
		addRoundKey(state, roundKey);			//XOR State (i) with roundKey (K(i+1))
	}
	subBytes(state);
	shiftRows(state);
	updateRoundKey(fullKey, roundKey, 10);		//Convert 16-byte key round 10 in Expansion key to Round key 
	addRoundKey(state, roundKey);				//XOR State (9) with roundKey (K(10))

	printResult(state);

	return 0;
}