#include <iostream>
#include "ConvertFuncs.h"
using namespace std;

constexpr auto BLOCK_SIZE = 4;
static uint8_t iter_key[32][4];
static unsigned char Pi[8][16] =
{
  {1,7,14,13,0,5,8,3,4,15,10,6,9,12,11,2},
  {8,14,2,5,6,9,1,12,15,4,11,0,13,10,3,7},
  {5,13,15,6,9,2,12,10,11,7,8,1,4,3,14,0},
  {7,15,5,10,8,1,6,13,0,9,3,14,11,4,2,12},
  {12,8,2,1,13,4,15,6,7,0,10,5,3,14,9,11},
  {11,3,5,8,2,15,10,13,14,1,7,4,12,9,6,0},
  {6,8,2,3,9,10,5,12,1,14,4,7,11,13,0,15},
  {12,4,6,2,10,5,11,9,14,8,13,7,0,3,15,1}
};


ref class GOST_Magma {
public:
	void GOST_Magma_encrypt(const uint8_t* key, uint8_t* input_data,  uint8_t* input_data2);
	void Print_key_and_iter_key(const uint8_t* key);
	void Print_data(uint8_t* out_data);
	void xorf(const uint8_t* a, const uint8_t* b, uint8_t* c)
	{
		int i;
		for (i = 0; i < BLOCK_SIZE * 2; i++)
			c[i] = a[i] ^ b[i];
	}
	void GOST_Magma_Decript(const uint8_t* blk, uint8_t* out_blk);
	void GOST_Magma_Expand_Key(const uint8_t* key);
	void splitToBlocks(uint8_t** block_arr, string message, size_t message_size, size_t block_count);
	void shrinkBlocks(uint8_t** block_arr, string& message, size_t block_count);
	void printmatr(uint8_t** matr, size_t block_count);
private:
	

	
	static void GOST_Magma_Add_32(const uint8_t* a, const uint8_t* b, uint8_t* c);
	static void GOST_Magma_Add(const uint8_t* a, const uint8_t* b, uint8_t* c);
	static void GOST_Magma_T(const uint8_t* in_data, uint8_t* out_data);
	static void GOST_Magma_g(const uint8_t* k, const uint8_t* a, uint8_t* out_data);
	static void GOST_Magma_G(const uint8_t* k, const uint8_t* a, uint8_t* out_data);
	static void GOST_Magma_G_Fin(const uint8_t* k, const uint8_t* a, uint8_t* out_data);
};

