#include "stdafx.h"
#include "Boss.h"
#include "SceneGame.h"
#include "Scene.h"
#include "Player.h"

void Boss::Init()
{
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Idle.csv"));
	animation.AddClip(*RESOURCE_MGR.GetAnimationClip("Animations/Boss/Move.csv"));


	animation.SetTarget(&sprite);

	SetOrigin(Origins::MC);

	moveTime = 0.f;
	moveTimerDuration = 0.f;
	startPos = sf::Vector2f{ -270.f, -250.f };
	endPos = sf::Vector2f({ 0.f, -50.f });
	secondPos = sf::Vector2f(-200.f, 0.f);
	attackRand1 = Utils::RandomRange(0, 5);


	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(this);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();
	bossAttackNoramalPatternChangeTimeLimit = 10.f;
}

void Boss::Release()
{
	SpriteGo::Release();
	bossShootPool.Release();
}

void Boss::Reset()
{
	bossShootPool.Clear();
	shootPatternMgr.ClearBossShootPools();
	uniqueshootPatternMgr.ClearBossShootPools();
	animation.Play("Idle");
	SetOrigin(Origins::MC);
	SetPosition(-270.f, -250.f);
	bossHp = 810;
	startPos = sf::Vector2f{ -270.f, -250.f };
	endPos = sf::Vector2f({ 0.f, -50.f });
	secondPos = sf::Vector2f(-200.f, 0.f);
	moveTime = 0.f;
	moveTimerDuration = 0.f;
	bossAttackNoramalPatternChangeTime = 0.f;
	bossAttackTimeOneLimit = 1.0f;
	stopAttackTime = 0.f;
	bossDie = false;
	score = 0;
	onePage = true;
	twoPage = false;
	threePage = false;
	fourPage = false;
	stopAttackTimeLimit = 2.0f;
	bossAttackNoramalPatternChangeTimeLimit = 10.f;
}

void Boss::Update(float dt)
{
	if(bossHp >750.f && !onePage)onePage = true;
	else if (bossHp < 750.f && bossHp>500.f && !twoPage)
	{
		onePage = false;
		twoPage = true;
	}
	else if (bossHp < 500.f && bossHp>200.f && !threePage)
	{
		twoPage = false;
		threePage = true;
	}
	else if (bossHp < 200.f && !fourPage)
	{
		threePage = false;
		fourPage = true;
	}

	if (bossHp == 0.f)
		bossDie = true;
	if (!bossDie && !player->GetPlayerDie())
	{
		BossMove(dt);
		BossFireUcnique(dt);
		BossFireNormal(dt);
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Tab) && sceneGame->GetBoombCountSpriteCurrent()> -1 && player->GetEffectDraw())
		{
			shootPatternMgr.ClearBossShootPools();
			uniqueshootPatternMgr.ClearBossShootPools();
			sceneGame->UseBoomb();
		}
		
		animation.Update(dt);
		SpriteGo::Update(dt);
	}
	if (player->GetPlayerDie())
	{
		shootPatternMgr.ClearBossShootPools();
		uniqueshootPatternMgr.ClearBossShootPools();
	}
}

