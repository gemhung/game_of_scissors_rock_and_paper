#ifndef UTIL_HEADER
#define UTIL_HEADER

#include <random>

#include<choice.h>

auto toString(Choice choice) -> std::string_view {
	switch (choice) {
	case Choice::Paper:
		return "Paper";
	case Choice::Rock:
		return "Rock";
	case Choice::Scissors:
		return "Scissors";
	}
}

auto to_symbol(Choice choice) -> std::string_view {
	switch (choice) {
	case Choice::Paper:
		return "👋";
	case Choice::Rock:
		return "✊";
	case Choice::Scissors:
		return "✌️";
	}
}

#endif
