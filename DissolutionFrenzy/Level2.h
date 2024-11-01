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

	/// <summary>
	/// Summary for Level2
	/// </summary>
	public ref class Level2 : public System::Windows::Forms::Form
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
		// // Balas
		Bitmap^ balasJugadorSprite;
		Bitmap^ balasRobotinSprite;
		Bitmap^ balasBabosinSprite;
		Bitmap^ wallSprite;
		Bitmap^ upcBalaSprite;
		// // Upgrade
		Bitmap^ healthUpgradeSprite;
		Bitmap^ resistanceUpgradeSprite;
		Bitmap^ attackUpgradeSprite;
		// // UI
		Bitmap^ vidaSprite;
		Bitmap^ resistanceSprite;
		Bitmap^ relojSprite;
		Bitmap^ ataqueSprite;
		Bitmap^ winnerSprite;
		// // Background
		Bitmap^ fondo2;
		// // Music
		SoundPlayer^ songlvl2;
		SoundPlayer^ songboss2;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::Label^ debugLabel;
	private: System::Windows::Forms::Label^ lbl_Boss;
	private: System::Windows::Forms::ProgressBar^ prgBar_Boss;
	private: System::Windows::Forms::Label^ lbl_TimeLabel;


		   // // Map
		Bitmap^ tileSprite;
	public:
		Level2(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			// INITIALIZE MAP
			changeMapLevel2();
			// Game Objects
			//jugador = new Player(77 * 20, (14 * 1 + 12) * 20); // ACTUAL BEGIN LOCATION
			jugador = new Player(4 * 20, (14 * 3 + 5) * 20); // BOSS LOCATION
			aiActivos = new ListaAI();
			balasActivas = new ListaBalas();
			upgradesActivos = new ListaUpgrades();
			areaJefe = new BossArea(25, 14*3, 0, 0);
			// Boss Game
			jefeReferencia = NULL;
			// DS Game
			interaccion = false;
			interaccionNerf = false;
			// Sprites
			playerSprite = gcnew Bitmap("Imagenes/Hero2.0.png");
			tileSprite = gcnew Bitmap("Imagenes/Level2Tile.png");
			robotinSprite = gcnew Bitmap("Imagenes/RobotinComplete.png");
			babosinSprite = gcnew Bitmap("Imagenes/babosin.png");
			abejorroSprite = gcnew Bitmap("Imagenes/BigBeeComplete.png");
			aranhaSprite = gcnew Bitmap("Imagenes/aranha.png");
			bichoSprite = gcnew Bitmap("Imagenes/ELBICHOComplete.png");
			upcSprite = gcnew Bitmap("Imagenes/UPC.png");
			capsulaSprite = gcnew Bitmap("Imagenes/Capsule.png");
			wallSprite = gcnew Bitmap("Imagenes/Cuboid.png");
			upcBalaSprite = gcnew Bitmap("Imagenes/UPCBala.png");
			// // Balas
			balasJugadorSprite = gcnew Bitmap("Imagenes/DisparoJugador.png");
			balasRobotinSprite = gcnew Bitmap("Imagenes/RobotinBala.png");
			balasBabosinSprite = gcnew Bitmap("Imagenes/BabosinBala.png");
			// // Upgrade
			healthUpgradeSprite = gcnew Bitmap("Imagenes/HealthUpgrade.png");
			resistanceUpgradeSprite = gcnew Bitmap("Imagenes/ShieldUpgrade.png");
			attackUpgradeSprite = gcnew Bitmap("Imagenes/AttackUpgrade.png");
			// // UI
			vidaSprite = gcnew Bitmap("Imagenes/HeartMana.png");
			resistanceSprite = gcnew Bitmap("Imagenes/Mana.png");
			relojSprite = gcnew Bitmap("Imagenes/HealthUpgrade.png");
			ataqueSprite = gcnew Bitmap("Imagenes/Attack.png");
			winnerSprite = gcnew Bitmap("Imagenes/WinnerLevel2.png");
			// // Background
			fondo2 = gcnew Bitmap("Imagenes/BackgroundLevel2.png");
			// // Music
			songlvl2 = gcnew SoundPlayer("Musica/Nivel2.wav");
			songboss2 = gcnew SoundPlayer("Musica/UPC.wav");
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
			upgradesActivos->addItem(69, 73, ResistanceBoost);


		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Level2()
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
			// // Balas
			delete balasJugadorSprite;
			delete balasRobotinSprite;
			delete balasBabosinSprite;
			delete wallSprite;
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
			delete fondo2;
			// // Music
			delete songlvl2;
			delete songboss2;
		}
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
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->debugLabel = (gcnew System::Windows::Forms::Label());
			this->lbl_Boss = (gcnew System::Windows::Forms::Label());
			this->prgBar_Boss = (gcnew System::Windows::Forms::ProgressBar());
			this->lbl_TimeLabel = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 50;
			this->timer->Tick += gcnew System::EventHandler(this, &Level2::timer_Tick);
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
			// lbl_Boss
			// 
			this->lbl_Boss->AutoSize = true;
			this->lbl_Boss->Location = System::Drawing::Point(339, 8);
			this->lbl_Boss->Name = L"lbl_Boss";
			this->lbl_Boss->Size = System::Drawing::Size(54, 20);
			this->lbl_Boss->TabIndex = 1;
			this->lbl_Boss->Text = L"U.P.C.";
			this->lbl_Boss->Visible = false;
			this->lbl_Boss->Click += gcnew System::EventHandler(this, &Level2::lbl_Boss_Click);
			// 
			// prgBar_Boss
			// 
			this->prgBar_Boss->Location = System::Drawing::Point(399, 6);
			this->prgBar_Boss->Name = L"prgBar_Boss";
			this->prgBar_Boss->Size = System::Drawing::Size(100, 23);
			this->prgBar_Boss->TabIndex = 2;
			this->prgBar_Boss->Value = 100;
			this->prgBar_Boss->Visible = false;
			this->prgBar_Boss->Click += gcnew System::EventHandler(this, &Level2::prgBar_Boss_Click);
			// 
			// lbl_TimeLabel
			// 
			this->lbl_TimeLabel->AutoSize = true;
			this->lbl_TimeLabel->BackColor = System::Drawing::Color::LightCoral;
			this->lbl_TimeLabel->Location = System::Drawing::Point(712, 9);
			this->lbl_TimeLabel->Name = L"lbl_TimeLabel";
			this->lbl_TimeLabel->Size = System::Drawing::Size(51, 20);
			this->lbl_TimeLabel->TabIndex = 3;
			this->lbl_TimeLabel->Text = L"label1";
			this->lbl_TimeLabel->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(232, 387);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(184, 63);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Volver al Men�";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			this->button1->Click += gcnew System::EventHandler(this, &Level2::button1_Click);
			// 
			// Level2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(775, 462);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->lbl_TimeLabel);
			this->Controls->Add(this->prgBar_Boss);
			this->Controls->Add(this->lbl_Boss);
			this->Controls->Add(this->debugLabel);
			this->Name = L"Level2";
			this->Text = L"Level2";
			this->Load += gcnew System::EventHandler(this, &Level2::Level2_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Level2::KeyDowned);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Level2::KeyPressed);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Level2::KeyUpped);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Level2::MouseDowned);
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
		aiActivos->addStation(47, 95);
		aiActivos->addStation(4, 67);
		aiActivos->addStation(122, 95);
		aiActivos->addStation(33, 5);


		aiActivos->addRobotin(15, 6, 2, 3);
		aiActivos->addRobotin(61, 26, 0, 11);
		aiActivos->addBicho(29, 34, 0, 3);
		aiActivos->addRobotin(38, 34, 0, 5);
		aiActivos->addRobotin(48, 61, 0, 3);
		aiActivos->addRobotin(93, 72, 0, 5);
		aiActivos->addRobotin(90, 96, 32, 0);
		aiActivos->addRobotin(45, 2, 0, 4);
		aiActivos->addRobotin(112, 6, 0, 4);
		aiActivos->addRobotin(116, 20, 5, 0);
		aiActivos->addRobotin(30, 20, 0, 6);
		aiActivos->addBicho(6, 20, 0, 8);
		aiActivos->addBicho(8, 15, 0, 4);
		aiActivos->addRobotin(38, 34, 0, 4);
		aiActivos->addBicho(73, 28, 0, 6);
		aiActivos->addRobotin(101, 59, 0, 3);
		aiActivos->addRobotin(111, 62, 0, 5);
		aiActivos->addRobotin(37, 96, 3, 8);
		aiActivos->addBicho(8, 89, 0, 11);
		aiActivos->addRobotin(7, 77, 0, 10);
		aiActivos->addRobotin(8, 64, 0, 8);
		aiActivos->addBicho(88, 58, 0, 3);
		aiActivos->addRobotin(87, 76, 0, 3);
		aiActivos->addRobotin(66, 5, 0, 3);

		aiActivos->addBicho(32, 18, 9, 9);
		aiActivos->addBicho(73, 30, 3, 8);
		aiActivos->addBicho(113, 74, 2, 6);
		aiActivos->addBicho(99, 88, 0, 8);
		aiActivos->addBicho(91, 18, 8, 0);
		aiActivos->addBicho(87, 5, 4, 3);
		aiActivos->addBicho(59, 39, 5, 10);
		aiActivos->addBicho(113, 46, 3, 1);
		aiActivos->addBicho(87, 46, 5, 3);
		aiActivos->addBicho(96, 53, 25, 0);
		aiActivos->addBicho(32, 76, 3, 13);
		aiActivos->addBicho(62, 75, 4, 3);
		aiActivos->addBicho(98, 95, 0, 15);
		aiActivos->addBicho(72, 103, 2, 10);
		aiActivos->addBicho(102, 107, 0, 19);
		aiActivos->addBicho(121, 104, 18, 0);



		aiActivos->addAranha(30, 1); // ARANHA: SIEMPRE con 0.5 menos del bloque donde lo quieras poner
		aiActivos->addBabasin(40, 1);
		aiActivos->addBabasin(65, 1);
		aiActivos->addAranha(60, 15);
		aiActivos->addBabasin(35, 29);
		aiActivos->addAranha(95, 29);
		aiActivos->addAranha(111, 43);
		aiActivos->addBabasin(60, 48);
		aiActivos->addAranha(27, 57);
		aiActivos->addAranha(30, 57);
		aiActivos->addBabasin(119, 32);
		aiActivos->addAranha(45, 60);
		aiActivos->addBabasin(70, 61);
		aiActivos->addAranha(84, 85);
		aiActivos->addAranha(81, 1);
		aiActivos->addBabasin(109, 1);
		aiActivos->addAranha(103, 16);
		aiActivos->addAranha(15, 15);
		aiActivos->addAranha(5, 15);
		aiActivos->addBabasin(60, 29);
		aiActivos->addAranha(85, 29);
		aiActivos->addBabasin(79, 43);
		aiActivos->addAranha(31, 71);
		aiActivos->addAranha(44, 71);
		aiActivos->addAranha(122, 50);
		aiActivos->addAranha(99, 43);
		aiActivos->addBabasin(101, 43);
		aiActivos->addAranha(47, 85);
		aiActivos->addBabasin(18, 85);
		aiActivos->addAranha(19, 57);
		aiActivos->addBabasin(2, 57);
		aiActivos->addAranha(77, 71);
		aiActivos->addBabasin(107, 85);
		aiActivos->addAranha(81, 99);

	}
	private: System::Void Level2_Load(System::Object^ sender, System::EventArgs^ e) {
		jugador->storeGameTick(timer->Interval);
		songlvl2->PlayLooping();
	}
	private: void modoJefeBeginPlay() {
		songlvl2->Stop();
		songboss2->PlayLooping();
		modoJefe = true;
		aiActivos->deleteAll();
		aiActivos->addUPC(25 + 13, 14 * 3 + 7);
		jefeReferencia = aiActivos->compound[0];
		lbl_Boss->Visible = true;
		prgBar_Boss->Visible = true;
	}
	private: void modoJefeFinalization() {
		songboss2->Stop();
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
		songlvl2->Stop();
		songboss2->Stop();

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
		//aquiiiiiii
		Rectangle area = Rectangle(0, 0, fondo2->Width, fondo2->Height-300); //recorte de la imagen
		Rectangle limit = Rectangle(0, 0, gr->VisibleClipBounds.Width, gr->VisibleClipBounds.Height); //X,Y,WIDTH,HEIGHT
		buffer->Graphics->DrawImage(fondo2, limit, area, GraphicsUnit::Pixel);

		//
		drawMap(buffer, jugador->getX(), jugador->getY(), tileSprite, modoJefe, areaJefe->getBlockX());
		balasActivas->todosDraw(buffer, jugador, modoJefe, areaJefe->getBlockX(), balasJugadorSprite, balasRobotinSprite, balasBabosinSprite, wallSprite, upcBalaSprite);
		aiActivos->todosDraw(buffer, jugador, modoJefe, areaJefe->getBlockX(), robotinSprite, babosinSprite, abejorroSprite, aranhaSprite, bichoSprite, upcSprite, capsulaSprite);
		jugador->draw(buffer, playerSprite, modoJefe, areaJefe->getBlockX(), areaJefe->getBlockY());
		if (!modoJefe) upgradesActivos->todosDraw(buffer, jugador, healthUpgradeSprite, resistanceUpgradeSprite, attackUpgradeSprite);
		uiDraw(buffer);

		// (3) Renderizar Buffer
		buffer->Render(gr);

		// (4) Deleting Memory
		delete buffer;
		delete space;
		delete gr;

		// Deaths -> En caso de que alguien muera, se ve aqui (solo funciona despu�s de los delete)
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
			areaJefe->possiblyCollides(jugador) + "\n"
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
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void lbl_Boss_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void prgBar_Boss_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
