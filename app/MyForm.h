#pragma once
#include "Functions.h"
#include "ConvertFuncs.h"
namespace app {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			backgroundImage = Image::FromFile("D:\\Downloads\\fon.jpg");
			//
			//
			//TODO: добавьте код конструктора
			//
			this->dgvInfo->CellEndEdit += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::dataGridView1_CellEndEdit);
			this->dgvInfo->CurrentCellDirtyStateChanged += gcnew System::EventHandler(this, &MyForm::dataGridView1_CurrentCellDirtyStateChanged);
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ buttonInsertData;
	protected:

	private: System::Windows::Forms::TextBox^ text;
	private: System::Windows::Forms::DataGridView^ dgvInfo;

	private: System::Windows::Forms::BindingSource^ bindingSource1;
	private: System::Windows::Forms::Button^ buttonTakeData;

	private: System::Windows::Forms::Button^ buttonDecrypt;
	private: System::Windows::Forms::TextBox^ userName;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Timer^ timer1;
	private: int timer1_tickCount;
	private: Image^ backgroundImage;

	private: System::ComponentModel::IContainer^ components;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		/// 
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->buttonInsertData = (gcnew System::Windows::Forms::Button());
			this->text = (gcnew System::Windows::Forms::TextBox());
			this->dgvInfo = (gcnew System::Windows::Forms::DataGridView());
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->buttonTakeData = (gcnew System::Windows::Forms::Button());
			this->buttonDecrypt = (gcnew System::Windows::Forms::Button());
			this->userName = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvInfo))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->BeginInit();
			this->SuspendLayout();
			// 
			// buttonInsertData
			// 
			this->buttonInsertData->BackColor = System::Drawing::SystemColors::HighlightText;
			this->buttonInsertData->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonInsertData->Location = System::Drawing::Point(118, 371);
			this->buttonInsertData->Name = L"buttonInsertData";
			this->buttonInsertData->Size = System::Drawing::Size(126, 23);
			this->buttonInsertData->TabIndex = 0;
			this->buttonInsertData->Text = L"Внести данные";
			this->buttonInsertData->UseVisualStyleBackColor = false;
			this->buttonInsertData->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// text
			// 
			this->text->BackColor = System::Drawing::SystemColors::HighlightText;
			this->text->Location = System::Drawing::Point(93, 345);
			this->text->MaxLength = 64;
			this->text->Name = L"text";
			this->text->PasswordChar = '*';
			this->text->Size = System::Drawing::Size(190, 20);
			this->text->TabIndex = 1;
			// 
			// dgvInfo
			// 
			this->dgvInfo->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dgvInfo->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dgvInfo->BackgroundColor = System::Drawing::Color::Linen;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvInfo->DefaultCellStyle = dataGridViewCellStyle1;
			this->dgvInfo->GridColor = System::Drawing::Color::AliceBlue;
			this->dgvInfo->Location = System::Drawing::Point(78, 12);
			this->dgvInfo->MultiSelect = false;
			this->dgvInfo->Name = L"dgvInfo";
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Consolas", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dgvInfo->RowHeadersDefaultCellStyle = dataGridViewCellStyle2;
			this->dgvInfo->Size = System::Drawing::Size(470, 210);
			this->dgvInfo->TabIndex = 0;
			// 
			// buttonTakeData
			// 
			this->buttonTakeData->BackColor = System::Drawing::SystemColors::HighlightText;
			this->buttonTakeData->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonTakeData->Location = System::Drawing::Point(351, 302);
			this->buttonTakeData->Name = L"buttonTakeData";
			this->buttonTakeData->Size = System::Drawing::Size(187, 23);
			this->buttonTakeData->TabIndex = 2;
			this->buttonTakeData->Text = L"Получить информацию о БД";
			this->buttonTakeData->UseVisualStyleBackColor = false;
			this->buttonTakeData->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// buttonDecrypt
			// 
			this->buttonDecrypt->BackColor = System::Drawing::SystemColors::HighlightText;
			this->buttonDecrypt->Enabled = false;
			this->buttonDecrypt->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->buttonDecrypt->Location = System::Drawing::Point(351, 343);
			this->buttonDecrypt->Name = L"buttonDecrypt";
			this->buttonDecrypt->Size = System::Drawing::Size(187, 23);
			this->buttonDecrypt->TabIndex = 4;
			this->buttonDecrypt->Text = L"Расшифровать БД";
			this->buttonDecrypt->UseVisualStyleBackColor = false;
			this->buttonDecrypt->Click += gcnew System::EventHandler(this, &MyForm::buttonDecrypt_Click);
			// 
			// userName
			// 
			this->userName->BackColor = System::Drawing::SystemColors::HighlightText;
			this->userName->Location = System::Drawing::Point(93, 304);
			this->userName->MaxLength = 8;
			this->userName->Name = L"userName";
			this->userName->Size = System::Drawing::Size(190, 20);
			this->userName->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(127, 288);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(119, 15);
			this->label1->TabIndex = 7;
			this->label1->Text = L"Имя пользователя";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(118, 327);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(140, 15);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Пароль пользователя";
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(216, 407);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(203, 31);
			this->label4->TabIndex = 10;
			this->label4->Text = L"label4";
			this->label4->Visible = false;
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(625, 488);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->userName);
			this->Controls->Add(this->buttonDecrypt);
			this->Controls->Add(this->buttonTakeData);
			this->Controls->Add(this->dgvInfo);
			this->Controls->Add(this->text);
			this->Controls->Add(this->buttonInsertData);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"SkriptMaster";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvInfo))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bindingSource1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		private:
			uint8_t* key1 = new uint8_t[32];
			uint8_t* key2 = new uint8_t[32];
		// Обработчик события CellEndEdit
		void dataGridView1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
		{
			int rowIndex = e->RowIndex;
			int columnIndex = e->ColumnIndex;
			String^ newValue = dgvInfo->Rows[rowIndex]->Cells[columnIndex]->Value->ToString();

		}
		
		
		
		// Обработчик события CurrentCellDirtyStateChanged
		void dataGridView1_CurrentCellDirtyStateChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (this->dgvInfo->IsCurrentCellDirty)
			{
				this->dgvInfo->CommitEdit(System::Windows::Forms::DataGridViewDataErrorContexts::Commit);
			}
		}

