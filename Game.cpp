#include "Game.h"

using namespace solitaire;

void Game::Init(HWND hwnd)
{
	mhwnd = hwnd;
	mBackgroundImage = std::make_unique<Gdiplus::Image>(L"images/bg_blank.png");
	CreateCardDeck();
}

void Game::Release()
{
	mDeck.clear();
	mBackgroundImage.reset();
}

void Game::Draw(Gdiplus::Graphics& graphics)
{
	graphics.DrawImage(
		mBackgroundImage.get(), 0, 0, mBackgroundImage->GetWidth(), mBackgroundImage->GetHeight()
	);

	for (auto& card : mDeck) 
	{
		card.Draw(graphics);
	}

	Gdiplus::PointF pos(895.0f, 20.0f);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255,79,64));
	Gdiplus::Font font(L"¸¼Àº °íµñ", 20);
	graphics.DrawString(L"Å¬¸¯ ¼ö : ", -1, &font, pos, &brush);

	Gdiplus::StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentCenter);
	format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	graphics.DrawString(
		std::to_wstring(mFlipCount).c_str(),
		-1,
		&font,
		BOARD_COUNT,
		&format,
		&brush
	);
}

void Game::OnClick(int x, int y)
{
	for(auto& card : mDeck)
	{
		if (card.CheckClicked(x, y)) 
		{
			//TODO
		}
	}
}

void solitaire::Game::CreateCardDeck()
{
	//TODO
	//mDeck.push_back(Card(mhwnd, Card::Type::Bear, 0, 0));
	//mDeck.push_back(Card(mhwnd, Card::Type::Wolf, 120, 0));
	//mDeck.push_back(Card(mhwnd, Card::Type::Dragon, 240, 0));
}
