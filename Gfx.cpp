#include "Gfx.h"

Font::Font(Root *root, TTF_Font *font):Component(root) {
		this->font = font;
		this->maxWidth = 0;
	}
	
Font::~Font() {
	SDL_DestroyTexture(texture);
}
	
void Font::build() {
	height = TTF_FontHeight(font);

	// find font max width
	for(char c = ' '; c <= '~'; c++) {
		int minx, maxx;
		if(TTF_GlyphMetrics(font, c, &minx,&maxx, NULL, NULL, NULL) == 0) {
			int width = maxx - minx;
			widths[c - ' '] = width;

			if(width > maxWidth) {
				maxWidth = width;
			}
		}
	}

	SDL_Surface *surf = SDL_CreateRGBSurface(0, maxWidth * ('~' - ' '), 100, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = maxWidth;
	dst.h = height;

	for(char c = ' '; c <= '~'; c++) {
		SDL_Surface *letter = TTF_RenderGlyph_Blended(font, c, {255,255,255});
		if(letter) {
			SDL_BlitSurface(letter, NULL, surf, &dst);
			SDL_FreeSurface(letter);
		}

		dst.x += maxWidth;
	}

	SDL_SaveBMP(surf, "/tmp/a.bmp");
	texture = SDL_CreateTextureFromSurface(root->renderer, surf);
	
	SDL_FreeSurface(surf);

	/*SDL_Rect r;
	r.x = 0; r.y = 200;
	SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);

	SDL_RenderCopy(root->renderer, texture, NULL, &r);*/
}


void Font::write(const char *msg, const SDL_Rect &rect, const SDL_Color &color) {		
	SDL_Rect src, dst;		

	dst.h = height;
	dst.x = rect.x;
	dst.y = rect.y;

	src.h = height;
	src.w = maxWidth;
	
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

	for(int i = 0; msg[i] != '\0'; i++) {
		// put newline if overflows or newline character
		if(msg[i] == '\n' || dst.x + widths[msg[i] - ' '] > rect.x + rect.w) {
			dst.y += height;
			dst.x = rect.x;
		}

		// dont render more chars when overflows y
		if(dst.y + height >= rect.y + rect.h) {
			break;
		}



		if(msg[i] >= ' ' && msg[i] <= '~') {
			src.x = maxWidth * (msg[i] - ' ');
			src.y = 0;

			dst.w = maxWidth;

			SDL_RenderCopy(root->renderer, texture, &src, &dst);

			dst.x += widths[msg[i] - ' '];				
		}
	}
}


TBox::TBox(Root *root, Font *font, SDL_Rect rect):Component(root) {
	this->font = font;
	this->rect = rect;
	this->color = {255, 255, 255};
	this->background = {250, 0, 0, 0};
}

void TBox::print(const char *msg) {
	buffer += msg;
}

void TBox::render() {
	//SDL_SetRenderDrawBlendMode(root->renderer, SDL_BLENDMODE_BLEND);
	//SDL_SetRenderDrawColor(root->renderer, background.r, background.g, background.b, 0);
	//SDL_RenderFillRect(root->renderer, &rect);

	font->write(buffer.c_str(), rect, color);
}