#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Functions f;
		ConvertFuncs C;
		try {
			key1 = f.getKeys();
		}
		catch (string err) {
			String^ out_err;
			C.ConvertStdStringToSystemString(err, out_err);
			label4->Text = out_err;
			label4->ForeColor = Color::Red;
			label4->Visible = true;
			return;
		}

		String^ input_data = text->Text;
		String^ iv = userName->Text;
		try {
			f.Insert(input_data, iv, key1);
		}
		catch(String^ err){
			label4->Text=err;
			label4->ForeColor = Color::Red;
			label4->Visible = true;
			timer1->Start();
			return;
		}
		label4->ForeColor = Color::Green;
		label4->Text = "Данные успешно внесены!";
		buttonTakeData->PerformClick();
	}
	
	
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		Functions f;
		f.FillDataGridView(dgvInfo);
		buttonDecrypt->Enabled = true;
		Functions F;
		
		
	}

	private: System::Void buttonDecrypt_Click(System::Object^ sender, System::EventArgs^ e) {
		//const uint8_t key[BLOCK_SIZE * 8] = { 0xff,0xee,0xdd,0xcc,0xbb,0xaa,0x99,0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,0x00,
		//								  0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff };

		Functions f;
		ConvertFuncs C;
		try {
			key1 = f.getKeys();
		}
		catch (string err) {
			String^ out_err;
			C.ConvertStdStringToSystemString(err, out_err);
			label4->Text = out_err;
			label4->ForeColor = Color::Red;
			label4->Visible = true;
			return;
		}
		label4->Text = "Ключи успешно получены!";
		label4->ForeColor = Color::Green;
		label4->Show();
		for (int i = 0 ; i<dgvInfo->RowCount - 1;i++)
		{
			String^ input_data = dgvInfo->Rows[i]->Cells[1]->Value->ToString();
			String^ iv = dgvInfo->Rows[i]->Cells[0]->Value->ToString();
			input_data = f.Decrypt(input_data, iv, key1);
			dgvInfo->Rows[i]->Cells[1]->Value = input_data;
			dgvInfo->Rows[i]->Cells[0]->Value = iv;
		}
		
		buttonDecrypt->Enabled = false;
		
	}

private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	timer1_tickCount++;
	if (timer1_tickCount>2)
	{
		timer1->Stop();
		timer1_tickCount = 0;
		for (int i = 0; i < 2; i++)
		{
			label4->Text->Substring(0, label4->Text->Length);
		}
		
	}
	label4->Text += " !";

}
};
}
