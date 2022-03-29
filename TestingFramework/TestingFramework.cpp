#include <iostream>
#include <string>
#include <map>
#include <set>
#include <exception>
#include <sstream>

using namespace std;

using Map = map<string, set<string>>;

template <typename T>
ostream& operator << (ostream& stream, const set<T>& set) {
	stream << "{";
	bool first = true;
	for (const auto& el : set) {
		if (!first) {
			stream << ", ";
		}
		first = false;
		stream << el;
	}
	return stream << "}";
}

template <typename Key, typename Value>
ostream& operator << (ostream& stream, const map<Key, Value>& m) {
	stream << "{";
	bool first = true;
	for (const auto& el : m) {
		if (!first) {
			stream << ", ";
		}
		first = false;
		stream << el.first << ": " << el.second;
	}
	return stream << "}";
}

template <typename T, typename U>
void AssertEqual(const T& t, const U& u, const string& hint={}) {
	if (t != u) {
		ostringstream os;
		os << t << " != " << u;
		if (!hint.empty()) {
			os << "; hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool bool_value, const string& hint) {
	AssertEqual(bool_value, true, hint);
}

class TestRunner {
public:
	template <typename TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (runtime_error& err) {
			++fail_count;
			cerr << test_name << " failed: " << err.what() << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " test(-s) failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

void TestAll() {
	TestRunner test_runner;
	// run your tests from test_runner instance there
}

int main() {
	TestAll();
	return 0;
}
