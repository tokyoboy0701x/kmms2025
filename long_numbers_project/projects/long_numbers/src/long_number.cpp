#include "long_number.hpp"

using ordo::LongNumber;
		
LongNumber::LongNumber() {
	length = 1; 
	sign = 0;	
	numbers = new int[length];
	numbers[0] = 0;
}

LongNumber::LongNumber(int length, int sign) {
	this->length = length;
	this->sign = sign;

	if (length > 0) {
		numbers = new int[length];
		for (int i = 0; i < length; i++) {
			numbers[i] = 0;
		}
	}
	else {
		numbers = nullptr;
	}
}

LongNumber::LongNumber(const char* const str) {
	if (str[0] == '-') {
		sign = 1;
	}
	else {
		sign = 0;
	}
	length = get_length(str);
	numbers = new int[length];

	int start = sign;
	for (int i = 0; i < length; i++) {
		numbers[i] = str[start + length - i - 1] - '0';
	}
}

LongNumber::LongNumber(const LongNumber& x) {
	length = x.length;
	sign = x.sign;
	numbers = new int[length];

	for (int i = 0; i < length; i++) {
        numbers[i] = x.numbers[i];
    }
}

LongNumber::LongNumber(LongNumber&& x) {
	numbers = x.numbers;
	length = x.length;
	sign = x.sign;

	x.numbers = nullptr;
	x.length = 0;
	x.sign = 0;
}

LongNumber::~LongNumber() {
	delete[] numbers;
	numbers = nullptr;
	length = 0;
	sign = 0;
}

