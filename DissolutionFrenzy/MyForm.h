#pragma once

#include "Constants.h"
#include "Player.h"
#include "ListaNPCs.h"
#include "ListaBalas.h"
#include "ListaUpgrades.h"
#include "BossArea.h"
#include "GameOver.h"
#include <iostream>
#include <vector>

namespace DissolutionFrenzy {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;
	using namespace std;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		// Game Objects
		Player* jugador;
		ListaAI* aiActivos;
		ListaBalas* balasActivas;
		ListaUpgrades* upgradesActivos;
		AI* jefeReferencia;
		BossArea* areaJefe;
		// Input Holders
		float inputX;
		float inputY;
		int dirY;
		bool jump;
		bool shoot;
		// Time Game
		float time;
		// Boss Game
		bool modoJefe;
		// DS Game
		bool interaccion;
		bool interaccionNerf;
		// Sprites
		// // Jugador
		Bitmap^ playerSprite;
		// // AI
		Bitmap^ robotinSprite;
		Bitmap^ babosinSprite;
		Bitmap^ abejorroSprite;
		Bitmap^ upcSprite;
		Bitmap^ bichoSprite;
		Bitmap^ aranhaSprite;
		Bitmap^ capsulaSprite;
		Bitmap^ wallSprite;
		// // Balas
		Bitmap^ balasJugadorSprite;
		Bitmap^ balasRobotinSprite;
		Bitmap^ balasBabosinSprite;
		Bitmap^ upcBalaSprite;
		// // Upgrade
		Bitmap^ healthUpgradeSprite;
		Bitmap^ resistanceUpgradeSprite;
		Bitmap^ attackUpgradeSprite;
	private: System::Windows::Forms::Button^ button1;
		   // // UI
		Bitmap^ vidaSprite;
		Bitmap^ resistanceSprite;
		Bitmap^ relojSprite;
		Bitmap^ ataqueSprite;
		Bitmap^ winnerSprite;
		// // Background
		Bitmap^ fondo1;
		// // Music
		SoundPlayer^ songlvl1;
		SoundPlayer^ songboss1;
	private: System::Windows::Forms::Label^ lbl_TimeLabel;
	private: System::Windows::Forms::Label^ lbl_Boss;

	private: System::Windows::Forms::ProgressBar^ prgBar_Boss;
	private: System::Windows::Forms::Timer^ timer1;

		   // // Map
		Bitmap^ tileSprite;
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			
			// INICIAR MAPA
			changeMapLevel1();
			// Game Objects
			//jugador = new Player(2*20, 12*20); // ACTUAL BEGIN LOCATION
			jugador = new Player((125 - 40) * 20, 105 * 20); // BOSS LOCATION
			aiActivos = new ListaAI();
			balasActivas = new ListaBalas();
			upgradesActivos = new ListaUpgrades();
			areaJefe = new BossArea(126 - 25 - 1, 113 - 14 - 1, 0, 0);
			// Boss Game
			jefeReferencia = NULL;
			// DS Game
			interaccion = false;
			interaccionNerf = false;
			// Sprites
			playerSprite = gcnew Bitmap("Imagenes/Hero2.0.png");
			tileSprite = gcnew Bitmap("Imagenes/Level1Tile.jpg");
			robotinSprite = gcnew Bitmap("Imagenes/RobotinComplete.png");
			babosinSprite = gcnew Bitmap("Imagenes/babosin.png");
			abejorroSprite = gcnew Bitmap("Imagenes/BigBeeComplete.png");
			aranhaSprite = gcnew Bitmap("Imagenes/aranha.png");
			bichoSprite = gcnew Bitmap("Imagenes/ELBICHOComplete.png");
			upcSprite = gcnew Bitmap("Imagenes/UPC.png");
			capsulaSprite = gcnew Bitmap("Imagenes/Capsule.png");
			// // Balas
			balasJugadorSprite = gcnew Bitmap("Imagenes/DisparoJugador.png");
			balasRobotinSprite = gcnew Bitmap("Imagenes/RobotinBala.png");
			balasBabosinSprite = gcnew Bitmap("Imagenes/BabosinBala.png");
			wallSprite = gcnew Bitmap("Imagenes/Cuboid.png");
			upcBalaSprite = gcnew Bitmap("Imagenes/UPCBala.png");
			// // Upgrade
			healthUpgradeSprite = gcnew Bitmap("Imagenes/HealthUpgrade.png");
			resistanceUpgradeSprite = gcnew Bitmap("Imagenes/ShieldUpgrade.png");
			attackUpgradeSprite = gcnew Bitmap("Imagenes/AttackUpgrade.png");
			// // UI
			vidaSprite = gcnew Bitmap("Imagenes/HeartMana.png");
			resistanceSprite = gcnew Bitmap("Imagenes/Mana.png");
			relojSprite = gcnew Bitmap("Imagenes/HealthUpgrade.png");
			ataqueSprite = gcnew Bitmap("Imagenes/Attack.png");
			winnerSprite = gcnew Bitmap("Imagenes/WinnerLevel1.png");
			// // Background
			fondo1 = gcnew Bitmap("Imagenes/BackgroundLevel1.png");
			// // Music
			songlvl1 = gcnew SoundPlayer("Musica/Nivel1.wav");
			songboss1 = gcnew SoundPlayer("Musica/Abejorro.wav");
			// Input Holders
			inputX = 0;
			inputY = 0;
			dirY = 0;
			jump = false;
			shoot = false;
			// Time Game
			time = 500.0;
			// Boss Game
			modoJefe = false;
			// Spawning on Map
			//aiActivos->addRobotin(15, 12, 11, 5);
			//aiActivos->addBabasin(20, 5);
			//aiActivos->addBabasin(20, 20);
			//upgradesActivos->addItem(5, 5, AttackBoost);
			//upgradesActivos->addItem(10, 10, HealthBoost);
			//upgradesActivos->addItem(2, 7, ResistanceBoost);


