#include <iostream>
#include <assert.h>
#include "FontManager.h"

FontManager* FontManager::fontManager = nullptr;

FontManager* FontManager::getInstance()
{
	if (FontManager::fontManager == nullptr)
		FontManager::fontManager = new FontManager();
	return FontManager::fontManager;
}

FontManager::FontManager()
{
	fonts = std::vector<Font*>();
}

FontManager::~FontManager()
{

}

bool FontManager::addFont(char* name, char* fontFilePath)
{
	Font* newFont = new Font(name, fontFilePath);

	if (newFont->isCreated())
	{
		fonts.push_back(newFont);
		return true;
	}
	else
	{
		delete newFont;
		return false;
	}
}

Font* FontManager::getFont(int index)
{
	if (index >= 0 && index < fonts.size())
	{
		return fonts[index];
	}
	return nullptr;
}

Font* FontManager::getFont(char* name)
{
	for (unsigned int i = 0; i < fonts.size(); i++)
	{
		if (strcmp(name, fonts[i]->getName()) == 0)
			return fonts[i];
	}
	return nullptr;
}

int FontManager::getFontCount()
{
	return (int)fonts.size();
}