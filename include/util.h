#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <random>

#include<choice.h>

const char* toString(Choice choice) {
	switch (choice) {
	case Choice::Paper:
		return "Paper";
	case Choice::Rock:
		return "Rock";
	case Choice::Scissors:
		return "Scissors";
//	case Choice::None:
// return "None";
	default:
		throw std::bad_cast();
	}
}

const char* to_symbol(Choice choice) {
	switch (choice) {
	case Choice::Paper:
		return "👋";
	case Choice::Rock:
		return "✊";
	case Choice::Scissors:
		return "✌️";
	default:
		throw std::bad_cast();
	}
}

#endif