void Boss::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Boss::BossMove(float dt)
{
	moveTime += dt;
	moveTimerDuration += dt;
	float t = moveTime / moveDuration;
	if (t >= 1.f)
	{
		t = 1.f;
	}
	if (position == endPos) effectUniqueAttack = true;
	else effectUniqueAttack = false;
	if (position == endPos)
	{
		animation.Play("Idle");
		moveBoss = false;
		stopBoss = true;
		if (moveTimerDuration > stopLimit)
		{
			stopBoss = false;
			moveTime = 0.f;
			moveTimerDuration = 0.f;
			startPos = position;
			secondPos = sf::Vector2f(Utils::RandomRange(0, 500), -Utils::RandomRange(0, 150));
			if (secondPos.x > 200.f)
				secondPos.x = -secondPos.x;
			endPos = sf::Vector2f(Utils::RandomRange(0, 500), -Utils::RandomRange(0, 150));
			if (endPos.x > 200.f)
				endPos.x = -endPos.x;
		}
	}
	sf::Vector2f p = CalculateBezierPoint(startPos, secondPos, endPos, t);
	if (p.x - sprite.getGlobalBounds().width * 0.5f < WallBounds.x)
	{
		p.x = WallBounds.x + sprite.getGlobalBounds().width * 0.5f;
	}
	else if (p.x + sprite.getGlobalBounds().width * 0.5f > WallBounds.x + bgWidth)
	{
		p.x = WallBounds.x + bgWidth - sprite.getGlobalBounds().width * 0.5f;
	}

	if (p.y + sprite.getGlobalBounds().height * 0.5f > WallBounds.y + bgHeight)
	{
		p.y = WallBounds.y + bgHeight - sprite.getGlobalBounds().height * 0.5f;
	}
	else if (p.y - sprite.getGlobalBounds().height * 0.5f < WallBounds.y)
	{
		p.y = WallBounds.y + sprite.getGlobalBounds().height * 0.5f;
	}
	position = p;
	if (position.x != 0.f)
	{
		if (!moveBoss)
		{
			SetScale(1.f, 1.f);
			animation.Play("Move");
			moveBoss = true;
		}
	}
	position += direction * speed * dt;
	SetPosition(position);
}

void Boss::BossFireUcnique(float dt)
{
	stopAttackTime -= dt;
	if (twoPage) stopAttackTimeLimit = 0.5f;
	else stopAttackTimeLimit = 2.0f;

	if (stopBoss && stopAttackTime < stopAttackTimeLimit && twoPage) 
	{
		stopAttackTime = 4.0f;
		uniqueshootPatternMgr.ChangePattern(1);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();
	}
	if (threePage) stopAttackTimeLimit = 1.0f;
	if (stopBoss && stopAttackTime < stopAttackTimeLimit && threePage)
	{
		stopAttackTime = 1.5f;
		uniqueshootPatternMgr.ChangePattern(2);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();

	}
	if (stopBoss && stopAttackTime < stopAttackTimeLimit && fourPage)
	{
		stopAttackTime = 4.0f;
		uniqueshootPatternMgr.ChangePattern(1);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();

		uniqueshootPatternMgr.ChangePattern(3);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();
	}
	
}

void Boss::BossFireNormal(float dt)
{
	bossAttackNoramalPatternChangeTime += dt;
	bossAttackTimeOne -= dt;

	if (attackRand1 == 2 && twoPage)
	{
		bossAttackTimeOneLimit = 0.2f;
	}
	else
	{
		bossAttackTimeOneLimit = 1.0f;
	}
	if (bossAttackNoramalPatternChangeTime > bossAttackNoramalPatternChangeTimeLimit && (twoPage || threePage))
	{
		int prevType = attackRand1;
		attackRand1 = Utils::RandomRange(0, 5);
		if (prevType == attackRand1)
			attackRand1 = Utils::RandomRange(0, 5);
		bossAttackNoramalPatternChangeTime = 0.f;
	}
	if (bossAttackTimeOne < bossAttackTimeOneLimit && (twoPage || threePage))
	{
		bossAttackTimeOne = bossAttackTimeOneLimit + 0.3f;
		shootPatternMgr.ChangePattern(attackRand1);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.ShootBullets();
	}
	if (onePage && bossAttackTimeOne < bossAttackTimeOneLimit)
	{
		bossAttackTimeOne = 3.f;
		uniqueshootPatternMgr.ChangePattern(0);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();
	}
	
}


bool Boss::CheckCollisionWithBullet(const Shoot& bullet)
{

	if (sprite.getGlobalBounds().intersects(bullet.sprite.getGlobalBounds()))
	{
		bossHp -= player->GetPlayerDamage();
		score++;
		return true;
	}
	return false;
}

void Boss::SetWallBounds(sf::Vector2f boundf, float widthX, float widthY)
{
	bgWidth = widthX;
	bgHeight = widthY;
	WallBounds = boundf;
}


sf::Vector2f Boss::CalculateBezierPoint(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2, float t)
{
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;
	float uuu = uu * u;
	float ttt = tt * t;

	sf::Vector2f p = uuu * p0;
	p += 3 * uu * t * p1;
	p += 3 * u * tt * p2;
	p += ttt * p2;

	return p;
}
