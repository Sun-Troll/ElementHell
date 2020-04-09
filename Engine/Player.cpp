#include "Player.h"
#include <cassert>

Player::Player(const VecF& pos)
	:
	pos(pos)
{
	spritesPlayer.resize(nSpritesPlayer);
	for (int i = 0; i < nSpritesPlayer; ++i)
	{
		const std::string bitmapFile = "Sprites\\Player\\Player" + std::to_string(i) + ".bmp";
		spritesPlayer[i] = Surface(bitmapFile);
		assert(spritesPlayer[i].GetWidth() == spritePlayerWidth
			&& spritesPlayer[i].GetHeight() == spritePlayerHeight);
	}
	spritesBulletCenter.resize(nSpritesBulletCenter);
	for (int i = 0; i < nSpritesBulletCenter; ++i)
	{
		const std::string bitmapFile = "Sprites\\PlBulCenter\\PlBulCenter" + std::to_string(i) + ".bmp";
		spritesBulletCenter[i] = Surface(bitmapFile);
		assert(spritesBulletCenter[i].GetWidth() == spriteBulletCenterDim
			&& spritesBulletCenter[i].GetHeight() == spriteBulletCenterDim);
	}
}

void Player::Move(bool left, bool right, bool up, bool down, float dt)
{
	VecF dir{ 0.0f, 0.0f };
	if (left)
	{
		dir.x -= speed;
	}
	if (right)
	{
		dir.x += speed;
	}
	if (up)
	{
		dir.y -= speed;
	}
	if (down)
	{
		dir.y += speed;
	}
	pos += dir.GetNormalized() * speed * dt;
}

void Player::Clamp()
{
	if (pos.x < movementRegionPlayer.left)
	{
		pos.x = movementRegionPlayer.left;
	}
	else if (pos.x > movementRegionPlayer.right)
	{
		pos.x = movementRegionPlayer.right;
	}
	if (pos.y < movementRegionPlayer.top)
	{
		pos.y = movementRegionPlayer.top;
	}
	else if (pos.y > movementRegionPlayer.bottom)
	{
		pos.y = movementRegionPlayer.bottom;
	}
}

void Player::Fire(float dt)
{
	const VecF playerCenter{ pos.x + float(spritePlayerWidth) / 2.0f, pos.y + float(spritePlayerHeight) / 2.0f };
	const VecF target{ playerCenter.x, playerCenter.y - 500.0f };
	curFireBasePlayerAnim += dt;
	while (curFireBasePlayerAnim >= maxFireTimePlayerAnim)
	{
		curFireBasePlayerAnim -= maxFireTimePlayerAnim;
		bulletsCenter.emplace_back(BulletCenter{
			{ playerCenter.x - float(spriteBulletCenterDim) / 2.0f, playerCenter.y - float(spriteBulletCenterDim) / 2.0f },
			{ (target - playerCenter).GetNormalized() * bulletCenterSpeed } });
	}
}

void Player::UpdateCenterBullets(float dt)
{
	for (auto& bc : bulletsCenter)
	{
		bc.Move(dt);
		bc.Animate(dt);
	}

	for (int i = 0; i < bulletsCenter.size(); ++i)
	{
		if (bulletsCenter[i].Clamp(movementRegionBulletCenter)) //change this to real value after cliping sprite draw in
		{
			PopCenterBullet(i);
			--i;
		}
	}
}

void Player::PopCenterBullet(int i)
{
	std::swap(bulletsCenter[i], bulletsCenter.back());
	bulletsCenter.pop_back();
}

void Player::Draw(Graphics& gfx) const
{
	const int iSpritePlayer = int(curFireBasePlayerAnim * nSpritesPlayer / maxFireTimePlayerAnim);
	gfx.DrawSprite(int(pos.x), int(pos.y), spritesPlayer[iSpritePlayer]);
}

void Player::DrawBulletsCenter(Graphics& gfx) const
{
	for (const auto& bc : bulletsCenter)
	{
		bc.Draw(spritesBulletCenter, gfx);
	}
}

Player::BulletCenter::BulletCenter(const VecF& pos, const VecF& vel)
	:
	pos(pos),
	vel(vel)
{
}

void Player::BulletCenter::Move(float dt)
{
	pos += vel * dt;
}

void Player::BulletCenter::Animate(float dt)
{
	curAnimTime += dt;
	while (curAnimTime >= maxAnimTime)
	{
		curAnimTime -= maxAnimTime;
	}
}

bool Player::BulletCenter::Clamp(const RectF& bulletCenterRegion)
{
	if (pos.x < bulletCenterRegion.left)
	{
		return true;
	}
	else if (pos.x > bulletCenterRegion.right)
	{
		return true;
	}
	if (pos.y < bulletCenterRegion.top)
	{
		return true;
	}
	else if (pos.y > bulletCenterRegion.bottom)
	{
		return true;
	}
	return false;
}

void Player::BulletCenter::Draw(const std::vector<Surface>& sprites, Graphics& gfx) const
{
	const int iBulletCenter = int(curAnimTime * nSpritesBulletCenter / maxAnimTime);
	gfx.DrawSprite(int(pos.x), int(pos.y), sprites[iBulletCenter], gfx.GetGameRect());
}
