#pragma once

#include "../defines.h"
#include <optional>


namespace evo{

	EVO_NODISCARD constexpr auto stringSize(const char* str, size_t max_length = 100) noexcept -> size_t {
		for(size_t i = 0; i < max_length + 1; i+=1){
			if(str[i] == '\0'){
				return i;
			}
		}

		return max_length;
	};



	// optional is nullopt if exceeds the max string length
	EVO_NODISCARD constexpr auto stringsEqual(const char* str1, const char* str2, size_t max_length = 100) noexcept -> std::optional<bool> {
		for(size_t i = 0; i < max_length + 1; i+=1){
			if(str1[i] == str2[i]){
				if(str1[i] == '\0'){
					return true;
				}

				continue;
			}

			return false;
		}

		return std::nullopt;
	};






	EVO_NODISCARD constexpr auto isLowerLetter(char character) noexcept -> bool {
		switch(character){
			case 'a': case 'b':
			case 'c': case 'd':
			case 'e': case 'f':
			case 'g': case 'h':
			case 'i': case 'j':
			case 'k': case 'l':
			case 'm': case 'n':
			case 'o': case 'p':
			case 'q': case 'r':
			case 's': case 't':
			case 'u': case 'v':
			case 'w': case 'x':
			case 'y': case 'z':
				return true;
		};

		return false;
	};


	EVO_NODISCARD constexpr auto isUpperLetter(char character) noexcept -> bool {
		switch(character){
			case 'A': case 'B':
			case 'C': case 'D':
			case 'E': case 'F':
			case 'G': case 'H':
			case 'I': case 'J':
			case 'K': case 'L':
			case 'M': case 'N':
			case 'O': case 'P':
			case 'Q': case 'R':
			case 'S': case 'T':
			case 'U': case 'V':
			case 'W': case 'X':
			case 'Y': case 'Z':
				return true;
		};

		return false;
	};

	EVO_NODISCARD constexpr auto isLetter(char character) noexcept -> bool {
		return isLowerLetter(character) || isUpperLetter(character);
	};


	EVO_NODISCARD constexpr auto isNumber(char character) noexcept -> bool {
		switch(character){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return true;
		};

		return false;
	};


	EVO_NODISCARD constexpr auto isHexNumber(char character) noexcept -> bool {
		switch(character){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case 'a': case 'A':
			case 'b': case 'B':
			case 'c': case 'C':
			case 'd': case 'D':
			case 'e': case 'E':
			case 'f': case 'F':
				return true;
		};

		return false;
	};

	EVO_NODISCARD constexpr auto isOctalNumber(char character) noexcept -> bool {
		switch(character){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
				return true;
		};

		return false;
	};


	EVO_NODISCARD constexpr auto isAlphaNumeric(char character) noexcept -> bool {
		return isLetter(character) || isNumber(character);
	};


