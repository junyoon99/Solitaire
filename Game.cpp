#include "Game.h"
#include <vector>
#include <random>

using namespace solitaire;

void Game::Init(HWND hwnd)
{
	mHwnd = hwnd;
	mBackgroundImage = std::make_unique<Gdiplus::Image>(L"images/bg_blank.png");
	CreateCardDeck();
	mpSelectedCard = nullptr;
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
	Card* pCard{};
	for(auto& card : mDeck)
	{
		if (card.CheckClicked(x, y)) 
		{
			pCard = &card;
			break;
		}
	}
	if (pCard) 
	{
		mFlipCount++;
		RECT rct = { (LONG)BOARD_COUNT.GetLeft(), (LONG)BOARD_COUNT.GetTop(),
			(LONG)BOARD_COUNT.GetRight(), (LONG)BOARD_COUNT.GetBottom() };
		InvalidateRect(mHwnd, &rct, false);

		if (mpSelectedCard == nullptr) 
		{
			mpSelectedCard = pCard;
		}
		else 
		{
			if (pCard->Gettype() == mpSelectedCard->Gettype()) 
			{
				mpSelectedCard->Invalidate();
				mDeck.remove_if([&](Card& card) { return card.Getindex() == pCard->Getindex(); });
				mDeck.remove_if([&](Card& card) { return card.Getindex() == mpSelectedCard->Getindex(); });
				mpSelectedCard = nullptr;
			}
			else 
			{
				UpdateWindow(mHwnd);
				Sleep(500);

				pCard->Flip(false);
				mpSelectedCard->Flip(false);
				mpSelectedCard = nullptr;
			}
		}
	}
}

void solitaire::Game::CreateCardDeck()
{
	//TODO
	//mDeck.push_back(Card(mhwnd, Card::Type::Bear, 0, 0));
	//mDeck.push_back(Card(mhwnd, Card::Type::Wolf, 120, 0));
	//mDeck.push_back(Card(mhwnd, Card::Type::Dragon, 240, 0));

	std::vector<Card::Type> types;
	while (types.size() < (size_t)BOARD_COLUMN * BOARD_ROW) 
	{
		int mod = types.size() % 6;

		switch (mod)
		{
			case 0:
				types.push_back(Card::Type::Bear);
				types.push_back(Card::Type::Bear);
				break;

			case 2:
				types.push_back(Card::Type::Wolf);
				types.push_back(Card::Type::Wolf);
				break;

			case 4:
				types.push_back(Card::Type::Dragon);
				types.push_back(Card::Type::Dragon);
				break;
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());

	std::shuffle(types.begin(), types.end(), gen);

	int index{};
	int posX{ 15 }, posY{ 10 };
	for (int x{}; x < BOARD_COLUMN; ++x) 
	{
		posY = 10;

		for (int y{}; y < BOARD_ROW; ++y) 
		{
			mDeck.push_back(Card(mHwnd, index, types[index++], posX, posY));
			posY += 150;
		}
		posX += 110;
	}
}
