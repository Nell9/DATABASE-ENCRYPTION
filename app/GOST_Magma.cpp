#include "GOST_Magma.h"

void GOST_Magma::GOST_Magma_Expand_Key(const uint8_t* key)
{
	for (size_t i = 0, j = 0; i < 24; i++, j += 4)
	{
		if (i % 8 == 0)j = 0;
		memcpy(iter_key[i], key + j, 4);
	}

	for (size_t i = 24, j = 28; i < 32; i++, j -= 4)
		memcpy(iter_key[i], key + j, 4);
}

void GOST_Magma::splitToBlocks(uint8_t** block_arr, string message, size_t message_size, size_t block_count) {
	ConvertFuncs C;
	uint8_t* byteData = new uint8_t[message_size];
	C.ConvertSdtStringToUint8(message, byteData);



	for (int i = 0, k = 0; i < block_count; i++)
	{
		for (int j = 0; j < BLOCK_SIZE * 2; j++, k++)
		{
			block_arr[i][j] = byteData[k];
			cout << hex << (int)byteData[k];
		}
		cout << endl;
	}
}

void GOST_Magma::shrinkBlocks(uint8_t** block_arr, string& message, size_t block_count) {
	ConvertFuncs C;
	string buff_str = "";
	for (int i = 0; i < block_count; i++)
	{

		C.ConvertUint8ToStdString(block_arr[i], BLOCK_SIZE * 2, buff_str);
		message += buff_str;
		buff_str = "";

	}

}
void GOST_Magma::printmatr(uint8_t** matr, size_t block_count) {

	for (int i = 0; i < block_count; i++)
	{
		for (int j = 0; j < BLOCK_SIZE * 2; j++)
		{
			cout << hex << (int)matr[i][j];
		}
		cout << endl;
	}
}

void GOST_Magma::GOST_Magma_Add_32(const uint8_t* a, const uint8_t* b, uint8_t* c)
{
	int i;
	unsigned int internal = 0;
	for (i = 3; i >= 0; i--)
	{
		internal = a[i] + b[i] + (internal >> 8);
		c[i] = internal & 0xff;
	}
}

void GOST_Magma::GOST_Magma_Add(const uint8_t* a, const uint8_t* b, uint8_t* c)
{
	int i;
	for (i = 0; i < 4; i++)
		c[i] = a[i] ^ b[i];
}


void GOST_Magma::GOST_Magma_T(const uint8_t* in_data, uint8_t* out_data)
{
	uint8_t first_part_byte, sec_part_byte;
	int i;
	for (i = 0; i < 4; i++)
	{
		first_part_byte = (in_data[i] & 0xf0) >> 4;
		sec_part_byte = (in_data[i] & 0x0f);
		first_part_byte = Pi[i * 2][first_part_byte];
		sec_part_byte = Pi[i * 2 + 1][sec_part_byte];
		out_data[i] = (first_part_byte << 4) | sec_part_byte;
	}
}

void GOST_Magma::GOST_Magma_g(const uint8_t* k, const uint8_t* a, uint8_t* out_data)
{
	uint8_t internal[4];
	uint32_t out_data_32;

	GOST_Magma_Add_32(a, k, internal);
	GOST_Magma_T(internal, internal);

	out_data_32 = internal[0];
	out_data_32 = (out_data_32 << 8) + internal[1];
	out_data_32 = (out_data_32 << 8) + internal[2];
	out_data_32 = (out_data_32 << 8) + internal[3];
	out_data_32 = (out_data_32 << 11) | (out_data_32 >> 21);
	out_data[3] = out_data_32;
	out_data[2] = out_data_32 >> 8;
	out_data[1] = out_data_32 >> 16;
	out_data[0] = out_data_32 >> 24;
}

void GOST_Magma::GOST_Magma_G(const uint8_t* k, const uint8_t* a, uint8_t* out_data)
{
	uint8_t a_r[4];
	uint8_t a_l[4];
	uint8_t G[4];

	int i;
	for (i = 0; i < 4; i++)
	{
		a_r[i] = a[4 + i];
		a_l[i] = a[i];
	}

	GOST_Magma_g(k, a_r, G);
	GOST_Magma_Add(a_l, G, G);

	for (i = 0; i < 4; i++)
	{

		a_l[i] = a_r[i];

		a_r[i] = G[i];
	}

	for (i = 0; i < 4; i++)
	{
		out_data[i] = a_l[i];
		out_data[4 + i] = a_r[i];
	}
}

void GOST_Magma::GOST_Magma_G_Fin(const uint8_t* k, const uint8_t* a, uint8_t* out_data)
{
	uint8_t a_r[4];
	uint8_t a_l[4];
	uint8_t G[4];

	for (int i = 0; i < 4; i++)
	{
		a_r[i] = a[4 + i];
		a_l[i] = a[i];
	}

	GOST_Magma_g(k, a_r, G);
	GOST_Magma_Add(a_l, G, G);

	for (int i = 0; i < 4; i++)
		a_l[i] = G[i];
	for (int i = 0; i < 4; i++)
	{
		out_data[i] = a_l[i];
		out_data[4 + i] = a_r[i];
	}
}

void GOST_Magma::GOST_Magma_encrypt(const uint8_t* key, uint8_t* input_data, uint8_t* output_data2)
{
	uint8_t out_data[BLOCK_SIZE * 2];


	GOST_Magma_Expand_Key(key);
	GOST_Magma_G(iter_key[0], input_data, out_data);

	int i = 1;
	while (i < 31) {
		GOST_Magma_G(iter_key[i], out_data, out_data);
		i++;
	}
	GOST_Magma_G_Fin(iter_key[31], out_data, out_data);

	output_data2 = out_data;
}

void GOST_Magma::GOST_Magma_Decript(const uint8_t* blk, uint8_t* out_blk)
{
	GOST_Magma_G(iter_key[31], blk, out_blk);
	for (int i = 30; i > 0; i--)
		GOST_Magma_G(iter_key[i], out_blk, out_blk);

	GOST_Magma_G_Fin(iter_key[0], out_blk, out_blk);
	
	cout << "Расшифрованные данные:";
	Print_data(out_blk);
}

void GOST_Magma::Print_data(uint8_t* out_data)
{
	for (int i = 0; i < BLOCK_SIZE * 2; i++)
	{
		cout << hex << int(out_data[i]);
	}
	cout << endl;
}

void GOST_Magma::Print_key_and_iter_key(const uint8_t* key)
{
	cout << "key: ";
	for (int i = 0; i < BLOCK_SIZE * 8; i++)
	{
		cout << hex << int(key[i]);
	}
	cout << endl;

	for (int i = 0; i < BLOCK_SIZE * 8; i++)
	{
		cout << "KEY" << dec << i + 1 << " = ";
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			cout << hex << int(iter_key[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

