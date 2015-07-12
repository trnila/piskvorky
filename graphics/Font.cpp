#include "Font.h"

Font::Font(SDL_Renderer *renderer, TTF_Font *font) {
	this->font = font;
	this->maxWidth = 0;
	this->renderer = renderer;
	this->spacing = 10;
	build();
}
	
Font::~Font() {
	SDL_DestroyTexture(texture);
}
	
void Font::build() {
	height = TTF_FontHeight(font);
	bitmapHeight = ceil(('~' - ' ') / 8.0) * height;
	
	// find font max width
	for(char c = ' '; c <= '~'; c++) {
		int minx, maxx;
		if(TTF_GlyphMetrics(font, c, &minx,&maxx, NULL, NULL, NULL) == 0) {
			int width = maxx - minx;
			widths[c - ' '] = width+spacing;

			if(width > maxWidth) {
				maxWidth = width;
			}
		}
	}
        
	SDL_Surface *surf = SDL_CreateRGBSurface(0, maxWidth * 8, bitmapHeight, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	SDL_Rect dst;
	dst.x = 0;
	dst.y = 0;
	dst.w = maxWidth;
	dst.h = bitmapHeight;
        
	for(char c = ' '; c <= '~'; c++) {
		if((c-' ') % 8 == 0 && c != ' ') { //dirty hack :D
			dst.x = 0;
			dst.y += TTF_FontHeight(font);            
		}

		SDL_Surface *letter = TTF_RenderGlyph_Blended(font, c, {255,255,255});
		if(letter) {
			SDL_BlitSurface(letter, NULL, surf, &dst);
			SDL_FreeSurface(letter);
		}

		dst.x += maxWidth;
	}

	SDL_SaveBMP(surf, "/tmp/a.bmp");
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	
	SDL_FreeSurface(surf);

	/*SDL_Rect r;
	r.x = 0; r.y = 200;
	SDL_QueryTexture(texture, NULL, NULL, &r.w, &r.h);

	SDL_RenderCopy(root->renderer, texture, NULL, &r);*/
}


SDL_Rect Font::write(const char *msg, const SDL_Rect &rect, const SDL_Color &color, int fontSize) {		
	SDL_Rect src, dst;		

	dst.h = fontSize > 0 ? fontSize : height;
	dst.x = rect.x;
	dst.y = rect.y;

	src.h = height;
	src.w = maxWidth;
	
	SDL_Rect result;
	result.x = rect.x;
	result.y = rect.y;
	result.h = dst.h;
	result.w = 0;
	
	int w = 0;
	
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);

	for(int i = 0; msg[i] != '\0'; i++) {
		// put newline if overflows or newline character
		if(msg[i] == '\n' || (rect.w != 0 && dst.x + widths[msg[i] - ' '] > rect.x + rect.w)) {
			dst.y += height;
			dst.x = rect.x;
			
			result.h += dst.h;
			
			if(w > result.w) {
				result.w = w;
			}
			w = 0;
		}

		// dont render more chars when overflows y
		if(rect.h != 0 && dst.y + height >= rect.y + rect.h) {
			break;
		}


		//widths[0] = 20;
		if(msg[i] >= ' ' && msg[i] <= '~') {
			src.x = maxWidth * ((msg[i] - ' ')%8);
			src.y = ceil((msg[i] - ' ') / 8)*height;
			dst.w = maxWidth;
			w += widths[msg[i] - ' '];

			SDL_RenderCopy(renderer, texture, &src, &dst);

			dst.x += widths[msg[i] - ' '];				
		}
	}
	
	if(w > result.w) {
		result.w = w;
	}
	
	/*SDL_SetRenderDrawBlendMode(root->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(root->renderer, 0, 255, 0, 125);
	SDL_RenderFillRect(root->renderer, &result);
	*/
	return result;
}

