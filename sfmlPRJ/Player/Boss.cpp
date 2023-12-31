#include "stdafx.h"
#include "Boss.h"
#include "SceneGame.h"
#include "Scene.h"
#include "Player.h"
#include "SoundGo.h"
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
	attackTypeRand = Utils::RandomRange(0, 5);

	bossTan = new SoundGo("Sounds/BossTan.wav");
	bossShootPool.OnCreate = [this](Shoot* bullet) {
		bullet->SetBoss(this);
		bullet->pool = &bossShootPool;
	};
	bossShootPool.Init();
	normalPatternTimeDuration = 10.f;
}

void Boss::Release()
{
	SpriteGo::Release();
	bossShootPool.Release();
	if (bossTan != nullptr) delete bossTan;
}

void Boss::Reset()
{
	bossShootPool.Clear();
	animation.Play("Idle");
	SetOrigin(Origins::MC);
	SetPosition(-270.f, -250.f);
	bossHp = 810;
	startPos = sf::Vector2f{ -270.f, -250.f };
	endPos = sf::Vector2f({ 0.f, -50.f });
	secondPos = sf::Vector2f(-200.f, 0.f);
	moveTime = 0.f;
	moveTimerDuration = 0.f;
	normalPatternTime = 0.f;
	normalAttackDuration = 1.0f;
	normalAttackTime = 3.0f;
	stopAttackTime = 0.f;
	bossDie = false;
	score = 0;
	onePage = true;
	twoPage = false;
	threePage = false;
	fourPage = false;
	stopAttackTimeLimit = 2.0f;
	normalPatternTimeDuration = 10.f;
}

void Boss::Update(float dt)
{
	PageCheck();
	if (bossHp <=0.f)
	{
		bossDie = true;
	}
	if (!bossDie && !player->GetPlayerDie())
	{
		BossMove(dt);
		BossFireUcnique(dt);
		BossFireNormal(dt);
		Scene* scene = SCENE_MGR.GetCurrScene();
		SceneGame* sceneGame = dynamic_cast<SceneGame*>(scene);
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Tab) && sceneGame->GetBoombCountSpriteCurrent()> -1 && player->GetEffectDraw())
		{
			bossShootPool.Clear();
			sceneGame->UseBoomb();
		}
		
		animation.Update(dt);
		SpriteGo::Update(dt);
	}
	if (player->GetPlayerDie())
	{
		bossShootPool.Clear();
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
		bossTan->SoundPlay();
		uniqueshootPatternMgr.ChangePattern(1);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();
	}
	if (threePage) 
		stopAttackTimeLimit = 1.0f;
	else 
		stopAttackTimeLimit = 2.0f;
	if (stopBoss && stopAttackTime < stopAttackTimeLimit && threePage)
	{
		stopAttackTime = 1.5f;
		bossTan->SoundPlay();
		uniqueshootPatternMgr.ChangePattern(2);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.ShootBullets();

	}
	if (stopBoss && stopAttackTime < stopAttackTimeLimit && fourPage)
	{
		bossTan->SoundPlay();
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
	normalPatternTime += dt;
	normalAttackTime -= dt;

	if (attackTypeRand == 2 && twoPage)
	{
		normalAttackDuration = 0.2f;
	}
	else
	{
		normalAttackDuration = 1.0f;
	}
	if (normalPatternTime > normalPatternTimeDuration && (twoPage || threePage))
	{
		int prevType = attackTypeRand;
		attackTypeRand = Utils::RandomRange(0, 5);
		if (prevType == attackTypeRand)
			attackTypeRand = Utils::RandomRange(0, 5);
		normalPatternTime = 0.f;
	}
	if (normalAttackTime < normalAttackDuration && (twoPage || threePage))
	{
		normalAttackTime = normalAttackDuration + 0.3f;
		shootPatternMgr.ChangePattern(attackTypeRand);
		shootPatternMgr.SetCharacterAll(player, this);
		shootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
		shootPatternMgr.ShootBullets();
	}
	if (onePage && normalAttackTime < normalAttackDuration)
	{
		normalAttackTime = 3.f;
		bossTan->SoundPlay();
		uniqueshootPatternMgr.ChangePattern(0);
		uniqueshootPatternMgr.SetCharacterAll(player, this);
		uniqueshootPatternMgr.SetWallBounds(WallBounds, bgWidth, bgHeight);
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

void Boss::PageCheck()
{
	if (bossHp > 750.f && !onePage)onePage = true;
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
}
