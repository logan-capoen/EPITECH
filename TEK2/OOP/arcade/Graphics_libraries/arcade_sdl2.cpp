/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** SDL2
*/

#include "arcade_sdl2.hpp"

SDL2::SDL2()
{
    _name = "sdl2";
    _type = LibType::DISPLAY;
}

SDL2::~SDL2()
{
}

int SDL2::createWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        throw std::runtime_error(std::string("SDL_Init failed: ") + SDL_GetError());
    }
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        throw std::runtime_error(std::string("IMG_Init failed: ") + IMG_GetError());
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error(std::string("TTF_Init failed: ") + TTF_GetError());
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw std::runtime_error(std::string("Mix_OpenAudio failed: ") + Mix_GetError());
    }
    _window = SDL_CreateWindow(
        "SDL2 ARCADE MENU",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!_window) {
        throw std::runtime_error(std::string("SDL_CreateWindow failed: ") + SDL_GetError());
    }
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!_renderer) {
        throw std::runtime_error(std::string("SDL_CreateRenderer failed: ") + SDL_GetError());
    }
    if (SDL_RenderSetLogicalSize(_renderer, 1920, 1080) != 0) {
        throw std::runtime_error(std::string("SDL_RenderSetLogicalSize failed: ") + SDL_GetError());
    }
    _colors[RED] = {255, 0, 0, 255};
    _colors[GREEN] = {0, 255, 0, 255};
    _colors[BLUE] = {0, 0, 255, 255};
    _colors[YELLOW] = {255, 255, 0, 255};
    _colors[BLACK] = {0, 0, 0, 255};
    _colors[WHITE] = {255, 255, 255, 255};
    _colors[MAGENTA] = {255, 0, 255, 255};
    _colors[CYAN] = {0, 255, 255, 255};
    return 0;
}

void SDL2::closeWindow()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void SDL2::clear()
{
    if (_renderer) {
        SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        SDL_RenderClear(_renderer);
    }
}

void SDL2::display()
{
    if (_renderer) {
        SDL_RenderPresent(_renderer);
    }
}

InputEvent SDL2::getInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return {QUIT, {0, 0}};
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    return {UP_ARROW, {0, 0}};
                case SDLK_DOWN:
                    return {DOWN_ARROW, {0, 0}};
                case SDLK_LEFT:
                    return {LEFT_ARROW, {0, 0}};
                case SDLK_RIGHT:
                    return {RIGHT_ARROW, {0, 0}};
                case SDLK_SPACE:
                    return {SPACE, {0, 0}};
                case SDLK_ESCAPE:
                    return {QUIT, {0, 0}};
                case SDLK_m:
                    return {CALL_MENU, {0, 0}};
                case SDLK_d:
                    return {SWITCH_DISPLAY, {0, 0}};
                case SDLK_g:
                    return {SWITCH_GAME, {0, 0}};
                case SDLK_r:
                    return {RESTART_GAME, {0, 0}};
            }
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
            return {LEFT_CLICK, {event.button.x / 64, event.button.y / 54}};
        }
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
            return {RIGHT_CLICK, {event.button.x / 64, event.button.y / 54}};
        }
    }
    return {UNKNOWN, {0, 0}};
}

void SDL2::drawText(pos position, float size, std::string text, Color color)
{
    if (!_renderer || text.empty()) {
        return;
    }
    auto it = _colors.find(color);
    SDL_Color sdlColor = (it != _colors.end()) ? it->second : SDL_Color{255, 255, 255, 255};
    TTF_Font *font = TTF_OpenFont(FONT_PATH, static_cast<int>(40 * size));
    if (!font) {
        return;
    }
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), sdlColor);
    if (!surface) {
        TTF_CloseFont(font);
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_Rect dst;
    dst.w = surface->w;
    dst.h = surface->h;
    if (position.x == -1)
        dst.x = (1920 - dst.w) / 2;
    else
        dst.x = static_cast<int>(position.x * (1920 / 30.0f));
    dst.y = static_cast<int>(position.y * (1080 / 20.0f));
    SDL_RenderCopy(_renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void SDL2::drawSprite(pos position, int rotation, float size, std::string name)
{
    auto it = _textures.find(name);
    if (it == _textures.end())
        return;
    SDL_Texture *texture = it->second;
    SDL_Rect rect;
    rect.w = static_cast<int>(64.0f * size);
    rect.h = static_cast<int>(54.0f * size);
    rect.x = static_cast<int>(position.x * 64.0f + 32.0f) - (rect.w / 2);
    rect.y = static_cast<int>(position.y * 54.0f + 27.0f) - (rect.h / 2);
    SDL_RenderCopyEx(_renderer, texture, nullptr, &rect, static_cast<double>(rotation), nullptr, SDL_FLIP_NONE);
}

int SDL2::loadTexture(std::string game)
{
    std::string path = "assets/" + game + "/images";
    if (!std::filesystem::exists(path))
        throw std::runtime_error("directory: " + path + " not found");
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_regular_file())
            continue;
        SDL_Surface *surface = IMG_Load(entry.path().string().c_str());
        if (!surface)
            continue;
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_FreeSurface(surface);
        if (texture)
            _textures[entry.path().stem().string()] = texture;
    }
    return 0;
}

int SDL2::loadSound(std::string game)
{
    std::string path = "assets/" + game + "/sounds";
    if (!std::filesystem::exists(path))
        throw std::runtime_error("directory: " + path + " not found");
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_regular_file())
            continue;
        Mix_Chunk *sound = Mix_LoadWAV(entry.path().string().c_str());
        if (sound)
            _sounds[entry.path().stem().string()] = sound;
    }
    return 0;
}

int SDL2::playSound(std::string sound)
{
    if (_sounds.find(sound) != _sounds.end())
        Mix_PlayChannel(-1, _sounds[sound], 0);
    return 0;
}

std::string SDL2::loadName()
{
    std::string name;
    SDL_Event event;
    SDL_StartTextInput();
    while (true) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_StopTextInput();
                return name.empty() ? "keryan poulet druelle" : name;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SDL_StopTextInput();
                    return "";
                }
                if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    SDL_StopTextInput();
                    return name.empty() ? "keryan poulet druelle" : name;
                }
                if (event.key.keysym.sym == SDLK_BACKSPACE && !name.empty())
                    name.pop_back();
            }
            if (event.type == SDL_TEXTINPUT)
                if (name.size() < 20)
                    name += event.text.text;
        }
        clear();
        drawText({POS_CENTER.x - 8, POS_CENTER.y - 4}, 3.0f, "Choisissez votre nom :", WHITE);
        drawText({POS_CENTER.x - 8, POS_CENTER.y + 1}, 2.5f, name + "|", CYAN);
        display();
    }
}

std::tuple<int, int> SDL2::recoverWindowSize()
{
    return {1920, 1080};
}

void SDL2::drawBackground(std::string background_name)
{
    auto it = _textures.find(background_name);
    if (it != _textures.end()) {
        SDL_Rect dstRect = {0, 0, 1920, 1080};
        SDL_RenderCopy(_renderer, it->second, nullptr, &dstRect);
    }
}

extern "C" ILib* entryPoint()
{
    return new SDL2();
}