			//aiActivos->addMedico1(8, 8);
			//aiActivos->addMedico1(15, 4);
			//upgradesActivos->addItem(12, 12, AttackBoost);
			//

			generateAICharacters();



			upgradesActivos->addItem(75, 67, HealthBoost);
			upgradesActivos->addItem(55, 50, HealthBoost);
			upgradesActivos->addItem(26, 60, HealthBoost);
			upgradesActivos->addItem(123, 27, HealthBoost);
			upgradesActivos->addItem(34, 2, HealthBoost);
			upgradesActivos->addItem(65, 35, HealthBoost);
			upgradesActivos->addItem(75, 48, HealthBoost);
			upgradesActivos->addItem(100, 44, HealthBoost);
			upgradesActivos->addItem(48, 103, HealthBoost);

			upgradesActivos->addItem(120, 30, AttackBoost);
			upgradesActivos->addItem(29, 60, AttackBoost);
			upgradesActivos->addItem(5, 4, AttackBoost);
			upgradesActivos->addItem(89, 35, AttackBoost);
			upgradesActivos->addItem(115, 35, AttackBoost);
			upgradesActivos->addItem(75, 5, AttackBoost);
			upgradesActivos->addItem(67, 44, AttackBoost);
			upgradesActivos->addItem(123, 62, AttackBoost);
			upgradesActivos->addItem(69, 87, AttackBoost);

