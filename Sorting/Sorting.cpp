// Sorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

bool PRINT_ANYTHING = false;

std::vector<int> sort_radix(std::vector<int> input) {
	std::vector<int> buckets[10] = {};
	int max_digits = -1;
	int iteration = 1;
	while (true) {
		if (PRINT_ANYTHING) std::cout << "iteration " << iteration << std::endl;
		for (int index = 0; index < input.size(); index++) {
			int number = input[index];
			int digits = floor(log10(number)) + 1;
			int digit = ((int) floor(number / pow(10, iteration - 1))) % 10;
			max_digits = std::max(max_digits, digits);
			buckets[digit].push_back(number);
		}
		input.clear();
		for (int bucket = 0; bucket < 10; bucket++) {
			if (PRINT_ANYTHING) std::cout << "B " << bucket << ": ";
			for (int index = 0; index < buckets[bucket].size(); index++) {
				if (PRINT_ANYTHING) std::cout << buckets[bucket][index] << " ";
				input.push_back(buckets[bucket][index]);
			}
			if (PRINT_ANYTHING) std::cout << std::endl;
			buckets[bucket].clear();
		}
		if (++iteration > max_digits) {
			break;
		}
	}
	return input;
}

bool isSorted(std::vector<int> input) {
	for (int index = 0; index < input.size() - 1; index++) {
		if (input[index] > input[index + 1]) {
			return false;
		}
	}
	return true;
}

std::vector<int> sort_bogo(std::vector<int> input) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(input.begin(), input.end(), std::default_random_engine(seed));
	return input;
}

std::vector<int> sort_bubble(std::vector<int> input) {
	for (int outter = 0; outter < input.size(); outter++) {
		for (int inner = 0; inner < input.size() - outter - 1; inner++) {
			if (input[inner] > input[inner + 1]) {
				int temp = input[inner];
				input[inner] = input[inner + 1];
				input[inner + 1] = temp;
			}
		}
	}
	return input;
}


void option_radix(std::vector<int> input) {
	std::vector<int> radix_output = sort_radix(input);
	if (PRINT_ANYTHING) {
		std::cout << "Radix Sort: \n";
		for (int i = 0; i < radix_output.size(); i++) {
			std::cout << radix_output[i] << " ";
			if (i % 10 == 9) {
				std::cout << std::endl;
			}
		}
	}
}

void option_bogo(std::vector<int> input) {
	int iterations = 0;
	while (!isSorted(input)) {
		input = sort_bogo(input);
		iterations++;
	}
	
	if (PRINT_ANYTHING) {
		std::cout << std::endl;
		std::cout << "Bogo Sort: \n";
		for (int i = 0; i < input.size(); i++) {
			std::cout << input[i] << " ";
			if (i % 10 == 9) {
				std::cout << std::endl;
			}
		}
	}
	
	std::cout << std::endl << "done after " << iterations << " iterations" << std::endl;
}

void option_bubble(std::vector<int> input) {
	input = sort_bubble(input);
	if (PRINT_ANYTHING) {
		std::cout << "Bubble Sort: \n";

		for (int i = 0; i < input.size(); i++) {
			std::cout << input[i] << " ";
			if (i % 10 == 9) {
				std::cout << std::endl;
			}
		}
	}
}

int main()
{

	// ask for input parameters
	std::cout << "Enter the number of elements to sort: ";
	int SORT_SIZE = 100;
	std::cin >> SORT_SIZE;

	std::cout << "Enter the max value for the elements: ";
	int MAX_NUMBER = 99999999;
	std::cin >> MAX_NUMBER;

	std::cout << "Print process and results? (y/n): ";
	char PRINT_RESULTS = 'n';
	std::cin >> PRINT_RESULTS;

	PRINT_ANYTHING = (PRINT_RESULTS == 'y');
	
	// create a vector with random number inputs
	std::vector<int> sample_numbers = {};
	for (int i = 0; i < SORT_SIZE; i++) {
		sample_numbers.push_back(rand() % MAX_NUMBER);
	}

	while (true) {

		// ask for what sorting algorithm to use
		std::cout << std::endl << "What sorting algorithm do you want to use?" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Radix Sort" << std::endl;
		std::cout << "2. Bogo Sort" << std::endl;
		std::cout << "3. Bubble Sort" << std::endl;

		int choice = 0;
		std::cin >> choice;

		auto start = std::chrono::high_resolution_clock::now();
		switch (choice) {
		case 1:
			option_radix(sample_numbers);
			break;
		case 2:
			option_bogo(sample_numbers);
			break;
		case 3:
			option_bubble(sample_numbers);
			break;
		case 0:
		default:
			exit(0);
			break;
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::endl << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
