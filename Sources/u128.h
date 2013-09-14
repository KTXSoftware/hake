#pragma once

namespace kake {
#ifdef SYS_WINDOWS
	typedef unsigned __int64 u64;
#else
	typedef unsigned long long u64;
#endif

#ifdef SYS_WINDOWS
	typedef __int64 s64;
#else
	typedef long long s64;
#endif

	class u128 {
	public:
		u128();
		u128(u64 low);
		u128(u64 low, u64 high);
		u128 operator+(u128 u);
		u128 operator-(u128 u);
		bool operator<(const u128& other) const;
		bool operator==(u128 u) const;
		bool operator!=(u128 u) const;
		u64 high() const;
		u64 low() const;
		unsigned hash() const;
	private:
		u64 myHigher;
		u64 myLower;
	};
}
