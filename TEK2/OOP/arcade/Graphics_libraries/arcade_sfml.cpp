/*
** EPITECH PROJECT, 2026
** G-OOP-400-LIL-4-1-arcade-6
** File description:
** SFML
*/

#include "arcade_sfml.hpp"
#include "ArcadeException.hpp"

SFML::SFML()
{
    _name = "sfml";
    _type = LibType::DISPLAY;
}

SFML::~SFML()
{
}

void SFML::clear()
{
    if (_window)
        _window->clear();
}

void SFML::display()
{
    if (_window)
        _window->display();
}

InputEvent SFML::getInput()
{
    sf::Event event;

    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return {QUIT, {0, 0}};
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    return {UP_ARROW, {0, 0}};
                case sf::Keyboard::Down:
                    return {DOWN_ARROW, {0, 0}};
                case sf::Keyboard::Left:
                    return {LEFT_ARROW, {0, 0}};
                case sf::Keyboard::Right:
                    return {RIGHT_ARROW, {0, 0}};
                case sf::Keyboard::Space:
                    return {SPACE, {0, 0}};
                case sf::Keyboard::Escape:
                    return {QUIT, {0, 0}};
                case sf::Keyboard::M:
                    return {CALL_MENU, {0, 0}};
                case sf::Keyboard::D:
                    return {SWITCH_DISPLAY, {0, 0}};
                case sf::Keyboard::G:
                    return {SWITCH_GAME, {0, 0}};
                case sf::Keyboard::R:
                    return {RESTART_GAME, {0, 0}};
                default:
                    break;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
            sf::Vector2f realPos = _window->mapPixelToCoords(pixelPos);
            return {LEFT_CLICK, {static_cast<int>(realPos.x) / 64, static_cast<int>(realPos.y) / 54}};
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            sf::Vector2i pixelPos(event.mouseButton.x, event.mouseButton.y);
            sf::Vector2f realPos = _window->mapPixelToCoords(pixelPos);
            return {RIGHT_CLICK, {static_cast<int>(realPos.x) / 64, static_cast<int>(realPos.y) / 54}};
        }
    }
    return {UNKNOWN, {0, 0}};
}

int SFML::createWindow()
{
    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "SFML ARCADE MENU");
    if (!_window)
        throw ArcadeException("Error : fail to create window");
    _window->setFramerateLimit(60);
    if (!_font.loadFromFile(FONT_PATH))
        throw ArcadeException("Error : fail to load font");
    _colors.clear();
    _colors.insert({RED, sf::Color::Red});
    _colors.insert({GREEN, sf::Color::Green});
    _colors.insert({BLUE, sf::Color::Blue});
    _colors.insert({YELLOW, sf::Color::Yellow});
    _colors.insert({BLACK, sf::Color::Black});
    _colors.insert({WHITE, sf::Color::White});
    _colors.insert({MAGENTA, sf::Color::Magenta});
    _colors.insert({CYAN, sf::Color::Cyan});

    return 0;
}

void SFML::closeWindow()
{
    if (_window)
        _window->close();
}

void SFML::drawText(pos position, float size, std::string text, Color color) 
{
    sf::Text textdraw;
    textdraw.setFont(_font);
    textdraw.setCharacterSize(static_cast<unsigned int>(40 * size));
    textdraw.setString(text);

    auto elem = _colors.find(color);
    sf::Color colordraw = (elem != _colors.end()) ? elem->second : sf::Color::White;
    textdraw.setFillColor(colordraw);

    auto sizeWindow = recoverWindowSize();
    float windowWidth = static_cast<float>(std::get<0>(sizeWindow));
    float windowHeight = static_cast<float>(std::get<1>(sizeWindow));

    float x_d, y_d;
    
    if (position.x == -1) {
        sf::FloatRect textBounds = textdraw.getLocalBounds();
        x_d = (windowWidth - textBounds.width) / 2.f - textBounds.left;
    } else
        x_d = position.x * (windowWidth / 30.f);
    y_d = position.y * (windowHeight / 20.f);
    textdraw.setPosition(x_d, y_d);
    _window->draw(textdraw);
}

