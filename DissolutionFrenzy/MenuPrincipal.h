#pragma once
#include "SelectorNivel.h"

namespace DissolutionFrenzy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	/// <summary>
	/// Summary for MenuPrincipal
	/// </summary>
	public ref class MenuPrincipal : public System::Windows::Forms::Form
	{
	private:
		SoundPlayer^ songmenu;
		Bitmap^ logo;
		   Bitmap^ fondomenu;
		Bitmap^ jugadorTitleSprite;
	public:
		MenuPrincipal(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			songmenu = gcnew SoundPlayer("Musica/Menu.wav");
			logo = gcnew Bitmap("Imagenes/Logo.png");
			fondomenu = gcnew Bitmap("Imagenes/BackgroundMenu.png");
			jugadorTitleSprite = gcnew Bitmap("Imagenes/Title.png");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MenuPrincipal()
		{
			if (components)
			{
				delete components;
			}
			delete songmenu;
			delete logo;
			delete fondomenu;
			delete jugadorTitleSprite;
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
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
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MenuPrincipal::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(92, 351);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(294, 58);
			this->button1->TabIndex = 0;
			this->button1->Text = L"----- Empezar -----";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MenuPrincipal::button1_Click);
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(92, 275);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(294, 58);
			this->button2->TabIndex = 1;
			this->button2->Text = L"--- Instrucciones ---";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &MenuPrincipal::button2_Click);
			// 
			// MenuPrincipal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(492, 492);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MenuPrincipal";
			this->Text = L"MenuPrincipal";
			this->Load += gcnew System::EventHandler(this, &MenuPrincipal::MenuPrincipal_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
    private: void uiDraw(BufferedGraphics^ buffer) {

        //buffer->Graphics->DrawImage();

    }
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
        Graphics^ gr = this->CreateGraphics();
        BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
        BufferedGraphics^ buffer = space->Allocate(gr, this->ClientRectangle);

        buffer->Graphics->Clear(Color::White);


		Drawing::Font^ miFuente = gcnew Drawing::Font("Aharoni", 20);

		// // fondo
		Rectangle area = Rectangle(0, 0, fondomenu->Width, fondomenu->Height); //recorte de la imagen
		Rectangle limit = Rectangle(0, 0, gr->VisibleClipBounds.Width, gr->VisibleClipBounds.Height); //X,Y,WIDTH,HEIGHT
		buffer->Graphics->DrawImage(fondomenu, limit, area, GraphicsUnit::Pixel);

		
		// // logo
		area = Rectangle(0, 0, logo->Width, logo->Height); //recorte de la imagen
		limit = Rectangle(12, 24, 300, 80); //X,Y,WIDTH,HEIGHT
		buffer->Graphics->DrawImage(logo, limit, area, GraphicsUnit::Pixel);

		// jugadorsin
		area = Rectangle(0, 0, jugadorTitleSprite->Width, jugadorTitleSprite->Height); //recorte de la imagen
		limit = Rectangle(12, 24 + 55, 300, 160); //X,Y,WIDTH,HEIGHT
		buffer->Graphics->DrawImage(jugadorTitleSprite, limit, area, GraphicsUnit::Pixel);

		Drawing::Font^ miFuente2 = gcnew Drawing::Font("Arial Nova", 10);
		gr->DrawString("Querido Programador: Cuando escribí", miFuente2, Brushes::Black, 50, 80);
		gr->DrawString(" este código solo yo y Dios sabían como", miFuente2, Brushes::Black, 50, 95);
		gr->DrawString("  funcionaba. Ahora, solo Dios sabe ", miFuente2, Brushes::Black, 50, 110);

        uiDraw(buffer);
        // (3) Renderizar Buffer
        buffer->Render(gr);

        // (4) Deleting Memory
        delete buffer;
        delete space;
        delete gr;
	}
	private: System::Void MenuPrincipal_Load(System::Object^ sender, System::EventArgs^ e) {
        songmenu->PlayLooping();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		SelectorNivel^ selniv = gcnew SelectorNivel;
        songmenu->Stop();
		selniv->Show();

	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {

		//soundmenu->Stop();    <---- Descomentar cuando se cree el segundo nivel
	}
	};
}
