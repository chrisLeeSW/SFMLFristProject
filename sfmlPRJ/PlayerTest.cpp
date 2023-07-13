#include "stdafx.h"
#include "PlayerTest.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
PlayerTest::PlayerTest(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

void PlayerTest::Init()
{
	RESOURCE_MGR.Load(ResourceTypes::AimationClip, "Animations/Player_Ani_Idel.csv");
	RESOURCE_MGR.Load(ResourceTypes::AimationClip, "Animations/Player_Ani_Move.csv");
	RESOURCE_MGR.Load(ResourceTypes::AimationClip, "Animations/Player_Ani_Jump.csv");

	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Idel.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Move.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Player_Ani_Jump.csv"));

	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);

}

void PlayerTest::Reset()
{
	animation.Play("Idle");
	SetOrigin(origin);
	SetPosition(0, 0);
	//SpriteGo::Reset();
}

void PlayerTest::Update(float dt)
{
	bool LeftKey = INPUT_MGR.GetKey(sf::Keyboard::Left);
	bool RightKey = INPUT_MGR.GetKey(sf::Keyboard::Right);
	bool UpKeyDown = INPUT_MGR.GetKeyDown(sf::Keyboard::Up);
	bool LeftKeyUp = INPUT_MGR.GetKeyUp(sf::Keyboard::Left);
	bool RightKeyUp = INPUT_MGR.GetKeyUp(sf::Keyboard::Right);
	bool UpKeyUp = INPUT_MGR.GetKeyUp(sf::Keyboard::Up);

	if (LeftKey && !dontMoveLeftPlayer)
	{
		if (!movePlayer)
		{
			animation.Play("Move");
			sprite.setScale(-1.f, 1.f);
			direction = { -1.f,0.f };
			movePlayer = true;
		}
		dontMoveRigthPlayer = true;
	}
	if (RightKey && !dontMoveRigthPlayer)
	{
		if (!movePlayer)
		{
			animation.Play("Move");
			sprite.setScale(1.f, 1.f);
			direction = { 1.f,0.f };
			movePlayer = true;

		}
		dontMoveLeftPlayer = true;
	}
	if (UpKeyDown)
	{
		animation.Play("Jump");
		velocity = jumpFource;
	}
	if (LeftKeyUp || RightKeyUp)
	{
		animation.Play("Idle");
		direction = { 0.f,0.f };
		movePlayer = false;
		dontMoveRigthPlayer = false;
		dontMoveLeftPlayer = false;
	}
	if (UpKeyUp)
	{
		if (RightKey || LeftKey)
			animation.PlayQueue("Move");
		else
			animation.PlayQueue("Idle");
	}
	
	position += direction * 500.f * dt;
	velocity -= grivaty * dt;
	position.y -= velocity;

	position.y -= grivaty * dt;
	sprite.setPosition(position);


	SpriteGo::Update(dt);
	animation.Update(dt);
}
/*a += dt;
	if (a >= ? )
	{
		abc = Utils::RandomRange(0, 5);일반패턴
		switch (abc)
		{
			s = dasd
				dsad
				sad

		}문자열
		animation, playQueq(s);
	}

	if (hp < 50 && !newPaten)
	{
		cuuern ->
			animation.Play("Idle");
	}*/
	// 느낌의 보스 슈팅 패턴 짜보기