	EVO_NODISCARD constexpr auto isWhitespace(char character) noexcept -> bool {
		switch(character){
			case ' ':
			case '\n':
			case '\r':
			case '\t':
				return true;
		};

		return false;
	};


	
	// based on data from: https://theasciicode.com.ar/ 
	//               also: https://en.cppreference.com/w/c/language/escape
	EVO_NODISCARD constexpr auto printCharName(char character) noexcept -> const char* {
		switch(character){
			// ASCII control characters non printable 
			break; case '\0': return "\\0";
			break; case  1: return "SOH"; // ( Start of Header )
			break; case  2: return "STX"; // ( Start of Text )
			break; case  3: return "ETX"; // ( End of Text, hearts card suit )
			break; case  4: return "EOT"; // ( End of Transmission, diamonds card suit )
			break; case  5: return "ENQ"; // ( Enquiry, clubs card suit )
			break; case  6: return "ACK"; // ( Acknowledgement, spade card suit )
			break; case  7: return "\\a"; // ( Bell )
			break; case  8: return "\\b"; // ( Backspace )
			break; case  9: return "\\t"; // ( Horizontal Tab )
			break; case 10: return "\\n"; // ( Line feed )
			break; case 11: return "\\v"; // ( Vertical Tab, male symbol, symbol for Mars )
			break; case 12: return "\\f"; // ( Form feed, female symbol, symbol for Venus )
			break; case 13: return "\\r"; // ( Carriage return )
			break; case 14: return "SO"; // ( Shift Out )
			break; case 15: return "SI"; // ( Shift In )
			break; case 16: return "DLE"; // ( Data link escape )
			break; case 17: return "DC1"; // ( Device control 1 )
			break; case 18: return "DC2"; // ( Device control 2 )
			break; case 19: return "DC3"; // ( Device control 3 )
			break; case 20: return "DC4"; // ( Device control 4 )
			break; case 21: return "NAK"; // ( NAK Negative-acknowledge )
			break; case 22: return "SYN"; // ( Synchronous idle )
			break; case 23: return "ETB"; // ( End of trans. block )
			break; case 24: return "CAN"; // ( Cancel )
			break; case 25: return "EM"; // ( End of medium )
			break; case 26: return "SUB"; // ( Substitute )
			break; case 27: return "\\e"; // ( Escape )
			break; case 28: return "FS"; // ( File separator )
			break; case 29: return "GS"; // ( Group separator )
			break; case 30: return "RS"; // ( Record separator )
			break; case 31: return "US"; // ( Unit separator )
			break; case 127: return "DEL"; // ( Delete )

			// Printable ASCII characters :
			// ( alphanumeric, symbols and signs )
			break; case 32: return "space"; // ( Space )
			break; case 33: return "!"; // ( Exclamation mark )
			break; case 34: return "\""; // ( Double quotes ; Quotation mark ; speech marks )
			break; case 35: return "#"; // ( Number sign )
			break; case 36: return "$"; // ( Dollar sign )
			break; case 37: return "%"; // ( Percent sign )
			break; case 38: return "&"; // ( Ampersand )
			break; case 39: return "'"; // ( Single quote or Apostrophe )
			break; case 40: return "("; // ( round brackets or parentheses, opening round bracket )
			break; case 41: return ")"; // ( parentheses or round brackets, closing parentheses )
			break; case 42: return "*"; // ( Asterisk )
			break; case 43: return "+"; // ( Plus sign )
			break; case 44: return ","; // ( Comma )
			break; case 45: return "-"; // ( Hyphen , minus sign )
			break; case 46: return "."; // ( Dot, full stop )
			break; case 47: return "/"; // ( Slash , forward slash , fraction bar , division slash )
			break; case 48: return "0"; // ( number zero )
			break; case 49: return "1"; // ( number one )
			break; case 50: return "2"; // ( number two )
			break; case 51: return "3"; // ( number three )
			break; case 52: return "4"; // ( number four )
			break; case 53: return "5"; // ( number five )
			break; case 54: return "6"; // ( number six )
			break; case 55: return "7"; // ( number seven )
			break; case 56: return "8"; // ( number eight )
			break; case 57: return "9"; // ( number nine )
			break; case 58: return ":"; // ( Colon )
			break; case 59: return ";"; // ( Semicolon )
			break; case 60: return "<"; // ( Less-than sign )
			break; case 61: return "="; // ( Equals sign )
			break; case 62: return ">"; // ( Greater-than sign ; Inequality )
			break; case 63: return "?"; // ( Question mark )
			break; case 64: return "@"; // ( At sign )
			break; case 65: return "A"; // ( Capital letter A )
			break; case 66: return "B"; // ( Capital letter B )
			break; case 67: return "C"; // ( Capital letter C )
			break; case 68: return "D"; // ( Capital letter D )
			break; case 69: return "E"; // ( Capital letter E )
			break; case 70: return "F"; // ( Capital letter F )
			break; case 71: return "G"; // ( Capital letter G )
			break; case 72: return "H"; // ( Capital letter H )
			break; case 73: return "I"; // ( Capital letter I )
			break; case 74: return "J"; // ( Capital letter J )
			break; case 75: return "K"; // ( Capital letter K )
			break; case 76: return "L"; // ( Capital letter L )
			break; case 77: return "M"; // ( Capital letter M )
			break; case 78: return "N"; // ( Capital letter N )
			break; case 79: return "O"; // ( Capital letter O )
			break; case 80: return "P"; // ( Capital letter P )
			break; case 81: return "Q"; // ( Capital letter Q )
			break; case 82: return "R"; // ( Capital letter R )
			break; case 83: return "S"; // ( Capital letter S )
			break; case 84: return "T"; // ( Capital letter T )
			break; case 85: return "U"; // ( Capital letter U )
			break; case 86: return "V"; // ( Capital letter V )
			break; case 87: return "W"; // ( Capital letter W )
			break; case 88: return "X"; // ( Capital letter X )
			break; case 89: return "Y"; // ( Capital letter Y )
			break; case 90: return "Z"; // ( Capital letter Z )
			break; case 91: return "["; // ( square brackets or box brackets, opening bracket )
			break; case 92: return "\\"; // ( Backslash , reverse slash )
			break; case 93: return "]"; // ( box brackets or square brackets, closing bracket )
			break; case 94: return "^"; // ( Circumflex accent or Caret )
			break; case 95: return "_"; // ( underscore , understrike , underbar or low line )
			break; case 96: return "`"; // ( Grave accent )
			break; case 97: return "a"; // ( Lowercase letter a , minuscule a )
			break; case 98: return "b"; // ( Lowercase letter b , minuscule b )
			break; case 99: return "c"; // ( Lowercase letter c , minuscule c )
			break; case 100: return "d"; // ( Lowercase letter d , minuscule d )
			break; case 101: return "e"; // ( Lowercase letter e , minuscule e )
			break; case 102: return "f"; // ( Lowercase letter f , minuscule f )
			break; case 103: return "g"; // ( Lowercase letter g , minuscule g )
			break; case 104: return "h"; // ( Lowercase letter h , minuscule h )
			break; case 105: return "i"; // ( Lowercase letter i , minuscule i )
			break; case 106: return "j"; // ( Lowercase letter j , minuscule j )
			break; case 107: return "k"; // ( Lowercase letter k , minuscule k )
			break; case 108: return "l"; // ( Lowercase letter l , minuscule l )
			break; case 109: return "m"; // ( Lowercase letter m , minuscule m )
			break; case 110: return "n"; // ( Lowercase letter n , minuscule n )
			break; case 111: return "o"; // ( Lowercase letter o , minuscule o )
			break; case 112: return "p"; // ( Lowercase letter p , minuscule p )
			break; case 113: return "q"; // ( Lowercase letter q , minuscule q )
			break; case 114: return "r"; // ( Lowercase letter r , minuscule r )
			break; case 115: return "s"; // ( Lowercase letter s , minuscule s )
			break; case 116: return "t"; // ( Lowercase letter t , minuscule t )
			break; case 117: return "u"; // ( Lowercase letter u , minuscule u )
			break; case 118: return "v"; // ( Lowercase letter v , minuscule v )
			break; case 119: return "w"; // ( Lowercase letter w , minuscule w )
			break; case 120: return "x"; // ( Lowercase letter x , minuscule x )
			break; case 121: return "y"; // ( Lowercase letter y , minuscule y )
			break; case 122: return "z"; // ( Lowercase letter z , minuscule z )
			break; case 123: return "{"; // ( braces or curly brackets, opening braces )
			break; case 124: return "|"; // ( vertical-bar, vbar, vertical line or vertical slash )
			break; case 125: return "}"; // ( curly brackets or braces, closing curly brackets )
			break; case 126: return "~"; // ( Tilde ; swung dash )
		};
		

		return "{{??}}";
	};



	EVO_NODISCARD constexpr auto boolStr(bool boolean) noexcept -> const char* {
		if(boolean){
			return "true";
		}else{
			return "false";
		}
	};



	
};