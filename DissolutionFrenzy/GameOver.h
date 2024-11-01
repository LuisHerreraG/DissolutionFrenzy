#pragma once
namespace DissolutionFrenzy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for GameOver
	/// </summary>
	public ref class GameOver : public System::Windows::Forms::Form
	{
		private:
            Bitmap^ game_over;
	public:
		GameOver(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
            game_over = gcnew Bitmap("Imagenes/GameOverScreen.png");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameOver()
		{
			if (components)
			{
				delete components;
			}
			delete game_over;
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:

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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(65, 133);
			this->button1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(366, 68);
			this->button1->TabIndex = 0;
			this->button1->Text = L"------ Try Again ------";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &GameOver::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &GameOver::timer1_Tick);
			// 
			// GameOver
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 356);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"GameOver";
			this->Text = L"GameOver";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
        Graphics^ gr = this->CreateGraphics();
        BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
        BufferedGraphics^ buffer = space->Allocate(gr, this->ClientRectangle);

        buffer->Graphics->Clear(Color::White);
        // // logo game over
        Rectangle area = Rectangle(0, 0, game_over->Width, game_over->Height); //recorte de la imagen
        Rectangle limit = Rectangle(0, 0, gr->VisibleClipBounds.Width, gr->VisibleClipBounds.Height); //X,Y,WIDTH,HEIGHT
        buffer->Graphics->DrawImage(game_over, limit, area, GraphicsUnit::Pixel);

        buffer->Render(gr);

        delete buffer;
        delete space;
        delete gr;
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		this->Close();
	}
	};
}
