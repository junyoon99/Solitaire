#include "Card.h"

using namespace solitaire;

void Card::Draw(Gdiplus::Graphics& graphics)
{
	if (mIsFront) 
	{
		graphics.DrawImage(
			mFrontImage.get(), mX, mY, mFrontImage->GetWidth(), mFrontImage->GetHeight()
		);
	}
	else 
	{
		graphics.DrawImage(
			mBackImage.get(), mX, mY, mBackImage->GetWidth(), mBackImage->GetHeight()
		);
	}
}

void Card::Flip(bool isFront)
{
	mIsFront = isFront;
	Invalidate();
}

bool Card::CheckClicked(int x, int y)
{
	if (x >= mX &&
		y >= mY &&
		x <= mX + (int)mBackImage->GetWidth() &&
		y <= mY + (int)mBackImage->GetHeight())
	{
		Flip(!mIsFront);
		return true;
	}

	return false;
}

void solitaire::Card::Invalidate()
{
	RECT rct{ mX, mY, mX + (int)mBackImage->GetWidth(), mY + (int)mBackImage->GetHeight() };
	InvalidateRect(mHwnd, &rct, false);
}
