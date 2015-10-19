class Hero {

private:
	int life;
	int atk;
	int speed;
	int x;
	int y;
	bool bonus;
	int score;

public:

	Hero() {
		this->life = 100;
		this->atk = 10;
		this->speed = 1;
		this->x = 0;
		this->y = 0;
		this->bonus = false;
		this->score = 0;
	};

	int getLife() { return life; }
	int getAtk() { return atk; }
	int getSpeed() { return speed; }
	int getX() { return x; }
	int getY() { return y; }
	int getScore() { return score;  }

	void setLife(int l) { this->life = l; }
	void setAtk(int a) { this->atk = a; }
	void setSpeed(int s) { this->speed = s; }

	void ramasserBonus(int b){
		
	}
	

};
