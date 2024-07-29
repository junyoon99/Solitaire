#pragma once

#include <Windows.h>
#include <gdiplus.h>
#include <memory>
#include <string>

namespace solitaire {
	class Card 
	{
	public:
		enum class Type 
		{
			Wolf,
			Dragon,
			Bear
		};

	private:
		std::unique_ptr<Gdiplus::Image> mBackImage;
		std::unique_ptr<Gdiplus::Image> mFrontImage;

		HWND mHwnd;
		int mX;
		int mY;
		Type mType;
		bool mIsFront;

	public:
		Card(HWND hwnd, Type type, int x, int y) :
			mHwnd(hwnd), mX(x), mY(y), mType(type), mIsFront(false)
		{
			mBackImage = std::make_unique<Gdiplus::Image>(L"images/card_back.png");

			std::wstring filename;
			switch (type)
			{
				case Type::Wolf:
					filename = L"images/card_creature_wolf.png";
					break;
				case Type::Dragon:
					filename = L"images/card_creature_dragon.png";
					break;
				case Type::Bear:
					filename = L"images/card_creature_bear.png";
					break;
			}

			mFrontImage = std::make_unique<Gdiplus::Image>(filename.c_str());
		}

		void Draw(Gdiplus::Graphics& graphics);
		void Flip(bool isFront);
		bool CheckClicked(int x, int y);
		void Invalidate();
	}; 
}