void SFML::drawSprite(pos position, int rotation, float size, std::string name)
{
    auto elem = _textures.find(name);
    if (elem == _textures.end())
        return;
    sf::Sprite sprite(elem->second);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    float scaleX = (64.f / bounds.width) * size;
    float scaleY = (54.f / bounds.height) * size;
    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(position.x * 64.f + 32.f, position.y * 54.f + 27.f);
    sprite.setRotation(static_cast<float>(rotation));
    _window->draw(sprite);
}

int SFML::loadTexture(std::string game)
{
    std::string path = "assets/" + game + "/images";

    std::cout << path << std::endl;
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (!entry.is_regular_file())
                continue;
            sf::Texture texture;
            if (!texture.loadFromFile(entry.path().string())) {
                std::cerr << "fail to load " << entry.path().string() << std::endl;
                continue;
            }
            _textures[entry.path().stem().string()] = std::move(texture);
            std::cout << "texture loaded : " << entry.path().stem().string() << std::endl;
        }
    } else {
        throw ArcadeException("directory: " + path + " not found");
    }
    if (!_font.loadFromFile(FONT_PATH))
        throw ArcadeException("fail to load font");
    _colors.insert({RED, sf::Color::Red});
    _colors.insert({GREEN, sf::Color::Green});
    _colors.insert({BLUE, sf::Color::Blue});
    _colors.insert({YELLOW, sf::Color::Yellow});
    _colors.insert({BLACK, sf::Color::Black});
    _colors.insert({WHITE, sf::Color::White});
    _colors.insert({MAGENTA, sf::Color::Magenta});
    _colors.insert({CYAN, sf::Color::Cyan});
    return 0;
}

int SFML::loadSound(std::string game)
{
    std::string path = "assets/" + game + "/sounds";

    if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (!entry.is_regular_file())
                continue;
            sf::SoundBuffer buffer;
            if (!buffer.loadFromFile(entry.path().string())) {
                std::cerr << "fail to load " << entry.path().string() << std::endl;
                continue;
            }
            std::string name = entry.path().stem().string();
            _soundBuffers[name] = std::move(buffer);
            _sounds[name].setBuffer(_soundBuffers[name]);
            std::cout << "sound loaded : " << name << std::endl;
        }
    } else {
        throw ArcadeException("Directory: " + path + " not found");
    }
    return 0;
}

int SFML::playSound(std::string sound_name_in_map)
{
    _sounds[sound_name_in_map].play();
    return 0;
}  

std::string SFML::loadName()
{
    std::string name;

    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                return "";
            if (event.type == sf::Event::Closed)
                return name.empty() ? "keryan poulet druelle" : name;
            if (event.type == sf::Event::TextEntered) {
                uint32_t c = event.text.unicode;
                if (c == '\r')
                    return name.empty() ? "keryan poulet druelle" : name;
                else if (c == '\b' && !name.empty())
                    name.pop_back();
                else if (c >= 32 && c < 128 && name.size() < 20)
                    name += (char)c;
            }
        }

        _window->clear();
        drawText({POS_CENTER.x - 8, POS_CENTER.y - 4}, 3.0f, "Choisissez votre nom :", WHITE);
        drawText({POS_CENTER.x - 8, POS_CENTER.y + 1}, 2.5f, name + "|", CYAN);
        _window->display();
    }
    return name.empty() ? "Player1" : name;
}

std::tuple<int, int> SFML::recoverWindowSize()
{
    return {1920,1080};
}

void SFML::drawBackground(std::string background_name)
{
    auto elem = _textures.find(background_name);
    if (elem == _textures.end())
        return;
    sf::Sprite sprite(elem->second);
    float boundX = static_cast<float>(64)  / sprite.getLocalBounds().width;
    float boundY = static_cast<float>(54) / sprite.getLocalBounds().height;
    sprite.setPosition(0, 0);
    _window->draw(sprite);
}

extern "C" ILib* entryPoint()
{
    return new SFML();
}