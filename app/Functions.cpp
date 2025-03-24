#include "Functions.h"
#include "ConvertFuncs.h"
#include <fstream>
//Подключение к таблице БД
//Data Source=EGOR-DESK\MSSQLSERVER_ONE;Initial Catalog=Bank;Integrated Security=True;
// Connect Timeout=30;Encrypt=False;Trust Server Certificate=False;Application Intent=ReadWrite;Multi Subnet Failover=False
void Functions::ConnectToDB() {
	
	connStringBuilder = gcnew SqlConnectionStringBuilder();
	connStringBuilder->DataSource = "EGOR-DESK\\MSSQLSERVER_ONE";
	connStringBuilder->InitialCatalog = "Bank";
	connStringBuilder->IntegratedSecurity = true;
	connStringBuilder->ConnectTimeout = 30;
	connStringBuilder->Encrypt = false;
	connStringBuilder->TrustServerCertificate = false;
	connStringBuilder->ApplicationIntent = Data::SqlClient::ApplicationIntent::ReadWrite;
	connStringBuilder->MultiSubnetFailover = false;

	conn = gcnew SqlConnection(Convert::ToString(connStringBuilder));
}



int Functions::Insert(String^ &text, String^ &iv,const uint8_t key[]) {
	int error;
	try
	{

		Encrypt(text, iv, key);
		//Подключаемся к БД
		if (text == "") throw;
		if (iv == "") throw;
		ConnectToDB();
		String^ cmdText = "INSERT INTO dbo.people (password, nickname) VALUES (@Password, @Nickname)";
		SqlCommand^ cmd = gcnew SqlCommand(cmdText, conn);

		//Инициализируем параметры
		cmd->Parameters->AddWithValue("@Password", text);
		cmd->Parameters->AddWithValue("@Nickname", iv);

		conn->Open();
		cmd->ExecuteNonQuery();
		//cmd->EndExecuteReader();
	}
	catch (Exception^ ex)
	{
		
		
		if (ex->Message[0] == 1053) {
			throw "Имя пользователя " + iv + " занято. Попробуйте снова. ";					//Код ошибки 1 - повторяющийся никнейм
		}
		else if (text == "" || iv == "") {
			if (text == "")throw (String^)"Пароль не введен.";
			if (iv == "")throw (String^)"Имя пользователя не введено.";
		}
		else {
			MessageBox::Show(ex->Message);
		}
	}
	finally
	{
		if (conn != nullptr) {
			conn->Close();
		}
		
	}
	return error;
}

uint8_t* Functions::getKeys() {
	fstream file;
	string path = "F:\\keys.txt";
	file.open(path);
	char key1[32];
	char key2[32];
	uint8_t* uintKey1= new uint8_t[32];
	uint8_t* uintKey2= new uint8_t[32];
	if (!file.is_open()) {
		throw "По пути <" + path + "> не удалось найти ключевой файл.";
	}
	else {
		
		file.getline(key1, 32);
		file.getline(key2, 32);
		for (size_t i = 0; i < 32; i++)
		{
			uintKey1[i] = (uint8_t)key1[i];
		}
	}
	return uintKey1;
}

int Functions::InsertInCell(String^& text, String^& iv, const uint8_t key[]) {
	int error;
	try
	{

		Encrypt(text, iv, key);
		//Подключаемся к БД
		if (text == "") throw;
		if (iv == "") throw;
		ConnectToDB();
		String^ cmdText = "INSERT INTO dbo.people (password, nickname) VALUES (@Password, @Nickname)";
		SqlCommand^ cmd = gcnew SqlCommand(cmdText, conn);

		//Инициализируем параметры
		cmd->Parameters->AddWithValue("@Password", text);
		cmd->Parameters->AddWithValue("@Nickname", iv);

		conn->Open();
		cmd->ExecuteNonQuery();
		//cmd->EndExecuteReader();
	}
	catch (Exception^ ex)
	{


		if (ex->Message[0] == 1053) {
			throw "Имя пользователя " + iv + " занято. Попробуйте снова. ";					//Код ошибки 1 - повторяющийся никнейм
		}
		else if (text == "" || iv == "") {
			if (text == "")throw (String^)"Пароль не введен.";
			if (iv == "")throw (String^)"Имя пользователя не введено.";
		}
		else {
			MessageBox::Show(ex->Message);
		}
	}
	finally
	{
		if (conn != nullptr) {
			conn->Close();
		}

	}
	return error;
}

