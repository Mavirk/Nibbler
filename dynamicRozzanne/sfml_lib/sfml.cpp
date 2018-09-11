#include "sfml.hpp"

extern "C" SFML* create_object(){
	std::cout << "Lib SFML Object created" << std::endl;
	return new SFML;
}

extern "C" void destroy_object( SFML* object ){
	delete object;
	std::cout << "Lib SFML Object destroyed" << std::endl;
}

SFML::SFML( void ) {
	this->_isRunning = true;
	this->_win = NULL;
	std::cout << "Making SFML" << std::endl;
	return ;
}

SFML::SFML( const SFML& copy ) {
	*this = copy;
}

SFML&	SFML::operator=( const SFML& rhs ) {
	this->maxWidth = rhs.maxWidth;
	this->maxHeight = rhs.maxHeight;
	this->_win = new sf::RenderWindow( sf::VideoMode( rhs.maxWidth, rhs.maxHeight ), "Snake Game SFML" );
	this->_font = rhs._font;
	this->_isRunning = rhs._isRunning;
	this->_size = rhs._size;
	return *this;
}

SFML::~SFML( void ) {
	this->_win->close();
	std::cout << "Ending SFML" << std::endl;
	return ;
}

bool	SFML::init( int width, int height, int size ) {
	std::cout << "INIT WINDOW" << std::endl;
	this->_size = size * 2;
	this->maxWidth = width * 2;
	this->maxHeight = height * 2;

	this->_win = new sf::RenderWindow( sf::VideoMode( this->maxWidth, this->maxHeight ), "Snake Game SFML" );

	if ( this->_win->isOpen() ) {
		std::cout << "The window is open" << std::endl;
		this->_isRunning = true;
	} else {
		std::cout << "Error: The window did not open" << std::endl;
		this->_isRunning = false;
		return false;
	}

	if ( !this->_font.loadFromFile( "OpenSans-ExtraBold.ttf" ) ) {
		this->_isRunning = false;
		return false;
	}

	return true;
}

char	SFML::handleInput( void ) {
	sf::Event	event;
	char		input = '\0';

	if ( this->_win->pollEvent( event ) ) {
		switch ( event.type ) {
			case sf::Event::KeyPressed:
				if ( event.key.code == sf::Keyboard::Left ) {
					input = 'l';
				} else if ( event.key.code == sf::Keyboard::Right ) {
					input = 'r';
				} else if ( event.key.code == sf::Keyboard::Up ) {
					input = 'u';
				} else if ( event.key.code == sf::Keyboard::Down ) {
					input = 'd';
				} else if ( event.key.code == sf::Keyboard::Num1 ) {
					input = '1';
				} else if ( event.key.code == sf::Keyboard::Num2 ) {
					input = '2';
				} else if ( event.key.code == sf::Keyboard::Num3 ) {
					input = '3';
				} else if ( event.key.code == sf::Keyboard::Escape ) {
					this->_isRunning = false;
				}
				break ;
			case sf::Event::Closed:
				this->_isRunning = false;
				break ;
			default:
				break ;
		}
	}

	return input;
}

void	SFML::render( Snake& snake ) {

	this->_win->clear( sf::Color( 255, 255, 255 ) );

	// render food
	sf::RectangleShape		rect( sf::Vector2f( this->_size, this->_size ) );
	rect.setFillColor( sf::Color::Cyan );
	rect.setPosition( snake.food.x * 2, snake.food.y * 2 );
	this->_win->draw( rect );
	// render snake
	std::vector<snakePart>	snakeTemp = snake.getSnake();
	for ( unsigned int i = 0; i < snakeTemp.size(); i ++ ){
		sf::RectangleShape		snake( sf::Vector2f( this->_size, this->_size ) );
		if (i == 0)
			snake.setFillColor( sf::Color::Black );
		else snake.setFillColor( sf::Color::Red );
		snake.setPosition( snakeTemp[i].x * 2, snakeTemp[i].y * 2 );
		this->_win->draw( snake );
	}

	// render boader
	sf::RectangleShape		boarderLeft( sf::Vector2f( this->_size, this->maxHeight ) );
	boarderLeft.setFillColor( sf::Color::Black );
	boarderLeft.setPosition( 0, 0 );
	this->_win->draw( boarderLeft );
	sf::RectangleShape		boarderTop( sf::Vector2f( this->maxWidth, this->_size ) );
	boarderTop.setFillColor( sf::Color::Black );
	boarderTop.setPosition( 0, 0 );
	this->_win->draw( boarderTop );
	sf::RectangleShape		boarderRight( sf::Vector2f( this->_size, this->maxHeight ) );
	boarderRight.setFillColor( sf::Color::Black );
	boarderRight.setPosition( this->maxWidth - this->_size, 0 );
	this->_win->draw( boarderRight );
	sf::RectangleShape		boarderBottom( sf::Vector2f( this->maxWidth, this->_size * 3 ) );
	boarderBottom.setFillColor( sf::Color::Black );
	boarderBottom.setPosition( 0, this->maxHeight - (this->_size * 3) );
	this->_win->draw( boarderBottom );

	// render score
	sf::Text	text;
	std::string	score = "Score ";

	score += std::to_string( snake.score );
	text.setFont( this->_font );
	text.setString( score );
	text.setCharacterSize(36);
	text.setFillColor( sf::Color::White );
	text.setPosition( this->_size, this->maxHeight - (this->_size * 3) );
	this->_win->draw( text );

	this->_win->display();
}

bool	SFML::running( void ) {
	return this->_isRunning;
}

void	SFML::clean( void ) {
	this->_win->close();
	std::cout << "SDL game is cleaned" << std::endl;
}