LongNumber& LongNumber::operator = (const char* const str) {
	delete[] numbers;

	if (str[0] == '-') {
		sign = 1;
	}
	else {
		sign = 0;
	}
	length = get_length(str);
	numbers = new int[length];

	int start = sign;
	for (int i = 0; i < length; i++) {
		numbers[i] = str[start + length - i - 1] - '0';
	}

	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x) {
		return *this;
	}

	delete[] numbers;

	length = x.length;
	sign = x.sign;
	numbers = new int[length];
	for (int i = 0; i < length; i++) {
		numbers[i] = x.numbers[i];
	}

	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if (this == &x) {
		return *this;
	}

	delete[] numbers; 

	numbers = x.numbers;
	length = x.length;
	sign = x.sign;

	x.numbers = nullptr;
	x.length = 0;
	x.sign = 0;

	return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
	if (sign != x.sign) {
		return false;
	}
	if (length != x.length) {
		return false;
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			return false;
		}
	}

	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	if (sign != x.sign) {
		return true;
	}
	if (length != x.length) {
		return true;
	}
	for (int i = 0; i < length; i++) {
		if (numbers[i] != x.numbers[i]) {
			return true;
		}
	}

	return false;
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (sign != x.sign) {
		return sign == 0;
	}

	if (sign == 0) {
		if (length != x.length) {
			return length > x.length;
		}

		for (int i = length - 1; i >= 0; i--) {
			if (numbers[i] != x.numbers[i]) {
				return numbers[i] > x.numbers[i];
			}
		}
	}
	else {
		if (length != x.length) {
			return length < x.length;
		}

		for (int i = length - 1; i >= 0; i--) {
			if (numbers[i] != x.numbers[i]) {
				return numbers[i] < x.numbers[i];
			}
		}
	}

	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	if (sign != x.sign) {
		return sign == 1;
	}

	if (sign == 0) {
		if (length != x.length) {
			return length < x.length;
		}

		for (int i = length - 1; i >= 0; i--) {
			if (numbers[i] != x.numbers[i]) {
				return numbers[i] < x.numbers[i];
			}
		}
	}
	else {
		if (length != x.length) {
			return length > x.length;
		}

		for (int i = length - 1; i >= 0; i--) {
			if (numbers[i] != x.numbers[i]) {
				return numbers[i] > x.numbers[i];
			}
		}
	}

	return false;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	if (sign != x.sign) {
		if (sign == 0) {
			LongNumber temp = x;
			temp.sign = 0;
			return *this - temp; 
		}
		else {
			LongNumber temp = *this;
			temp.sign = 0;
			return x - temp;
		}
	}
	else {
		
		int max_length = (length > x.length) ? length : x.length;
		LongNumber result(max_length + 1, sign);

		int i = 0;
		int remainder = 0;

		for (; i < length && i < x.length; i++) {
			int sum = numbers[i] + x.numbers[i] + remainder;
			result.numbers[i] = sum % 10;
			remainder = sum / 10;
		}

		if (length > x.length) {
			for (; i < length; i++) {
				int sum = numbers[i] + remainder; 
				result.numbers[i] = sum % 10;
				remainder = sum / 10;
			}
		}
		else {
			for (; i < x.length; i++) {
				int sum = x.numbers[i] + remainder;
				result.numbers[i] = sum % 10;
				remainder = sum / 10;
			}
		}

		if (remainder > 0) {
			result.numbers[max_length] = remainder;
		}
		else {
			result.length = max_length;
		}
		return result;
	}
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	if (sign != x.sign) {
		if (sign == 0) {
			LongNumber temp = x;
			temp.sign = 0;
			return *this + temp;
		}
		else {
			LongNumber temp = x;
			temp.sign = 1;
			return *this + temp;
		}
	}
	else {
		if (*this == x) {
			LongNumber zero;
			return zero;
		}

		LongNumber abs_this = *this;
		LongNumber abs_x = x;
		abs_this.sign = 0;
		abs_x.sign = 0;

		bool abs_this_bigger = (abs_this > abs_x);

		int result_sign;
		const LongNumber* bigger_abs;
		const LongNumber* smaller_abs;

		if (abs_this_bigger) {
			if (sign == 0) {
				result_sign = 0;
			}
			else {
				result_sign = 1;
			}
			bigger_abs = &abs_this;
			smaller_abs = &abs_x;
		}
		else {
			if (sign == 0) {
				result_sign = 1;
			}
			else {
				result_sign = 0;
			}
			bigger_abs = &abs_x;
			smaller_abs = &abs_this;
		}

		LongNumber result(bigger_abs->length, result_sign);

		int borrow = 0;
		int i = 0;

		for (; i < smaller_abs->length; i++) {
			int diff = bigger_abs->numbers[i] - smaller_abs->numbers[i] - borrow;

			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else {
				borrow = 0;
			}

			result.numbers[i] = diff;
		}

		for (; i < bigger_abs->length; i++) {
			int diff = bigger_abs->numbers[i] - borrow;

			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else {
				borrow = 0;
			}

			result.numbers[i] = diff;
		}

		while (result.length > 1 && result.numbers[result.length - 1] == 0) {
			result.length--;	
		}
		
		return result;
	}
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	int result_sign = (sign == x.sign) ? 0 : 1;

	LongNumber abs_this = *this;
	LongNumber abs_x = x;
	abs_this.sign = 0;
	abs_x.sign = 0;

	LongNumber result(abs_this.length + abs_x.length, result_sign);

	for (int i = 0; i < abs_this.length; i++) {
		int remainder = 0;
		for (int j = 0; j < abs_x.length; j++) {
			int product = abs_this.numbers[i] * abs_x.numbers[j] + result.numbers[i + j] + remainder;
			result.numbers[i + j] = product % 10;
			remainder = product / 10;
		}
		if (remainder > 0) {
			result.numbers[i + abs_x.length] += remainder;
		}
	}

	while (result.length > 1 && result.numbers[result.length - 1] == 0) {
		result.length--;
	}

	return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	if (x.length == 1 && x.numbers[0] == 0) {
		throw std::runtime_error("деление на 0");
	}

	int result_sign = (sign == x.sign) ? 0 : 1;	

	LongNumber abs_this = *this;
	LongNumber abs_x = x;
	abs_this.sign = 0;
	abs_x.sign = 0;

	if (abs_this < abs_x) {
		LongNumber zero;
		return zero;
	}

	LongNumber result(abs_this.length, result_sign);

	LongNumber remainder(1, 0);

	for (int i = abs_this.length - 1; i >= 0; i--) {
        LongNumber temp(remainder.length + 1, 0);
        
        for (int j = 0; j < remainder.length; j++) {
            temp.numbers[j + 1] = remainder.numbers[j];
        }
        temp.numbers[0] = abs_this.numbers[i];
        
        while (temp.length > 1 && temp.numbers[temp.length - 1] == 0) {
            temp.length--;
        }
        
        remainder = temp;

        int quotient = 0;
        LongNumber temp2 = remainder;
        while (temp2 > abs_x || temp2 == abs_x) {
            temp2 = temp2 - abs_x;
            quotient++;
        }
        
        while (temp2.length > 1 && temp2.numbers[temp2.length - 1] == 0) {
            temp2.length--;
        }

		result.numbers[i] = quotient;
		remainder = temp2;
	} 

	while (result.length > 1 && result.numbers[result.length - 1] == 0) {
		result.length--;
	}

	return result;
}	

LongNumber LongNumber::operator % (const LongNumber& x) const {
	if (x.length == 1 && x.numbers[0] == 0) {
		throw std::runtime_error("деление на 0");
	}

	LongNumber quotient = *this / x;
	LongNumber product = quotient * x;
	LongNumber remainder = *this - product;

	return remainder;
}

bool LongNumber::is_negative() const noexcept {
	return sign == 1;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	int i = 0;
	if (str[i] == '-') {
		i = 1;
	} 
	int c = 0;
	while (str[i] != '\0') {
		c++;
		i++;
	}

	return c;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace ordo {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if (x.sign == 1) {
			os << '-';
		}

		for (int i = x.length - 1; i >= 0; i--) {
			os << x.numbers[i];
		}

		return os;
	}
}