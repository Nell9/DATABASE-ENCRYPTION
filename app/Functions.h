#pragma once

#include "iostream"
#include "GOST_Magma.h"
#include "ConvertFuncs.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Data;
using namespace Data::SqlClient;
using namespace std;

ref class Functions
{
public:
	Functions() {};
private:
	SqlConnection^ conn;
	SqlConnectionStringBuilder^ connStringBuilder;
	void ConnectToDB();
	void Encrypt(String^& text, String^& iv, const uint8_t key[]);
	
	
public:
	String^ Decrypt(String^ text, String^ iv, const uint8_t key[]);
	int Insert(String^ &text, String^ &iv, const uint8_t key[]);
	int InsertInCell(String^& text, String^& iv, const uint8_t key[]);
	uint8_t* getKeys();
	void FillDataGridView(DataGridView^ dgvInfo);
	
};