			upgradesActivos->addItem(122, 55, ResistanceBoost);
			upgradesActivos->addItem(40, 8, ResistanceBoost);
			upgradesActivos->addItem(100, 34, ResistanceBoost);
			upgradesActivos->addItem(68, 2, ResistanceBoost);
			upgradesActivos->addItem(55, 50, ResistanceBoost);
			upgradesActivos->addItem(13, 97, ResistanceBoost);
			upgradesActivos->addItem(110, 72, ResistanceBoost);
			upgradesActivos->addItem(96, 86, ResistanceBoost);
			upgradesActivos->addItem(94, 3, ResistanceBoost);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			// Game Objects
			delete jugador;
			delete aiActivos;
			delete balasActivas;
			delete upgradesActivos;
			delete jefeReferencia;
			delete areaJefe;
			// Sprites
			// // Jugador
			delete playerSprite;
			// // AI
			delete robotinSprite;
			delete babosinSprite;
			delete abejorroSprite;
			delete upcSprite;
			delete bichoSprite;
			delete aranhaSprite;
			delete capsulaSprite;
			delete wallSprite;
			// // Balas
			delete balasJugadorSprite;
			delete balasRobotinSprite;
			delete balasBabosinSprite;
			delete upcBalaSprite;
			// // Upgrade
			delete healthUpgradeSprite;
			delete resistanceUpgradeSprite;
			delete attackUpgradeSprite;
			   // // UI
			delete vidaSprite;
			delete resistanceSprite;
			delete relojSprite;
			delete ataqueSprite;
			delete winnerSprite;
			   // // Background
			delete fondo1;
			   // // Music
			delete songlvl1;
			delete songboss1;
			   delete tileSprite;
		}
	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::Label^ debugLabel;

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
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->debugLabel = (gcnew System::Windows::Forms::Label());
			this->lbl_TimeLabel = (gcnew System::Windows::Forms::Label());
			this->lbl_Boss = (gcnew System::Windows::Forms::Label());
			this->prgBar_Boss = (gcnew System::Windows::Forms::ProgressBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 50;
			this->timer->Tick += gcnew System::EventHandler(this, &MyForm::timer_Tick);
			// 
			// debugLabel
			// 
			this->debugLabel->AutoSize = true;
			this->debugLabel->Location = System::Drawing::Point(12, 9);
			this->debugLabel->Name = L"debugLabel";
			this->debugLabel->Size = System::Drawing::Size(51, 20);
			this->debugLabel->TabIndex = 0;
			this->debugLabel->Text = L"label1";
			this->debugLabel->Visible = false;
			// 
			// lbl_TimeLabel
			// 
			this->lbl_TimeLabel->AutoSize = true;
			this->lbl_TimeLabel->BackColor = System::Drawing::Color::LightSkyBlue;
			this->lbl_TimeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbl_TimeLabel->ForeColor = System::Drawing::SystemColors::ControlText;
			this->lbl_TimeLabel->Location = System::Drawing::Point(712, 9);
			this->lbl_TimeLabel->Name = L"lbl_TimeLabel";
			this->lbl_TimeLabel->Size = System::Drawing::Size(51, 20);
			this->lbl_TimeLabel->TabIndex = 1;
			this->lbl_TimeLabel->Text = L"label1";
			this->lbl_TimeLabel->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// lbl_Boss
			// 
			this->lbl_Boss->AutoSize = true;
			this->lbl_Boss->Location = System::Drawing::Point(328, 9);
			this->lbl_Boss->Name = L"lbl_Boss";
			this->lbl_Boss->Size = System::Drawing::Size(256, 20);
			this->lbl_Boss->TabIndex = 2;
			this->lbl_Boss->Text = L"Ravenous Bumblebee, The Cursed";
			this->lbl_Boss->Visible = false;
			// 
			// prgBar_Boss
			// 
			this->prgBar_Boss->Location = System::Drawing::Point(588, 7);
			this->prgBar_Boss->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->prgBar_Boss->Name = L"prgBar_Boss";
			this->prgBar_Boss->Size = System::Drawing::Size(100, 22);
			this->prgBar_Boss->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->prgBar_Boss->TabIndex = 3;
			this->prgBar_Boss->Value = 100;
			this->prgBar_Boss->Visible = false;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(618, 403);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(145, 47);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Volver al Menú";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(775, 462);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->prgBar_Boss);
			this->Controls->Add(this->lbl_Boss);
			this->Controls->Add(this->lbl_TimeLabel);
			this->Controls->Add(this->debugLabel);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::KeyDowned);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::KeyPressed);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::KeyUpped);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MouseDowned);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void generateAICharacters() {

		aiActivos->addStation(10, 11);
		aiActivos->addStation(51, 53);
		aiActivos->addStation(31, 67);
		aiActivos->addStation(30, 39);
		aiActivos->addStation(102, 53);
		aiActivos->addStation(106, 34);
		aiActivos->addStation(122, 67); //No disponible en nivel 2, ante la pregunta de "por qué?", pues, es que ahí spawneas xd
		aiActivos->addStation(47, 95);
		aiActivos->addStation(4, 67);
		aiActivos->addStation(122, 95);
		aiActivos->addStation(33, 5);


		aiActivos->addRobotin(15, 6, 2, 3);
		aiActivos->addRobotin(32, 20, 0, 4);  //Se mueve a la derecha 1 menos
		aiActivos->addRobotin(61, 26, 0, 11);
		aiActivos->addRobotin(29, 35, 0, 3);
		aiActivos->addRobotin(38, 34, 0, 5);
		aiActivos->addRobotin(73, 32, 0, 6);
		aiActivos->addRobotin(96, 54, 22, 0);
		aiActivos->addRobotin(48, 61, 0, 3);
		aiActivos->addRobotin(87, 48, 0, 3);
		aiActivos->addRobotin(62, 76, 0, 3);
		aiActivos->addRobotin(93, 72, 0, 5);
		aiActivos->addRobotin(58, 96, 0, 32);
		aiActivos->addRobotin(90, 96, 32, 0);
		aiActivos->addRobotin(72, 105, 0, 5);
		aiActivos->addRobotin(45, 2, 0, 4);
		aiActivos->addRobotin(87, 6, 0, 5);
		aiActivos->addRobotin(112, 6, 0, 4);
		aiActivos->addRobotin(116, 20, 5, 0);
		aiActivos->addRobotin(91, 20, 5, 0);
		aiActivos->addRobotin(30, 20, 0, 6);
		aiActivos->addRobotin(6, 22, 0, 8);
		aiActivos->addRobotin(8, 17, 0, 4);
		aiActivos->addRobotin(38, 34, 0, 4);
		aiActivos->addRobotin(73, 32, 0, 6);
		aiActivos->addRobotin(32, 77, 0, 10);
		aiActivos->addRobotin(101, 59, 0, 3);
		aiActivos->addRobotin(111, 62, 0, 5);
		aiActivos->addRobotin(113, 48, 0, 3);
		aiActivos->addRobotin(37, 96, 3, 8);
		aiActivos->addRobotin(6, 91, 0, 6);
		aiActivos->addRobotin(7, 77, 0, 10);
		aiActivos->addRobotin(8, 64, 0, 8);
		aiActivos->addRobotin(26, 54, 0, 22); //No esta en nivel 2, boss zone
		aiActivos->addRobotin(59, 45, 0, 2);
		aiActivos->addRobotin(88, 62, 0, 3);
		aiActivos->addRobotin(87, 76, 0, 3);
		aiActivos->addRobotin(113, 76, 0, 3);
		aiActivos->addRobotin(98, 89, 0, 3);
		aiActivos->addRobotin(66, 5, 0, 3);



		aiActivos->addBabasin(30, 1);
		aiActivos->addBabasin(40, 1);
		aiActivos->addBabasin(65, 1);
		aiActivos->addBabasin(60, 15);
		aiActivos->addBabasin(35, 29);
		aiActivos->addBabasin(95, 29);
		aiActivos->addBabasin(111, 43);
		aiActivos->addBabasin(60, 48);
		aiActivos->addBabasin(27, 57);
		aiActivos->addBabasin(30, 57);
		aiActivos->addBabasin(119, 32);
		aiActivos->addBabasin(45, 60);
		aiActivos->addBabasin(70, 61);
		aiActivos->addBabasin(84, 85);
		aiActivos->addBabasin(81, 1);
		aiActivos->addBabasin(109, 1);
		aiActivos->addBabasin(103, 16);
		aiActivos->addBabasin(15, 15);
		aiActivos->addBabasin(5, 15);
		aiActivos->addBabasin(60, 29);
		aiActivos->addBabasin(85, 29);
		aiActivos->addBabasin(79, 43);
		aiActivos->addBabasin(31, 71);
		aiActivos->addBabasin(44, 71);
		aiActivos->addBabasin(122, 50);
		aiActivos->addBabasin(99, 43);
		aiActivos->addBabasin(101, 43);
		aiActivos->addBabasin(47, 85);
		aiActivos->addBabasin(18, 85);
		aiActivos->addBabasin(19, 57);
		aiActivos->addBabasin(2, 57);
		aiActivos->addBabasin(30, 43); //No esta en nivel 2, boss zone
		aiActivos->addBabasin(43, 43); //No esta en nivel 2, boss zone
		aiActivos->addBabasin(77, 71);
		aiActivos->addBabasin(107, 85);
		aiActivos->addBabasin(81, 99);
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		this->songlvl1->PlayLooping();
		jugador->storeGameTick(timer->Interval);
	}
	private: void modoJefeBeginPlay() {
		this->songlvl1->Stop();
		this->songboss1->PlayLooping();
		modoJefe = true;
		aiActivos->deleteAll();
		aiActivos->addBumblebee(126 - 1 - 6, 113 - 1 - 10);
		jefeReferencia = aiActivos->compound[0];
		lbl_Boss->Visible = true;
		prgBar_Boss->Visible = true;
	}
	private: void modoJefeFinalization() {
		this->songboss1->Stop();
		timer->Enabled = false;
		aiActivos->deadAIsRemoval();
		button1->Visible = true;
		prgBar_Boss->Visible = false;
		lbl_Boss->Visible = false;
		lbl_TimeLabel->Visible = false;

		Graphics^ gr = this->CreateGraphics();

		Rectangle area = Rectangle(0, 0, winnerSprite->Width, winnerSprite->Height); //recorte de la imagen
		Rectangle limit = Rectangle(0, 0, gr->VisibleClipBounds.Width, gr->VisibleClipBounds.Height); //X,Y,WIDTH,HEIGHT
		gr->DrawImage(winnerSprite, limit, area, GraphicsUnit::Pixel);

		delete gr;
	}
	private: void gameOver() {
		songlvl1->Stop();
		songboss1->Stop();

		GameOver^ gameOverForm = gcnew GameOver();
		gameOverForm->Show();
		timer->Enabled = false;
		this->Close();
	}
	private: void Winner() {

	}
	private: void healthStationEvent() {
		aiActivos->deleteAll();
		generateAICharacters();
		jugador->setHealth(jugador->getMaxHealth());
		interaccion = false;
		interaccionNerf = true;
	}
	private: void uiDraw(BufferedGraphics^ buffer) {
		
		//buffer->Graphics->DrawImage();
		
		// Health
		jugador->getHealth();
		jugador->getMaxHealth();
		if (jugador->getMaxHealth() <= 30) {
			for (int i = 0; i < jugador->getMaxHealth(); i += 2) {
				if (jugador->getHealth() - i > 0) {
					Rectangle area = Rectangle(0, 0, vidaSprite->Width / 3, vidaSprite->Height); //recorte de la imagen
					Rectangle limit = Rectangle(12 + 12 * (i / 2), 12, 15, 10); //X,Y,WIDTH,HEIGHT
					buffer->Graphics->DrawImage(vidaSprite, limit, area, GraphicsUnit::Pixel);
				}
				else {
					Rectangle area = Rectangle(2 * vidaSprite->Width / 3, 0, vidaSprite->Width / 3, vidaSprite->Height); //recorte de la imagen
					Rectangle limit = Rectangle(12 + 12 * (i / 2), 12, 15, 10); //X,Y,WIDTH,HEIGHT
					buffer->Graphics->DrawImage(vidaSprite, limit, area, GraphicsUnit::Pixel);
				}
			}
		}
		else {
			Rectangle area = Rectangle(0, 0, vidaSprite->Width / 3, vidaSprite->Height); //recorte de la imagen
			Rectangle limit = Rectangle(12, 12, 15, 10); //X,Y,WIDTH,HEIGHT
			buffer->Graphics->DrawImage(vidaSprite, limit, area, GraphicsUnit::Pixel);
			RectangleF rect = Rectangle(12 + 15 + 2, 12, 28 + 10, 10);
			buffer->Graphics->FillRectangle(Brushes::White, rect);
			buffer->Graphics->DrawString("" + jugador->getHealth() + "/" + jugador->getMaxHealth(), gcnew System::Drawing::Font("Arial", 7), Brushes::Black, rect);
		}

		// Resistance
		jugador->getResistance();
		if (jugador->getResistance() <= 30) {
			for (int i = 0; i < jugador->getResistance(); i += 2) {
					Rectangle area = Rectangle(0, 0, resistanceSprite->Width, resistanceSprite->Height); //recorte de la imagen
					Rectangle limit = Rectangle(12 + 12 * (i / 2), 24, 15, 10); //X,Y,WIDTH,HEIGHT
					buffer->Graphics->DrawImage(resistanceSprite, limit, area, GraphicsUnit::Pixel);
			}
		}
		else {
			Rectangle area = Rectangle(0, 0, resistanceSprite->Width, resistanceSprite->Height); //recorte de la imagen
			Rectangle limit = Rectangle(12, 24, 15, 10); //X,Y,WIDTH,HEIGHT
			buffer->Graphics->DrawImage(resistanceSprite, limit, area, GraphicsUnit::Pixel);
			RectangleF rect = Rectangle(12 + 15 + 2, 24, 14 + 10, 10);
			buffer->Graphics->FillRectangle(Brushes::White, rect);
			buffer->Graphics->DrawString("" + jugador->getResistance(), gcnew System::Drawing::Font("Arial", 7), Brushes::Black, rect);
		}

		// Attack
		jugador->getAttack();
		if (jugador->getAttack() <= 30) {
			for (int i = 0; i < jugador->getAttack(); i += 2) {
				Rectangle area = Rectangle(0, 0, ataqueSprite->Width, ataqueSprite->Height); //recorte de la imagen
				Rectangle limit = Rectangle(12 + 12 * (i / 2), 36, 15, 10); //X,Y,WIDTH,HEIGHT
				buffer->Graphics->DrawImage(ataqueSprite, limit, area, GraphicsUnit::Pixel);
			}
		}
		else {
			Rectangle area = Rectangle(0, 0, ataqueSprite->Width, ataqueSprite->Height); //recorte de la imagen
			Rectangle limit = Rectangle(12, 36, 15, 10); //X,Y,WIDTH,HEIGHT
			buffer->Graphics->DrawImage(ataqueSprite, limit, area, GraphicsUnit::Pixel);
			RectangleF rect = Rectangle(12 + 15 + 2, 36, 14 + 10, 10);
			buffer->Graphics->FillRectangle(Brushes::White, rect);
			buffer->Graphics->DrawString("" + jugador->getAttack(), gcnew System::Drawing::Font("Arial", 7), Brushes::Black, rect);
		}
		
		// Time
		time;

		// Boss

	}
	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		// (0) Setup
		Graphics^ gr = this->CreateGraphics();
		BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = space->Allocate(gr, this->ClientRectangle);

		// (1) Clear Screen
		buffer->Graphics->Clear(Color::White);

		// (2) Movement and Object Drawing
		// Time Timer
		if (!modoJefe) time += -timer->Interval / 1000.0;
		// Reset Velocity -> Resetear la velocidad para ir con calculo querido
		jugador->cancelVelocity();
		jugador->cancelInputVelocity();
		// Input -> Obtener la velocidad teorica del jugador
		// // Jump
		jugador->jump(jump);
		if (jump == true) jump = false;
		// // Movement Input
		jugador->gravity();
		jugador->movementInput(inputX, 0);
		// // Shoot
		jugador->shoot(shoot, inputX, dirY, balasActivas);
		if (shoot == true) shoot = false;
		// AI Input -> Obtener velocidad teorica de los AI
		aiActivos->todosAIMove(jugador, modoJefe, areaJefe->getBlockX());
		balasActivas->createAIShoots(aiActivos);
		// Timers -> Actualiza los timers de los objetos y el juego
		jugador->timers();
		// Combine Velocity -> Combina las velocidades para encontrar la velocidad teorica total
		jugador->combineVelocity();
		// Cap Velocity -> Asegura que la velocidad se encuentre en el rango sin errores
		jugador->capVelocity();
		// Colisiones -> Alteracion de Velocidad para no moverse en espacios tomados
		jugador->mapCollides();
		jugador->borderCollides();
		aiActivos->solvingCollision(jugador);
		balasActivas->checkCollision(jugador, aiActivos, modoJefe, areaJefe->getBlockX());
		upgradesActivos->collisionPlayer(jugador);
		if (modoJefe && jefeReferencia->getHealth() < 0) jefeReferencia->setHealth(0);
		// Check Boss Area -> Chequear si se ha llegado a la base del Jefe y empieza el modo Jefe
		if (aiActivos->interaccionEstacionJugador(interaccion, jugador)) healthStationEvent();
		if (!modoJefe && areaJefe->possiblyCollides(jugador)) modoJefeBeginPlay();
		if (modoJefe) prgBar_Boss->Value = int(float(jefeReferencia->getHealth()) / jefeReferencia->getMaxHealth() * 100);
		// Mover -> Con la velocidad correcta, agregarla a la posicion
		balasActivas->todosUseVelocity();
		jugador->useVelocity();
		aiActivos->todosUseVelocity();
		// Dibujar -> Graficar los objetos ya colocados correctamente

		Rectangle area = Rectangle(0, 0, fondo1->Width, fondo1->Height-600); //recorte de la imagen
		Rectangle limit = Rectangle(0, 0, gr->VisibleClipBounds.Width, gr->VisibleClipBounds.Height); //X,Y,WIDTH,HEIGHT
		buffer->Graphics->DrawImage(fondo1, limit, area, GraphicsUnit::Pixel);

		drawMap(buffer, jugador->getX(), jugador->getY(), tileSprite, modoJefe, areaJefe->getBlockX());
		balasActivas->todosDraw(buffer, jugador, modoJefe, areaJefe->getBlockX(), balasJugadorSprite, balasRobotinSprite, balasBabosinSprite, wallSprite, upcBalaSprite);
		aiActivos->todosDraw(buffer, jugador, modoJefe, areaJefe->getBlockX(), robotinSprite, babosinSprite, abejorroSprite, aranhaSprite, bichoSprite, upcSprite, capsulaSprite);
		jugador->draw(buffer, playerSprite, modoJefe, areaJefe->getBlockX(), areaJefe->getBlockY());
		upgradesActivos->todosDraw(buffer, jugador, healthUpgradeSprite, resistanceUpgradeSprite, attackUpgradeSprite);
		uiDraw(buffer);

		// (3) Renderizar Buffer
		buffer->Render(gr);

		// (4) Deleting Memory
		delete buffer;
		delete space;
		delete gr;

		// Deaths -> En caso de que alguien muera, se ve aqui (solo funciona después de los delete)
		if (jugador->getHealth() <= 0) gameOver();
		if (modoJefe) prgBar_Boss->Value = int(float(jefeReferencia->getHealth()) / jefeReferencia->getMaxHealth() * 100);
		if (modoJefe && aiActivos->deadBossCheck()) modoJefeFinalization(); // Es importante que venga antes de deadAIsRemoval
		aiActivos->deadAIsRemoval();

		// Con el try again ->

		// (5) Debug
		// // Left UI
		debugLabel->Text = "" + jugador->getHealth() + "/" + jugador->getMaxHealth() + "\n" +
								jugador->getAttack() + "\n" +
								jugador->getResistance() + "\n" +
								areaJefe->possiblyCollides(jugador) + "\n" +
								interaccion
			;

		// // Right UI
		lbl_TimeLabel->Text = "" + Int16(time);

		// (N) Finalization
		inputY = 0;
	}
	private: System::Void KeyPressed(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		Random^ r = gcnew Random();

		switch (tolower(e->KeyChar)) {
		case 'a':
			break;
		case 'd':
			break;
		case 'w':
			break;
		case 's':
			break;
		}

		delete r;
	}

	private: System::Void KeyDowned(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::A:
			inputX = -1;
			break;
		case Keys::D:
			inputX = 1;
			break;
		case Keys::W:
			dirY = -1;
			break;
		case Keys::E:
			if (!interaccionNerf) interaccion = true;
			break;
		case Keys::Space:
			if (jugador->isInGround())
				jump = true;
			else
				jump = false;
			break;
		}
	}
	private: System::Void KeyUpped(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::A:
			inputX = 0;
			break;
		case Keys::D:
			inputX = 0;
			break;
		case Keys::W:
			dirY = 0;
			break;
		case Keys::E:
			interaccion = false;
			interaccionNerf = false;
			break;
		case Keys::Space:
			jump = false;
			break;
		}
	}
	private: System::Void MouseDowned(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		shoot = true;
		/*
		switch (e->Button) {
		case ::MouseButtons::Left:
			shoot = true;
			break;
		}
		*/
	}
    private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	
    }
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
