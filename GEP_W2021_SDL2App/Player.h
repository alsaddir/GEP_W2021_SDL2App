#pragma once
#include"SpriteEx.h"
#include"vector"
#include"Bullet.h"

using namespace std;
class Player : public SpriteExAnimated
{
private:
	vector<Bullet*> m_vBullets;

	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;

	void UpdateBullets();
	void MoveForward();
	void UpdatePlayer();
public:
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	void Render();
	void Update();
	void SetIdle();
	void SpawnBullet();
	


	vector<Bullet*>& GetBullets() { return m_vBullets; }


};

