#include "u128.h"

using namespace kake;

u128::u128() : myLower(0), myHigher(0) {

}

u128::u128(u64 low) : myLower(low), myHigher(0) {

}

u128::u128(u64 low, u64 high) : myLower(low), myHigher(high) {

}

u128 u128::operator+(u128 u) {
	u128 sum(low() + u.low(), high() + u.high());
	if (sum.low() < low()) ++sum.myHigher;
	return sum;
}

u128 u128::operator-(u128 u) {
	u128 difference(low() - u.low(), high() - u.high());
	if (difference.low() > low()) --difference.myHigher;
	return difference;
}

bool u128::operator<(const u128& u) const {
	if (high() == u.high()) return low() < u.low();
	return high() < u.high();
}

bool u128::operator==(u128 u) const {
	return high() == u.high() && low() == u.low();
}

bool u128::operator!=(u128 u) const{
	return !(*this == u);
}

u64 u128::high() const {
	return myHigher;
}

u64 u128::low() const {
	return myLower;
}

unsigned u128::hash() const {
	return static_cast<unsigned>(myLower % 0xffffffff);
}
