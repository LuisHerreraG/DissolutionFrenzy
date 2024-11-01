#pragma once
#include "MyForm.h"
#include "Level2.h"

namespace DissolutionFrenzy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SelectorNivel
	/// </summary>
	public ref class SelectorNivel : public System::Windows::Forms::Form
	{
	private:
        SoundPlayer^ songmenu;
        Bitmap^ fondoselect;
		// Imagenes de Niveles
		Bitmap^ level1Showcase;
		Bitmap^ level2Showcase;
	public:
		SelectorNivel(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            songmenu = gcnew SoundPlayer("Musica/Menu.wav");
            fondoselect = gcnew Bitmap("Imagenes/BackgrounSelectorNivel.png");
			level1Showcase = gcnew Bitmap("Imagenes/Level1Showcase.PNG");
			level2Showcase = gcnew Bitmap("Imagenes/Level2Showcase.PNG");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SelectorNivel()
		{
			if (components)
			{
				delete components;
			}
			delete songmenu;
			delete fondoselect;
			// Imagenes de Niveles
			delete level1Showcase;
			delete level2Showcase;
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &SelectorNivel::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 16.2F));
			this->button1->Location = System::Drawing::Point(142, 32);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(216, 59);
			this->button1->TabIndex = 0;
			this->button1->Text = L"--- Nivel 1 ---";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &SelectorNivel::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 16.2F));
			this->button2->Location = System::Drawing::Point(573, 32);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(216, 59);
			this->button2->TabIndex = 1;
			this->button2->Text = L"--- Nivel 2 ---";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &SelectorNivel::button2_Click);
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 16.2F));
			this->button3->Location = System::Drawing::Point(272, 431);
			this->button3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(415, 51);
			this->button3->TabIndex = 2;
			this->button3->Text = L"---------- Atrás ----------";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &SelectorNivel::button3_Click);
			// 
			// SelectorNivel
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(939, 498);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"SelectorNivel";
			this->Text = L"SelectorNivel";
			this->Load += gcnew System::EventHandler(this, &SelectorNivel::SelectorNivel_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ gr = this->CreateGraphics();
		BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = space->Allocate(gr, this->ClientRectangle);
        Rectangle area = Rectangle(0, 0, fondoselect->Width, fondoselect->Height); //recorte de la imagen
        Rectangle limit = Rectangle(0, 0, gr->VisibleClipBounds.Width, gr->VisibleClipBounds.Height); //X,Y,WIDTH,HEIGHT
        buffer->Graphics->DrawImage(fondoselect, limit, area, GraphicsUnit::Pixel);
		Pen^ pen = gcnew Pen(Color::Red, 3);
		buffer->Graphics->DrawRectangle(pen, 30, 70, 270, 180);
		buffer->Graphics->DrawRectangle(pen, 320, 70, 270, 180);

		area = Rectangle(0, 0, level1Showcase->Width, level1Showcase->Height); //recorte de la imagen
		limit = Rectangle(30, 70, 270, 180); //X,Y,WIDTH,HEIGHT
		buffer->Graphics->DrawImage(level1Showcase, limit, area, GraphicsUnit::Pixel);

		area = Rectangle(0, 0, level2Showcase->Width, level2Showcase->Height); //recorte de la imagen
		limit = Rectangle(320, 70, 270, 180); //X,Y,WIDTH,HEIGHT
		buffer->Graphics->DrawImage(level2Showcase, limit, area, GraphicsUnit::Pixel);

		buffer->Render(gr);

		delete buffer;
		delete space;
		delete gr;

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		MyForm^ form = gcnew MyForm();
		form->Show();
		this->Close();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		Level2^ form = gcnew Level2();
		form->Show();
		this->Close();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
        songmenu->PlayLooping();
		this->Close();
	}
	private: System::Void SelectorNivel_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
