#include "Player.h"

Player::Player(const VecF& pos)
	:
	pos(pos),
	spriteBase("Sprites\\PlayerTestEdit.bmp")
{
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
	if (pos.x < movementRegion.left)
	{
		pos.x = movementRegion.left;
	}
	else if (pos.x > movementRegion.right)
	{
		pos.x = movementRegion.right;
	}
	if (pos.y < movementRegion.top)
	{
		pos.y = movementRegion.top;
	}
	else if (pos.y > movementRegion.bottom)
	{
		pos.y = movementRegion.bottom;
	}
}

void Player::Draw(Graphics& gfx) const
{
	gfx.DrawSprite(int(pos.x), int(pos.y), spriteBase);
}