void Functions::FillDataGridView(DataGridView^ dgvInfo) {
	try
	{
		ConnectToDB();
		conn->Open();
		String^ cmdText = "SELECT * FROM dbo.people";
		SqlCommand^ cmd = gcnew SqlCommand(cmdText, conn);

		SqlDataAdapter^ sda = gcnew SqlDataAdapter(cmd);
		DataTable^ dt = gcnew DataTable();
		sda->Fill(dt);

		dgvInfo->DataSource = dt;
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
	finally
	{
		if (conn != nullptr)
		{
			conn->Close();
		}

	}
}




void Functions::Encrypt(String^ &in_text,String^& in_iv, const uint8_t key[]) {

	

	setlocale(LC_ALL, "rus");
	GOST_Magma G;
	ConvertFuncs C;
	
	
	string in_text_std; string in_iv_std;
	C.ConvertSystemStringToStdString(in_text, in_text_std);
	C.ConvertSystemStringToStdString(in_iv, in_iv_std);
	
	uint8_t* gamma = new uint8_t[in_iv_std.size()];
	memset(gamma, 0, in_iv_std.size());
	C.ConvertSdtStringToUint8(in_iv_std, gamma);

	size_t block_count;
	if (in_text_std.size() % (BLOCK_SIZE * 2) == 0)
	{
		block_count = (in_text_std.size() / (BLOCK_SIZE * 2));
	}
	else {
		block_count = (in_text_std.size() / (BLOCK_SIZE * 2)) + 1;
	}
	uint8_t** block_arr = new uint8_t * [block_count];
	for (int i = 0; i < block_count; i++)
	{
		block_arr[i] = new uint8_t[BLOCK_SIZE * 2];
	}
	G.splitToBlocks(block_arr, in_text_std, in_text_std.size(), block_count);
	G.printmatr(block_arr, block_count);


	uint8_t xortxt[BLOCK_SIZE * 2];
	uint8_t out_data[BLOCK_SIZE * 2];

	for (int i = 0; i < block_count; i++)
	{
		if (i == 0) {
			cout << "Открытый текст " << i << " блок: " << " - ";
			G.Print_data(block_arr[0]);

			uint8_t* gamma_buff = new uint8_t[in_iv_std.size()];
			G.GOST_Magma_encrypt(key, gamma, gamma_buff);
			G.xorf(gamma_buff, block_arr[0], block_arr[0]);

			cout << "Зашифрованный текст под гаммой " << i << " блок: " << " - ";
			G.Print_data(block_arr[0]);
			delete[] gamma_buff;
		}
		else {
			cout << "Открытый текст " << i << " блок: " << " - ";
			G.Print_data(block_arr[i]);


			G.GOST_Magma_encrypt(key, block_arr[i - 1], block_arr[i - 1]);
			G.xorf(block_arr[i], block_arr[i - 1], block_arr[i]);
			cout << "Зашифрованный текст под гаммой " << i << " блок: " << " - ";
			G.Print_data(block_arr[i]);
		}
	}
	cout << endl << endl;
	
	
	string message = "";
	G.shrinkBlocks(block_arr, message, block_count);

	String^ output_text;
	C.ConvertStdStringToSystemString(message, output_text);
	in_text = output_text;
	
	
	//Console::WriteLine(in_text);
	for (size_t i = 0; i < block_count; i++)
	{
		delete[] block_arr[i];
	}
	delete[] gamma;
}

String^ Functions::Decrypt(String^ in_text,String^ in_iv, const uint8_t key[]) {
	setlocale(LC_ALL, "rus");
	GOST_Magma G;
	ConvertFuncs C;


	string in_text_std; string in_iv_std;
	C.ConvertSystemStringToStdString(in_text, in_text_std);
	C.ConvertSystemStringToStdString(in_iv, in_iv_std);

	uint8_t* gamma = new uint8_t[in_iv_std.size()];
	memset(gamma, 0, in_iv_std.size());
	C.ConvertSdtStringToUint8(in_iv_std, gamma);

	size_t block_count;
	if (in_text_std.size() % (BLOCK_SIZE * 2) == 0)
	{
		block_count = (in_text_std.size() / (BLOCK_SIZE * 2));
	}
	else {
		block_count = (in_text_std.size() / (BLOCK_SIZE * 2)) + 1;
	}
	uint8_t** block_arr = new uint8_t * [block_count];
	for (int i = 0; i < block_count; i++)
	{
		block_arr[i] = new uint8_t[BLOCK_SIZE * 2];
	}
	G.splitToBlocks(block_arr, in_text_std, in_text_std.size(), block_count);
	G.printmatr(block_arr, block_count);


	uint8_t xortxt[BLOCK_SIZE * 2];
	uint8_t out_data[BLOCK_SIZE * 2];

	uint8_t** NEWarr = new uint8_t * [block_count];
	for (int i = 0; i < block_count; i++)
	{
		NEWarr[i] = new uint8_t[BLOCK_SIZE * 2];
	}
	for (int i = 0; i < block_count; i++)
	{
		if (i == 0) {

			uint8_t* gamma_buff = new uint8_t[in_iv_std.size()];
			G.GOST_Magma_encrypt(key, gamma, gamma_buff);
			G.xorf(gamma_buff, block_arr[0], NEWarr[0]);
			cout << "Расшифрованный текст с гаммой:";
			G.Print_data(NEWarr[0]);
			delete[] gamma_buff;
		}
		else {


			G.GOST_Magma_encrypt(key, block_arr[i - 1], block_arr[i - 1]);
			G.xorf(block_arr[i], block_arr[i - 1], NEWarr[i]);
			cout << "Расшифрованный текст с гаммой:";
			G.Print_data(NEWarr[i]);
		}
	}
	cout << endl << endl;


	string message = "";
	G.shrinkBlocks(NEWarr, message, block_count);
	for (int i = 0; i < BLOCK_SIZE * 2 * block_count; i++)
	{
		if (message[i] == 'э' || message[i] == 'Э') {
			message[i] = ' ';
		}

	}
	String^ output_text;
	C.ConvertStdStringToSystemString(message, output_text);
	
	in_text = output_text;


	//Console::WriteLine(in_text);


	System::Text::Encoding^ utf8 = System::Text::Encoding::UTF8;
	System::Text::Encoding^ cp1251 = System::Text::Encoding::GetEncoding(1251);
	cli::array<Byte>^ utf8Bytes = utf8->GetBytes(in_text);
	cli::array<Byte>^ cp1251Bytes = System::Text::Encoding::Convert(utf8, cp1251, utf8Bytes);
	in_text = in_text->Remove(0,BLOCK_SIZE);
	in_text = cp1251->GetString(cp1251Bytes);
	

	for (size_t i = 0; i < block_count; i++)
	{
		delete[] block_arr[i];
	}
	for (size_t i = 0; i < block_count; i++)
	{
		delete[] NEWarr[i];
	}
	delete[] gamma;
	return in_text;
}
